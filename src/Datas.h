#ifndef Datas_H
#define Datas_H

template <typename ... Data>
class Datas : public Data...
{
	public:
	Datas(Data& ... in) : Data(in)...
	{
	}
};
	
#endif
