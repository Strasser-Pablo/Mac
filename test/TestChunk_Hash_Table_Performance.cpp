#include "../src/Data_Chunk_Speed.h"
#include "../src/Data_Chunk_Pressure.h"
#include "../src/Data_Chunk_Layer.h"
#include "../src/Data_Chunk_CellType.h"
#include "../src/Data_Chunk_Bool_Array.h"
#include "../src/Neighbour_List_Empty.h"
#include "../src/Data_Chunk.h"
#include "../src/Hookable_Hash_Table.h"
#include "../src/Hook_Neighbour_List_Chunk.h"
#include "../src/ChunkHashTable.h"
#include "../src/Offset.h"
#include "../src/Offset_Base.h"
#include "../src/Physvector.h"
#include "../src/HashPhysvector.h"
#include "../src/Offset_Base_Speed.h"
#include "../src/Offset_Base_Pressure.h"
#include "../src/Offset_Base_CellType.h"
#include "../src/Offset_Base_Layer.h"
#include "../src/Offset_Base_Neighbour.h"
#include "../src/Singleton.h"

int main()
{
		const int NL=32;
		const int N=pow(NL,3);
		typedef Data_Chunk_Speed<double,N> type_speed;
		typedef Data_Chunk_Bool_Array<N> type_bool_array;
		typedef Data_Chunk<type_speed,type_bool_array> type_chunk;
		typedef Neighbour_List_Empty<3,type_chunk> type_neigh;
		typedef Offset<int,3,NL> type_off;
		typedef Offset_Base<type_off,type_neigh> type_off_base;
		typedef Offset_Base_Speed<double,type_off_base> type_off_base_speed;
		typedef Offset_Base_Neighbour<type_off_base_speed> type_off_base_neighbour;
		typedef Physvector<3,int> type_vect;
		typedef HashPhysvector<3,int> type_hash;
		typedef ChunkHashTable<Hook_Neighbour_List_Chunk,type_vect,type_neigh,type_off_base_neighbour,type_hash> type_chunk_table;
		type_hash hash;
		type_chunk_table m_table(hash);
		type_vect v;
		for(int i=0;i<=200;++i)
		{
			v.Set(1,i);
			for(int j=0;j<=200;++j)
			{
				v.Set(2,j);
				for(int k=0;k<=200;++k)
				{
					v.Set(3,k);
					m_table[v].Speed_GetRef()=(i+j+k)*0.01;
				}
			}
		}

		double sum=0;
		for(int i=0;i<=10;++i)
		{
			for(typename type_chunk_table::iterator it=m_table.begin();it!=m_table.end();++it)
			{
				sum+=it.data().Speed_GetRef();
				for(int j=1;j<=3;++j)
				{
					for(int sign=-1;sign<=1;sign+=2)
					{
						if(it.data().GetNeighbour(j,sign).GetBase()!=nullptr)
						{
							sum+=it.data().GetNeighbour(j,sign).Speed_GetRef();
						}
					}
				}
			}
		}
		cout<<sum<<endl;

		SingletonManager::Kill();
}
