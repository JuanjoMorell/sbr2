#include "MecanismoInferencia.h"

#include <iostream>
#include <list>
#include <iterator>
#include <set>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#include "BaseConocimiento.h"
#include "BaseHechos.h"
#include "Atributo.h"
#include "Regla.h"

using namespace std;

extern ofstream fichero1;
extern ofstream fichero2;

bool MecanismoInferencia::contenida(string meta, BaseHechos& hechos)
{
    list<Atributo> hechosActuales = hechos.getHechos();
    for(Atributo atributo : hechosActuales)
    {
        if(atributo.getAtributo().compare(meta) == 0)
        {
            return true;
        }
    }

    return false;
}

bool MecanismoInferencia::EncaminamientoDelante(BaseConocimiento& conocimiento, BaseHechos& hechos)
{
    list<Atributo> hechosIniciales(hechos.getHechos());
    list<Regla> reglas(conocimiento.getReglas());
    list<Regla> conflictos;

    //Inicializacion de los ficheros
    fichero1 << "Dominio de la aplicacion: " << conocimiento.getDominio() << endl;
    fichero1 << "Atributo objetivo: " << conocimiento.getObjetivo() << endl;
    fichero1 << "-------------------------------------" << endl;

    fichero1 << "BH INICIAL" << endl;
    for(Atributo atributo : hechosIniciales)
    {
        fichero1 << atributo.getAtributo() << " " << atributo.getOp() << " " << atributo.getValor() << endl;
    }
    fichero1 << "-------------------------------------" << endl;

    fichero2 << "Dominio de la aplicacion: " << conocimiento.getDominio() << endl;
    fichero2 << "Atributo objetivo: " << conocimiento.getObjetivo() << endl;
    fichero2 << "-------------------------------------" << endl;

    string meta = conocimiento.getObjetivo();

    while(!contenida(meta, hechos) || !conflictos.empty())
    {
        //Calcular conjunto conflicto
        for(Regla regla : reglas)
        {
            Atributo *atributo = regla.getSubRegla();

            for(int i = 0; regla.getNSubReglas(); i++)
            {
                for(Atributo hechosActuales : hechos)
                {
                    //Si son iguales los atributos se add a conflictos y se elimina de las reglas

                }
            }
        }

        if(!conflictos.empty())
        {
            //Resolver y actualizar
        }
    }
    //Si hay meta == exito
    if(contenida(meta, hechos))
    {
        //Anadir mensaje de exito
        return true;
    }

    //Anadir mensaje de error
    return false;
}

MecanismoInferencia::MecanismoInferencia()
{
    //ctor
}

MecanismoInferencia::~MecanismoInferencia()
{
    //dtor
}


/*
funcion ENCADENAMIENTO-HACIA-DELANTE
    BH=HechosIniciales;
    ConjuntoConflicto={ };
    ReglasAplicadas={ };
    repetir
        ConjuntoConflicto=ConjuntoConflicto-ReglasAplicadas;
        ConjuntoConflicto=ConjuntoConflicto+Equiparar(antecedente(BC),BH);
        si NoVacio(ConjuntoConflicto) entonces
            R=Resolver(ConjuntoConflicto);
            NuevosHechos=Aplicar(R,BH); ReglasAplicadas=ReglasAplicadas+{R}
            Actualizar(BH,NuevosHechos);
        fin si
    hasta Contenida(Meta,BH) o Vacio(ConjuntoConflicto);
    si Contenida(Meta,BH)entonces devolver ‘’exito’’
fin si
*/
