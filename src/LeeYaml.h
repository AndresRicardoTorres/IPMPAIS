#ifndef LEEYAML_H
#define LEEYAML_H

#include <iostream>
#include <list>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>

typedef std::list<std::list<std::string> > listaDeListas;


class LeeYaml
{
	private:
        char *nombreArchivo;
        listaDeListas listaAnteriores;
        listaDeListas listaNuevas;
        void cargarEquivalencias();

	public:
        LeeYaml(std::string nombreArchivoIn);
        ~LeeYaml();
        listaDeListas getAnteriores();
        listaDeListas getNuevas();
};

#endif // LEEYAML_H
