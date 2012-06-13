template <class TypeWorld,class TypeGetStagSpeedPos,class TypeGetSpeed>
OutputXMLVTK_Particle<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed>::OutputXMLVTK_Particle(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,type_cell fluid,TypeGetSpeed &GetSpeed):OutputXMLVTK_Speed_Pressure<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed>(world,stag,h,fluid,GetSpeed)
{
	
}

template <class TypeWorld,class TypeGetStagSpeedPos,class TypeGetSpeed>
void OutputXMLVTK_Particle<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed>::OutputParticle(const char * filename)
{
	vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct=vtkSmartPointer<vtkUnstructuredGrid>::New();
	vtkSmartPointer<vtkPoints> vtkpoints=vtkSmartPointer<vtkPoints>::New();
	int nbCell=0;
	
	for(typename TypeWorld::type_tablecontainer::iterator it= this->m_world.m_particle_list.begin();it!=this->m_world.m_particle_list.end();++it)
	{
		Physvector<type_dim,type_data> pos;
		(*it).GetPos(pos);
		type_data temp[3];
		for(int i=1;i<=type_dim;++i)
		{
			temp[i-1]=pos.Get(i);
		}
		for(int i=type_dim+1;i<=3;++i)
		{
			temp[i-1]=0;
		}
		vtkpoints->InsertPoint(nbCell,temp);
		++nbCell;
	}
	 vtkunstruct->SetPoints(vtkpoints);
		for(int i=0;i<nbCell;++i)
	{
		vtkIdType temp[1];
		temp[0]=i;
		vtkunstruct->InsertNextCell(1,1,temp);
	}
	
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer=vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  //writer->SetDataModeToAscii();
  writer->SetInput(vtkunstruct);
  writer->SetFileName(filename);
  writer->Write();
}
