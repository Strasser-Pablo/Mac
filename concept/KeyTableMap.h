/**
 * @brief Container mapping a key to a object.
 *
 * In summary the following method are needed:
 * - Iterator and constant iterator.
 * - Insert operator and get operator.
 * - Serialization operator.
 *
 * Note that the constructor is not part of the concept.
 **/
template<class TypeKey,class TypeData>
class KeyTableMap
{
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & Ar,const unsigned int version);
public:
	typedef size_t size_type;
	typedef KeyTableMapIterator<TypeKey,TypeData> iterator;
	typedef KeyTableMapConstIterator<TypeKey,TypeData>  const_iterator;
	typedef TypeData type_data;
	typedef TypeKey type_key;
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
	virtual void insert(size_type count);
};
