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

#include "GUIDialog.h"

///////////////////////////////////////////////////////////////////////////

GUIDialog::GUIDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 2, 2, 0, 0 );
	
	gSizer1->SetMinSize( wxSize( 230,-1 ) ); 
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Host : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer1->Add( m_staticText2, 0, wxALL, 5 );
	
	inputHost = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( inputHost, 0, wxALL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Puerto :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer1->Add( m_staticText3, 0, wxALL, 5 );
	
	inputPuerto = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( inputPuerto, 0, wxALL, 5 );
	
	m_staticText51 = new wxStaticText( this, wxID_ANY, wxT("Base de datos : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	gSizer1->Add( m_staticText51, 0, wxALL, 5 );
	
	inputNombrebd = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( inputNombrebd, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Usuario : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer1->Add( m_staticText4, 0, wxALL, 5 );
	
	inputUsuario = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( inputUsuario, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Contraseña : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gSizer1->Add( m_staticText5, 0, wxALL, 5 );
	
	inputClave = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	gSizer1->Add( inputClave, 0, wxALL, 5 );
	
	boton_ayuda = new wxButton( this, wxID_ANY, wxT("Ayuda"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( boton_ayuda, 0, wxALL, 5 );
	
	boton_guardar = new wxButton( this, wxID_ANY, wxT("Guardar"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( boton_guardar, 0, wxALL, 5 );
	
	boton_test = new wxButton( this, wxID_ANY, wxT("Probar"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( boton_test, 0, wxALL, 5 );
	
	boton_salir = new wxButton( this, wxID_ANY, wxT("Salir"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( boton_salir, 0, wxALL, 5 );
	
	this->SetSizer( gSizer1 );
	this->Layout();
	gSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIDialog::OnClose ) );
	boton_ayuda->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnAyuda ), NULL, this );
	boton_guardar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnGuardar ), NULL, this );
	boton_test->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnProbar ), NULL, this );
	boton_salir->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnSalir ), NULL, this );
}

GUIDialog::~GUIDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIDialog::OnClose ) );
	boton_ayuda->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnAyuda ), NULL, this );
	boton_guardar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnGuardar ), NULL, this );
	boton_test->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnProbar ), NULL, this );
	boton_salir->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnSalir ), NULL, this );
}
