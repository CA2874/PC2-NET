#include "pch.h"
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>
#include <sstream>
#include <ctime>
#include "BinarySearchTree.h"
#include "Sorting.h"
#include "HashTableSCH.h"

using namespace std;
using namespace System;

class Registro {
    string fecha;
    string ubilesion;
    string sexo;
    int edad;
    string tipoinc;
    int diasPerdidos;
    string planta;
    string tipoInf;
    string turno;
    string departamento;
    int costoInc;
    string wkDay;
    int mes;
    int anio;

public:
    Registro(
        string fecha,
        string ubilesion,
        string sexo,
        int edad,
        string tipoinc,
        int diasPerdidos,
        string planta,
        string tipoInf,
        string turno,
        string departamento,
        int costoInc,
        string wkDay,
        int mes,
        int anio) : fecha(fecha),
        ubilesion(ubilesion),
        sexo(sexo),
        edad(edad),
        tipoinc(tipoinc),
        diasPerdidos(diasPerdidos),
        planta(planta),
        tipoInf(tipoInf),
        turno(turno),
        departamento(departamento),
        costoInc(costoInc),
        wkDay(wkDay),
        mes(mes),
        anio(anio) {}
     
      
    int getcostoInc() {
        return this->costoInc;
    }

    friend ostream& operator<<(ostream& os, Registro r) {
        os << r.fecha << " " << r.costoInc << " " << r.edad << " " << r.diasPerdidos << " " << r.departamento << " " << r.planta;
        return os;
    }

    bool operator<(Registro b) {
        if (this->tipoinc.compare(b.tipoinc) == 0) return this->edad < b.edad;
        return this->tipoinc.compare(b.tipoinc) < 0;
    }

    bool operator>(Registro b) {
        if (this->tipoinc.compare(b.tipoinc) == 0) return (this->edad > b.edad);
        return this->tipoinc.compare(b.tipoinc) > 0;
    }
};

class BaseDeDatos {
    ifstream lectura;
    ofstream escritura;
    BinarySearchTree<Registro>* arbol;
    vector<Registro> datos;
    HashTable<Registro>* ht;
public:
    BaseDeDatos() {
        arbol = new BinarySearchTree<Registro>(
            [](Registro value) -> void {
                cout << value << "\n";
            },
            [](Registro a, Registro b) -> bool {
                return a.getcostoInc() < b.getcostoInc();
            }
            );

        ht = new HashTable<Registro>(520);
        leerLosDatos();
    }
    void leerLosDatos() {
        lectura.open("dataSeguridad.csv");
        string line;
        int j = 0;
        while (getline(lectura, line, '\n')) {
            if (j != 0) {
                stringstream s(line);
                string aux;

                string fecha;
                string ubilesion;
                string sexo;
                int edad;
                string tipoinc;
                int diasPerdidos;
                string planta;
                string tipoInf;
                string turno;
                string departamento;
                int costoInc;
                string wkDay;
                int mes;
                int anio;

                getline(s, aux, ';');
                fecha = aux;
                getline(s, aux, ';');
                ubilesion = aux;
                getline(s, aux, ';');
                sexo = aux;
                getline(s, aux, ';');
                edad = stoi(aux);
                getline(s, aux, ';');
                tipoinc = aux;
                getline(s, aux, ';');
                diasPerdidos = stoi(aux);
                getline(s, aux, ';');
                planta = aux;
                getline(s, aux, ';');
                tipoInf = aux;
                getline(s, aux, ';');
                turno = aux;
                getline(s, aux, ';');
                departamento = aux;
                getline(s, aux, ';');
                costoInc = stoi(aux);
                getline(s, aux, ';');
                wkDay = aux;
                getline(s, aux, ';');
                mes = stoi(aux);
                getline(s, aux, ';');
                anio = stoi(aux);
                Registro r(fecha, ubilesion, sexo, edad, tipoinc, diasPerdidos, planta, tipoInf, turno, departamento, costoInc, wkDay, mes, anio);
                datos.push_back(r);
                ht->insert(string(ubilesion + departamento), r);
            }
            j++;


        }
        lectura.close();
        //cout << "Mostrar HashTable usando la modificacion de cout:" << endl;
        //ht->display([](Registro v) -> void { std::cout << v << ";"; });
        shuffle();
        guardarEnBST();
    }
    void mostrarBST() {
        arbol->preOrder();
    }
    int buscarCostoIncEnUnRango(int low, int high) {
        int count = 0;
        this->arbol->roadTree(
            [&](Registro r) -> void {
                if (r.getcostoInc() >= low && r.getcostoInc() <= high) ++count;
            }
        );
        return count;
    }
    void addToList() {
        list<Registro> lista;
        this->arbol->roadTree(
            [&lista](Registro r) -> void {
                lista.push_back(r);
            }
        );
        for (Registro& r : lista) {
            std::cout << r << "\n";
        }
    }
    void ordenarPorTipInc() {
        auto compare1 = [](Registro a, Registro b) -> bool {
            return a > b;
        };
        auto compare2 = [](Registro a, Registro b) -> bool {
            return a < b;
        };

        SortingAlgorithms<Registro>::quickSort(this->datos, compare1, compare2, 0, this->datos.size() - 1);

        for (Registro& r : datos) {
            cout << r << "--";
        }
        cout << "\n";
    }
    void mostrarHashTable() {
        ht->display([](Registro value) -> void {
            cout << value << "\n";
            });
    }
private:
    void guardarEnBST() {
        for (Registro& r : datos)
            this->arbol->insert(r);
    }
    void shuffle() {
        for (int i = datos.size() - 1; i > 0; --i) {
            // [0,i> => 0 + rand() % ( (i - 1) - 0 + 1);
            int pos = 0 + rand() % i;
            this->swap(datos[i], datos[pos]);
        }
    }
    void swap(Registro& a, Registro& b) {
        Registro c = a;
        a = b;
        b = c;
    }
};

int main() {
    BaseDeDatos bd;
    bd.mostrarBST();
    cout << "\n";
    std::cout << bd.buscarCostoIncEnUnRango(0, 5000) << "\n";
    bd.addToList();
    std::cout << "\n";
    bd.ordenarPorTipInc();
    bd.mostrarHashTable();
    return 0;
}
