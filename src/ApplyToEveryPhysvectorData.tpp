/**
 * @file ApplyToEveryPhysvectorData.tpp
 * @brief
 * Implementation file for class ApplyToEveryPhysvectorData.
 **/


template <class TypeDataIn,class TypeDataOut,class TypeFunctor,int DIM>
void ApplyToEveryPhysvectorData<TypeDataIn,TypeDataOut,TypeFunctor,DIM>::Transform(const Physvector<DIM,TypeDataIn> & vin,Physvector<DIM,TypeDataOut> & vout,TypeFunctor & func)
{
	for(int i=1;i<=DIM;++i){
		vout.Set(i,func(vin.Get(i)));
	}
}