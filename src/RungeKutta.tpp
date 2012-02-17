/**
 * @file RungeKutta.tpp
 * @brief
 * Implementation file for class RungeKutta.
 **/

template<class TypeData,class TypeFunctor,class TypeTime>
RungeKutta<TypeData,TypeFunctor,TypeTime>::RungeKutta()
{
	
}

template<class TypeData,class TypeFunctor,class TypeTime>
RungeKutta<TypeData,TypeFunctor,TypeTime>::~RungeKutta()
{
	
}

template<class TypeData,class TypeFunctor,class TypeTime>
void RungeKutta<TypeData,TypeFunctor,TypeTime>::Calculate(TypeData &data0, TypeFunctor &functor,TypeTime &timeStep,TypeData &dataResult)
{
	TypeData k=functor(data0);
	double frac=1./6.;
	dataResult=data0+frac*timeStep*k;
	 k=functor(data0+k*(timeStep/2.0));
	dataResult+=2.0*k*frac*timeStep;
	 k=functor(data0+k*(timeStep/2.0));
	dataResult+=2.0*k*frac*timeStep;
	k=functor(data0+k*timeStep);
	dataResult+=k*frac*timeStep;
}

