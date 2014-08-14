/***************************************************************
 * Name:      dao.h
 * Purpose:   Super clase con utilidades para gestión de grupos
 *            de entidades
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

/**
 * @class DAO
 * @brief Super clase con utilidades para gestión de grupos
 *         de entidades
 */

#ifndef DAO_H
#define DAO_H

#include <string>
#include <ctype.h>
#include <wx/gauge.h>

#include "datos/csv.h"

class DAO
{
    public:
      DAO();
      virtual ~DAO();
      /**
	* Se debe implementar un metodo para crear las tablas, borrandolas
	* si existen.
	*/
      virtual void crearTablas() = 0;
      /**
	* Se debe implementar un metodo para insertar datos desde la lectura
	* de un archivo CSV
	* @param encabezados Los nombres de los encabezados, la primera
	* linea del archivo CSV
	* @param datosIn El archivo CSV sin el encabezado
	* @param barraProgreso Objeto para informar el progreso de la
	* inserción a la GUI.
	* @return Un string informando cuantos registros se ingresaron y
	* cuantos fueron erroneos
	*/
      virtual const char* insertar( encabezadoCSV encabezados
				  , datosCSV datosIn
				  , wxGauge *barraProgreso) = 0;
    protected:
      /**
       * Transforma en minuscula y elimina espacios en blanco.
       * @param str String a limpiar
       * @return String sin espacios y con letras en minuscula
       */
        std::string limpiarString(std::string str);


};

#endif // DAO_H
