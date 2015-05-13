/***************************************************************
 * Name:      calificaciondao.h
 * Purpose:   Permite gestionar y aplicar operaciones en conjuntos de
 *            calificaciones
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

/**
 * @class CalificacionDAO
 * @brief Permite gestionar y aplicar operaciones en conjuntos de
 *        calificaciones
 */

#ifndef CALIFICACIONDAO_H
#define CALIFICACIONDAO_H

#include <map>
#include <string>
#include <vector>

#include "datos/csv.h"
#include "ipmpais/calificacion.h"
#include "ipmpais/dao.h"
#include "ipmpais/equivalenciadao.h"

typedef std::vector<Calificacion* > VectorCalificaciones;
typedef std::vector<std::vector<std::string> > VectorPromedios;
typedef std::map<const char*, const char*> PromediosDeEstudiantes;

class CalificacionDAO: protected DAO
{
    public:
      /**
       * @param conexion String con la información de conexion a la base de
       * datos
       */
      CalificacionDAO(std::string conexion);
      virtual ~CalificacionDAO();
      /**
       * Estan soportados equivalencias entre :
       * + 1 a 1 asignatura
       * + 1 a 2 asignaturas
       * + 2 a 1 asignatura
       * + 2 a 2 asignaturas
       *
       * @param equivalencias Vector ordenado con objetos equivalencias para
       * ser aplicadas
       * @return Un string con el resultado de la operación
       */
      const char* aplicarEquivalencias(VectorEquivalencias *equivalencias);
      /**
       * Crea la tabla calificacion, la elimina si no existe
       */
      void crearTablas();
      /**
       * Devuelve todas las calificaciones de la base de datos, ordenadas
       * por el código de tipo (donde tipo puede ser repitente, habilitacion,
       * etc )
       * @return Devuelve un vector de objetos calificaciones
       */
      VectorCalificaciones* getCalificacionesOrdenasPorTipo();
      /**
       * Obtiene una lista de los códigos de las asignaturas que tienen
       * calificacion, este metodo deberia llamarse luego de aplicar las
       * equivalencias, pero no tiene en cuenta esto.
       * @return Lista de strings con códigos de asignaturas
       */
      listaCSV* getListadoAsignaturas();
      /**
       * Calcula el promedio de todos los estudiantes teniendo en cuenta
       * unicamente las asignaturas que tienen nota numerica y que tengan
       * creditos
       * @return Lista con códigos de estudiantes y su respectivo promedio
       */
      PromediosDeEstudiantes* getPromediosDeEstudiantes();
      /**
       * Inserta en la base de datos un conjunto de calificaciones leidas
       * desde un archivo CSV.
       * @param encabezados La lista de encabezados del archivo CSV, para
       * buscar la columna con los datos necesarios
       * @param datosIn El archivo CSV sin el encabezado
       * @param barraProgreso Objeto que representa la barra de progreso,
       * para informar a la GUI del progreso.
       * @return Retorna un String con el estado de la operación, cuantas
       * calificaciones fueron ingresadas y cuantas erroneas
       */
      const char* insertar( encabezadoCSV encabezados
			  , datosCSV datosIn
			  , wxGauge *barraProgreso
 			  );
    private:
      std::string conexion;
      bool borrar(Calificacion *obj);
      VectorCalificaciones* getCalificacionesPorAsignatura
	(std::string asignatura);
      bool guardar(Calificacion *obj);
      std::string formatearComas(std::string asignatura);
      vectorCSV separarComas(std::string asignatura);
      vectorCSV separarPuntoComas(std::string asignatura);
};

#endif // CALIFICACIONDAO_H
