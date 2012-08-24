#ifndef Data_CellType_Interior_SFINAE_H
#define Data_CellType_Interior_SFINAE_H

template <typename Base, typename Enable,typename Dummy=void>
class Data_CellType_Interior_SFINAE
{
	typedef void type;
	typedef int type2;
};

template <typename Base>
class Data_CellType_Interior_SFINAE<Base,Base,typename Base::type_method_interior_exist>
{
	typedef int type;
	typedef void type2;
};
#endif
