#ifndef Offset_Key_H
#define Offset_Key_H

template <typename Key,typename Base>
class Offset_Key : public Base
{
	public:
	Key GetKey() const
	{
		Key ret;
		this->m_off.ToKey(ret,this->m_base->GetKey());
		return ret;
	}
	Offset_Key()
	{
	}
	template<typename ... Arg>
	Offset_Key(Arg ... arg): Base(arg...)
	{
	}
};
#endif
