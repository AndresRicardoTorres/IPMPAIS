/*
  Archivo: test_gen.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#include "test_gen.h"


Test_Gen::Test_Gen()
{
}


Test_Gen::~Test_Gen()
{
}


bool Test_Gen::ejecutar(int veces)
{
  bool hayErrores = false;
  Matematicas *matematicas = Matematicas::crear();

  while(veces--)
  {
    double valorMinimo;
    double valorMaximo;
    do
    {
      valorMinimo = matematicas->randDouble(0, 100000);
      valorMaximo = matematicas->randDouble(0, 100000);
    }
    while(valorMinimo > valorMaximo);

    Gen unGen(valorMinimo, valorMaximo);
    double v1 = unGen.valor();
    if(v1 < valorMinimo or v1 > valorMaximo or v1 != unGen.valor())
    {  std::cout << "Error1 en valor del Gen";  hayErrores = true; }
    unGen.mutacionUniforme();
    double v2 = unGen.valor();
    if(v2 < valorMinimo or v2 > valorMaximo or v2 != unGen.valor() or v2 == v1)
    {  std::cout << "Error2 en valor del Gen";  hayErrores = true; }
    unGen.mutacionGaussiana();
    double v3 = unGen.valor();
    if(v3 < valorMinimo or v3 > valorMaximo or v3 != unGen.valor() or v3 == v2)
    {  std::cout << "Error3 en valor del Gen";  hayErrores = true; }
    Gen otroGen(valorMinimo, valorMaximo);
    Gen *genHijoUniforme = unGen.cruceUniforme(&otroGen);
    if(genHijoUniforme->valor() != unGen.valor() and genHijoUniforme->valor() != otroGen.valor())
    {  std::cout << "Error4 en valor del Gen";  hayErrores = true; }
    double v4 = (unGen.valor() + otroGen.valor())/2;
    Gen *genHijoPromedio = unGen.crucePromedio(&otroGen);
    if(genHijoPromedio->valor() != v4)
    {  std::cout << "Error5 en valor del Gen";  hayErrores = true; }
  }
  return hayErrores;
}

