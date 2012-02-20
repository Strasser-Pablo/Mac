JetDEau::JetDEau():m_fluid(1),m_air(0),m_cfl_factor(0.25),
m_table(m_O),m_w(m_table,m_part),m_init(m_w,m_fluid,m_air,m_v_1_h,m_v_h,10,m_stag),
m_stag(m_v_h),m_get_v(m_w,m_stag,m_v_1_h),
m_conv(m_w,m_rungeKutta,m_get_v,m_stag,m_dt,m_fluid,m_N_V),
m_grav(m_w,m_g,m_dt,m_fluid,m_N_V),
m_viscosity(m_w,m_viscosity_const,m_dt,m_v_1_h,m_fluid),
m_out(m_w,m_stag,m_v_h,m_t,1),m_time_step(m_w,m_v_1_h,m_cfl_factor,m_dt,m_fluid),
m_pres(m_w,m_v_1_h,m_fluid),m_pres_umf(m_w,m_v_1_h,m_fluid),m_extrapolate_v(m_w,m_fluid,10,m_N_V),
m_move_part(m_w,m_rungeKutta,m_get_v,m_dt),
m_time_out("timing.csv", fstream::out),
m_conv_time(double(sysconf(_SC_CLK_TCK)))
{
	#if Use_GooglePerf
		ProfilerStart("perf.prof");
	#endif
	m_N_V=m_stag.GetNeighborsVelocity();
	m_t=0;
	m_viscosity_const=0.000001;
	//m_viscosity_const=0;
	Physvector<3,double> speed;
	speed.SetAll(0);
	double speedmax=55;
	m_v_1_h.SetAll(20);
	m_v_h.SetAll(0.05);
	m_v_h.Set(2,1);
	m_v_1_h.Set(2,1);
	int Nx=10;
	int Nz=10;
	int r=10;
	Physvector<3,int> key;
	double r02=pow(r,2);
	for(int i=-Nx;i<=Nx;++i)
	{
		for(int k=-Nz;k<=Nz;++k)
	{
		double r2=pow(i+0.5,2)+pow(k+0.5,2);
		
		if(r2>r02)
		{
			continue;
		}
		speed.Set(2,speedmax*(1-r2/r02));
	key.Set(1,i);
	key.Set(2,0);
	key.Set(3,k);
	mac m(speed,0,0,0);
	m.SetConstSpeed(2,true);
	m_w.m_mac_grid[key]=m;
	}
	}
	
	m_init.PrepareConstSpeed();
	m_init.Update();
	m_extrapolate_v.Calculate2();
	m_g.Set(1,0);
	m_g.Set(2,-9.81);
	m_g.Set(3,0);
	m_out.Calculate();			
}

void JetDEau::Calculate()
{
	cout<<"update"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	m_init.Update();
	m_time_ticks_end=times(&m_time_end);
	m_time_init=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	cout<<"timestep"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	m_time_step.Calculate();
	m_time_ticks_end=times(&m_time_end);
	m_time_time_step=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	if(m_dt>0.1)
	{
		m_dt=0.1;
	}
	cout<<"convect"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	m_conv.Calculate();
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
	m_out.Calculate();
	
	m_time_ticks_end=times(&m_time_end);
	m_time_output=(m_time_ticks_end-m_time_ticks_deb)/m_conv_time;
	
	cout<<"end"<<endl;
	m_time_out<<"cell number : "<<m_w.m_mac_grid.size()<<" particle number "<<m_w.m_particle_list.size()<<" time intit: "<<m_time_init<<" time timestep: "<<m_time_time_step<<" time convect: "<<m_time_convect<<" time gravity: "<<m_time_gravity<<" time viscosity: "<<m_time_viscosity<<" time pressure: "<<m_time_pressure<<" time extrapolation: "<<m_time_extrapolate<<" time move: "<<m_time_move<<" time output: "<<m_time_output<<endl;
	#if Use_GooglePerf
		ProfilerFlush();
	#endif
}