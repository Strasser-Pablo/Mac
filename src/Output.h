#ifndef Output_H
#define Output_H
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
/**
 * @ingroup GR_Output
 * @brief
 * Output class.
 * @tparam TypeWorld World type used.
 * @tparam TypeGetStagSpeedPos TypeGetStagSpeedPos used.
 **/
template <class OutputMethod,int type_dim>
class Output
{
	fstream m_out; 
	streampos &m_spos;
	int & m_i;
	double & m_t;
	bool b_with_part;
	OutputMethod& m_out_meth;
	public:
	/**
	 * @brief
	 * Constructor.
	 * @param world World used.
	 * @param stag StagSpeedPos used.
	 * @param h Spacing used.
	 * @param t Actual time.
	 * @param fluid Fluid Cell value.
	 * @param i Reference to the output file number.
	 * @param spos Streampos reference used in backup function.
	 **/
	Output(OutputMethod& outmethod,double t,int &i,streampos &spos,bool with_part=true);
	/**
	 * @brief
	 * Make an output.
	 **/
	void Calculate();
	/**
	 * @brief
	 * SetUp with default value.
	 **/
	void SetUp();
	/**
	 * @brief
	 * Load the needed value for a load of a interupted state.
	 **/
	void Load();
};
#include "Output.tpp"
#endif
