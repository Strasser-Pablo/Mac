#ifndef Singleton_H
#define Singleton_H

#include <unordered_set>
using namespace std;

template <typename T>
class Singleton
{
	protected:
	static T* m_class;
	private:
	T& operator=(const T&)=delete;
	public:
	static T& GetInstance();
	static void Kill();
};

class SingletonManager
{
	public:
	static unordered_set<void**> m_set;
	static void Kill()
	{
		for(unordered_set<void**>::iterator it=m_set.begin();it!=m_set.end();++it)
		{
			if(**it!=nullptr)
			{
				::operator delete(**it);
				**it=nullptr;
			}
		}
	}
	static void Insert(void** point)
	{
		m_set.insert(point);
	}
	static void Remove(void** point)
	{
		m_set.insert(point);
	}
};

#endif
