#ifndef Particle_H
#define Particle_H
#include <boost/serialization/nvp.hpp>
/**
 * @file Particle.h
 * @brief
 * Declaration file for class Particle.
 **/
 
 /**
  * @ingroup GR_Particle
  * @brief
  * class Representing a particle with a given position and speed.
  * @tparam TypeVector type used for vector.
  **/
template <class TypeVector> 
class Particle{
	TypeVector m_pos;
	bool m_berase=false;
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & ar,const unsigned int version);
public:
 typedef TypeVector type_vector;
 /**
  * @brief
  * Default Constructor.
  **/
	Particle();
	void SetToErase(bool berase);
	bool GetToErase();
 /**
  * @brief
  * Construct a Particle with givent postion and speed.
  * @param pos Position.
  * @param speed Speed.
  **/
	Particle(const TypeVector & pos);
	/**
	 * @brief
	 * Get the position.
	 * @param pos Position returned.
	 **/
	void GetPos(TypeVector &pos)const;
	/**
	 * @brief
	 * Set the pos.
	 * @param pos Position to set.
	 **/
	void SetPos(const TypeVector &pos);
};
#include "Particle.tpp"
#endif
