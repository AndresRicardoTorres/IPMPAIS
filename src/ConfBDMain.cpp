/***************************************************************
 * Name:      ConfBDMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ConfBDMain.h"
#include <iostream>


ConfBDDialog::ConfBDDialog(wxDialog *dlg)
    : GUIDialog(dlg)
{
    objLector = new LeerConfiguracion();
    if(objLector->LeerDatos()){
        wxString host(objLector->Gethost().c_str(), wxConvUTF8);
        inputHost->SetValue(host);

        wxString puerto;
        puerto << objLector->Getpuerto();
        inputPuerto->SetValue(puerto);

        wxString nombrebd(objLector->Getnombrebd().c_str(), wxConvUTF8);
        inputNombrebd->SetValue(nombrebd);

        wxString usuario(objLector->Getusuario().c_str(), wxConvUTF8);
        inputUsuario->SetValue(usuario);

        wxString clave(objLector->Getclave().c_str(), wxConvUTF8);
        inputClave->SetValue(clave);
    }
}

ConfBDDialog::~ConfBDDialog()
{
//Destroy();
}

void ConfBDDialog::OnClose(wxCloseEvent &event)
{
    Show(false);
}

void ConfBDDialog::OnSalir(wxCommandEvent &event)
{
    Show(false);
}

string ConfBDDialog::getInformacion()
{
    stringstream info;
    info << "user=" << objLector->Getusuario() << " password="<<objLector->Getclave()<<" dbname="<<objLector->Getnombrebd()<<
    " hostaddr="<<objLector->Gethost()<<" port="<<objLector->Getpuerto();
    return info.str();
}

void ConfBDDialog::OnAyuda( wxCommandEvent& event ){

}

void ConfBDDialog::OnGuardar( wxCommandEvent& event ){

}

void ConfBDDialog::OnProbar( wxCommandEvent& event ){

}
