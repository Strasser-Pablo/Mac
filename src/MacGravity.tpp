/**
 * @file MacGravity.tpp
 * @brief
 * Implementation file for class MacGravity.
 **/

template <class TypeWorld>
MacGravity<TypeWorld>::MacGravity( TypeWorld & world,const Physvector<type_dim,type_data>& g,const type_data &dt,const type_cell fluid,NeighborsVelocity<type_dim,int> &neigh):m_g(g),m_dt(dt),m_fluid(fluid),m_world(world),m_neigh(neigh)
{
}


template <class TypeWorld>
void MacGravity<TypeWorld>::Calculate()
{
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_cell type;
		it.data().GetCellType(type);
		if(type==m_fluid)
		{
			Physvector<type_dim,type_data> temp;
			it.data().GetSpeed(temp);
			temp+=m_g*m_dt;
			it.data().SetSpeed(temp);
		}
		else
		{	
			for(int i=1;i<=type_dim;++i)
			{
				Physvector<type_dim,int> vect;
				Physvector<type_dim,int> v;
			    if(m_neigh.Get(i,vect)){
				v=it.key()-vect;
				if(m_world.m_mac_grid.Exist(v))
				{
				m_world.m_mac_grid[v].GetCellType(type);
				if(type==m_fluid)
				{
				Physvector<type_dim,type_data> temp;
				it.data().GetSpeed(temp);
				temp.GetRef(i)+=m_g.Get(i)*m_dt;
				it.data().SetSpeed(temp);
				}
				}
				}
			}
		}
	}
}