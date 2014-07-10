/***************************************************************
 * Name:      dialogoconfiguracion.h
 * Purpose:   Interfaz para el dialogo de configuración
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

#ifndef DIALOGOCONFIGURACION_H
#define DIALOGOCONFIGURACION_H

#include <fstream>
#include <wx/msgdlg.h>

#include "wx_dialogoconfiguracion.h"
#include "datos/configuracion.h"
#include "datos/postgresql.h"

/**
 * @brief Interfaz para el dialogo de configuración
 *
 * Esta clase tiene la lógica del dialogo de configuración, los elementos 
 * gráficos están en el archivo wx_dialogoconfiguracion.  
 */
class ConfBDDialog: public GUIDialog
{
    public:
        ConfBDDialog(wxDialog *dlg);
        ~ConfBDDialog();
        string getInformacion();
    private:
        LeerConfiguracion* objLector;
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnSalir(wxCommandEvent& event);
        virtual void OnAyuda( wxCommandEvent& event );
	virtual void OnGuardar( wxCommandEvent& event );
	virtual void OnProbar( wxCommandEvent& event );
	wxString host;
	wxString puerto;
	wxString nombrebd;
	wxString usuario;
	wxString clave;
};
#endif // CONFBDMAIN_H
