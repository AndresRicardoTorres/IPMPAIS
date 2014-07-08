/*
  Archivo: main.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  8 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#define TEST


#ifdef TEST

#include "test_fenotipoipmpais.h"
#include "test_algoritmogenetico.h"
#include "test_cromosoma.h"
#include "test_gen.h"
#include "test_matematicas.h"



int main(int, char **)
{
  int numeroDeErrores = 0;
  try
  {
    Test_Matematicas test_Matematicas;
    if(test_Matematicas.ejecutar())
      numeroDeErrores++;

    Test_Gen test_gen;
    if(test_gen.ejecutar())
      numeroDeErrores++;

    Test_Cromosoma test_cromosoma;
    if(test_cromosoma.ejecutar())
      numeroDeErrores++;

    Test_FenotipoIPMPAIS test_FenotipoIPMPAIS;
    if(test_FenotipoIPMPAIS.ejecutar())
      numeroDeErrores++;

    Test_AlgoritmoGenetico test_algoritmoGenetico;
    if(test_algoritmoGenetico.ejecutar())
      numeroDeErrores++;
  }
  catch(const char *mensaje)
  {
    std::cout << "Excepción: " << mensaje << std::endl;
  }
  return numeroDeErrores;
}

#else
// Es una biblioteca, sin main()
#endif
