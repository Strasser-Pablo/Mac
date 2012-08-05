#ifndef Offset_Base_H
#define Offset_Base_H

template <typename Offset,typename Base>
class Offset_Base
{
	Offset m_off;
	Base* m_base;
	public:
	Offset_Base(Offset off,Base* base):m_off(off),m_base(base)
	{
	}
	Offset_Base():m_base(nullptr)
	{
	}
	Offset_Base<Offset,Base> GetNeighbour(int i,int sign)
	{
		Offset_Base res;
		if(m_off.GetNeighbour(i,sign,res.m_off))
		{
			res.m_base=m_base->GetNeighbour(i,sign);
		}
		else
		{
			res.m_base=m_base;
		}
		return res;
	}
	void SetOffset(Offset off)
	{
		m_off=off;
	}
	void SetBase(Base* base)
	{
		m_base=base;
	}
	Offset GetOffset()
	{
		return m_off;
	}
	Base* GetBase()
	{
		return m_base;	
	}

};
#endif
