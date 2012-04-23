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
	typedef list<type_particle*> type_list_surface_elem;
	enum class dir_exterior{LEFT,RIGHT};
	struct list_elem
	{
		dir_exterior m_dir;
		type_list_surface_elem m_list;
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
};
#endif
