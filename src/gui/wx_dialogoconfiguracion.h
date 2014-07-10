///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIDialog__
#define __GUIDialog__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialog
///////////////////////////////////////////////////////////////////////////////
class GUIDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText2;
		wxTextCtrl* inputHost;
		wxStaticText* m_staticText3;
		wxTextCtrl* inputPuerto;
		wxStaticText* m_staticText51;
		wxTextCtrl* inputNombrebd;
		wxStaticText* m_staticText4;
		wxTextCtrl* inputUsuario;
		wxStaticText* m_staticText5;
		wxTextCtrl* inputClave;
		wxButton* boton_ayuda;
		wxButton* boton_guardar;
		wxButton* boton_test;
		wxButton* boton_salir;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnAyuda( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGuardar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProbar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSalir( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Configuración de base de datos"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE );
		~GUIDialog();
	
};

#endif //__GUIDialog__
