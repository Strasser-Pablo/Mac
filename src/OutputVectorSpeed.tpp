template <class TypeWorld,class TypeGetStagSpeedPos>
OutputVectorSpeed<TypeWorld,TypeGetStagSpeedPos>::OutputVectorSpeed(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,type_cell fluid):m_world(world),m_point(m_o),m_stag_pos(stag),m_h(h),m_fluid(fluid)
{
	
}

template <class TypeWorld,class TypeGetStagSpeedPos> template <class Stream>
void OutputVectorSpeed<TypeWorld,TypeGetStagSpeedPos>::Output(Stream & OS,int ind)
{
	m_i=0;
	m_point.clear();
	stringstream S;
	stringstream S2;
	int nbCell=0;
	int nbPoint=0;
	int nbvois=pow(2,type_dim);
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		Physvector<type_dim,type_data> temp=m_stag_pos.Get(it.key(),ind);
		m_point[it.key()]=nbPoint;
		for(int i=1;i<=type_dim;++i)
		{
			S2<<temp.Get(i)<<" ";
			
		}
		for(int i=type_dim+1;i<=3;++i)
		{
			S2<<0<<" ";
		}
		S2<<endl;
		++nbPoint;
	}
	S2<<"</DataArray>"<<endl;
	S2<<"</Points>"<<endl;
	S2<<"<Cells>"<<endl;
	S2<<"<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">"<<endl;
		for(typename type_table_point::iterator it= m_point.begin();it!=m_point.end();++it)
	{
		Physvector<type_dim,int> key=it.key();
		Physvector<type_dim,int> vdir;
		vdir.SetAll(0);
		bool bcont=true;
		while(bcont)
		{	
			int dir=1;
			while(dir<=type_dim)
			{
			if(vdir.Get(dir)==1)
			{
				vdir.Set(dir,0);
				key.GetRef(dir)-=1;
				++dir;
			}
			else
			{
				key.GetRef(dir)+=1;
				vdir.Set(dir,1);
				break;
			}
			
		}
		if(!m_point.Exist(key))
		{
			bcont=false;
			break;
		}
		if(dir>type_dim)
		{
			bcont=true;
			break;
		}
		}
		if(!bcont)
		{
			continue;
		}
		//Ok all neighburs exist.
		while(true)
		{
			S2<<m_point[key]<<" ";
			int dir=1;
			while(dir<=type_dim)
			{
			if(vdir.Get(dir)==1)
			{
				vdir.Set(dir,0);
				key.GetRef(dir)-=1;
				++dir;
			}
			else
			{
				key.GetRef(dir)+=1;
				vdir.Set(dir,1);
				break;
			}
			
		}
		if(dir>type_dim)
		{
			break;
		}
		}
		S2<<endl;
		++nbCell;
	}
	S<<"<?xml version=\"1.0\"?>"<<endl;
	S<<"<VTKFile type= \"UnstructuredGrid\"  version= \"0.1\"  byte_order= \"BigEndian\">"<<endl;
	S<<"<UnstructuredGrid>"<<endl;
	
	S<<"<Piece NumberOfPoints=\""<<nbPoint<<"\" NumberOfCells=\""<<nbCell<<"\">"<<endl;
	S<<"<Points>"<<endl;
	S<<"<DataArray type=\"Float64\" NumberOfComponents=\"3\" format=\"ascii\">"<<endl;
	S<<S2.str();
	
	S<<"</DataArray>"<<endl;
	S<<"<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">"<<endl;
	int offset=0;
	for(int i=0;i<nbCell;++i)
	{
		offset+=nbvois;
		S<<offset<<endl;
	}
	S<<"</DataArray>"<<endl;
	S<<"<DataArray type=\"Int32\" Name=\"types\" format=\"ascii\">"<<endl;
		int ntype;
	if(type_dim==1)
	{
		ntype=3;
	}
	else if(type_dim==2)
	{
		ntype=8;
	}
	else if(type_dim==3)
	{
		ntype=11;
	}
	else
	{
		throw VTKDimensionError();
	}
		for(int i=0;i<nbCell;++i)
	{
			S<<ntype<<endl;
	}
	S<<"</DataArray>"<<endl;
	S<<"</Cells>"<<endl;
	S<<"<PointData >"<<endl;
	S<<"<DataArray type=\"Float64\" NumberOfComponents=\"3\" Name=\"Speed\" format=\"ascii\">"<<endl;
	
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		Physvector<type_dim,type_data> temp;
		it.data().GetSpeed(temp);
		for(int i=1;i<=3;++i)
		{
			if(i==ind){
			S<<temp.Get(i)<<" ";
			}
			else{
			S<<0<<" ";
			}
		}
		S<<endl;
	}
	S<<"</DataArray>"<<endl;
	S<<"</PointData>"<<endl;
	S<<"</Piece>"<<endl;
	S<<"</UnstructuredGrid>"<<endl;
	S<<"</VTKFile>"<<endl;
	OS<<S.str();
}


template <class TypeWorld,class TypeGetStagSpeedPos> template <class Stream>
void OutputVectorSpeed<TypeWorld,TypeGetStagSpeedPos>::OutputPressure(Stream & OS)
{
	m_i=0;
	PhysvectorKeyOrder<type_dim,double> O;
	KeyTableMap<Physvector<type_dim,double> ,int,PhysvectorKeyOrder<type_dim,double> > point(O);
	stringstream S;
	stringstream S2;
	int nbCell=0;
	int nbPoint=0;
	int nbvois=pow(2,type_dim);
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		Physvector<type_dim,int> temp=it.key();
		Physvector<type_dim,double> vkey;
		Physvector<type_dim,int> vdir;
		vkey.SetAll(0);
		vdir.SetAll(0);
		for(int i=1;i<=type_dim;++i)
		{
			vkey.GetRef(i)=temp.Get(i)-0.5;
		}
		while(true)
		{	
			if(!point.Exist(vkey))
			{
				point[vkey]=nbPoint;
				++nbPoint;
			for(int i=1;i<=type_dim;++i)
			{
			S2<<vkey.Get(i)*m_h.Get(i)<<" ";
			}
			for(int i=type_dim+1;i<=3;++i)
			{
			S2<<0<<" ";
			}
			S2<<endl;
			}
			int dir=1;
			while(dir<=type_dim)
			{
				if(vdir.Get(dir)==1)
				{
				vdir.Set(dir,0);
				vkey.GetRef(dir)-=1;
				++dir;
				}
				else
				{
				vkey.GetRef(dir)+=1;
				vdir.Set(dir,1);
				break;
				}
			}
			if(dir>type_dim)
			{
			break;
			}
		}
	}
	S2<<"</DataArray>"<<endl;
	S2<<"</Points>"<<endl;
	S2<<"<Cells>"<<endl;
	S2<<"<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">"<<endl;
		for(typename KeyTableMap<Physvector<type_dim,double>,int,PhysvectorKeyOrder<type_dim,double> >::iterator it= point.begin();it!=point.end();++it)
	{
		Physvector<type_dim,double> key=it.key();
		Physvector<type_dim,double> vdir;
		vdir.SetAll(0);
		bool bcont=true;
		while(bcont)
		{	
			int dir=1;
			while(dir<=type_dim)
			{
			if(vdir.Get(dir)==1)
			{
				vdir.Set(dir,0);
				key.GetRef(dir)-=1;
				++dir;
			}
			else
			{
				key.GetRef(dir)+=1;
				vdir.Set(dir,1);
				break;
			}
			
		}
		if(!point.Exist(key))
		{
			bcont=false;
			break;
		}
		if(dir>type_dim)
		{
			bcont=true;
			break;
		}
		}
		if(!bcont)
		{
			continue;
		}
		//Ok all neighburs exist.
		while(true)
		{
			S2<<point[key]<<" ";
			int dir=1;
			while(dir<=type_dim)
			{
			if(vdir.Get(dir)==1)
			{
				vdir.Set(dir,0);
				key.GetRef(dir)-=1;
				++dir;
			}
			else
			{
				key.GetRef(dir)+=1;
				vdir.Set(dir,1);
				break;
			}
			
		}
		if(dir>type_dim)
		{
			break;
		}
		}
		S2<<endl;
		++nbCell;
	}
	S<<"<?xml version=\"1.0\"?>"<<endl;
	S<<"<VTKFile type= \"UnstructuredGrid\"  version= \"0.1\"  byte_order= \"BigEndian\">"<<endl;
	S<<"<UnstructuredGrid>"<<endl;
	
	S<<"<Piece NumberOfPoints=\""<<nbPoint<<"\" NumberOfCells=\""<<nbCell<<"\">"<<endl;
	S<<"<Points>"<<endl;
	S<<"<DataArray type=\"Float64\" NumberOfComponents=\"3\" format=\"ascii\">"<<endl;
	S<<S2.str();
	
	S<<"</DataArray>"<<endl;
	S<<"<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">"<<endl;
	int offset=0;
	for(int i=0;i<nbCell;++i)
	{
		offset+=nbvois;
		S<<offset<<endl;
	}
	S<<"</DataArray>"<<endl;
	S<<"<DataArray type=\"Int32\" Name=\"types\" format=\"ascii\">"<<endl;
		int ntype;
	if(type_dim==1)
	{
		ntype=3;
	}
	else if(type_dim==2)
	{
		ntype=8;
	}
	else if(type_dim==3)
	{
		ntype=11;
	}
	else
	{
		throw VTKDimensionError();
	}
		for(int i=0;i<nbCell;++i)
	{
			S<<ntype<<endl;
	}
	S<<"</DataArray>"<<endl;
	S<<"</Cells>"<<endl;
	S<<"<CellData >"<<endl;
	S<<"<DataArray type=\"Float64\" NumberOfComponents=\"1\" Name=\"Pressure\" format=\"ascii\">"<<endl;

		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_data temp;
		it.data().GetPressure(temp);
		S<<temp<<endl;
	}
	S<<"</DataArray>"<<endl;
/*	S<<"<DataArray type=\"Int32\" NumberOfComponents=\"1\" Name=\"Fluid\" format=\"ascii\">"<<endl;
		for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell temp;
		it.data().GetCellType(temp);
		S<<(temp==m_fluid)<<endl;
	}
	S<<"</DataArray>"<<endl;
	 */
	S<<"</CellData>"<<endl;
	S<<"</Piece>"<<endl;
	S<<"</UnstructuredGrid>"<<endl;
	S<<"</VTKFile>"<<endl;
	OS<<S.str();
}



template <class TypeWorld,class TypeGetStagSpeedPos> template <class Stream>
void OutputVectorSpeed<TypeWorld,TypeGetStagSpeedPos>::OutputParticle(Stream & OS)
{
		int nbCell=m_world.m_particle_list.size();
	OS<<"<?xml version=\"1.0\"?>"<<endl;
	OS<<"<VTKFile type= \"UnstructuredGrid\"  version= \"0.1\"  byte_order= \"BigEndian\">"<<endl;
	OS<<"<UnstructuredGrid>"<<endl;
	
	OS<<"<Piece NumberOfPoints=\""<<nbCell<<"\" NumberOfCells=\""<<nbCell<<"\">"<<endl;
	OS<<"<Points>"<<endl;
	OS<<"<DataArray type=\"Float64\" NumberOfComponents=\"3\" format=\"ascii\">"<<endl;
for(typename TypeWorld::type_tablecontainer::iterator it= m_world.m_particle_list.begin();it!=m_world.m_particle_list.end();++it)
	{
		Physvector<type_dim,type_data> pos;
		(*it).GetPos(pos);
		for(int i=1;i<=type_dim;++i)
		{
			OS<<pos.Get(i)<<" ";
		}
		for(int i=type_dim+1;i<=3;++i)
		{
			OS<<0<<" ";
		}
			OS<<endl;
	}
	OS<<"</DataArray>"<<endl;
	OS<<"</Points>"<<endl;
	OS<<"<Cells>"<<endl;
	OS<<"<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">"<<endl;
		for(int i=0;i<nbCell;++i)
	{
		OS<<i<<endl;
	}
	OS<<"</DataArray>"<<endl;
	OS<<"<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">"<<endl;
	for(int i=1;i<=nbCell;++i)
	{
		OS<<i<<endl;
	}
	OS<<"</DataArray>"<<endl;
	OS<<"<DataArray type=\"Int32\" Name=\"types\" format=\"ascii\">"<<endl;
		for(int i=0;i<nbCell;++i)
	{
			OS<<1<<endl;
	}
	OS<<"</DataArray>"<<endl;
	OS<<"</Cells>"<<endl;
	OS<<"<CellData >"<<endl;
	OS<<"</CellData>"<<endl;
	OS<<"</Piece>"<<endl;
	OS<<"</UnstructuredGrid>"<<endl;
	OS<<"</VTKFile>"<<endl;
}