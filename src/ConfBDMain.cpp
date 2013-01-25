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
        host = wxString(objLector->Gethost().c_str(), wxConvUTF8);
        inputHost->SetValue(host);

        puerto << objLector->Getpuerto();
        inputPuerto->SetValue(puerto);

        nombrebd = wxString(objLector->Getnombrebd().c_str(), wxConvUTF8);
        inputNombrebd->SetValue(nombrebd);

        usuario = wxString(objLector->Getusuario().c_str(), wxConvUTF8);
        inputUsuario->SetValue(usuario);

        clave = wxString(objLector->Getclave().c_str(), wxConvUTF8);
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
    info << "user=" << std::string(usuario.mb_str()) << " password="<<objLector->Getclave()<<" dbname="<<objLector->Getnombrebd()<<
    " hostaddr="<<objLector->Gethost()<<" port="<<objLector->Getpuerto();
    return info.str();
}

void ConfBDDialog::OnAyuda( wxCommandEvent& event ){
    wxMessageBox(_("El boton probar intenta hacer una conexion con los datos ingresados actualmente \n El boton guardar almacena los datos de conexion en el archivo determinador.conf para futuras conexiones"), _("Ayuda"));
}

void ConfBDDialog::OnGuardar( wxCommandEvent& event ){
    wxString path = wxStandardPaths::Get().GetExecutablePath().BeforeLast('/')+ wxT("/determinador.conf");

    ofstream miArchivo;
    miArchivo.open (std::string(path.mb_str()).c_str());

    if (!miArchivo) {
        wxMessageBox(_("Unable to open file"), _("Guardar Archivo"));
        return;
    }

    miArchivo << "host=" << std::string(inputHost->GetValue().mb_str()) <<std::endl;
    miArchivo << "puerto=" << std::string(inputPuerto->GetValue().mb_str()) <<std::endl;
    miArchivo << "nombrebd=" << std::string(inputNombrebd->GetValue().mb_str()) <<std::endl;
    miArchivo << "usuario=" << std::string(inputUsuario->GetValue().mb_str()) <<std::endl;
    miArchivo << "clave=" << std::string(inputClave->GetValue().mb_str()) <<std::endl;

    miArchivo.close();
    wxMessageBox(_("Guardado con exito"), _("Guardar Archivo"));
}

void ConfBDDialog::OnProbar( wxCommandEvent& event ){

    stringstream info;

    info << "user=" << std::string(inputUsuario->GetValue().mb_str()) << " password="<<std::string(inputClave->GetValue().mb_str())<<" dbname="<<std::string(inputNombrebd->GetValue().mb_str())<<
    " hostaddr="<<std::string(inputHost->GetValue().mb_str())<<" port="<<std::string(inputPuerto->GetValue().mb_str());

    PG *objPg = new PG(info.str().c_str());
    bool hayBD = objPg->checkStatus();

    wxString msg = _("");
    if (hayBD)
        msg=_("La conexion es correcta");
    else
        msg=_("La conexion es incorrecta");
    wxMessageBox(msg, _("Estado de la conexion"));

}
