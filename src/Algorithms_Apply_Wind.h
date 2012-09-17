#ifndef Algorithms_Apply_Wind_H
#define Algorithms_Apply_Wind_H
template <typename Data,typename Policy>
class Algorithms_Apply_Wind : public Policy
{
	using Policy::GetWindDirection;
	using Policy::GetWindIntensity;
	using Policy::GetWindSens;
	typedef typename Data::type_data_struct::type_Data_Grid type_Data_Grid;
	typedef typename type_Data_Grid::type_key type_key;
	typedef typename type_Data_Grid::type_data::type_speed::type_data_value type_speed_value;
	static const int type_dim=type_key::type_dim;
	type_Data_Grid& m_grid;
	public:
	Algorithms_Apply_Wind(Data data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData())
	{
	}
	void Do()
	{
		const int idir=this->GetWindDirection();
		const int dir=this->GetWindSens();
		const type_speed_value speed=this->GetWindIntensity();
		type_key k;
		for(int i=1;i<=type_dim;++i)
		{
			if(i!=idir)
			{
				k.GetRef(i)=m_grid.GetBound(i,-1);
			}
			else
			{
				k.GetRef(i)=m_grid.GetBound(i,-dir);
			}
		}
		while(true)
		{
			while(true)
			{
				if(m_grid.Exist(k))
				{
					if(m_grid[k].CellType_GetRef().GetIsFluid())
					{
						if(dir==1)
						{
							m_grid[k].Acceleration_GetRef().Set(idir,m_grid[k].Acceleration_GetRef().Get(idir)+speed);
						}
						else
						{
							m_grid[k].GetNeighbour(idir,1).Acceleration_GetRef().Set(idir,m_grid[k].GetNeighbour(idir,1).Acceleration_GetRef().Get(idir)+speed);
						}
						break;
					}
				}
				if(dir==1)
				{
					if(k.GetRef(idir)>=m_grid.GetBound(idir,1))
					{
						break;
					}
				}
				else
				{
					if(k.GetRef(idir)<=m_grid.GetBound(idir,-1))
					{
						break;
					}
				}
				k.GetRef(idir)+=dir;
			}
			int i=1;
			bool b=false;
			while(true)
			{
				if(i>type_dim)
				{
					b=true;
					break;
				}
				if(i==idir)
				{
					++i;
					continue;	
				}
				if(k.GetRef(i)>=m_grid.GetBound(i,1))
				{
					k.GetRef(i)=m_grid.GetBound(i,-1);
					++i;
				}
				else
				{
					++k.GetRef(i);
					break;
				}
			}
			k.GetRef(idir)=m_grid.GetBound(i,-dir);
			if(b)
			{
				break;
			}
		}
		
	}
};
#endif
