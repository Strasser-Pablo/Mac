#ifndef Data_Chunk_Speed_H
#define Data_Chunk_Speed_H


template <typename DataSpeed,int NBSpeed,int NBAcceleration,int N>
class Data_Chunk_Speed
{
	public:
	typedef typename DataSpeed::type_const Const;
	private:
	const static int type_dim=DataSpeed::type_dim;
	const DataSpeed& m_cop;
	DataSpeed* m_data_speed[NBSpeed];
	DataSpeed* m_data_acceleration[NBAcceleration];
	Const* m_const;
	public:
	static int ispeed;
	static int iacceleration;
	typedef Data_Chunk_Speed<DataSpeed,NBSpeed,NBAcceleration,N> type_chunk_speed;
	Data_Chunk_Speed(const DataSpeed& cop):m_cop(cop),m_const(nullptr)
	{
		for(int i=0;i<NBSpeed;++i)
		{
			m_data_speed[i]=nullptr;
		}
		for(int i=0;i<NBAcceleration;++i)
		{
			m_data_acceleration[i]=nullptr;
		}
	}
	DataSpeed* Speed_GetPointer(int i=type_chunk_speed::ispeed)
	{
		return m_data_speed[i];
	}
	DataSpeed& Speed_GetRef(int i=type_chunk_speed::ispeed)
	{
		return *m_data_speed[i];
	}
	const DataSpeed& Speed_GetRef(int i=type_chunk_speed::ispeed) const
	{
		return *m_data_speed[i];
	}
	void Speed_SetPointer(DataSpeed* data,int i=type_chunk_speed::ispeed)
	{
		m_data_speed[i]=data;
	}

	DataSpeed* Acceleration_GetPointer(int i=type_chunk_speed::iacceleration)
	{
		return m_data_acceleration[i];
	}
	DataSpeed& Acceleration_GetRef(int i=type_chunk_speed::iacceleration)
	{
		return *m_data_acceleration[i];
	}
	const DataSpeed& Acceleration_GetRef(int i=type_chunk_speed::iacceleration) const
	{
		return *m_data_acceleration[i];
	}
	void Acceleration_SetPointer(DataSpeed* data,int i=type_chunk_speed::iacceleration)
	{
		m_data_acceleration[i]=data;
	}
	typedef DataSpeed type_speed;

	void Allocate()
	{
		UnAllocate();
		m_const=reinterpret_cast<Const*>(::operator new (N*sizeof(Const)));
		for(int i=0;i<N;++i)
		{
			new  (m_const+i) Const(m_cop.GetConstRef());
		}
		for(int i=0;i<NBSpeed;++i)
		{
			m_data_speed[i]=reinterpret_cast<DataSpeed*>(::operator new (N*sizeof(DataSpeed)));
			for(int j=0;j<N;++j)
			{
				new  (m_data_speed[i]+j) DataSpeed(m_cop,m_const[j]);
			}
		}
		for(int i=0;i<NBAcceleration;++i)
		{
			m_data_acceleration[i]=reinterpret_cast<DataSpeed*>(::operator new (N*sizeof(DataSpeed)));
			for(int j=0;j<N;++j)
			{
				new  (m_data_acceleration[i]+j) DataSpeed(m_cop,m_const[j]);
			}
		}
	}
	void UnAllocate()
	{
		for(int i=0;i<NBSpeed;++i)
		{
			if(m_data_speed[i]!=nullptr)
			{
				for(int j=0;j<N;++j)
				{
					m_data_speed[i][j].~DataSpeed();
				}
				::operator delete(m_data_speed[i]);
			}
		}
		for(int i=0;i<NBAcceleration;++i)
		{
			if(m_data_acceleration[i]!=nullptr)
			{
				for(int j=0;j<N;++j)
				{
					m_data_acceleration[i][j].~DataSpeed();
				}
				::operator delete(m_data_acceleration[i]);
			}
		}
		for(int i=0;i<N;++i)
		{
			m_const[i].~Const();
		}
		::operator delete(m_const);
	}
};

template <typename DataSpeed,int NBSpeed,int NBAcceleration,int N>
int Data_Chunk_Speed<DataSpeed,NBSpeed,NBAcceleration,N>::ispeed=0;

template <typename DataSpeed,int NBSpeed,int NBAcceleration,int N>
int Data_Chunk_Speed<DataSpeed,NBSpeed,NBAcceleration,N>::iacceleration=0;
#endif
