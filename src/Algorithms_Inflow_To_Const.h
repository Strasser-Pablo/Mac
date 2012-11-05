#ifndef Algorithms_Inflow_To_Const_H
#define Algorithms_Inflow_To_Const_H

template <typename DataType,typename Policy>
class Algorithms_Inflow_To_Const : public Policy
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::iterator iterator;
	static const int type_dim=type_grid::type_speed::type_dim;
	type_grid& m_grid;
	public:
	Algorithms_Inflow_To_Const(DataType data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().CellType_GetRef().GetIsInflow())
			{
				for(int i=1;i<=type_dim;++i)
				{
					it.data().Speed_GetRef().Speed_Set_Const(i);
				}
			}
		}
		long t_end=times(&t2);
		cout<<"real Inflow To Const "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Inflow To Const "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
};

#endif
