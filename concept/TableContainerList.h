/**
 * @brief Generic Container to store list.
 *
 * In summary we need:
 * - Default constructible.
 * - Copyable
 * - Serializable
 * - Get iterator to end or begin.
 * - Manipulate element.
 **/
template<class TypeData>
class TableContainerList
{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar,const unsigned int version);
	public:
		/**
 		* @brief
 		* Type for Size.
 		**/
		typedef typename list<TypeData>::size_type size_type;
		/**
		 * @brief
		 * Type for Iterator.
		 **/
		typedef TableContainerListIterator<TypeData> iterator;
		/**
		 * @brief
		 * Type for ConstIterator.
		 **/
		typedef TableContainerListConstIterator<TypeData>  const_iterator;
		typedef TypeData type_data;
			TableContainerList();
			virtual ~TableContainerList();
			virtual bool empty() __attribute__((pure));
			virtual size_type size() __attribute__((pure));
			virtual void push_front(const TypeData & data);
			virtual void push_back(const TypeData &data);
			virtual void pop_back();
			virtual void pop_front();
			virtual TypeData& front() __attribute__((pure));
			virtual const TypeData& front()const __attribute__((pure));
			virtual TypeData& back() __attribute__((pure));
			virtual const TypeData& back()const __attribute__((pure));
			virtual void insert(const TypeData &data);
			virtual iterator insert(iterator pos,const TypeData & data);
			virtual iterator erase(iterator pos);
			virtual iterator begin();
			virtual const_iterator begin() const;
			virtual iterator end();
			virtual const_iterator end() const;
	
};
