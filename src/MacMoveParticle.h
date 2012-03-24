#ifndef MacMoveParticle_H
#define MacMoveParticle_H
#include "Physvector.h"
#include "MacConvectSpeed.h"
#include "ODEFirstOrderTimeIndependent.h"
/**
 * @ingroup GR_Move_Particle
 **/
template <class TypeWorld,class TypeMethod,class TypeGetSpeed,class TypeGetStagSpeedPos>
class MacMoveParticle
{
		typedef typename TypeWorld::type_data type_data;
		static const int type_dim=TypeWorld::type_dim;
		TypeWorld & m_world;
		Physvector<type_dim,type_data> m_pos;
		type_data& m_dt;
		MacConvectSpeedFunctor<TypeWorld,TypeGetSpeed> m_functor;
		ODEFirstOrderTimeIndependent<Physvector<type_dim,type_data>,MacConvectSpeedFunctor<TypeWorld,TypeGetSpeed> ,type_data,TypeMethod> m_ode;
public:
		MacMoveParticle(TypeWorld & world,TypeMethod &method,TypeGetSpeed & GetSpeed,type_data & dt);
		void Calculate();
};
#include "MacMoveParticle.tpp"
#endif
