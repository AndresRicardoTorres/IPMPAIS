/***************************************************************
 * Name:      ConfBDMain.h
 * Purpose:   Defines Application Frame
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

#ifndef CONFBDMAIN_H
#define CONFBDMAIN_H

#include <fstream>
#include <wx/msgdlg.h>

#include "guidialog.h"
#include "datos/configuracion.h"
#include "datos/postgresql.h"

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
