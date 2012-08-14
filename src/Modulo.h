#ifndef Modulo_H
#define Modulo_H
template<typename INT>
INT Modulo(INT a,INT b)
{
	return a>=0 ? a%b : b-1-((-a-1)%b);
}
#endif
