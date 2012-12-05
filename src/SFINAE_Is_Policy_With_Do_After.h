#ifndef SFINAE_IS_POLICY_WITH_DO_AFTER_H
#define SFINAE_IS_POLICY_WITH_DO_AFTER_H
template <typename Policy,typename Dummy=void>
class SFINAE_Is_Policy_With_Do_After
{
    typedef void TRUE;
    typedef int FALSE;
};

template <typename Policy>
class SFINAE_Is_Policy_With_Do_After<Policy,typename Policy::type_has_do_after>
{
    typedef void FALSE;
    typedef int TRUE;
};
#endif // SFINAE_IS_POLICY_WITH_DO_AFTER_H
