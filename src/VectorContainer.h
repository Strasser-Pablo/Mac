#include <cstring>

#ifndef VectorContainer_h
#define VectorContainer_h

/**
 * @file VectorContainer.h
 * @brief
 * File for declaration of class VectorContainer.
 **/

//Forward declaration of class.
template <class TypeContainer,class TypeData,class TypeConstant>
class VectorContainer;

//Declarration of template for template friend function
template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant> operator*(const  VectorContainer<TypeContainer,TypeData,TypeConstant> & b,const TypeConstant &C);
	
template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant> operator*(const TypeConstant &C,const  VectorContainer<TypeContainer,TypeData,TypeConstant> & b);
	
template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant>& operator*=(  VectorContainer<TypeContainer,TypeData,TypeConstant> & b,const TypeConstant &C);


/**
 * @brief
 * This class implement element by element addition and multiplication by a constant.
 * The underlying container can be every stl compatible container.
 * The Data type can be every type that define an addition and multiplication by a constant.
 * 
 * \tparam TypeContainer Type of the stl compatible container that contain data.
 * \tparam TypeData Type of the data in the container (double or 2d or 3d vector for a physical case).
 * \tparam TypeConstant Type of the constant used for constant multiplication element by element (normaly double).
 **/
template <class TypeContainer,class TypeData,class TypeConstant>
class VectorContainer{
	/**
	 * @brief
	 * Containter Containing the data.
	 **/
	TypeContainer m_data;
public:
	/**
	 * @brief 
	 * Acces to underlying iterator of the container.
	 **/
	typedef typename TypeContainer::iterator iterator;
	/**
	 * @brief 
	 * Acces to underlying const_iterator of the container.
	 **/
	typedef typename TypeContainer::const_iterator const_iterator;
	/**
	 * @brief 
	 * Acces to underlying size_type of the container.
	 **/
	typedef typename TypeContainer::size_type size_type;
	/**
	 * Create an container of size n constructed with copie of value.
	 * \param n Size of the container to be constructed.
	 * \param value Value of initial value for the data in the container.
	 **/
	inline VectorContainer(size_type n=0, const TypeData& value= TypeData());
	/**
	 * Create a copy with same element.
	 * @param toCopie Element to copy.
	 **/
	inline VectorContainer(const VectorContainer<TypeContainer,TypeData,TypeConstant> & toCopie);
	
	/**
	 * Default destructor.
	 **/
	inline ~VectorContainer();
	
	/**
	 * @brief
	 * Return an iterator to the begining of the container.
	 * @return iterator An iterator of the underlying container.
	 **/
	inline iterator begin();
	/**
	 * @brief
	 * Return an constant iterator to the begining of the container.
	 * @return const_iterator An const_iterator of the underlying container.
	 **/
	inline const_iterator begin() const;
	
	/**
	 * @brief
	 * Return an iterator to the end of the container.
	 * @return iterator An iterator of the underlying container.
	 **/
	inline iterator end();
	
	/**
	 * @brief
	 * Return an constant iterator to the end of the container.
	 * @return const_iterator An const_iterator of the underlying container.
	 **/
	inline const_iterator end() const;
	
	/**
	 * @brief
	 * Return the size of the underlying container.
	 * @return size_type Size of the container.
	 **/
	inline size_type size() const;
	
	/**
	 * @brief
	 * Element by element addition of element of the container.
	 * @param b Container to add with.
	 * @return VectorContainer Container containing the sum.
	 **/
	inline VectorContainer<TypeContainer,TypeData,TypeConstant> operator+(const  VectorContainer<TypeContainer,TypeData,TypeConstant> & b);
	
	/**
	 * @brief
	 * Element by element addition of element of the container with replacing of left hand side.
	 * @param b Container to add with.
	 * @return VectorContainer Container containing the sum.
	 **/
	inline VectorContainer<TypeContainer,TypeData,TypeConstant> & operator+=(  VectorContainer<TypeContainer,TypeData,TypeConstant> & b);
	
	
	/**
	 * @brief
	 * Element by element soustraction of element of the container.
	 * @param b Container to soustract with.
	 * @return VectorContainer Container containing the soustraction.
	 **/
	inline VectorContainer<TypeContainer,TypeData,TypeConstant> operator-(const  VectorContainer<TypeContainer,TypeData,TypeConstant> & b);
	
	/**
	 * @brief
	 * Element by element soustraction of element of the container with replacing of left hand side.
	 * @param b Container to soustract with.
	 * @return VectorContainer Container containing the soustraction.
	 **/
	inline VectorContainer<TypeContainer,TypeData,TypeConstant> & operator-=(  VectorContainer<TypeContainer,TypeData,TypeConstant> & b);
	
	/**
	 * @brief
	 * Push an element at back of the container.
	 * @param data Data to push.
	 **/
	inline void push_back(const TypeData & data);
	
	/**
	 * @brief
	 * Push an element at front the container.
	 * @param data Data to push.
	 **/
	inline void push_front(const TypeData & data);
	
	/**
	 * @brief
	 * Right multiplication of all element by the constant.
	 * @param b Container to multiply with.
	 * @param C Constant to multiply by.
	 * @return VectorContainer Result of the multiplication.
	 **/
	friend  VectorContainer<TypeContainer,TypeData,TypeConstant> operator*<TypeContainer,TypeData,TypeConstant>(const  VectorContainer<TypeContainer,TypeData,TypeConstant> & b,const TypeConstant &C);
	
	/**
	 * @brief
	 *  Multiplication of all element by the constant with replacing the left hand side.
	 * @param b Container to multiply with.
	 * @param C Constant to multiply by.
	 * @return VectorContainer Result of the multiplication.
	 **/
	friend  VectorContainer<TypeContainer,TypeData,TypeConstant>& operator*=<TypeContainer,TypeData,TypeConstant>(  VectorContainer<TypeContainer,TypeData,TypeConstant> & b,const TypeConstant &C);
	
	/**
	 * @brief
	 * Left multiplication of all element by the constant.
	 * @param b Container to multiply with.
	 * @param C Constant to multiply by.
	 * @return VectorContainer Result of the multiplication.
	 **/
	friend  VectorContainer<TypeContainer,TypeData,TypeConstant> operator*<TypeContainer,TypeData,TypeConstant>(const TypeConstant &C,const  VectorContainer<TypeContainer,TypeData,TypeConstant> & b);
};

#include "VectorContainer.tpp"
#endif