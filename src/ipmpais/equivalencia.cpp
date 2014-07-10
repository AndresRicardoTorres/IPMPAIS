#include "equivalencia.h"

Equivalencia::Equivalencia()
{
    //ctor
}

Equivalencia::Equivalencia(const char* antigua,const char* nueva,unsigned int orden)
{
    setAntigua(antigua);
    setNueva(nueva);
    setOrden(orden);
}

Equivalencia::~Equivalencia()
{
    //dtor
}
