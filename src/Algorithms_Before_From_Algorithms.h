#ifndef ALGORITHMS_BEFORE_FROM_ALGORITHMS_H
#define ALGORITHMS_BEFORE_FROM_ALGORITHMS_H

template <typename Data,typename Policy>
class Algorithms_Before_From_Algorithms
{
    Policy& m_alg;
public:
    typedef void type_has_do_before;
    Algorithms_Before_From_Algorithms(Data& m_data,Policy & pol):m_alg(pol)
    {

    }
   void DoBefore()
   {
       m_alg.Do();
   }
};
#endif // ALGORITHMS_BEFORE_FROM_ALGORITHMS_H
