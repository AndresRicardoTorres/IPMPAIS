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


#include "PuntajesMinimosApp.h"

#include "algoritmogenetico.h"
#include "fenotipoipmpais.h"
#include "admisionesunivalle.h"

#include "ConfBDMain.h"
#include "DialogoAsignaturas.h"
#include "Calificacion.h"
#include "GUIFrame.h"
#include "LeerCSV.h"
#include "LeeYaml.h"

#include "EquivalenciaDAO.h"
#include "CalificacionDAO.h"
#include "EstudianteDAO.h"

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
        DialogoAsignaturas* dialogo_asignaturas;


        char filename[1024];
        int un_numero_aleatorio;
        int filtro_completitud_datos;
        int filtro_fecha_inicio;
        int filtro_fecha_final;
        int cantidad_estudiantes_filtrados;
        std::string listadoAsignaturas;


        bool cargarArchivo(int opcion);
        string limpiarString(string str);
        string encriptar(string in);

        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnBDConfig( wxCommandEvent& event );
        virtual void OnPaint( wxPaintEvent& event );
        virtual void cargarInformacionAdmisiones( wxCommandEvent& event );
        virtual void CagarPuntajesICFES( wxCommandEvent& event );
		virtual void cargarInformacionEquivalencias( wxCommandEvent& event );
		virtual void cargarInformacionRegistroAcademico( wxCommandEvent& event );
		virtual void cargarInformacionECAES( wxCommandEvent& event );
		virtual void OnRadioBoxFiltroCompletitud( wxCommandEvent& event );
		virtual void BotonBuscar( wxCommandEvent& event );
		const char* getInformacionConexion();
		virtual void mostar_puntajes_minimos( wxCommandEvent& event );

		bool checkDB();
		void informar(const char* mensaje);
		bool comprobarConexionBD();
		void actualizarCantidadMuestra();

		virtual void actualizarFiltroFechaInicio( wxCommandEvent& event );
		virtual void actualizarFiltroFechaFin( wxCommandEvent& event );

};

#endif // PUNTAJESMINIMOSMAIN_H
