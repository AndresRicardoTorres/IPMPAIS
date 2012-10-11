/***************************************************************
 * Name:      PuntajesMinimosMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "PuntajesMinimosMain.h"

PuntajesMinimosFrame::PuntajesMinimosFrame(wxFrame *frame)
    : GUIFrame(frame)
{
    ///Inicializo los dialogos que se utilizaran
    dialogo_configuracion_base_datos = new ConfBDDialog(0L);
    dialogo_asignaturas = new DialogoAsignaturas(0L);
    ///Inicializo los filtros de la aplicacion
    filtro_completitud_datos = 1;
    filtro_fecha_inicio = 0;
    filtro_fecha_final = 0;
    listadoAsignaturas = "";
    ///Miro si hay conexion a la base de datos, para colocarlo en la barra de estado
    checkDB();

#if CODIGOS_ENCRIPTADOS
    ///Inicializo el numero aleatorio para la encriptacion
    srand(time(0));  // Initialize random number generator.
    un_numero_aleatorio = rand();
#endif
    //grilla_puntajes_minimos->Show(false);
}

const char* PuntajesMinimosFrame::getInformacionConexion(){
    string conexion = dialogo_configuracion_base_datos->getInformacion();
    //std::cout<<"getInformacionConexion() "<<conexion<<std::endl;
    return conexion.c_str();
}

bool PuntajesMinimosFrame::checkDB(){
    const char* BORAR = getInformacionConexion();
    //std::cout<<"checkDB()46 "<<BORAR<<std::endl;
    PG *objPg = new PG(BORAR);
    //std::cout<<"checkDB()48 "<<BORAR<<std::endl;
    bool hayBD = objPg->checkStatus();

#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("Bienvenido!"), 0);
    if(hayBD)
    statusBar->SetStatusText(_("Conectado a la base de datos !"), 1);
    else
    statusBar->SetStatusText(_("No conectado con la base de datos !"), 1);
#endif
    actualizarCantidadMuestra();
    return hayBD;
}

PuntajesMinimosFrame::~PuntajesMinimosFrame()
{
    ///Elimino los dialogos que cree
    delete dialogo_configuracion_base_datos;
    delete dialogo_asignaturas;
}

bool PuntajesMinimosFrame::comprobarConexionBD()
{
    if(!checkDB()){
        wxMessageBox( _("Configure la conexión a la base de datos"),_("Error"));
        dialogo_configuracion_base_datos->Show();
        return false;
    }
    return true;
}

bool PuntajesMinimosFrame::cargarArchivo(int opcion){
    if(!comprobarConexionBD())
        return false;
    wxString titulo,tipoArchivo;
    switch(opcion){
        case 1:
            titulo = _("Abrir archivo .CSV");
            tipoArchivo = _("Archivo de valores separados por comas (*.csv)|*.csv");
        break;
        case 2:
            titulo = _("Abrir archivo .YAML");
            tipoArchivo = _("*.yaml");
        break;
    }

    wxFileDialog openFileDialog(this,titulo, wxT(""), wxT(""),tipoArchivo, wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) return false;     // the user changed idea...
    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxMessageBox((wxT("Cannot open file ")+openFileDialog.GetPath()),_("Error"));
        return false;
    }
    // assuming you want UTF-8, change the wxConv* parameter as needed
    strncpy(filename, (const char*)openFileDialog.GetPath().mb_str(wxConvUTF8), 1023);
    return true;
}


void PuntajesMinimosFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void PuntajesMinimosFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void PuntajesMinimosFrame::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc(panel_grafico);

    //dc.DrawText(wxT("Лев Николaевич Толстoй"), 40, 60);
    //dc.DrawText(wxT("Анна Каренина"), 70, 80);
}

void PuntajesMinimosFrame::OnAbout(wxCommandEvent &event)
{
//    wxString msg = wxbuildinfo(long_f);
//
}

void PuntajesMinimosFrame::OnBDConfig(wxCommandEvent &event)
{
    dialogo_configuracion_base_datos->Show();
}


void PuntajesMinimosFrame::cargarInformacionAdmisiones( wxCommandEvent& event )
{
    if(cargarArchivo(1)){
        statusBar->SetStatusText(_("Leyendo archivo de admisiones ...."), 0);
        ///Leo el archivo
        LeerCSV *objLectorCSV = new LeerCSV(filename);
        encabezadoCSV encabezados = objLectorCSV->leerEncabezado();
        datosCSV datosIn = objLectorCSV->leerDatos();

        ///Borro y creo las tablas e inserto los datos
        EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
        objEstudiantes->crearTablas();
        const char* resultado = objEstudiantes->insertar(encabezados,datosIn,progresoAdmisiones);
        informar(resultado);
    }
}

void PuntajesMinimosFrame::CagarPuntajesICFES( wxCommandEvent& event )
{
    if(cargarArchivo(1)){
        statusBar->SetStatusText(_("Leyendo archivo de puntajes del ICFES ...."), 0);
        ///Leo el archivo
        LeerCSV *objLectorCSV = new LeerCSV(filename);
        encabezadoCSV encabezados = objLectorCSV->leerEncabezado();
        datosCSV datosIn = objLectorCSV->leerDatos();

        EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
        const char* resultado = objEstudiantes->insertarICFES(encabezados,datosIn,progresoICFES);
        informar(resultado);
    }
}

void PuntajesMinimosFrame::cargarInformacionEquivalencias( wxCommandEvent& event )
{
    ///2 por que es un archivo YAML
     if(cargarArchivo(2)){
        statusBar->SetStatusText(_("Leyendo archivo de equivalencias ...."), 0);
        ///Leo el archivo
        LeeYaml *objLector = new LeeYaml(filename);

        list<list<string> > anteriores=objLector->getAnteriores();
        list<list<string> > nuevas=objLector->getNuevas();

        EquivalenciaDAO *objEquivalencias = new EquivalenciaDAO(getInformacionConexion());
        objEquivalencias->crearTablas();

        const char* resultado = objEquivalencias->insertar(anteriores,nuevas,progresoEquivalencias);
        informar(resultado);
    }
}


void PuntajesMinimosFrame::informar(const char* mensaje)
{
    std::cout<<mensaje<<std::endl;
    wxString wxMensaje = wxString(mensaje,wxConvUTF8);
    statusBar->SetStatusText(wxMensaje, 0);
    //wxMessageBox(wxMensaje, _("Resultado"));
}

void PuntajesMinimosFrame::cargarInformacionRegistroAcademico( wxCommandEvent& event )
{
    if(cargarArchivo(1)){
        const char* resultado;
        wxString wxResultado;
        EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
        CalificacionDAO *objCalificaciones = new CalificacionDAO(getInformacionConexion());

        statusBar->SetStatusText(_("Leyendo archivo de registro academico ...."), 0);
        ///Leo el archivo

        LeerCSV *objLectorCSV = new LeerCSV(filename);
        encabezadoCSV encabezados = objLectorCSV->leerEncabezado();
        datosCSV datosIn = objLectorCSV->leerDatos();


        ///Creo las tablas

        std::cout<<"Creo las tablas"<<std::endl;
        objCalificaciones->crearTablas();

        ///Inserto todas las notas

std::cout<<"Inserto todas las notas"<<std::endl;

        resultado = objCalificaciones->insertar(encabezados,datosIn,progresoRegistro);
        informar(resultado);

        ///Aplico las equivalencias
        std::cout<<"Aplico las equivalencias"<<std::endl;
        EquivalenciaDAO *objEquivalencias = new EquivalenciaDAO(getInformacionConexion());


        VectorEquivalencias *listadoEquivalencias = objEquivalencias->getEquivalencias();
        resultado = objCalificaciones->aplicarEquivalencias(listadoEquivalencias);

        informar(resultado);


        ///Crear columnas de tablas con codigos de asigantruas en las tablas de informacion de estudiantes

        listaCSV *listadoCodigoAsignaturas = objCalificaciones->getListadoAsignaturas();

        std::cout<<"Cantidad asignaturas despues de equivalencia : "<<(listadoCodigoAsignaturas->size())<<std::endl;



        while (!listadoCodigoAsignaturas->empty())
        {
            objEstudiantes->crearColumnasAsignaturas(listadoCodigoAsignaturas->back());
            listadoCodigoAsignaturas->pop_back();
        }

        ///Copiar datos de la tabla calificaciones a la de estudiantes con las equivalencias ya aplicadas
        std::cout<<"Copiando calificaciones"<<std::endl;
        VectorCalificaciones *todasLasNotas = objCalificaciones->getCalificacionesOrdenasPorTipo();
        int correctas = 0,incorrectas = 0;

        std::cout<<"todasLasNotas->size() "<<todasLasNotas->size()<<std::endl;

        for(unsigned int i=0;i<todasLasNotas->size();i++)
        {
            if(objEstudiantes->actualizar(todasLasNotas->at(i)))
            {
                correctas++;
            }
            else
            {
                incorrectas++;
            }
        }

        std::stringstream respuesta;
        respuesta << "Se insertaron " << correctas <<" calificaciones";
        if(incorrectas>0)
            respuesta <<", "<<incorrectas<<" incorrectos";

        informar(respuesta.str().c_str());

        ///Calculo los promedios con las califiaciones
std::cout<<"Calculando Promedios"<<std::endl;

        objEstudiantes->crearColumnasPromedio();

        resultado = objEstudiantes->actualizarPromedio(objCalificaciones->getPromediosDeEstudiantes());
        informar(resultado);

        statusBar->SetStatusText(_("Carga Finalizada"), 0);
    }
}

void PuntajesMinimosFrame::cargarInformacionECAES( wxCommandEvent& event )
{
    if(cargarArchivo(1)){
        statusBar->SetStatusText(_("Leyendo archivo de ECAES ...."), 0);
        LeerCSV *objLectorCSV = new LeerCSV(filename);
        listaCSV encabezados = objLectorCSV->leerEncabezado();
        datosCSV datosIn = objLectorCSV->leerDatos();

        EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
        std::string resultado = objEstudiantes->insertarPuntajesECAES(encabezados,datosIn,progresoECAES);
        informar(resultado.c_str());
    }
}


void PuntajesMinimosFrame::OnRadioBoxFiltroCompletitud( wxCommandEvent& event ){
    filtro_completitud_datos = radioBox_filtro_completitud->GetSelection();
}

void PuntajesMinimosFrame::actualizarCantidadMuestra(){
   ///Consulto cuantos estudiantes hay actualmente para tener actualizado al usuario
    EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
    listaCSV *listadoCodigoEstudiantes = objEstudiantes->getListaEstudiantesOrdenadaPorPromedio(filtro_fecha_inicio,filtro_fecha_final);
    cantidad_estudiantes_filtrados = listadoCodigoEstudiantes->size();
    label_cantidad->SetLabel(wxString::Format(wxT("Total de la muestra : %i estudiantes"),cantidad_estudiantes_filtrados));
    wxString cantidad = wxString::Format(wxT("%i"),listadoCodigoEstudiantes->size());
    statusBar->SetStatusText(cantidad+_(" estudiantes selecionados"), 0);
}

void PuntajesMinimosFrame::actualizarFiltroFechaInicio( wxCommandEvent& event )
{
    filtro_fecha_inicio = wxAtoi(input_fecha_desde->GetValue());
    actualizarCantidadMuestra();
}

void PuntajesMinimosFrame::actualizarFiltroFechaFin( wxCommandEvent& event )
{
    filtro_fecha_final = wxAtoi(input_fecha_hasta->GetValue());
    actualizarCantidadMuestra();

}


 void PuntajesMinimosFrame::mostar_puntajes_minimos( wxCommandEvent& event ){
///TODO: mosttar o ocultar inputs
//    bool soloCalcularPonderaciones = !check_mostrar_puntajes_minimos->IsChecked();
/*
    if(soloCalcularPonderaciones)
        grilla_puntajes_minimos->Show(false);
    else
        grilla_puntajes_minimos->Show(true);
        */

 }

// 2012-09-28: Función alterada por Angel, para no tener en cuenta PuntajesMinimos(=0) y para repetir
// varias veces el AG, obteniendo el promedio y la desviación típica de las ponderaciones.
#include <math.h>
void PuntajesMinimosFrame::BotonBuscar( wxCommandEvent& event ){
  // ?? Imprimir en GUI el número de estudiantes despues del filtro
    if(!comprobarConexionBD())
        return;

    bool soloCalcularPonderaciones = !check_mostrar_puntajes_minimos->IsChecked();  // ??? Obtener esta información de la GUI (y modificar la GUI en función de ello poniendo dos columnas más para PuntajesMinimosPromedio y PuntajesMinimosDesviacionTipica) */

    AdmisionesUnivalle admisionesUnivalle(getInformacionConexion(),filtro_fecha_inicio,filtro_fecha_final);

    EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
    int cuantosComponentesExamenIngreso = 7;
    double puntajeMinimo_minimo =  0;
    double puntajeMinimo_maximo = 120; //El maximo que he visto es 116.95
    double ponderacion_minimo = 0;
    double ponderacion_maximo = 100;

    listaCSV *listadoCodigoEstudiantes = objEstudiantes->getListaEstudiantesOrdenadaPorPromedio(filtro_fecha_inicio,filtro_fecha_final);
    int cuantosEgresados = listadoCodigoEstudiantes->size();
    const char **listaEgresadosOrdenada = new const char*[cuantosEgresados];
    int i=0;
    for (listaCSV::iterator it = listadoCodigoEstudiantes->begin(); it != listadoCodigoEstudiantes->end(); it++,i++)
    {
        std::string stringIt =  *it;
        listaEgresadosOrdenada[i] = stringIt.c_str();
    }

    int veces=wxAtoi(input_numero_iteraciones->GetValue());  // ??? Obtener este valor de la GUI */

    double vectorPuntajesMinimos[veces][cuantosComponentesExamenIngreso];
    double vectorPonderaciones[veces][cuantosComponentesExamenIngreso];
    double vectorAptitudes[veces];
    for(int vez=0; vez<veces; vez++)
    {
        FenotipoIPMPAIS *fenotipo=new FenotipoIPMPAIS(cuantosComponentesExamenIngreso, puntajeMinimo_minimo, puntajeMinimo_maximo, ponderacion_minimo, ponderacion_maximo, admisionesUnivalle, listaEgresadosOrdenada, cuantosEgresados, soloCalcularPonderaciones);
        double puntajesMinimos[cuantosComponentesExamenIngreso];  // Array vacío
        double ponderaciones[cuantosComponentesExamenIngreso];  // Array vacío
        AlgoritmoGenetico algoritmoGenetico(fenotipo);
        double aptitud;
        fenotipo->expresar(algoritmoGenetico.ejecutar(aptitud, 100000), puntajesMinimos, ponderaciones);
        vectorAptitudes[vez] = aptitud;
        for(int i=0; i<cuantosComponentesExamenIngreso; i++)
        {
          vectorPuntajesMinimos[vez][i] = puntajesMinimos[i];
          vectorPonderaciones[vez][i] = ponderaciones[i];
        }
        delete fenotipo;
        fenotipo=0;
    }

    double puntajesMinimosPromedio[cuantosComponentesExamenIngreso];  // Array vacío
    double puntajesMinimosDesviacionTipica[cuantosComponentesExamenIngreso];  // Array vacío
    double ponderacionesPromedio[cuantosComponentesExamenIngreso];  // Array vacío
    double ponderacionesDesviacionTipica[cuantosComponentesExamenIngreso];  // Array vacío

    for(int i=0; i<cuantosComponentesExamenIngreso; i++)
    {
      puntajesMinimosPromedio[i] = 0;
      ponderacionesPromedio[i] = 0;
      puntajesMinimosDesviacionTipica[i] = 0;
      ponderacionesDesviacionTipica[i] = 0;
      for(int vez=0; vez<veces; vez++)
      {
          puntajesMinimosPromedio[i] += vectorPuntajesMinimos[vez][i];
          ponderacionesPromedio[i] += vectorPonderaciones[vez][i];
          puntajesMinimosDesviacionTipica[i] += vectorPuntajesMinimos[vez][i] * vectorPuntajesMinimos[vez][i];
          ponderacionesDesviacionTipica[i] += vectorPonderaciones[vez][i] * vectorPonderaciones[vez][i];
      }
      puntajesMinimosPromedio[i] /= veces;
      ponderacionesPromedio[i] /= veces;
      puntajesMinimosDesviacionTipica[i] = sqrt(puntajesMinimosDesviacionTipica[i] / veces - puntajesMinimosPromedio[i] * puntajesMinimosPromedio[i]);
      ponderacionesDesviacionTipica[i] = sqrt(ponderacionesDesviacionTipica[i] / veces - ponderacionesPromedio[i] * ponderacionesPromedio[i]);
    }

    double aptitudPromedio = 0;
    double aptitudDesviacionTipica = 0;
    for(int vez=0; vez<veces; vez++)
    {
        aptitudPromedio += vectorAptitudes[vez];
        std::cout<<"vectorAptitudes "<<vectorAptitudes[vez]<<std::endl;
        aptitudDesviacionTipica += vectorAptitudes[vez] * vectorAptitudes[vez];
    }
    aptitudPromedio /= veces;
    aptitudDesviacionTipica = sqrt(aptitudDesviacionTipica / veces - aptitudPromedio * aptitudPromedio);
    /* ??? Imprimir en GUI aptitudPromedio y aptitudDesviacionTipica */

    if(not soloCalcularPonderaciones)
    {
      /* ??? Imprimir en GUI puntajesMinimosPromedio y puntajesMinimosDesviacionTipica */

        inputPonderacionLenguaje->SetValue(wxString::Format(wxT("%f"),puntajesMinimosPromedio[0]));
        inputPonderacionMatematica->SetValue(wxString::Format(wxT("%f"),puntajesMinimosPromedio[1]));
        inputPonderacionSociales->SetValue(wxString::Format(wxT("%f"),puntajesMinimosPromedio[2]));
        inputPonderacionFilosofia->SetValue(wxString::Format(wxT("%f"),puntajesMinimosPromedio[3]));
        inputPonderacionBiologia->SetValue(wxString::Format(wxT("%f"),puntajesMinimosPromedio[4]));
        inputPonderacionQuimica->SetValue(wxString::Format(wxT("%f"),puntajesMinimosPromedio[5]));
        inputPonderacionFisica->SetValue(wxString::Format(wxT("%f"),puntajesMinimosPromedio[6]));

        inputDPonderacionLenguaje->SetValue(wxString::Format(wxT("%f"),puntajesMinimosDesviacionTipica[0]));
        inputDPonderacionMatematica->SetValue(wxString::Format(wxT("%f"),puntajesMinimosDesviacionTipica[1]));
        inputDPonderacionSociales->SetValue(wxString::Format(wxT("%f"),puntajesMinimosDesviacionTipica[2]));
        inputDPonderacionFilosofia->SetValue(wxString::Format(wxT("%f"),puntajesMinimosDesviacionTipica[3]));
        inputDPonderacionBiologia->SetValue(wxString::Format(wxT("%f"),puntajesMinimosDesviacionTipica[4]));
        inputDPonderacionQuimica->SetValue(wxString::Format(wxT("%f"),puntajesMinimosDesviacionTipica[5]));
        inputDPonderacionFisica->SetValue(wxString::Format(wxT("%f"),puntajesMinimosDesviacionTipica[6]));

    }

    double suma = 0;
    for(int i=0; i<cuantosComponentesExamenIngreso; i++)
    {
        suma+=ponderacionesPromedio[i];

        //std::cout<<"ponderacionesPromedio "<<ponderacionesPromedio[i]<<std::endl;
        //std::cout<<"ponderacionesDesviacionTipica "<<ponderacionesDesviacionTipica[i]<<std::endl;
    }

    for(int i=0; i<cuantosComponentesExamenIngreso; i++)
    {
      ponderacionesPromedio[i]=ponderacionesPromedio[i]*100/suma;
      ponderacionesDesviacionTipica[i]=ponderacionesDesviacionTipica[i]*100/suma;
    }

    inputPuntajeLenguaje->SetValue(wxString::Format(wxT("%f"),ponderacionesPromedio[0]));
    inputPuntajeMatematica->SetValue(wxString::Format(wxT("%f"),ponderacionesPromedio[1]));
    inputPuntajeSociales->SetValue(wxString::Format(wxT("%f"),ponderacionesPromedio[2]));
    inputPuntajeFilosofia->SetValue(wxString::Format(wxT("%f"),ponderacionesPromedio[3]));
    inputPuntajeBiologia->SetValue(wxString::Format(wxT("%f"),ponderacionesPromedio[4]));
    inputPuntajeQuimica->SetValue(wxString::Format(wxT("%f"),ponderacionesPromedio[5]));
    inputPuntajeFisica->SetValue(wxString::Format(wxT("%f"),ponderacionesPromedio[6]));

    inputDPuntajeLenguaje->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[0]));
    inputDPuntajeMatematica->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[1]));
    inputDPuntajeSociales->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[2]));
    inputDPuntajeFilosofia->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[3]));
    inputDPuntajeBiologia->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[4]));
    inputDPuntajeQuimica->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[5]));
    inputDPuntajeFisica->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[6]));

    inputPromedio->SetValue(wxString::Format(wxT("%f"),aptitudPromedio));
    inputDesviacionPromedio->SetValue(wxString::Format(wxT("%f"),aptitudDesviacionTipica));
}
