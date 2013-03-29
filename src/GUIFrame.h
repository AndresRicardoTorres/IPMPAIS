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
#include <wx/valgen.h>
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
		wxPanel* panel_resultados;
		wxBoxSizer* box_resultados;
		wxRadioBox* radio_comparacion;
		wxStaticText* m_staticText1;
		wxTextCtrl* input_fecha_desde;
		wxStaticText* m_staticText2;
		wxTextCtrl* input_fecha_hasta;
		wxStaticText* label_cantidad;
		wxStaticBoxSizer* filtro_asignaturas;
		wxTextCtrl* input_asignaturas;
		wxStaticBoxSizer* filtro_ecaes;
		wxStaticText* label_componentes_seleccionados;
		wxButton* m_button9;
		wxStaticText* m_staticText16;
		wxTextCtrl* input_numero_iteraciones;
		wxCheckBox* check_mostrar_puntajes_minimos;
		wxButton* boton_buscar;
		wxGridSizer* grilla_valores;
		wxStaticText* input_vacio;
		wxStaticText* input_peso;
		wxStaticText* input_d_peso;
		wxStaticText* input_puntaje;
		wxStaticText* input_d_puntaje;
		wxStaticText* input_lenguaje;
		wxTextCtrl* inputPuntajeLenguaje;
		wxTextCtrl* inputDPuntajeLenguaje;
		wxTextCtrl* inputPonderacionLenguaje;
		wxTextCtrl* inputDPonderacionLenguaje;
		wxStaticText* input_matematica;
		wxTextCtrl* inputPuntajeMatematica;
		wxTextCtrl* inputDPuntajeMatematica;
		wxTextCtrl* inputPonderacionMatematica;
		wxTextCtrl* inputDPonderacionMatematica;
		wxStaticText* input_ciencias_sociales;
		wxTextCtrl* inputPuntajeSociales;
		wxTextCtrl* inputDPuntajeSociales;
		wxTextCtrl* inputPonderacionSociales;
		wxTextCtrl* inputDPonderacionSociales;
		wxStaticText* input_filosofia;
		wxTextCtrl* inputPuntajeFilosofia;
		wxTextCtrl* inputDPuntajeFilosofia;
		wxTextCtrl* inputPonderacionFilosofia;
		wxTextCtrl* inputDPonderacionFilosofia;
		wxStaticText* input_biologia;
		wxTextCtrl* inputPuntajeBiologia;
		wxTextCtrl* inputDPuntajeBiologia;
		wxTextCtrl* inputPonderacionBiologia;
		wxTextCtrl* inputDPonderacionBiologia;
		wxStaticText* input_quimica;
		wxTextCtrl* inputPuntajeQuimica;
		wxTextCtrl* inputDPuntajeQuimica;
		wxTextCtrl* inputPonderacionQuimica;
		wxTextCtrl* inputDPonderacionQuimica;
		wxStaticText* input_fisica;
		wxTextCtrl* inputPuntajeFisica;
		wxTextCtrl* inputDPuntajeFisica;
		wxTextCtrl* inputPonderacionFisica;
		wxTextCtrl* inputDPonderacionFisica;
		wxStaticText* m_staticText13;
		wxTextCtrl* inputPromedio;
		wxButton* boton_guardarCSV;
		wxButton* button_guardar_datos;

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
		virtual void OnRadioBoxComparar( wxCommandEvent& event ) { event.Skip(); }
		virtual void actualizarFiltroFechaInicio( wxCommandEvent& event ) { event.Skip(); }
		virtual void actualizarFiltroFechaFin( wxCommandEvent& event ) { event.Skip(); }
		virtual void actualizarFiltroAsignaturas( wxCommandEvent& event ) { event.Skip(); }
		virtual void seleccionarComponentesYCompetencias( wxCommandEvent& event ) { event.Skip(); }
		virtual void mostar_puntajes_minimos( wxCommandEvent& event ) { event.Skip(); }
		virtual void BotonBuscar( wxCommandEvent& event ) { event.Skip(); }
		virtual void BotonGuardarResultados( wxCommandEvent& event ) { event.Skip(); }
		virtual void GuardarDatosCSV( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Determinador de puntajes minimos "), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,768 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIFrame();

};

#endif //__GUIFrame__
