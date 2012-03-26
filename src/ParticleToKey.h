#ifndef ParticleToKey_H
#define ParticleToKey_H

#include "ApplyToEveryPhysvectorData.h"
#include "RundingFunction.h"
#include "Physvector.h"
/**
 * @file ParticleToKey.h
 * @brief
 * Declaration file for class ParticleToKey.
 **/

/**
 * @brief
 * Transform a particle to the key to the cell in wish particle is.
 * Using the value of 1/h .
 * 
 * \tparam TypeParticle Particle type used.
 * \tparam TypeDataKey type of the data in the physvector used as key(usualy int).
 * \tparam TypeData type of the data in the physvector used as position (usualy double).
 * \tparam DIM dimension of the vector.
 **/
template<class TypeParticle,class TypeDataKey,class TypeData,int DIM>
class ParticleToKey
{
	const Physvector<DIM,TypeData> & m_1_h;
	const Physvector<DIM,TypeData> & m_h;
public:
/**
 * @brief 
 * Constructor.
 * @param _1_h 1 over the spacial spacing.
 **/
	ParticleToKey(const Physvector<DIM,TypeData>& _1_h,const Physvector<DIM,TypeData>& h);
/**
 * @brief 
 * Find the key from a Particle.
 * @param part Particle to witch find key.
 * @return Physvector<DIM,TypeDataKey> key in witch cell is the particle.
 **/
	Physvector<DIM,TypeDataKey> ToKey(const TypeParticle &part);
/**
 * @brief
 * Transform a key integer data to a position.
 **/
	Physvector<DIM,TypeData> FromKey(const Physvector<DIM,TypeDataKey> &key);
};
#include "ParticleToKey.tpp"

#endif
