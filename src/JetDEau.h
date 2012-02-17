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
#include "MacInitializeCell.h"
#include "MacApplyViscosity.h"
#include "CalculateTimeStep.h"
#include "ExtrapolateCellFluid.h"
#include "MacMoveParticle.h"
#include <iostream>
#include <fstream>
#include <sys/times.h>
#include "CalculateTimeStepNonIso.h"
using namespace std;
class JetDEau
{
	typedef Physvector<3,int> keyvect;
	typedef Physvector<3,double> vect;
	typedef Particle<vect> part;
	typedef MacCell<3,double,int> mac;
	typedef TableContainerList<part> list_part;
	typedef PhysvectorKeyOrder<3,int> order;
	typedef KeyTableMap<keyvect,mac,order> keytable;
	typedef MacWorld<keytable,list_part> world;
	typedef MacGetStagPos<world>  type_stag;
	typedef MacGetVelocity<world,type_stag > type_vel;
	typedef RungeKutta<Physvector<3,double> ,MacConvectSpeedFunctor<world,type_vel>,double >  type_meth;
	int m_fluid;
	int m_air;
	type_meth m_rungeKutta;
	SolvePressureCG<world> m_pres;
	type_vel m_get_v;
	type_stag m_stag;
	order m_O;
	list_part m_part;
	keytable m_table;
	world m_w;
	Output<world,type_stag> m_out;
	MacConvectSpeed<world,type_meth,type_vel,type_stag> m_conv;
	MacGravity<world> m_grav;
	NeighborsVelocity<3,int> m_N_V;
	double m_dt;
	double m_t;
	double m_viscosity_const;
	Physvector<3,double> m_g;
	Physvector<3,double> m_v_h;
	Physvector<3,double> m_v_1_h;
	MacInitializeCell<world,type_stag> m_init;
	MacApplyViscosity<world> m_viscosity;
	CalculateTimeStepNonIso<world,double> m_time_step;
	ExtrapolateCellFluid<world> m_extrapolate_v;
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
public:
	JetDEau();
	void Calculate();
};
#include "JetDEau.tpp"
#endif
