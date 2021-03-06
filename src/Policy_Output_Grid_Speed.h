#ifndef Policy_Output_Grid_Speed_H
#define Policy_Output_Grid_Speed_H

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
class Policy_Output_Grid_Speed
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_offset type_neigh;
	typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
	typedef typename type_Data_Grid::type_spacing_vector::type_data type_spacing_value;
	typedef typename type_Data_Grid::iterator iterator;
	static const int type_dim=type_Data_Grid::type_data::type_speed::type_dim;
	type_Data_Grid& m_grid;
	const type_spacing_vector &m_h;
	const char * m_pref;
	public:
	Policy_Output_Grid_Speed(Data & data,const char* pref): m_grid(data.m_data.GetGridData()),m_h(data.m_data.GetGridData().m_h.GetRef()),m_pref(pref)
	{
	}
	void OutputGridSpeed(int i,list<string>& m_list)
	{
		for(int ispeed=1;ispeed<=type_dim;++ispeed)
		{
	 		vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct=vtkSmartPointer<vtkUnstructuredGrid>::New();
			vtkSmartPointer<vtkPoints> vtkpoints=vtkSmartPointer<vtkPoints>::New();
            vtkpoints->SetDataTypeToDouble();
			int num=0;
			for(iterator it=m_grid.begin();it!=m_grid.end();++it)
			{
				if(it.data().Layer_GetRef().GetIsLayerEmpty())
				{
					continue;
				}
				it.data().Layer_GetRef().SetLayer(num);
				type_spacing_value vtemp[3];
				for(int ipos=1;ipos<=type_dim;++ipos)
				{
					if(ipos!=ispeed)
					{
						vtemp[ipos-1]=it.key().Get(ipos)*m_h.Get(ipos);
					}
					else
					{
						vtemp[ipos-1]=(it.key().Get(ipos)-0.5)*m_h.Get(ipos);
					}
				}
				for(int ipos=type_dim+1;ipos<=3;++ipos)
				{
					vtemp[ipos-1]=0;
				}
				vtkpoints->InsertPoint(num,vtemp);
				++num;
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
			int nbcont=pow(2,type_dim);
			for(iterator it=m_grid.begin();it!=m_grid.end();++it)
			{
				if(it.data().Layer_GetRef().GetIsLayerEmpty())
				{
					continue;
				}
				vtkIdType con[nbcont];
				con[0]=it.data().Layer_GetRef().GetLayer();
				type_neigh neigh=it.data().GetNeighbour(1,1);
				if(!neigh.IsValid()||neigh.Layer_GetRef().GetIsLayerEmpty())
				{
					continue;
				}
				con[1]=neigh.Layer_GetRef().GetLayer();
				if(type_dim>=2)
				{
					neigh=it.data().GetNeighbour(2,1);
					if(!neigh.IsValid()||neigh.Layer_GetRef().GetIsLayerEmpty())
					{
						continue;
					}
					con[2]=neigh.Layer_GetRef().GetLayer();
					neigh=neigh.GetNeighbour(1,1);
					if(!neigh.IsValid()||neigh.Layer_GetRef().GetIsLayerEmpty())
					{
						continue;
					}
					con[3]=neigh.Layer_GetRef().GetLayer();
					if(type_dim>=3)
					{
						neigh=it.data().GetNeighbour(3,1);
						if(!neigh.IsValid()||neigh.Layer_GetRef().GetIsLayerEmpty())
						{
							continue;
						}
						con[4]=neigh.Layer_GetRef().GetLayer();
						type_neigh neigh2=neigh.GetNeighbour(1,1);
						if(!neigh2.IsValid()||neigh2.Layer_GetRef().GetIsLayerEmpty())
						{
							continue;
						}
						con[5]=neigh2.Layer_GetRef().GetLayer();
						neigh=neigh.GetNeighbour(2,1);
						if(!neigh.IsValid()||neigh.Layer_GetRef().GetIsLayerEmpty())
						{
							continue;
						}
						con[6]=neigh.Layer_GetRef().GetLayer();
						neigh=neigh.GetNeighbour(1,1);
						if(!neigh.IsValid()||neigh.Layer_GetRef().GetIsLayerEmpty())
						{
							continue;
						}
						con[7]=neigh.Layer_GetRef().GetLayer();
					}
				}
				vtkunstruct->InsertNextCell(ntype,nbcont,con);
			}
			vtkSmartPointer<vtkDoubleArray> vtkspeedarray=vtkSmartPointer<vtkDoubleArray>::New();
			for(iterator it=m_grid.begin();it!=m_grid.end();++it)
			{
				if(it.data().Layer_GetRef().GetIsLayerEmpty())
				{
					continue;
				}
				vtkspeedarray->InsertComponent(it.data().Layer_GetRef().GetLayer(),0,it.data().Speed_GetRef().Get(ispeed));
			}
			if(ispeed==1)
			{
				vtkspeedarray->SetName("speedx");
			}
			else if (ispeed==2)
			{
				vtkspeedarray->SetName("speedy");
			}
			else if (ispeed==3)
			{
				vtkspeedarray->SetName("speedz");
			}
			vtkunstruct->GetPointData()->AddArray(vtkspeedarray);
			vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer=vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
			writer->SetInput(vtkunstruct);
			stringstream stream;
			stream<<i;
			stringstream stream2;
			stream2<<ispeed;
			string str=string(m_pref)+string("_")+stream2.str()+string("_")+stream.str()+string(".vtu");
			writer->SetFileName(str.c_str());
			m_list.push_back(str.c_str());
  			//writer->SetDataModeToAscii();
			writer->Write();
		}
	}
        void InputGridSpeed(int i)
        {
        }
};
#endif
