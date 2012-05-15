#include <utility>
#include <functional>

namespace std {
template<class A,class B>
class hash<pair<A,B> > {
public:
    size_t operator()(pair<A,B> p) const 
    {
        size_t h1 = std::hash<A>()(p.first);
        size_t h2 = std::hash<B>()(p.second);
        return h1 ^ ( h2 << 1 );
    }
};
}
