#ifndef Decorators_H
#define Decorators_H

/**
 * @ingroup GR_Decorators
 * @brief
 * Empty class from witch we derivate.
 * @tparam Data Data to derivate with.
 **/
template<typename Data>
class Nothing : public Data
{
	public:
	/**
	 * @brief
	 * Constructor.
	 * @param d Data to copy and inherite.
	 **/
	Nothing(Data & d):Data(d)
	{}
};

/**
 * @ingroup GR_Decorators
 * @brief
 * This class will define a type to reorder template argument to be used for the Decorator pattern.
 * The goal is to allow added functionality by derivating by other class.
 * @tparam Data data class that will be given as first template to all template.
 * @tparam Decorator1 name of a template class that accept 2 argument. The first one will be Data. The second one will be a Base Class to derivate by.
 * @tparam Decorator name of a template class that accept 2 argument. The first one will be Data. The second one will be a Base Class to derivate by.
 * 
 * The type defined will be `Decorator1<Data,Decorator2<Data,...> >`.
 **/
template <typename Data,template<class T,class T2> class Decorator1,template<class T3,class T4> class ...Decorator>
class Decorators
{
	public:
	/**
	 * @brief
	 * Type composite witch have the good template order.
	 **/
	typedef  Decorator1<Data,typename Decorators<Data,Decorator...>::type_composite> type_composite;
};

/**
 * @ingroup GR_Decorators
 * @brief
 * This class will define a type to reorder template argument to be used for the Decorator pattern.
 * The goal is to allow added functionality by derivating by other class.
 * @tparam Data data class that will be given as first template to all template.
 * @tparam Decorator1 name of a template class that accept 2 argument. The first one will be Data. The second one will be a Base Class to derivate by.
 * @tparam Decorator name of a template class that accept 2 argument. The first one will be Data. The second one will be a Base Class to derivate by.
 * 
 * The type defined will be `Decorator1<Data,Decorator2<Data,...> >`.
 **/
template <typename Data,template<class T1,class T2> class Decorator1>
class Decorators<Data,Decorator1>
{
	public:
	/**
	 * @brief
	 * Type composite witch have the good template order.
	 **/
	typedef Decorator1<Data,Nothing<Data> > type_composite;
};

#endif
