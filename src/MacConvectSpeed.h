#ifndef MacConvectSpeed_H
#define MacConvectSpeed_H

#include "ODEFirstOrderTimeIndependent.h"
#include "Physvector.h"
#include <iostream>
#include "NeighborsVelocity.h"
/**
 * @file MacConvectSpeed.h
 * @brief
 * Declaration file for class MacConvectSpeed and MacConvectSpeedFunctor.
 **/

using namespace std;
template <class TypeWorld,class TypeGetSpeed>
class MacConvectSpeedFunctor;

/**
 * @brief
 * Convect Speed using a Backward trace particle.
 * Send a particle with backward in time one time step.
 * And Assign speed from the position of the particle.
 * @tparam TypeWorld World to use.
 * @tparam TypeMethod Method to use to solve the differential Equation. Per Example RungeKutta, of Euler.
 * @tparam TypeGetSpeed Method used to interpolate speed.
 * @tparam TypeGetStagSpeedPos Class giving the position of speed point.
 **/
template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos>
class MacConvectSpeed
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_cell type_cell;
	const type_cell & m_fluid;
	ODEFirstOrderTimeIndependent<Physvector<type_dim,type_data>,MacConvectSpeedFunctor<TypeWorld,TypeGetSpeed> ,type_data,TypeMethod> m_ode;
	Physvector<type_dim,type_data> m_speed;
	TypeWorld & m_world;
	TypeGetStagSpeedPos & m_stag_pos;
	TypeGetSpeed &m_GetSpeed;
	type_data& m_dt;
	NeighborsVelocity<type_dim,int> & m_NV;
	MacConvectSpeedFunctor<TypeWorld,TypeGetSpeed> m_functor;
	void TracePart(const Physvector<type_dim,int>& key,Physvector<type_dim,type_data> &vout,int comp);	
	void TracePart(const Physvector<type_dim,int>& key,Physvector<type_dim,type_data> &vout);
public:
		/**
		 * @brief
		 * constructor. 
		 * @param world World Used to acess grid.
		 * @param method Method used to solve differential equation.
		 * @param GetSpeed Method used to interpolate.
		 * @param GetStagPos Class representing position of speed.
		 * @param dt Time step.
		 * @param fluid Fluid cell value.
		 **/
MacConvectSpeed(TypeWorld & world,TypeMethod &method,TypeGetSpeed & GetSpeed, TypeGetStagSpeedPos &GetStagPos,type_data & dt,const type_cell & fluid,NeighborsVelocity<type_dim,int> & NV);
  
  /**
   * @brief
   * Do the calculation.
   **/
  void Calculate();  
};

/**
 * @brief
 * Functor used in class MacConvectSpeed. As function giving the speed.
 * @tparam TypeWorld World type used.
 * @tparam TypeGetSpeed Type of interpolation used.
 **/
template <class TypeWorld,class TypeGetSpeed>
class MacConvectSpeedFunctor
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	TypeGetSpeed &m_GetSpeed;
public:
/**
 * @brief
 * Constructor.
 * @param GetSpeed Method of interpolation used.
 **/
	MacConvectSpeedFunctor(TypeGetSpeed &GetSpeed);
	/**
	 * @brief
	 * Function call of the functor. Calculate the speed.
	 * @param pos Position where to calculate speed.
	 * @return Physvector<type_dim,type_data> speed found.
	 **/
	Physvector<type_dim,type_data> operator()(const Physvector<type_dim,type_data>& pos);
};
#include "MacConvectSpeed.tpp"

#endif