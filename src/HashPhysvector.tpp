template<int DIM,class TypeData>
size_t HashPhysvector<DIM,TypeData>::operator()(const Physvector<DIM,TypeData>& key) const
{
	size_t ret=0;
	int k=0;
	for(int i=1;i<=DIM;++i)
	{
		ret+=key.Get(i)<<k;
		k+=10;
	}
	return ret;	
}

