#ifndef Datas_H
#define Datas_H


template <typename ... Data>
class Datas_Without_Base :  public Data...
{
	public:
	Datas_Without_Base(Data& ... in) : Data(in)...
	{
	}
};

template <typename DataBase,typename ... Data>
class Datas : public DataBase::template type_base_base<DataBase,Datas_Without_Base<Data...> > 
{
	public:
	Datas(DataBase base,Data& ... in) : DataBase::template type_base_base<DataBase,Datas_Without_Base<Data...> >(base,Datas_Without_Base<Data...>(in...))	
	{
	}
	typedef DataBase type_Mac_DataBase;
	typedef void type_Mac_DataBase_Exist;
};
	
#endif
