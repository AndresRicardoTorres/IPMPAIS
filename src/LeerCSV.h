#ifndef LEERCSV_H
#define LEERCSV_H

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

class LeerCSV
{
    public:
        LeerCSV(std::string archivo);
        virtual ~LeerCSV();
        datosCSV leerDatos();
        bool escribirDatos(datosCSV entrada);
        encabezadoCSV leerEncabezado();
    protected:
    private:
        std::string nombreArchivo;
};

#endif // LEERCSV_H
