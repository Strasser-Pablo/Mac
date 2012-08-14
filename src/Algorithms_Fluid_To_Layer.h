#ifndef Algorithms_Fluid_To_Layer_H
#define Algorithms_Fluid_To_Layer_H

using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Fluid_To_Layer : public Policy
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::iterator iterator;
	type_grid& m_grid;
	public:
	Algorithms_Fluid_To_Layer(DataType data,const Policy& pol) :Policy(pol), m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().CellType_GetRef().GetIsFluid())
			{
				it.data().Layer_GetRef().SetLayer(0);
			}
			else
			{
				it.data().Layer_GetRef().SetLayerEmpty();
			}
		}
	}
};

#endif
