/*
  Archivo: gen.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#include "gen.h"


Gen::Gen(double valorMinimo, double valorMaximo)
  : valorMinimo(valorMinimo), valorMaximo(valorMaximo)
{
  mutacionUniforme();
}


Gen::Gen(const Gen &otroGen)
  : valorActual(otroGen.valorActual), valorMinimo(otroGen.valorMinimo), valorMaximo(otroGen.valorMaximo)
{
}


Gen::~Gen()
{
}


double Gen::valor() const
{
  return valorActual;
}


void Gen::mutacionUniforme()
{
  Matematicas *matematicas = Matematicas::crear();
  valorActual = matematicas->randDouble(valorMinimo, valorMaximo, false, false);
}


void Gen::mutacionGaussiana(double desviacionTipicaDeLaMutacion)
{
  Matematicas *matematicas = Matematicas::crear();
  valorActual = matematicas->randGaussiano(valorActual, valorMinimo, valorMaximo, false, false, desviacionTipicaDeLaMutacion);
  if(valorActual < valorMinimo)
    valorActual = valorMinimo;
  if(valorActual > valorMaximo)
    valorActual = valorMaximo;
}


Gen *Gen::cruceUniforme(const Gen *otroGen) const
{
  Matematicas *matematicas = Matematicas::crear();
  Gen *hijo = (matematicas->randBool() ? clonar() : otroGen->clonar());
  return hijo;
}


Gen *Gen::crucePromedio(const Gen *otroGen) const
{
  Gen *hijo = clonar();
  hijo->valorActual = (valorActual + otroGen->valorActual) / 2.0;
  return hijo;
}


Gen *Gen::clonar() const
{
  return new Gen(*this);
}





