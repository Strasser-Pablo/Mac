#include "VectorContainer.h"
#include "VectorContainerWithLabelIterator.h"

#ifndef VectorContainerWithLabel_h
#define VectorContainerWithLabel_h

/**
 * @file VectorContainerWithLabel.h
 * @brief
 * File for declaration of Class VectorContainerWithLabel.
 **/

// Forward declaration of the class.
template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
class VectorContainerWithLabel;

//Template forward declaration
template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> operator*(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& a, const TypeConstant & C);

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> operator*(const TypeConstant & C,const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& a);

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& operator*=(VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& a, const TypeConstant & C);

/**
 * @brief
 * This class consist like VectorContainer of a element and element addition and multiplication.
 * With as additional information an label.
 * 
 * After every operation an control is done that the label are the same.
 * 
 * \tparam TypeContainer Type of the stl compatible container that contain data.
 * \tparam TypeData Type of the data in the container (double or 2d or 3d vector for a physical case).
 * \tparam TypeConstant Type of the constant used for constant multiplication element by element (normaly double).
 * \tparam TypeContainerLabel Type of the container used for label.
 * \tparam TypeLabel Type of the label(can be everithing with an == operator).
 **/
template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
class VectorContainerWithLabel:public VectorContainer<TypeContainer,TypeData,TypeConstant>
{
	/**
	 * @brief
	 * Container containing the label.
	 **/
	TypeContainerLabel m_label;
	/**
	 * @brief
	 * Compare if label of the two vector are the same.
	 * @param b Vector to compare with.
	 * @return bool True if the label are the same. False if not.
	 **/
	bool ControlIfSameLabel(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> &b);
public:
    /**
	 * @brief
	 * Size type of the container.
	 **/
	typedef typename VectorContainer<TypeContainer,TypeData,TypeConstant>::size_type size_type;
	
	/**
	 * @brief
	 * Iterator type of the container.
	 **/
	typedef  VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> iterator;
	
	/**
	 * @brief
	 * Const_Iterator type of the container.
	 **/
	typedef  VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> const_iterator;
	
	/**
	 * @brief
	 * Label type of the container.
	 **/
	typedef  TypeLabel LabelType;
	
	/**
	 * @brief
	 * Constructor that construct an list of size n with default given value.
	 * \param n Size of the container.
	 * \param value Default value of the container.
	 * \param label Default value of the label.
	 **/
	inline VectorContainerWithLabel(size_type n=0, const TypeData& value= TypeData(),const TypeLabel &label=TypeLabel());
	
	/**
	 * @brief
	 * Default destructor.
	 **/
	inline ~VectorContainerWithLabel();
	
	/**
	 * @brief
	 * Return an iterator to the begining of the container.
	 **/
	inline VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> begin();
	
	/**
	 * @brief
	 * Return an iterator to the ending of the container.
	 **/
	inline VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> end();
	
	/**
	 * @brief
	 * Return an const iterator to the begining of the container.
	 **/
	inline VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> begin() const;
	
	/**
	 * @brief
	 * Return an const iterator to the ending of the container.
	 **/
	inline VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> end() const;
	
	/**
	 * @brief
	 * Add a value at the back of the container.
	 * @param data Data to add.
	 * @param label Label to add.
	 **/
	inline void push_back(const TypeData & data,const TypeLabel & label);
	
	/**
	 * @brief
	 * Add a value at the front of the container.
	 * @param data Data to add.
	 * @param label Label to add.
	 **/
	inline void push_front(const TypeData & data,const TypeLabel & label);
	
	/**
	 * @brief 
	 * Assign a value element by element, including label.
	 * @param b Element to assign.
	 **/
	inline VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & operator=(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & b );
	
	/**
	 * @brief 
	 * Add element by element the data of the container, controling that the label is the same.
	 * @param b Element to add.
	 **/
	inline VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>  operator+(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & b );
	
	/**
	 * @brief 
	 * Substract element by element the data of the container, controling that the label is the same.
	 * @param b Element to Substracted.
	 **/
	inline VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>  operator-(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & b );
	
	/**
	 * @brief 
	 * Add element by element the data of the container, controling that the label is the same.
	 * @param b Element to add.
	 **/
	inline VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>&  operator+=(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & b );
	
	/**
	 * @brief 
	 * Substract element by element the data of the container, controling that the label is the same.
	 * @param b Element to Substracted.
	 **/
	inline VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>&  operator-=(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & b );
	
	/**
	 * @brief
	 * Return the size of the container.
	 **/
	inline size_type size();
	
	/**
	 * @brief
	 * Multiplication with an constant with control of the label.
	 * @param a Container to multiply.
	 * @param C Constant to multiply.
	 **/
	friend VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> operator*<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& a, const TypeConstant & C);
	
	/**
	 * @brief
	 * Multiplication with an constant with control of the label.
	 * @param a Container to multiply.
	 * @param C Constant to multiply.
	 **/
	friend VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& operator*=<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>(VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& a, const TypeConstant & C);
	
	/**
	 * @brief
	 * Multiplication with an constant with control of the label.
	 * @param a Container to multiply.
	 * @param C Constant to multiply.
	 **/
	friend VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> operator*<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>(const TypeConstant & C,const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& a);
};

#include "VectorContainerWithLabel.tpp"
#endif