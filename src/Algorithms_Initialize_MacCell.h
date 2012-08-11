#ifndef Algorithms_Initialize_MacCell_H
#define Algorithms_Initialize_MacCell_H

template <typename DataType,typename Policy>
class Algorithms_Initialize_MacCell : public Policy
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::iterator iterator;
	type_grid& m_grid;
	public:
	Algorithms_Initialize_MacCell(DataType data,const Policy& pol) :Policy(pol), m_grid(data.m_data.GetGridData()) 
	{
	}
	void Do()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Layer_GetRef().SetLayerEmpty();
		}
	}
};
#endif
