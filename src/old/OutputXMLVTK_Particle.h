#ifndef OutputXMLVTK_Particle_H
#define OutputXMLVTK_Particle_H
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
#include "OutputXMLVTK_Speed_Pressure.h"
#include "VTK_Exception.h"

/**
 * @ingroup GR_Output
 * @brief
 * Output XML vtk compatible file.
 * @tparam TypeWorld Type used for World.
 * @tparam TypeGetStagSpeedPos Type used for GetStagSpeedPos.
 **/
template <class TypeWorld,class TypeGetStagSpeedPos,class TypeGetSpeed>
class OutputXMLVTK_Particle : public OutputXMLVTK_Speed_Pressure<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed>
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_cell type_cell;
public:
	/**
	 * @brief
	 * Constructor.
	 * @param world World used.
	 * @param stag TypeGetStagSpeedPos used.
	 * @param h Spacing used.
	 * @param fluid Value used for fluid.
	 **/
	OutputXMLVTK_Particle(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,type_cell fluid,TypeGetSpeed &GetSpeed);

	/**
	 * @brief
	 * Output Particle.
	 * @param filename Filename.
	 **/
	void OutputParticle(const char * filename);
}
;
#include "OutputXMLVTK_Particle.tpp"
#endif
