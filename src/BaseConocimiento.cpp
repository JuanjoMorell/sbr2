#include <iostream>
#include <string>
#include <list>
#include <cstring>
#include <sstream>
#include <fstream>


#include "BaseConocimiento.h"
#include "Atributo.h"
#include "Regla.h"
#include "configuracion.h"

void BaseConocimiento::setNReglas(int nuevoNReglas)
{
    nReglas = nuevoNReglas;
}

void BaseConocimiento::setDominio(const string &nDominio)
{
    dominio = nDominio;
}

void BaseConocimiento::setReglas(list<Regla> nuevas_reglas)
{
    reglas = nuevas_reglas;
}

int BaseConocimiento::getNReglas()
{
    return nReglas;
}

string BaseConocimiento::getObjetivo()
{
    return config.getObjetivo();
}

list<Regla> BaseConocimiento::getReglas()
{
    return reglas;
}

string BaseConocimiento::getDominio()
{
    return dominio;
}

int BaseConocimiento::reglasLeidas;

void BaseConocimiento::LeerReglas(const string &line)
{
    int nSubReglas = 1;
    Atributo *tabla = new Atributo[10];
    int indice = 0;
    string st1 = "";

    istringstream s(line);

    s >> st1;
    while(s >> st1)
    {
        char linea[st1.size()];
        strcpy(linea, st1.c_str());
        if(strcmp(linea, "y") == 0)
        {
            nSubReglas++;
        }

        Atributo atributo_aux;
        s >> st1;
        atributo_aux.setAtributo(st1);
        atributo_aux.setTipo(config.getTipoArgumento(st1));
        s >> st1;
        atributo_aux.setOp(st1);
        s >> st1;
        atributo_aux.setValor(st1);

        tabla[indice] = atributo_aux;
        indice++;
    }
    Regla regla_aux;
    regla_aux.setNumRegla(reglasLeidas + 1);
    regla_aux.setPrioridad(config.getPrioridadRegla(reglasLeidas));
    regla_aux.setSubRegla(*tabla);
    regla_aux.setNSubReglas(nReglas);
    reglas.push_back(regla_aux);
    reglasLeidas++;
}

void BaseConocimiento::LeerBaseConocimiento()
{
    getline(fichero_base, dominio);
    fichero_base >> nReglas;
    string linea = "";
    getline(fichero_base, linea);
    for(int i = 0; i < nReglas; i++)
    {
        getline(fichero_base, linea);
        LeerReglas(linea);
    }
    fichero_base.close();
}

BaseConocimiento::BaseConocimiento(ifstream &fichero_base, ifstream &fichero_config)
    :fichero_base(fichero_base), fichero_config(fichero_config), config(fichero_config)
{
    setNReglas(0);
    setDominio("");
    LeerBaseConocimiento();
}

BaseConocimiento::~BaseConocimiento()
{
    //eliminar reglas
}
