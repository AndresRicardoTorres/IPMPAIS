#ifndef __DialogoEcaes__
#define __DialogoEcaes__

/**
@file
Subclass of GUIDialogoEcaes, which is generated by wxFormBuilder.
*/

#include "wx_dialogoecaes.h"
#include <vector>
#include <string>

/** Implementing GUIDialogoEcaes */

/**
 * @brief Interfaz para el dialogo de filtros de la opción ECAES.
 *
 * En esta clase solo esta la lógica de la interfaz, los elementos gráficos
 * están en la clase GUIDialogoEcaes 
 */
class DialogoEcaes : public GUIDialogoEcaes
{
public:
	/** Constructor */
	DialogoEcaes( wxWindow* parent );
    std::string getOpciones();

    unsigned int getCantidadComponentes();
    unsigned int getCantidadCompetencias();
    unsigned int getCantidadTotal();
private:
    std::vector<bool> opciones;
    unsigned int cantidad_componentes;
    unsigned int cantidad_competencias;
    unsigned int cantidad_total;
    virtual void botonAceptar( wxCommandEvent& event );
    virtual void verificarSeleccion( wxCommandEvent& event );
    virtual void verificarSeleccionTotal( wxCommandEvent& event );
};

#endif // __DialogoEcaes__
