/**
 * @file ParticleToKey.tpp
 * @brief
 * Implementation file for class ParticleToKey.
 **/

template<class TypeParticle,class TypeDataKey,class TypeData,int DIM>
ParticleToKey<TypeParticle,TypeDataKey,TypeData,DIM>::ParticleToKey(const Physvector<DIM,TypeData> & _1_h,const Physvector<DIM,TypeData> &h):m_1_h(_1_h),m_h(h)
{
}

template<class TypeParticle,class TypeDataKey,class TypeData,int DIM>
Physvector<DIM,TypeDataKey> ParticleToKey<TypeParticle,TypeDataKey,TypeData,DIM>::ToKey(const TypeParticle &part)
{
	Physvector<DIM,TypeDataKey> vout;
	Physvector<DIM,TypeData> vscaled;
	part.GetPos(vscaled);
	for(int i=1;i<=DIM;++i)
	{
	vscaled.GetRef(i)*=m_1_h.Get(i);
	}
	ApplyToEveryPhysvectorData<TypeData,TypeDataKey,Round<TypeData,TypeDataKey>,DIM> apl;
	Round<TypeData,TypeDataKey>R;
	apl.Transform(vscaled,vout,R);
	return vout;
}

template<class TypeParticle,class TypeDataKey,class TypeData,int DIM>
Physvector<DIM,TypeData> ParticleToKey<TypeParticle,TypeDataKey,TypeData,DIM>::FromKey(const  Physvector<DIM,TypeDataKey> & key)
{
	Physvector<DIM,TypeData> ret;
	for(int i=1;i<=DIM;++i)
	{
		ret.Set(i,key.Get(i)*m_h.Get(i));
	}
	return ret;
}