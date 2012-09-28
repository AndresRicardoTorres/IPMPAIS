/*
  Archivo: algoritmogenetico.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#include "algoritmogenetico.h"


AlgoritmoGenetico::AlgoritmoGenetico(Fenotipo *fenotipo, int cuantosCromosomas)
  : fenotipo(fenotipo), cuantosCromosomas(cuantosCromosomas)
{
  cromosomas = new Cromosoma*[cuantosCromosomas];
  for(int cualCromosoma = 0; cualCromosoma < cuantosCromosomas; cualCromosoma++)
  {
    cromosomas[cualCromosoma] = fenotipo->crearCromosoma();
  }
}


AlgoritmoGenetico::~AlgoritmoGenetico()
{
  for(int cualCromosoma = 0; cualCromosoma < cuantosCromosomas; cualCromosoma++)
  {
    delete cromosomas[cualCromosoma];
    cromosomas[cualCromosoma] = 0;
  }
  delete [] cromosomas;
  cromosomas = 0;
}


const Cromosoma *AlgoritmoGenetico::ejecutar(int numeroDeGeneraciones, int probabilidadDeCrucePromedio, int probabilidadDeCruceUniforme, double desviacionTipicaDeLaMutacion)
{
  while(numeroDeGeneraciones-- > 0)
  {
    int indiceUnCromosoma, indiceOtroCromosoma;

    seleccion(indiceUnCromosoma, indiceOtroCromosoma); // Retorna indiceUnCromosoma e indiceOtroCromosoma
    Cromosoma *hijo = reproduccion(cromosomas[indiceUnCromosoma], cromosomas[indiceOtroCromosoma], probabilidadDeCrucePromedio, probabilidadDeCruceUniforme, desviacionTipicaDeLaMutacion);
    sustitucion(hijo);
  }
  return elMejor();
}


void AlgoritmoGenetico::seleccion(int &indiceUnCromosoma, int &indiceOtroCromosoma) const
{
    // Seleccionar dos parejas de Cromosomas y hacer dos torneos para quedarse con dos Cromosomas (indiceUnCromosoma,indiceOtroCromosoma) por torneo, calculando (si es necesario) la aptitud de cada Cromosoma:
  Matematicas *matematicas = Matematicas::crear();
  int indiceCromosoma[4];
  for(int i = 0; i < 4; i++)
  {
    indiceCromosoma[i] = matematicas->randInt(cuantosCromosomas);
    if(not cromosomas[indiceCromosoma[i]]->yaEvaluado())
      cromosomas[indiceCromosoma[i]]->setAptitud(fenotipo->evaluar(cromosomas[indiceCromosoma[i]]));
  }

  indiceUnCromosoma = indiceCromosoma[0];
  if(cromosomas[indiceCromosoma[1]]->getAptitud() > cromosomas[indiceCromosoma[0]]->getAptitud())
    indiceUnCromosoma = indiceCromosoma[1];

  indiceOtroCromosoma = indiceCromosoma[2];
  if(cromosomas[indiceCromosoma[3]]->getAptitud() > cromosomas[indiceCromosoma[2]]->getAptitud())
    indiceOtroCromosoma = indiceCromosoma[3];
}


Cromosoma *AlgoritmoGenetico::reproduccion(const Cromosoma *unCromosoma, const Cromosoma *otroCromosoma, int probabilidadDeCrucePromedio, int probabilidadDeCruceUniforme, double desviacionTipicaDeLaMutacion) const
{
  // Reproducir con cierta probabilidad por CrucePromedio o por CruceUniforme y el hijo resultante se muta gaussianamente:
  Matematicas *matematicas = Matematicas::crear();
  Cromosoma *hijo = 0;
  if(matematicas->randInt(100) < probabilidadDeCrucePromedio + probabilidadDeCruceUniforme)
  {
    if(matematicas->randInt(100) < probabilidadDeCruceUniforme)
      hijo = unCromosoma->cruceUniforme(otroCromosoma);
    else
      hijo = unCromosoma->crucePromedio(otroCromosoma);
  }
  else if(unCromosoma->getAptitud() > otroCromosoma->getAptitud())
    hijo = unCromosoma->clone();
  else
    hijo = otroCromosoma->clone();

  hijo->mutacionGaussiana(desviacionTipicaDeLaMutacion);

  return hijo;
}


void AlgoritmoGenetico::sustitucion(Cromosoma *hijo)
{
  // Sustituir por un Cromosoma no evaluado o, si todos están evaluados, por uno al azar:
  Matematicas *matematicas = Matematicas::crear();
  bool sustituido = false;
  for(int cualCromosoma = 0; cualCromosoma < cuantosCromosomas; cualCromosoma++)
  {
    if(not cromosomas[cualCromosoma]->yaEvaluado())
    {
      delete cromosomas[cualCromosoma];
      cromosomas[cualCromosoma] = hijo;
      sustituido = true;
      break;
    }
  }
  if(not sustituido)
  {
    int indiceAlAzar = matematicas->randInt(cuantosCromosomas);
    delete cromosomas[indiceAlAzar];
    cromosomas[indiceAlAzar] = hijo;
  }
}


const Cromosoma *AlgoritmoGenetico::elMejor() const
{
// Buscar el mejor Cromosoma:
  double aptitudMayor = 0;
  bool hayAptitudMayor = false;
  int indiceCromosomaMejor = 0;
  for(int cualCromosoma = 0; cualCromosoma < cuantosCromosomas; cualCromosoma++)
  {
    if(not hayAptitudMayor)
    {
      if(cromosomas[cualCromosoma]->yaEvaluado())
      {
        aptitudMayor = cromosomas[cualCromosoma]->getAptitud();
        indiceCromosomaMejor = cualCromosoma;
        hayAptitudMayor = true;
      }
    }
    else if(cromosomas[cualCromosoma]->yaEvaluado() and aptitudMayor < cromosomas[cualCromosoma]->getAptitud())
      aptitudMayor = cromosomas[indiceCromosomaMejor = cualCromosoma]->getAptitud();
  }

  if(not hayAptitudMayor)
    throw "No se encontró ninguna solución";

  return cromosomas[indiceCromosomaMejor];
}


Cromosoma *AlgoritmoGenetico::operator [](int indice)
{
  return cromosomas[indice];
}


