#ifndef Policy_Output_Animation_H
#define Policy_Output_Animation_H

#include <fstream>
#include <string>
#include <sstream>
#include <list>

using namespace std;

template <typename Data>
class Policy_Output_Animation
{
	typedef typename Data::type_data_struct::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	const char* m_filename;
	fstream m_out; 
	streampos m_spos;
	public:
	Policy_Output_Animation(const Data & data __attribute__ ((unused)),const char* filename):m_filename(filename), m_out(filename,fstream::out)
	{
		m_out<<"<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
		m_out<<"<Collection>"<<endl;
	}
	Policy_Output_Animation(const Policy_Output_Animation<Data>& cop): m_filename(cop.m_filename),m_out(cop.m_filename,fstream::out)
	{
		m_out<<"<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
		m_out<<"<Collection>"<<endl;
	}

	Policy_Output_Animation(const char* filename): m_filename(filename),m_out(filename)
	{
		m_out<<"<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
		m_out<<"<Collection>"<<endl;
	}
	void OutputAnimation(list<string>& m_list,const type_Time_Type& t)
	{
		int i=1;
		for(list<string>::iterator it=m_list.begin();it!=m_list.end();++it)
		{
            m_out<<std::setprecision(30)<<" <DataSet timestep=\""<<t<<"\" group=\"\" part=\""<<i<<"\" file=\""<<*it<<"\" />"<<endl;
			++i;
		}
		m_spos=m_out.tellp();
		m_out<<"</Collection>"<<endl;
		m_out<<"</VTKFile>"<<endl;
		m_out.seekp(m_spos);
		m_out.flush();
	}
};
#endif
