#ifndef Offset_Base_Neighbour_H
#define Offset_Base_Neighbour_H
template <typename Base>
class Offset_Base_Neighbour : public Base
{
	public:
	Offset_Base_Neighbour()
	{
	}
	template<typename ... Arg>
	Offset_Base_Neighbour(Arg ... arg): Base(arg...)
	{
	}
	Offset_Base_Neighbour<Base> GetNeighbour(int i,int sign)
	{
		Offset_Base_Neighbour<Base> res;
		if(this->m_off.GetNeighbour(i,sign,res.m_off))
		{
			res.m_base=this->m_base->GetNeighbour(i,sign);
		}
		else
		{
			res.m_base=this->m_base;
		}
		if(res.m_base!=nullptr)
		{
			if(!res.m_base->GetChunk_Bool_Array()[res.m_off.Get()])
			{
				res.m_base=nullptr;
			}
		}
		return res;
	}
	const Offset_Base_Neighbour<Base> GetNeighbour(int i,int sign) const
	{
		Offset_Base_Neighbour<Base> res;
		if(this->m_off.GetNeighbour(i,sign,res.m_off))
		{
			res.m_base=this->m_base->GetNeighbour(i,sign);
		}
		else
		{
			res.m_base=this->m_base;
		}
		if(res.m_base!=nullptr)
		{
			if(!res.m_base->GetChunk_Bool_Array()[res.m_off.Get()])
			{
				res.m_base=nullptr;
			}
		}
		return res;
	}
};
#endif
