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
