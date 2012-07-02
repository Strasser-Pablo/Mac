template <class Function,class TypeData,int DIM,int dact>
NDForMin<Function,TypeData,DIM,dact>::NDForMin(Physvector<DIM,TypeData> &init,TypeData &min,Function &f):m_init(init),m_min(min),m_f(f),m_for(init,min,f)
{
	m_save=m_init.Get(dact+1);
}

template <class Function,class TypeData,int DIM,int dact>
void NDForMin<Function,TypeData,DIM,dact>::Calculate()
{
	for(m_init.GetRef(dact+1)=m_save;m_init.GetRef(dact+1)>=m_min;--m_init.GetRef(dact+1))
	{
			m_for.Calculate();
	}
}

template <class Function,class TypeData,int DIM>
NDForMin<Function,TypeData,DIM,DIM>::NDForMin(Physvector<DIM,TypeData> &init,TypeData &min,Function &f):m_init(init),m_min(min),m_f(f)
{
	
}

template <class Function,class TypeData,int DIM>
void NDForMin<Function,TypeData,DIM,DIM>::Calculate()
{
	m_f(m_init);
}