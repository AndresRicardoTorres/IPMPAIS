/*
  Archivo: admisionesunivalle.h
  Licencia: GNU-GPL
  Fecha creacion: 21 de octubre de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.2
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


/**
  @class AdmisionesUnivalle
  @brief Logica del ordenamiento de candidatos para la admision en Univalle.
*/

#ifndef ADMISIONESUNIVALLE_H
#define ADMISIONESUNIVALLE_H

#include <cstdio>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "ipmpais/estudiantedao.h"
/**
 * @brief Ordena pares compuestos por código y puntaje, por el código de
 * estudiante
 */
class OrdenarParesPorCodigo
{
public:
  OrdenarParesPorCodigo(){}

 bool operator() ( const std::pair<const char*,double>& lhs
                 , const std::pair<const char*,double>& rhs) const
  {
    return lhs.second<rhs.second;
  }
};

/**
 * @brief Ordena pares compuestos por posición y puntaje, por posición
 */
class OrdenarPorPosicion
{
public:
  OrdenarPorPosicion(){}

  bool operator() ( const std::pair<unsigned int,double>& lhs
                  , const std::pair<unsigned int,double>& rhs) const
  {
    return lhs.second < rhs.second;
 }};


typedef std::vector<const char*> VectorEstudiantes;
typedef std::vector<std::vector <const char*> > puntajesICFES;

class AdmisionesUnivalle
{
  public:
    /** Se construye el objeto admisionesUnivalle con una la información
     * para conectarse a la base de datos y los filtros para tener en
     * cuenta solo los estudiantes en los años de interses.
     *
     * @param conexion String de conexion para la base de datos
     * @param filtro_anno_inicio Filtro con el año inicial a tomar en
     * cuenta para el analisis, por ejemplo 2000
     * @param filtro_anno_final  Filtro con el año final a tomar en cuenta
     * para el analisis, por ejemplo 2010
     */
    AdmisionesUnivalle( const char* conexion
                      , int filtro_anno_inicio
                      , int filtro_anno_final
		      );
	AdmisionesUnivalle(){};
    ~AdmisionesUnivalle();

    /**
     * A esta clase se le envia un array de doubles con los puntajes minimos
     * y otro con las ponderaciones. Se usan esos arrays para ordenar los
     * estudiantes de mayor a menor puntaje total. Y se retorna un vector
     * ordenado de estudiantes ordenados por orden de puntaje (primero los que
     * aparecerían en ADMISIONES de UNIVALLE con mayor puntaje) conteniendo el
     * código del estudiante.
     *
     * @param puntajesMinimos Los puntajes minimos a tener en cuenta para el
     * ordenamiento
     * @param ponderaciones Las ponderaciones de cada elemento del ICFES a
     * tener en cuenta para el ordenamiento
     */
    const VectorEstudiantes *ordenarEstudiantesAdmisionesSegunPuntajesMinimosYPonderaciones(double puntajesMinimos[], double ponderaciones[]);
    private:
        puntajesICFES *resultadosICFES;
};

#else
class AdmisionesUnivalle; // Declaración adelantada
#endif
