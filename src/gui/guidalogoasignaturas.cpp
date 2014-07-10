///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "guidialogoasignaturas.h"

///////////////////////////////////////////////////////////////////////////

GUIDialogoAsignaturas::GUIDialogoAsignaturas( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Asignaturas : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer2->Add( m_staticText4, 0, wxALIGN_CENTER|wxALL, 5 );

	wxArrayString m_checkList4Choices;
	m_checkList4 = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxSize( -1,200 ), m_checkList4Choices, 0 );
	bSizer2->Add( m_checkList4, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 2, 2, 0, 0 );

	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer7->Add( boton_cancelar, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer7->Add( boton_aceptar, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	bSizer2->Add( gSizer7, 1, wxALIGN_RIGHT|wxEXPAND|wxSHAPED, 5 );

	this->SetSizer( bSizer2 );
	this->Layout();
}

GUIDialogoAsignaturas::~GUIDialogoAsignaturas()
{
}
