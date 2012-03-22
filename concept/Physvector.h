/**
 * @brief Concept Class for class Physvector.
 *
 * The Constraint are sumarized by:
 * - Default Constructible.
 * - Copyable
 * - Serialisable
 * - Allow all arithmetique opperation.
 * - Allow Access of individual component (Set, Get, GetRef).
 * - Index from 1 to Dim. 
 * - Calculation of a Norm
 **/
template <int Dim,class TypeData>
class Physvector{
	private:
	
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar,const unsigned int version);
	
	public:
	
		typedef TypeData type_data;
	
		const static int type_dim=Dim;
		inline Physvector(Physvector<Dim,TypeData> &B);
		/**
	 	* @brief
	 	* Default Constructor.
	 	**/
		inline Physvector();
		/**
	 	* @brief
	 	* Default Destructor.
	 	**/
		inline ~Physvector();
		/**
	 	* @brief
	 	* Set the given indice to given value.
	 	* @param indice Indice to set.
	 	* @param value Value to set to.
	 	**/
		inline void Set(int indice,TypeData value);
		inline void SetAll(TypeData value);
		
		/**
		 * @brief
		 * Get the given indice value.
		 * @param indice Indice to get.
		 * @return TypeData Returned value.
		 **/
		inline TypeData Get(int indice)const;
		inline TypeData& GetRef(int indice);
		/**
		 * @brief
		 * Element by Element addition.
		 * @param b Vector to add with.
		 **/
		inline Physvector<Dim,TypeData> operator+(const Physvector<Dim,TypeData> &b)const;
		/**
		 * @brief
		 * Element by Element substraction.
		 * @param b Vector to substract with.
		 **/
		inline Physvector<Dim,TypeData> operator-(const Physvector<Dim,TypeData> &b)const;
		/**
		 * @brief
		 * Element by Element addition.
		 * @param b Vector to add with.
		 **/
		inline Physvector<Dim,TypeData>& operator+=(const Physvector<Dim,TypeData> &b);
		/**
		 * @brief
		 * Element by Element substraction.
		 * @param b Vector to substract with.
		 **/
		inline Physvector<Dim,TypeData>& operator-=(const Physvector<Dim,TypeData> &b);
		/**
		 * @brief
		 * Multiplication of all element by constant.
		 * @param C Constant to multiply by.
		 **/
		inline Physvector<Dim,TypeData>& operator*=(const TypeData& C);
		/**
		 * @brief
		 * Element by element comparaison.
		 * @param b Vector to compare with.
		 **/
		inline bool operator==(const Physvector<Dim,TypeData> & b) const;
		/**
		 * @brief
		 * Element by element comparaison.
		 * @param b Vector to compare with.
		 **/
		inline bool operator!=(const Physvector<Dim,TypeData> & b) const;	
		
		inline TypeData Norm();
		
		inline TypeData Norm2();
		/**
		 * @brief
		 * Multiplication of all element by constant.
		 * @param C Constant to multiply by.
		 * @param vect Vector to mulitply with.
		 **/
		friend Physvector<Dim,TypeData> operator*<Dim,TypeData>(const TypeData & C,const Physvector<Dim,TypeData> & vect);
		/**
		 * @brief
		 * Multiplication of all element by constant.
		 * @param C Constant to multiply by.
		 * @param vect Vector to mulitply with.
		 **/
		friend Physvector<Dim,TypeData> operator*<Dim,TypeData>(const Physvector<Dim,TypeData> & vect,const TypeData & C);
};
