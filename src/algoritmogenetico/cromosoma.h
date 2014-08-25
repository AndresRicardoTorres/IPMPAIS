/*
  Archivo: cromosoma.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  8 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


/**
  @class Cromosoma
  @brief Representación con un array lineal de genes.

  El cromosoma consiste en un array lineal de genes y cada gen es un número flotante de doble precisión.
  Se usará en un algoritmo genético. Se le puede pedir mutar() y cruzar() con
  otro Cromosoma. Tiene una Aptitud que se puede escribir como resultado de una evaluación; y también
  leer. Se puede acceder a cada gen individualmente con operator [].

  Relaciones con otras clases y objetos:
    - Contiene un array lineal de objetos Gen.
    .
*/

#ifndef CROMOSOMA_H
#define CROMOSOMA_H

#include "matematicas.h"
#include "gen.h"


class Cromosoma
{
  public:
    /** Constructor.
        Construye un Cromosoma vacío, que podrá albergar cuantosGenes.
        @param cuantosGenes
    */
    Cromosoma(int cuantosGenes);
    /** Añade un Gen al final del Cromosoma, tomando propiedad de ello
      @param gen
    */
    void appendGen(Gen *gen);
    /** Destructor.
    */
    ~Cromosoma();
    /** Muta el Cromosoma. La mutación es gaussiana.
        Para ello, elige al azar uno de sus Genes y le suma ruido gaussiano.
        @param desviacionTipicaDeLaMutacion
    */
    void mutacionGaussiana(double desviacionTipicaDeLaMutacion);
    /** Se cruza con otroCromosoma. El cruce es de tipo uniforme, eligiendo al azar entre cada par de genes homólogos.
        @param otroCromosoma
        @return el hijo que salió del cruce, cediendo su propiedad.
    */
    Cromosoma *cruceUniforme(const Cromosoma *otroCromosoma) const;
    /** Se cruza con otroCromosoma. El cruce es de tipo promedio, promediando los valores de cada par de genes homólogos.
        @param otroCromosoma
        @return el hijo que salió del cruce, cediendo su propiedad.
    */
    Cromosoma *crucePromedio(const Cromosoma *otroCromosoma) const;
    /** Saca una copia profunda del Cromosoma, cediendo propiedad.
        @return la copia, cediendo su propiedad.
    */
    Cromosoma *clone() const;
    /** Asigna la Aptitud que se merece este Cromosoma.
        @param valor
    */
    void setAptitud(double valor);
    /** Averigua la Aptitud de este Cromosoma.
        @return la Aptitud del Cromosoma.
    */
    double getAptitud() const;
    /** Verifica si el Cromosoma ya fue evaluado.
      @return true si ya fue evaluado y tiene calculada su aptitud; y false en caso contrario
    */
    bool yaEvaluado() const;
    /** Retorna el Gen que está en la posición indice.
        @param indice
        @return el gen que está en la posición indice.
    */
    Gen *operator [] (int indice) const;
    /** Mira a ver si es menor que otro Cromosoma. Para ello, compara las respectivas Aptitudes.
        Hay que entender que, de esta manera, dos cromosomas son iguales si tienen la misma Aptitud.
        @return true si la propia Aptitud es menor que la de otroCromosoma; y false en caso contrario.
    */
    bool operator < (const Cromosoma &otroCromosoma) const;

  private:
    double aptitud;
    bool aptitudValida;
    int cuantosGenes;
    int cuantosGenesVacios;
    Gen **genes;
};

#else
class Cromosoma;  // Declaracion adelantada
#endif
