#ifndef Singleton_Impl_H
#define Singleton_Impl_H
template <typename T>
T* Singleton<T>::m_class=nullptr;


template <typename T>
T& Singleton<T>::GetInstance()
{
	if(m_class==nullptr)
	{
		Singleton<T>::m_class=reinterpret_cast<T*>(::operator new(sizeof(T)));
		*Singleton<T>::m_class=T();
		SingletonManager::Insert(reinterpret_cast<void**>(&Singleton<T>::m_class));
	//	Singleton<T>::m_class=new T();
	}
	return *m_class;
}


template <typename T>
void Singleton<T>::Kill()
{
	::operator delete(reinterpret_cast<void*>(m_class));
	//delete Singleton<T>::m_class;
	Singleton<T>::m_class=nullptr;
	SingletonManager::Remove(&Singleton<T>::m_class);
}

unordered_set<void**> SingletonManager::m_set=unordered_set<void**>();
#endif
