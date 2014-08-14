#include "postgresql.h"

PG::PG(const char* conexion)
{
    //ctor
    std::string copia = conexion;
    conn = PQconnectdb(copia.c_str());

    if(checkStatus() == false)
    {
      std::cout << "PQstatus = " << PQstatus(conn) << std::endl;
      std::cout << "PQerrorMessage = " << PQerrorMessage(conn) << std::endl;
    }
}

PG::~PG()
{
    //dtor
    PQfinish(conn);
}

ResultadoConsulta* PG::select(const char* query)
{
    ResultadoConsulta *resultado = new ResultadoConsulta();
    PGresult  *res = PQexec(conn,query);
    for (int i=0;i<PQntuples(res);i++)
    {
        std::vector<const char*> unVector;
        for(int j=0;j<PQnfields(res);j++)
        {
            unVector.push_back(PQgetvalue(res, i, j));
        }
        resultado->push_back(unVector);
    }
    return resultado;
}

void PG::query(const char* query)
{
    PGresult *res = PQexec(conn,query);
    PQclear(res);
}

bool PG::checkStatus()
{
    return !(PQstatus(conn) == CONNECTION_BAD);
}

int PG::insert(const char* query){
    return operacion(query);
}

int PG::borrar(const char* query){
    return operacion(query);
}

int PG::update(const char* query){
    return operacion(query);
}

int PG::operacion(const char* query){
    PGresult *res = PQexec(conn,query);
    int x = atoi(PQcmdTuples(res));
    // Para obtener errores :
    // char* error = PQresultErrorField(res,PG_DIAG_SQLSTATE);
    PQclear(res);
    return x;
}

