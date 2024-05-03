#include <iostream>
#include <string>
using namespace std;

// Estructura para representar una organizadora de turismo
struct OrganizadoraTurismo {
    string codigo_rnt;
    int dia_vencimiento_rnt;
    int mes_vencimiento_rnt;
    int año_vencimiento_rnt;
    string nombre;
    OrganizadoraTurismo* izquierda;
    OrganizadoraTurismo* derecha;

    OrganizadoraTurismo(string codigo_rnt, int dia_vencimiento_rnt, int mes_vencimiento_rnt, int año_vencimiento_rnt, string nombre) {
        this->codigo_rnt = codigo_rnt;
        this->dia_vencimiento_rnt = dia_vencimiento_rnt;
        this->mes_vencimiento_rnt = mes_vencimiento_rnt;
        this->año_vencimiento_rnt = año_vencimiento_rnt;
        this->nombre = nombre;
        this->izquierda = nullptr;
        this->derecha = nullptr;
    }
};

// Función para insertar una organizadora de turismo en el árbol según su código RNT
void insertarPorRNT(OrganizadoraTurismo*& raiz, OrganizadoraTurismo* nuevaOrganizadora) {
    if (raiz == nullptr) {
        raiz = nuevaOrganizadora;
    } else {
        if (nuevaOrganizadora->codigo_rnt < raiz->codigo_rnt) {
            insertarPorRNT(raiz->izquierda, nuevaOrganizadora);
        } else {
            insertarPorRNT(raiz->derecha, nuevaOrganizadora);
        }
    }
}

// Función para insertar una organizadora de turismo en el subárbol según su fecha de vencimiento del RNT
void insertarPorVencimientoRNT(OrganizadoraTurismo*& raiz, OrganizadoraTurismo* nuevaOrganizadora) {
    if (raiz == nullptr) {
        raiz = nuevaOrganizadora;
    } else {
        if (nuevaOrganizadora->año_vencimiento_rnt < raiz->año_vencimiento_rnt) {
            insertarPorVencimientoRNT(raiz->izquierda, nuevaOrganizadora);
        } else if (nuevaOrganizadora->año_vencimiento_rnt > raiz->año_vencimiento_rnt) {
            insertarPorVencimientoRNT(raiz->derecha, nuevaOrganizadora);
        } else {
            if (nuevaOrganizadora->mes_vencimiento_rnt < raiz->mes_vencimiento_rnt) {
                insertarPorVencimientoRNT(raiz->izquierda, nuevaOrganizadora);
            } else if (nuevaOrganizadora->mes_vencimiento_rnt > raiz->mes_vencimiento_rnt) {
                insertarPorVencimientoRNT(raiz->derecha, nuevaOrganizadora);
            } else {
                if (nuevaOrganizadora->dia_vencimiento_rnt < raiz->dia_vencimiento_rnt) {
                    insertarPorVencimientoRNT(raiz->izquierda, nuevaOrganizadora);
                } else {
                    insertarPorVencimientoRNT(raiz->derecha, nuevaOrganizadora);
                }
            }
        }
    }
}

// Función para recorrer el árbol en preorden
void preorden(OrganizadoraTurismo* raiz) {
    if (raiz != nullptr) {
        cout << "Codigo RNT: " << raiz->codigo_rnt << " - Fecha de vencimiento del RNT: " << raiz->dia_vencimiento_rnt << "/" << raiz->mes_vencimiento_rnt << "/" << raiz->año_vencimiento_rnt
             << " - Nombre: " << raiz->nombre << endl;
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

// Función para recorrer el árbol en inorden
void inorden(OrganizadoraTurismo* raiz) {
    if (raiz != nullptr) {
        inorden(raiz->izquierda);
        cout << "Codigo RNT: " << raiz->codigo_rnt << " - Fecha de vencimiento del RNT: " << raiz->dia_vencimiento_rnt << "/" << raiz->mes_vencimiento_rnt << "/" << raiz->año_vencimiento_rnt
             << " - Nombre: " << raiz->nombre << endl;
        inorden(raiz->derecha);
    }
}

// Función para recorrer el árbol en posorden
void posorden(OrganizadoraTurismo* raiz) {
    if (raiz != nullptr) {
        posorden(raiz->izquierda);
        posorden(raiz->derecha);
        cout << "Codigo RNT: " << raiz->codigo_rnt << " - Fecha de vencimiento del RNT: " << raiz->dia_vencimiento_rnt << "/" << raiz->mes_vencimiento_rnt << "/" << raiz->año_vencimiento_rnt
             << " - Nombre: " << raiz->nombre << endl;
    }
}

int main() {
    OrganizadoraTurismo* raizRNT = nullptr;
    OrganizadoraTurismo* raizVencimientoRNT = nullptr;
    int opcion;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Registrar organizadora de turismo" << endl;
        cout << "2. Mostrar organizadoras de turismo (Preorden)" << endl;
        cout << "3. Mostrar organizadoras de turismo (Inorden)" << endl;
        cout << "4. Mostrar organizadoras de turismo (Posorden)" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                string codigo_rnt, nombre;
                int dia_vencimiento_rnt, mes_vencimiento_rnt, año_vencimiento_rnt;
                cout << "Ingrese el código RNT de la organizadora de turismo: ";
                cin >> codigo_rnt;
                cout << "Ingrese el día de vencimiento del RNT: ";
                cin >> dia_vencimiento_rnt;
                cout << "Ingrese el mes de vencimiento del RNT: ";
                cin >> mes_vencimiento_rnt;
                cout << "Ingrese el año de vencimiento del RNT: ";
                cin >> año_vencimiento_rnt;
                cout << "Ingrese el nombre de la organizadora de turismo: ";
                cin.ignore(); // Para limpiar el buffer del teclado antes de getline
                getline(cin, nombre);

                OrganizadoraTurismo* nuevaOrganizadora = new OrganizadoraTurismo(codigo_rnt, dia_vencimiento_rnt, mes_vencimiento_rnt, año_vencimiento_rnt, nombre);
                insertarPorRNT(raizRNT, nuevaOrganizadora);
                insertarPorVencimientoRNT(raizVencimientoRNT, nuevaOrganizadora);
                break;
            }
            case 2:
                cout << "\nOrganizadoras de turismo (Preorden):" << endl;
                cout << "Árbol por RNT:" << endl;
                preorden(raizRNT);
                cout << "Subárbol por fecha de vencimiento del RNT:" << endl;
                preorden(raizVencimientoRNT);
                break;
            case 3:
                cout << "\nOrganizadoras de turismo (Inorden):" << endl;
                cout << "Árbol por RNT:" << endl;
                inorden(raizRNT);
                cout << "Subárbol por fecha de vencimiento del RNT:" << endl;
                inorden(raizVencimientoRNT);
                break;
            case 4:
                cout << "\nOrganizadoras de turismo (Posorden):" << endl;
                cout << "Árbol por RNT:" << endl;
                posorden(raizRNT);
                cout << "Subárbol por fecha de vencimiento del RNT:" << endl;
                posorden(raizVencimientoRNT);
                break;
            case 5:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor ingrese una opción válida." << endl;
        }

    } while (opcion != 5);

    return 0;
}

