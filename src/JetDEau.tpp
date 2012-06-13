JetDEau::JetDEau():m_fluid(1),m_air(0),m_cfl_factor(0.25),m_GetCellType(m_w,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound),
m_table(m_hash),m_w(m_table,m_part),m_init(m_w,m_GetCellType,m_v_1_h,m_v_h,5,m_stag,m_part_cond,m_pres_func,m_extrapolate_v,m_out),
m_stag(m_v_h),m_get_v(m_w,m_stag,m_v_1_h),m_boundary_air(2),m_boundary_fluid(3),
m_conv(m_w,m_rungeKutta,m_get_v,m_stag,m_dt,m_GetCellType),
m_grav(m_w,m_g,m_dt,m_fluid,m_GetCellType),
m_viscosity(m_w,m_viscosity_const,m_dt,m_v_1_h,m_GetCellType),
m_out_aux(m_w,m_stag,m_v_h,1,m_get_v),
m_out(m_out_aux,1,m_i,m_spos),m_time_step(m_w,m_v_1_h,m_cfl_factor,m_dt,m_GetCellType),
m_pres(m_w,m_v_1_h,m_GetCellType),m_pres_umf(m_w,m_v_1_h,m_GetCellType),m_extrapolate_v(m_w,m_GetCellType,m_v_h,m_v_1_h),
m_move_part(m_w,m_rungeKutta,m_get_v,m_dt),
m_time_out("timing.csv", fstream::out),
m_conv_time(double(sysconf(_SC_CLK_TCK))),
m_part_cond([](Physvector<dim,int> key){return key.Get(2)<-5;}),
m_pres_func([](Physvector<dim,int> key){return 0;}),
m_rho_fluid(1000),m_rho_air(1),m_1_rho_fluid(0.001),m_1_rho_air(1),m_rho_inter(1000),m_1_rho_inter(0.001),m_rho_inter_bound(1000),m_1_rho_inter_bound(0.001),m_conv_1_up(m_w,m_get_v,m_stag,m_dt,m_GetCellType,m_v_h,m_v_1_h),
m_conv_center(m_w,m_get_v,m_stag,m_dt,m_GetCellType,m_v_h,m_v_1_h)
,m_delete(m_w),m_no_output(false),m_calc_circ(m_w,m_v_h)
{
	#if Use_GooglePerf
		ProfilerStart("perf.prof");
	#endif
	m_N_V=m_stag.GetNeighborsVelocity();
}

void JetDEau::SetUp()
{
	m_i=0;
	m_out.SetUp();
	m_t=0; 
	m_viscosity_const=1.307e-6;
	Physvector<dim,double> speed;
	speed.SetAll(0);
	double speedmax=55;
	int Nx=50;
	int Nz=0;
	int r=50;
	m_v_1_h.SetAll(20.0*Nx);
	m_v_h.SetAll(1./(20.0*Nx));
	//m_v_h.Set(2,1);
	//m_v_1_h.Set(2,1);
	Physvector<dim,int> key;
	double r02=pow(r,2);
	if(dim==3)
	{
	for(int i=-Nx;i<=Nx;++i)
	{
		for(int k=-Nz;k<=Nz;++k)
	{
		double r2=pow(i,2)+pow(k,2);
		
		if(r2>r02)
		{
			continue;
		}
		speed.Set(2,speedmax*(1-r2/r02));
	key.Set(1,i);
	key.Set(2,0);
	key.Set(3,k);
	mac m(speed,0,m_boundary_fluid,0);
	m.SetConstSpeed(2,true);
	m_w.m_mac_grid[key]=m;
	}
	}
	}
	
	if(dim==2)
	{
	for(int i=-Nx;i<=Nx;++i)
	{
		double r2=pow(i,2);
		
		if(r2>r02)
		{
			continue;
		}
		speed.Set(2,speedmax*(1-r2/r02));
		key.Set(1,i);
		key.Set(2,0);
		mac m(speed,0,m_boundary_fluid,0);
		m.SetConstSpeed(2,true);
		m_w.m_mac_grid[key]=m;
	}
	}
	m_init.PrepareConstSpeed();
	m_g.Set(1,0);
	m_g.Set(2,-9.81);
	if(dim==3)
	{
	m_g.Set(3,0);
	}
	m_calc_circ.Calculate();
	m_out.Calculate();			
	m_dt=0;
	m_t=0;
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
	cout<<"m_dt "<<m_dt<<endl;
	if(m_dt>0.1)
	{
		m_dt=0.1;
	}
	cout<<"convect"<<endl;
	m_time_ticks_deb=times(&m_time_deb);
	//m_conv.Calculate();
	m_conv_1_up.Calculate();
        //m_conv_center.Calculate();

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
		m_calc_circ.Calculate();
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
template <class Archive>
void JetDEau::serialize(Archive & ar,const unsigned int version)
{
	ar & boost::serialization::make_nvp("Time",m_t);
	ar & boost::serialization::make_nvp("TimeStep",m_dt);
	ar & boost::serialization::make_nvp("h",m_v_h);
	ar & boost::serialization::make_nvp("_1_h",m_v_1_h);
	ar & boost::serialization::make_nvp("g",m_g);
	ar & boost::serialization::make_nvp("Fluid",m_fluid);
	ar & boost::serialization::make_nvp("Air",m_air);
	ar & boost::serialization::make_nvp("Boundary_Air",m_boundary_air);
	ar & boost::serialization::make_nvp("Boundary_Fluid",m_boundary_fluid);
	ar & boost::serialization::make_nvp("CFL_Factor",m_cfl_factor);
	ar & boost::serialization::make_nvp("Rho_Fluid",m_rho_fluid);
	ar & boost::serialization::make_nvp("Rho_Air",m_rho_air);
	ar & boost::serialization::make_nvp("Rho_Inter",m_rho_inter);
	ar & boost::serialization::make_nvp("Rho_Inter_Boundary",m_rho_inter_bound);
	ar & boost::serialization::make_nvp("Rho_1_Fluid",m_1_rho_fluid);
	ar & boost::serialization::make_nvp("Rho_1_Air",m_1_rho_air);
	ar & boost::serialization::make_nvp("Rho_1_Inter",m_1_rho_inter);
	ar & boost::serialization::make_nvp("Rho_1_Inter_Boundary",m_1_rho_inter_bound);
	ar & boost::serialization::make_nvp("World",m_w);
	ar & boost::serialization::make_nvp("File_Number",m_i);
	if(typename Archive::is_loading())
	{
		long int temp;
		ar & boost::serialization::make_nvp("Seek_Pos_Animation",temp);
		m_spos=temp;
	}
	else if(typename Archive::is_saving())
	{
		long int temp=m_spos;
		ar & boost::serialization::make_nvp("Seek_Pos_Animation",temp);
	}
	if(typename Archive::is_loading())
	{
		m_out.Load();
	}
}
	int& JetDEau::GetFileNumber()
{
	return m_i;
}
	

void JetDEau::SetIfOutput(bool b)
{
	m_no_output=b;
}

