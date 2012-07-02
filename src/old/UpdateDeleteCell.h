#ifndef UpdateDeleteCell_H
#define UpdateDeleteCell_H
/**
 * @file UpdateDeleteCell.h
 * @brief
 * Declaration file for class UpdateDeleteCell.
 **/
 
 /**
  * @ingroup GR_Update_Delete
  * @brief 
  * Delete cell that have -1 as layer.
  * This class is used to cleanup unused air cell.
  **/
template <class TypeWorld>
class UpdateDeleteCell
{
	TypeWorld &m_world;
public:
/**
 * @brief
 * Constructor.
 * @param world World to use.
 **/
	UpdateDeleteCell(TypeWorld &world);
	/**
	 * @brief
	 * Do the update.
	 **/
	void Update();
};
#include "UpdateDeleteCell.tpp"
#endif
