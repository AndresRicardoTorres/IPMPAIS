///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	mbar = new wxMenuBar( 0 );
	archivo = new wxMenu();
	wxMenuItem* salir;
	salir = new wxMenuItem( archivo, ID_SALIR, wxString( wxT("&Salir") ) + wxT('\t') + wxT("Alt+F4"), wxT("Salir de la aplicación"), wxITEM_NORMAL );
	archivo->Append( salir );
	
	mbar->Append( archivo, wxT("&Archivo") );
	
	configuracion = new wxMenu();
	wxMenuItem* baseDeDatos;
	baseDeDatos = new wxMenuItem( configuracion, ID_BASE_DE_DATOS, wxString( wxT("Base de datos") ) , wxEmptyString, wxITEM_NORMAL );
	configuracion->Append( baseDeDatos );
	
	mbar->Append( configuracion, wxT("Configuración") );
	
	ayuda = new wxMenu();
	wxMenuItem* item_ayuda;
	item_ayuda = new wxMenuItem( ayuda, ID_AYUDA, wxString( wxT("Ayuda") ) , wxEmptyString, wxITEM_NORMAL );
	ayuda->Append( item_ayuda );
	
	wxMenuItem* acercaDe;
	acercaDe = new wxMenuItem( ayuda, ID_ACERCA_DE_, wxString( wxT("&Acerca de ..") ) + wxT('\t') + wxT("F1"), wxT("Muestra información acerca de esta aplicación"), wxITEM_NORMAL );
	ayuda->Append( acercaDe );
	
	mbar->Append( ayuda, wxT("&Ayuda") );
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	panel_lectura = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( panel_lectura, wxID_ANY, wxT("Datos demograficos") ), wxVERTICAL );
	
	m_button1 = new wxButton( panel_lectura, wxID_ANY, wxT("Cargar información de admisiones ..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( m_button1, 0, wxALL|wxEXPAND, 5 );
	
	progresoAdmisiones = new wxGauge( panel_lectura, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	sbSizer1->Add( progresoAdmisiones, 0, wxALL|wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer1, 1, wxEXPAND, 50 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( panel_lectura, wxID_ANY, wxT("Puntajes del ICFES") ), wxVERTICAL );
	
	m_button5 = new wxButton( panel_lectura, wxID_ANY, wxT("Cargar puntajes del ICFES ..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( m_button5, 0, wxALL|wxEXPAND, 5 );
	
	progresoICFES = new wxGauge( panel_lectura, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	sbSizer6->Add( progresoICFES, 0, wxALL|wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( panel_lectura, wxID_ANY, wxT("Equivalencias") ), wxVERTICAL );
	
	m_button11 = new wxButton( panel_lectura, wxID_ANY, wxT("Cargar información de equivalencias ..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer3->Add( m_button11, 0, wxALL|wxEXPAND, 5 );
	
	progresoEquivalencias = new wxGauge( panel_lectura, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	sbSizer3->Add( progresoEquivalencias, 0, wxALL|wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer3, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( panel_lectura, wxID_ANY, wxT("Calificaciones asignaturas de Universidad del Valle") ), wxVERTICAL );
	
	m_button12 = new wxButton( panel_lectura, wxID_ANY, wxT("Cargar información de registro academico ..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_button12, 0, wxALL|wxEXPAND, 5 );
	
	progresoRegistro = new wxGauge( panel_lectura, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	sbSizer4->Add( progresoRegistro, 0, wxALL|wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( panel_lectura, wxID_ANY, wxT("Puntajes del ECAES") ), wxVERTICAL );
	
	m_button13 = new wxButton( panel_lectura, wxID_ANY, wxT("Cargar información de puntajes de ECAES ..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_button13, 0, wxALL|wxEXPAND, 5 );
	
	progresoECAES = new wxGauge( panel_lectura, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	sbSizer5->Add( progresoECAES, 0, wxALL|wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	panel_lectura->SetSizer( bSizer2 );
	panel_lectura->Layout();
	bSizer2->Fit( panel_lectura );
	m_notebook1->AddPage( panel_lectura, wxT("Lectura de datos"), false );
	panel_resultados = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxString radio_comparacionChoices[] = { wxT("ICFES con asignaturas"), wxT("ICFES con ECAES") };
	int radio_comparacionNChoices = sizeof( radio_comparacionChoices ) / sizeof( wxString );
	radio_comparacion = new wxRadioBox( panel_resultados, wxID_ANY, wxT("Modo de compararción"), wxDefaultPosition, wxDefaultSize, radio_comparacionNChoices, radio_comparacionChoices, 1, wxRA_SPECIFY_ROWS );
	radio_comparacion->SetSelection( 0 );
	bSizer5->Add( radio_comparacion, 0, wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( panel_resultados, wxID_ANY, wxT("Filtros") ), wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( panel_resultados, wxID_ANY, wxT("Rango de años") ), wxVERTICAL );
	
	wxGridSizer* gSizer5;
	gSizer5 = new wxGridSizer( 2, 2, 0, 0 );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 1, 5, 0, 0 );
	
	m_staticText1 = new wxStaticText( panel_resultados, wxID_ANY, wxT("Desde:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gSizer1->Add( m_staticText1, 0, wxALIGN_CENTER|wxALL, 5 );
	
	input_fecha_desde = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	input_fecha_desde->SetMaxLength( 4 ); 
	gSizer1->Add( input_fecha_desde, 0, wxALIGN_CENTER, 5 );
	
	m_staticText2 = new wxStaticText( panel_resultados, wxID_ANY, wxT("Hasta:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer1->Add( m_staticText2, 0, wxALIGN_CENTER|wxALL, 5 );
	
	input_fecha_hasta = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( input_fecha_hasta, 0, wxALIGN_CENTER, 5 );
	
	gSizer5->Add( gSizer1, 1, 0, 5 );
	
	label_cantidad = new wxStaticText( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	label_cantidad->Wrap( -1 );
	gSizer5->Add( label_cantidad, 0, wxALL, 5 );
	
	sbSizer12->Add( gSizer5, 1, wxEXPAND, 5 );
	
	sbSizer9->Add( sbSizer12, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer14;
	sbSizer14 = new wxStaticBoxSizer( new wxStaticBox( panel_resultados, wxID_ANY, wxT("Lista de asignaturas") ), wxVERTICAL );
	
	input_asignaturas = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 540,-1 ), 0 );
	sbSizer14->Add( input_asignaturas, 5, wxEXPAND, 5 );
	
	sbSizer9->Add( sbSizer14, 0, wxALL|wxEXPAND, 5 );
	
	bSizer5->Add( sbSizer9, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( panel_resultados, wxID_ANY, wxT("Ponderaciones recomendadas") ), wxVERTICAL );
	
	wxGridSizer* gSizer51;
	gSizer51 = new wxGridSizer( 1, 4, 0, 0 );
	
	m_staticText16 = new wxStaticText( panel_resultados, wxID_ANY, wxT("Numero de iteraciones : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	gSizer51->Add( m_staticText16, 0, wxALL, 5 );
	
	input_numero_iteraciones = new wxTextCtrl( panel_resultados, wxID_ANY, wxT("5"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
	gSizer51->Add( input_numero_iteraciones, 0, wxALL, 5 );
	
	check_mostrar_puntajes_minimos = new wxCheckBox( panel_resultados, wxID_ANY, wxT("Mostrar puntajes minimos"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer51->Add( check_mostrar_puntajes_minimos, 0, wxALL, 5 );
	
	boton_buscar = new wxButton( panel_resultados, wxID_ANY, wxT("Buscar ..."), wxDefaultPosition, wxDefaultSize, 0 );
	boton_buscar->Enable( false );
	
	gSizer51->Add( boton_buscar, 0, wxALIGN_LEFT|wxALL, 5 );
	
	sbSizer8->Add( gSizer51, 0, 0, 5 );
	
	grilla_valores = new wxGridSizer( 9, 5, 2, 0 );
	
	input_vacio = new wxStaticText( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	input_vacio->Wrap( -1 );
	grilla_valores->Add( input_vacio, 0, wxALL, 5 );
	
	input_peso = new wxStaticText( panel_resultados, wxID_ANY, wxT("Valor medio peso"), wxDefaultPosition, wxDefaultSize, 0 );
	input_peso->Wrap( -1 );
	grilla_valores->Add( input_peso, 0, wxALL, 5 );
	
	input_d_peso = new wxStaticText( panel_resultados, wxID_ANY, wxT("Desviación típica"), wxDefaultPosition, wxDefaultSize, 0 );
	input_d_peso->Wrap( -1 );
	grilla_valores->Add( input_d_peso, 0, wxALL, 5 );
	
	input_puntaje = new wxStaticText( panel_resultados, wxID_ANY, wxT("Valor medio puntaje"), wxDefaultPosition, wxDefaultSize, 0 );
	input_puntaje->Wrap( -1 );
	grilla_valores->Add( input_puntaje, 0, wxALL, 5 );
	
	input_d_puntaje = new wxStaticText( panel_resultados, wxID_ANY, wxT("Desviación típica"), wxDefaultPosition, wxDefaultSize, 0 );
	input_d_puntaje->Wrap( -1 );
	grilla_valores->Add( input_d_puntaje, 0, wxALL, 5 );
	
	input_lenguaje = new wxStaticText( panel_resultados, wxID_ANY, wxT("Lenguaje : "), wxDefaultPosition, wxDefaultSize, 0 );
	input_lenguaje->Wrap( -1 );
	grilla_valores->Add( input_lenguaje, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	inputPuntajeLenguaje = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPuntajeLenguaje, 0, wxALL, 5 );
	
	inputDPuntajeLenguaje = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPuntajeLenguaje, 0, wxALL, 5 );
	
	inputPonderacionLenguaje = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPonderacionLenguaje, 0, wxALL, 5 );
	
	inputDPonderacionLenguaje = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPonderacionLenguaje, 0, wxALL, 5 );
	
	input_matematica = new wxStaticText( panel_resultados, wxID_ANY, wxT("Matemática : "), wxDefaultPosition, wxDefaultSize, 0 );
	input_matematica->Wrap( -1 );
	grilla_valores->Add( input_matematica, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	inputPuntajeMatematica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPuntajeMatematica, 0, wxALL, 5 );
	
	inputDPuntajeMatematica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPuntajeMatematica, 0, wxALL, 5 );
	
	inputPonderacionMatematica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPonderacionMatematica, 0, wxALL, 5 );
	
	inputDPonderacionMatematica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPonderacionMatematica, 0, wxALL, 5 );
	
	input_ciencias_sociales = new wxStaticText( panel_resultados, wxID_ANY, wxT("Ciencias sociales : "), wxDefaultPosition, wxDefaultSize, 0 );
	input_ciencias_sociales->Wrap( -1 );
	grilla_valores->Add( input_ciencias_sociales, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	inputPuntajeSociales = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPuntajeSociales, 0, wxALL, 5 );
	
	inputDPuntajeSociales = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPuntajeSociales, 0, wxALL, 5 );
	
	inputPonderacionSociales = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPonderacionSociales, 0, wxALL, 5 );
	
	inputDPonderacionSociales = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPonderacionSociales, 0, wxALL, 5 );
	
	input_filosofia = new wxStaticText( panel_resultados, wxID_ANY, wxT("Filosofía :"), wxDefaultPosition, wxDefaultSize, 0 );
	input_filosofia->Wrap( -1 );
	grilla_valores->Add( input_filosofia, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	inputPuntajeFilosofia = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPuntajeFilosofia, 0, wxALL, 5 );
	
	inputDPuntajeFilosofia = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPuntajeFilosofia, 0, wxALL, 5 );
	
	inputPonderacionFilosofia = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPonderacionFilosofia, 0, wxALL, 5 );
	
	inputDPonderacionFilosofia = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPonderacionFilosofia, 0, wxALL, 5 );
	
	input_biologia = new wxStaticText( panel_resultados, wxID_ANY, wxT("Biología : "), wxDefaultPosition, wxDefaultSize, 0 );
	input_biologia->Wrap( -1 );
	grilla_valores->Add( input_biologia, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	inputPuntajeBiologia = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPuntajeBiologia, 0, wxALL, 5 );
	
	inputDPuntajeBiologia = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPuntajeBiologia, 0, wxALL, 5 );
	
	inputPonderacionBiologia = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPonderacionBiologia, 0, wxALL, 5 );
	
	inputDPonderacionBiologia = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPonderacionBiologia, 0, wxALL, 5 );
	
	input_quimica = new wxStaticText( panel_resultados, wxID_ANY, wxT("Química : "), wxDefaultPosition, wxDefaultSize, 0 );
	input_quimica->Wrap( -1 );
	grilla_valores->Add( input_quimica, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	inputPuntajeQuimica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPuntajeQuimica, 0, wxALL, 5 );
	
	inputDPuntajeQuimica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPuntajeQuimica, 0, wxALL, 5 );
	
	inputPonderacionQuimica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPonderacionQuimica, 0, wxALL, 5 );
	
	inputDPonderacionQuimica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPonderacionQuimica, 0, wxALL, 5 );
	
	input_fisica = new wxStaticText( panel_resultados, wxID_ANY, wxT("Física : "), wxDefaultPosition, wxDefaultSize, 0 );
	input_fisica->Wrap( -1 );
	grilla_valores->Add( input_fisica, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	inputPuntajeFisica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPuntajeFisica, 0, wxALL, 5 );
	
	inputDPuntajeFisica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPuntajeFisica, 0, wxALL, 5 );
	
	inputPonderacionFisica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPonderacionFisica, 0, wxALL, 5 );
	
	inputDPonderacionFisica = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDPonderacionFisica, 0, wxALL, 5 );
	
	m_staticText13 = new wxStaticText( panel_resultados, wxID_ANY, wxT("Promedio : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	grilla_valores->Add( m_staticText13, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	inputPromedio = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputPromedio, 0, wxALL, 5 );
	
	inputDesviacionPromedio = new wxTextCtrl( panel_resultados, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	grilla_valores->Add( inputDesviacionPromedio, 0, wxALL, 5 );
	
	sbSizer8->Add( grilla_valores, 1, wxALIGN_RIGHT|wxEXPAND, 5 );
	
	bSizer5->Add( sbSizer8, 3, wxEXPAND, 5 );
	
	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 2, 2, 0, 0 );
	
	boton_guardarCSV = new wxButton( panel_resultados, wxID_ANY, wxT("Guardar ..."), wxDefaultPosition, wxDefaultSize, 0 );
	boton_guardarCSV->Enable( false );
	
	gSizer4->Add( boton_guardarCSV, 0, wxALL, 5 );
	
	button_guardar_datos = new wxButton( panel_resultados, wxID_ANY, wxT("Guardar datos aplicando filtos ..."), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer4->Add( button_guardar_datos, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	bSizer5->Add( gSizer4, 0, wxEXPAND, 5 );
	
	panel_resultados->SetSizer( bSizer5 );
	panel_resultados->Layout();
	bSizer5->Fit( panel_resultados );
	m_notebook1->AddPage( panel_resultados, wxT("Resultados"), true );
	
	bSizer1->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( salir->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( baseDeDatos->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnBDConfig ) );
	this->Connect( acercaDe->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::cargarInformacionAdmisiones ), NULL, this );
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::CagarPuntajesICFES ), NULL, this );
	m_button11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::cargarInformacionEquivalencias ), NULL, this );
	m_button12->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::cargarInformacionRegistroAcademico ), NULL, this );
	m_button13->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::cargarInformacionECAES ), NULL, this );
	input_fecha_desde->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::actualizarFiltroFechaInicio ), NULL, this );
	input_fecha_hasta->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::actualizarFiltroFechaFin ), NULL, this );
	input_asignaturas->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::actualizarFiltroAsignaturas ), NULL, this );
	check_mostrar_puntajes_minimos->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrame::mostar_puntajes_minimos ), NULL, this );
	boton_buscar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::BotonBuscar ), NULL, this );
	boton_guardarCSV->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::BotonGuardarResultados ), NULL, this );
	button_guardar_datos->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::GuardarDatosCSV ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnBDConfig ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::cargarInformacionAdmisiones ), NULL, this );
	m_button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::CagarPuntajesICFES ), NULL, this );
	m_button11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::cargarInformacionEquivalencias ), NULL, this );
	m_button12->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::cargarInformacionRegistroAcademico ), NULL, this );
	m_button13->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::cargarInformacionECAES ), NULL, this );
	input_fecha_desde->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::actualizarFiltroFechaInicio ), NULL, this );
	input_fecha_hasta->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::actualizarFiltroFechaFin ), NULL, this );
	input_asignaturas->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrame::actualizarFiltroAsignaturas ), NULL, this );
	check_mostrar_puntajes_minimos->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrame::mostar_puntajes_minimos ), NULL, this );
	boton_buscar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::BotonBuscar ), NULL, this );
	boton_guardarCSV->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::BotonGuardarResultados ), NULL, this );
	button_guardar_datos->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::GuardarDatosCSV ), NULL, this );
}
