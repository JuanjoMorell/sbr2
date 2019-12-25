#include "BaseHechos.h"
#include <string>
#include <iostream>
#include <fstream>

#include "BaseHechos.h"
using namespace std;

void BaseHechos::addHecho(Atributo hecho)
{
    hechos.push_front(hecho);
}

list<Atributo> BaseHechos::getHechos()
{
    return hechos;
}

void BaseHechos::LeerHechos()
{
    int nHechos = 0;
    fichero_hechos >> nHechos;
    string linea = "";

    getline(fichero_hechos, linea);
    for(int i = 0; i < nHechos; i++)
    {
        Atributo hecho;
        string aux = "";
        fichero_hechos >> aux;
        hecho.setAtributo(aux);
        fichero_hechos >> aux;
        hecho.setOp(aux);
        fichero_hechos >> aux;
        hecho.setValor(aux);

        addHecho(hecho);
        getline(fichero_hechos, linea);
    }
}

BaseHechos::BaseHechos(ifstream &fichero_hechos) :fichero_hechos(fichero_hechos)
{
    LeerHechos();
}

BaseHechos::~BaseHechos()
{
    fichero_hechos.close();
}
