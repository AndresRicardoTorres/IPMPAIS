/*
  Archivo: fenotipo.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#include "fenotipo.h"


Fenotipo::Fenotipo()
{
}


Fenotipo::~Fenotipo()
{
}


void Fenotipo::expresar(const Cromosoma *)
{
  throw "Función pseudo virtual pura";
}
