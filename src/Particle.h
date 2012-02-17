#ifndef Particle_H
#define Particle_H
/**
 * @file Particle.h
 * @brief
 * Declaration file for class Particle.
 **/
 
 /**
  * @brief
  * class Representing a particle with a given position and speed.
  * @tparam TypeVector type used for vector.
  **/
template <class TypeVector> 
class Particle{
	TypeVector m_pos;
public:
 typedef TypeVector type_vector;
 /**
  * @brief
  * Default Constructor.
  **/
	Particle();
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