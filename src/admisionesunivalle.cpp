/***************************************************************
 * Name:      adminsionesunivalle.cpp
 * Purpose:   Code for Application Frame
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com) y Angel García Baños (angel.garcia@correounivalle.edu.co)
 * Created:   2012-03-23
 * Copyright: Andrés Ricardo Torres Martínez y Angel García Baños ()
 * License: GPL
 * Fecha ultima modificacion:  10 de marzo de 2012
 **************************************************************/

#include "admisionesunivalle.h"

AdmisionesUnivalle::AdmisionesUnivalle(bool ECAESoRegistro,const char* conn,int filtro_anno_inicio,int filtro_anno_final,std::string listadoAsignaturas)
{
    unsigned int limite = 0;
  EstudianteDAO *objEstudiantes = new EstudianteDAO(conn);
  if(ECAESoRegistro)
  {
      limite=10;
    resultadosICFES = objEstudiantes->getPuntajesECAES(filtro_anno_inicio,filtro_anno_final,listadoAsignaturas);
  }else{
      limite=7;
    resultadosICFES = objEstudiantes->getPuntajesICFES(filtro_anno_inicio,filtro_anno_final,listadoAsignaturas);
  }

  delete objEstudiantes;

// 2012-10-21: Modificado por Angel
  std::vector<std::pair<unsigned int,double> > vectorTemporal;  // indiceEnResultadosICFES, puntajeDeUnaComponenteICFES
  setlocale(LC_ALL,"C"); ///Para el separador decimal

  for(unsigned int j=0;j<limite;j++)
  {
    for(unsigned int i=0; i<resultadosICFES->size(); i++)
    {
      std::pair<unsigned int,double> unPar(i, atof(resultadosICFES->at(i).at(j+1)));
      vectorTemporal.push_back(unPar);
    }
    std::priority_queue<std::pair<unsigned int,double>,std::vector<std::pair<unsigned int,double> >,miComparador2> miColaDePrioridad(vectorTemporal.begin(),vectorTemporal.end(),miComparador2());
    for(unsigned int i=0; i<resultadosICFES->size(); i++)
    {
      unsigned int indiceOrdenado = (miColaDePrioridad.top()).first;
      miColaDePrioridad.pop();
//      char *tmp = new char[11];  // Un entero sin signo tiene como máximo 10 cifras, más el terminador.
      char *tmp = new char[int(1+ceil(log10f(sizeof(unsigned int))))];  // Un entero sin signo tiene como máximo 10 cifras, más el terminador.
      sprintf(tmp, "%u", (resultadosICFES->size()-i));
      resultadosICFES->at(indiceOrdenado).at(j+1) = tmp;
    }
  }
}


// 2012-10-21: Modificado por Angel
AdmisionesUnivalle::~AdmisionesUnivalle()
{
// Esto debería funcionar, pero sin embargo produce la muerte del programa
/*
  for(unsigned int j=0;j<7;j++)
  {
    for(unsigned int i=0; i<resultadosICFES->size(); i++)
    {
      delete [] resultadosICFES->at(i).at(j+1);
    }
  }
*/
}


const VectorEstudiantes* AdmisionesUnivalle::ordenarEstudiantesAdmisionesSegunPuntajesMinimosYPonderaciones(double puntajesMinimos[], double ponderaciones[])
{
    VectorEstudiantes *vectorResultado = new VectorEstudiantes;
    std::vector<std::pair<const char*,double> > vectorTemporal;
    setlocale(LC_ALL,"C"); ///Para el separador decimal
    /*
for(unsigned int j=0;j<7;j++)
{
    std::cout<<j<<" - "<<ponderaciones[j]<<std::endl;
}
std::cout<<std::endl;
*/

    for(unsigned int i=0;i<resultadosICFES->size();i++)
    {
        //bool inserto = true;
        double puntajeTotal = 0;
        for(unsigned int j=0;j<7;j++)
        {
            puntajeTotal+= ponderaciones[j] * atof(resultadosICFES->at(i).at(j+1));
        }
        std::pair<const char*,double> unPar(resultadosICFES->at(i).at(0) , puntajeTotal);
        vectorTemporal.push_back(unPar);
    }

    std::priority_queue<std::pair<const char*,double>,std::vector<std::pair<const char*,double> >,miComparador> miColaDePrioridad(vectorTemporal.begin(),vectorTemporal.end(),miComparador());



//std::cout<<"RESULTADOS"<<std::endl;
    for(unsigned int i=0;i<vectorTemporal.size();i++)
    {
        /*
        if(i<10)
        {
            std::cout<<i<<" - "<<miColaDePrioridad.top().first<<" "<<miColaDePrioridad.top().second<<std::endl;
        }
        */
        vectorResultado->push_back((miColaDePrioridad.top()).first);
        miColaDePrioridad.pop();
    }

    return vectorResultado;
}

