/*
  Archivo: test_matematicas.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  11 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/

/**
  @class Test_Matematicas
  Hace el test de la clase Gen

  Relaciones con otras clases y objetos:
    - Contiene objetos de clase Gen.
    .
*/


#ifndef TEST_MATEMATICAS_H
#define TEST_MATEMATICAS_H

#include <iostream>


class Test_Matematicas
{
  public:
    /** Constructor. No hace nada.
    */
    Test_Matematicas();
    /** Destructor. No hace nada.
    */
    ~Test_Matematicas();
    /** Ejecuta todos los tests de Matematicas
      @return true si hubo errores; y false en caso contrario
    */
    bool ejecutar(int veces=100);
    /** Se realiza varias veces (muestras) un experimento aleatorio discreto, que debería dar teorico pero
      que en la práctica da medidas.
      Por ejemplo, si se lanzan 100 monedas al aire, debería salir teorico={50,50} pero digamos que sale medidas={48,52}
      La función calcula si son razonables los resultados o si, por el contrario, están sesgados.
      @param muestras
      @param medidas
      @param teorico
      @return true si el resultado es razonable; y false en caso contrario
    */
    bool pruebaKolmogorovSmirnov(int muestras, int medidas[], int teorico[]);
  };


#else
class Test_Matematicas;  // Declaración adelantada
#endif

