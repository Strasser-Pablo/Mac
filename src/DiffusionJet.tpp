DiffusionJet::DiffusionJet():m_fluid(1),m_air(0),m_cfl_factor(0.25),m_GetCellType(m_w,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound),
m_table(m_hash),m_w(m_table,m_part),
m_stag(m_v_h),m_get_v(m_w,m_stag,m_v_1_h),m_boundary_air(2),m_boundary_fluid(3),
m_conv(m_w,m_rungeKutta,m_get_v,m_stag,m_dt,m_GetCellType),
m_out(m_w,m_stag,m_v_h,m_t,1,m_i,m_spos,m_get_v,false),m_time_step(m_w,m_v_1_h,m_cfl_factor,m_dt,m_GetCellType),
m_rho_fluid(1000),m_rho_air(1),m_1_rho_fluid(0.001),m_1_rho_air(1),m_rho_inter(1000),m_1_rho_inter(0.001),m_rho_inter_bound(1000),m_1_rho_inter_bound(0.001),m_conv_1_up(m_w,m_get_v,m_stag,m_dt,m_GetCellType,m_v_h,m_v_1_h)
,m_calc_circ(m_w,m_v_h)
{
}

void DiffusionJet::SetUp()
{
	m_out.SetUp();
	m_t=0; 
	Physvector<2,double> speed;
	speed.SetAll(0);
	double speeddeb=10;
	int Nx=10;
	int Ny=10;
	int Nlay=4;
	m_v_1_h.SetAll(1*Nx);
	m_v_h.SetAll(1./Nx);

	Physvector<2,int> key;
	for(int i=0;i<Nx;++i)
	{
		for(int j=0;j<Ny;++j)
		{
			if(i==j)
			{
				speed.Set(1,speeddeb);
				speed.Set(2,speeddeb);
			}
			else if(i==j-1)
			{
				speed.Set(1,speeddeb);
				speed.Set(2,0.0);
			}
			else if(j==i-1)
			{
				speed.Set(1,0.0);
				speed.Set(2,speeddeb);
			}
			else
			{
				speed.Set(1,0);
				speed.Set(2,0);
			}
			key.Set(1,i);
			key.Set(2,j);
			mac m(speed,0,m_fluid,0);
			if(i==j)
			{
				m.SetConstSpeed(1,true);
				m.SetConstSpeed(2,true);
			}
			m_w.m_mac_grid[key]=m;
		}
	}
	speed.Set(1,speeddeb);
	speed.Set(2,0);
	key.Set(1,Nx+1);
	key.Set(2,Ny);
	mac m(speed,0,m_air,0);
	m_w.m_mac_grid[key]=m;

	speed.Set(1,0);
	speed.Set(2,speeddeb);
	key.Set(1,Nx);
	key.Set(2,Ny+1);
	mac m2(speed,0,m_air,0);
	m_w.m_mac_grid[key]=m2;
	for(int i=-Nlay;i<0;++i)
	{
		for(int j=-Nlay;j<Ny+Nlay;++j)
		{
			speed.Set(1,0);
			speed.Set(2,0);
			key.Set(1,i);
			key.Set(2,j);
			mac m(speed,0,m_air,0);
			m_w.m_mac_grid[key]=m;
		}
	}
	for(int i=Nx;i<Nx+Nlay;++i)
	{
		for(int j=-Nlay;j<Ny+Nlay;++j)
		{
			speed.Set(1,0);
			speed.Set(2,0);
			key.Set(1,i);
			key.Set(2,j);
			mac m(speed,0,m_air,0);
			m_w.m_mac_grid[key]=m;
		}
	}

	for(int i=0;i<Nx;++i)
	{
		for(int j=-Nlay;j<0;++j)
		{
			speed.Set(1,0);
			speed.Set(2,0);
			key.Set(1,i);
			key.Set(2,j);
			mac m(speed,0,m_air,0);
			m_w.m_mac_grid[key]=m;
		}
		for(int j=Ny;j<Ny+Nlay;++j)
		{
			speed.Set(1,0);
			speed.Set(2,0);
			key.Set(1,i);
			key.Set(2,j);
			mac m(speed,0,m_air,0);
			m_w.m_mac_grid[key]=m;
		}
	}
	m_calc_circ.Calculate();
	m_out.Calculate();			
	m_dt=0;
	m_t=0;
}

void DiffusionJet::Calculate()
{
	m_time_step.Calculate();
	if(m_dt>0.1)
	{
		m_dt=0.1;
	}
	cout<<"dt "<<m_dt<<endl;
	m_conv.Calculate();
	//m_conv_1_up.Calculate();

	m_calc_circ.Calculate();
	m_t+=m_dt; 
	m_out.Calculate();
}
	int& DiffusionJet::GetFileNumber()
{
	return m_i;
}

