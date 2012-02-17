

/**
 * @file VectorContainerWithLabel.tpp
 * @brief
 * File for implemetation of Class VectorContainerWithLabel.
 **/

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::VectorContainerWithLabel(size_type n, const TypeData& value,const TypeLabel &label):VectorContainer<TypeContainer,TypeData,TypeConstant>(n,value),m_label(n,label)
{
	
}
	
template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::~VectorContainerWithLabel()
{
	
}


template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::begin()
{
	return VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>( VectorContainer<TypeContainer,TypeData,TypeConstant>::begin(),m_label.begin());
}

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel> VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::end()
{
	return VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>(VectorContainer<TypeContainer,TypeData,TypeConstant>::end(),m_label.end());
}

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::begin() const
{
	return VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>( VectorContainer<TypeContainer,TypeData,TypeConstant>::begin(),m_label.begin());
}

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabelIteratorConst<TypeContainer,TypeContainerLabel> VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::end() const
{
	return VectorContainerWithLabelIterator<TypeContainer,TypeContainerLabel>(VectorContainer<TypeContainer,TypeData,TypeConstant>::end(),m_label.end());
}


template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
void VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::push_back(const TypeData & data,const TypeLabel & label)
{
	 m_label.push_back(label);
	 VectorContainer<TypeContainer,TypeData,TypeConstant>::push_back(data);
}

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
void VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>:: push_front(const TypeData & data,const TypeLabel & label)
{
	 m_label.push_front(label);
	 VectorContainer<TypeContainer,TypeData,TypeConstant>::push_front(data);
}

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::operator=(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & b )
{
 m_label=b.m_label;
VectorContainer<TypeContainer,TypeData,TypeConstant>::operator=(b);
 return *this;
}


template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>  VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::operator+(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & b )
{
 if(!ControlIfSameLabel(b)){
	 abort();
 }
 VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> res(*this);
 VectorContainer<TypeContainer,TypeData,TypeConstant> & base=res;
 base+=b;
 return res;
}

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>  VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::operator-(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & b )
{
 if(!ControlIfSameLabel(b)){
	 abort();
 }
 VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> res(*this);
 VectorContainer<TypeContainer,TypeData,TypeConstant> & base=res;
 base-=b;
 return res;
}


template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>&  VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::operator+=(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & b )
{
 if(!ControlIfSameLabel(b)){
	 abort();
 }
 VectorContainer<TypeContainer,TypeData,TypeConstant> & base=*this;
 base+=b;
 return *this;
}

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
bool VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::ControlIfSameLabel(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> &b){
	if(size()!=b.size()){
		return false;
	}
	
	VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::const_iterator it2=b.begin();
	for(VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::const_iterator it=begin();it!=end();++it)
	{
		if(*it2!=*it){
			false;
		}
	}
	return true;
}

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>&  VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::operator-=(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> & b )
{
 if(!ControlIfSameLabel(b)){
	 abort();
 }
 VectorContainer<TypeContainer,TypeData,TypeConstant> & base=*this;
 base-=b;
 return *this;
}




template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> operator*(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& a, const TypeConstant & C)
{
 VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> res(a);
 VectorContainer<TypeContainer,TypeData,TypeConstant> & base=res;
 base=base*C;
 return res;
}


template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& operator*=(const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& a, const TypeConstant & C)
{
 VectorContainer<TypeContainer,TypeData,TypeConstant> & base=a;
 base*=C;
 return a;
}

template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> operator*(const TypeConstant & C,const VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>& a)
{
 VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel> res(a);
 VectorContainer<TypeContainer,TypeData,TypeConstant> & base=res;
 base=C*base;
 return res;
}


template <class TypeContainer,class TypeData,class TypeConstant,class TypeContainerLabel,class TypeLabel>
typename VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::size_type VectorContainerWithLabel<TypeContainer,TypeData,TypeConstant,TypeContainerLabel,TypeLabel>::size()
{
 return m_label.size();
}