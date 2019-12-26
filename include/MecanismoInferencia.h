#ifndef MECANISMOINFERENCIA_H
#define MECANISMOINFERENCIA_H

#include "BaseConocimiento.h"
#include "BaseHechos.h"

class MecanismoInferencia
{
    public:
        bool EncaminamientoDelante(BaseConocimiento &conocimiento, BaseHechos &hechos);

        MecanismoInferencia();
        ~MecanismoInferencia();

    private:
        bool contenida(string meta, list<Atributo> &hechos);
        bool compararAtributos(Atributo &at1, Atributo &at2);
};

#endif // MECANISMOINFERENCIA_H
