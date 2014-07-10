/***************************************************************
 * Name:      csv.cpp
 * Purpose:   Utilidad para leer archivos CSV
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

#include "datos/csv.h"

CSV::CSV(std::string archivo)
{
    nombreArchivo = archivo;
}

CSV::~CSV()
{
    //dtor
}

encabezadoCSV CSV::leerEncabezado(){
    encabezadoCSV lista;
    std::ifstream  data(nombreArchivo.c_str());

    std::string line;
    std::getline(data,line);

    std::stringstream  lineStream(line);
    std::string        cell;
    while(std::getline(lineStream,cell,','))
    {
        lista.push_back(cell);
    }
    return lista;
}

datosCSV CSV::leerDatos(){
    datosCSV lista;
    std::ifstream  data(nombreArchivo.c_str());

    std::string line;
    std::list <std::string> tmp;
    bool primeraVez = false;
    bool abierto=false;
    while(std::getline(data,line))
    {
        std::stringstream  lineStream(line);
        std::string        cell;
        std::string        longCell;
        while(std::getline(lineStream,cell,','))
        {
            if(cell[0]=='\"')
            {
                abierto=true;
                longCell=cell;
                if(cell[cell.size()-1]=='\"')
                {
                    abierto=false;
                    tmp.push_back(cell);
                }
            }
            else if(abierto)
            {
                longCell+=","+cell;
                if(cell[cell.size()-1]=='\"')
                {
                    cell=longCell;
                    abierto=false;
                    tmp.push_back(cell);
                }
            }
            else
                tmp.push_back(cell);
            //cout<<"_"<<cell<<"*";
            // You have a cell!!!!

        }
        if(primeraVez)
            lista.push_back(tmp);
        tmp.clear();
        primeraVez=true;
    }
    return lista;
}
