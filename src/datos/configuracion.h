/***************************************************************
 * Name:      configuracion.h
 * Purpose:   Utilidad para leer archivos de configuracion
 *            generados por la aplicacion
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

/**
 * @class LeerConfiguracion
 * @brief Utilidad para leer archivos de configuracion generados por la
 * aplicacion
 *
 * Permite leer archivos con la siguiente sintaxis :
 *
 *     host=<string>
 *     puerto=<integer>
 *     nombrebd=<string>
 *     usuario=<string>
 *     clave=<string>
 *
 *
 * El archivo debe tener exactamente esas etiquetas y no tener espacios.
 *
 * El archivo debe estar en la misma carpeta del ejecutable y llamarse
 * "determinador.conf".
 *
 * El orden de las lineas no importa
 */

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
        /** Default constructor
         * Los valores por defecto son "" o 0.
         * */
        LeerConfiguracion();
        /** Default destructor */
        virtual ~LeerConfiguracion();
        /** Access m_host
         * \return The current value of m_host
         */
        string Gethost() { return m_host; }
        /** Access m_puerto
         * \return The current value of m_puerto
         */
        int Getpuerto() { return m_puerto; }
       /** Access m_usuario
         * \return The current value of m_usuario
         */
        string Getusuario() { return m_usuario; }
        /** Access m_clave
         * \return The current value of m_clave
         */
        string Getclave() { return m_clave; }
        string Getnombrebd() { return m_nombrebd; }
        /**
         * @brief Lee el archivo en la ubicacion predeterminada
         *
         * Si no se encuentra el valor en el archivo se tendran en cuenta los
         * valores por defecto.
         *
         * @return Retorna FALSE si el archivo no se encuentra en la ubicacion
         * predeterminada, caso contrario retorna TRUE
         */
        bool LeerDatos();
    protected:
    private:
        string cutAndTrim(string palabra,int longitud);
        string m_host; //!< Member variable "m_host"
        int m_puerto; //!< Member variable "m_puerto"
        string m_usuario; //!< Member variable "m_usuario"
        string m_clave; //!< Member variable "m_clave"
        string m_nombrebd; //!< Member variable "m_nombrebd"
        /** Set m_host
         * \param val New value to set
         */
        void Sethost(string val) { m_host = val; }
         /** Set m_puerto
         * \param val New value to set
         */
        void Setpuerto(int val) { m_puerto = val; }
        /** Set m_usuario
         * \param val New value to set
         */
        void Setusuario(string val) { m_usuario = val; }
        /** Set m_clave
         * \param val New value to set
         */
        void Setclave(string val) { m_clave = val; }
        /** Set m_clave
         * \param val New value to set
         */
        void Setnombrebd(string val) { m_nombrebd = val; }
};

#endif // LEERCONFIGURACION_H
