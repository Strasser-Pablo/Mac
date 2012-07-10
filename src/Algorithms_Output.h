#ifndef Algorithms_Output_H
#define Algorithms_Output_H
template <typename Data,typename Policy>
class Algorithms_Output : Policy
{
	using Policy::OutputGridSpeed;
	using Policy::OutputGridPressure;
	using Policy::OutputTopology;
	typedef typename Data::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data_mac_cell type_data_grid;
	typedef typename type_data_grid::type_data_value type_data_value;
	typedef typename type_data_grid::type_data_vector type_data_vector;
	typedef typename type_grid::const_iterator iterator;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	static const int type_dim=type_grid::type_dim;
	int m_i=0;
	public:
	Algorithms_Output(Data & data,const Policy& pol,int i=0) : Policy(pol),m_i(i)
	{
	}
	void Do()
	{
		OutputGridSpeed(m_i);
		OutputGridPressure(m_i);
		OutputTopology(m_i);
		++m_i;
	}
};
#endif
