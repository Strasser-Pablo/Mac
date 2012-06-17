#ifndef GetCellType_Base_H
#define GetCellType_Base_H

template <class TypeWorld>
struct GetCellType_Base_Argument
{
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	const type_cell &m_default;
	TypeWorld &m_world;
	GetCellType_Base_Argument(TypeWorld & world,const type_cell & _default):m_world(world),m_default(_default)
	{
	}
};

template <class TypeWorld>
class GetCellType_Base
{
	public:
	typedef GetCellType_Base_Argument<TypeWorld> type_input_struct;
	void Compute()
	{
	}
	private:
	typedef typename TypeWorld::type_cell type_cell;
	typedef typename TypeWorld::type_data type_data;
	typedef typename TypeWorld::type_key type_key;
	typedef typename TypeWorld::type_mac_cell type_mac_cell;
	const int type_dim=TypeWorld::type_dim;
	const type_cell &m_default;
	TypeWorld &m_world;
	protected:
	GetCellType_Base(type_input_struct in);
	auto KeyToType(const type_key & key)-> type_cell;
	bool KeyToMacCell(const type_key & key,type_mac_cell & mac);
	bool KeyToMacCellAndType(const type_key & key,type_mac_cell & mac,type_cell& c);
	bool KeyToSignDiff(const type_key & key1,const type_key &key2,int &sign,int& dim);
	void SignDiffToKey(const type_key & key1,type_key &key2,const int sign,const int dim);
};
#include "GetCellType_Base.tpp"
#endif
