#ifndef  Container_Filling_H
#define  Container_Filling_H
#include "Physvector.h"
#include "Particle.h"
#include "MacCell.h"
#include "TableContainerList.h"
#include "PhysvectorKeyOrder.h"
#include "KeyTableMap.h"
#include "MacWorld.h"
#include "MacGetStagPos.h"
#include "MacGetVelocity.h"
#include "RungeKutta.h"
#include "MacConvectSpeed.h"
#include "SolvePressureCG.h"
#include "Output.h"
#include "OutputXMLVTK_Particle.h"
#include "MacGravity.h"
#include "MacInitializeCell.h"
#include "MacApplyViscosity.h"
#include "CalculateTimeStep.h"
#include "ExtrapolateCellFluid2.h"
#include "MacMoveParticle.h"
#include <iostream>
#include <fstream>
#include <sys/times.h>
#include "CalculateTimeStepNonIso.h"
#include "SolvePressureUmfpack.h"
#include "GetCellType.h"
#include <functional>
#include "Config.h"
#include "Mac_1_Order_UpWindConvect.h"
#include "MacConvectCenter.h"
#include "UpdateDeleteCell.h"
#include "KeyTableUnorderedMap.h"
#include "HashPhysvector.h"
#include <boost/serialization/nvp.hpp>
#include "MacCalculateCirculation.h"
const int dim=2;
#define INTERPOLATION_NO_PROTECTION
#if Use_GooglePerf
	#include <google/profiler.h>
#endif
using namespace std;
/**
 * @ingroup GR_JetDEau
 *
 * @brief
 * Class that assemble all module for JetDEau
 *
 * This class is an important class where all class and module needed are put together.
 **/
class Container_Filling
{
	typedef Physvector<dim,int> keyvect;
	typedef Physvector<dim,double> vect;
	typedef Particle<vect> part;
	typedef MacCell<dim,double,int> mac;
	typedef TableContainerList<part> list_part;
	typedef PhysvectorKeyOrder<dim,int> order;
	typedef HashPhysvector<dim,int> Hash;
	typedef KeyTableUnorderedMap<keyvect,mac,Hash> keytable;
	typedef MacWorld<keytable,list_part> world;
	typedef MacGetStagPos<world>  type_stag;
	typedef MacGetVelocity<world,type_stag > type_vel;
	typedef RungeKutta<Physvector<dim,double> ,MacConvectSpeedFunctor<world,type_vel>,double >  type_meth;
	typedef GetCellType<world> type_get_cell_type;
	typedef std::function<bool(Physvector<dim,int>)> type_partcondfunc;
	typedef std::function<double(Physvector<dim,int>)> type_pres_func;
	typedef ExtrapolateCellFluid2<world,type_get_cell_type> type_extrapolate;
 	typedef OutputXMLVTK_Particle<world,type_stag,type_vel> type_out_aux;
 	typedef Output<type_out_aux,dim> type_out;
	Hash m_hash;
	type_partcondfunc m_part_cond;
	type_pres_func m_pres_func;
	type_get_cell_type m_GetCellType;
	int m_fluid;
	int m_air;
	int m_boundary_air;
	int m_boundary_fluid;
	double m_rho_fluid;
	double m_rho_air;
	double m_1_rho_fluid;
	double m_1_rho_air;
	double m_rho_inter;
	double m_1_rho_inter;
	double m_rho_inter_bound;
	double m_1_rho_inter_bound;
	type_meth m_rungeKutta;
	SolvePressureCG<world,type_get_cell_type> m_pres;
	SolvePressureUmfpack<world,type_get_cell_type> m_pres_umf;
	type_vel m_get_v;
	type_stag m_stag;
	order m_O;
	list_part m_part;
	keytable m_table;
	world m_w;
	type_out m_out;
	type_out_aux m_out_aux;
	MacConvectSpeed<world,type_meth,type_vel,type_stag,type_get_cell_type> m_conv;
	Mac_1_Order_UpWindConvect<world,type_vel,type_stag,type_get_cell_type> m_conv_1_up;
	MacConvectCenter<world,type_vel,type_stag,type_get_cell_type> m_conv_center;
	MacGravity<world,type_get_cell_type> m_grav;
	NeighborsVelocity<dim,int> m_N_V;
	double m_dt;
	double m_t;
	double m_viscosity_const;
	Physvector<dim,double> m_g;
	Physvector<dim,double> m_v_h;
	Physvector<dim,double> m_v_1_h;
	MacInitializeCell<world,type_stag,type_get_cell_type,type_partcondfunc,type_pres_func,type_extrapolate> m_init;
	MacApplyViscosity<world,type_get_cell_type> m_viscosity;
	CalculateTimeStepNonIso<world,double,type_get_cell_type> m_time_step;
	type_extrapolate m_extrapolate_v;
	MacMoveParticle<world,type_meth,type_vel,type_stag> m_move_part;
	fstream m_time_out;
	double m_conv_time;
	struct tms m_time_deb;
	struct tms m_time_end;
	double m_time_init;
	double m_time_time_step;
	double m_time_gravity;
	double m_time_viscosity;
	double m_time_pressure;
	double m_time_extrapolate;
	double m_time_move;
	double m_time_convect;
	double m_time_output;
	long m_time_ticks_deb;
	long m_time_ticks_end;
	double m_cfl_factor;
	int m_i;
	streampos m_spos;
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & ar,const unsigned int version);
	UpdateDeleteCell<world> m_delete;
	bool m_no_output;
	MacCalculateCirculation<world> m_calc_circ;
public:
	/**
	 * @brief
	 * Default constructor.
	 * This only prépare the module. It doesn't put initial condition for speed or set somes variable
	 * like dimension.
	 **/
	Container_Filling();
	/**
	 * @brief
	 * Calculate the next time step.
	 **/
	void Calculate();
	/**
	 * @brief
	 * SetUp the new initial condition. Like initial speed and initial condition.
	 **/
	void SetUp();
	/**
	 * @brief
	 * Return a reference of the file number.
	 **/
	int& GetFileNumber() __attribute__((const));
	void SetIfOutput(bool b);
};
#include "Container_Filling.tpp"
#endif
