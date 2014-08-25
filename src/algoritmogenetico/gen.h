/*
  Archivo: gen.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  8 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/

/**
  @class Gen
  @brief Es un gen de un algoritmo evolutivo.
  Es un gen de un algoritmo evolutivo.
  El gen tiene un valor flotante (double) que puede mutar dentro de un valor mínimo y uno máximo.
  La mutación se logra sumando ruido gaussiano con una desviacionTipica especificada en el constructor.
  El Gen tiene las siguientes funciones evolutivas:
    - clonar(): saca una copia profunda del Gen, cediendo propiedad.
      La función clonar es muy útil porque así se puede evitar una fábrica de genes. Internamente
      sólo hace return new Gen(*this); pero con ello oculta la clase (Gen) dentro de la función. De
      este modo, se logra polimorfismo en la creación de objetos.
    - mutar(): suma ruido gaussiano al valor dentro del intervalo válido y caracterizado por una desviacionTipica dada.
    .

  Relaciones con otras clases y objetos:
    - Ninguna.
    .
*/

#ifndef GEN_H
#define GEN_H


#include "matematicas.h"


class Gen
{
  public:
    /** Constructor.
        Construye un gen con un intervalo de valores double válidos valorMinimo y valorMaximo.
        Asigna al gen un valor al azar en ese intervalo.
        @param valorMinimo Por defecto, 0.
        @param valorMaximo Por defecto, 1.
    */
    Gen(double valorMinimo=0, double valorMaximo=100);
    /** Constructor de copia.
        Construye un gen a partir de otro.
        @param otroGen
    */
    Gen(const Gen &otroGen);
    /** Destructor.
    */
    ~Gen();
    /**
        @return el valor del Gen.
    */
    double valor() const;
    /** Produce una mutación, es decir un cambio al azar en el valor del intervalo.
        El cambio se logra eligiendo al azar otro valor dentro del intervalo (con distribución de
        probabilidad uniforme).
    */
    void mutacionUniforme();
    /** Produce una mutación, es decir un cambio al azar en el valor del intervalo.
        El cambio se logra sumando a ese valor un ruido gaussiano, de desviacionTipica dada.
        @param desviacionTipicaDeLaMutacion Por defecto, 1.
    */
    void mutacionGaussiana(double desviacionTipicaDeLaMutacion=1);
    /** Produce un cruce uniforme con otroGen.
        El cruce consiste en elegir al azar uno cualquiera de los genes y retornarlo, sacando una copia profunda y
        cediendo propiedad.
        @param otroGen
        @return el gen hijo.
    */
    Gen *cruceUniforme(const Gen *otroGen) const;
    /** Produce un cruce promedio con otroGen.
        El cruce consiste en una combinación lineal entre los valores de los genes padre y retornarlo, sacando
        una copia profunda y cediendo propiedad.
        @param otroGen
        @return el gen hijo.
    */
    Gen *crucePromedio(const Gen *otroGen) const;
    /** Retorna una copia profunda, cediendo propiedad. La copia tiene todos los atributos internos idéntica al Gen original.
        @return el gen hijo, cediendo propiedad.
    */
    Gen *clonar() const;

  private:
    double valorActual;
    double valorMinimo;
    double valorMaximo;
};

#else
class Gen;  // Declaracion adelantada
#endif
