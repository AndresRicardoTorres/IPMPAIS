#ifndef LEERCONFIGURACION_H
#define LEERCONFIGURACION_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <wx/stdpaths.h>

using namespace std;

class LeerConfiguracion
{
    public:
        /** Default constructor */
        LeerConfiguracion();
        /** Default destructor */
        virtual ~LeerConfiguracion();
        /** Access m_host
         * \return The current value of m_host
         */
        string Gethost() { return m_host; }
        /** Set m_host
         * \param val New value to set
         */
        void Sethost(string val) { m_host = val; }
        /** Access m_puerto
         * \return The current value of m_puerto
         */
        int Getpuerto() { return m_puerto; }
        /** Set m_puerto
         * \param val New value to set
         */
        void Setpuerto(int val) { m_puerto = val; }
        /** Access m_usuario
         * \return The current value of m_usuario
         */
        string Getusuario() { return m_usuario; }
        /** Set m_usuario
         * \param val New value to set
         */
        void Setusuario(string val) { m_usuario = val; }
        /** Access m_clave
         * \return The current value of m_clave
         */
        string Getclave() { return m_clave; }
        /** Set m_clave
         * \param val New value to set
         */
        void Setclave(string val) { m_clave = val; }
        string Getnombrebd() { return m_nombrebd; }
        /** Set m_clave
         * \param val New value to set
         */
        void Setnombrebd(string val) { m_nombrebd = val; }
        bool LeerDatos();
    protected:
    private:
        string cutAndTrim(string palabra,int longitud);
        string m_host; //!< Member variable "m_host"
        int m_puerto; //!< Member variable "m_puerto"
        string m_usuario; //!< Member variable "m_usuario"
        string m_clave; //!< Member variable "m_clave"
        string m_nombrebd; //!< Member variable "m_nombrebd"
};

#endif // LEERCONFIGURACION_H
