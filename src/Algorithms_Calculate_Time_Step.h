#ifndef Algorithms_Calculate_Time_Step_H
#define Algorithms_Calculate_Time_Step_H

template <typename DataType,typename Policy>
class Algorithms_Calculate_Time_Step : public Policy
{
	using Policy::CheckDT;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data_mac_cell type_data_grid;
	typedef typename type_data_grid::type_data_value type_data_value;
	typedef typename type_data_grid::type_data_vector type_data_vector;
	typedef typename type_grid::const_iterator iterator;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	static const int type_dim=type_grid::type_dim;
	type_grid& m_grid;
	type_Time_Type& m_dt;
	type_Time_Type& m_factor;
	const type_data_vector& m_1_h;
	public:
	Algorithms_Calculate_Time_Step(DataType data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData()),m_dt(data.m_data.GetTimingData().m_dt),m_factor(data.m_data.GetTimingData().m_factor),m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv())
	{
	}
	void Do()
	{
		type_data_value max=0;
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().GetRef().GetIsFluid())
			{
				type_data_value temp=0;
				for(int i=1;i<=type_dim;++i)
				{
					temp+=pow(it.data().GetRef().Speed_Get(i)*m_1_h.Get(i),2);
				}
				if(temp>max)
				{
					max=temp;
				}
			}
		}
		m_dt=sqrt(max)*m_factor;
		m_dt=CheckDT(m_dt);
	}
};

#endif
