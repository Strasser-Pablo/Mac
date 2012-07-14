#ifndef Algorithms_Fluid_To_Layer_H
#define Algorithms_Fluid_To_Layer_H

using namespace std;

template <typename DataType,typename Policy>
class Algorithms_Fluid_To_Layer : public Policy
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data_neigh type_data_neigh;
	typedef typename type_grid::type_data_key type_data_key;
	typedef typename type_grid::type_data_mac_cell type_data_grid;
	typedef typename type_data::type_Data_Topology type_topology;
	typedef typename type_topology::type_particle_list type_particle_list;
	typedef typename type_grid::iterator iterator;
	static const int type_dim=type_data_key::type_dim;
	type_grid& m_grid;
	public:
	Algorithms_Fluid_To_Layer(DataType data,const Policy& pol) :Policy(pol), m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().GetRef().GetIsFluid())
			{
				it.data().GetRef().SetLayer(0);
			}
			else
			{
				it.data().GetRef().SetLayerEmpty();
			}
		}
	}
};

#endif
