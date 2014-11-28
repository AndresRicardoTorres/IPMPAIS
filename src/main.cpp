/*
  Archivo: main.cpp
  Licencia: GNU-GPL
  Fecha creacion: 8 de marzo de 2012
  Fecha ultima modificacion:  27 de noviembre de 2014
  Version: 1.1.4
  Copyright: (C) 2012 by Angel Garcia Baños
  Email: angel.garcia@correounivalle.edu.co
  EVALAB (EISC - Universidad del Valle, Cali, Colombia)
*/

const char *version = "1.1.4";

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__


#include "ipmpais/puntajesminimos.h"
#include "gui/ventanaprincipal.h"

#include "test_fenotipoipmpais.h"
#include "test_algoritmogenetico.h"
#include "test_cromosoma.h"
#include "test_gen.h"

#include <string.h>



void uso(void)
{
  std::cout << "Uso: ipmpais [opcion]" << std::endl;
  std::cout << "  Opciones disponibles (sólo se puede especificar una):" << std::endl;
  std::cout << "   --version   -v   Muestra la versión del programa y termina " << std::endl;
  std::cout << "   --help      -h   Muestra esta ayuda y termina " << std::endl;
  std::cout << "   --test      -t   Hace el test de las clases que componen el algoritmo genético. Imprime los errores que encuentre y termina retornando el número de errores encontrados (normalmente, debería ser 0)" << std::endl;
  std::cout << "Si no se especifica ninguna opción, el programa se ejecuta normalmente en modo gráfico. Y allí dispone de un menú de ayuda adicional." << std::endl;
}

int test(void)
{
  int numeroDeErrores = 0;
  try
  {
    Test_Gen test_gen;
    if(test_gen.ejecutar())
      numeroDeErrores++;

    Test_Cromosoma test_cromosoma;
    if(test_cromosoma.ejecutar())
      numeroDeErrores++;

    Test_FenotipoIPMPAIS test_FenotipoIPMPAIS;
    if(test_FenotipoIPMPAIS.ejecutar())
      numeroDeErrores++;

    Test_AlgoritmoGenetico test_algoritmoGenetico;
    if(test_algoritmoGenetico.ejecutar())
      numeroDeErrores++;
  }
  catch(const char *mensaje)
  {
    std::cout << "Excepción: " << mensaje << std::endl;
  }
  return numeroDeErrores;
}

int main(int numArgs, char **args)
{
  switch(numArgs)
  {
  case 1:
    wxEntryStart(numArgs, args);
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();
    return 0;
  break;
  case 2:
    if(!strcmp(args[1], "--test") or !strcmp(args[1], "-t"))
    {
      return test();
    }
    else if(!strcmp(args[1], "--version") or !strcmp(args[1], "-v"))
    {
      std::cout << "ipmpais " << version << std::endl;
    }
    else
    {
      uso();
    }
  break;
  default:
    uso();
  }
  return 0;
}
