/**
 * @brief Class of access to the grid and particle list.
 *  
 *  This class store a grid and a particle list.
 *
 *  \pre the following constraint need to be respected.
 *   For KeyTable:
 *   - Need to be a KeyTableMap Concept.
 *   - With as Key a Vector of integral type.
 *   - With as data a MacCell type.
 *    
 *   For TableContainer:
 *   - Need to be a TableContainerList Concept.
 *   - With as Data a Particle Concept.
 **/
template <class KeyTable,class TableContainer>
struct MacWorld{
	/**
	 * @brief
	 * The mac_cell type.
	 **/
	typedef typename KeyTable::type_data type_mac_cell;
	/**
	 * @brief
	 * The key type used to acess the mac cell.
	 **/
	typedef typename KeyTable::type_key type_key;
	/**
	 * @brief
	 * The type of particle.
	 **/
	typedef typename TableContainer::type_data type_particle;
	/**
	 * @brief
	 * The type of keytable.
	 **/
	typedef  KeyTable type_keytable;
	/**
	 * @brief
	 * The type of tablecontainer.
	 **/
	typedef  TableContainer type_tablecontainer;
	/**
	 * @brief
	 * Type of data (float,double).
	 **/
	typedef typename KeyTable::type_data::type_data type_data;
	/**
	 * @brief
	 * Type of vector for key.
	 **/
	typedef typename KeyTable::type_key type_key_vect;
	/**
	 * @brief
	 * Type of mac cell.
	 **/
	typedef typename type_mac_cell::type_cell type_cell;

	/**
	 * @brief 
	 * Dimension of space.
	 **/
	static const int type_dim= KeyTable::type_key::type_dim;

	/**
	 * @brief
	 * The mac grid.
	 **/
	KeyTable m_mac_grid;
	/**
	 * @brief
	 * The list of particle.
	 **/
	TableContainer m_particle_list;
	/**
	 * @brief
	 * Constructor.
	 * @param grid KeyTable to copy to create grid.
	 * @param particles TableContainer to copy to create particles list.
	 **/
	MacWorld(const KeyTable &grid,const TableContainer & particles):m_mac_grid(grid),m_particle_list(particles)
	{
	}
	/**
	 * @brief
	 * Constructor.
	 * @attention 
	 * With this constructor element are default constructed. Not Always possible.
	 **/
	MacWorld()
	{
	}
};
