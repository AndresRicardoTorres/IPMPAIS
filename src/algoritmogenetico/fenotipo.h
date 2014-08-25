/*
  Archivo: fenotipo.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  8 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


/**
  @class Fenotipo
  @brief Abstracción general del algoritmo genetico
  En cualquier algoritmo genético hay un algoritmo abstracto y unas funciones que dependen del problema concreto de que se trate.
  Estas funciones (como se crea y como se evalúa el Cromosoma) se agrupan en el Fenotipo.

  Relaciones con otras clases y objetos:
    - Es una clase abstracta. Hay que crear una clase derivada e implementar las funciones codificar y evaluar.
    .
*/

#ifndef FENOTIPO_H
#define FENOTIPO_H


#include "cromosoma.h"


class Fenotipo
{
  public:
    /** Constructor. No hace nada. En las clases derivadas debe recibir todos los datos que se necesiten para crear un Cromosoma.
    */
    Fenotipo();
    /** Destructor. No hace nada.
    */
    virtual ~Fenotipo();
    /** Función virtual pura. Debe implementarse en las clases derivadas.
      Crea un nuevo Cromosoma y cede su propiedad
      @return Cromosoma.
    */
    virtual Cromosoma *crearCromosoma() const = 0;
    /**
      Evalúa un cromosoma
      @return el valor de la aptitud de ese cromosoma.
    */
    virtual double evaluar(const Cromosoma *cromosoma) = 0;
    /**  Función virtual pura. Debe implementarse en las clases derivadas.
         Expresa un cromosoma
    */
    void expresar(const Cromosoma *cromosoma);
};


#else
class Fenotipo;  // Declaracion adelantada
#endif
