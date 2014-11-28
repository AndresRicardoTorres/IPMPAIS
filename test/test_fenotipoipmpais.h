/*
  Archivo: test_fenotipoipmpais.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


/**
  @class Test_FenotipoIPMPAIS
  Crea y evalúa un Cromosoma para resolver el problema de IPMPAIS.

  Relaciones con otras clases y objetos:
    - Es un Fenotipo.
    .
*/


#ifndef TEST_FENOTIPOIPMPAIS_H
#define TEST_FENOTIPOIPMPAIS_H


#include "algoritmogenetico/matematicas.h"
#include "ipmpais/fenotipoipmpais.h"
#include "algoritmogenetico/cromosoma.h"
#include <iostream>


class Test_FenotipoIPMPAIS
{
  public:
    /** Constructor. No hace nada.
    */
    Test_FenotipoIPMPAIS();
    /** Destructor. No hace nada.
    */
    ~Test_FenotipoIPMPAIS();
    /** Ejecuta todos los tests de FenotipoIPMPAIS
      @return true si hubo errores; y false en caso contrario
    */
    bool ejecutar(int veces=100);
};

#else
class Test_FenotipoIPMPAIS;  // Declaración adelantada
#endif
