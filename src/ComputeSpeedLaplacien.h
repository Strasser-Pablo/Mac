#ifndef ComputeSpeedLaplacien_H
#define ComputeSpeedLaplacien_H

/**
 * @file ComputeSpeedLaplacien.h
 * @brief
 * Declaration file for class ComputeSpeedLaplacien.
 **/

/**
 * @brief
 * Compute the Laplacien for speed from the grid.
 * @tparam TypeWorld World type used to access the grid.
 * The following operation need to be defined:
 * a public member named m_mac_grid that have operator []
 * with argument Physvector<type_dim,int>.
 * And the result need to have an operation GetSpeed.
 * With as argument an reference to Physvector<type_dim,type_data>.
 * @attention 
 * The fluid cell need to have neighboor. In the contrary risk of use of non unitialize value.
 **/
template <class TypeWorld>
class ComputeSpeedLaplacien{
	/**
	 * @brief
	 * Dimension of space for vector like speed.
	 **/
	static const int type_dim=TypeWorld::type_dim;
	/**
	 * @brief
	 * Type for data.
	 **/
	typedef typename TypeWorld::type_data type_data;
	 TypeWorld &m_world;
	const Physvector<type_dim,type_data>& m_1_h;
public:
/**
 * @brief 
 * Constructor from a world and an spacing.
 * @param world World to access the grid.
 * @param _1_h Vector of spacing.
 **/
	ComputeSpeedLaplacien( TypeWorld &world,const Physvector<type_dim,type_data> & _1_h);
	
/**
 * @brief
 * Calculate the derivatif at a given point.
 * @param key Position where to calculate the Laplacien.
 * @param res Vector containing the result.
 **/
	void Calculate( Physvector<type_dim,int> key ,Physvector<type_dim,type_data> & res);
};
#include "ComputeSpeedLaplacien.tpp"
#endif