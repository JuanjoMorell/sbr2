#ifndef BASEHECHOS_H
#define BASEHECHOS_H

#include <list>
#include "Atributo.h"

using namespace std;

class BaseHechos
{
    public:
        void addHecho(Atributo hecho);
        list<Atributo> getHechos();

        BaseHechos(ifstream &fichero_hechos);
        ~BaseHechos();

    private:
        ifstream &fichero_hechos;
        list<Atributo> hechos;
        void LeerHechos();
};

#endif // BASEHECHOS_H
