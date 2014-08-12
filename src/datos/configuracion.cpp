#include "configuracion.h"

LeerConfiguracion::LeerConfiguracion()
{
    //ctor
    m_clave = "";
    m_host = "";
    m_puerto = 0;
    m_usuario = "";
}

LeerConfiguracion::~LeerConfiguracion()
{
    //dtor
}

bool LeerConfiguracion::LeerDatos()
{
    ifstream inFile;
    string linea;


    wxString path = wxStandardPaths::Get().GetExecutablePath().BeforeLast('/')+ wxT("/determinador.conf");
    std::cout<<"Usando archivo de configuracion : "<<std::string(path.mb_str()).c_str()<<std::endl;

    inFile.open(std::string(path.mb_str()).c_str());
    if (!inFile) {
        cout << "Unable to open file";
        return false;
    }

    size_t found;
    while (inFile >> linea) {
        found = linea.find("host=");
        if (found!=string::npos)
            Sethost(cutAndTrim(linea,found+5));

        found = linea.find("puerto=");
        if (found!=string::npos)
            Setpuerto(atoi(cutAndTrim(linea,found+7).c_str()));

        found = linea.find("nombrebd=");
        if (found!=string::npos){
            Setnombrebd(cutAndTrim(linea,found+9));
        }

        found = linea.find("usuario=");
        if (found!=string::npos)
            Setusuario(cutAndTrim(linea,found+8));

        found = linea.find("clave=");
        if (found!=string::npos)
            Setclave(cutAndTrim(linea,found+6));

    }

    inFile.close();
    return true;
}

string LeerConfiguracion::cutAndTrim(string palabra,int longitud)
{
    string resultado;
    stringstream trimmer;
    resultado = palabra.substr(longitud,palabra.size());
    trimmer << resultado;
    resultado.clear();
    trimmer >> resultado;
    return resultado;
}
