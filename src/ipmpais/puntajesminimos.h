/***************************************************************
 * Name:      PuntajesMinimosApp.h
 * Purpose:   Defines Application Class
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

/**
  @class PuntajesMinimos
  \brief Inicio de la aplicación

  Inicia la interfaz grafica y el generador de numeros aleatorios
*/

#ifndef SRC_IPMPAIS_PUNTAJESMINIMOS_H_
#define SRC_IPMPAIS_PUNTAJESMINIMOS_H_

#include <wx/app.h>
#include <wx/dcclient.h>

#include "algoritmogenetico/matematicas.h"
#include "gui/ventanaprincipal.h"

class PuntajesMinimos : public wxApp{
 public:
     /// Inicializa la aplicación
    virtual bool OnInit();
};

#endif  // SRC_IPMPAIS_PUNTAJESMINIMOS_H_
