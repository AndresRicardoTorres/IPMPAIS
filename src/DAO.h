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
        std::string encriptar(std::string in);
    private:

};

#endif // DAO_H
