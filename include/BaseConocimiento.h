#ifndef BASECONOCIMIENTO_H
#define BASECONOCIMIENTO_H

#include <string>
#include <list>
#include "Regla.h"
#include "configuracion.h"

class BaseConocimiento
{
    public:
        void setNReglas(int nuevoNReglas);
        void setDominio(const string &nDominio);
        void setReglas(list<Regla> nuevas_reglas);

        int getNReglas();
        string getObjetivo();
        list<Regla> getReglas();
        string getDominio();

        BaseConocimiento(ifstream &fichero_base, ifstream &fichero_config);
        ~BaseConocimiento();

    private:
        ifstream &fichero_base;
        ifstream &fichero_config;
        string dominio;
        string objetivo;
        list<Regla> reglas;
        configuracion config;
        int nReglas;
        static int reglasLeidas;

        void LeerBaseConocimiento();
        void LeerReglas(const string &line);
};

#endif // BASECONOCIMIENTO_H
