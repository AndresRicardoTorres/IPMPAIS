/***************************************************************
 * Name:      PuntajesMinimosMain.h
 * Purpose:   Defines Application Frame
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

#ifndef PUNTAJESMINIMOSMAIN_H
#define PUNTAJESMINIMOSMAIN_H

#define CODIGOS_ENCRIPTADOS FALSE

#include "algoritmogenetico/algoritmogenetico.h"
#include "ipmpais/fenotipoipmpais.h"
#include "ipmpais/admisionesunivalle.h"

#include "gui/confbdmain.h"
#include "ipmpais/calificacion.h"
#include "wx_ventanaprincipal.h"
#include "datos/csv.h"
#include "gui/dialogoecaes.h"

#include "ipmpais/equivalenciadao.h"
#include "ipmpais/calificaciondao.h"
#include "ipmpais/estudiante.h"

#include <wx/wfstream.h>
#include <wx/msgdlg.h>
#include <wx/wx.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
//#include <algorithm>


#if CODIGOS_ENCRIPTADOS
    #include <openssl/sha.h>
    #include <iomanip>
    #include <ctime>
#endif

class PuntajesMinimosFrame: public GUIFrame
{
    public:
        PuntajesMinimosFrame(wxFrame *frame);
        ~PuntajesMinimosFrame();
    private:

        ConfBDDialog* dialogo_configuracion_base_datos;
        DialogoEcaes* dialogo_ecaes;

        char filename[1024];
        int un_numero_aleatorio;
        int filtro_completitud_datos;
        int filtro_fecha_inicio;
        int filtro_fecha_final;
        int cantidad_estudiantes_filtrados;
        std::string listadoAsignaturas;
        std::string opcionesEcaes;
        int cuantosComponentesExamenIngreso;
        double puntajeMinimo_minimo;
        double puntajeMinimo_maximo; //El maximo que he visto es 116.95
        double ponderacion_minimo;
        double ponderacion_maximo;

        bool cargarArchivo();
        string limpiarString(string str);
        string encriptar(string in);

        virtual void OnRadioBoxComparar( wxCommandEvent& event );
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnBDConfig( wxCommandEvent& event );
        virtual void cargarInformacionAdmisiones( wxCommandEvent& event );
        virtual void CagarPuntajesICFES( wxCommandEvent& event );
		virtual void cargarInformacionEquivalencias( wxCommandEvent& event );
		virtual void cargarInformacionRegistroAcademico( wxCommandEvent& event );
		virtual void cargarInformacionECAES( wxCommandEvent& event );
		virtual void BotonBuscar( wxCommandEvent& event );
		virtual void BotonGuardarResultados( wxCommandEvent& event );
		virtual void GuardarDatosCSV( wxCommandEvent& event );
		const char* getInformacionConexion();
		virtual void mostar_puntajes_minimos( wxCommandEvent& event );

		bool checkDB();
		void informar(const char* mensaje);
		bool comprobarConexionBD();
		void actualizarCantidadMuestra();

		virtual void actualizarFiltroFechaInicio( wxCommandEvent& event );
		virtual void actualizarFiltroFechaFin( wxCommandEvent& event );
		virtual void actualizarFiltroAsignaturas( wxCommandEvent& event );
		void actualizarInterfaz();

		virtual void seleccionarComponentesYCompetencias( wxCommandEvent& event );

};

#endif // PUNTAJESMINIMOSMAIN_H