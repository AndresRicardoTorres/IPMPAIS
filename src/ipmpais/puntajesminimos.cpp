/***************************************************************
 * Name:      puntajesminimos.cpp
 * Purpose:   Main para la aplicacion
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

#include "ipmpais/puntajesminimos.h"

//IMPLEMENT_APP(PuntajesMinimos);
IMPLEMENT_APP_NO_MAIN(PuntajesMinimos);
IMPLEMENT_WX_THEME_SUPPORT;

bool PuntajesMinimos::OnInit() {
    // 2012-10-21: Angel
    // Inicializo el numero aleatorio para la encriptacion
    Matematicas::crear();  // Initialize random number generator.
    VentanaPrincipal* frame = new VentanaPrincipal(0L);

    frame->Show();

    return true;
}
