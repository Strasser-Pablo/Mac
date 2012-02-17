
#ifndef Physvector_H
#define Physvector_H
#include <cstdarg>
#include <exception>
#include <string>
#include <sstream>
#include <cmath>
/**
 * @file Physvector.h
 * @brief
 * Declaration file for class Physvector 
 **/
enum UseEllipse{
	USEELLIPSE
};
class OutOfBoundException:public std::exception{
	public:
	virtual const char* what() const throw(){
		return "Out of BoundException";
	}
};

/**
 * @brief
 * Exception used for OverFlowIndice.
 **/
class OverFlowException:public OutOfBoundException{
	int m_indice;
	int m_limit;
public:
/**
 * @brief 
 * Constructor.
 * @param indice Indice asked.
 * @param limit Maximun valid indice.
 **/
	OverFlowException(int indice,int limit):m_indice(indice),m_limit(limit)
	{
		
	}
	/**
	 * @brief
	 * Description message generated.
	 **/
	virtual const char* what() const throw(){
		std::stringstream ss;
		ss<<"Overflow indice "<<m_indice<<" > "<<m_limit<<".";
		return ss.str().c_str();
	}
};

/**
 * @brief
 * Exception used for UnderFlowIndice.
 **/
class UnderFlowException:public OutOfBoundException{
	int m_indice;
public:
/**
 * @brief
 * Constructor.
 * @param indice Indice asked.
 **/
	UnderFlowException(int indice):m_indice(indice)
	{
		
	}
	/**
	 * @brief
	 * Description message generated.
	 **/
	virtual const char* what() const throw(){
		std::stringstream ss;
		ss<<"Overflow indice "<<m_indice<<" <1. ";
		return ss.str().c_str();
	}
};
//Template forward declaration
template<int Dim,class TypeData>
class Physvector;

//Friend function forward declaration
template<int Dim,class TypeData>
Physvector<Dim,TypeData> operator*(const TypeData & C,const Physvector<Dim,TypeData> & vect);

template<int Dim,class TypeData>
Physvector<Dim,TypeData> operator*(const Physvector<Dim,TypeData> & vect,const TypeData & C);


/**
 * @brief
 * Class representing a N dimensional vector.
 * 
 * \tparam Dim Dimension of the Vector.
 * \tparam TypeData Type of the data.
 * 
 * The type TypeData need to define all standard arithmetique operation (+,-,*).
 * \exception 
 * UnderFlowException and OverFlowException in case of out of range indice.
 * Indice are from 1 to Dim.
 **/
template <int Dim,class TypeData>
class Physvector{
	/**
	 * @brief
	 * Data for the last indice
	 **/
	TypeData m_data[Dim];
	
public:
	
	typedef TypeData type_data;
	
	const static int type_dim=Dim;
	/**
	 * @brief
	 * Default Constructor.
	 **/
	inline Physvector();
	/**
	 * @brief
	 * Default Destructor.
	 **/
	inline ~Physvector();
	/**
	 * @brief
	 * Set the given indice to given value.
	 * @param indice Indice to set.
	 * @param value Value to set to.
	 **/
	inline void Set(int indice,TypeData value);
	inline void SetAll(TypeData value);
	
	inline void Set(UseEllipse ,TypeData first,...);
	/**
	 * @brief
	 * Get the given indice value.
	 * @param indice Indice to get.
	 * @return TypeData Returned value.
	 **/
	inline TypeData Get(int indice)const;
	inline TypeData& GetRef(int indice);
	/**
	 * @brief
	 * Element by Element addition.
	 * @param b Vector to add with.
	 **/
	inline Physvector<Dim,TypeData> operator+(const Physvector<Dim,TypeData> &b)const;
	/**
	 * @brief
	 * Element by Element substraction.
	 * @param b Vector to substract with.
	 **/
	inline Physvector<Dim,TypeData> operator-(const Physvector<Dim,TypeData> &b)const;
	/**
	 * @brief
	 * Element by Element addition.
	 * @param b Vector to add with.
	 **/
	inline Physvector<Dim,TypeData>& operator+=(const Physvector<Dim,TypeData> &b);
	/**
	 * @brief
	 * Element by Element substraction.
	 * @param b Vector to substract with.
	 **/
	inline Physvector<Dim,TypeData>& operator-=(const Physvector<Dim,TypeData> &b);
	/**
	 * @brief
	 * Multiplication of all element by constant.
	 * @param C Constant to multiply by.
	 **/
	inline Physvector<Dim,TypeData>& operator*=(const TypeData& C);
	/**
	 * @brief
	 * Element by element comparaison.
	 * @param b Vector to compare with.
	 **/
	inline bool operator==(const Physvector<Dim,TypeData> & b);
	/**
	 * @brief
	 * Element by element comparaison.
	 * @param b Vector to compare with.
	 **/
	inline bool operator!=(const Physvector<Dim,TypeData> & b);	
	
	inline TypeData Norm();
	
	inline TypeData Norm2();
	/**
	 * @brief
	 * Multiplication of all element by constant.
	 * @param C Constant to multiply by.
	 * @param vect Vector to mulitply with.
	 **/
	friend Physvector<Dim,TypeData> operator*<Dim,TypeData>(const TypeData & C,const Physvector<Dim,TypeData> & vect);
	/**
	 * @brief
	 * Multiplication of all element by constant.
	 * @param C Constant to multiply by.
	 * @param vect Vector to mulitply with.
	 **/
	friend Physvector<Dim,TypeData> operator*<Dim,TypeData>(const Physvector<Dim,TypeData> & vect,const TypeData & C);
	#ifdef TesThrowIntExcept
	void Boum();
	#endif
};


#include "Physvector.tpp"
#endif