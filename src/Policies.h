#ifndef Policies_H
#define Policies_H

template <class ... Policy>
class Policies : public Policy...
{
	public:
	Policies(Policy& ... in) : Policy(in)...
	{
	}
};

#endif
