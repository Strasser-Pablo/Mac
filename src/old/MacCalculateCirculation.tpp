template <class TypeWorld>
MacCalculateCirculation<TypeWorld>::MacCalculateCirculation(TypeWorld & world,Physvector<type_dim,type_data>& h):m_world(world),m_h(h)
{

}

template <class TypeWorld>
void MacCalculateCirculation<TypeWorld>::Calculate()
{
	for(typename TypeWorld::type_keytable::iterator it= m_world.m_mac_grid.begin();it!=m_world.m_mac_grid.end();++it)
	{
		type_data circulation=0;
		bool b=false;
		if(type_dim==2)
		{
			Physvector<type_dim,int> key=it.key();
			key.GetRef(2)-=1;
			type_data temp;	
			if(m_world.m_mac_grid.Exist(key))
			{
				m_world.m_mac_grid[key].GetInterSpeed(1,temp);
				circulation+=m_h.Get(1)*0.5*temp;	
			}
			else
			{
				b=true;
			}
			key.GetRef(1)+=1;
			if(m_world.m_mac_grid.Exist(key))
			{
				m_world.m_mac_grid[key].GetInterSpeed(1,temp);
				circulation+=m_h.Get(1)*0.5*temp;	
			}
			else
			{
				b=true;
			}
			key.GetRef(1)-=1;
			key.GetRef(2)+=2;
			if(m_world.m_mac_grid.Exist(key))
			{
				m_world.m_mac_grid[key].GetInterSpeed(1,temp);
				circulation-=m_h.Get(1)*0.5*temp;	
			}
			else
			{
				b=true;
			}
			key.GetRef(1)+=1;
			if(m_world.m_mac_grid.Exist(key))
			{
				m_world.m_mac_grid[key].GetInterSpeed(1,temp);
				circulation-=m_h.Get(1)*0.5*temp;	
			}
			else
			{
				b=true;
			}

			if(m_world.m_mac_grid.Exist(key))
			{
				m_world.m_mac_grid[key].GetInterSpeed(2,temp);
				circulation+=m_h.Get(2)*0.5*temp;	
			}
			else
			{
				b=true;
			}

			key.GetRef(2)-=1;
			if(m_world.m_mac_grid.Exist(key))
			{
				m_world.m_mac_grid[key].GetInterSpeed(2,temp);
				circulation+=m_h.Get(2)*0.5*temp;	
			}
			else
			{
				b=true;
			}

			key.GetRef(1)-=2;
			if(m_world.m_mac_grid.Exist(key))
			{
				m_world.m_mac_grid[key].GetInterSpeed(2,temp);
				circulation-=m_h.Get(2)*0.5*temp;	
			}
			else
			{
				b=true;
			}

			key.GetRef(2)+=1;
			if(m_world.m_mac_grid.Exist(key))
			{
				m_world.m_mac_grid[key].GetInterSpeed(2,temp);
				circulation-=m_h.Get(2)*0.5*temp;	
			}
			else
			{
				b=true;
			}
		}
		else
		{
			b=true;
		}
		if(b)
		{
			it.data().SetCirculation(0.0);
		}
		else
		{
			it.data().SetCirculation(circulation);
		}
	}
}
