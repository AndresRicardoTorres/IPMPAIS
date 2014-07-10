#include "dao.h"

DAO::DAO()
{
    //ctor
}

DAO::~DAO()
{
    //dtor
}

std::string DAO::limpiarString(std::string str)
{
    std::string res;
    for (size_t i=0; i<str.length(); ++i)
        if(str[i] != ' ')
            res+=tolower(str[i]);
    return res;
}

std::string DAO::encriptar(std::string in){

#if CODIGOS_ENCRIPTADOS
    // a sha1 hash is 20 bytes
    std::stringstream sstm;
    sstm << un_numero_aleatorio << in;
    string input = sstm.str();

    unsigned char hash[20];
    SHA1((unsigned char*)input.c_str(), input.size(), hash);
    sstm.str(string());
    sstm.str(std::string());
    for(int i = 0; i < 20; ++i) {
        sstm << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return sstm.str();
 #endif
    return in;
}
