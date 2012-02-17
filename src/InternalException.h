#ifndef InternalException_H
#define InternalException_H

/**
 * @file InternalException.h
 * @brief
 * Declaration and implementation file for class InternalException.
 **/

/**
 * @brief
 * Class signaling Internal Error that are not caused by wrong input.
 **/
class InternalError:public std::exception{
	const char* m_mes;
public:
/**
 * @brief
 * Constructor.
 * @param mes Message describing the error.
 **/
	InternalError(const char * mes):m_mes(mes)
	{
		
	}
	/**
	 * @brief
	 * Return the error message.
	 **/
	virtual const char* what() const throw(){
		return m_mes;
	}
};
#endif