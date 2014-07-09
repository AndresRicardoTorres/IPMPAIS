/*
  Archivo: test_matematicas.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  11 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#include "test_matematicas.h"


Test_Matematicas::Test_Matematicas()
{
}


Test_Matematicas::~Test_Matematicas()
{
}


bool Test_Matematicas::pruebaKolmogorovSmirnov(int muestras, int medidas[], int teorico[])
{
    return true;
}


bool Test_Matematicas::ejecutar(int veces)
{
  bool hayErrores = false;

  while(veces--)
  {
    if(false)
    {  std::cout << "Error1 en Matematicas";  hayErrores = true; }
  }
  return hayErrores;
}
