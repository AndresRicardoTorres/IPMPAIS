#ifndef POSTGRESQL_H
#define POSTGRESQL_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <libpq-fe.h>
#include <vector>

typedef std::vector<const char*> ResultadoFila;
typedef std::vector<std::vector<const char*> > ResultadoConsulta;

class PG
{
    public:
        PG(const char* conexion);
        virtual ~PG();
        ResultadoConsulta* select(const char* query);
        bool query(const char* query);
        bool checkStatus();
        int insert(const char* query);
        int update(const char* query);
        int borrar(const char* query);
    protected:
    private:
        PGconn  *conn;
};

#endif // POSTGRESQL_H
