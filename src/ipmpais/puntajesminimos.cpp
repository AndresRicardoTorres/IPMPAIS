/***************************************************************
 * Name:      puntajesminimos.cpp
 * Purpose:   Main para la aplicacion
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
#endif  // __BORLANDC__

#include "algoritmogenetico/matematicas.h"
#include "gui/ventanaprincipal.h"
#include "ipmpais/puntajesminimos.h"

IMPLEMENT_APP(PuntajesMinimos);

bool PuntajesMinimos::OnInit() {
    // 2012-10-21: Angel
    // Inicializo el numero aleatorio para la encriptacion
    Matematicas::crear();  // Initialize random number generator.
    PuntajesMinimosFrame* frame = new PuntajesMinimosFrame(0L);

    frame->Show();

    return true;
}
