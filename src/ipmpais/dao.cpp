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
