#include "postgresql.h"

PG::PG(const char* conexion)
{
    //ctor
    std::string copia = conexion;
    conn = PQconnectdb(copia.c_str());

    if(checkStatus() == false)
    {

        std::cout<<"STATUS :( " << PQstatus(conn) << std::endl;

        std::cout<<":'( "<<PQerrorMessage(conn)<<std::endl;
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
    //std::cout<<"SELECT "<<query<<std::endl;
    for (int i=0;i<PQntuples(res);i++)
    {
        std::vector<const char*> unVector;
        for(int j=0;j<PQnfields(res);j++)
        {
            unVector.push_back(PQgetvalue(res, i, j));
        }
        resultado->push_back(unVector);
          //  antigua = PQgetvalue(res, i, 0);
          //  nueva = PQgetvalue(res, i, 1);

    }
    return resultado;
}

bool PG::query(const char* query)
{
    //std::cout<<"query>> "<<query<<std::endl;
    PGresult  *res = PQexec(conn,query);
    PQclear(res);

    return true;
}

bool PG::checkStatus()
{
    //std::cout<<"checkStatus() coon>> "<<conn<<std::endl;
    return !(PQstatus(conn) == CONNECTION_BAD);
}

int PG::insert(const char* query){
    //std::cout<<"insert() coon>> "<<conn<<std::endl;
    //std::cout<<"INSERT "<<query<<std::endl;
    PGresult  *res = PQexec(conn,query);
//    char* error = PQresultErrorField(res,PG_DIAG_SQLSTATE);
//    std::cout<<"ERROR>> "<<error<<std::endl;
    int x = atoi(PQcmdTuples(res));
    //std::cout<<"INSERT>> "<<x<<std::endl;
    PQclear(res);

    return x;
}

int PG::borrar(const char* query){
    PGresult  *res = PQexec(conn,query);
    int x = atoi(PQcmdTuples(res));
    if(0 == x)
    {
        char* error = PQresultErrorField(res,PG_DIAG_SQLSTATE);
        std::cout<<"ERROR>> "<<query<<"*"<<std::endl;

        std::cout<<"ERROR>> "<<error<<"*"<<std::endl;
        std::cout<<"???"<<std::endl;
    }
    PQclear(res);

    return x;
}

int PG::update(const char* query){
    //std::cout<<"insert() coon>> "<<conn<<std::endl;
    //std::cout<<"UPDATE "<<query<<std::endl;
    PGresult *res = PQexec(conn,query);
//    char* error = PQresultErrorField(res,PG_DIAG_SQLSTATE);
//    std::cout<<"ERROR>> "<<error<<std::endl;
    int x = atoi(PQcmdTuples(res));
    //std::cout<<"INSERT>> "<<x<<std::endl;
    PQclear(res);

    return x;
}
