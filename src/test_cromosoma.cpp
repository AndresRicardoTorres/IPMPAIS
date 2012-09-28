/*
  Archivo: test_cromosoma.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  10 de marzo de 2012
  Version: 0.1
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/


#include "test_cromosoma.h"


Test_Cromosoma::Test_Cromosoma()
{
}


Test_Cromosoma::~Test_Cromosoma()
{
}


bool Test_Cromosoma::ejecutar(int veces)
{
  bool hayErrores = false;
  Matematicas *matematicas = Matematicas::crear();
  bool tipoDeCruce[4] = {false,false,false,false}; // Si los padres son PM los hijos pueden salir PP, PM, MP o MM. Aquí se guarda {true, false}  si salió alguno de estos 4 tipos.

  while(veces--)
  {
    Cromosoma unCromosoma(2);
    unCromosoma.appendGen(new Gen(0,1000));
    unCromosoma.appendGen(new Gen(2000,3000));
    double rand1 = matematicas->randDouble(0,5);
    unCromosoma.setAptitud(rand1);
    if(unCromosoma.getAptitud() != rand1)
    {  std::cout << "Error3 en Cromosoma";  hayErrores = true; }
    double valor0 = unCromosoma[0]->valor();
    double valor1 = unCromosoma[1]->valor();
    if(valor0 < 0 or valor0 > 1000)
    {  std::cout << "Error1 en Cromosoma";  hayErrores = true; }
    if(valor1 < 2000 or valor1 > 3000)
    {  std::cout << "Error2 en Cromosoma";  hayErrores = true; }
    unCromosoma.mutacionGaussiana(1); // Es prácticamente imposible que la mutación salga 0.000000000000000000
    if(not((unCromosoma[0]->valor() == valor0) xor (unCromosoma[1]->valor() == valor1)))
    {  std::cout << "Error4 en Cromosoma";  hayErrores = true; }
    Cromosoma *c = unCromosoma.clone();
    if(((*c)[0]->valor() != unCromosoma[0]->valor()) or ((*c)[1]->valor() != unCromosoma[1]->valor()))
    {  std::cout << "Error5 en Cromosoma";  hayErrores = true; }
    c->mutacionGaussiana(1);
    if(not(((*c)[0]->valor() == unCromosoma[0]->valor()) xor ((*c)[1]->valor() == unCromosoma[1]->valor())))
    {  std::cout << "Error6 en Cromosoma";  hayErrores = true; }
    delete c;
    c=0;
    unCromosoma.setAptitud(rand1);

    Cromosoma otroCromosoma(2);
    otroCromosoma.appendGen(new Gen(4000,5000));
    otroCromosoma.appendGen(new Gen(6000,7000));
    double rand2 = matematicas->randDouble(6,8);
    otroCromosoma.setAptitud(rand2);
    if(otroCromosoma < unCromosoma)
    {  std::cout << "Error7 en Cromosoma";  hayErrores = true; }
    Cromosoma *unHijo = unCromosoma.crucePromedio(&otroCromosoma);
    if(not matematicas->iguales((*unHijo)[0]->valor(), (unCromosoma[0]->valor()+otroCromosoma[0]->valor())/2.0))
    {  std::cout << "Error8 en Cromosoma";  hayErrores = true; }
    delete unHijo;
    unHijo = 0;
    Cromosoma *otroHijo = unCromosoma.cruceUniforme(&otroCromosoma);
    if((*otroHijo)[0]->valor() ==  unCromosoma[0]->valor() and (*otroHijo)[1]->valor() ==  unCromosoma[1]->valor())
      tipoDeCruce[0] = true;
    if((*otroHijo)[0]->valor() ==  unCromosoma[0]->valor() and (*otroHijo)[1]->valor() == otroCromosoma[1]->valor())
      tipoDeCruce[1] = true;
    if((*otroHijo)[0]->valor() == otroCromosoma[0]->valor() and (*otroHijo)[1]->valor() ==  unCromosoma[1]->valor())
      tipoDeCruce[2] = true;
    if((*otroHijo)[0]->valor() == otroCromosoma[0]->valor() and (*otroHijo)[1]->valor() == otroCromosoma[1]->valor())
      tipoDeCruce[3] = true;
    delete otroHijo;
    otroHijo = 0;
  }

  if(tipoDeCruce[0] == false or tipoDeCruce[1] == false or tipoDeCruce[2] == false or tipoDeCruce[3] == false)
  {  std::cout << "Error9 en Cromosoma";  hayErrores = true; }
  return hayErrores;
}

