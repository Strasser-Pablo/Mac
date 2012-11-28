#ifndef Neighbour_List_Key_H
#define Neighbour_List_Key_H

template<typename Key,typename Base>
class Neighbour_List_Key : public Base
{
	Key m_key;
	typedef Key type_key;
	public:
	void SetKey(const type_key& key)
	{
		m_key=key;	
	};
	const type_key& GetKey() const
	{
		return m_key;
	}
	template< typename ...Arg>
	Neighbour_List_Key(Arg &... arg):Base(arg...)
	{
	}
};

#endif
