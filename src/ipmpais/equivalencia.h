/***************************************************************
 * Name:      equivalencia.h
 * Purpose:   Entidad que representa una equivalencia entre dos
 *            o varias asignaturas
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

/**
 * @class Equivalencia
 * @brief Entidad que representa una equivalencia entre dos
 *            o varias asignaturas
 */

#ifndef EQUIVALENCIA_H
#define EQUIVALENCIA_H


class Equivalencia
{
    public:
        Equivalencia();
        Equivalencia(const char* antigua,const char* nueva,unsigned int orden);
        virtual ~Equivalencia();
        unsigned int getOrden() { return orden; }
        void setOrden(unsigned int val) { orden = val; }
        const char*  getNueva() { return nueva; }
        void setNueva(const char*  val) { nueva = val; }
        const char*  getAntigua() { return antigua; }
        void setAntigua(const char*  val) { antigua = val; }
    protected:
    private:
        unsigned int orden;
        const char*  nueva;
        const char*  antigua;
};

#endif // EQUIVALENCIA_H
