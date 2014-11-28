/*
  Archivo: test_gen.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  8 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/

/**
  @class Test_Gen
  Hace el test de la clase Gen

  Relaciones con otras clases y objetos:
    - Contiene objetos de clase Gen.
    .
*/

#ifndef TEST_GEN_H
#define TEST_GEN_H

#include "algoritmogenetico/matematicas.h"
#include "algoritmogenetico/gen.h"
#include <iostream>


class Test_Gen
{
  public:
    /** Constructor. No hace nada.
    */
    Test_Gen();
    /** Destructor. No hace nada.
    */
    ~Test_Gen();
    /** Ejecuta todos los tests de Gen
      @return true si hubo errores; y false en caso contrario
    */
    bool ejecutar(int veces=100);
};

#else
class Test_Gen;  // Declaración adelantada
#endif
