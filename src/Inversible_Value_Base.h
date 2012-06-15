#ifndef Inversible_Value_Base_H
#define Inversible_Value_Base_H
template <class Data,class Parent>
class Inversible_Value_Base
{
	Data m_data;
	Data m_1_data;
	protected:
	Data Inverse_Abstract(const Data& data)
	{
		return static_cast<Parent&>(*this).Inverse(data);
	}
	public:
	Inversible_Value_Base()
	{

	}
	Inversible_Value_Base(const Data & data)
	{
		m_data=data;
		m_1_data=Inverse_Abstract(data);
	}
	Data Get() const
	{
		return m_data;
	}
	Data Get_Inv() const
	{
		return m_1_data;
	}
	Data Set(Data data)
	{
		m_data=data;
		m_1_data=Inverse_Abstract(m_data);
	}
	Data Set_Inv(Data data)
	{
		m_data=Inverse_Abstract(m_data);
		m_1_data=data;
	}
	typedef Data type_data;
};
#endif
