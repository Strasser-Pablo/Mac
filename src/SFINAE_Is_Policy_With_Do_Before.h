#ifndef SFINAE_IS_POLICY_WITH_DO_BEFORE_H
#define SFINAE_IS_POLICY_WITH_DO_BEFORE_H
template <typename Policy,typename Dummy=void>
class SFINAE_Is_Policy_With_Do_Before
{
    typedef void TRUE;
    typedef int FALSE;
};

template <typename Policy>
class SFINAE_Is_Policy_With_Do_Before<Policy,typename Policy::type_has_do_before>
{
    typedef void FALSE;
    typedef int TRUE;
};
#endif // SFINAE_IS_POLICY_WITH_DO_BEFORE_H
