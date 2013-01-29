#include "CalificacionDAO.h"

CalificacionDAO::CalificacionDAO(const char* conn)
{
    //ctor
    conexion = conn;
}

CalificacionDAO::~CalificacionDAO()
{
    //dtor
}

const char* CalificacionDAO::aplicarEquivalencias(VectorEquivalencias *equivalencias)
{
    PG *objPg = new PG(conexion.c_str());
    int afectadas = 0,totales = 0,errores=0,cantidadAntiguas = 0,cantidadNuevas = 0;
    std::string antigua,nueva,sql;
    std::stringstream sstm;

    for (unsigned int i=0;i<equivalencias->size();i++)
    {
        Equivalencia *unaEquivalencia = equivalencias->at(i);

        antigua = unaEquivalencia->getAntigua();
        nueva = unaEquivalencia->getNueva();

        std::cout<<"Aplicando equivalencia "<<antigua<<" => "<<nueva<<std::endl;

        cantidadAntiguas=1;
        cantidadNuevas=1;

        if(antigua.find(";")!=std::string::npos)
            cantidadAntiguas=2;

        if(nueva.find(";")!=std::string::npos)
            cantidadNuevas=2;


        ///Equivalencia uno a uno
        if(cantidadAntiguas==1 && cantidadNuevas == 1)
        {
            sql = "UPDATE calificacion SET codigo_asignatura  = '"+nueva+"' WHERE codigo_asignatura = '"+antigua+"';";
            afectadas = objPg->update(sql.c_str());
            totales += afectadas;
            /*
            if(0==afectadas){
                std::cout<<" EQuivalencia no afecto "<<i<<" "<<sql.c_str()<<std::endl;
            }
            */
        }
        ///Equivalencia uno a dos
        else if(cantidadAntiguas==1 && cantidadNuevas == 2)
        {

            VectorCalificaciones *calificaciones =  getCalificacionesPorAsignatura(antigua);

            vectorCSV nuevas = separarPuntoComas(nueva);

            for(unsigned int i=0;calificaciones->size()>i;i++)
            {
                Calificacion *unaCalificacion = calificaciones->at(i);


                Calificacion *calificacionNueva1 = new Calificacion();
                calificacionNueva1->setCodigoAsignatura(nuevas.at(0).c_str());

                calificacionNueva1->setAnno(unaCalificacion->getAnno());
                calificacionNueva1->setCalificacion(unaCalificacion->getCalificacion());
                calificacionNueva1->setCalificacionReal(unaCalificacion->getCalificacionReal());
                calificacionNueva1->setCodigoEstudiante(unaCalificacion->getCodigoEstudiante());
                calificacionNueva1->setCodigoOriginalAsignatura(unaCalificacion->getCodigoOriginalAsignatura());
                calificacionNueva1->setCreditos(unaCalificacion->getCreditos());
                calificacionNueva1->setNombreAsignatura(unaCalificacion->getNombreAsignatura());
                calificacionNueva1->setPeriodo(unaCalificacion->getPeriodo());
                calificacionNueva1->setTipoCursado(unaCalificacion->getTipoCursado());
                calificacionNueva1->setTipoNumericoCursado(unaCalificacion->getTipoNumericoCursado());

                Calificacion *calificacionNueva2 = new Calificacion();
                calificacionNueva2->setCodigoAsignatura(nuevas.at(1).c_str());

                calificacionNueva2->setAnno(unaCalificacion->getAnno());
                calificacionNueva2->setCalificacion(unaCalificacion->getCalificacion());
                calificacionNueva2->setCalificacionReal(unaCalificacion->getCalificacionReal());
                calificacionNueva2->setCodigoEstudiante(unaCalificacion->getCodigoEstudiante());
                calificacionNueva2->setCodigoOriginalAsignatura(unaCalificacion->getCodigoOriginalAsignatura());
                calificacionNueva2->setCreditos(unaCalificacion->getCreditos());
                calificacionNueva2->setNombreAsignatura(unaCalificacion->getNombreAsignatura());
                calificacionNueva2->setPeriodo(unaCalificacion->getPeriodo());
                calificacionNueva2->setTipoCursado(unaCalificacion->getTipoCursado());
                calificacionNueva2->setTipoNumericoCursado(unaCalificacion->getTipoNumericoCursado());
                if(borrar(unaCalificacion)==0){errores++;}
                if(guardar(calificacionNueva1)==1)afectadas++;else{errores++;}
                if(guardar(calificacionNueva2)==1)afectadas++;else{errores++;}


            }


        }
        ///Equivalencia dos a uno
        else if(cantidadAntiguas==2 && cantidadNuevas == 1)
        {
            VectorCalificaciones *calificaciones =  getCalificacionesPorAsignatura(antigua);
            const char* estudiante_anterior = "";
            double calificacion_nueva = 0;
            for(unsigned int i=0;calificaciones->size()>i;i++)
            {
                Calificacion *unaCalificacion = calificaciones->at(i);
                if(estudiante_anterior == unaCalificacion->getCodigoEstudiante()){
                    calificacion_nueva += unaCalificacion->getCalificacionReal();
                    calificacion_nueva = calificacion_nueva / 2;


                    Calificacion *calificacionNueva1 = new Calificacion();

                    calificacionNueva1->setCodigoAsignatura(nueva.c_str());
                    calificacionNueva1->setAnno(unaCalificacion->getAnno());
                    calificacionNueva1->setCalificacion(unaCalificacion->getCalificacion());
                    calificacionNueva1->setCalificacionReal(calificacion_nueva);
                    calificacionNueva1->setCodigoEstudiante(unaCalificacion->getCodigoEstudiante());
                    calificacionNueva1->setCodigoOriginalAsignatura(unaCalificacion->getCodigoOriginalAsignatura());
                    calificacionNueva1->setCreditos(unaCalificacion->getCreditos());
                    calificacionNueva1->setNombreAsignatura(unaCalificacion->getNombreAsignatura());
                    calificacionNueva1->setPeriodo(unaCalificacion->getPeriodo());
                    calificacionNueva1->setTipoCursado(unaCalificacion->getTipoCursado());
                    calificacionNueva1->setTipoNumericoCursado(unaCalificacion->getTipoNumericoCursado());
                    if(borrar(unaCalificacion)==0){errores++;}
                    if(guardar(calificacionNueva1)==1)afectadas++;else{errores++;}

                }else{
                    estudiante_anterior = unaCalificacion->getCodigoEstudiante();
                    calificacion_nueva = unaCalificacion->getCalificacionReal();
                    if(borrar(unaCalificacion)==0){errores++;}

                }

            }
        }
        ///Equivalencia 2 a 2
        else if(cantidadAntiguas==2 && cantidadNuevas == 2)
        {
            VectorCalificaciones *calificaciones =  getCalificacionesPorAsignatura(antigua);
            const char* estudiante_anterior = "";
            double calificacion_nueva = 0;
            vectorCSV nuevas = separarPuntoComas(nueva);
            for(unsigned int i=0;calificaciones->size()>i;i++)
            {
                Calificacion *unaCalificacion = calificaciones->at(i);
                if(estudiante_anterior == unaCalificacion->getCodigoEstudiante()){
                    calificacion_nueva += unaCalificacion->getCalificacionReal();
                    calificacion_nueva = calificacion_nueva / 2;


                    Calificacion *calificacionNueva1 = new Calificacion();

                    calificacionNueva1->setCodigoAsignatura(nuevas.at(0).c_str());
                    calificacionNueva1->setAnno(unaCalificacion->getAnno());
                    calificacionNueva1->setCalificacion(unaCalificacion->getCalificacion());
                    calificacionNueva1->setCalificacionReal(calificacion_nueva);
                    calificacionNueva1->setCodigoEstudiante(unaCalificacion->getCodigoEstudiante());
                    calificacionNueva1->setCodigoOriginalAsignatura(unaCalificacion->getCodigoOriginalAsignatura());
                    calificacionNueva1->setCreditos(unaCalificacion->getCreditos());
                    calificacionNueva1->setNombreAsignatura(unaCalificacion->getNombreAsignatura());
                    calificacionNueva1->setPeriodo(unaCalificacion->getPeriodo());
                    calificacionNueva1->setTipoCursado(unaCalificacion->getTipoCursado());
                    calificacionNueva1->setTipoNumericoCursado(unaCalificacion->getTipoNumericoCursado());

                    Calificacion *calificacionNueva2 = new Calificacion();
                    calificacionNueva2->setCodigoAsignatura(nuevas.at(1).c_str());
                    calificacionNueva2->setAnno(unaCalificacion->getAnno());
                    calificacionNueva2->setCalificacion(unaCalificacion->getCalificacion());
                    calificacionNueva2->setCalificacionReal(calificacion_nueva);
                    calificacionNueva2->setCodigoEstudiante(unaCalificacion->getCodigoEstudiante());
                    calificacionNueva2->setCodigoOriginalAsignatura(unaCalificacion->getCodigoOriginalAsignatura());
                    calificacionNueva2->setCreditos(unaCalificacion->getCreditos());
                    calificacionNueva2->setNombreAsignatura(unaCalificacion->getNombreAsignatura());
                    calificacionNueva2->setPeriodo(unaCalificacion->getPeriodo());
                    calificacionNueva2->setTipoCursado(unaCalificacion->getTipoCursado());
                    calificacionNueva2->setTipoNumericoCursado(unaCalificacion->getTipoNumericoCursado());
                    if(borrar(unaCalificacion)==0){errores++;}
                    if(guardar(calificacionNueva1)==1)afectadas++;else{errores++;}
                    if(guardar(calificacionNueva2)==1)afectadas++;else{errores++;}

                }else{
                    estudiante_anterior = unaCalificacion->getCodigoEstudiante();
                    calificacion_nueva = unaCalificacion->getCalificacionReal();
                    if(borrar(unaCalificacion)==0){errores++;}

                }
            }
        }
    }

    delete objPg;

    sstm << "Se actualizaron " << totales <<" calificaciones , errores "<<errores;

    return sstm.str().c_str();
}

bool CalificacionDAO::guardar(Calificacion *obj)
{
    PG *objPG = new PG(conexion.c_str());
    std::stringstream sstm;
    std::string sql;
    unsigned int anno = obj->getAnno();
    const char* codigoEstudiante = obj->getCodigoEstudiante();
    const char* codigoOriginalAsignatura = obj->getCodigoOriginalAsignatura();
    const char* codigoAsignatura = obj->getCodigoAsignatura();
    const char* nombreAsignatura = obj->getNombreAsignatura();
    const char* tipoCursado = obj->getTipoCursado();
    int tipoNumericoCursado = obj->getTipoNumericoCursado();
    unsigned int creditos = obj->getCreditos();
    const char* calificacion = obj->getCalificacion();
    const char* periodo = obj->getPeriodo();
    double calificacionReal = obj->getCalificacionReal();

    sstm << "INSERT INTO calificacion(año,periodo,codigo_estudiante, codigo_asignatura,codigo_asignatura_original, nombre_asignatura, tipo, calificacion,tipo_numerico,creditos,calificacion_numerica) VALUES ("<<anno<<",'"<<periodo<<"','"<<codigoEstudiante<<"','"<<codigoAsignatura<<"','"<<codigoOriginalAsignatura<<"','"<<nombreAsignatura<<"','"<<tipoCursado<<"','"<<calificacion<<"',"<<tipoNumericoCursado<<","<<creditos<<","<<calificacionReal<<");";
    sql = sstm.str();
    //std::cout<<"CalificacionDAO guardar() "<<sql<<std::endl;

    int afectadas = objPG->insert(sql.c_str());
    delete objPG;
    if(afectadas!=1)
    {
        std::cout<<"INSERT ERROR >>>"<<sql<<std::endl;
    }
    return afectadas == 1;
}

bool CalificacionDAO::borrar(Calificacion *obj)
{
    PG *objPG = new PG(conexion.c_str());
    std::stringstream sstm;
    std::string sql;
//    unsigned int anno = obj->getAnno();
    const char* codigoEstudiante = obj->getCodigoEstudiante();
//    const char* codigoOriginalAsignatura = obj->getCodigoOriginalAsignatura();
    const char* codigoAsignatura = obj->getCodigoAsignatura();
 //   const char* nombreAsignatura = obj->getNombreAsignatura();
  //  const char* tipoCursado = obj->getTipoCursado();
   // int tipoNumericoCursado = obj->getTipoNumericoCursado();
    //unsigned int creditos = obj->getCreditos();
    //const char* calificacion = obj->getCalificacion();
    const char* periodo = obj->getPeriodo();
    //double calificacionReal = obj->getCalificacionReal();


    sstm << "DELETE FROM calificacion WHERE periodo = '" <<  periodo << "' AND codigo_asignatura ='"<<codigoAsignatura << "' AND codigo_estudiante = '" << codigoEstudiante << "';";

    sql = sstm.str();
    //std::cout<<"CalificacionDAO borrar() "<<sql<<std::endl;
    int x = objPG->borrar(sql.c_str());

    delete objPG;

    if(x!=1)
    {
        std::cout<<"DELETE ERROR >>>"<<sql<<std::endl;
    }
    return 0 < x;
}

vectorCSV CalificacionDAO::separarComas(std::string asignatura)
{
//std::cout<<"separarComas() "<<asignatura<<std::endl;
    vectorCSV results;

    size_t found;
    found = asignatura.find(",");

    while(found != std::string::npos){

        if(found > 0){
            results.push_back(asignatura.substr(0,found));
        }
        asignatura = asignatura.substr(found+1);
        found = asignatura.find(",");
    }
    if(asignatura.length() > 0){
        results.push_back(asignatura);
    }

    for(unsigned int i=0;i<results.size();i++)
    {
         std::cout<<" "<<results.at(i);
    }
 //std::cout<<"END separarComas() "<<std::endl;
    return results;
}

vectorCSV CalificacionDAO::separarPuntoComas(std::string asignatura)
{
//std::cout<<"separarPuntoComas() "<<asignatura<<std::endl;
    vectorCSV results;

    size_t found;
    found = asignatura.find(";");

    while(found != std::string::npos){

        if(found > 0){
            results.push_back(asignatura.substr(0,found));
        }
        asignatura = asignatura.substr(found+1);
        found = asignatura.find(",");
    }
    if(asignatura.length() > 0){
        results.push_back(asignatura);
    }

    for(unsigned int i=0;i<results.size();i++)
    {
         std::cout<<" "<<results.at(i);
    }
 //std::cout<<"END separarPuntoComas() "<<std::endl;
    return results;
}


std::string CalificacionDAO::formatearComas(std::string asignatura)
{
    vectorCSV results = separarComas(asignatura);
    unsigned int size = results.size();
    std::stringstream sstm;
    for(unsigned int i=0;i<size;i++)
    {
        sstm <<"'"<<results.at(i)<<"'";
        if(i+1<size)
            sstm << ",";
    }

    return sstm.str();
}

VectorCalificaciones* CalificacionDAO::getCalificacionesPorAsignatura(std::string asignatura)
{
    //std::cout<<"getCalificacionesPorAsignatura()"<<std::endl;
    VectorCalificaciones *califaciones = new VectorCalificaciones();
    PG *objPG = new PG(conexion.c_str());
    std::string sql ="SELECT año ,periodo,codigo_estudiante   ,codigo_asignatura_original  ,codigo_asignatura  ,nombre_asignatura  ,tipo  ,tipo_numerico ,calificacion  ,creditos ,calificacion_numerica  FROM calificacion WHERE codigo_asignatura = "+formatearComas(asignatura)+" ORDER BY codigo_estudiante";
    ResultadoConsulta *resultado = objPG->select(sql.c_str());
    //std::cout<<"SQL "<< sql <<std::endl;
    //std::cout<<"CANTIDAD CALIFICACIONES "<<resultado->size()<<std::endl;
    for(unsigned int i=0;i<resultado->size();i++)
    {
        ResultadoFila unaFila= resultado->at(i);
        Calificacion *unaCalificacion = new Calificacion();
        unaCalificacion->setAnno(atoi(unaFila.at(0)));
        unaCalificacion->setPeriodo(unaFila.at(1));
        unaCalificacion->setCodigoEstudiante(unaFila.at(2));
        unaCalificacion->setCodigoOriginalAsignatura(unaFila.at(3));
        unaCalificacion->setCodigoAsignatura(unaFila.at(4));
        unaCalificacion->setNombreAsignatura(unaFila.at(5));
        unaCalificacion->setTipoCursado(unaFila.at(6));
        unaCalificacion->setTipoNumericoCursado(atoi(unaFila.at(7)));
        unaCalificacion->setCalificacion(unaFila.at(8));
        unaCalificacion->setCreditos(atoi(unaFila.at(9)));
        unaCalificacion->setCalificacionReal(atof(unaFila.at(10)));

        califaciones->push_back(unaCalificacion);
    }
    delete objPG;
    return califaciones;
}

VectorCalificaciones* CalificacionDAO::getCalificacionesOrdenasPorTipo()
{
    VectorCalificaciones *califaciones = new VectorCalificaciones();
    PG *objPG = new PG(conexion.c_str());

    std::string sql ="SELECT año,periodo,codigo_estudiante,codigo_asignatura,codigo_asignatura_original,nombre_asignatura,tipo,tipo_numerico,calificacion,creditos,calificacion_numerica FROM calificacion ORDER BY tipo_numerico;";

    ResultadoConsulta *resultado = objPG->select(sql.c_str());
    for(unsigned int i=0;i<resultado->size();i++)
    {
        ResultadoFila unaFila= resultado->at(i);
        Calificacion *unaCalificacion = new Calificacion();
        unaCalificacion->setAnno(atoi(unaFila.at(0)));
        unaCalificacion->setPeriodo(unaFila.at(1));
        unaCalificacion->setCodigoEstudiante(unaFila.at(2));
        unaCalificacion->setCodigoAsignatura(unaFila.at(3));
        unaCalificacion->setCodigoOriginalAsignatura(unaFila.at(4));
        unaCalificacion->setNombreAsignatura(unaFila.at(5));
        unaCalificacion->setTipoCursado(unaFila.at(6));
        unaCalificacion->setTipoNumericoCursado(atoi(unaFila.at(7)));
        unaCalificacion->setCalificacion(unaFila.at(8));
        unaCalificacion->setCreditos(atoi(unaFila.at(9)));
        unaCalificacion->setCalificacionReal(atof(unaFila.at(10)));

        califaciones->push_back(unaCalificacion);
    }
    return califaciones;
}

void CalificacionDAO::crearTablas()
{
    PG *objPg = new PG(conexion.c_str());
    objPg->query("DROP TABLE IF EXISTS calificacion;");
    objPg->query("CREATE TABLE calificacion(año integer,periodo character varying,codigo_estudiante character varying,codigo_asignatura_original character varying,codigo_asignatura character varying,nombre_asignatura character varying,tipo character varying,tipo_numerico integer,calificacion character varying,creditos integer,calificacion_numerica real,CONSTRAINT calificacion_pkey PRIMARY KEY (periodo,codigo_asignatura,codigo_estudiante));");
}

const char* CalificacionDAO::insertar(encabezadoCSV encabezados,datosCSV datosIn,wxGauge *barraProgreso)
{
    PG *objPg = new PG(conexion.c_str());
    int columna_periodo=-1,columna_estudiante = -1,columna_codigo = -1,columna_asignatura = -1,columna_tipo = -1,columna_creditos = -1,columna_calificacion = -1,columna_habilitacion = -1,i = 0,j=0,ntipo=0,afectadas = 0,correctas = 0,incorrectas = 0;
    std::string anno,estudiante,codigo,asignatura,tipo,creditos,habilitacion,cal,calificacion,periodo,sql;
    float calificacionNumerica;
    std::stringstream sstm;


    barraProgreso->SetRange(datosIn.size());

    for (encabezadoCSV::iterator it = encabezados.begin(); it != encabezados.end(); it++,i++){
        std::string stringIt =  *it;
        stringIt = limpiarString(stringIt);
        if(stringIt.find("estudiante")==0)columna_estudiante=i;
        if(stringIt.find("periodo")==0)columna_periodo=i;
        if(stringIt.find("codigo")==0)columna_codigo=i;
        if(stringIt.find("asignatura")==0)columna_asignatura=i;
        if(stringIt.find("tipo")==0)columna_tipo=i;
        if(stringIt.find("crd")==0)columna_creditos=i;
        if(stringIt.find("calificacion")==0)columna_calificacion=i;
        if(stringIt.find("calif")==0)columna_calificacion=i;
        if(stringIt.find("hab")==0)columna_habilitacion=i;
    }

    i=1;

    for (datosCSV::iterator it = datosIn.begin(); it != datosIn.end(); it++,i++){
        j=0;
        barraProgreso->SetValue(i);
        anno.clear();estudiante.clear();codigo.clear();asignatura.clear();tipo.clear();calificacion.clear();creditos.clear();habilitacion.clear();cal.clear();periodo.clear();
        for (listaCSV::iterator it2 = it->begin(); it2 != it->end(); it2++,j++){
            if(j ==  columna_estudiante) estudiante = *it2;
            if(j ==  columna_codigo) codigo = *it2;
            if(j ==  columna_asignatura) asignatura = *it2;
            if(j ==  columna_tipo) tipo = *it2;
            if(j ==  columna_calificacion) calificacion =*it2;
            if(j ==  columna_creditos) creditos = *it2;
            if(j ==  columna_habilitacion) habilitacion = *it2;
            if(j == columna_periodo) periodo = *it2;
        }

        if(0 == creditos.size())creditos = "NULL";
        if(0 == tipo.compare("VALIDACION")) ntipo =(0 == habilitacion.size())? 1 : 2;
        if(0 == tipo.compare("EXIMIDO EXAMEN CLASF"))ntipo = (0 == habilitacion.size())? 3 : 4;
        if(0 == tipo.compare("EQUIVALENCIA"))ntipo = (0 == habilitacion.size())? 5 : 6;
        if(0 == tipo.compare("PROFIC. EN IDIOMA EXTRANJERO"))ntipo = (0 == habilitacion.size())? 7 : 8;
        if(0 == tipo.compare("NORMAL"))ntipo = (0 == habilitacion.size())? 9 : 10;
        if(0 == tipo.compare("REPETICION")) ntipo = (0 == habilitacion.size())? 11 : 12;
        if(0 == tipo.compare("SEGUNDA REPETICION")) ntipo = (0 == habilitacion.size())? 13 : 14;

        if(ntipo % 2 == 0){
            tipo = "HABILITACION "+tipo;
            calificacion = habilitacion;
        }

        setlocale(LC_ALL,"C");

        if(calificacion.size() > 0){
            calificacionNumerica = atof(calificacion.c_str());
            anno=estudiante.substr(0,4);
            sstm << "INSERT INTO calificacion(año,periodo,codigo_estudiante, codigo_asignatura,codigo_asignatura_original, nombre_asignatura, tipo, calificacion,tipo_numerico,creditos,calificacion_numerica) VALUES ("<<anno<<",'"<<periodo<<"','"<<encriptar(estudiante)<<"','"<<codigo<<"','"<<codigo<<"','"<<asignatura<<"','"<<tipo<<"','"<<calificacion<<"',"<<ntipo<<","<<creditos<<","<<calificacionNumerica<<");";
            sql = sstm.str();
            sstm.str(std::string());

            afectadas = objPg->insert(sql.c_str());


            if(0==afectadas){
                std::cout<<i<<" "<<sql.c_str()<<std::endl;
                incorrectas++;
            }else{
                correctas++;
            }
        }
    }

    sstm << "Se insertaron " << correctas <<" calificaciones ";
    if(incorrectas>0)
        sstm <<", "<<incorrectas<<" incorrectas";

    return sstm.str().c_str();
}

listaCSV* CalificacionDAO::getListadoAsignaturas()
{
    PG *objPg = new PG(conexion.c_str());
    ResultadoConsulta *resultado =  objPg->select("SELECT DISTINCT codigo_asignatura FROM calificacion ORDER BY codigo_asignatura DESC;");
    ///Creo que el order by no es necesario, EDIT si es necesario para el orden de las columnas de la tabla estudiante
    /// DESC por que guardo en una lista al reves, mejor vector?
    listaCSV *listado = new listaCSV();
    for(unsigned int i=0;i<resultado->size();i++)
    {
        ResultadoFila unaFila= resultado->at(i);
        listado->push_back(unaFila.at(0));
    }
    return listado;
}


PromediosDeEstudiantes* CalificacionDAO::getPromediosDeEstudiantes()
{
    PG *objPg = new PG(conexion.c_str());
    ResultadoConsulta *resultado =  objPg->select("SELECT codigo_estudiante,SUM(calificacion_numerica*creditos)/SUM(creditos) as b FROM calificacion WHERE creditos is not null AND creditos!= 0  AND calificacion !='A.P'  AND calificacion !='C.U' AND calificacion !='A.P' AND calificacion !='E' AND calificacion !='E.X' AND calificacion !='I.C' AND calificacion !='L.A' AND calificacion !='M.E' AND calificacion !='N.A' AND calificacion !='N.C' AND calificacion !='P.D'  AND calificacion !='P.P'  GROUP BY codigo_estudiante ORDER BY codigo_estudiante");
    PromediosDeEstudiantes *listado = new PromediosDeEstudiantes();

    for(unsigned int i=0;i<resultado->size();i++)
    {
        ResultadoFila unaFila= resultado->at(i);
        listado->insert(std::pair<const char*,const char*>(unaFila.at(0),unaFila.at(1)));
    }
    delete objPg;
    delete resultado;
    return listado;

}


