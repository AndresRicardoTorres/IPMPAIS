#ifndef ESTUDIANTEDAO_H
#define ESTUDIANTEDAO_H

#include <wx/gauge.h>

#include "datos/postgresql.h"
#include "datos/csv.h"
#include "dao.h"
#include "calificacion.h"
#include "calificaciondao.h"
#include "admisionesunivalle.h"

/**
 * Un lista con :
 * + código del estaudiante
 * + ICFES lenguaje
 * + ICFES matematica
 * + ICFES ciencias sociales ( o el promedio entre geografia e historia)
 * + ICFES filosofia
 * + ICFES biologia
 * + ICFES quimica
 * + ICFES fisica
 *
 * para todos los estudiantes.
 *
 * Este orden NO se debe cambiar, se utiliza el mismo orden en la clase
 * AdmisionesUnivalle
 */
typedef std::vector<std::vector <const char*> > puntajesICFES;

/**
 * @brief Encargada de gestionar grupos de objetos estudiantes y su
 * almacenamiento en la base de datos
 */
class EstudianteDAO: protected DAO
{
    public:
      EstudianteDAO(const char* conn);
      virtual ~EstudianteDAO();
      /**
       * Dada una calificación actualiza las tablas estudiante_creditos y
       * estudiante_tipo
       * Si no se puede actualizar la nota, se asume que el estudiante no
       * existe, y se crea la información para un nuevo estudiante, por esta
       * razón es posible que hayan estudiantes con notas pero sin otro
       * tipo de información.
       * @param unaCalificacion Un objeto calificación
       * @return True si tuvo exito al actualizar o insertar el nuevo
       * estudiante, False en caso contrario
       */
      bool actualizar(Calificacion* unaCalificacion);
      /**
       * Crea las columnas en estudiante_tipo y estudiante_creditos según
       * el código de la asignatura.
       *
       * @param codigo_asignatura Código de la asignatura, ejemplo: 111050M
       */
      void crearColumnasAsignaturas(std::string codigo_asignatura);
      /**
       * Crea las tablas estudiante, estudiante_tipo y estudiante_creditos
       * En la primera tabla se almacena el contenido del archivo CSV
       * de los datos de los estudiantes.
       * Las tablas estudiante_tipo y estudiante_creditos se utilizan
       * para organizar las calificaciones de los estudiantes.
       */
      void crearTablas();
      /**
       * Devulve una lista con los códigos de estudiantes ordenados por el
       * promedio, se puede filtrar por años de ingreso del estudiante, y el
       * promedio se puede filtrar por lista de asignaturas
       * @param fecha_inicio Año inicial para filtrar estudiantes
       * @param fecha_final Año final para filtrar estudiantes
       * @param filtro_texto Lista de asignaturas separadas por coma
       * @param ECAESoRegistro Promedio del ECAES o promedio de las asignaturas
       * de la universidad
       * @return Una lista de códigos de estudiantes
       */
     listaCSV* getListaEstudiantesOrdenadaPorPromedio
        ( int fecha_inicio
        , int fecha_final
        , std::string filtro_texto
        , bool ECAESoRegistro
        );
      /**
       * Devuelve una lista con el código y los puntajes del ICFES de cada
       * estudiante, filtrando los estudiantes por los años
       * de sus códigos
       * @param fecha_inicio
       * @param fecha_final
       * @return Una lista de listas, con los puntajes de varios estudiantes
       */
      puntajesICFES* getPuntajesICFES(int fecha_inicio, int fecha_final);
      /**
	* Se insertan la información de los estudiantes desde un archivo CSV
	* con las columnas:
	* + codigo
	* + documento
	* + estrato
	* + comuna
	* + barrio
	* + ciudad
	* + colegio
	* + tipocolegio
	*
	* En cualquier orden, sin importar masyusculas o minusculas
	* @param encabezados Los nombres de los encabezados, la primera
	* linea del archivo CSV
	* @param datosIn El archivo CSV sin el encabezado
	* @param barraProgreso Objeto para informar el progreso de la
	* inserción a la GUI.
	* @return Un string informando cuantos registros se ingresaron y
	* cuantos fueron erroneos
	*/
      const char* insertar( encabezadoCSV encabezado
			  , datosCSV data
			  , wxGauge *barraProgreso
			  );
      /**
       *
       * Inserta datos de un archivo CSV a la base de datos, las columnas del
       * archivo deben ser código ( del estudiante ), snp, area y puntaje.
       *
       * Las areas deben ser (bio, cis, fil, fis, feo, his, idi, int, len,
       * mat, qui)
       * @param encabezados Los nombres de los encabezados, la primera
       * linea del archivo CSV
       * @param datosIn El archivo CSV sin el encabezado
       * @param barraProgreso Objeto para informar el progreso de la
       * inserción a la GUI.
       * @return Un string informando cuantos registros se ingresaron y
       * cuantos fueron erroneos
       */
      const char* insertarICFES( encabezadoCSV encabezados
			       , datosCSV datosIn
			       , wxGauge *barraProgreso
			       );
      /**
       * Inserta los datos de puntajes de ECAES desde un archivo CSV a la
       * base de datos, los nombres de las columnas pueden ser :
       * + documento | documento de identidad | identificacion
       * + puntajetotal | puntaje
       * + componante1p
       * + componante2p
       * + componante3p
       * + componante4p
       * + componante5p
       * + componante6p
       * + componante7p
       * + competencias1p
       * + competencias2p
       * + competencias3p
       *
       * Se ignoran las lineas que no se pueda definir su documento de
       * identidad y su puntaje total.
       *
       * @param encabezados Los nombres de los encabezados, la primera
       * linea del archivo CSV
       * @param datosIn El archivo CSV sin el encabezado
       * @param barraProgreso Objeto para informar el progreso de la
       * inserción a la GUI.
       * @return Un string informando cuantos registros se ingresaron y
       * cuantos fueron erroneos
       */
      std::string insertarPuntajesECAES( encabezadoCSV encabezados
                                       , datosCSV datosIn
                                       , wxGauge *barraProgreso
                                       );
      /**
       * Devuelve la lista de las columnas de la tabla estudiante para
       * construir un archivo CSV.
       * @return Lista separada por comas con los nombres de columnas
       */
      std::string obtenerNombreColumnas();
      /**
       * Consulta el promedio de estudiantes aplicando diferentes filtros.
       *
       * En modo ECAES filtra por todos los componentes, competencias y
       * puntaje total, ordenado por el código del estudiante.
       *
       * En modo registro académico, calcula el promedio de las asignaturas
       * en la universidad y ordena por este promedio, no tiene en cuenta
       * los estudiantes que no tengan puntajes de ICFES
       *
       * Este método tiene muchas responsabilidades, se recomiendo refactorarlo
       * en dos diferentes métodos para cada modo.
       *
       * @param columnas Los campos de la base de datos que se requieren
       * @param fecha_inicio La fecha de inicio para filtrar los estudiantes
       * @param fecha_final La fecha final para filtrar los estudiantes
       * @param listadoAsignaturas En modo ECAES, una lista exactamente 11
       * dígitos binarios, indicando si en el promedio se tiene en cuenta
       * los componentes, las competencias y el puntaje final, los primeros
       * 7 para los componentes, los siguientes 3 para las competencias y
       * el ultimo para el puntaje final
       * En modo registro académico una lista separada por comas, de las
       * asignaturas a tener en cuenta
       * @param ECAESoRegistro Representa el modo de la consulta, TRUE
       * si se necesita el modo ECAES, FALSE para el modo de registro académico
       * @return
       */
      ResultadoConsulta* selectAll( std::string columnas
                                  , int fecha_inicio
                                  , int fecha_final
                                  , std::string listadoAsignaturas
                                  , bool ECAESoRegistro
                                  );
    private:
        std::string conexion;
};

#else
class EstudianteDAO; // Declaración adelantada
#endif // ESTUDIANTEDAO_H
