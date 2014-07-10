/***************************************************************
 * Name:      ventanaprincipal.h
 * Purpose:   Defines Application Frame
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

#ifndef SRC_GUI_VENTANAPRINCIPAL_H_
#define SRC_GUI_VENTANAPRINCIPAL_H_

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <wx/msgdlg.h>
#include <wx/wfstream.h>
#include <wx/wx.h>

#include "algoritmogenetico/algoritmogenetico.h"
#include "datos/csv.h"
#include "gui/dialogoconfiguracion.h"
#include "gui/dialogoecaes.h"
#include "gui/wx_ventanaprincipal.h"
#include "ipmpais/admisionesunivalle.h"
#include "ipmpais/calificacion.h"
#include "ipmpais/calificaciondao.h"
#include "ipmpais/equivalenciadao.h"
#include "ipmpais/estudiante.h"
#include "ipmpais/fenotipoipmpais.h"

/**
  \brief La ventana que maneja las pestañas, el menu y el llamado a dialogos

  VentanaPrincipal Hereda de wx_ventanaprincipal.h donde estan definidos las
  pestañas (pestaña lectura de datos y pestaña de resultados) y el menu.
  Estan definidos el comportamiento de los eventos en la ventana
*/


class VentanaPrincipal: public GUIFrame
{
    public:
        VentanaPrincipal(wxFrame *frame);
        ~VentanaPrincipal();
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

#endif // SRC_GUI_VENTANAPRINCIPAL_H_
