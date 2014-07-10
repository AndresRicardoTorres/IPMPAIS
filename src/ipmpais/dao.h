/***************************************************************
 * Name:      dao.h
 * Purpose:   Super clase con utilidades para gestión de grupos
 *            de entidades
 * Author:    Andrés Ricardo Torres Martínez (aritoma@gmail.com)
 * Created:   2012-02-12
 * Copyright: Andrés Ricardo Torres Martínez ()
 * License:
 **************************************************************/

/**
 * @class DAO
 * @brief Super clase con utilidades para gestión de grupos
 *         de entidades
 */

#ifndef DAO_H
#define DAO_H


#include <string>
#include <ctype.h>

class DAO
{
    public:
        DAO();
        virtual ~DAO();
    protected:
        std::string limpiarString(std::string str);

};

#endif // DAO_H
