#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <list>

#include "configuracion.h"
#include "Regla.h"
#include "Atributo.h"
#include "BaseConocimiento.h"
#include "BaseHechos.h"
#include "MecanismoInferencia.h"

using namespace std;

ofstream fichero1;
ofstream fichero2;

int main(int argc, char const *argv[])
{
    ifstream fichero_conocimiento(argv[1]);
    ifstream fichero_config(argv[2]);
    ifstream fichero_hechos(argv[3]);

    string nombreBH =  argv[3];
    nombreBH = nombreBH.substr(nombreBH.size() - 6, nombreBH.size());
    string nombre1 = "Salida1-" + nombreBH;
    string nombre2 = "Salida2-" + nombreBH;


    fichero1.open(nombre1);
    fichero2.open(nombre2);

    BaseConocimiento *conocimiento = new BaseConocimiento(fichero_conocimiento, fichero_config);
    BaseHechos *hechos = new BaseHechos(fichero_hechos);

    //inferencia
    MecanismoInferencia *inferencia = new MecanismoInferencia();
    inferencia->EncaminamientoDelante(*conocimiento, *hechos);

    delete conocimiento;
    delete hechos;

    return 0;
}
