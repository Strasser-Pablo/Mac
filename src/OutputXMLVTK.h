#ifndef OutputXMLVTK_H
#define OutputXMLVTK_H
#include "KeyTableMap.h"
#include <cmath>
#include <exception>
#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkDataArray.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkXMLUnstructuredGridWriter.h>

using namespace std;
class VTKDimensionError:public std::exception{
	public:
	virtual const char* what() const throw(){
		return "VTK File Format doesn't accept dimension different than 1,2,3.";
	}
};

/**
 * @ingroup GR_Output
 **/
template <class TypeWorld,class TypeGetStagSpeedPos>
class OutputXMLVTK
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef KeyTableMap<typename TypeWorld::type_key,int,PhysvectorKeyOrder<type_dim,int> > type_table_point;
	typedef typename TypeWorld::type_cell type_cell;
	TypeWorld &m_world;
	PhysvectorKeyOrder<type_dim,int> m_o;
	KeyTableMap<typename TypeWorld::type_key,int,PhysvectorKeyOrder<type_dim,int> > m_point;
	int m_i;
	TypeGetStagSpeedPos m_stag_pos;
	const Physvector<type_dim,type_data>& m_h;
	type_cell m_fluid;
public:
	OutputXMLVTK(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,type_cell fluid);
	void Output(const char * filename,int ind);
	void OutputPressure(const char * filename);
	void OutputParticle(const char * filename);
}
;
#include "OutputXMLVTK.tpp"
#endif
