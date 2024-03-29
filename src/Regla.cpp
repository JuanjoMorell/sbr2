#include "Regla.h"
#include <iostream>

using namespace std;

void Regla::setSubRegla(Atributo &nuevaSubRegla)
{
    subRegla = &nuevaSubRegla;
}

void Regla::setNSubReglas(int nuevaNSubRegla)
{
    nSubReglas = nuevaNSubRegla;
}

void Regla::setPrioridad(int nuevaPrio)
{
    prioridad = nuevaPrio;
}

void Regla::setNumRegla(int n)
{
    numRegla = n;
}

void Regla::setConclusion(Atributo &nConclusion)
{
    conclusion = nConclusion;
}

Atributo *Regla::getSubRegla()
{
    return subRegla;
}

int Regla::getNSubReglas()
{
    return nSubReglas;
}

int Regla::getPrioridad()
{
    return prioridad;
}

int Regla::getNumRegla()
{
    return numRegla;
}

Atributo Regla::getConclusion()
{
    return conclusion;
}

Regla::Regla()
{
    //ctor
}

Regla::~Regla()
{
    //dtor
}
