/**
 * @file ComputeSpeedLaplacien.tpp
 * @brief
 * Implementation file for class ComputeSpeedLaplacien.
 **/

template <class TypeWorld>
ComputeSpeedLaplacien<TypeWorld>::ComputeSpeedLaplacien( TypeWorld &world,const Physvector<type_dim,type_data> & _1_h):m_world(world),m_1_h(_1_h)
{
	
}

template <class TypeWorld>
void ComputeSpeedLaplacien<TypeWorld>::Calculate( Physvector<type_dim,int> key ,Physvector<type_dim,type_data> & res)
{
	res.SetAll(0);
	for(int i=1;i<=type_dim;++i)
	{ 
		key.GetRef(i)+=1;
		Physvector<type_dim,type_data> temp;
		m_world.m_mac_grid[key].GetSpeed(temp);
		res+=temp*m_1_h.Get(i)*m_1_h.Get(i);
		key.GetRef(i)-=2;
		m_world.m_mac_grid[key].GetSpeed(temp);
		res+=temp*m_1_h.Get(i)*m_1_h.Get(i);
		key.GetRef(i)+=1;
		m_world.m_mac_grid[key].GetSpeed(temp);
		res-=2.0*temp*m_1_h.Get(i)*m_1_h.Get(i);
	}
}