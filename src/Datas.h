#ifndef Datas_H
#define Datas_H

template <typename Base>
class Data_Empty_Inherit : public Base
{
	public:
	Data_Empty_Inherit(const Base & base):Base(base)
	{
	}
};

template <typename ... Data>
class Datas_Without_Base :  public Data...
{
	public:
	Datas_Without_Base(const Data& ... in) : Data(in)...
	{
	}
};

template <typename DataBase,typename ... Data>
class Datas : public DataBase::template type_DataBase_SubInherite<Datas_Without_Base<Data_Empty_Inherit<DataBase>,Data...> > 
{
	public:
	Datas(const DataBase& base,const Data& ... in) : DataBase::template type_DataBase_SubInherite<Datas_Without_Base<Data_Empty_Inherit<DataBase>,Data...> >(base,Datas_Without_Base<Data_Empty_Inherit<DataBase>,Data...>(base,in...))
	{
	}
	typedef void type_Mac_DataBase_Exist;
	typedef Data_Empty_Inherit<DataBase> type_Mac_DataBase;
};
	
#endif
