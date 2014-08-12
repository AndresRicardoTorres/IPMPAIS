/***************************************************************
 * Name:      csv.h
 * Purpose:   Utilidad para leer archivos CSV
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

/**  
  @class CSV
  \brief Utilidad para leer archivos CSV Comma Separated Values
 
  Se pueden leer archivos CSV con encabezados, con diferente cantidad de
  columnas
  
*/

#ifndef SRC_DATOS_CSV_H_
#define SRC_DATOS_CSV_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

typedef std::list<std::string> encabezadoCSV;
typedef std::list<std::list<std::string> > datosCSV;
typedef std::list<std::string> listaCSV;
typedef std::vector<std::string> vectorCSV;


class CSV{
 public:
    /// Crea un lector desde la ruta de un archivo
    explicit CSV(std::string archivo);
    virtual ~CSV();

    /// Retorna los datos sin en el encabezado
    /** Retorna una lista de lista de los datos del archivo 
        sin el encabezado
        */
    datosCSV leerDatos();

    /// Retorna una lista con unicamente el encabezado del archivo
    encabezadoCSV leerEncabezado();
 private:
        std::string nombreArchivo;
};

#endif  // SRC_DATOS_CSV_H_
