#ifndef To0_h
#define To0_h

/**
 * @file To0.h
 * @brief
 * Declaration file for class To0.
 **/

/**
 * @brief
 * Uttility template metaprogramation class that determine the 0 value.
 * @tparam T Type to know the 0.
 **/
template<class T>
struct To0{
	static const bool implement=false;
	static const T value;
};

/**
 * @brief
 * Specialization for the double case of this class giving the 0 value.
 **/
template<>
struct To0<double>{
	/**
	 * @brief
	 * Value 0. Used to know the 0 value.
	 **/
	static const double value=0;
	
	static const bool implement=true;
};

template<>
struct To0<int>{
	/**
	 * @brief
	 * Value 0. Used to know the 0 value.
	 **/
	static const double value=0;
	
	static const bool implement=true;
};
#endif