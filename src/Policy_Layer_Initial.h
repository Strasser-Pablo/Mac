#ifndef Policy_Layer_Initial_H
#define Policy_Layer_Initial_H

template <typename Type_Int, Type_Int Initial_Layer>
class Policy_Layer_Initial
{
	public:
	static int GetLayerInitial()
	{
		return Initial_Layer;
	}
};

#endif
