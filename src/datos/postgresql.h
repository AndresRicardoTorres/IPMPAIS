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
#include <string>
#include <vector>

/** ResultadoFila Representa un registro de la base de datos */
typedef std::vector<const char*> ResultadoFila;
/** Representa un conjunto de registros de la base de datos */
typedef std::vector<std::vector<const char*> > ResultadoConsulta;
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
       * \param conexion String de conexión a la base de datos
       */
      PG(std::string conexion);
      /**
       * \brief Cierra la conexión a la base de datos
       */
      virtual ~PG();
      /**
       * Envia una consulta SQL para realizar un DELETE
       * @param query consulta SQL
       * @return La cantidad de registros eliminados
       */
      int borrar(const char* query);
      /**
       * Verifica el estado de la conexión
       * @return True si se puede conectar al servidor de base de datos,
       * False en caso contrario
       */
      bool checkStatus();
      /**
       * Envia una consulta SQL para realizar un INSERT
       * @param query consulta SQL
       * @return La cantidad de registros insertados correctamente
       */
      int insert(const char* query);
      /**
       * Envia una consulta SQL, no retorna ningún reporte de la operación
       * @param query consulta SQL
       */
      void query(const char* query);
      /**
       * @param query consulta SQL
       * return
       */
      ResultadoConsulta* select(const char* query);
      /**
       * Envia una consulta SQL para realizar un UPDATE
       * @param query consulta SQL
       * @return La cantidad de registros actualizados
       */
      int update(const char* query);
    private:
      PGconn  *conn;
      int operacion(const char* query);
};

#endif // POSTGRESQL_H
