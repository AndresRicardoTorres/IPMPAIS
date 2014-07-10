/*
  Archivo: test_algoritmogenetico.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  8 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/

/**
  @class Test_AlgoritmoGenetico
  Hace el test de la clase AlgoritmoGenetico
  Para poder testear las funciones protected, se crea una clase Wrapp_AlgoritmoGenetico, que convierte esas funciones a públicas.

  Relaciones con otras clases y objetos:
    - Contiene objetos de clase AlgoritmoGenetico.
    .
*/

#ifndef TEST_ALGORITMOGENETICO_H
#define TEST_ALGORITMOGENETICO_H


#include "matematicas.h"
#include "fenotipoipmpais.h"
#include "admisionesunivalle.h"
#include "algoritmogenetico.h"
#include <iostream>


class Wrapp_AlgoritmoGenetico : public AlgoritmoGenetico
{
  public:
    Wrapp_AlgoritmoGenetico(Fenotipo *fenotipo, int cuantosCromosomas) : AlgoritmoGenetico(fenotipo, cuantosCromosomas)
    {
    }
    void seleccion(int &indiceUnCromosoma, int &indiceOtroCromosoma) const
    {
      AlgoritmoGenetico::seleccion(indiceUnCromosoma, indiceOtroCromosoma);
    }
    Cromosoma *reproduccion(const Cromosoma *unCromosoma, const Cromosoma *otroCromosoma, int probabilidadDeCrucePromedio, int probabilidadDeCruceUniforme, double desviacionTipicaDeLaMutacion) const
    {
      return AlgoritmoGenetico::reproduccion(unCromosoma, otroCromosoma, probabilidadDeCrucePromedio, probabilidadDeCruceUniforme, desviacionTipicaDeLaMutacion);
    }
    void sustitucion(Cromosoma *hijo)
    {
      AlgoritmoGenetico::sustitucion(hijo);
    }
    const Cromosoma *elMejor() const
    {
      return AlgoritmoGenetico::elMejor();
    }
    Cromosoma *operator [](int indice)
    {
      return AlgoritmoGenetico::operator [](indice);
    }
};


class Test_AlgoritmoGenetico
{
  public:
    /** Constructor. No hace nada.
    */
    Test_AlgoritmoGenetico();
    /** Destructor. No hace nada.
    */
    ~Test_AlgoritmoGenetico();
    /** Ejecuta todos los tests de Gen
      @return true si hubo errores; y false en caso contrario
    */
    bool ejecutar(int veces=100);

  protected:
    bool verificarEstadisticamente(int veces, int cuentaAptitudes[2], int numeroDeCromosomasConAptitudAlta, int numeroDeCromosomas);
};

#else
class Test_AlgoritmoGenetico;  // Declaración adelantada
#endif
