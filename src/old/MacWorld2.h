#ifndef MacWorld2_H
#define MacWorld2_H
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>
#include <list>
#include <unordered_map>
#include <stack>

using namespace std;
/**
 * @file MacWorld2.h
 * @brief
 * Declaration file for class MacWorld.
 **/
/**
 * @ingroup GR_World
 * @brief 
 * Structure to store information the mac grid and the particle.
 * @tparam KeyTable Key Table where the mac cell are stored.
 * @tparam TableContainer Container where the particle are stored.
 **/
template <class KeyTable,class TableContainer,int DIM>
struct MacWorld2
{
	MacWorld2()=delete;
};


template <class KeyTable,class TableContainer>
struct MacWorld2<KeyTable,TableContainer,2> 
{
	/**
	 * @brief
	 * The mac_cell type.
	 **/
	typedef typename KeyTable::type_data type_mac_cell;
	/**
	 * @brief
	 * The key type used to acess the mac cell.
	 **/
	typedef typename KeyTable::type_key type_key;
	/**
	 * @brief
	 * The type of particle.
	 **/
	typedef typename TableContainer::type_data type_particle;
	/**
	 * @brief
	 * The type of keytable.
	 **/
	typedef  KeyTable type_keytable;
	/**
	 * @brief
	 * The type of tablecontainer.
	 **/
	typedef  TableContainer type_tablecontainer;
	/**
	 * @brief
	 * Type of data (float,double).
	 **/
	typedef typename KeyTable::type_data::type_data type_data;
	/**
	 * @brief
	 * Type of vector for key.
	 **/
	typedef typename KeyTable::type_key type_key_vect;
	/**
	 * @brief
	 * Type of mac cell.
	 **/
	typedef typename type_mac_cell::type_cell type_cell;

	/**
	 * @brief 
	 * Dimension of space.
	 **/
	static const int type_dim= KeyTable::type_key::type_dim;

	/**
	 * @brief
	 * The mac grid.
	 **/
	KeyTable m_mac_grid;
	/**
	 * @brief
	 * The list of particle.
	 **/
	TableContainer m_particle_list;
	TableContainer m_particle_const_list;
	typedef list<type_particle*> type_list_surface_elem;
	enum class dir_exterior{LEFT,RIGHT};
	struct list_elem
	{
		dir_exterior m_dir;
		type_list_surface_elem m_list;
		template <class Archive>
		void serialize(Archive & ar,const unsigned int version)
		{
			ar & boost::serialization::make_nvp("dir_exterior",m_dir);
			ar & boost::serialization::make_nvp("list_surf",m_list);
		}
	};
	typedef list_elem type_list_elem;
	typedef unordered_map<int,list_elem> type_list_surface;
	typedef stack<int> type_stack_id;
	type_list_surface m_list_surface;
	MacWorld2(const KeyTable &grid,const TableContainer & particles):m_mac_grid(grid),m_particle_list(particles)
	{
	}
	/**
	 * @brief
	 * Constructor.
	 * @attention 
	 * With this constructor element are default constructed. Not Always possible.
	 **/
	MacWorld2()
	{
	}

	int GetNextId()
	{
		if(m_id_stack.empty())
		{
			++m_max_id;
			return m_max_id;
		}
		else
		{
			int ret=m_id_stack.top();
			m_id_stack.pop();
			return ret;
		}
	}

	void FreeId(int id)
	{
		m_id_stack.push(id);
	}
	private:
	int m_max_id=-1;
	type_stack_id m_id_stack;
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & ar,const unsigned int version)
	{
		ar & boost::serialization::make_nvp("Cell",m_mac_grid);
		ar & boost::serialization::make_nvp("Particle",m_particle_list);
		ar & boost::serialization::make_nvp("max_id",m_max_id);
		if(typename Archive::is_loading())
		{
			cout<<"loading"<<endl;
			size_t size;
			ar & boost::serialization::make_nvp("Size",size);
			for(size_t i=0;i<size;++i)
			{
				typename unordered_map<int,list_elem>::value_type in;
				ar & boost::serialization::make_nvp("Pair",in);
				m_list_surface.insert(in);	
			}
			cout<<"loading hash"<<endl;
			ar & boost::serialization::make_nvp("Size",size);
			cout<<"after size "<<endl;
			for(size_t i=0;i<size;++i)
			{
				int in;
				ar & boost::serialization::make_nvp("Pair",in);
				m_id_stack.push(in);	
			}
			cout<<"after loading"<<endl;
		}
		else if(typename Archive::is_saving())
		{
			size_t size=m_list_surface.size();
			ar & boost::serialization::make_nvp("Size",size);
			for(typename unordered_map<int,list_elem>::const_iterator it=m_list_surface.begin();it!=m_list_surface.end();++it)
			{

				typename unordered_map<int,list_elem>::value_type out=*it;
				ar & boost::serialization::make_nvp("Pair",out);
			}
			

			type_stack_id m_stack;
			size=m_id_stack.size();
			ar & boost::serialization::make_nvp("Size",size);
			while(!m_id_stack.empty())
			{
				m_stack.push(m_id_stack.top());
				int out=m_id_stack.top();
				ar & boost::serialization::make_nvp("Pair",out);
				m_id_stack.pop();
			}

			while(!m_stack.empty())
			{
				m_id_stack.push(m_stack.top());
				m_stack.pop();
			}
		}
	}
};
#endif
