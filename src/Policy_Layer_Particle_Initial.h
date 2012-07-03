#ifndef Policy_Layer_Particle_Initial_H
#define Policy_Layer_Particle_Initial_H

template <typename Type_Int, Type_Int Initial_Layer>
class Policy_Layer_Particle_Initial
{
	public:
	static int GetLayerParticleInitial()
	{
		return Initial_Layer;
	}
};

#endif
