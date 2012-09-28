/*
  Archivo: admisionesunivalle.h
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


/**
  @class AdmisionesUnivalle
    donde admisionesUnivalle es un objeto de clase AdmisionesUnivalle, que
    tú debes escribir. A ese objeto yo le envío un array de doubles con
    los puntajesMinimos y otro con las ponderaciones. Tu usas esos arrays
    para ordenar los estudiantes de mayor a menor puntaje total. Y me
    retornas un vector ordenado de estudiantes, concretamente conteniendo
    los sha1 (que son strings de tipo const char*) del código del
    estudiante ordenados por orden de puntaje (primero los que aparecerían
    en ADMISIONES de UNIVALLE con mayor puntaje).
*/

#ifndef ADMISIONESUNIVALLE_H
#define ADMISIONESUNIVALLE_H

#include <vector>
#include <queue>
#include "EstudianteDAO.h"

#include <iostream>


class miComparador
{
public:
  miComparador(){}

  bool operator() (const std::pair<const char*,double>& lhs,const std::pair<const char*,double>& rhs) const
  {
    return lhs.second<rhs.second;
  }
};

typedef std::vector<const char*> VectorEstudiantes;
typedef std::vector<std::vector <const char*> > puntajesICFES;

class AdmisionesUnivalle
{
  public:
    AdmisionesUnivalle(const char* conn,int filtro_anno_inicio,int filtro_anno_final);
    ~AdmisionesUnivalle();
    const VectorEstudiantes *ordenarEstudiantesAdmisionesSegunPuntajesMinimosYPonderaciones(double puntajesMinimos[], double ponderaciones[]);
    private:
        std::string conexion;
        puntajesICFES *resultadosICFES;


};

#else
class AdmisionesUnivalle; // Declaración adelantada
#endif
