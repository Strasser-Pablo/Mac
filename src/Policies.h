#ifndef Policies_H
#define Policies_H

/**
 * @ingroup GR_Policies
 * @brief
 * This class combine class by publicly inheriting.
 * @tparam Policy Class to inherit by.
 **/
template <class ... Policy>
class Policies : public Policy...
{
	public:
	/**
	 * @brief
	 * Constructor.
	 * @param in Instance to Policy to copy.
	 **/
	Policies(Policy& ... in) : Policy(in)...
	{
	}
};

#endif
