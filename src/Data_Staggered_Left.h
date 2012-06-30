#ifndef Data_Staggered_Left_H
#define Data_Staggered_Left_H

template<typename Enable,typename Base,typename Type,typename dummy=void>
class Is_Staggered_Left_SFINAE
{
	public:
	typedef void type;
};

template<typename Base,typename Type>
class Is_Staggered_Left_SFINAE<Type,Base,Type,typename Base::type_data_mac_cell::type_staggered_pos_left>
{
	public:
	typedef int type;
};


template<typename Enable,typename Base,typename Type,typename dummy=void>
class Is_Staggered_SFINAE
{
};

template<typename Base,typename Type>
class Is_Staggered_SFINAE<Type,Base,Type,typename Base::type_data_mac_cell::type_staggered_pos>
{
	public:
	typedef int type;
};

template <typename Base>
class Data_Staggered_Left : public Base
{
	public:
	typedef void type_staggered_pos;
	typedef void type_staggered_pos_left;
	Data_Staggered_Left(const Base & base):Base(base)
	{
	}

	Data_Staggered_Left()
	{
	}

	template <typename InheritedWith>
	using type_DataBase_SubInherite=Data_Staggered_Left<typename Base::template type_DataBase_SubInherite<InheritedWith> >;
	
	typedef Data_Staggered_Left<typename Base::type_SubInherite_Base> type_SubInherite_Base;
	
	template<typename InheritedWith> 
	Data_Staggered_Left(const  type_SubInherite_Base& base, const InheritedWith& in): Base(base,in)
	{
	}
};

#endif 
