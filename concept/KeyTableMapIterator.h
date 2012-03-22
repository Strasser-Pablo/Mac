
/**
 * @brief Iterator for KeyTableMap concept class
 *
 * In summary we need to have the following method:
 * - Default construction.
 * - Increment operator.
 * - Dereference operator.
 **/
template<class TypeKey,class TypeData,class TypeComp>
class KeyTableMapIterator{
	public:
	KeyTableMapIterator();
	virtual ~KeyTableMapIterator();
	virtual bool operator==(const KeyTableMapIterator &B) __attribute__((pure));
	virtual bool operator!=(const KeyTableMapIterator &B) __attribute__((pure));
	virtual KeyTableMapIterator<TypeKey,TypeData>& operator++();
	virtual KeyTableMapIterator<TypeKey,TypeData> operator++(int);
	virtual TypeData& operator*() __attribute__((pure));
	virtual TypeKey key() __attribute__((pure));
	virtual TypeData& data() __attribute__((pure));
	/**
	 * @brief 
	 * Return the map iterator used internaly.
	 * @return Map iterator.
	 **/
};

template<class TypeKey,class TypeData,class TypeComp>
class KeyTableMapConstIterator;

/**
 * @brief Constant Iterator for KeyTableMap concept class
 *
 * In summary we need to have the following method:
 * - Default construction.
 * - Increment operator.
 * - Dereference operator.
 **/
template<class TypeKey,class TypeData,class TypeComp>
class KeyTableMapConstIterator
{
	public:
	KeyTableMapConstIterator();
	virtual ~KeyTableMapConstIterator();
	virtual bool operator==(const KeyTableMapConstIterator &B) __attribute__((pure));
	virtual bool operator!=(const KeyTableMapConstIterator &B) __attribute__((pure));
	virtual KeyTableMapConstIterator<TypeKey,TypeData>& operator++();
	virtual KeyTableMapConstIterator<TypeKey,TypeData> operator++(int);
	virtual const TypeData& operator*() __attribute__((pure));
	virtual const TypeKey key() __attribute__((pure));
	virtual const TypeData& data() __attribute__((pure));
};
