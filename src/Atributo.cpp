#include "Atributo.h"
#include <string>
#include <string.h>

using namespace std;

void Atributo::setReglas(list <int> nuevas_reglas)
{
    reglas = nuevas_reglas;
}

void Atributo::setAtributo(const string &nombre)
{
    atributo.atributo = nombre;
}

void Atributo::setOp(const string &operacion)
{
    atributo.op = operacion;
}

void Atributo::setValor(const string &valor)
{
  atributo.valor = valor;
}

void Atributo::setTipo(const string &nTipo)
{
  atributo.tipo = nTipo;
}

string Atributo::getAtributo()
{
  return atributo.atributo;
}

string Atributo::getOp()
{
  return atributo.op;
}

string Atributo::getValor()
{
  return atributo.valor;
}

string Atributo::getTipo()
{
  return atributo.tipo;
}

list<int> Atributo::getReglas()
{
    return reglas;
}

Atributo::Atributo()
{
    //ctor
}

Atributo::~Atributo()
{
    //dtor
}
