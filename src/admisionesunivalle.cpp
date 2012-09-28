/***************************************************************
 * Name:      adminsionesunivalle.cpp
 * Purpose:   Code for Application Frame
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-03-23
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

#include "admisionesunivalle.h"

AdmisionesUnivalle::AdmisionesUnivalle(const char* conn,int filtro_anno_inicio,int filtro_anno_final){
    EstudianteDAO *objEstudiantes = new EstudianteDAO(conn);
    resultadosICFES = objEstudiantes->getPuntajesICFES(filtro_anno_inicio,filtro_anno_final);
    delete objEstudiantes;
}

AdmisionesUnivalle::~AdmisionesUnivalle(){

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

