#ifndef EQUIVALENCIADAO_H
#define EQUIVALENCIADAO_H

#include <vector>
#include <wx/gauge.h>

#include "dao.h"
#include "datos/postgresql.h"
#include "datos/csv.h"
#include "equivalencia.h"

/**
 * Lista ordenada de objetos equivalencia
 */
typedef std::vector<Equivalencia* > VectorEquivalencias;

/**
 * @brief Encargada de gestionar grupos de equivalencias
 */
class EquivalenciaDAO: protected DAO
{
    public:
      /*
       * @conn String con la información de la conexión a la base de datos
       */
      EquivalenciaDAO(const char* conn);
      virtual ~EquivalenciaDAO();
      /**
       * Crea la tabla equivalencia
       */
      void crearTablas();
      /**
       * Se insertan un archivo CSV con los encabezados "actual" y "antigua"
       * en la base de datos
      * @param encabezado Los nombres de los encabezados, la primera
      * linea del archivo CSV
      * @param datosIn El archivo CSV sin el encabezado
      * @param barraProgreso Objeto para informar el progreso de la
      * inserción a la GUI.
      * @return Un string informando cuantos registros se ingresaron y
      * cuantos fueron erroneos
      */
      const char* insertar( listaCSV encabezado
			  , datosCSV datosIn
			  , wxGauge *barraProgreso
			  );
      /**
       * Devuelve una lista ordenada de objetos equivalencia
       */
      VectorEquivalencias* getEquivalencias();

    protected:
    private:
        std::string conexion;
};

#endif // EQUIVALENCIADAO_H
