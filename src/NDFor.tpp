template <class Function,class TypeData,int DIM,int dact>
NDFor<Function,TypeData,DIM,dact>::NDFor(Physvector<DIM,TypeData> &init,TypeData &max,Function &f):m_init(init),m_max(max),m_f(f),m_for(init,max,f)
{
	m_save=m_init.Get(dact+1);
}

template <class Function,class TypeData,int DIM,int dact>
void NDFor<Function,TypeData,DIM,dact>::Calculate()
{
	for(m_init.GetRef(dact+1)=m_save;m_init.GetRef(dact+1)<=m_max;++m_init.GetRef(dact+1))
	{
			m_for.Calculate();
	}
}

template <class Function,class TypeData,int DIM>
NDFor<Function,TypeData,DIM,DIM>::NDFor(Physvector<DIM,TypeData> &init,TypeData &max,Function &f):m_init(init),m_max(max),m_f(f)
{
	
}

template <class Function,class TypeData,int DIM>
void NDFor<Function,TypeData,DIM,DIM>::Calculate()
{
	m_f(m_init);
}