#ifndef ATRIBUTO_H
#define ATRIBUTO_H

#include <string>
#include <list>

using namespace std;

class Atributo
{
    public:
        void setAtributo(const string &nombre);
        void setOp(const string &operacion);
        void setValor(const string &valor);
        void setTipo(const string &nTipo);
        void setReglas(list<int> reglas);

        string getAtributo();
        string getOp();
        string getValor();
        string getTipo();
        list<int> getReglas();

        Atributo();
        ~Atributo();


    private:
        list<int> reglas;

        struct esquema
        {
            string atributo;
            string op;
            string valor;
            string tipo;
        };

        esquema atributo;
};

#endif // ATRIBUTO_H
