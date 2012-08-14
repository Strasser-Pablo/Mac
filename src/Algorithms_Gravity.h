#ifndef Algorithms_Gravity_H
#define Algorithms_Gravity_H

template <typename Data,typename Policy>
class Algorithms_Gravity : public Policy
{
	using Policy::ApplyGravity;
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::iterator iterator;
	type_Data_Grid& m_grid;
	public:
	Algorithms_Gravity(Data data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			ApplyGravity(it.data());
		}
	}
};

#endif
