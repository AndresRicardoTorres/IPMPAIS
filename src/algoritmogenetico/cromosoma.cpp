/*
  Archivo: cromosoma.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#include "cromosoma.h"


Cromosoma::Cromosoma(int cuantosGenes)
  : aptitud(0), aptitudValida(false), cuantosGenes(cuantosGenes), cuantosGenesVacios(cuantosGenes)
{
  genes = new Gen*[cuantosGenes];
}


Cromosoma::~Cromosoma()
{
  for(int cualGen = 0; cualGen < cuantosGenes - cuantosGenesVacios; cualGen++)
  {
    delete genes[cualGen];
    genes[cualGen] = 0;
  }
  delete [] genes;
  genes = 0;
}


void Cromosoma::appendGen(Gen *gen)
{
  if(cuantosGenesVacios <= 0)
    throw "No caben tantos genes";
  genes[cuantosGenes - cuantosGenesVacios--] = gen; // Toma propiedad
}


void Cromosoma::mutacionGaussiana(double desviacionTipicaDeLaMutacion)
{
  Matematicas *matematicas = Matematicas::crear();
  int indiceGenAMutar = matematicas->randInt(cuantosGenes - cuantosGenesVacios);
  genes[indiceGenAMutar]->mutacionGaussiana(desviacionTipicaDeLaMutacion);
  aptitudValida = false;
}


Cromosoma *Cromosoma::cruceUniforme(const Cromosoma *otroCromosoma) const
{
  Cromosoma *hijo = new Cromosoma(cuantosGenes);
  for(int cualGen = 0; cualGen < cuantosGenes - cuantosGenesVacios; cualGen++)
    hijo->appendGen(genes[cualGen]->cruceUniforme((*otroCromosoma)[cualGen]));
  return hijo;
}


Cromosoma *Cromosoma::crucePromedio(const Cromosoma *otroCromosoma) const
{
  Cromosoma *hijo = new Cromosoma(cuantosGenes);
  for(int cualGen = 0; cualGen < cuantosGenes - cuantosGenesVacios; cualGen++)
    hijo->appendGen(genes[cualGen]->crucePromedio((*otroCromosoma)[cualGen]));
  return hijo;
}


Cromosoma *Cromosoma::clone() const
{
  Cromosoma *hijo = new Cromosoma(cuantosGenes);
  for(int cualGen = 0; cualGen < cuantosGenes - cuantosGenesVacios; cualGen++)
    hijo->appendGen(genes[cualGen]->clonar());
  hijo->aptitud = aptitud;
  hijo->aptitudValida = aptitudValida;
  return hijo;
}


void Cromosoma::setAptitud(double valor)
{
  aptitud = valor;
  aptitudValida = true;
}


double Cromosoma::getAptitud() const
{
  if(not aptitudValida or cuantosGenesVacios != 0)
    throw "Aptitud invalida en Cromosoma";
  return aptitud;
}


bool Cromosoma::yaEvaluado() const
{
  return aptitudValida;
}


Gen *Cromosoma::operator [] (int indice) const
{
  if(indice < 0 or indice >= cuantosGenes - cuantosGenesVacios)
    throw "Indice fuera de rango en Cromosoma::operator []";
  return genes[indice];
}


bool Cromosoma::operator < (const Cromosoma &otroCromosoma) const
{
  return (*this).getAptitud() < otroCromosoma.getAptitud();
}


