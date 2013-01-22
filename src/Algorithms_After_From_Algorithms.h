#ifndef ALGORITHMS_AFTER_FROM_ALGORITHMS_H
#define ALGORITHMS_AFTER_FROM_ALGORITHMS_H
/**
 * @brief Transform a Algorithm in a DoAfter Algorithm.
 *
 *  This is done in creating a method DoAfter witch simpl launch the do method
 *
 * @tparam Data
 *  @tparam Policy an algorithm with a Do method.
 */
template <typename Data,typename Policy>
class Algorithms_After_From_Algorithms
{
    Policy& m_alg;
public:
    typedef void type_has_do_after;
    /**
     * @brief Algorithms_After_From_Algorithms Constructor.
     * @param m_data
     * @param pol reference to algorithm to use.
     */
    Algorithms_After_From_Algorithms(Data& m_data,Policy & pol):m_alg(pol)
    {

    }
    /**
    * @brief DoAfter New Do after method witch call the do method of the policy.
    */
   void DoAfter()
   {
       m_alg.Do();
   }
};
#endif // ALGORITHMS_AFTER_FROM_ALGORITHMS_H
