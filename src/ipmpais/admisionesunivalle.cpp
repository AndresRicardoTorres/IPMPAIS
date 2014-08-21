/***************************************************************
 * Name:      adminsionesunivalle.cpp
 * Purpose:   Code for Application Frame
 * Author:    Andrés Ricardo Torres Martínez
 * (ricardo.torres@correounivalle.edu.co) y Angel García Baños
 * (angel.garcia@correounivalle.edu.co)
 * Created:   2012-03-23
 * Copyright: Andrés Ricardo Torres Martínez y Angel García Baños
 * License: GPL
 * Fecha ultima modificacion:  10 de marzo de 2012
 **************************************************************/

#include "admisionesunivalle.h"

AdmisionesUnivalle::AdmisionesUnivalle(const char* conexion,int filtro_anno_inicio,int filtro_anno_final)
{
    // <!-- Cantidad de asignaturas del ICFES -->
    unsigned int limite = 7;

    EstudianteDAO *objEstudiantes = new EstudianteDAO(conexion);
    resultadosICFES = objEstudiantes->getPuntajesICFES( filtro_anno_inicio
                                                      , filtro_anno_final
						      );
    delete objEstudiantes;

    std::vector<std::pair<unsigned int,double> > vectorTemporal;

    // <!-- Para el separador decimal -->
    setlocale(LC_ALL,"C");

    for(unsigned int j=0;j<limite;j++)
    {
        for(unsigned int i=0; i<resultadosICFES->size(); i++)
        {
            std::pair<unsigned int,double> unPar(i, atof(resultadosICFES->at(i).at(j+1)));
            vectorTemporal.push_back(unPar);
        }
        std::priority_queue <std::pair<unsigned int,double>,
                             std::vector<std::pair<unsigned int,double> >,
                             OrdenarPorPosicion>
        miColaDePrioridad(vectorTemporal.begin(), vectorTemporal.end(),
                          OrdenarPorPosicion());

        for(unsigned int i=0; i<resultadosICFES->size(); i++)
        {
            unsigned int indiceOrdenado = (miColaDePrioridad.top()).first;
            miColaDePrioridad.pop();

            char buffer [33];
            sprintf(buffer,"%d",((int)(resultadosICFES->size())-i));
            resultadosICFES->at(indiceOrdenado).at(j+1) = buffer;
        }
    }
}

AdmisionesUnivalle::~AdmisionesUnivalle()
{

}


const VectorEstudiantes* AdmisionesUnivalle::ordenarEstudiantesAdmisionesSegunPuntajesMinimosYPonderaciones(double puntajesMinimos[], double ponderaciones[])
{
    VectorEstudiantes *vectorResultado = new VectorEstudiantes;
    std::vector<std::pair<const char*,double> > vectorTemporal;

    for(unsigned int i=0;i<resultadosICFES->size();i++)
    {
        double puntajeTotal = 0;
        for(unsigned int j=0;j<7;j++)
        {
            puntajeTotal+= ponderaciones[j] *
			   atoi(resultadosICFES->at(i).at(j+1));
        }
        std::pair<const char*,double> unPar( resultadosICFES->at(i).at(0)
	                                   , puntajeTotal
					   );
        vectorTemporal.push_back(unPar);
    }

    std::priority_queue<std::pair<const char*,double>
                       ,std::vector<std::pair<const char*,double> >
                       ,OrdenarParesPorCodigo>
     miColaDePrioridad( vectorTemporal.begin()
                      , vectorTemporal.end()
                      , OrdenarParesPorCodigo());


    for(unsigned int i=0;i<vectorTemporal.size();i++)
    {
        vectorResultado->push_back((miColaDePrioridad.top()).first);
        miColaDePrioridad.pop();
    }

    return vectorResultado;
}

