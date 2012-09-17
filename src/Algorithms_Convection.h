#ifndef Algorithms_Convection_H
#define Algorithms_Convection_H

template <typename Data,typename Policy>
class Algorithms_Convection : public Policy
{
	using Policy::Get_Convection_Speed;
	using Policy::Get_If_Apply_Convection;
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::iterator iterator;
	typedef typename type_Data_Grid::type_data::type_speed type_speed;
	static const int type_dim=type_speed::type_dim;
	type_Data_Grid& m_grid;
	public:
	Algorithms_Convection(Data data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			for(int i=1;i<=type_dim;++i)
			{
				if(Get_If_Apply_Convection(it.data(),i))
				{
					it.data().Acceleration_GetRef().Set(i,it.data().Acceleration_GetRef().Get(i)+Get_Convection_Speed(it.data(),i));
				}
			}
		}
	}
};

#endif
