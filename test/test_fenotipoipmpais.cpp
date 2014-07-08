/*
  Archivo: test_fenotipoipmpais.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#include "test_fenotipoipmpais.h"


Test_FenotipoIPMPAIS::Test_FenotipoIPMPAIS()
{
}


Test_FenotipoIPMPAIS::~Test_FenotipoIPMPAIS()
{
}


bool Test_FenotipoIPMPAIS::ejecutar(int veces)
{
  bool hayErrores = false;
//  Matematicas *matematicas = Matematicas::crear();

  while(veces--)
  {
    {
      AdmisionesUnivalle admisionesUnivalle;
      const char *listaEgresadosOrdenada[] = { "A", "B", "C", "D", "E" };
      int cuantosEgresados = 5;
      FenotipoIPMPAIS fenotipo(2, 200, 300, 0, 100, admisionesUnivalle, listaEgresadosOrdenada, cuantosEgresados);
      Cromosoma *cromosoma = fenotipo.crearCromosoma();
      if((*cromosoma)[0]->valor() < 200 or (*cromosoma)[0]->valor() > 300)
      {  std::cout << "Error1 en Test_FenotipoIPMPAIS";  hayErrores = true; }
      if((*cromosoma)[1]->valor() < 0 or (*cromosoma)[1]->valor() > 100)
      {  std::cout << "Error2 en Test_FenotipoIPMPAIS";  hayErrores = true; }
      double valor = fenotipo.evaluar(cromosoma);
      if(valor != 0)
      {  std::cout << "Error3 en Test_FenotipoIPMPAIS";  hayErrores = true; }
      delete cromosoma;
    }
  }
  {
    AdmisionesUnivalle admisionesUnivalle;
    const char *listaEgresadosOrdenada[] = { "B", "A", "C", "D", "E" };
    int cuantosEgresados = 5;
    FenotipoIPMPAIS fenotipo(2, 200, 300, 0, 100, admisionesUnivalle, listaEgresadosOrdenada, cuantosEgresados);
    Cromosoma *cromosoma = fenotipo.crearCromosoma();
    double valor = fenotipo.evaluar(cromosoma);
    if(valor != -(1+1))
    {  std::cout << "Error4 en Test_FenotipoIPMPAIS";  hayErrores = true; }
    delete cromosoma;
  }
  {
    AdmisionesUnivalle admisionesUnivalle;
    const char *listaEgresadosOrdenada[] = { "C", "B", "A", "D", "E" };
    int cuantosEgresados = 5;
    FenotipoIPMPAIS fenotipo(2, 200, 300, 0, 100, admisionesUnivalle, listaEgresadosOrdenada, cuantosEgresados);
    Cromosoma *cromosoma = fenotipo.crearCromosoma();
    double valor = fenotipo.evaluar(cromosoma);
    if(valor != -(4+4))
    {  std::cout << "Error5 en Test_FenotipoIPMPAIS";  hayErrores = true; }
    delete cromosoma;
  }
  {
    AdmisionesUnivalle admisionesUnivalle;
    const char *listaEgresadosOrdenada[] = { "E", "D", "C", "B", "A" };
    int cuantosEgresados = 5;
    FenotipoIPMPAIS fenotipo(2, 200, 300, 0, 100, admisionesUnivalle, listaEgresadosOrdenada, cuantosEgresados);
    Cromosoma *cromosoma = fenotipo.crearCromosoma();
    double valor = fenotipo.evaluar(cromosoma);
    if(valor != -(16+4+0+4+16))
    {  std::cout << "Error6 en Test_FenotipoIPMPAIS";  hayErrores = true; }
    delete cromosoma;
  }
  return hayErrores;
}

