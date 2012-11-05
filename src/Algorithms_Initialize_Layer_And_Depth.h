#ifndef Algorithms_Initialize_Layer_And_Depth_H
#define Algorithms_Initialize_Layer_And_Depth_H

template <typename DataType,typename Policy>
class Algorithms_Initialize_Layer_And_Depth : public Policy
{
	using Policy::GetDepthRemoveParticle;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::iterator iterator;
	type_grid& m_grid;
	public:
	Algorithms_Initialize_Layer_And_Depth(DataType data,const Policy& pol) :Policy(pol), m_grid(data.m_data.GetGridData()) 
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
			it.data().Layer_GetRef().SetLayerEmpty();
			if(it.data().CellType_GetRef().GetIsFluid()&&!it.data().CellType_GetRef().GetIsInterior())
			{
				it.data().Depth_GetRef().SetDepthEmpty();
			}
		}
		long t_end=times(&t2);
		cout<<"real Initialize Layer And Depth "<<(t_end-t_deb)/conv<<endl;
		cout<<"real Initialize Layer And Depth "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
	}
};
#endif
