/**
 * @file Euler.tpp
 * @brief
 * Implementation file for Euler.
 **/

template<class TypeData,class TypeFunctor,class TypeTime>
Euler<TypeData,TypeFunctor,TypeTime>::Euler()
{
	
}

template<class TypeData,class TypeFunctor,class TypeTime>
Euler<TypeData,TypeFunctor,TypeTime>::~Euler()
{
	
}

template<class TypeData,class TypeFunctor,class TypeTime>
void Euler<TypeData,TypeFunctor,TypeTime>::Calculate(TypeData &data0, TypeFunctor &functor,TypeTime &time,TypeData &dataResult)
{
	dataResult=data0+functor(data0)*time;
}

