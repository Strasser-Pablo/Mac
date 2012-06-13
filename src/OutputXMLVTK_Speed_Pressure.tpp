template <class TypeWorld,class TypeGetStagSpeedPos,class TypeGetSpeed>
OutputXMLVTK_Speed_Pressure<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed>::OutputXMLVTK_Speed_Pressure(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,type_cell fluid,TypeGetSpeed &GetSpeed):m_world(world),m_point(m_o),m_stag_pos(stag),m_h(h),m_fluid(fluid),m_GetSpeed(GetSpeed)
{
	
}

template <class TypeWorld,class TypeGetStagSpeedPos,class TypeGetSpeed>
void OutputXMLVTK_Speed_Pressure<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed>::Output(const char * filename,int ind)
{
	 vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct=vtkSmartPointer<vtkUnstructuredGrid>::New();
	m_i=0;
	m_point.clear();
	vtkSmartPointer<vtkPoints> vtkpoints=vtkSmartPointer<vtkPoints>::New();
	int nbCell=0;
	int nbPoint=0;
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		m_point[it.key()]=nbPoint;
		++nbPoint;
	}

	for(typename type_table_point::iterator it= m_point.begin();it!=m_point.end();++it)
	{
		Physvector<type_dim,type_data> temp=m_stag_pos.Get(it.key(),ind);
		type_data vtemp[3];
		for(int i=1;i<=type_dim;++i)
		{
			vtemp[i-1]=temp.Get(i);
		}
		for(int i=type_dim+1;i<=3;++i)
		{
			vtemp[i-1]=0;
		}
		vtkpoints->InsertPoint(it.data(),vtemp);
	}
	  vtkunstruct->SetPoints(vtkpoints);
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

	int nbcont=pow(2,type_dim);
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
		vtkIdType con[nbcont];
		int icon=0;
		while(true)
		{
			con[icon]=m_point[key];
			++icon;
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
		vtkunstruct->InsertNextCell(ntype,nbcont,con);
		++nbCell;
	}	

  vtkSmartPointer<vtkDoubleArray> vtkspeedarray=vtkSmartPointer<vtkDoubleArray>::New();
  vtkspeedarray->SetNumberOfComponents(3);
	for(typename type_table_point::iterator it= m_point.begin();it!=m_point.end();++it)
	{
		Physvector<type_dim,type_data> temp;
		m_world.m_mac_grid[it.key()].GetSpeed(temp);
		for(int j=1;j<=3;++j)
		{
			if(j==ind){
			vtkspeedarray->InsertComponent(it.data(),j-1,temp.Get(j));
			}
			else{
			vtkspeedarray->InsertComponent(it.data(),j-1,0);
			}
		}
	}
	vtkspeedarray->SetName("speed");
	vtkunstruct->GetPointData()->AddArray(vtkspeedarray);
	
	
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer=vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  //writer->SetDataModeToAscii();
  writer->SetInput(vtkunstruct);
  writer->SetFileName(filename);
  writer->Write();
}


template <class TypeWorld,class TypeGetStagSpeedPos,class TypeGetSpeed>
void OutputXMLVTK_Speed_Pressure<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed>::OutputPressure(const char * filename)
{
	vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct=vtkSmartPointer<vtkUnstructuredGrid>::New();
	m_i=0;
	m_point.clear();
	vtkSmartPointer<vtkPoints> vtkpoints=vtkSmartPointer<vtkPoints>::New();
	int nbCell=0;
	int nbPoint=0;
	int nbexist=0;
	m_i=0;
	KeyTableMap<typename TypeWorld::type_key,int,PhysvectorKeyOrder<type_dim,int> > m_point2(m_o);
	
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		Physvector<type_dim,int> temp=it.key();
		Physvector<type_dim,int> vkey;
		Physvector<type_dim,int> vdir;
		type_data vtemp[3];
		vkey.SetAll(0);
		vdir.SetAll(0);
		for(int i=1;i<=type_dim;++i)
		{
			vkey.GetRef(i)=2*temp.Get(i)-1;
		}
		m_point2[vkey]=1;
		while(true)
		{	
			if(!m_point.Exist(vkey))
			{
				m_point[vkey]=nbPoint;
				Physvector<type_dim,type_data> temp_vect;
			for(int i=1;i<=type_dim;++i)
			{
			vtemp[i-1]=0.5*vkey.Get(i)*m_h.Get(i);
			}
			for(int i=type_dim+1;i<=3;++i)
			{
			vtemp[i-1]=0;
			}
				vtkpoints->InsertPoint(nbPoint,vtemp);
				++nbPoint;
			}
			else
			{
				++nbexist;
			}
			int dir=1;
			while(dir<=type_dim)
			{
				if(vdir.Get(dir)==1)
				{
				vdir.Set(dir,0);
				vkey.GetRef(dir)-=2;
				++dir;
				}
				else
				{
				vkey.GetRef(dir)+=2;
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
		 vtkunstruct->SetPoints(vtkpoints);
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
	
	int nbcont=pow(2,type_dim);
	nbCell=0;
	int nbtotcon=0;
	
		for(typename KeyTableMap<Physvector<type_dim,int>,int,PhysvectorKeyOrder<type_dim,int> >::iterator it= m_point2.begin();it!=m_point2.end();++it)
	{
		Physvector<type_dim,int> key=it.key();
		vtkIdType con[nbcont];
		int icon=0;
		Physvector<type_dim,int> vdir;
		vdir.SetAll(0);
		while(true)
		{
			con[icon]=m_point[key];
			++icon;
			++nbtotcon;
			int dir=1;
			while(dir<=type_dim)
			{
			if(vdir.Get(dir)==1)
			{
				vdir.Set(dir,0);
				key.GetRef(dir)-=2;
				++dir;
			}
			else
			{
				key.GetRef(dir)+=2;
				vdir.Set(dir,1);
				break;
			}
			
		}
		if(dir>type_dim)
		{
			break;
		}
		}
		vtkunstruct->InsertNextCell(ntype,nbcont,con);
		++nbCell;
	}

  vtkSmartPointer<vtkDoubleArray> vtkspeedarray=vtkSmartPointer<vtkDoubleArray>::New();
  vtkspeedarray->SetNumberOfComponents(3);

	for(typename type_table_point::iterator it= m_point.begin();it!=m_point.end();++it)
	{
		Physvector<type_dim,type_data> pos;
		for(int i=1;i<=type_dim;++i)
		{
			pos.GetRef(i)=0.5*it.key().Get(i)*m_h.Get(i);
		}
		for(int i=1;i<=3;++i)
		{
			if(i<=type_dim)
			{
				vtkspeedarray->InsertComponent(it.data(),i-1,m_GetSpeed.Get(pos,i));
			}
			else
			{
				vtkspeedarray->InsertComponent(it.data(),i-1,0);
			}
		}
	}

	vtkspeedarray->SetName("speed");
	vtkunstruct->GetPointData()->AddArray(vtkspeedarray);

vtkSmartPointer<vtkFloatArray> vpress=vtkSmartPointer<vtkFloatArray>::New();
vtkSmartPointer<vtkIntArray> vtype=vtkSmartPointer<vtkIntArray>::New();
vtkSmartPointer<vtkFloatArray> vdiv=vtkSmartPointer<vtkFloatArray>::New();
vtkSmartPointer<vtkFloatArray> vViscosityForce=vtkSmartPointer<vtkFloatArray>::New();
vtkSmartPointer<vtkFloatArray> vcirculation=vtkSmartPointer<vtkFloatArray>::New();

int k=0;
		for(typename KeyTableMap<Physvector<type_dim,int>,int,PhysvectorKeyOrder<type_dim,int> >::iterator it= m_point2.begin();it!=m_point2.end();++it)
	{
		Physvector<type_dim,int> key;
		for(int i=1;i<=type_dim;++i)
		{
			key.GetRef(i)=(it.key().Get(i)+1)/2;
		}
		type_data temp;
		int type; 
		m_world.m_mac_grid[key].GetPressure(temp);
		m_world.m_mac_grid[key].GetCellType(type);
		double div;
		double viscos_force;
		m_world.m_mac_grid[key].GetViscosityForce(viscos_force);
		m_world.m_mac_grid[key].GetDivergence(div);
		type_data circ;
		m_world.m_mac_grid[key].GetCirculation(circ);
		vpress->InsertValue(k,temp);
		vtype->InsertValue(k,type);
		vdiv->InsertValue(k,div);
		vcirculation->InsertValue(k,circ);
		vViscosityForce->InsertValue(k,viscos_force);
		++k;
	}
	vpress->SetName("pressure");
	vtype->SetName("type");
	vdiv->SetName("Divergence");
	vcirculation->SetName("Circulation");
	vViscosityForce->SetName("Viscosity Force");
	vtkunstruct->GetCellData()->AddArray(vpress);
	vtkunstruct->GetCellData()->AddArray(vtype);
	vtkunstruct->GetCellData()->AddArray(vdiv);
	vtkunstruct->GetCellData()->AddArray(vcirculation);
	vtkunstruct->GetCellData()->AddArray(vViscosityForce);
  	vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer=vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  //writer->SetDataModeToAscii();
 	writer->SetInput(vtkunstruct);
  	writer->SetFileName(filename);
	writer->Write();
}
