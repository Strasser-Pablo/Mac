#ifndef Algorithms_H
#define Algorithms_H
template <typename ...>
class Algorithms
{
	public:
	void Do()
	{
	}
};

template <typename Algorithm1, typename ...Algorithm>
class Algorithms<Algorithm1,Algorithm...> : public  Algorithms<Algorithm...>
{
	Algorithm1& A;
	public:
	Algorithms(Algorithm1& in1,Algorithm& ... in2):Algorithms<Algorithm...>(in2...),A(in1)
	{}
	void Do()
	{
		A.Do();
		Algorithms<Algorithm...>::Do();
	}
};
#endif
