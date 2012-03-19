#ifndef JetDEau_H
#define JetDEau_H
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
#include "MacGravity.h"
#include "MacInitializeCell3.h"
#include "MacApplyViscosity.h"
#include "CalculateTimeStep.h"
#include "ExtrapolateCellFluid.h"
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
#include <boost/serialization/nvp.hpp>
const int dim=2;

#if Use_GooglePerf
	#include <google/profiler.h>
#endif
using namespace std;
class JetDEau
{
	typedef Physvector<dim,int> keyvect;
	typedef Physvector<dim,double> vect;
	typedef Particle<vect> part;
	typedef MacCell<dim,double,int> mac;
	typedef TableContainerList<part> list_part;
	typedef PhysvectorKeyOrder<dim,int> order;
	typedef KeyTableMap<keyvect,mac,order> keytable;
	typedef MacWorld<keytable,list_part> world;
	typedef MacGetStagPos<world>  type_stag;
	typedef MacGetVelocity<world,type_stag > type_vel;
	typedef RungeKutta<Physvector<dim,double> ,MacConvectSpeedFunctor<world,type_vel>,double >  type_meth;
	typedef GetCellType<world> type_get_cell_type;
	typedef std::function<bool(Physvector<dim,int>)> type_partcondfunc;
	typedef std::function<double(Physvector<dim,int>)> type_pres_func;
	typedef ExtrapolateCellFluid<world,type_get_cell_type> type_extrapolate;
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
	Output<world,type_stag> m_out;
	MacConvectSpeed<world,type_meth,type_vel,type_stag,type_get_cell_type> m_conv;
	Mac_1_Order_UpWindConvect<world,type_vel,type_stag,type_get_cell_type> m_conv_1_up;
	MacGravity<world,type_get_cell_type> m_grav;
	NeighborsVelocity<dim,int> m_N_V;
	double m_dt;
	double m_t;
	double m_viscosity_const;
	Physvector<dim,double> m_g;
	Physvector<dim,double> m_v_h;
	Physvector<dim,double> m_v_1_h;
	MacInitializeCell3<world,type_stag,type_get_cell_type,type_partcondfunc,type_pres_func,type_extrapolate> m_init;
	MacApplyViscosity<world,type_get_cell_type> m_viscosity;
	CalculateTimeStepNonIso<world,double,type_get_cell_type> m_time_step;
	ExtrapolateCellFluid<world,type_get_cell_type> m_extrapolate_v;
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
public:
	JetDEau();
	void Calculate();
	void SetUp();
	int& GetFileNumber();
};
#include "JetDEau.tpp"
#endif
