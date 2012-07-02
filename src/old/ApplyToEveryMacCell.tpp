/**
 * @file ApplyToEveryMacCell.tpp
 * @brief
 * Implementation file for class ApplyToEveryMacCell.
 **/

template <class TypeFunctor,class MacWorld>
ApplyToEveryMacCell<TypeFunctor,MacWorld>::ApplyToEveryMacCell(MacWorld & world,TypeFunctor & funct)
{
	for(typename MacWorld::type_keytable::iterator it=world.m_mac_grid.begin();it!=world.m_mac_grid.end();++it)
	{
		funct(*it);
	}
}

template <class TypeFunctor,class MacWorld>
ApplyToEveryMacCell<TypeFunctor,MacWorld>::ApplyToEveryMacCell(const MacWorld & world,TypeFunctor & funct)
{
	for(typename MacWorld::type_keytable::const_iterator it=world.m_mac_grid.begin();it!=world.m_mac_grid.end();++it)
	{
		funct(*it);
	}
}