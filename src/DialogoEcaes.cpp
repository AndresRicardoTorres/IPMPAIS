#include "DialogoEcaes.h"

DialogoEcaes::DialogoEcaes( wxWindow* parent )
:
GUIDialogoEcaes( parent )
{

}

std::vector<bool> DialogoEcaes::getOpciones(){
    std::vector<bool> a;
    a.push_back(m_checkComponente1->IsChecked());
    a.push_back(m_checkComponente2->IsChecked());
    a.push_back(m_checkComponente3->IsChecked());
    a.push_back(m_checkComponente4->IsChecked());
    a.push_back(m_checkComponente5->IsChecked());
    a.push_back(m_checkComponente6->IsChecked());
    a.push_back(m_checkComponente7->IsChecked());

    a.push_back(m_checkBoxCompetencia1->IsChecked());
    a.push_back(m_checkBoxCompetencia2->IsChecked());
    a.push_back(m_checkBoxCompetencia3->IsChecked());

    a.push_back(m_checkBoxTotal->IsChecked());
    return a;
}

void DialogoEcaes::botonAceptar( wxCommandEvent& event ){
    this->Show(false);
}
