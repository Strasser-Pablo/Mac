#ifndef Data_Chunk_Speed_H
#define Data_Chunk_Speed_H


template <typename DataSpeed,int NBSpeed,int N>
class Data_Chunk_Speed
{
	public:
	typedef typename DataSpeed::type_speed DataSpeedContainer;
	typedef typename DataSpeed::type_const Const;
	private:
	const static int type_dim=DataSpeed::type_dim;
	static int ispeed;
	const DataSpeedContainer& m_cop;
	DataSpeed* m_data[NBSpeed];
	DataSpeedContainer* m_temp_speed;
	Const* m_const;
	public:
	typedef Data_Chunk_Speed<DataSpeed,NBSpeed,N> type_chunk_speed;
	Data_Chunk_Speed(const DataSpeedContainer& cop):m_cop(cop),m_temp_speed(nullptr),m_const(nullptr)
	{
		for(int i=0;i<NBSpeed;++i)
		{
			m_data[i]=nullptr;
		}
	}
	DataSpeed* Speed_GetPointer(int i=type_chunk_speed::ispeed)
	{
		return m_data[i];
	}
	DataSpeed& Speed_GetRef(int i=type_chunk_speed::ispeed)
	{
		return *m_data[i];
	}
	const DataSpeed& Speed_GetRef(int i=type_chunk_speed::ispeed) const
	{
		return *m_data[i];
	}
	void Speed_SetPointer(DataSpeed* data,int i=type_chunk_speed::ispeed)
	{
		m_data[i]=data;
	}
	typedef DataSpeed type_speed;

	void Allocate()
	{
		UnAllocate();
		m_temp_speed=new DataSpeedContainer(m_cop);
		m_const=new Const[N];
		for(int i=0;i<NBSpeed;++i)
		{
			m_data[i]=reinterpret_cast<DataSpeed*>(::operator new (N*sizeof(DataSpeed)));
			for(int j=0;j<N;++j)
			{
				new  (m_data[i]+j) DataSpeed(*m_temp_speed,m_const[j]);
			}
		}
	}
	void UnAllocate()
	{
		for(int i=0;i<NBSpeed;++i)
		{
			if(m_data[i]!=nullptr)
			{
				for(int j=0;j<N;++j)
				{
					m_data[i][j].~DataSpeed();
				}
				::operator delete(m_data[i]);
			}
		}
		delete m_temp_speed;
		delete[] m_const;
	}
};

template <typename DataSpeed,int NBSpeed,int N>
int Data_Chunk_Speed<DataSpeed,NBSpeed,N>::ispeed=0;
#endif
