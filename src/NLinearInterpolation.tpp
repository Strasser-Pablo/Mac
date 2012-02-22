/**
 * @file NLinearInterpolation.tpp
 * @brief
 * Implementation file for class NLinearInterpolation.
 **/

template <class TypeWorld>
NLinearInterpolation<TypeWorld>::NLinearInterpolation(TypeWorld &world,const Physvector<type_dim,type_data> &_1_h ):m_1_h(_1_h),m_world(world)
{
}


template <class TypeWorld>
typename TypeWorld::type_data	NLinearInterpolation<TypeWorld>::Calculate( Physvector<type_dim,type_data>  pos,int ind)
{
	Floor<type_data,int> f;
	Physvector<type_dim,int> key0;
	for(int i=1;i<=type_dim;++i)
	{
		pos.GetRef(i)*=m_1_h.Get(i);
		key0.GetRef(i)=f(pos.GetRef(i));
		pos.GetRef(i)-=key0.GetRef(i);
	}
	Physvector<type_dim,int> el;
	SubElement<type_dim,type_data,1,type_dim+1,TypeWorld> SE;
	return SE.Do(el,pos,key0,ind,m_world);
}
