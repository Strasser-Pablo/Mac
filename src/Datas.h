#ifndef Datas_H
#define Datas_H

/**
 * @ingroup GR_Datas
 * @brief
 * Class that derivate from it's template argument.
 *
 * @tparam Base Base class.
 **/
template <typename Base>
class Data_Empty_Inherit : public Base
{
	/**
	 * @brief
	 * Constructor.
	 * @param base Base class instance.
	 **/
	public:
	Data_Empty_Inherit(const Base & base):Base(base)
	{
	}
};

/**
 * @ingroup GR_Datas
 * @brief
 * Class that aggregate Data with multiple inheritance.
 *
 * @tparam Data Other Data that we will derivate with.
 **/
template <typename ... Data>
class Datas_Without_Base :  public Data...
{
	public:
	/**
	 * @brief
	 * Constructor from reference of all element.
	 * @param in Data instance to copy. 
	 **/
	Datas_Without_Base(const Data& ... in) : Data(in)...
	{
	}
};

/**
 * @ingroup GR_Datas
 * @brief
 * Class that aggregate Data with multiple inheritance.
 *
 * DataBase class is a special class that can be Derivated by the other class.
 * DataBase class is treated so that it's definition and method have more priority than the other.
 *
 * This is done with an intrusif modification of DataBase base class that will change itself to allow derivation from the Data.. class.
 *
 * DataBase need to be a class in group @ref GR_DataBase
 *
 * @tparam DataBase DataBase described above.
 * @tparam Data Other Data that we will derivate with.
 **/
template <typename DataBase,typename ... Data>
class Datas : public DataBase::template type_DataBase_SubInherite<Datas_Without_Base<Data_Empty_Inherit<DataBase>,Data...> > 
{
	public:
	/**
	 * @brief
	 * Constructor from reference of all element.
	 * @param base DataBase instance to copy.
	 * @param in Data instance to copy. 
	 **/
	Datas(const DataBase& base,const Data& ... in) : DataBase::template type_DataBase_SubInherite<Datas_Without_Base<Data_Empty_Inherit<DataBase>,Data...> >(base,Datas_Without_Base<Data_Empty_Inherit<DataBase>,Data...>(base,in...))
	{
	}
	/**
	 * @brief
	 * Type used for SFINAE indicating that we have a DataBase class.
	 **/
	typedef void type_Mac_DataBase_Exist;
	/**
	 * @brief
	 * Type used in the cell definition to find the DataBase.
	 **/
	typedef Data_Empty_Inherit<DataBase> type_Mac_DataBase;
};
	
#endif
