/*
  Archivo: fenotipoipmpais.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#include "fenotipoipmpais.h"


FenotipoIPMPAIS::FenotipoIPMPAIS(int cuantosComponentesExamenIngreso, double puntajeMinimo_minimo, double puntajeMinimo_maximo, double ponderacion_minimo, double ponderacion_maximo, AdmisionesUnivalle &admisionesUnivalle, const char *listaEgresadosOrdenada[], int cuantosEgresados)
  : Fenotipo(), cuantosComponentesExamenIngreso(cuantosComponentesExamenIngreso),
    puntajeMinimo_minimo(puntajeMinimo_minimo), puntajeMinimo_maximo(puntajeMinimo_maximo),
    ponderacion_minimo(ponderacion_minimo), ponderacion_maximo(ponderacion_maximo),
    admisionesUnivalle(admisionesUnivalle)
{
  for(int posicion = 0; posicion < cuantosEgresados; posicion++)
    puntajesEgresados[listaEgresadosOrdenada[posicion]] = posicion;
}


FenotipoIPMPAIS::~FenotipoIPMPAIS()
{
}


Cromosoma *FenotipoIPMPAIS::crearCromosoma() const
{
  Cromosoma *cromosoma = new Cromosoma(2*cuantosComponentesExamenIngreso);
  for(int cualComponenteExamenIngreso = 0; cualComponenteExamenIngreso < cuantosComponentesExamenIngreso; cualComponenteExamenIngreso++)
  {
    cromosoma->appendGen(new Gen(puntajeMinimo_minimo, puntajeMinimo_maximo));
    cromosoma->appendGen(new Gen(ponderacion_minimo, ponderacion_maximo));
  }
  return cromosoma;
}


#include <iostream>
double FenotipoIPMPAIS::evaluar(const Cromosoma *cromosoma)
{
  double puntajesMinimos[cuantosComponentesExamenIngreso];
  double ponderaciones[cuantosComponentesExamenIngreso];
  for(int cualGen = 0; cualGen < cuantosComponentesExamenIngreso; cualGen++)
  {
    puntajesMinimos[cualGen] = (*cromosoma)[2*cualGen]->valor();
    ponderaciones[cualGen] = (*cromosoma)[2*cualGen+1]->valor();
  }
  const VectorEstudiantes *estudiantesOrdenados = admisionesUnivalle.ordenarEstudiantesAdmisionesSegunPuntajesMinimosYPonderaciones(puntajesMinimos, ponderaciones);

  int distancia = 0;
  for(unsigned int posicion = 0; posicion < estudiantesOrdenados->size(); posicion++)
  {
    int aux = puntajesEgresados[(*estudiantesOrdenados)[posicion]] - posicion;
    distancia += aux * aux;
  }
  delete estudiantesOrdenados;
  return -distancia;
}


void FenotipoIPMPAIS::expresar(const Cromosoma *cromosoma, double puntajesMinimos[], double ponderaciones[])
{
  for(int cualComponente = 0; cualComponente < cuantosComponentesExamenIngreso; cualComponente++)
  {
    puntajesMinimos[cualComponente] = (*cromosoma)[2*cualComponente]->valor();
    ponderaciones[cualComponente] = (*cromosoma)[2*cualComponente+1]->valor();
  }
}



