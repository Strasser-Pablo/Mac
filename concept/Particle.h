/** 
 * @brief Store a Particle with a position.
 *
 * In summary we have the following constraint:
 * - Default constructible
 * - Copyable
 * - Serializable
 * - Access speed.
 **/

template <class TypeVector> 
class Particle{
	private:
		friend class boost::serialization::access;
		template <class Archive>
		void serialize(Archive & ar,const unsigned int version);
	public:
		typedef TypeVector type_vector;
		/**
		* @brief
		* Default Constructor.
		**/
		Particle();
	 	/**
	  	* @brief
	  	* Construct a Particle with givent postion and speed.
	  	* @param pos Position.
	  	* @param speed Speed.
	  	**/
		Particle(const TypeVector & pos);
		/**
		 * @brief
		 * Get the position.
		 * @param pos Position returned.
		 **/
		void GetPos(TypeVector &pos)const;
		/**
		 * @brief
		 * Set the pos.
		 * @param pos Position to set.
		 **/
		void SetPos(const TypeVector &pos);
};
