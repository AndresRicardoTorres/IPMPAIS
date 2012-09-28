#include "LeeYaml.h"

LeeYaml::LeeYaml(std::string nombreArchivoIn)
{
	nombreArchivo=new char[nombreArchivoIn.size()];
	strcpy (nombreArchivo, nombreArchivoIn.c_str());
	cargarEquivalencias();
}

LeeYaml::~LeeYaml()
{
//dtor
}

void LeeYaml::cargarEquivalencias()
{
	std::ifstream archivo(nombreArchivo);
	std::string linea, codAntiguo, codNuevo;
	bool antiguo=true;

	while(getline(archivo,linea))
	{
		if(linea[0]!='#' && linea[0]!='-')
		{
			std::stringstream  paraCodigos(linea);

			getline(paraCodigos,codAntiguo,' ');
			if(antiguo)
			{
				std::list<std::string> codigosAnt;
				while(getline(paraCodigos,codAntiguo,' '))
				{
					if(codAntiguo[0]=='[')
						codAntiguo=codAntiguo.substr(1,codAntiguo.size()-2);
					else if(codAntiguo[codAntiguo.size()-1]==']')
						codAntiguo=codAntiguo.substr(0,codAntiguo.size()-1);

					std::string codA=codAntiguo;
					codigosAnt.push_back(codA);
				}
				listaAnteriores.push_back(codigosAnt);
				antiguo=!antiguo;
			}
			else
			{
				std::list<std::string> codigosNue;
				while(getline(paraCodigos,codNuevo,' '))
				{
					if(codNuevo[0]=='[')
						codNuevo=codNuevo.substr(1,codNuevo.size()-2);
					else if(codNuevo[codNuevo.size()-1]==']')
						codNuevo=codNuevo.substr(0,codNuevo.size()-1);

					std::string codN=codNuevo;
					codigosNue.push_back(codN);
				}
				listaNuevas.push_back(codigosNue);
				antiguo=!antiguo;
			}
		}
	}
}

listaDeListas LeeYaml::getAnteriores()
{
	return listaAnteriores;
}

listaDeListas LeeYaml::getNuevas()
{
	return listaNuevas;
}

/*

int main()
{
	LeeYaml obj("equivalenciasYAML.txt");
	obj.cargarEquivalencias();

	list<list<string> > anteriores=obj.getAnteriores();
	list<list<string> > nuevas=obj.getNuevas();

	cout<<anteriores.size()<<endl;
	cout<<nuevas.size()<<endl;

	for (list<list<string> >::iterator it1 = anteriores.begin(), it2 = nuevas.begin();
		it1 != anteriores.end() && it2 != nuevas.end();
		it1++, it2++)
	{
		for (list<string>::iterator it3 = it1->begin(), it4 = it2->begin();
			it3 != it1->end() && it4 != it2->end();
			it3++, it4++)
		{
			cout  << *it3<< " : "<< *it4 << " ~ ";
		}
		cout  << endl;
	}

// 	list<string> actual1;
// 	list<string> actual2;
// 	for(int i=0; anteriores.size(); i++)
// 	{
// 		actual1=anteriores.front();
// 		actual2=nuevas.front();
//
// 		for(int j=0; actual1.size(); j++)
// 		{
// 			cout<<actual1.front()<<" : "<<actual2.front()<<endl;
// 			actual1.pop_front();
// 			actual2.pop_front();
// 		}
//
// 		anteriores.pop_front();
// 		nuevas.pop_front();
// 	}
	return 0;
}
*/
