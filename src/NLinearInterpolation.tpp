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
	return SubElement(el,pos,key0,ind);
}

template <class TypeWorld>
typename TypeWorld::type_data NLinearInterpolation<TypeWorld>::SubElement(Physvector<type_dim,int>& el,const Physvector<type_dim,double>& posdelta0scaled,const Physvector<type_dim,int> &key0 ,int ind,int prof)
{
	if(prof<=type_dim&&prof>=0){
	el.Set(prof,0);
	type_data a=SubElement(el,posdelta0scaled,key0,ind,prof+1);
	el.Set(prof,1);
	type_data b=SubElement(el,posdelta0scaled,key0,ind,prof+1);
	return a+b;
	}
	else if(prof==type_dim+1)
	{
		type_data ret=1;
		for(int i=1;i<=type_dim;++i)
		{
			ret*=(posdelta0scaled.Get(i)-1+el.Get(i) )*(-1+2*el.Get(i));
		}
		Physvector<type_dim,type_data> vtemp;
		if(m_world.m_mac_grid.Exist(key0+el))
		{
		m_world.m_mac_grid[key0+el].GetSpeed(vtemp);
		ret*=vtemp.Get(ind);
		return ret;
		}
		else{
			return 0;
		}
	}
	throw InternalError("Normally we don't get there!!!!");
}


 #ifdef TesThrowIntExcept
 template <class TypeWorld>
 void NLinearInterpolation<TypeWorld>::Boum()
 {
	 Physvector<type_dim,int> el;
	 const Physvector<type_dim,double> posdelta0scaled;
	 const Physvector<type_dim,int> key0;
	 SubElement(el,posdelta0scaled,key0,3,type_dim+10);}
 #endif