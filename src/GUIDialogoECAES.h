///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIDialogoECAES__
#define __GUIDialogoECAES__

#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialogoEcaes
///////////////////////////////////////////////////////////////////////////////
class GUIDialogoEcaes : public wxDialog 
{
	private:
	
	protected:
		wxCheckBox* m_checkComponente1;
		wxCheckBox* m_checkComponente2;
		wxCheckBox* m_checkComponente3;
		wxCheckBox* m_checkComponente4;
		wxCheckBox* m_checkComponente5;
		wxCheckBox* m_checkComponente6;
		wxCheckBox* m_checkComponente7;
		wxCheckBox* m_checkBoxCompetencia1;
		wxCheckBox* m_checkBoxCompetencia2;
		wxCheckBox* m_checkBoxCompetencia3;
		wxCheckBox* m_checkBoxTotal;
		wxButton* m_buttonAceptar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void botonAceptar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIDialogoEcaes( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~GUIDialogoEcaes();
	
};

#endif //__GUIDialogoECAES__
