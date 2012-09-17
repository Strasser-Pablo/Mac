#ifndef Algorithms_Solve_Pressure_Empty_Pressure_H
#define Algorithms_Solve_Pressure_Empty_Pressure_H

#include <cmath>
#include <map>
#include <deque>
#include <sys/times.h>

using namespace std;

template <typename DataType>
class Algorithms_Solve_Pressure_Empty_Pressure
{
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data type_data_data;
	typedef typename type_grid::iterator iterator;
	typedef typename type_data_data::type_pressure::type_pressure type_pressure;
	type_grid& m_grid;
	public:
	Algorithms_Solve_Pressure_Empty_Pressure(DataType data): m_grid(data.m_data.GetGridData())
	{
	}
	void Init_Iteration()
	{
	}
	void End_Iteration()
	{
	}
	void Divergence_Projection()
	{
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			it.data().Pressure_GetRef().Pressure_Set(type_pressure(0));
		}
	}
};
#endif
