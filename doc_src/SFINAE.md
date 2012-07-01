Substition Faillure Is Not An Error (SFINAE)
============================================

\defgroup GR_SFINAE SFINAE
This method allow to erase at compile time a function or a template specialisation with respect the value or the existance of a given type.

This idiom is based on the following principle. If an invalid argument or return type is formed during the instantiation of a template. This function is ignored.

The following example come from [Boost: Enable If](http://www.boost.org/doc/libs/1_50_0/libs/utility/enable_if.html)

	int negate(int i) { return -i; }

	template <class F>
	typename F::result_type negate(const F& f) { return -f(); }

Without SFINAE a call to `negate(1)` will be invalid, because when the compiler will instantiate the template function, it will need the type `int::result_type` witch doesn't exist. For this reason, it will ignore this function.

The removal of invalid code can be used to choose witch function to activate.

	template <class T, typename Is_SFINAE<T,int>::type =0>
	void f(T a);

Where Is_SFINAE is a class that define or not type. Type can for example be defined only for specific type of T.
If type is not defined the function will not be created.

For template class, the method is the same, where we use SFINAE on a additional template parameter.

	template <class T, class dummy=void> 
	class A
	{
	};

	template <class T>
	class A<T, Is_SFINAE<T>::type>
	{
	};

If `Is_SFINAE<T>::type` has value void, the second template class will be instantiated.
In the contrary if it doesn't exist the first template class will be instantiated.
