/*
  Archivo: test_cromosoma.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  8 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/

/**
  @class Test_Cromosoma
  Hace el test de la clase Cromosoma

  Relaciones con otras clases y objetos:
    - Contiene objetos de clase Cromosoma.
    .
*/

#ifndef TEST_CROMOSOMA_H
#define TEST_CROMOSOMA_H


#include "matematicas.h"
#include "cromosoma.h"
#include <iostream>


class Test_Cromosoma
{
  public:
    /** Constructor. No hace nada.
    */
    Test_Cromosoma();
    /** Destructor. No hace nada.
    */
    ~Test_Cromosoma();
    /** Ejecuta todos los tests de Gen
      @return true si hubo errores; y false en caso contrario
    */
    bool ejecutar(int veces=100);
};

#else
class Test_Cromosoma;  // Declaración adelantada
#endif
