JetDEau_Test ::JetDEau_Test():m_fluid(1),m_air(0),m_cfl_factor(0.25),m_GetCellType(m_w,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound),
m_table(m_hash),m_w(m_table,m_part),m_init(m_w,m_GetCellType,m_v_1_h,m_v_h,5,m_stag,m_part_cond,m_pres_func,m_extrapolate_v,m_out),
m_stag(m_v_h),m_get_v(m_w,m_stag,m_v_1_h),m_boundary_air(2),m_boundary_fluid(3),
m_conv(m_w,m_rungeKutta,m_get_v,m_stag,m_dt,m_GetCellType),
m_grav(m_w,m_g,m_dt,m_fluid,m_GetCellType),
m_viscosity(m_w,m_viscosity_const,m_dt,m_v_1_h,m_GetCellType),
m_out(m_w,m_stag,m_v_h,m_t,1,m_i,m_spos,m_get_v),m_time_step(m_w,m_v_1_h,m_cfl_factor,m_dt,m_GetCellType),
m_pres(m_w,m_v_1_h,m_GetCellType),m_pres_umf(m_w,m_v_1_h,m_GetCellType),m_extrapolate_v(m_w,m_GetCellType,m_v_h,m_v_1_h),
m_move_part(m_w,m_rungeKutta,m_get_v,m_dt),
m_time_out("timing.csv", fstream::out),
m_conv_time(double(sysconf(_SC_CLK_TCK))),
m_part_cond([](Physvector<dim,int> key){return key.Get(2)<-5;}),
m_pres_func([](Physvector<dim,int> key){return 0;}),
m_rho_fluid(1000),m_rho_air(1),m_1_rho_fluid(0.001),m_1_rho_air(1),m_rho_inter(1000),m_1_rho_inter(0.001),m_rho_inter_bound(1000),m_1_rho_inter_bound(0.001),m_conv_1_up(m_w,m_get_v,m_stag,m_dt,m_GetCellType,m_v_h,m_v_1_h)
,m_delete(m_w),m_no_output(true)
{
	#if Use_GooglePerf
		ProfilerStart("perf.prof");
	#endif
	m_N_V=m_stag.GetNeighborsVelocity();
}

void JetDEau_Test::Calculate()
{
	cout<<"update"<<endl;
	m_viscosity_const=0;
	m_time_ticks_deb=times(&m_time_deb);
	m_init.Update();
	m_time_ticks_end=times(&m_time_end);
	m_time_init=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	
	cout<<"timestep"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	m_time_step.Calculate();
	m_time_ticks_end=times(&m_time_end);
	m_time_time_step=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	cout<<"m_dt "<<m_dt<<endl;
	if(m_dt>0.1)
	{
		m_dt=0.1;
	}
	cout<<"convect"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	//m_conv.Calculate();
	m_conv_1_up.Calculate();
	m_time_ticks_end=times(&m_time_end);
	m_time_convect=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	
	
	cout<<"gravity"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	m_grav.Calculate();
	m_time_ticks_end=times(&m_time_end);
	m_time_gravity=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	cout<<"viscosity"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	m_viscosity.Calculate();
	m_time_ticks_end=times(&m_time_end);
	m_time_viscosity=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	
	m_extrapolate_v.Calculate();
	cout<<"pressure"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	//m_pres.Calculate();
	m_pres_umf.Calculate();
	m_time_ticks_end=times(&m_time_end);
	m_time_pressure=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	
	cout<<"extrapolate"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	m_extrapolate_v.Calculate();
	m_time_ticks_end=times(&m_time_end);
	m_time_extrapolate=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	
	cout<<"move particles"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	m_move_part.Calculate();
	m_time_ticks_end=times(&m_time_end);
	m_time_move=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	
	cout<<"output"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	m_t+=m_dt; 
	if(!m_no_output)
	{
		m_out.Calculate();
	}
	m_time_ticks_end=times(&m_time_end);
	m_time_output=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	
	cout<<"end"<<endl;
	m_time_out<<"cell number : "<<m_w.m_mac_grid.size()<<" particle number "<<m_w.m_particle_list.size()<<" time intit: "<<m_time_init<<" time timestep: "<<m_time_time_step<<" time convect: "<<m_time_convect<<" time gravity: "<<m_time_gravity<<" time viscosity: "<<m_time_viscosity<<" time pressure: "<<m_time_pressure<<" time extrapolation: "<<m_time_extrapolate<<" time move: "<<m_time_move<<" time output: "<<m_time_output<<endl;
	#if Use_GooglePerf
		ProfilerFlush();
	#endif
}
