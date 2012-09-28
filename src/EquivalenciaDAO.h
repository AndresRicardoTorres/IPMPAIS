#ifndef EQUIVALENCIADAO_H
#define EQUIVALENCIADAO_H

#include <vector>
#include "Equivalencia.h"
#include "PG.h"
#include <wx/gauge.h>
#include "LeeYaml.h"

#include "DAO.h"
typedef std::vector<Equivalencia* > VectorEquivalencias;

class EquivalenciaDAO: protected DAO
{
    public:
        EquivalenciaDAO(const char* conn);
        virtual ~EquivalenciaDAO();
        const char* insertar(listaDeListas anteriores,listaDeListas nuevas,wxGauge *barraProgreso);
        VectorEquivalencias* getEquivalencias();
        void crearTablas();
    protected:
    private:
        std::string conexion;
};

#endif // EQUIVALENCIADAO_H
