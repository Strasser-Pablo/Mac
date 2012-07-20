#ifndef Policy_Output_Grid_Pressure_H
#define Policy_Output_Grid_Pressure_H

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
#include <unordered_map>
#include "Data_CellType_Solid_SFINAE.h"
using namespace std;

template <typename Data>
class Policy_Output_Grid_Pressure
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data_mac_cell type_data_mac_cell;
	typedef typename type_data_mac_cell::type_pressure type_pressure;
	typedef typename type_Data_Grid::type_data_key type_data_key;
	typedef typename type_Data_Grid::type_hash type_hash;
	typedef typename type_Data_Grid::type_data_key_value type_data_key_value;
	typedef typename type_Data_Grid::type_data_vector type_data_vector;
	typedef typename type_Data_Grid::type_data_value type_data_value;
	typedef typename type_Data_Grid::type_data_neigh type_data_neigh;
	typedef typename type_data_mac_cell::type_speed type_speed;
	typedef typename type_Data_Grid::iterator iterator;
	static const int type_dim=type_Data_Grid::type_dim;
	typedef unordered_map<type_data_key,int,type_hash> type_map;
	type_Data_Grid& m_grid;
	const type_data_vector &m_h;
	const char * m_pref;
	template<typename T,typename Data_CellType_Solid_SFINAE<typename T::type_data_mac_cell,type_data_mac_cell>::type=0>
	void AddSolid(T& grid __attribute__ ((unused)),type_map &m_map,vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct)
	{
  		vtkSmartPointer<vtkIntArray> vtkSolid_Cell=vtkSmartPointer<vtkIntArray>::New();
		for(typename type_map::iterator it=m_map.begin();it!=m_map.end();++it)
		{
			vtkSolid_Cell->InsertValue(it->second,m_grid[it->first].GetRef().GetIsSolid());
		}
		vtkSolid_Cell->SetName("Solid");
		vtkunstruct->GetCellData()->AddArray(vtkSolid_Cell);
	}
	template<typename T,typename Data_CellType_Solid_SFINAE<typename T::type_data_mac_cell,type_data_mac_cell>::type2=0>
	void AddSolid(T& grid __attribute__ ((unused)),type_map &m_map __attribute__ ((unused)),vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct __attribute__ ((unused)))
	{
	}
	public:
	Policy_Output_Grid_Pressure(Data & data,const char* pref): m_grid(data.m_data.GetGridData()),m_h(data.m_data.GetGridData().m_h.GetRef()),m_pref(pref)
	{
	}
	void OutputGridPressure(int i,list<string>& m_list)
	{
		type_map m_map(10,m_grid.GetHash());
	 	vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct=vtkSmartPointer<vtkUnstructuredGrid>::New();
		vtkSmartPointer<vtkPoints> vtkpoints=vtkSmartPointer<vtkPoints>::New();
		int num=0;
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().GetRef().GetIsLayerEmpty())
			{
				continue;
			}
			m_map[it.key()]=num;
			type_data_value vtemp[3];
			for(int ipos=1;ipos<=type_dim;++ipos)
			{
				vtemp[ipos-1]=(it.key().Get(ipos)-0.5)*m_h.Get(ipos);
			}
			for(int ipos=type_dim+1;ipos<=3;++ipos)
			{
				vtemp[ipos-1]=0;
			}
			vtkpoints->InsertPoint(num,vtemp);
			++num;
			type_data_key k=it.key();
			for(int i=1;i<=type_dim;++i)
			{
				type_data_neigh * neigh=it.data().GetNeighbour(i,1);
				k.GetRef(i)+=1;
				if(neigh==nullptr&&m_map.count(k)==0)
				{
					for(int ipos=1;ipos<=type_dim;++ipos)
					{
						vtemp[ipos-1]=(k.Get(ipos)-0.5)*m_h.Get(ipos);
					}
					for(int ipos=type_dim+1;ipos<=3;++ipos)
					{
						vtemp[ipos-1]=0;
					}
					m_map[k]=num;
					vtkpoints->InsertPoint(num,vtemp);
					++num;
				}
				k.GetRef(i)-=1;
			}
		}
		typedef unordered_map<type_data_key,int,type_hash> type_map;
		type_map m_map2(10,m_grid.GetHash());
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
		vtkIdType con[nbcont];
		int icell=0;
		for(typename type_map::iterator it=m_map.begin();it!=m_map.end();++it)
		{
			con[0]=it->second;
			type_data_key k=it->first;
			k.GetRef(1)+=1;
			if(m_map.count(k)==0)
			{
				continue;
			}
			con[1]=m_map[k];
			k.GetRef(1)-=1;
			if(type_dim>=2)
			{
				k.GetRef(2)+=1;
				if(m_map.count(k)==0)
				{
					continue;
				}
				con[2]=m_map[k];
				k.GetRef(1)+=1;
				if(m_map.count(k)==0)
				{
					continue;
				}
				con[3]=m_map[k];
				k.GetRef(1)-=1;
				k.GetRef(2)-=1;
				if(type_dim>=3)
				{
					k.GetRef(3)+=1;
					if(m_map.count(k)==0)
					{
						continue;
					}
					con[4]=m_map[k];
					k.GetRef(1)+=1;
					if(m_map.count(k)==0)
					{
						continue;
					}
					con[5]=m_map[k];
					k.GetRef(1)-=1;
					k.GetRef(2)+=1;
					if(m_map.count(k)==0)
					{
						continue;
					}
					con[6]=m_map[k];
					k.GetRef(1)+=1;
					if(m_map.count(k)==0)
					{
						continue;
					}
					con[7]=m_map[k];
				}
			}
			m_map2[it->first]=icell;
			++icell;
			vtkunstruct->InsertNextCell(ntype,nbcont,con);
		}
  		vtkSmartPointer<vtkDoubleArray> vtkPressurearray=vtkSmartPointer<vtkDoubleArray>::New();
  		vtkSmartPointer<vtkIntArray> vtkType_Cell=vtkSmartPointer<vtkIntArray>::New();
		for(typename type_map::iterator it=m_map2.begin();it!=m_map2.end();++it)
		{
			vtkPressurearray->InsertValue(it->second,m_grid[it->first].GetRef().Pressure_Get().Get());
			vtkType_Cell->InsertValue(it->second,m_grid[it->first].GetRef().GetIsFluid());
		}
		vtkPressurearray->SetName("Pressure");
		vtkType_Cell->SetName("Fluid");
		AddSolid(m_grid,m_map2,vtkunstruct);
		vtkunstruct->GetCellData()->AddArray(vtkPressurearray);
		vtkunstruct->GetCellData()->AddArray(vtkType_Cell);

  		vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer=vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  		writer->SetInput(vtkunstruct);
		stringstream stream;
		stream<<i;
		string str=string(m_pref)+stream.str()+string(".vtu");
		writer->SetFileName(str.c_str());
  		writer->SetDataModeToAscii();
  		writer->Write();
		m_list.push_back(str);
	}
};
#endif
