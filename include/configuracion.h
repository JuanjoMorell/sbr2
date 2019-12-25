#ifndef CONFIGURACION_H
#define CONFIGURACION_H

using namespace std;

#include <string>
#include <map>

class configuracion
{
    public:
        void setObjetivo(const string &nuevoObjetivo);
        void setPrioridadReglas(int *nuevasPrioridades);
        string getObjetivo();
        ifstream& getArchivo();
        int getPrioridadRegla(int nRegla);
        string getTipoArgumento(string tipo);
        configuracion(ifstream &archivo_config);
        virtual ~configuracion();

    private:
        int *prioridades;
        string objetivo;
        map<string, string> argumentos;
        ifstream &archivo_config;

        void leerArtributos();
        void leerReglas();
        int palabrasReservadas(string palabra);
        void LeerArchivoConfig();
};

#endif // CONFIGURACION_H
