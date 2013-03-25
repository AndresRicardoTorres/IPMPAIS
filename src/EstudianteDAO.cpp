#include "EstudianteDAO.h"

EstudianteDAO::EstudianteDAO(const char* conn)
{
    //ctor
    conexion = conn;
}

EstudianteDAO::~EstudianteDAO()
{
    //dtor
}

void EstudianteDAO::crearTablas()
{
    PG *objPg = new PG(conexion.c_str());
    objPg->query("DROP TABLE IF EXISTS estudiante;");
    objPg->query("CREATE TABLE estudiante(año integer,codigo character varying,identificacion character varying,estrato character varying,comuna character varying,barrio character varying,ciudad character varying,colegio character varying,tipo_colegio character varying,snp character varying,bio real,cis real,fil real,fis real,geo real,his real,idi real,int real,len real,mat real,qui real,ecaes_total real,componente1 real,componente2 real,componente3 real,componente4 real,componente5 real,componente6 real,componente7 real,competencia1 real,competencia2 real,competencia3 real,CONSTRAINT estudiante_pkey PRIMARY KEY (codigo))");
    objPg->query("DROP TABLE IF EXISTS estudiante_tipo;");
    objPg->query("CREATE TABLE estudiante_tipo(año integer,codigo character varying,CONSTRAINT estudiante_tipo_pkey PRIMARY KEY (codigo ))");
    objPg->query("DROP TABLE IF EXISTS estudiante_creditos;");
    objPg->query("CREATE TABLE estudiante_creditos(año integer,codigo character varying,CONSTRAINT estudiante_creditos_pkey PRIMARY KEY (codigo ))");
    delete objPg;
}

const char* EstudianteDAO::insertar(encabezadoCSV encabezados,datosCSV datosIn,wxGauge *barraProgreso){
    int columna_codigo = -1,columna_documento = -1,columna_estrato = -1,columna_comuna = -1,columna_barrio = -1,columna_ciudad = -1,columna_colegio = -1,columna_tipo_colegio = -1, afectadas = 0,correctas = 0,erroneos = 0,i=0,j=0;
    std::string sql,codigo,documento,estrato,comuna,barrio,ciudad,colegio,tipo_colegio,ano;
    PG *objPg = new PG(conexion.c_str());


    ///Coloco limite al indicador
    barraProgreso->SetRange(datosIn.size());

    ///Busco las columnas correspondientes a los texto
    for (encabezadoCSV::iterator it = encabezados.begin(); it != encabezados.end(); it++,i++){
        std::string stringIt =  *it;
        stringIt = limpiarString(stringIt);
        if(stringIt.find("codigo") == 0)columna_codigo=i;
        if(stringIt.find("documento") == 0)columna_documento=i;
        if(stringIt.find("estrato") == 0)columna_estrato=i;
        if(stringIt.find("comuna") == 0)columna_comuna=i;
        if(stringIt.find("barrio") == 0)columna_barrio=i;
        if(stringIt.find("ciudad") == 0)columna_ciudad=i;
        if(stringIt.find("colegio") == 0)columna_colegio=i;
        if(stringIt.find("tipocolegio") == 0)columna_tipo_colegio=i;
    }


    i=0;
    for (std::list<std::list<std::string> >::iterator it = datosIn.begin(); it != datosIn.end(); it++,i++){
        barraProgreso->SetValue(i+1);
        j=0;
        codigo.clear();documento.clear();estrato.clear();comuna.clear();barrio.clear();ciudad.clear();colegio.clear();tipo_colegio.clear();
        for (std::list<std::string>::iterator it2 = it->begin(); it2 != it->end(); it2++,j++){
            if(j ==  columna_codigo) codigo = *it2;
            if(j ==  columna_documento) documento = *it2;
            if(j ==  columna_estrato) estrato = *it2;
            if(j ==  columna_comuna) comuna = *it2;
            if(j ==  columna_barrio) barrio = *it2;
            if(j ==  columna_ciudad) ciudad = *it2;
            if(j ==  columna_colegio) colegio = *it2;
            if(j ==  columna_tipo_colegio) tipo_colegio = *it2;

        }
        ano = codigo.substr(0,4);

        sql = "INSERT INTO estudiante(año,codigo, identificacion,estrato,comuna,barrio,ciudad,colegio,tipo_colegio) VALUES ("+ano+",'"+encriptar(codigo)+"','"+encriptar(documento)+"','"+estrato+"','"+comuna+"','"+barrio+"','"+ciudad+"','"+colegio+"','"+tipo_colegio+"');";
        afectadas = objPg->insert(sql.c_str());

        if(0==afectadas){
            //cout<<i<<"SQL: "<<sql<<endl;
            erroneos++;
        }else{
            correctas++;
        }
    }

    std::stringstream sstm;
    sstm << "Se insertaron " << correctas <<" estudiantes";
    if(erroneos>0)
        sstm <<", "<<erroneos<<" incorrectos";

    std::cout<<sstm.str()<<std::endl;
    delete objPg;
    return  sstm.str().c_str();
}

const char* EstudianteDAO::insertarICFES(encabezadoCSV encabezados,datosCSV datosIn,wxGauge *barraProgreso)
{
    barraProgreso->SetRange(datosIn.size());
    std::string actual="",codigo="",snp2="",snp="",bio="",cis="",fil="",fis="",geo="",his="",idi="",inte="",len="",mat="",qui="",area="",puntaje="",sql;
    int afectadas = 0, correctas = 0, erroneos = 0,i=0,j=0;
    bool unavez = false;
    PG *objPg = new PG(conexion.c_str());

    for (datosCSV::iterator it = datosIn.begin(); it != datosIn.end(); it++,i++){
                j=0;

        for (std::list<std::string>::iterator it2 = it->begin(); it2 != it->end(); it2++,j++){
            switch(j)
            {
                case 0:
                    codigo = *it2;
                break;
                case 1:
                    snp = *it2;
                break;
                case 2:
                    area = *it2;
                break;
                case 3:
                    puntaje = *it2;
                break;
            }

        }
        if(!unavez){
            actual = codigo;
            unavez = true;
            snp2 = snp;
        }
        if(0 != codigo.compare(actual))
        {
            barraProgreso->SetValue(i+1);

            if(0 == snp.size()) snp = "";
            if(0 == bio.size()) bio = "NULL";
            if(0 == cis.size()) cis = "NULL";
            if(0 == fil.size()) fil = "NULL";
            if(0 == fis.size()) fis = "NULL";
            if(0 == geo.size()) geo = "NULL";
            if(0 == his.size()) his = "NULL";
            if(0 == idi.size()) idi = "NULL";
            if(0 == inte.size()) inte = "NULL";
            if(0 == len.size()) len = "NULL";
            if(0 == mat.size()) mat = "NULL";
            if(0 == qui.size()) qui = "NULL";

            sql = "UPDATE estudiante SET snp = '"+
            snp2+
            "',bio = "+bio+
            ",cis = "+cis+
            ",fil = "+fil+
            ",fis = "+fis+
            ",geo = "+geo+
            ",his = "+his+
            ",idi = "+idi+
            ",\"int\" = "+inte+
            ",len = "+len+
            ",mat = "+mat+
            ",qui = "+qui+
            " WHERE codigo = '"+encriptar(actual)+"';";


            bio.clear();cis.clear();fil.clear();fis.clear();geo.clear();his.clear();idi.clear();inte.clear();len.clear();mat.clear();qui.clear();
            actual=codigo;
            snp2 = snp;

            afectadas = objPg->insert(sql.c_str());

            if(0==afectadas){
                erroneos++;
            }else{
                correctas++;
            }
        }
        area = limpiarString(area);
        puntaje = limpiarString(puntaje);

        if (puntaje.compare("0") != 0){
            if(area.find("bio")==0)bio=puntaje;
            if(area.find("cis")==0)cis=puntaje;
            if(area.find("fil")==0)fil=puntaje;
            if(area.find("fis")==0)fis=puntaje;
            if(area.find("geo")==0)geo=puntaje;
            if(area.find("his")==0)his=puntaje;
            if(area.find("idi")==0)idi=puntaje;
            if(area.find("int")==0)inte=puntaje;
            if(area.find("len")==0)len=puntaje;
            if(area.find("mat")==0)mat=puntaje;
            if(area.find("qui")==0)qui=puntaje;
        }

    }
///TODO
///UPDATE estudiante SET cis = (geo + his)/2 WHERE cis is null OR cis = 0;
    std::stringstream sstm;
    sstm << "Se actualizaron " << correctas <<" estudiantes";
    if(erroneos>0)
        sstm <<", "<<erroneos<<" incorrectos";
    delete objPg;
    return  sstm.str().c_str();

}

void EstudianteDAO::crearColumnasAsignaturas(std::string codigo_asignatura)
{
    std::string sql;
    PG *objPg = new PG(conexion.c_str());

    sql = "ALTER TABLE estudiante DROP COLUMN \"" + codigo_asignatura + "\";";
    objPg->query(sql.c_str());
    sql = "ALTER TABLE estudiante_tipo DROP COLUMN \"TIPO_" + codigo_asignatura+ "\";";
    objPg->query(sql.c_str());
    sql = "ALTER TABLE estudiante_creditos DROP COLUMN \"CREDITOS_" + codigo_asignatura  + "\";";
    objPg->query(sql.c_str());
    sql = "ALTER TABLE estudiante ADD COLUMN \"" + codigo_asignatura+ "\" character varying;";
    objPg->query(sql.c_str());
    sql = "ALTER TABLE estudiante_tipo ADD COLUMN \"TIPO_" +codigo_asignatura  + "\" character varying;";
    objPg->query(sql.c_str());
    sql = "ALTER TABLE estudiante_creditos ADD COLUMN \"CREDITOS_" + codigo_asignatura  + "\" integer;";
    objPg->query(sql.c_str());
    delete objPg;
}


bool EstudianteDAO::actualizar(Calificacion* unaCalificacion)
{
    PG *objPg = new PG(conexion.c_str());
    bool exito = false;
    int afectadas = 0;
    std::stringstream sql1,sql2,respuesta;

    ///Actualizo la tabla estudiante_tipo con la forma como curso el estudiante la asignatura

    sql1 << "UPDATE estudiante_tipo SET \"TIPO_" << unaCalificacion->getCodigoAsignatura()<<"\" = "<<unaCalificacion->getTipoNumericoCursado() << " WHERE codigo = '" << unaCalificacion->getCodigoEstudiante() << "';";
    afectadas = objPg->update(sql1.str().c_str());
    if(0==afectadas){
        sql2 << "INSERT INTO estudiante_tipo (año,codigo,\"TIPO_" << unaCalificacion->getCodigoAsignatura() << "\") VALUES (" << unaCalificacion->getAnno() << ",'" << unaCalificacion->getCodigoEstudiante() << "'," << unaCalificacion->getTipoNumericoCursado() << ");";
        afectadas = objPg->insert(sql2.str().c_str());
        if(0==afectadas){
            std::cout<<" "<<sql1.str().c_str()<<std::endl;
            std::cout<<" "<<sql2.str().c_str()<<std::endl;

        }
    }

    sql1.str(std::string());
    sql2.str(std::string());

    ///Actualizo la tabla estudiante creditos con los creditos que tenia la asignatura cuando la curso

    sql1 << "UPDATE estudiante_creditos SET \"CREDITOS_" << unaCalificacion->getCodigoAsignatura() << "\" = '" << unaCalificacion->getCreditos()<<"' WHERE codigo = '" << unaCalificacion->getCodigoEstudiante() << "';";
    afectadas = objPg->update(sql1.str().c_str());
    if(0==afectadas){
        sql2 << "INSERT INTO estudiante_creditos (año,codigo,\"CREDITOS_" << unaCalificacion->getCodigoAsignatura() << "\") VALUES (" << unaCalificacion->getAnno() << ",'" << unaCalificacion->getCodigoEstudiante() << "','" << unaCalificacion->getCreditos() << "');";
        afectadas = objPg->insert(sql2.str().c_str());
        if(0==afectadas){
            std::cout<<" "<<sql1.str().c_str()<<std::endl;
            std::cout<<" "<<sql2.str().c_str()<<std::endl;
        }

    }

    sql1.str(std::string());
    sql2.str(std::string());


    sql1 << "UPDATE estudiante SET \"" << unaCalificacion->getCodigoAsignatura() << "\" = '" << unaCalificacion->getCalificacion() << "' WHERE codigo = '" << unaCalificacion->getCodigoEstudiante() << "';";
    afectadas = objPg->update(sql1.str().c_str());

    if(0==afectadas){
        sql2 << "INSERT INTO estudiante (año,codigo,\"" << unaCalificacion->getCodigoAsignatura() << "\") VALUES (" << unaCalificacion->getAnno() << ",'" << unaCalificacion->getCodigoEstudiante() << "','" << unaCalificacion->getCalificacion() << "');";
         afectadas = objPg->insert(sql2.str().c_str());
        if(0==afectadas){
            std::cout<<" "<<sql1.str().c_str()<<std::endl;
            std::cout<<" "<<sql2.str().c_str()<<std::endl;
        }
        else
        {
            exito = true;
        }



    }else{
        exito = true;
    }

    delete objPg;
    return  exito;

}

std::string EstudianteDAO::insertarPuntajesECAES(encabezadoCSV encabezados,datosCSV datosIn,wxGauge *barraProgreso)
{
    PG *objPg = new PG(conexion.c_str());

    barraProgreso->SetRange(datosIn.size());

    int columna_documento = -1,columna_puntaje = -1,columna_componente_1 = 4,columna_componente_2 = 5,columna_componente_3 = 6,columna_componente_4 = 7,columna_componente_5 = 8,columna_componente_6 = 9,columna_componente_7 = 10,columna_competencia_1 = 11,columna_competencia_2 = 12,columna_competencia_3 = 13;

    size_t found;
    int i = 0,j=0;
    for (listaCSV::iterator it = encabezados.begin(); it != encabezados.end(); it++,i++){
        std::string stringIt =  *it;
        stringIt = limpiarString(stringIt);
        found=stringIt.find("documento");      if (found!=std::string::npos)columna_documento=1;
        found=stringIt.find("documento de identidad");      if (found!=std::string::npos)columna_documento=1;
        found=stringIt.find("identificacion");      if (found!=std::string::npos)columna_documento=i;
        found=stringIt.find("puntaje total");      if (found!=std::string::npos)columna_puntaje=i;
        found=stringIt.find("puntaje");      if (found!=std::string::npos)columna_puntaje=i;
        found=stringIt.find("Componente 1 P");      if (found!=std::string::npos)columna_componente_1=4;
        found=stringIt.find("Componente 2 P");      if (found!=std::string::npos)columna_componente_2=5;
        found=stringIt.find("Componente 3 P");      if (found!=std::string::npos)columna_componente_3=6;
        found=stringIt.find("Componente 4 P");      if (found!=std::string::npos)columna_componente_4=7;
        found=stringIt.find("Componente 5 P");      if (found!=std::string::npos)columna_componente_5=8;
        found=stringIt.find("Componente 6 P");      if (found!=std::string::npos)columna_componente_6=9;
        found=stringIt.find("Componente 7 P");      if (found!=std::string::npos)columna_componente_7=10;
        found=stringIt.find("Competencias 1 P");      if (found!=std::string::npos)columna_competencia_1=11;
        found=stringIt.find("Competencias 2 P");      if (found!=std::string::npos)columna_competencia_2=12;
        found=stringIt.find("Competencias 3 P");      if (found!=std::string::npos)columna_competencia_3=13;
    }

    std::cout<<"columna 1"<<columna_componente_1<<std::endl;
    std::cout<<"columna_componente_4"<<columna_componente_4<<std::endl;

    std::cout<<"columna columna_puntaje"<<columna_puntaje<<std::endl;



    std::string documento,puntaje ,componente_1 ,componente_2 ,componente_3 ,componente_4 ,componente_5 ,componente_6 ,componente_7 ,competencia_1 ,competencia_2 ,competencia_3 ;
    std::string sql;
    std::stringstream sstm;

    int afectadas = 0;
    int correctas = 0;
    int incorrectas = 0;
    for (datosCSV::iterator it = datosIn.begin(); it != datosIn.end(); it++,i++){
        barraProgreso->SetValue(i+1);
        j=0;
        documento.clear();puntaje.clear();componente_1.clear();componente_2.clear();componente_3.clear();componente_4.clear();componente_5.clear();
        componente_6.clear();componente_7.clear();competencia_1.clear();competencia_2.clear();competencia_3.clear();
        for (listaCSV::iterator it2 = it->begin(); it2 != it->end(); it2++,j++){
            if(j ==  columna_documento) documento = *it2;
            if(j ==  columna_puntaje) puntaje = *it2;
            if(j ==  columna_componente_1) componente_1 = *it2;
            if(j ==  columna_componente_2) componente_2 = *it2;
            if(j ==  columna_componente_3) componente_3 = *it2;
            if(j ==  columna_componente_4) componente_4 = *it2;
            if(j ==  columna_componente_5) componente_5 = *it2;
            if(j ==  columna_componente_6) componente_6 = *it2;
            if(j ==  columna_componente_7) componente_7 = *it2;
            if(j ==  columna_competencia_1) competencia_1 = *it2;
            if(j ==  columna_competencia_2) competencia_2 = *it2;
            if(j ==  columna_competencia_3) competencia_3 = *it2;
        }
        if(0==documento.size() && 0==puntaje.size()) continue;

        if(0 == componente_1.size())componente_1="NULL";
        if(0 == componente_2.size())componente_2="NULL";
        if(0 == componente_3.size())componente_3="NULL";
        if(0 == componente_4.size())componente_4="NULL";
        if(0 == componente_5.size())componente_5="NULL";
        if(0 == componente_6.size())componente_6="NULL";
        if(0 == componente_7.size())componente_7="NULL";
        if(0 == competencia_1.size())competencia_1="NULL";
        if(0 == competencia_2.size())competencia_2="NULL";
        if(0 == competencia_3.size())competencia_3="NULL";

        sstm << "UPDATE estudiante SET ecaes_total = "<<puntaje<<",componente1 ="<<componente_1<<",componente2 ="<<componente_2<<",componente3 ="<<componente_3<<",componente4 ="<<componente_4<<",componente5 ="<<componente_5<<",componente6 ="<<componente_6<<",componente7 ="<<componente_7<<",competencia1 ="<<competencia_1<<",competencia2 ="<<competencia_2<<",competencia3 ="<<competencia_3<<" WHERE identificacion = '"<<encriptar(documento)<<"';";
        sql = sstm.str();
        sstm.str(std::string());

        afectadas = objPg->update(sql.c_str());

        if(0==afectadas){
            //std::cout<<i<<" "<<sql.c_str()<<std::endl;
            incorrectas++;
        }else{
            correctas++;
        }

    }

    sstm << "Se ingresaron " << correctas <<" puntajes de ecaes";
    if(incorrectas>0)
    sstm <<", "<<incorrectas<<" incorrectos";

    delete objPg;
    return sstm.str();
}

listaCSV* EstudianteDAO::getListaEstudiantesOrdenadaPorPromedio(int fecha_inicio,int fecha_final,std::string filtro_texto,bool ECAESoRegistro)
{
    ResultadoConsulta *resultado = selectAll("codigo",fecha_inicio,fecha_final,filtro_texto,ECAESoRegistro);

    listaCSV *listadoCodigoEstudiantes = new listaCSV;
    for(unsigned int i=0;i<resultado->size();i++)
    {
        ResultadoFila unaFila= resultado->at(i);
        listadoCodigoEstudiantes->push_back(unaFila.at(0));
    }

    delete resultado;
    return listadoCodigoEstudiantes;
}

puntajesICFES * EstudianteDAO::getPuntajesICFES(int fecha_inicio,int fecha_final,std::string listadoAsignaturas)
{
    ///El orden de los campos de la consulta NO se debe cambiar, corresponde al orden en admisionesunivalle
    return selectAll("codigo,len,mat,CASE WHEN cis IS NULL THEN (geo+his)/2 ELSE cis END as cis,fil,bio,qui,fis",fecha_inicio,fecha_final,listadoAsignaturas,false);
}

ResultadoConsulta* EstudianteDAO::selectAll(std::string columnas,int fecha_inicio,int fecha_final,std::string listadoAsignaturas,bool ECAESoRegistro){

    PG *objPg = new PG(conexion.c_str());
    std::stringstream ss;
    std::string order;
    ResultadoConsulta *resultado;

    if(ECAESoRegistro){


        if(listadoAsignaturas.size()!=11){
            std::cout<<"ERROR listadoAsignaturas.size()"<<listadoAsignaturas.size()<<std::endl;
            resultado = objPg->select("SELECT FALSE");
            return resultado;
        }

        order="promedio";
        ss << " SELECT (";
        bool first_comma = false;
        unsigned int cantidad = 0;
        for(unsigned int i = 0;i<7;i++)
        {
            if(listadoAsignaturas.compare(i,1,"1")==0)
            {
                if(!first_comma)
                {
                    first_comma=true;
                }else{
                    ss << " + ";
                }
                ss << "componente" << (i+1);
                cantidad++;
            }

        }

        for(unsigned int i = 7;i<10;i++){
            if(listadoAsignaturas.compare(i,1,"1")==0)
            {
                if(!first_comma)
                {
                    first_comma=true;
                }else{
                    ss << " + ";
                }
                ss << "competencia" << (i-7+1);
                cantidad++;
            }
        }

        if(listadoAsignaturas.compare(10,1,"1")==0)
        {
            if(!first_comma)
                {
                    first_comma=true;
                }else{
                    ss << " + ";
                }
                ss << "ecaes_total";
                cantidad++;
        }

        if(cantidad==0){
            std::cout<<"ERROR cantidad ECAES"<<std::endl;
            resultado = objPg->select("SELECT FALSE");
            return resultado;
        }

        ss << ")/" << cantidad;

        ss << " as promedio ,codigo FROM estudiante WHERE componente1 IS NOT NULL AND componente7 IS NOT NULL ";


    }else{
        order="subconsulta.promedio";
        if(columnas.size() <= 0)
            columnas = "subconsulta.promedio,*";

        ss << "SELECT " << columnas <<" FROM estudiante JOIN (  SELECT codigo_estudiante,promedio FROM  (SELECT count(codigo_asignatura) as cantidad,codigo_estudiante,SUM(calificacion_numerica*creditos)/SUM(creditos) as promedio FROM calificacion WHERE creditos!= 0 ";

        if(listadoAsignaturas.size()>0)
            ss<<" AND codigo_asignatura IN("<<listadoAsignaturas<<")";

        ss << " GROUP BY codigo_estudiante ) as a ";

        if(listadoAsignaturas.size()>0){
            int cantidadComas = 1;
            for(unsigned int i=0;i<listadoAsignaturas.size();i++)
                if(listadoAsignaturas[i] == ',')
                    cantidadComas++;
            ///la cantidad es para limitar la cantidad materias promedidas si la repitio
            //ss<<" WHERE  cantidad = "<<cantidadComas;
        }

        ss<<") as subconsulta ON (codigo_estudiante = codigo) WHERE len is not null AND mat is not null AND fil IS NOT NULL AND bio IS NOT NULL AND qui IS NOT NULL and fis IS NOT NULL AND (cis IS NOT NULL OR (his IS NOT NULL AND geo IS NOT NULL))";
    }


    if(fecha_inicio > 0)
        ss << " AND año >= " << fecha_inicio;

    if(fecha_final > 0)
        ss << " AND año <= " << fecha_final;


    if(ECAESoRegistro){
        ss << "GROUP BY codigo";
    }

    ss << " ORDER BY " << order << " DESC ";


    std::cout<<"EstudianteDAO::selectAll"<<ss.str()<<std::endl;

    resultado = objPg->select(ss.str().c_str());

    delete objPg;
    return resultado;
}

std::string EstudianteDAO::obtenerNombreColumnas(){
    PG *objPg = new PG(conexion.c_str());
    std::stringstream ss;
    ResultadoConsulta *resultado = objPg->select("SELECT column_name FROM information_schema.columns WHERE table_name = 'estudiante' ORDER BY ordinal_position;");

    for(unsigned int i=0;i<resultado->size();i++)
    {
        ResultadoFila unaFila= resultado->at(i);
        ss<<unaFila.at(0);
        if(i<resultado->size()-1)
            ss<<",";
    }

    delete objPg;
    return ss.str();
}

