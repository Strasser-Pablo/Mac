/**
 * @file Particle.tpp
 * @brief
 * Implementation file for class Particle.
 **/

template <class TypeVector> 
Particle<TypeVector>::Particle(){
	
};

template <class TypeVector> 
Particle<TypeVector>::Particle(const TypeVector & pos):m_pos(pos){
	
};


template <class TypeVector> 
void Particle<TypeVector>::SetPos(const TypeVector & pos){
	m_pos=pos;
};

template <class TypeVector> 
void Particle<TypeVector>::GetPos( TypeVector & pos)const{
	pos=m_pos;
};

template <class TypeVector> 
template <class Archive>
void Particle<TypeVector>::serialize(Archive & ar,const unsigned int version)
{
	ar & boost::serialization::make_nvp("Position",m_pos);
}
