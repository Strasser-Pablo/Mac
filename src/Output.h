#ifndef Output_H
#define Output_H
//#include "OutputVectorSpeed.h"
#include "OutputXMLVTK.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
/**
 * @ingroup GR_Output
 * @brief
 * Output class.
 * @tparam TypeWorld World type used.
 * @tparam TypeGetStagSpeedPos TypeGetStagSpeedPos used.
 **/
template <class TypeWorld,class TypeGetStagSpeedPos,class TypeGetSpeed>
class Output
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef KeyTableMap<typename TypeWorld::type_key,int,PhysvectorKeyOrder<type_dim,int> > type_table_point;
	typedef typename TypeWorld::type_cell type_cell;
	OutputXMLVTK<TypeWorld,TypeGetStagSpeedPos,TypeGetSpeed> m_out_speed;
	fstream m_out; 
	streampos &m_spos;
	int & m_i;
	double & m_t;
	bool b_with_part;
	public:
	/**
	 * @brief
	 * Constructor.
	 * @param world World used.
	 * @param stag StagSpeedPos used.
	 * @param h Spacing used.
	 * @param t Actual time.
	 * @param fluid Fluid Cell value.
	 * @param i Reference to the output file number.
	 * @param spos Streampos reference used in backup function.
	 **/
	Output(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,double &t,type_cell fluid,int &i,streampos &spos,TypeGetSpeed &GetSpeed,bool with_part=true);
	/**
	 * @brief
	 * Make an output.
	 **/
	void Calculate();
	/**
	 * @brief
	 * SetUp with default value.
	 **/
	void SetUp();
	/**
	 * @brief
	 * Load the needed value for a load of a interupted state.
	 **/
	void Load();
};
#include "Output.tpp"
#endif
