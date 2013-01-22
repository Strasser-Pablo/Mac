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
    bool m_first;
	public:
    Policy_Output_Animation(const Data & data __attribute__ ((unused)),const char* filename):m_filename(filename),m_first(true)
	{

	}
    Policy_Output_Animation(const Policy_Output_Animation<Data>& cop): m_filename(cop.m_filename),m_first(true)
	{
	}

    Policy_Output_Animation(const char* filename): m_filename(filename),m_first(true)
	{
	}
	void OutputAnimation(list<string>& m_list,const type_Time_Type& t)
	{
        if(m_first)
        {
             m_out.open(m_filename,fstream::out);
            m_out<<"<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
            m_out<<"<Collection>"<<endl;
            m_first=false;
        }
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
        string str=string(m_filename)+string("_")+string(".m_spos");
        fstream out2(str.c_str(),fstream::out);
        out2<<m_spos<<endl;
        out2<<std::setprecision(30)<<t<<endl;
        out2.close();
	}

    void InputAnimation(type_Time_Type& t)
    {
        m_first=false;
        string str=string(m_filename)+string("_")+string(".m_spos");
        fstream out2(str.c_str(),fstream::in);
        int i;
        out2>>i;
        out2>>t;
        m_spos=i;
        out2.close();
        m_out.open(m_filename,fstream::out|fstream::in);
        m_out.seekp(m_spos);
    }
};
#endif
