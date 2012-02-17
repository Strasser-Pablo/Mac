/**
 * @file MacGetStagPos.tpp
 * @brief Implementation file for class MacGetStagPos.
 **/

template<class TypeWorld>
MacGetStagPos<TypeWorld>::MacGetStagPos(const Physvector<type_dim,type_data> &h):m_h(h)
{
	Physvector<type_dim,int> v;
	v.SetAll(0);
	for(int i=1;i<=type_dim;++i)
	{
		v.Set(i,1);
		m_neighv.Set(i,v);
		v.Set(i,0);
	}
}

template<class TypeWorld>
Physvector< MacGetStagPos<TypeWorld>::type_dim,typename MacGetStagPos<TypeWorld>::type_data> MacGetStagPos<TypeWorld>::Get( const Physvector<type_dim,int> key,int ind)
{
	Physvector<type_dim,type_data> ret;
	for(int i=1;i<=type_dim;++i)
	{
		if(i==ind){
		ret.Set(i,(key.Get(i)-0.5)*m_h.Get(i));
		}
		else
		{
			ret.Set(i,(key.Get(i))*m_h.Get(i));
		}
	}
	return ret;
}




template<class TypeWorld>
Physvector<MacGetStagPos<TypeWorld>::type_dim,typename MacGetStagPos<TypeWorld>::type_data> MacGetStagPos<TypeWorld>::GetCorrect(const Physvector<type_dim,type_data> pos,int ind)
{
	Physvector<type_dim,type_data> ret;
	for(int i=1;i<=type_dim;++i)
	{
		if(i==ind){
		ret.Set(i,(-0.5)*m_h.Get(i)+pos.Get(i));
		}
		else{
		ret.Set(i,pos.Get(i));
		}
	}
	return ret;
}

template<class TypeWorld>
Physvector<MacGetStagPos<TypeWorld>::type_dim,typename MacGetStagPos<TypeWorld>::type_data> MacGetStagPos<TypeWorld>::GetCorrectLow(const Physvector<type_dim,type_data> pos,int ind)
{
	Physvector<type_dim,type_data> ret;
	for(int i=1;i<=type_dim;++i)
	{
		if(i==ind){
		ret.Set(i,(+0.5)*m_h.Get(i)+pos.Get(i));
		}
		else{
		ret.Set(i,pos.Get(i));
		}
	}
	return ret;
}

template<class TypeWorld>
NeighborsVelocity<MacGetStagPos<TypeWorld>::type_dim,int> MacGetStagPos<TypeWorld>::GetNeighborsVelocity()
{
	return m_neighv;
}