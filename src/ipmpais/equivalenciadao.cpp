#include "equivalenciadao.h"

EquivalenciaDAO::EquivalenciaDAO(std::string conn)
{
    //ctor
    conexion = conn;
}

EquivalenciaDAO::~EquivalenciaDAO()
{
    //dtor
}

VectorEquivalencias* EquivalenciaDAO::getEquivalencias()
{
    VectorEquivalencias *equivalencias = new VectorEquivalencias();
    PG *objPG = new PG(conexion.c_str());
    ResultadoConsulta *resultado = objPG->select("SELECT antigua,nueva,orden"
      "FROM equivalencia ORDER BY orden");

    for(unsigned int i=0;i<resultado->size();i++)
    {
        ResultadoFila unaFila= resultado->at(i);
        Equivalencia *a = new Equivalencia( unaFila.at(0)
					  , unaFila.at(1)
					  , atoi(unaFila.at(2))
					  );
        equivalencias->push_back(a);
    }
    return equivalencias;
}

const char* EquivalenciaDAO::insertar( listaCSV encabezados
				     , datosCSV datosIn
				     , wxGauge *barraProgreso
				     )
{
    datosCSV anteriores;
    datosCSV nuevas;
    listaCSV tmp;
    int columna_nuevas     = -1
      , columna_anteriores = -1
      , i                  = 0
      , j                  = 0;

    for ( encabezadoCSV::iterator it = encabezados.begin()
        ; it != encabezados.end()
	; it++,i++){

        std::string stringIt =  *it;
        stringIt = limpiarString(stringIt);
        if(stringIt.find("actual") == 0)
	  columna_nuevas=i;
        if(stringIt.find("antigua") == 0)
	  columna_anteriores=i;
    }

    for ( datosCSV::iterator it = datosIn.begin()
        ; it != datosIn.end()
	; it++,i++){

        j=0;
        for ( listaCSV::iterator it2 = it->begin()
	  ; it2 != it->end()
	  ; it2++,j++){

            tmp.clear();
            tmp.push_back(*it2);
            if(j == columna_nuevas)
                nuevas.push_back(tmp);

            if(j == columna_anteriores)
                anteriores.push_back(tmp);

        }
    }

    PG *objPG = new PG(conexion.c_str());
    int afectadas = 0
      , correctas = 0
      , erroneos  = 0;
    i = 1;
    std::string antigua,nueva,sql;
    std::stringstream sstm;

    barraProgreso->SetRange(nuevas.size());

    for ( std::list<std::list<std::string> >::iterator it1 = anteriores.begin()
	, it2 = nuevas.begin()
	; it1 != anteriores.end() && it2 != nuevas.end()
	; it1++, it2++){
            for (std::list<std::string>::iterator it3 = it1->begin()
	        , it4 = it2->begin();
                it3 != it1->end() && it4 != it2->end();
                it3++, it4++){
                    if(0==antigua.size())
                        antigua += *it3;
                    else
                        antigua += ","+*it3;

                    if(0==nueva.size())
                        nueva += *it4;
                    else
                        nueva += ","+*it4;
            }

            barraProgreso->SetValue(i);
            i++;
            sstm << "INSERT INTO equivalencia VALUES('" << antigua << "','" <<
	      nueva << "'," << i << ");";

            afectadas = objPG->insert(sstm.str().c_str());
            sstm.str(std::string());
            if(0==afectadas){
                erroneos++;
            }else{
                correctas++;
            }
            antigua.clear();
            nueva.clear();
        }


    sstm << "Se insertaron " << correctas <<" equivalencias";
    if(erroneos>0)
        sstm <<", "<<erroneos<<" incorrectas";


    return sstm.str().c_str();
}


void EquivalenciaDAO::crearTablas()
{
    PG *objPg = new PG(conexion.c_str());

    objPg->query("DROP TABLE equivalencia;");
    objPg->query("CREATE TABLE equivalencia"
		 "( antigua character varying NOT NULL"
		 ", nueva character varying NOT NULL"
		 ", orden integer"
		 ");");

}
