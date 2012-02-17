#ifndef Output_H
#define Output_H
//#include "OutputVectorSpeed.h"
#include "OutputXMLVTK.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
template <class TypeWorld,class TypeGetStagSpeedPos>
class Output
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef KeyTableMap<typename TypeWorld::type_key,int,PhysvectorKeyOrder<type_dim,int> > type_table_point;
	typedef typename TypeWorld::type_cell type_cell;
	OutputXMLVTK<TypeWorld,TypeGetStagSpeedPos> m_out_speed;
	int m_i;
	double & m_t;
	public:
	Output(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,double &t,type_cell fluid);
	void Calculate();
};
#include "Output.tpp"
#endif