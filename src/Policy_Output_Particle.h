#ifndef Policy_Output_Particle_H
#define Policy_Output_Particle_H

#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkPoints2D.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkDataArray.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vtkXMLUnstructuredGridWriter.h>

template <typename Data>
class Policy_Output_Particle
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename Data::type_data_struct::type_Data_Topology type_Data_Topology;
	typedef typename type_Data_Topology::type_particle_list type_particle_list;
	typedef typename type_Data_Topology::type_particle type_particle;
	typedef typename type_particle::type_data_value type_data_value;
	typedef typename type_particle::type_data_vector type_data_vector;
	static const int type_dim=type_data_vector::type_dim;
	typedef typename type_particle_list::const_iterator iterator;
	public:
	const type_particle_list& m_part;
	const char * m_pref;
	Policy_Output_Particle(const Data & data,const char* pref): m_part(data.m_data.GetTopologyData().GetRefToParticleList()),m_pref(pref)
	{
	}
	void OutputTopology(int i,list<string>& m_list)
	{
		vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct=vtkSmartPointer<vtkUnstructuredGrid>::New();
		vtkSmartPointer<vtkPoints> vtkpoints=vtkSmartPointer<vtkPoints>::New();
		int nbCell=0;
		for(iterator it=m_part.begin();it!=m_part.end();++it)
		{
			type_data_vector vect=(*it).GetParticlePos();
			type_data_value temp[3];
			for(int i=1;i<=type_dim;++i)
			{
				temp[i-1]=vect.Get(i);
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
		writer->SetInput(vtkunstruct);
		stringstream stream;
		stream<<i;
		string str=string(m_pref)+stream.str()+string(".vtu");
		writer->SetFileName(str.c_str());
  		//writer->SetDataModeToAscii();
		writer->Write();
		m_list.push_back(str.c_str());
	}

};
#endif
