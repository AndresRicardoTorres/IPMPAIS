/***************************************************************
 * Name:      PuntajesMinimosMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Modified:  2013-03-25 by Angel García
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:   GPL
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(wxFrame *frame)
    : GUIFrame(frame)
{

    cuantosComponentesExamenIngreso = 7;
    puntajeMinimo_minimo =  0;
    puntajeMinimo_maximo = 120; //El maximo que he visto es 116.95
    ponderacion_minimo = 0;
    ponderacion_maximo = 100;


    ///Inicializo los dialogos que se utilizaran
    dialogo_configuracion_base_datos = new ConfBDDialog(0L);
    dialogo_ecaes = new DialogoEcaes(0L);
    ///Inicializo los filtros de la aplicacion
    filtro_completitud_datos = 1;
    filtro_fecha_inicio = 0;
    filtro_fecha_final = 0;
    listadoAsignaturas = "";
    ///Miro si hay conexion a la base de datos, para colocarlo en la barra de estado
    checkDB();
    actualizarInterfaz();
    wxCommandEvent CE;
    OnRadioBoxComparar(CE);
}

const char* VentanaPrincipal::getInformacionConexion(){
    string conexion = dialogo_configuracion_base_datos->getInformacion();
    return conexion.c_str();
}

bool VentanaPrincipal::checkDB(){
    const char* BORAR = getInformacionConexion();

    PG *objPg = new PG(BORAR);

    bool hayBD = objPg->checkStatus();

#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("Bienvenido!"), 0);
    if(hayBD)
    statusBar->SetStatusText(_("Conectado a la base de datos !"), 1);
    else
    statusBar->SetStatusText(_("No conectado con la base de datos !"), 1);
#endif

    if(hayBD){
        actualizarCantidadMuestra();
    }
    boton_buscar->Enable(hayBD);
    button_guardar_datos->Enable(hayBD);
    return hayBD;
}

VentanaPrincipal::~VentanaPrincipal()
{
    ///Elimino los dialogos que cree
    delete dialogo_configuracion_base_datos;
    delete dialogo_ecaes;
}

bool VentanaPrincipal::comprobarConexionBD()
{
    if(!checkDB()){
        wxMessageBox( _("Configure la conexión a la base de datos"),_("Error"));
        dialogo_configuracion_base_datos->Show();
        return false;
    }
    return true;
}

bool VentanaPrincipal::cargarArchivo(){

    if(!comprobarConexionBD())
        return false;

    wxFileDialog openFileDialog(this,_("Abrir archivo .CSV"), wxT(""), wxT(""), _("Archivo de valores separados por comas (*.csv)|*.csv"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

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


void VentanaPrincipal::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void VentanaPrincipal::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void VentanaPrincipal::OnAbout(wxCommandEvent &event)
{
//    wxString msg = wxbuildinfo(long_f);
//
}

void VentanaPrincipal::OnBDConfig(wxCommandEvent &event)
{
    dialogo_configuracion_base_datos->Show();
}


void VentanaPrincipal::cargarInformacionAdmisiones( wxCommandEvent& event )
{
    if(cargarArchivo()){
        statusBar->SetStatusText(_("Leyendo archivo de admisiones ...."), 0);
        ///Leo el archivo
        CSV *objLectorCSV = new CSV(filename);
        encabezadoCSV encabezados = objLectorCSV->leerEncabezado();
        datosCSV datosIn = objLectorCSV->leerDatos();

        ///Borro y creo las tablas e inserto los datos
        EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
        objEstudiantes->crearTablas();
        const char* resultado = objEstudiantes->insertar(encabezados,datosIn,progresoAdmisiones);
        informar(resultado);
    }
}

void VentanaPrincipal::CagarPuntajesICFES( wxCommandEvent& event )
{
    if(cargarArchivo()){
        statusBar->SetStatusText(_("Leyendo archivo de puntajes del ICFES ...."), 0);
        ///Leo el archivo
        CSV *objLectorCSV = new CSV(filename);
        encabezadoCSV encabezados = objLectorCSV->leerEncabezado();
        datosCSV datosIn = objLectorCSV->leerDatos();

        EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
        const char* resultado = objEstudiantes->insertarICFES(encabezados,datosIn,progresoICFES);
        informar(resultado);
    }
}

void VentanaPrincipal::cargarInformacionEquivalencias( wxCommandEvent& event )
{

     if(cargarArchivo()){
        statusBar->SetStatusText(_("Leyendo archivo de equivalencias ...."), 0);
        ///Leo el archivo
        CSV *objLectorCSV = new CSV(filename);

        encabezadoCSV encabezados = objLectorCSV->leerEncabezado();
        datosCSV datosIn = objLectorCSV->leerDatos();

        EquivalenciaDAO *objEquivalencias = new EquivalenciaDAO(getInformacionConexion());
        objEquivalencias->crearTablas();

        const char* resultado = objEquivalencias->insertar(encabezados,datosIn,progresoEquivalencias);
        informar(resultado);
    }
}


void VentanaPrincipal::informar(const char* mensaje)
{
    std::cout<<mensaje<<std::endl;
    wxString wxMensaje = wxString(mensaje,wxConvUTF8);
    statusBar->SetStatusText(wxMensaje, 0);
    //wxMessageBox(wxMensaje, _("Resultado"));
}

void VentanaPrincipal::cargarInformacionRegistroAcademico( wxCommandEvent& event )
{
    if(cargarArchivo()){
        const char* resultado;
        wxString wxResultado;
        EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
        CalificacionDAO *objCalificaciones = new CalificacionDAO(getInformacionConexion());

        statusBar->SetStatusText(_("Leyendo archivo de registro academico ...."), 0);
        ///Leo el archivo

        CSV *objLectorCSV = new CSV(filename);
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
        statusBar->SetStatusText(_("Carga Finalizada"), 0);
    }
}

void VentanaPrincipal::cargarInformacionECAES( wxCommandEvent& event )
{
    if(cargarArchivo()){
        statusBar->SetStatusText(_("Leyendo archivo de ECAES ...."), 0);
        CSV *objLectorCSV = new CSV(filename);
        listaCSV encabezados = objLectorCSV->leerEncabezado();
        datosCSV datosIn = objLectorCSV->leerDatos();

        EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
        std::string resultado = objEstudiantes->insertarPuntajesECAES(encabezados,datosIn,progresoECAES);
        informar(resultado.c_str());
    }
}



void VentanaPrincipal::actualizarCantidadMuestra(){
   ///Consulto cuantos estudiantes hay actualmente para tener actualizado al usuario


    bool ECAESoRegistro = radio_comparacion->GetSelection() != 0;

    opcionesEcaes = dialogo_ecaes->getOpciones();
    EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
    listaCSV *listadoCodigoEstudiantes = objEstudiantes->getListaEstudiantesOrdenadaPorPromedio(filtro_fecha_inicio,filtro_fecha_final,ECAESoRegistro?opcionesEcaes:listadoAsignaturas,ECAESoRegistro);
    delete objEstudiantes;


    cantidad_estudiantes_filtrados = listadoCodigoEstudiantes->size();
    label_cantidad->SetLabel(wxString::Format(wxT("Total de la muestra : %i estudiantes"),cantidad_estudiantes_filtrados));
    wxString cantidad = wxString::Format(wxT("%i"),cantidad_estudiantes_filtrados);
    statusBar->SetStatusText(cantidad+_(" estudiantes selecionados"), 0);

    if(ECAESoRegistro)
    {
        unsigned int cantidad_componentes = dialogo_ecaes->getCantidadComponentes();
        unsigned int cantidad_competencias = dialogo_ecaes->getCantidadCompetencias();
        unsigned int cantidad_total = dialogo_ecaes->getCantidadTotal();

        label_componentes_seleccionados->SetLabel(wxString::Format(wxT("%i Componentes , %i Competencias , %i Total"),cantidad_componentes,cantidad_competencias,cantidad_total));

    }

}

void VentanaPrincipal::actualizarFiltroFechaInicio( wxCommandEvent& event )
{
    filtro_fecha_inicio = wxAtoi(input_fecha_desde->GetValue());
    actualizarCantidadMuestra();
}

void VentanaPrincipal::actualizarFiltroFechaFin( wxCommandEvent& event )
{
    filtro_fecha_final = wxAtoi(input_fecha_hasta->GetValue());
    actualizarCantidadMuestra();
}

void VentanaPrincipal::actualizarFiltroAsignaturas( wxCommandEvent& event ) {

    wxString a = input_asignaturas->GetValue();
    a = a.Trim();
    a = a.Trim(false);
    listadoAsignaturas = "";
    if(a.size() > 0){
        listadoAsignaturas = "'";
        a.Replace(_(" "),_(""));
        a.Replace(_(","),_("','"));
        listadoAsignaturas += std::string(a.mb_str());
        listadoAsignaturas +="'";
    }

    std::cout<<listadoAsignaturas<<std::endl;

    actualizarCantidadMuestra();
}

void VentanaPrincipal::seleccionarComponentesYCompetencias( wxCommandEvent& event )
{
    dialogo_ecaes->ShowModal();
    actualizarCantidadMuestra();
}

void VentanaPrincipal::actualizarInterfaz(){

     actualizarCantidadMuestra();

    int opcion = radio_comparacion->GetSelection();
    switch(opcion){
        case 0:
            filtro_asignaturas->Show(true);
            filtro_ecaes->Show(false);
            //grilla_valores->Show(true);
        break;
        default:
            filtro_asignaturas->Show(false);
            filtro_ecaes->Show(true);
            //grilla_valores->Show(false);
        break;
    }

    bool soloCalcularPonderaciones = check_mostrar_puntajes_minimos->IsChecked();
    if(opcion != 0) soloCalcularPonderaciones=false;
    ///Se actualizan inputs de la grilla de asignaturas
    input_puntaje->Show(soloCalcularPonderaciones);
    input_d_puntaje->Show(soloCalcularPonderaciones);
    inputPonderacionLenguaje->Show(soloCalcularPonderaciones);
    inputDPonderacionLenguaje->Show(soloCalcularPonderaciones);
    inputPonderacionMatematica->Show(soloCalcularPonderaciones);
    inputDPonderacionMatematica->Show(soloCalcularPonderaciones);
    inputPonderacionSociales->Show(soloCalcularPonderaciones);
    inputDPonderacionSociales->Show(soloCalcularPonderaciones);
    inputPonderacionFisica->Show(soloCalcularPonderaciones);
    inputDPonderacionFisica->Show(soloCalcularPonderaciones);
    inputPonderacionFilosofia->Show(soloCalcularPonderaciones);
    inputDPonderacionFilosofia->Show(soloCalcularPonderaciones);
    inputPonderacionBiologia->Show(soloCalcularPonderaciones);
    inputDPonderacionBiologia->Show(soloCalcularPonderaciones);
    inputPonderacionQuimica->Show(soloCalcularPonderaciones);
    inputDPonderacionQuimica->Show(soloCalcularPonderaciones);
    inputPonderacionFisica->Show(soloCalcularPonderaciones);
    inputDPonderacionFisica->Show(soloCalcularPonderaciones);


    soloCalcularPonderaciones = check_mostrar_puntajes_minimos->IsChecked();
    if(opcion == 0) soloCalcularPonderaciones=false;
    ///Se actualizan inputs de la grilla del ECAES



    grilla_valores->RecalcSizes();
    box_resultados->RecalcSizes();
 }


 void VentanaPrincipal::mostar_puntajes_minimos( wxCommandEvent& event ){
    actualizarInterfaz();
 }

 void VentanaPrincipal::OnRadioBoxComparar( wxCommandEvent& event ){
    actualizarInterfaz();
 }

void VentanaPrincipal::GuardarDatosCSV( wxCommandEvent& event ){
    wxFileDialog saveFileDialog(this, _("Save CSV file"),  wxT(""), wxT(""),_("CSV files (*.csv)|*.csv"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...


    bool ECAESoRegistro = radio_comparacion->GetSelection() != 0;
    opcionesEcaes = dialogo_ecaes->getOpciones();

    EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
    ResultadoConsulta* resultado = objEstudiantes->selectAll("*",filtro_fecha_inicio,filtro_fecha_final,ECAESoRegistro?opcionesEcaes:listadoAsignaturas,ECAESoRegistro);

    std::stringstream contenido;

    contenido << objEstudiantes->obtenerNombreColumnas()<<std::endl;

    unsigned int cantidad_estudiante_guardados = 0;
    for(unsigned int i=0;i<resultado->size();i++)
    {
        ResultadoFila unaFila= resultado->at(i);
        for(unsigned int j=0;j<unaFila.size();j++){
            contenido<<unaFila.at(j);
            if(j<unaFila.size()-1)
                contenido<<",";
        }
        contenido<<std::endl;
        cantidad_estudiante_guardados++;
    }



    wxFileOutputStream output_stream(saveFileDialog.GetPath());
    if (!output_stream.IsOk())
    {
        informar("No se pudo guardar el archivo correctamente");
        return;
    }else{
        wxFFile file(saveFileDialog.GetPath(), _T("w"));

        wxString mystring(contenido.str().c_str(), wxConvUTF8);
        file.Write(mystring);
        file.Close();
    }
    std::stringstream ss;
    ss << "Se guardaron "<<cantidad_estudiante_guardados<<" estudiantes";
    informar(ss.str().c_str());
}

 void VentanaPrincipal::BotonGuardarResultados( wxCommandEvent& event ) {
    int columnas = 0;
    bool soloCalcularPonderaciones = !check_mostrar_puntajes_minimos->IsChecked();
    wxFileDialog saveFileDialog(this, _("Save CSV file"),  wxT(""), wxT(""),_("CSV files (*.csv)|*.csv"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    columnas = soloCalcularPonderaciones ? 2 : 4;

    listaCSV lista;
    lista.push_back("Peso óptimo");
    lista.push_back("Desviación tipíca");
    if(not soloCalcularPonderaciones){
        lista.push_back("Puntaje óptimo");
        lista.push_back("Desviación tipíca");
    }

    lista.push_back(std::string(inputPuntajeLenguaje->GetValue().mb_str()));
    lista.push_back(std::string(inputDPuntajeLenguaje->GetValue().mb_str()));
    if(not soloCalcularPonderaciones){
        lista.push_back(std::string(inputPonderacionLenguaje->GetValue().mb_str()));
        lista.push_back(std::string(inputDPonderacionLenguaje->GetValue().mb_str()));
    }

    lista.push_back(std::string(inputPuntajeMatematica->GetValue().mb_str()));
    lista.push_back(std::string(inputDPuntajeMatematica->GetValue().mb_str()));
    if(not soloCalcularPonderaciones){
        lista.push_back(std::string(inputPonderacionMatematica->GetValue().mb_str()));
        lista.push_back(std::string(inputDPonderacionMatematica->GetValue().mb_str()));
    }

    lista.push_back(std::string(inputPuntajeSociales->GetValue().mb_str()));
    lista.push_back(std::string(inputDPuntajeSociales->GetValue().mb_str()));
    if(not soloCalcularPonderaciones){
        lista.push_back(std::string(inputPonderacionSociales->GetValue().mb_str()));
        lista.push_back(std::string(inputDPonderacionSociales->GetValue().mb_str()));
    }

    lista.push_back(std::string(inputPuntajeFilosofia->GetValue().mb_str()));
    lista.push_back(std::string(inputDPuntajeFilosofia->GetValue().mb_str()));
    if(not soloCalcularPonderaciones){
        lista.push_back(std::string(inputPonderacionFilosofia->GetValue().mb_str()));
        lista.push_back(std::string(inputDPonderacionFilosofia->GetValue().mb_str()));
    }

    lista.push_back(std::string(inputPuntajeBiologia->GetValue().mb_str()));
    lista.push_back(std::string(inputDPuntajeBiologia->GetValue().mb_str()));
    if(not soloCalcularPonderaciones){
        lista.push_back(std::string(inputPonderacionBiologia->GetValue().mb_str()));
        lista.push_back(std::string(inputDPonderacionBiologia->GetValue().mb_str()));
    }

    lista.push_back(std::string(inputPuntajeQuimica->GetValue().mb_str()));
    lista.push_back(std::string(inputDPuntajeQuimica->GetValue().mb_str()));
    if(not soloCalcularPonderaciones){
        lista.push_back(std::string(inputPonderacionQuimica->GetValue().mb_str()));
        lista.push_back(std::string(inputDPonderacionQuimica->GetValue().mb_str()));
    }

    lista.push_back(std::string(inputPuntajeFisica->GetValue().mb_str()));
    lista.push_back(std::string(inputDPuntajeFisica->GetValue().mb_str()));
    if(not soloCalcularPonderaciones){
        lista.push_back(std::string(inputPonderacionFisica->GetValue().mb_str()));
        lista.push_back(std::string(inputDPonderacionFisica->GetValue().mb_str()));
    }



    std::stringstream contenido;

    int i =1;
    for (listaCSV::iterator it = lista.begin(); it != lista.end(); it++,i++){
        contenido<<(*it);
        if(0 != i%(columnas))
            contenido<<",";
        else
            contenido<<std::endl;
    }


    contenido<<std::string(inputPromedio->GetValue().mb_str())<<",";
//    contenido<<std::string(inputDesviacionPromedio->GetValue().mb_str())<<std::endl;

    wxFileOutputStream output_stream(saveFileDialog.GetPath());
    if (!output_stream.IsOk())
    {
        return;
    }else{
        wxFFile file(saveFileDialog.GetPath(), _T("w"));

        wxString mystring(contenido.str().c_str(), wxConvUTF8);
        file.Write(mystring);
        file.Close();
    }

 }

// 2012-09-28: Función alterada por Angel, para no tener en cuenta PuntajesMinimos(=0) y para repetir
// varias veces el AG, obteniendo el promedio y la desviación típica de las ponderaciones.
#include <math.h>
void VentanaPrincipal::BotonBuscar( wxCommandEvent& event ){
    std::cout<<"COMIENZO  botonBuscar >>>>"<<std::endl;
    ///Compruebo si hay conexion a la base de datos, si no, no hago nada
    if(!comprobarConexionBD())
        return;

    ///Obtengo opciones de la interfaz
    int veces=wxAtoi(input_numero_iteraciones->GetValue());
    bool soloCalcularPonderaciones = !check_mostrar_puntajes_minimos->IsChecked();
    bool ECAESoRegistro = radio_comparacion->GetSelection() != 0;
    ///ECAESoRegistro si es TRUE trabajo con el ECAES, si no con las notas de Univalle

    ///objeto AdmisionesUnivalle que controla en que puesto quedan los estudiantes
    std::cout<<"AdmisionesUnivalle"<<std::endl;
    AdmisionesUnivalle admisionesUnivalle(ECAESoRegistro,getInformacionConexion(),filtro_fecha_inicio,filtro_fecha_final);

    ///
    std::cout<<"objEstudiantes"<<std::endl;
    EstudianteDAO *objEstudiantes = new EstudianteDAO(getInformacionConexion());
    listaCSV *listadoCodigoEstudiantes = objEstudiantes->getListaEstudiantesOrdenadaPorPromedio(filtro_fecha_inicio,filtro_fecha_final,ECAESoRegistro?opcionesEcaes:listadoAsignaturas,ECAESoRegistro);
    delete objEstudiantes;

    std::cout<<":)"<<std::endl;
    int cuantosEgresados = listadoCodigoEstudiantes->size();
    std::cout << ">> " << cuantosEgresados << std::endl;

    const char **listaEgresadosOrdenada = new const char*[cuantosEgresados];
    int i=0;
    for (listaCSV::iterator it = listadoCodigoEstudiantes->begin(); it != listadoCodigoEstudiantes->end(); it++,i++)
    {
        std::string stringIt =  *it;
        listaEgresadosOrdenada[i] = stringIt.c_str();
    }

    double vectorPuntajesMinimos[veces][cuantosComponentesExamenIngreso];
    double vectorPonderaciones[veces][cuantosComponentesExamenIngreso];
    double vectorAptitudes[veces];
    for(int vez=0; vez<veces; vez++)
    {
        FenotipoIPMPAIS *fenotipo=new FenotipoIPMPAIS(cuantosComponentesExamenIngreso, puntajeMinimo_minimo, puntajeMinimo_maximo, ponderacion_minimo, ponderacion_maximo, admisionesUnivalle, listaEgresadosOrdenada, cuantosEgresados, soloCalcularPonderaciones);
        double puntajesMinimos[cuantosComponentesExamenIngreso];  // Array vacío
        double ponderaciones[cuantosComponentesExamenIngreso];  // Array vacío
        AlgoritmoGenetico algoritmoGenetico(fenotipo);
        double aptitud=0;
        std::cout<<"double aptitud=0=>"<<aptitud<<std::endl;
        fenotipo->expresar(algoritmoGenetico.ejecutar(aptitud, 100000), puntajesMinimos, ponderaciones);
        std::cout<<"cuantosEgresados="<<cuantosEgresados<<std::endl;
        std::cout<<"double aptitud= expresar=>"<<aptitud<<std::endl;
        vectorAptitudes[vez] = aptitud;
        for(int i=0; i<cuantosComponentesExamenIngreso; i++)
        {
          vectorPuntajesMinimos[vez][i] = puntajesMinimos[i];
          vectorPonderaciones[vez][i] = ponderaciones[i];
        }
        delete fenotipo;
        fenotipo=0;
    }

// CALCULA LOS ERRORES PROMEDIO Y LOS VALORES PROMEDIO
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

// PERO LO QUE REALMENTE ME INTERESA ES LA MEJOR APTITUD, QUE ES DONDE ESTA EL ERROR MENOR Y SUS CORRESPONDIENTES PUNTAJES MINIMOS
    double puntajesMinimosMejor[cuantosComponentesExamenIngreso];  // Array vacío
    double ponderacionesMejor[cuantosComponentesExamenIngreso];  // Array vacío
    double aptitudMejor = vectorAptitudes[0];
    int mejorVez = 0;
    for(int vez=1; vez<veces; vez++)
      if(aptitudMejor < vectorAptitudes[vez])
      {
        mejorVez = vez;
        aptitudMejor = vectorAptitudes[vez];
      }

    for(int i=0; i<cuantosComponentesExamenIngreso; i++)
    {
      puntajesMinimosMejor[i] = vectorPuntajesMinimos[mejorVez][i];
      ponderacionesMejor[i] = vectorPonderaciones[mejorVez][i];
    }

    std::cout<<"aptitudMejor=>"<<aptitudMejor<<std::endl;

    if(not soloCalcularPonderaciones)
    {

        inputPonderacionLenguaje->SetValue(wxString::Format(wxT("%f"),puntajesMinimosMejor[0]));
        inputPonderacionMatematica->SetValue(wxString::Format(wxT("%f"),puntajesMinimosMejor[1]));
        inputPonderacionSociales->SetValue(wxString::Format(wxT("%f"),puntajesMinimosMejor[2]));
        inputPonderacionFilosofia->SetValue(wxString::Format(wxT("%f"),puntajesMinimosMejor[3]));
        inputPonderacionBiologia->SetValue(wxString::Format(wxT("%f"),puntajesMinimosMejor[4]));
        inputPonderacionQuimica->SetValue(wxString::Format(wxT("%f"),puntajesMinimosMejor[5]));
        inputPonderacionFisica->SetValue(wxString::Format(wxT("%f"),puntajesMinimosMejor[6]));

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
        suma+=ponderacionesMejor[i];
    }

    for(int i=0; i<cuantosComponentesExamenIngreso; i++)
    {
      ponderacionesMejor[i]=ponderacionesMejor[i]*100/suma;
      ponderacionesDesviacionTipica[i]=ponderacionesDesviacionTipica[i]*100/suma;
    }

    inputPuntajeLenguaje->SetValue(wxString::Format(wxT("%f"),ponderacionesMejor[0]));
    inputPuntajeMatematica->SetValue(wxString::Format(wxT("%f"),ponderacionesMejor[1]));
    inputPuntajeSociales->SetValue(wxString::Format(wxT("%f"),ponderacionesMejor[2]));
    inputPuntajeFilosofia->SetValue(wxString::Format(wxT("%f"),ponderacionesMejor[3]));
    inputPuntajeBiologia->SetValue(wxString::Format(wxT("%f"),ponderacionesMejor[4]));
    inputPuntajeQuimica->SetValue(wxString::Format(wxT("%f"),ponderacionesMejor[5]));
    inputPuntajeFisica->SetValue(wxString::Format(wxT("%f"),ponderacionesMejor[6]));

    inputDPuntajeLenguaje->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[0]));
    inputDPuntajeMatematica->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[1]));
    inputDPuntajeSociales->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[2]));
    inputDPuntajeFilosofia->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[3]));
    inputDPuntajeBiologia->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[4]));
    inputDPuntajeQuimica->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[5]));
    inputDPuntajeFisica->SetValue(wxString::Format(wxT("%f"),ponderacionesDesviacionTipica[6]));

    inputPromedio->SetValue(wxString::Format(wxT("%f"),-aptitudMejor)); // 2013-03-26 by Angel: le quito el signo porque despista en la GUI

    boton_guardarCSV->Enable(true);
}
