/*
  Archivo: algoritmogenetico.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  8 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


/**
  @class AlgoritmoGenetico
  Es un algoritmo genético diseñado para optimizar los puntajes mínimos de cada uno de los componentes del examen
  de ingreso a la universidad y sus ponderaciones.
  El cromosoma consiste en un array lineal de genes. Los genes impares son promedios mínimos exigidos y los genes pares
  son sus correspondientes ponderaciones.
  Al ejecutar el algoritmo genético, el resultado es el mejor Cromosoma, es decir, los puntajes mínimos y poderaciones
  de cada componente del examen, que maximizan la calidad de los estudiantes que entran. En este contexto, calidad significa
  lo probable que es que un estudiante termine la carrera sacando un buen puntaje al egresar (examen de ECAES, promedio de la
  carrera, etc.).

  Relaciones con otras clases y objetos:
    - Contiene un array lineal (población) de Cromosomas.
    .
*/
#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H


#include "cromosoma.h"
#include "fenotipo.h"


class AlgoritmoGenetico
{
  public:
    /** Costructor del algoritmo genético.
      @param fenotipo
      @param cuantosCromosomas. Por defecto 100.
    */
    AlgoritmoGenetico(Fenotipo *fenotipo, int cuantosCromosomas=100);
    /** Destructor
    */
    ~AlgoritmoGenetico();
    /** Ejecuta el proceso de optimización del algoritmo genético y devuelve el mejor Cromosoma. Esta función se puede ejecutar
      varias veces sucesivas.
      @param numeroDeGeneraciones. Por defecto 10000
      @param probabilidadDeCrucePromedio. Por defecto 40 (o sea, 40%)
      @param probabilidadDeCruceUniforme. Por defecto 40 (o sea, 40%). La suma de ambas probabilidades no debe superar 100% (aunque no pasa nada malo si ello ocurre).
      @param desviacionTipicaDeLaMutacion. Por defecto, 1.
      @return el mejor Cromosoma.
    */
    const Cromosoma *ejecutar(int numeroDeGeneraciones=10000, int probabilidadDeCrucePromedio=40, int probabilidadDeCruceUniforme=40, double desviacionTipicaDeLaMutacion=1);

  protected:
    void seleccion(int &indiceUnCromosoma, int &indiceOtroCromosoma) const;
    Cromosoma *reproduccion(const Cromosoma *unCromosoma, const Cromosoma *otroCromosoma, int probabilidadDeCrucePromedio, int probabilidadDeCruceUniforme, double desviacionTipicaDeLaMutacion) const;
    void sustitucion(Cromosoma *hijo);
    const Cromosoma *elMejor() const;
    Cromosoma *operator [](int indice);

  private:
    Fenotipo *fenotipo;
    int cuantosCromosomas;
    Cromosoma **cromosomas;
};

#else
class AlgoritmoGenetico;  // Declaracion adelantada
#endif
