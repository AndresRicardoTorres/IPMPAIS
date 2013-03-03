#include "DialogoEcaes.h"

DialogoEcaes::DialogoEcaes( wxWindow* parent )
:
GUIDialogoEcaes( parent )
{

}

std::string DialogoEcaes::getOpciones(){
    opciones.clear();
    opciones.push_back(m_checkComponente1->IsChecked());
    opciones.push_back(m_checkComponente2->IsChecked());
    opciones.push_back(m_checkComponente3->IsChecked());
    opciones.push_back(m_checkComponente4->IsChecked());
    opciones.push_back(m_checkComponente5->IsChecked());
    opciones.push_back(m_checkComponente6->IsChecked());
    opciones.push_back(m_checkComponente7->IsChecked());

    opciones.push_back(m_checkBoxCompetencia1->IsChecked());
    opciones.push_back(m_checkBoxCompetencia2->IsChecked());
    opciones.push_back(m_checkBoxCompetencia3->IsChecked());

    opciones.push_back(m_checkBoxTotal->IsChecked());

    std::string codigo;

    cantidad_componentes = 0;
    for(unsigned int i = 0;i<7;i++)
    {
        if(opciones[i]){
            cantidad_componentes++;
            codigo.append("1");
        }
        else{
            codigo.append("0");
        }
    }

    cantidad_competencias = 0;
    for(unsigned int i = 7;i<10;i++)
    {
        if(opciones[i]){
            cantidad_competencias++;
            codigo.append("1");
        }else{
            codigo.append("0");
        }
    }

    cantidad_total = (opciones[10])?1:0;
    if(opciones[10])
        codigo.append("1");
    else
        codigo.append("0");

    return codigo;
}

void DialogoEcaes::botonAceptar( wxCommandEvent& event ){
    this->Show(false);
}

unsigned int DialogoEcaes::getCantidadComponentes(){
    getOpciones();
    return cantidad_componentes;
}

unsigned int DialogoEcaes::getCantidadCompetencias(){
    getOpciones();
    return cantidad_competencias;
}

unsigned int DialogoEcaes::getCantidadTotal(){
    getOpciones();
    return cantidad_total;
}

void DialogoEcaes::verificarSeleccion( wxCommandEvent& event )
{
    if( m_checkComponente1->IsChecked()  || m_checkComponente2->IsChecked() ||
        m_checkComponente3->IsChecked() || m_checkComponente4->IsChecked() ||
        m_checkComponente5->IsChecked() || m_checkComponente6->IsChecked() ||
        m_checkComponente7->IsChecked() || m_checkBoxCompetencia1->IsChecked() ||
        m_checkBoxCompetencia2->IsChecked() ||m_checkBoxCompetencia3->IsChecked()
       ){
          m_checkBoxTotal->SetValue(false);
       }

}

void DialogoEcaes::verificarSeleccionTotal( wxCommandEvent& event ){
    if(m_checkBoxTotal->IsChecked())
    {
        m_checkComponente1->SetValue(false);
        m_checkComponente2->SetValue(false);
        m_checkComponente3->SetValue(false);
        m_checkComponente4->SetValue(false);
        m_checkComponente5->SetValue(false);
        m_checkComponente6->SetValue(false);
        m_checkComponente7->SetValue(false);

        m_checkBoxCompetencia1->SetValue(false);
        m_checkBoxCompetencia2->SetValue(false);
        m_checkBoxCompetencia3->SetValue(false);
    }
}


