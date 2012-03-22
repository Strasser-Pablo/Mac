/**
 * @brief KeyTableMap
 *
 *
 *
 **/
template<class TypeKey,class TypeData,class TypeComp=less<TypeKey> >
class KeyTableMap
{
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & Ar,const unsigned int version);
public:
	typedef typename map<TypeKey,TypeData,TypeComp>::size_type size_type;
	typedef KeyTableMapIterator<TypeKey,TypeData,TypeComp> iterator;
	typedef KeyTableMapConstIterator<TypeKey,TypeData,TypeComp>  const_iterator;
	typedef TypeData type_data;
	typedef TypeKey type_key;
	/**
	 * @brief
	 * Construct an empty map with ordening given by argument.
	 * @param comp Class overloading () that compare two key and return true if first is before than second.
	 **/
	KeyTableMap(const TypeComp& comp=less<TypeKey>() );
	virtual ~KeyTableMap();
	virtual void insert(const TypeKey & key,const TypeData & value);
	virtual bool empty() __attribute__((pure));
	virtual size_type size() __attribute__((pure));
	virtual bool Exist(const TypeKey& key) __attribute__((pure));
	virtual TypeData& operator[](const TypeKey & key);
	virtual iterator begin();
	virtual iterator end();
	virtual const_iterator begin()const;
	virtual const_iterator end() const;
	virtual void erase(iterator pos);
	virtual void erase(const TypeKey & key);
	virtual void clear();
};
