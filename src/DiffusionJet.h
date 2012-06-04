#ifndef DiffusionJet_H
#define DiffusionJet_H
#include "Physvector.h"
#include "Particle.h"
#include "MacCell.h"
#include "TableContainerList.h"
#include "PhysvectorKeyOrder.h"
#include "KeyTableMap.h"
#include "MacWorld2.h"
#include "MacGetStagPos.h"
#include "MacGetVelocity.h"
#include "MacConvectSpeed.h"
#include "SolvePressureCG.h"
#include "Output.h"
#include "MacGravity.h"
#include "MacInitializeCell4.h"
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
#include "UpdateDeleteCell.h"
#include "KeyTableUnorderedMap.h"
#include "HashPhysvector.h"
#include <boost/serialization/nvp.hpp>
#include "MacCalculateCirculation.h"
#include "RungeKutta.h"
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
class DiffusionJet
{
	typedef Physvector<2,int> keyvect;
	typedef Physvector<2,double> vect;
	typedef Particle<vect> part;
	typedef TableContainerList<part> list_part;
	typedef MacCell<2,double,int> mac;
	typedef PhysvectorKeyOrder<2,int> order;
	typedef HashPhysvector<2,int> Hash;
	typedef KeyTableUnorderedMap<keyvect,mac,Hash> keytable;
	typedef MacWorld2<keytable,list_part,2> world;
	typedef MacGetStagPos<world>  type_stag;
	typedef MacGetVelocity<world,type_stag > type_vel;
	typedef GetCellType<world> type_get_cell_type;
 	typedef Output<world,type_stag,type_vel> type_out;
	typedef RungeKutta<Physvector<2,double> ,MacConvectSpeedFunctor<world,type_vel>,double >  type_meth;
	type_meth m_rungeKutta;
	Hash m_hash;
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
	type_vel m_get_v;
	list_part m_part;
	type_stag m_stag;
	order m_O;
	keytable m_table;
	world m_w;
	Output<world,type_stag,type_vel> m_out;
	MacConvectSpeed<world,type_meth,type_vel,type_stag,type_get_cell_type> m_conv;
	Mac_1_Order_UpWindConvect<world,type_vel,type_stag,type_get_cell_type> m_conv_1_up;
	double m_dt;
	double m_t;
	Physvector<2,double> m_v_h;
	Physvector<2,double> m_v_1_h;
	CalculateTimeStepNonIso<world,double,type_get_cell_type> m_time_step;
	double m_cfl_factor;
	int m_i;
	streampos m_spos;
	friend class boost::serialization::access;
	MacCalculateCirculation<world> m_calc_circ;
public:
	/**
	 * @brief
	 * Default constructor.
	 * This only prépare the module. It doesn't put initial condition for speed or set somes variable
	 * like dimension.
	 **/
	DiffusionJet();
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
};
#include "DiffusionJet.tpp"
#endif
