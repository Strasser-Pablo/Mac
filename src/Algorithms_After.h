#ifndef Algorithms_After_H
#define Algorithms_After_H
/**
 * @brief Template utility class, witch allow to put together algorithms that will be launched one after the other.
 *
 * @tparam ... Zero or more class with a DoAfter method. DoAfter methode will be lauched in left to right order.
 *
 * This version is the terminal case when all class are traversed.
 *
 *A type named type_has_do_after witch value int is defined. To be used in SFINAE method.
 */
template <typename ...>
class Algorithms_After
{
    public:
    typedef int type_has_do_after;
    /**
     * @brief DoAfter Base case witch do nothing.
     */
    void DoAfter()
    {
    }
};

/**
 * @brief Template utility class, witch allow to put together algorithms that will be launched one after the other.
 *
 * @tparam ... Zero or more class with a DoAfter method. DoAfter methode will be lauched in left to right order.
 *
 * This version is the recursif case whitch launch itself.
 *
 *A type named type_has_do_after witch value int is defined. To be used in SFINAE method.
 */
template <typename Algorithm1, typename ...Algorithm>
class Algorithms_After<Algorithm1,Algorithm...> : public  Algorithms_After<Algorithm...>
{
    Algorithm1& A;
    public:
    typedef int type_has_do_after;
    Algorithms_After(Algorithm1& in1,Algorithm& ... in2):Algorithms_After<Algorithm...>(in2...),A(in1)
    {}
    /**
     * @brief Do method witch will call the do method of all algorithms recursively.
     */
    void DoAfter()
    {
        A.DoAfter();
        Algorithms_After<Algorithm...>::Do();
    }
};
#endif

