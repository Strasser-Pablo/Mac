/**
 * @brief Return the speed interpolated at a given position.
 *
 * This concept need to return the speed at a given position.
 **/
template <class TypeWorld>
class MacGetVelocity
{
public:
	Physvector<type_dim,type_data> Get(const Physvector<type_dim,type_data> &pos);
	type_data Get(const Physvector<type_dim,type_data> &pos,int i);
};
