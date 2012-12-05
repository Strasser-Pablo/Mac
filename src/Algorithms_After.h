#ifndef Algorithms_After_H
#define Algorithms_After_H
template <typename ...>
class Algorithms_After
{
    public:
    typedef int type_has_do_after;
    void DoAfter()
    {
    }
};

template <typename Algorithm1, typename ...Algorithm>
class Algorithms_After<Algorithm1,Algorithm...> : public  Algorithms_After<Algorithm...>
{
    Algorithm1& A;
    public:
    typedef int type_has_do_after;
    Algorithms_After(Algorithm1& in1,Algorithm& ... in2):Algorithms_After<Algorithm...>(in2...),A(in1)
    {}
    void DoAfter()
    {
        A.DoAfter();
        Algorithms_After<Algorithm...>::Do();
    }
};
#endif

