#ifndef Policy_Output_Grid_Pressure_ID_H
#define Policy_Output_Grid_Pressure_ID_H

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
#include <vtkXMLUnstructuredGridReader.h>
#include <unordered_map>
#include "Data_CellType_Solid_SFINAE.h"
#include "Data_CellType_Interior_SFINAE.h"
using namespace std;

template <typename Data>
class Policy_Output_Grid_Pressure_ID
{
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_data::type_pressure type_pressure;
    typedef typename type_pressure::type_pressure type_pres;
	typedef typename type_Data_Grid::type_key type_key;
	typedef typename type_Data_Grid::type_hash type_hash;
	typedef typename type_Data_Grid::type_key::type_data type_key_value;
	typedef typename type_Data_Grid::type_spacing_vector type_spacing_vector;
	typedef typename type_Data_Grid::type_spacing_vector::type_data type_spacing_value;
	typedef typename type_Data_Grid::type_offset type_neigh;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	typedef typename type_Data_Grid::type_data::type_cell_type type_cell_type;
	typedef typename type_Data_Grid::iterator iterator;
	static const int type_dim=type_Data_Grid::type_spacing_vector::type_dim;
	typedef unordered_map<type_key,int,type_hash> type_map;
	type_Data_Grid& m_grid;
	const type_spacing_vector &m_h;
	const char * m_pref;
	template<typename T,typename Data_CellType_Solid_SFINAE<typename T::type_data::type_cell_type,type_cell_type>::type=0>
	void AddSolid(T& grid __attribute__ ((unused)),type_map &m_map,vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct)
	{
  		vtkSmartPointer<vtkIntArray> vtkSolid_Cell=vtkSmartPointer<vtkIntArray>::New();
		for(typename type_map::iterator it=m_map.begin();it!=m_map.end();++it)
		{
			vtkSolid_Cell->InsertValue(it->second,m_grid[it->first].CellType_GetRef().GetIsSolid());
		}
		vtkSolid_Cell->SetName("Solid");
		vtkunstruct->GetCellData()->AddArray(vtkSolid_Cell);
	}
	template<typename T,typename Data_CellType_Solid_SFINAE<typename T::type_data::type_cell_type,type_cell_type>::type2=0>
	void AddSolid(T& grid __attribute__ ((unused)),type_map &m_map __attribute__ ((unused)),vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct __attribute__ ((unused)))
	{
	}
	template<typename T,typename Data_CellType_Interior_SFINAE<typename T::type_data::type_cell_type,type_cell_type>::type=0>
	void AddInterior(T& grid __attribute__ ((unused)),type_map &m_map,vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct)
	{
  		vtkSmartPointer<vtkIntArray> vtkInterior_Cell=vtkSmartPointer<vtkIntArray>::New();
		for(typename type_map::iterator it=m_map.begin();it!=m_map.end();++it)
		{
			vtkInterior_Cell->InsertValue(it->second,m_grid[it->first].CellType_GetRef().GetIsInterior());
		}
		vtkInterior_Cell->SetName("Interior");
		vtkunstruct->GetCellData()->AddArray(vtkInterior_Cell);
	}
	template<typename T,typename Data_CellType_Interior_SFINAE<typename T::type_data::type_cell_type,type_cell_type>::type2=0>
	void AddInterior(T& grid __attribute__ ((unused)),type_map &m_map __attribute__ ((unused)),vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct __attribute__ ((unused)))
	{
	}

    void AddKey(type_Data_Grid& grid __attribute__ ((unused)),type_map &m_map,vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct)
    {
        vtkSmartPointer<vtkIntArray> vtkKey=vtkSmartPointer<vtkIntArray>::New();
        vtkKey->SetNumberOfComponents(3);
        for(typename type_map::iterator it=m_map.begin();it!=m_map.end();++it)
        {
            for(int i=1;i<=type_dim;++i)
            {
                vtkKey->InsertComponent(it->second,i-1,it->first.Get(i));
            }
            for(int i=type_dim+1;i<=3;++i)
            {
                 vtkKey->InsertComponent(it->second,i-1,0);
            }
        }
        vtkKey->SetName("Key");
        vtkunstruct->GetCellData()->AddArray(vtkKey);
    }

    void AddSpeed(type_Data_Grid& grid __attribute__ ((unused)),type_map &m_map,vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct)
    {
        vtkSmartPointer<vtkDoubleArray> vtkSpeed=vtkSmartPointer<vtkDoubleArray>::New();
        vtkSmartPointer<vtkIntArray> vtkSpeedConst=vtkSmartPointer<vtkIntArray>::New();
        vtkSpeed->SetNumberOfComponents(3);
        vtkSpeedConst->SetNumberOfComponents(3);
        for(typename type_map::iterator it=m_map.begin();it!=m_map.end();++it)
        {
            for(int i=1;i<=type_dim;++i)
            {
                vtkSpeed->InsertComponent(it->second,i-1,m_grid[it->first].Speed_GetRef().Get(i));
                vtkSpeedConst->InsertComponent(it->second,i-1,m_grid[it->first].Speed_GetRef().Get_Const(i));
            }
            for(int i=type_dim+1;i<=3;++i)
            {
                 vtkSpeed->InsertComponent(it->second,i-1,0);
                 vtkSpeedConst->InsertComponent(it->second,i-1,false);
            }
        }
        vtkSpeed->SetName("Speed");
        vtkunstruct->GetCellData()->AddArray(vtkSpeed);
        vtkSpeedConst->SetName("SpeedConst");
        vtkunstruct->GetCellData()->AddArray(vtkSpeedConst);
    }

    void LoadSpeed(type_Data_Grid& grid __attribute__ ((unused)),type_map &m_map,vtkSmartPointer<vtkCellData> vtkcell)
    {
        vtkSmartPointer<vtkDataArray> vtkdataspeed;
        vtkdataspeed= vtkcell->GetArray("Speed");
        vtkSmartPointer<vtkDataArray> vtkdataspeedConst;
        vtkdataspeedConst= vtkcell->GetArray("SpeedConst");
        for(typename type_map::iterator it=m_map.begin();it!=m_map.end();++it)
        {
            for(int i=1;i<=type_dim;++i)
            {
                m_grid[it->first].Speed_GetRef().Set(i,vtkdataspeed->GetComponent(it->second,i-1),true);
                if(vtkdataspeedConst->GetComponent(it->second,i-1))
                {
                    m_grid[it->first].Speed_GetRef().Set_Const(i);
                }
            }
        }
    }
    void LoadPressure(type_Data_Grid& grid __attribute__ ((unused)),type_map &m_map,vtkSmartPointer<vtkCellData> vtkcell)
    {
        vtkSmartPointer<vtkDataArray> vtkdatapressure;
        vtkSmartPointer<vtkDataArray> vtkdatacelltype;
        vtkdatapressure= vtkcell->GetArray("Pressure");
        vtkdatacelltype= vtkcell->GetArray("Type");
        for(typename type_map::iterator it=m_map.begin();it!=m_map.end();++it)
        {
                m_grid[it->first].Pressure_GetRef().Pressure_Set(type_pres(vtkdatapressure->GetComponent(it->second,0)));
                m_grid[it->first].CellType_GetRef().m_mat=static_cast<typename type_cell_type::Material_Type>(vtkdatacelltype->GetComponent(it->second,0));
        }
    }
	public:
	Policy_Output_Grid_Pressure_ID(Data & data,const char* pref): m_grid(data.m_data.GetGridData()),m_h(data.m_data.GetGridData().m_h.GetRef()),m_pref(pref)
	{
	}
	void OutputGridPressure(int i,list<string>& m_list)
	{
		type_map m_map(10,m_grid.GetHash());
	 	vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct=vtkSmartPointer<vtkUnstructuredGrid>::New();
		vtkSmartPointer<vtkPoints> vtkpoints=vtkSmartPointer<vtkPoints>::New();
        vtkpoints->SetDataTypeToDouble();
		int num=0;
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			m_map[it.key()]=num;
			type_spacing_value vtemp[3];
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
			type_key k=it.key();
			for(int i=1;i<=type_dim;++i)
			{
				type_neigh neigh=it.data().GetNeighbour(i,1);
				k.GetRef(i)+=1;
				if(!neigh.IsValid()&&m_map.count(k)==0)
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
		typedef unordered_map<type_key,int,type_hash> type_map;
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
			if(!m_grid.Exist(it->first))
			{
				continue;
			}
			con[0]=it->second;
			type_key k=it->first;
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
        vtkSmartPointer<vtkIntArray> vtkEnumType_Cell=vtkSmartPointer<vtkIntArray>::New();
		for(typename type_map::iterator it=m_map2.begin();it!=m_map2.end();++it)
		{
			vtkPressurearray->InsertValue(it->second,m_grid[it->first].Pressure_GetRef().Pressure_Get().Get());
			vtkType_Cell->InsertValue(it->second,m_grid[it->first].CellType_GetRef().GetIsFluid());
            vtkEnumType_Cell->InsertValue(it->second,static_cast<int>(m_grid[it->first].CellType_GetRef().m_mat));
		}
		vtkPressurearray->SetName("Pressure");
		vtkType_Cell->SetName("Fluid");
        vtkEnumType_Cell->SetName("Type");
		AddSolid(m_grid,m_map2,vtkunstruct);
		AddInterior(m_grid,m_map2,vtkunstruct);
        AddKey(m_grid,m_map2,vtkunstruct);
        AddSpeed(m_grid,m_map2,vtkunstruct);
		vtkunstruct->GetCellData()->AddArray(vtkPressurearray);
		vtkunstruct->GetCellData()->AddArray(vtkType_Cell);
        vtkunstruct->GetCellData()->AddArray(vtkEnumType_Cell);
		
  		vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer=vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  		writer->SetInput(vtkunstruct);
		stringstream stream;
		stream<<i;
		string str=string(m_pref)+stream.str()+string(".vtu");
		writer->SetFileName(str.c_str());
  		//writer->SetDataModeToAscii();
  		writer->Write();
		m_list.push_back(str);
	}
        void InputGridPressure(int i)
        {
            stringstream stream;
            stream<<i;
            string str=string(m_pref)+stream.str()+string(".vtu");
            vtkSmartPointer<vtkXMLUnstructuredGridReader> reader=vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
            reader->SetFileName(str.c_str());
            reader->Update();
            vtkSmartPointer<vtkUnstructuredGrid> vtkunstruct;
            vtkunstruct=reader->GetOutput();
            vtkSmartPointer<vtkCellData> vtkcell;
            vtkcell=vtkunstruct->GetCellData();
            vtkSmartPointer<vtkDataArray> vtkdatakey;
            vtkdatakey= vtkcell->GetArray("Key");
            int n=vtkdatakey->GetNumberOfTuples();
            type_map m_map(10,m_grid.GetHash());
            for(int i=0;i<n;++i)
            {
                type_key v;
                for(int j=1;j<=type_dim;++j)
                {
                    int temp=vtkdatakey->GetComponent(i,j-1);
                    v.Set(j,temp);
                }
                m_map[v]=i;
            }
            LoadSpeed(m_grid,m_map,vtkcell);
            LoadPressure(m_grid,m_map,vtkcell);
        }
};
#endif
