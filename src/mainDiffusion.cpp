#include "DiffusionJet.h"
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
using namespace std;

const bool bstop=false;
const int nb_stop=100;

int main()
{
	DiffusionJet J;
	J.SetUp();
	int &i=J.GetFileNumber();
	while(true)
	{
		J.Calculate();
		if(bstop)
		{
			if(i>nb_stop)
			{
				break;
			}
		}
	}
}
