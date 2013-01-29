#ifndef CALIFICACIONDAO_H
#define CALIFICACIONDAO_H

#include<vector>
#include<string>
#include<map>

#include "Calificacion.h"
#include "EquivalenciaDAO.h"
#include "LeerCSV.h"
#include "DAO.h"
typedef std::vector<Calificacion* > VectorCalificaciones;
typedef std::vector<std::vector<std::string> > VectorPromedios;
typedef std::map<const char*, const char*> PromediosDeEstudiantes;


class CalificacionDAO: protected DAO
{
    public:
        CalificacionDAO(const char* conn);
        virtual ~CalificacionDAO();
        const char* aplicarEquivalencias(VectorEquivalencias *equivalencias);
        void crearTablas();
        const char* insertar(encabezadoCSV encabezados,datosCSV datosIn,wxGauge *barraProgreso);
        VectorCalificaciones* getCalificacionesPorAsignatura(std::string asignatura);
        VectorCalificaciones* getCalificacionesOrdenasPorTipo();
        listaCSV* getListadoAsignaturas();
        PromediosDeEstudiantes* getPromediosDeEstudiantes();
        bool guardar(Calificacion *obj);
        bool borrar(Calificacion *obj);
        std::string formatearComas(std::string asignatura);
        vectorCSV separarComas(std::string asignatura);
        vectorCSV separarPuntoComas(std::string asignatura);
    protected:
    private:
        std::string conexion;
};

#endif // CALIFICACIONDAO_H
