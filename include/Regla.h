#ifndef REGLA_H
#define REGLA_H

#include <string>
#include "Atributo.h"

using namespace std;

class Regla
{
    public:
        void setSubRegla(Atributo &nuevaSubRegla);
        void setNSubReglas(int nuevaNSubRegla);
        void setPrioridad(int nuevaPrio);
        void setNumRegla(int n);
        void setConclusion(Atributo &nConclusion);

        Atributo *getSubRegla();
        int getNSubReglas();
        int getPrioridad();
        int getNumRegla();
        Atributo getConclusion();

        Regla();
        ~Regla();


    private:
        int numRegla;
        int nSubReglas;
        int prioridad;
        Atributo conclusion;
        Atributo *subRegla;
};

#endif // REGLA_H
