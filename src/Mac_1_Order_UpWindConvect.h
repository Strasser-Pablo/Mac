#ifndef MAC_1_ORDER_UPWINDCONVECT_H
#define MAC_1_ORDER_UPWINDCONVECT_H

#include "Physvector.h"
#include "Type_Inter.h"
#include <iostream>

using namespace std;
/**
 * @ingroup GR_Convection
 * @brief
 * Calculate convection using a first order upwind method.
 **/
template <class TypeWorld,class TypeGetSpeed,class TypeGetStagSpeedPos,class GetTypeCell>
class Mac_1_Order_UpWindConvect
{
	static const int type_dim=TypeWorld::type_dim;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_cell type_cell;
	TypeWorld & m_world;
	TypeGetStagSpeedPos & m_stag_pos;
	TypeGetSpeed &m_GetSpeed;
	type_data& m_dt;
	GetTypeCell& m_GetTypeCell;
	Physvector<type_dim,type_data> &m_h;
	Physvector<type_dim,type_data> &m_1_h;
	type_data ElementaryUpwind(Physvector<type_dim,int>& key,int i,int j);
	type_data ElementaryUpwind(Physvector<type_dim,int>&& key,int i,int j);
	public:
	/**
	 * @brief
	 * Constructor.
	 * @param world World to use.
	 * @param GetSpeed Class to use to get speed. Used to get speed component at other speed point.
	 * @param GetStagPos Class to use to get position of speed component.
	 * @param dt TimeStep to move with.
	 * @param getTypeCell Class to get the cell type of a cell.
	 * @param h Get the spacing.
	 * @param _1_h Get 1 over the spacing.
	 **/
	Mac_1_Order_UpWindConvect(TypeWorld & world,TypeGetSpeed & GetSpeed, TypeGetStagSpeedPos &GetStagPos,type_data & dt,GetTypeCell& getTypeCell,Physvector<type_dim,type_data>& h,Physvector<type_dim,type_data>& _1_h);
	/**
	 * @brief
	 * Calculate the next time step.
	 **/
	void Calculate();
};

#include "Mac_1_Order_UpWindConvect.tpp"
#endif
