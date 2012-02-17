#ifndef UpdateCellToInitialLayer_H
#define UpdateCellToInitialLayer_H
/**
 * @file UpdateCellToInitialLayer.h
 * @brief
 * Declaration file for class UpdateCellToInitialLayer.
 **/

/**
 * @brief 
 * Put the layer of all particle to -1.
 **/
template <class TypeWorld>
class UpdateCellToInitialLayer
{
	TypeWorld & m_world;
public:
	/**
	* @brief
	* Constructor.
	* @param world World to use.
	**/
	UpdateCellToInitialLayer(TypeWorld & world);
	/**
	 * @brief
	 * Do the update
	 **/
	void Update();
};
#include "UpdateCellToInitialLayer.tpp"
#endif