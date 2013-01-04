#ifndef Algorithms_Before_H
#define Algorithms_Before_H
template <typename ...>
class Algorithms_Before
{
    public:
    typedef int type_has_do_before;
    void DoBefore()
    {
    }
};

template <typename Algorithm1, typename ...Algorithm>
class Algorithms_Before<Algorithm1,Algorithm...> : public  Algorithms_Before<Algorithm...>
{
    Algorithm1& A;
    public:
    typedef int type_has_do_before;
    Algorithms_Before(Algorithm1& in1,Algorithm& ... in2):Algorithms_Before<Algorithm...>(in2...),A(in1)
    {}
    void DoBefore()
    {
        A.DoBefore();
        Algorithms_Before<Algorithm...>::Do();
    }
};
#endif
