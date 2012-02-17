/**
 * @file ODEFirstOrderTimeIndependent.tpp 
 * @brief
 * Implementation file for class ODEFirstOrderTimeIndependent.
 **/

template<class TypeData,class TypeFunctor,class TypeTime,class TypeMethod>
ODEFirstOrderTimeIndependent<TypeData,TypeFunctor,TypeTime,TypeMethod>::ODEFirstOrderTimeIndependent(TypeData & data,TypeFunctor & functor,TypeTime  time,TypeMethod &method):m_data(data),m_functor(functor),m_time(time),m_method(method)
{
}	

template<class TypeData,class TypeFunctor,class TypeTime,class TypeMethod>
ODEFirstOrderTimeIndependent<TypeData,TypeFunctor,TypeTime,TypeMethod>::~ODEFirstOrderTimeIndependent()
{
}

template<class TypeData,class TypeFunctor,class TypeTime,class TypeMethod>
void ODEFirstOrderTimeIndependent<TypeData,TypeFunctor,TypeTime,TypeMethod>::Calculate()
{
	m_method.Calculate(m_data,m_functor,m_time,m_data);
}

template<class TypeData,class TypeFunctor,class TypeTime,class TypeMethod>
void ODEFirstOrderTimeIndependent<TypeData,TypeFunctor,TypeTime,TypeMethod>::Calculate(TypeTime timeStep)
{
	m_method.Calculate(m_data,m_functor,timeStep,m_data);
}