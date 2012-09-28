/*
  Archivo: test_algoritmogenetico.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#include "test_algoritmogenetico.h"


Test_AlgoritmoGenetico::Test_AlgoritmoGenetico()
{
}


Test_AlgoritmoGenetico::~Test_AlgoritmoGenetico()
{
}


bool Test_AlgoritmoGenetico::ejecutar(int veces)
{
  bool hayErrores = false;
  Matematicas *matematicas = Matematicas::crear();

  // Test de selección
  for(int j = 0; j < veces; j++)
  {
    AdmisionesUnivalle admisionesUnivalle;
    const char *listaEgresadosOrdenada[] = { "B", "A", "C", "D", "E" };
    int cuantosEgresados = 5;
    FenotipoIPMPAIS fenotipo(2, 200, 300, 0, 100, admisionesUnivalle, listaEgresadosOrdenada, cuantosEgresados);
    int numeroDeCromosomas = 100;
    int numeroDeCromosomasConAptitudAlta = matematicas->randInt(numeroDeCromosomas, false, false);
    Wrapp_AlgoritmoGenetico algoritmoGenetico(&fenotipo, numeroDeCromosomas);
    for(int a=0; a<numeroDeCromosomasConAptitudAlta; a++)
      algoritmoGenetico[a]->setAptitud(1);  // Aptitud alta
    for(int a=numeroDeCromosomasConAptitudAlta; a<numeroDeCromosomas; a++)
      algoritmoGenetico[a]->setAptitud(0);  // Aptitud baja
    int uno, otro;
    int cuentaAptitudes[2] = {0, 0};
    for(int i=0; i<veces; i++)
    {
      algoritmoGenetico.seleccion(uno, otro);
      cuentaAptitudes[int(algoritmoGenetico[uno]->getAptitud())]++;    // Incrementa aptitud alta o baja
      cuentaAptitudes[int(algoritmoGenetico[otro]->getAptitud())]++;   // Incrementa aptitud alta o baja
    }
    if(cuentaAptitudes[1] < numeroDeCromosomasConAptitudAlta)
    {  std::cout << "Error1 en AlgoritmoGenetico";  hayErrores = true; }

    // Test de reproducción:
    int numeroGenes = 10;
    Cromosoma unCromosoma(numeroGenes), otroCromosoma(numeroGenes);
    for(int k=0; k<numeroGenes; k++)
    {
      unCromosoma.appendGen(new Gen(k*100,k*100+50));
      otroCromosoma.appendGen(new Gen(k*100,k*100+50));
    }
    unCromosoma.setAptitud(1);
    otroCromosoma.setAptitud(2);
    Cromosoma *hijo1 = algoritmoGenetico.reproduccion(&unCromosoma, &otroCromosoma, 100, 0, 1);
    int fallos = 0;
    for(int k=0; k<numeroGenes; k++)
      if(not matematicas->iguales((*hijo1)[k]->valor(), (unCromosoma[k]->valor()+otroCromosoma[k]->valor())/2))
        fallos++;
    if(fallos != 1)  // Debe haber un sólo fallo, debido a la mutación
    {  std::cout << "Error2 en AlgoritmoGenetico";  hayErrores = true; }
    if(hijo1->yaEvaluado())
    {  std::cout << "Error3 en AlgoritmoGenetico";  hayErrores = true; }

    Cromosoma *hijo2 = algoritmoGenetico.reproduccion(&unCromosoma, &otroCromosoma, 0, 100, 1);
    fallos = 0;
    for(int k=0; k<numeroGenes; k++)
      if(not (matematicas->iguales((*hijo2)[k]->valor(), unCromosoma[k]->valor()) or matematicas->iguales((*hijo2)[k]->valor(), otroCromosoma[k]->valor())))
        fallos++;
    if(fallos != 1)  // Debe haber un sólo fallo, debido a la mutación
    {  std::cout << "Error4 en AlgoritmoGenetico";  hayErrores = true; }

    // Sustitución:
    for(int k=0; k < numeroDeCromosomas; k++)
      algoritmoGenetico[k]->setAptitud(k);
    hijo1->setAptitud(-1);
    algoritmoGenetico.sustitucion(hijo1);
    int encontrado = 0;
    for(int k=0; k < numeroDeCromosomas; k++)
      if(matematicas->iguales(algoritmoGenetico[k]->getAptitud(), -1))
        encontrado++;
    if(encontrado != 1)
    {  std::cout << "Error5 en AlgoritmoGenetico";  hayErrores = true; }
    // Sustitución:
    int r = matematicas->randInt(numeroDeCromosomas);
    algoritmoGenetico[r]->mutacionGaussiana(1);  // Elimina la aptitud
    hijo2->setAptitud(-2);
    algoritmoGenetico.sustitucion(hijo2);
    if(not matematicas->iguales(algoritmoGenetico[r]->getAptitud(), -2))
    {  std::cout << "Error6 en AlgoritmoGenetico";  hayErrores = true; }

    // El mejor:
    for(int k=0; k < numeroDeCromosomas; k++)
      algoritmoGenetico[k]->setAptitud(k);
    for(int k=0; k < numeroDeCromosomas; k++)
    {
      int r1 = matematicas->randInt(numeroDeCromosomas);
      int r2 = matematicas->randInt(numeroDeCromosomas);
      double aux = algoritmoGenetico[r1]->getAptitud();
      algoritmoGenetico[r1]->setAptitud(algoritmoGenetico[r2]->getAptitud());
      algoritmoGenetico[r2]->setAptitud(aux);
    }
    if(not matematicas->iguales(algoritmoGenetico.elMejor()->getAptitud(), numeroDeCromosomas-1))
    {  std::cout << "Error7 en AlgoritmoGenetico";  hayErrores = true; }
  }

  return hayErrores;
}

