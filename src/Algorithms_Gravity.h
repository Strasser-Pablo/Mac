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
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			ApplyGravity(it.data());
		}
		long t_end=times(&t2);
		cout<<"real Gravity "<<(t_end-t_deb)/conv<<endl;
		cout<<"user Gravity "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
};

#endif
