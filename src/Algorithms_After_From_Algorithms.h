#ifndef ALGORITHMS_AFTER_FROM_ALGORITHMS_H
#define ALGORITHMS_AFTER_FROM_ALGORITHMS_H

template <typename Data,typename Policy>
class Algorithms_After_From_Algorithms
{
    Policy& m_alg;
public:
    typedef void type_has_do_after;
    Algorithms_After_From_Algorithms(Data& m_data,Policy & pol):m_alg(pol)
    {

    }
   void DoAfter()
   {
       m_alg.Do();
   }
};
#endif // ALGORITHMS_AFTER_FROM_ALGORITHMS_H
