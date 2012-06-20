#ifndef Decorators_H
#define Decorators_H

template<typename Data>
class Nothing : public Data
{
	public:
		Nothing(Data & d):Data(d)
		{}
};


template <typename Data,template<class T,class T2> class Decorator1,template<class T3,class T4> class ...Decorator>
class Decorators
{
	public:
	typedef  Decorator1<Data,typename Decorators<Data,Decorator...>::type_composite> type_composite;
};

template <typename Data,template<class T1,class T2> class Decorator1>
class Decorators<Data,Decorator1>
{
	public:
	typedef Decorator1<Data,Nothing<Data> > type_composite;
};

#endif
