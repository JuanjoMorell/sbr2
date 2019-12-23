#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <map>

using namespace std;

#include "configuracion.h"
//#include "conocimiento.h"

string configuracion::getTipoArgumento(string tipo)
{
    return argumentos.find(tipo)->second;
}

void configuracion::setObjetivo(const string &nuevoObjetivo)
{
    objetivo = nuevoObjetivo;
}

string configuracion::getObjetivo()
{
    return objetivo;
}

ifstream &configuracion::getArchivo()
{
    return archivo_config;
}

void configuracion::setPrioridadReglas(int *nuevasPrioridades)
{
    prioridades = nuevasPrioridades;
}

int configuracion::getPrioridadRegla(int nRegla)
{
    return prioridades[nRegla];
}

void configuracion::leerReglas()
{
    int numeroReglas = 0;
    archivo_config >> numeroReglas;
    prioridades = new int[numeroReglas];
    int valor = 0;

    for(int i = 0; i < numeroReglas; i++)
    {
        archivo_config >> valor;
        prioridades[i] = valor;
    }
}

void configuracion::leerArtributos()
{
    string atributo, tipo;
    int nAtributos;

    archivo_config >> nAtributos;

    for(int i = 0; i < nAtributos; i++)
    {
        archivo_config >> atributo;
        archivo_config >> tipo;
        argumentos.insert(pair<string, string>(atributo, tipo));

        int tamano = tipo.size() + 1;
        char linea[tamano];
        strcpy(linea, tipo.c_str());
        if(strcmp(linea, "NU") != 0)
        {
            archivo_config >> atributo;
        }
    }
    getline(archivo_config, atributo);
}

int configuracion::palabrasReservadas(string palabra)
{
    if (palabra.compare("ATRIBUTOS") == 0) {
        return 1;
    } else if (palabra.compare("OBJETIVO") == 0) {
        return 2;
    } else if (palabra.compare("PRIORIDADES-REGLAS") == 0) {
        return 3;
    }

    return 0;
}

void configuracion::LeerArchivoConfig()
{
    string linea;

    while(getline(archivo_config, linea))
    {
        string objetivo;
        int pReservada = palabrasReservadas(linea);
        switch(pReservada)
        {
        case 1:
            leerArtributos();
            break;

        case 2:
            getline(archivo_config, objetivo);
            setObjetivo(objetivo);
            break;

        case 3:
            leerReglas();
            break;

        default:
            break;
        }
    }
}

configuracion::configuracion(ifstream &archivo_config) : archivo_config(archivo_config)
{
    setPrioridadReglas(nullptr);
    setObjetivo("");

    LeerArchivoConfig();
    archivo_config.close();
}

configuracion::~configuracion()
{
    delete[] prioridades;
}
