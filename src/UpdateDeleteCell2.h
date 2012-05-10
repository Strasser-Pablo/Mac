#ifndef UpdateDeleteCell2_H
#define UpdateDeleteCell2_H
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
template <class TypeWorld,class TypeGetCellType>
class UpdateDeleteCell
{
	TypeWorld &m_world;
	TypeGetCellType& m_GetCellType;
public:
/**
 * @brief
 * Constructor.
 * @param world World to use.
 **/
	UpdateDeleteCell2(TypeWorld &world,TypeGetCellType& GetCellType);
	/**
	 * @brief
	 * Do the update.
	 **/
	void Update();
};
#include "UpdateDeleteCell2.tpp"
#endif
