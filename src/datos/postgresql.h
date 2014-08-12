/***************************************************************
 * Name:      postgresql.h
 * Purpose:   Enlace entre la aplicación y la base de datos
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

/**
 * @class PG
 * @brief Enlace entre la aplicación y la base de datos
 *
 * Solo deberia haber una instancia de esta clase en toda la aplicacion.
 */
#ifndef POSTGRESQL_H
#define POSTGRESQL_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <libpq-fe.h>
#include <vector>

/** ResultadoFila Representa un registro de la base de datos */
typedef std::vector<const char*> ResultadoFila;
typedef std::vector<std::vector<const char*> > ResultadoConsulta; /**< This is the documentation for the preceding typedef */

class PG
{
    public:
       /**
       * \brief Inicia una conexion con el servidor de base de datos, si la
       * conexion no se puede realizar informa con un mensaje de error.
       *
       * Solo deberia existir una instancia de esta clase, y todas las
       * consultas a la base de datos deberian realizarse por medio de esta
       * clase
       *
       * \param conexion String de conexion a la base de datos
       */
        PG(const char* conexion);
        /**
         * \brief Cierra la conexion a la base de datos
         */
        virtual ~PG();
        ResultadoConsulta* select(const char* query);
        bool query(const char* query);
        bool checkStatus();
        int insert(const char* query);
        int update(const char* query);
        int borrar(const char* query);
    private:
        PGconn  *conn;
};

#endif // POSTGRESQL_H
