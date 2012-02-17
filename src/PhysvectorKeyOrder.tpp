/**
 * @file PhysvectorKeyOrder.tpp
 * @brief
 * Implementation file for class PhysvectorKeyOrder.
 **/

template<int Dim,class TypeData>
bool PhysvectorKeyOrder<Dim,TypeData>::operator()(const Physvector<Dim,TypeData> &A,const Physvector<Dim,TypeData> &B) const
{
 	for(int i=1;i<=Dim;++i){
		if(A.Get(i)<B.Get(i)){
			return true;
		}
		if(A.Get(i)>B.Get(i)){
			return false;
		}
	}
	return false;
}