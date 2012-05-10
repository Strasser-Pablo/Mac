#include "JetDEau.h"
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
using namespace std;

const bool bstop=false;
const int nb_stop=100;
const bool barchive=true;
const int nb_archive=100;

const bool bload=false;
const char* file_to_load="backup40.xml";
const char* file_save_prefixe="backup";
const char* file_save_extension=".xml";


int main(){
	JetDEau J;
	if(bload)
	{
		std::ifstream ifs(file_to_load);
		boost::archive::xml_iarchive ia(ifs);
		ia>>boost::serialization::make_nvp("JetDEau",J);
	}
	else
	{
		J.SetUp();
	}
	int &i=J.GetFileNumber();
			std::ofstream ofs("initback.xml");
			boost::archive::xml_oarchive oa(ofs);
			oa<<boost::serialization::make_nvp("JetDEau",J);
while(true)
{
	J.Calculate();
	if(barchive)
	{
		if(i%nb_archive==0)
		{
			stringstream ss;
			ss<<i;
			string str=string(file_save_prefixe)+ss.str()+string(file_save_extension);
			cout<<"file: "<<str<<endl;
			std::ofstream ofs(str.c_str());
			boost::archive::xml_oarchive oa(ofs);
			oa<<boost::serialization::make_nvp("JetDEau",J);
		}
	}
	if(bstop)
	{
		if(i>nb_stop)
		{
			break;
		}
	}
}
}
