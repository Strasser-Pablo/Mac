template <class TypeWorld,class TypeGetStagSpeedPos,class TypeGetSpeed>
OutputXMLVTK_With_Line<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed>::OutputXMLVTK_With_Line(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,type_cell fluid,TypeGetSpeed &GetSpeed):OutputXMLVTK_Speed_Pressure<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed>(world,stag,h,fluid,GetSpeed)
{
	
}

template <class TypeWorld,class TypeGetStagSpeedPos,class TypeGetSpeed>
void OutputXMLVTK_With_Line<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed>::OutputParticle(const char * filename)
{
	vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct=vtkSmartPointer<vtkUnstructuredGrid>::New();
	vtkSmartPointer<vtkPoints> vtkpoints=vtkSmartPointer<vtkPoints>::New();
	int nbCell=0;
	for(typename TypeWorld::type_list_surface::iterator it=this->m_world.m_list_surface.begin();it!=this->m_world.m_list_surface.end();++it)
	{
		int size=it->second.m_list.size();
		vtkIdType pointlist[size];
		int i=0;
		for(typename TypeWorld::type_list_surface_elem::iterator it2=it->second.m_list.begin();it2!=it->second.m_list.end();++it2)
		{
			Physvector<type_dim,type_data> pos;
			(*it2)->GetPos(pos);
			type_data temp[type_dim];
			for(int i=1;i<=type_dim;++i)
			{
				temp[i-1]=pos.Get(i);
			}
			for(int i=type_dim+1;i<=3;++i)
			{
				temp[i-1]=0;
			}
			vtkpoints->InsertPoint(nbCell,temp);
			pointlist[i]=nbCell;
			++nbCell;
			++i;
		}
	 	vtkunstruct->SetPoints(vtkpoints);
		vtkunstruct->InsertNextCell(4,size,pointlist);
	}
	
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer=vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  //writer->SetDataModeToAscii();
  writer->SetInput(vtkunstruct);
  writer->SetFileName(filename);
  writer->Write();
}
