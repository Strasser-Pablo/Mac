#ifndef OutputXMLVTK_Speed_Pressure_H
#define OutputXMLVTK_Speed_Pressure_H
#include "KeyTableMap.h"
#include <cmath>
#include <exception>
#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkPoints2D.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkDataArray.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include "VTK_Exception.h"
using namespace std;

/**
 * @ingroup GR_Output
 * @brief
 * Output XML vtk compatible file.
 * @tparam TypeWorld Type used for World.
 * @tparam TypeGetStagSpeedPos Type used for GetStagSpeedPos.
 **/
template <class TypeWorld,class TypeGetStagSpeedPos,class TypeGetSpeed>
class OutputXMLVTK_Speed_Pressure
{
protected:
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef KeyTableMap<typename TypeWorld::type_key,int,PhysvectorKeyOrder<type_dim,int> > type_table_point;
	typedef typename TypeWorld::type_cell type_cell;
	TypeWorld &m_world;
	PhysvectorKeyOrder<type_dim,int> m_o;
	KeyTableMap<typename TypeWorld::type_key,int,PhysvectorKeyOrder<type_dim,int> > m_point;
	int m_i;
	TypeGetStagSpeedPos m_stag_pos;
	TypeGetSpeed &m_GetSpeed;
	const Physvector<type_dim,type_data>& m_h;
	type_cell m_fluid;
public:
	/**
	 * @brief
	 * Constructor.
	 * @param world World used.
	 * @param stag TypeGetStagSpeedPos used.
	 * @param h Spacing used.
	 * @param fluid Value used for fluid.
	 **/
	OutputXMLVTK_Speed_Pressure(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,type_cell fluid,TypeGetSpeed &GetSpeed);
	/**
	 * @brief
	 * Output speed.
	 * @param filename Filename.
	 * @param ind Speed component to output.
	 **/
	void Output(const char * filename,int ind);
	/**
	 * @brief
	 * Output Pressure.
	 * @param filename Filename.
	 **/
	void OutputPressure(const char * filename);
}
;
#include "OutputXMLVTK_Speed_Pressure.tpp"
#endif
