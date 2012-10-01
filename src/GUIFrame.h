///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFrame__
#define __GUIFrame__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/button.h>
#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/notebook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define ID_SALIR 1000
#define ID_BASE_DE_DATOS 1001
#define ID_AYUDA 1002
#define ID_ACERCA_DE_ 1003

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mbar;
		wxMenu* archivo;
		wxMenu* configuracion;
		wxMenu* ayuda;
		wxStatusBar* statusBar;
		wxNotebook* m_notebook1;
		wxPanel* panel_lectura;
		wxButton* m_button1;
		wxGauge* progresoAdmisiones;
		wxButton* m_button5;
		wxGauge* progresoICFES;
		wxButton* m_button11;
		wxGauge* progresoEquivalencias;
		wxButton* m_button12;
		wxGauge* progresoRegistro;
		wxButton* m_button13;
		wxGauge* progresoECAES;
		wxPanel* panel_filtros;
		wxRadioBox* radioBox_filtro_completitud;
		wxStaticText* m_staticText1;
		wxTextCtrl* input_fecha_desde;
		wxStaticText* m_staticText2;
		wxTextCtrl* input_fecha_hasta;
		wxTextCtrl* m_textCtrl31;
		wxButton* button_seleccionar_asignaturas;
		wxPanel* m_panel5;
		wxButton* button_guardar_datos;
		wxPanel* panel_grafico;
		wxPanel* panel_resultados;
		wxStaticText* label_cantidad;
		wxCheckBox* check_mostrar_puntajes_minimos;
		wxButton* boton_buscar;
		wxStaticText* input_vacio;
		wxStaticText* input_lenguaje11;
		wxStaticText* input_lenguaje111;
		wxStaticText* input_lenguaje;
		wxTextCtrl* inputPuntajeLenguaje;
		wxTextCtrl* inputPonderacionLenguaje;
		wxStaticText* input_matematica;
		wxTextCtrl* inputPuntajeMatematica;
		wxTextCtrl* inputPonderacionMatematica;
		wxStaticText* input_ciencias_sociales;
		wxTextCtrl* inputPuntajeSociales;
		wxTextCtrl* inputPonderacionSociales;
		wxStaticText* input_filosofia;
		wxTextCtrl* inputPuntajeFilosofia;
		wxTextCtrl* inputPonderacionFilosofia;
		wxStaticText* input_biologia;
		wxTextCtrl* inputPuntajeBiologia;
		wxTextCtrl* inputPonderacionBiologia;
		wxStaticText* input_quimica;
		wxTextCtrl* inputPuntajeQuimica;
		wxTextCtrl* inputPonderacionQuimica;
		wxStaticText* input_fisica;
		wxTextCtrl* inputPuntajeFisica;
		wxTextCtrl* inputPonderacionFisica;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textCtrl18;
		wxTextCtrl* m_textCtrl19;
		wxButton* boton_guardarCSV;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBDConfig( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void cargarInformacionAdmisiones( wxCommandEvent& event ) { event.Skip(); }
		virtual void CagarPuntajesICFES( wxCommandEvent& event ) { event.Skip(); }
		virtual void cargarInformacionEquivalencias( wxCommandEvent& event ) { event.Skip(); }
		virtual void cargarInformacionRegistroAcademico( wxCommandEvent& event ) { event.Skip(); }
		virtual void cargarInformacionECAES( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRadioBoxFiltroCompletitud( wxCommandEvent& event ) { event.Skip(); }
		virtual void actualizarFiltroFechaInicio( wxCommandEvent& event ) { event.Skip(); }
		virtual void actualizarFiltroFechaFin( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonSeleccionarAsignaturas( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickGuardarDatos( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void mostar_puntajes_minimos( wxCommandEvent& event ) { event.Skip(); }
		virtual void BotonBuscar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Determinador de puntajes minimos "), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIFrame();
	
};

#endif //__GUIFrame__
