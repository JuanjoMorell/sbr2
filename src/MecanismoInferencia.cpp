#include "MecanismoInferencia.h"

#include <iostream>
#include <list>
#include <iterator>
#include <set>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <array>

#include "BaseConocimiento.h"
#include "BaseHechos.h"
#include "Atributo.h"
#include "Regla.h"

using namespace std;

extern ofstream fichero1;
extern ofstream fichero2;

bool MecanismoInferencia::contenida(string meta, list<Atributo> &hechos)
{
    for(Atributo atributo : hechos)
    {
        if(atributo.getAtributo().compare(meta) == 0)
        {
            return true;
        }
    }

    return false;
}

bool MecanismoInferencia::compararAtributos(Atributo &at1, Atributo &at2)
{
    if(at1.getAtributo().compare(at2.getAtributo()) == 0)
    {
        if(at1.getTipo().compare("NU") == 0)
        {
            //Obtener valor de los atributos
            int valor1 = stoi(at1.getValor());
            int valor2 = stoi(at2.getValor());

            string operacion = at1.getOp();
            if(operacion.compare(">") == 0)
            {
                if(valor2 > valor1) return true;
            }
            else if(operacion.compare("<") == 0)
            {
                if(valor2 < valor1) return true;
            }
            else if(operacion.compare(">=") == 0)
            {
                if(valor2 >= valor1) return true;
            }
            else if(operacion.compare("<=") == 0)
            {
                if(valor2 <= valor1) return true;
            }
            else if(operacion.compare("=") == 0)
            {
                if(valor2 == valor1) return true;
            }
        }
        else
        {
            if(at1.getValor().compare(at2.getValor()) == 0)
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

    while(!contenida(meta, hechosIniciales) || !conflictos.empty())
    {
        //Calcular conjunto conflicto
        fichero1 << "Analizando posibles reglas a aplicar" << endl;
        for(list<Regla>::iterator it = reglas.begin(); it != reglas.end(); it++)
        {
            Atributo *atributo = it->getSubRegla();
            int nReglas = it->getNSubReglas();
            int condiciones = 0;
            bool conclusion = false;
            for(int i = 0; i < nReglas; i++)
            {
                for(Atributo hechoActual : hechosIniciales)
                {
                    if(compararAtributos(atributo[i], hechoActual))
                        condiciones++;
                    if(it->getConclusion().getAtributo().compare(hechoActual.getAtributo()) == 0 &&
                       it->getConclusion().getValor().compare(hechoActual.getValor()) == 0)
                        conclusion = true;
                }
            }
            if(condiciones == nReglas && !conclusion)
            {
                fichero1 << "Regla: " << it->getNumRegla() << ", " << it->getPrioridad() << ". ";
                conflictos.push_back(*it);
                it = reglas.erase(it);
                it--;
            }
        }

        if(!conflictos.empty())
        {
            //Resolver y actualizar
            fichero1 << "Reglas que pueden ser incluidas: " << endl;
            int max_prioridad = -1;
            list<Regla>::iterator max_it;
            for(list<Regla>::iterator it = conflictos.begin(); it != conflictos.end(); it++)
            {
                if (it->getPrioridad() > max_prioridad)
                {
                    max_prioridad = it->getPrioridad();
                    max_it = it;
                }
                else if(it->getPrioridad() == max_prioridad && it->getNumRegla() < max_it->getNumRegla())
                {
                    max_it = it;
                }
            }

            //comprobar si el conflicto es adecuado
            //eliminar de conflicto
            Regla max_regla = *max_it;
            fichero1 << "Regla con mas prioridad: " << max_regla.getNumRegla() << ", prio: " << max_regla.getPrioridad() << endl;
            conflictos.erase(max_it);

            hechosIniciales.push_back(max_regla.getConclusion());

            fichero1 << "BASE ACTUALIZADA" << endl;
            for(Atributo at_actual : hechosIniciales)
            {
                fichero1<< at_actual.getAtributo() << " " << at_actual.getOp() << " " << at_actual.getValor() << endl;
            }
            fichero1 << "-------------------------------------" << endl;


        }
    }
    //Si hay meta == exito
    if(contenida(meta, hechosIniciales))
    {
        fichero1 << "TERMINADO" << endl;
        //Anadir mensaje de exito en fichero 2
        Atributo at_final = hechosIniciales.back();
        list<int> reglas_aplicadas = at_final.getReglas();

        fichero2 << "Conclusion: " << endl;
        fichero2 << at_final.getAtributo() << ", " << at_final.getValor() << endl;


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
