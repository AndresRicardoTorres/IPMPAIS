/*
  Archivo: fenotipoipmpais.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  28 de septiembre de 2012
  Version: 0.2
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


/**
  @class FenotipoIPMPAIS
  Crea y evalúa un Cromosoma para resolver el problema de IPMPAIS.

  Relaciones con otras clases y objetos:
    - Es un Fenotipo.
    .
*/


#ifndef FENOTIPOIPMPAIS_H
#define FENOTIPOIPMPAIS_H

#include "admisionesunivalle.h"
#include "algoritmogenetico/fenotipo.h"
#include <string.h>
#include <map>
#include <vector>

struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

typedef std::map<const char*, double, ltstr> HashEstudiantesYPuntajes;
typedef std::vector<const char*> VectorEstudiantes;



class FenotipoIPMPAIS : virtual public Fenotipo
{
  public:
    /** Constructor.
      @param cuantosComponentesExamenIngreso
      @param puntajeMinimo_minimo
      @param puntajeMinimo_maximo
      @param ponderacion_minimo
      @param ponderacion_maximo
      @param admisionesUnivalle. Este es el objeto que calcula la selección y ordenación de estudiantes que van a ingresar a Univalle en función de sus puntajes de ICFES.
      @param listaEgresadosOrdenada. Debe ir ordenada según los puntajes de egresado (ECAES, promedio de carrera, o algo similar) de mayor a menor.
      @param cuantosEgresados. La longitud de la lista anterior.
      @param soloCalcularPonderaciones. Si es false, calcula valores mínimos y ponderaciones. Si es true (por defecto), calcula sólo ponderaciones.
    */
    FenotipoIPMPAIS(int cuantosComponentesExamenIngreso, double puntajeMinimo_minimo, double puntajeMinimo_maximo, double ponderacion_minimo, double ponderacion_maximo, AdmisionesUnivalle &admisionesUnivalle, const char *listaEgresadosOrdenada[], int cuantosEgresados, bool soloCalcularPonderaciones=true);
    /** Destructor. No hace nada.
    */
    ~FenotipoIPMPAIS();
    /** Crea un nuevo Cromosoma y cede su propiedad. El Cromosoma va a tener dos doubles por cada componente del examen
      de ingreso a la universidad. El primero es el puntaje mínimo exigido en ese componente. El segundo es la ponderación
      del puntaje que el estudiante obtuvo en ese componente.
      @return Cromosoma.
    */
    Cromosoma *crearCromosoma() const;
    /** Evalúa un cromosoma. Para ello compara los puestos sacados por cada estudiante en el examen de ingreso con los puestos
      que obtuvo en el examen de egreso. Sin son iguales, la aptitud es alta. Si son muy distintos, la aptitud es baja.
      Para ello, para cada estudiante se calcula la resta al cuadrado de su puntaje de ingreso menos su puntaje de egreso. Y
      se suman los resultados de todos los estudiantes. Se cambia el signo. De este modo, todas las aptitudes van a ser
      números negativos: las más altas son números negativos cercanos a cero, y las más bajas son números negativos grandes.
      @return el valor de la aptitud de ese cromosoma.
    */
    double evaluar(const Cromosoma *cromosoma);
    /** Expresa un Cromosoma. OJO: esta función no es ni puede ser virtual. No se puede usar sobre la clase base. Esta es la gran limitación en el polimorfismo de C++ (las funciones de clase base y derivadas deben tener la misma firma)
      @param puntero a Cromosoma
      @param retorna un array de puntajesMinimos
      @param retorna un array de pondereaciones
    */
    void expresar(const Cromosoma *cromosoma, double puntajesMinimos[], double ponderaciones[]);

  private:
    int cuantosComponentesExamenIngreso;
    double puntajeMinimo_minimo;
    double puntajeMinimo_maximo;
    double ponderacion_minimo;
    double ponderacion_maximo;
    HashEstudiantesYPuntajes puntajesEgresados;
    AdmisionesUnivalle &admisionesUnivalle;
    bool soloCalcularPonderaciones;
};



#else
class FenotipoIPMPAIS;  // Declaracion adelantada
#endif

