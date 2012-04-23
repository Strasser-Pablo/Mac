#ifndef MacWorld2_H
#define MacWorld2_H
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>
#include "MacWorld.h"
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
struct MacWorld2:public MacWorld<KeyTable,TableContainer>
{
	MacWorld()==delete;
};


template <class KeyTable,class TableContainer>
struct MacWorld2<KeyTable,TableContainer,2>:public MacWorld<KeyTable,TableContainer>
{
	typedef list<type_particle*> type_list_surface_elem;
	typedef unordered_map<int,type_list_surface_elem> type_list_surface;
	typedef stack<int> type_stack_id;
	type_list_surface m_list_surface;
	MacWorld(const KeyTable &grid,const TableContainer & particles):m_mac_grid(grid),m_particle_list(particles)
	{
	}
	/**
	 * @brief
	 * Constructor.
	 * @attention 
	 * With this constructor element are default constructed. Not Always possible.
	 **/
	MacWorld()
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
			int ret=m_id_stack.front();
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
