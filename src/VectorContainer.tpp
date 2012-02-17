#include <cstdlib>
#include <iostream>

using namespace std;
/**
 * @file VectorContainer.tpp
 * @brief
 * File where class VectorContainer is implemented.
 **/

template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant>::VectorContainer(size_type n, const TypeData& value): m_data(n,value)
{	
}

template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant>::VectorContainer(const VectorContainer<TypeContainer,TypeData,TypeConstant> & toCopie):m_data(toCopie.m_data)
{
}
	
	
template <class TypeContainer,class TypeData,class TypeConstant>
 VectorContainer<TypeContainer,TypeData,TypeConstant>::~VectorContainer()
 {
	 
 }
 
template <class TypeContainer,class TypeData,class TypeConstant>
typename VectorContainer<TypeContainer,TypeData,TypeConstant>::iterator VectorContainer<TypeContainer,TypeData,TypeConstant>::begin(){
 return m_data.begin();
}
	
template <class TypeContainer,class TypeData,class TypeConstant>
inline typename VectorContainer<TypeContainer,TypeData,TypeConstant>::const_iterator VectorContainer<TypeContainer,TypeData,TypeConstant>::begin() const {
	return m_data.begin();
}
	
template <class TypeContainer,class TypeData,class TypeConstant>
 typename VectorContainer<TypeContainer,TypeData,TypeConstant>::iterator VectorContainer<TypeContainer,TypeData,TypeConstant>::end(){
	return m_data.end();
}
	
template <class TypeContainer,class TypeData,class TypeConstant>
typename VectorContainer<TypeContainer,TypeData,TypeConstant>::const_iterator VectorContainer<TypeContainer,TypeData,TypeConstant>::end() const{
	return m_data.end();
}

template <class TypeContainer,class TypeData,class TypeConstant>
typename VectorContainer<TypeContainer,TypeData,TypeConstant>::size_type VectorContainer<TypeContainer,TypeData,TypeConstant>::size() const{
	return m_data.size();
}

template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant> VectorContainer<TypeContainer,TypeData,TypeConstant>::operator+(const  VectorContainer<TypeContainer,TypeData,TypeConstant> & b){
	if(size()!=b.size()){
		abort();
	}
	VectorContainer<TypeContainer,TypeData,TypeConstant> res(*this);
	const_iterator it=begin();
	const_iterator it2=b.begin();
	for(iterator itres=res.begin();itres!=res.end();++itres){
		*itres=*it+*it2;
		++it;
		++it2;
	}
	return res;
}


template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant>& VectorContainer<TypeContainer,TypeData,TypeConstant>::operator+=(  VectorContainer<TypeContainer,TypeData,TypeConstant> & b){
	if(size()!=b.size()){
		abort();
	}
	const_iterator it2=b.begin();
	for(iterator it=begin();it!=end();++it){
		*it+=*it2;
		++it2;
	}
	return *this;
}


template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant> VectorContainer<TypeContainer,TypeData,TypeConstant>::operator-(const  VectorContainer<TypeContainer,TypeData,TypeConstant> & b){
	if(size()!=b.size()){
		abort();
	}
	VectorContainer<TypeContainer,TypeData,TypeConstant> res(*this);
	const_iterator it=begin();
	const_iterator it2=b.begin();
	for(iterator itres=res.begin();itres!=res.end();++itres){
		*itres=*it-*it2;
		++it;
		++it2;
	}
	return res;
}



template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant>& VectorContainer<TypeContainer,TypeData,TypeConstant>::operator-=(  VectorContainer<TypeContainer,TypeData,TypeConstant> & b){
	if(size()!=b.size()){
		abort();
	}
	const_iterator it2=b.begin();
	for(iterator it=begin();it!=end();++it){
		*it-=*it2;
		++it2;
	}
	return *this;
}

template <class TypeContainer,class TypeData,class TypeConstant>
 void  VectorContainer<TypeContainer,TypeData,TypeConstant>::push_back(const TypeData & data){
	m_data.push_back(data);
}

template <class TypeContainer,class TypeData,class TypeConstant>
 void  VectorContainer<TypeContainer,TypeData,TypeConstant>::push_front(const TypeData & data){
	m_data.push_front(data);
}

template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant> operator*(const  VectorContainer<TypeContainer,TypeData,TypeConstant> & b,const TypeConstant &C)
{
	VectorContainer<TypeContainer,TypeData,TypeConstant> res(b);
	typename VectorContainer<TypeContainer,TypeData,TypeConstant>::const_iterator it=b.begin();
	for(typename VectorContainer<TypeContainer,TypeData,TypeConstant>::iterator itres=res.begin();itres!=res.end();++itres){
		*itres=*it*C;
		++it;
	}
	return res;
}


template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant>& operator*=(  VectorContainer<TypeContainer,TypeData,TypeConstant> & b,const TypeConstant &C)
{
	for(typename VectorContainer<TypeContainer,TypeData,TypeConstant>::iterator it=b.begin();it!=b.end();++it){
		*it*=C;
	}
	return b;
}
	
template <class TypeContainer,class TypeData,class TypeConstant>
VectorContainer<TypeContainer,TypeData,TypeConstant> operator*(const TypeConstant &C,const  VectorContainer<TypeContainer,TypeData,TypeConstant> & b)
{
	VectorContainer<TypeContainer,TypeData,TypeConstant> res(b);
	typename VectorContainer<TypeContainer,TypeData,TypeConstant>::const_iterator it=b.begin();
	for(typename VectorContainer<TypeContainer,TypeData,TypeConstant>::iterator itres=res.begin();itres!=res.end();++itres){
		*itres=C**it;
		++it;
	}
	return res;
}
	
