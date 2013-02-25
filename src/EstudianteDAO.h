#ifndef ESTUDIANTEDAO_H
#define ESTUDIANTEDAO_H

#include "DAO.h"
#include "PG.h"
#include "LeerCSV.h"
#include <wx/gauge.h>
#include "Calificacion.h"
#include "CalificacionDAO.h"
#include "admisionesunivalle.h"

typedef std::vector<std::vector <const char*> > puntajesICFES;

class EstudianteDAO: protected DAO
{
    public:
        EstudianteDAO(const char* conn);
        virtual ~EstudianteDAO();
        void crearTablas();
        const char* insertar(encabezadoCSV encabezado,datosCSV data,wxGauge *barraProgreso);
        const char* insertarICFES(encabezadoCSV encabezados,datosCSV datosIn,wxGauge *barraProgreso);
        void crearColumnasAsignaturas(std::string codigo_asignatura);
        bool actualizar(Calificacion* unaCalificacion);
        const char * actualizarPromedio(PromediosDeEstudiantes *listadoPromedios);
        std::string insertarPuntajesECAES(encabezadoCSV encabezados,datosCSV datosIn,wxGauge *barraProgreso);
        listaCSV* getListaEstudiantesOrdenadaPorPromedio(int fecha_inicio,int fecha_final,std::string filtro_texto,bool ECAESoRegistro);
        puntajesICFES* getPuntajesICFES(int fecha_inicio,int fecha_final,std::string listadoAsignaturas);
        ResultadoConsulta* selectAll(std::string columnas,int fecha_inicio,int fecha_final,std::string listadoAsignaturas,bool ICFESoECAES);
        std::string obtenerNombreColumnas();
    protected:
    private:
        std::string conexion;
};

#else
class EstudianteDAO; // Declaración adelantada
#endif // ESTUDIANTEDAO_H
