#ifndef Algorithms_H
#define Algorithms_H
/**
 * @brief Template utility class, witch allow to put together algorithms that will be launched one after the other.
 *
 * @tparam ... Zero or more class with a Do method. Do methode will be lauched in left to right order.
 *
 * This version is the terminal case when all class are traversed.
 */
template <typename ...>
class Algorithms
{
	public:
    /**
     * @brief Do Base case witch do nothing.
     */
	void Do()
	{
	}
};

template <typename Algorithm1, typename ...Algorithm>
class Algorithms<Algorithm1,Algorithm...> : public  Algorithms<Algorithm...>
{
	Algorithm1& A;
	public:
    /**
     * @brief Algorithms Constructor witch will take a reference of all algorithm in the same order.
     * @param ... Algorithm where a reference is stored to after launch them in order.
     */
	Algorithms(Algorithm1& in1,Algorithm& ... in2):Algorithms<Algorithm...>(in2...),A(in1)
	{}
    /**
     * @brief Do method witch will call the do method of all algorithms recursively.
     */
	void Do()
	{
		A.Do();
		Algorithms<Algorithm...>::Do();
	}
};
#endif
