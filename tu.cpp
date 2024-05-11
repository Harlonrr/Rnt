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
};

// Función para insertar una organizadora de turismo en el árbol según su código RNT
void insertarPorRNT(OrganizadoraTurismo*& raiz, OrganizadoraTurismo nuevaOrganizadora) {
    if (raiz == nullptr) {
        raiz = (OrganizadoraTurismo*)malloc(sizeof(OrganizadoraTurismo));
        *raiz = nuevaOrganizadora;
    } else if (nuevaOrganizadora.codigo_rnt < raiz->codigo_rnt) {
        insertarPorRNT(raiz->izquierda, nuevaOrganizadora);
    } else {
        insertarPorRNT(raiz->derecha, nuevaOrganizadora);
    }
}

// Función para insertar una organizadora de turismo en el subárbol según su fecha de vencimiento del RNT
void insertarPorVencimientoRNT(OrganizadoraTurismo*& raiz, OrganizadoraTurismo nuevaOrganizadora) {
    if (raiz == nullptr) {
        raiz = (OrganizadoraTurismo*)malloc(sizeof(OrganizadoraTurismo));
        *raiz = nuevaOrganizadora;
    } else if (nuevaOrganizadora.año_vencimiento_rnt < raiz->año_vencimiento_rnt ||
               (nuevaOrganizadora.año_vencimiento_rnt == raiz->año_vencimiento_rnt && nuevaOrganizadora.mes_vencimiento_rnt < raiz->mes_vencimiento_rnt) ||
               (nuevaOrganizadora.año_vencimiento_rnt == raiz->año_vencimiento_rnt && nuevaOrganizadora.mes_vencimiento_rnt == raiz->mes_vencimiento_rnt &&
                nuevaOrganizadora.dia_vencimiento_rnt < raiz->dia_vencimiento_rnt)) {
        insertarPorVencimientoRNT(raiz->izquierda, nuevaOrganizadora);
    } else {
        insertarPorVencimientoRNT(raiz->derecha, nuevaOrganizadora);
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

// Función para liberar la memoria del árbol
void liberarArbol(OrganizadoraTurismo*& raiz) {
    if (raiz != nullptr) {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        free(raiz);
        raiz = nullptr;
    }
}

// Función para encontrar el nodo mínimo en un subárbol (para el caso de eliminar un nodo con dos hijos)
OrganizadoraTurismo* encontrarMinimo(OrganizadoraTurismo* nodo) {
    OrganizadoraTurismo* actual = nodo;
    while (actual->izquierda != nullptr) {
        actual = actual->izquierda;
    }
    return actual;
}

// Función para eliminar un nodo específico del árbol principal
void eliminarNodo(OrganizadoraTurismo*& raiz, string codigo_rnt) {
    if (raiz == nullptr) {
        return;
    }

    if (codigo_rnt < raiz->codigo_rnt) {
        eliminarNodo(raiz->izquierda, codigo_rnt);
    } else if (codigo_rnt > raiz->codigo_rnt) {
        eliminarNodo(raiz->derecha, codigo_rnt);
    } else {
        // Caso 1: Nodo sin hijos o con un hijo
        if (raiz->izquierda == nullptr) {
            OrganizadoraTurismo* temp = raiz->derecha;
            free(raiz);
            raiz = temp;
        } else if (raiz->derecha == nullptr) {
            OrganizadoraTurismo* temp = raiz->izquierda;
            free(raiz);
            raiz = temp;
        }
        // Caso 2: Nodo con dos hijos
        else {
            OrganizadoraTurismo* temp = encontrarMinimo(raiz->derecha);
            raiz->codigo_rnt = temp->codigo_rnt;
            raiz->dia_vencimiento_rnt = temp->dia_vencimiento_rnt;
            raiz->mes_vencimiento_rnt = temp->mes_vencimiento_rnt;
            raiz->año_vencimiento_rnt = temp->año_vencimiento_rnt;
            raiz->nombre = temp->nombre;
            eliminarNodo(raiz->derecha, temp->codigo_rnt);
        }
    }
}

// Función para eliminar el nodo espejo correspondiente en el subárbol
void eliminarNodoEspejo(OrganizadoraTurismo* raiz, string codigo_rnt) {
    if (raiz == nullptr) {
        return;
    }

    if (codigo_rnt < raiz->codigo_rnt) {
        eliminarNodoEspejo(raiz->derecha, codigo_rnt);
    } else if (codigo_rnt > raiz->codigo_rnt) {
        eliminarNodoEspejo(raiz->izquierda, codigo_rnt);
    } else {
        // El nodo espejo encontrado en el subárbol, eliminarlo
        free(raiz);
        raiz = nullptr;
    }
}

int main() {
    OrganizadoraTurismo* raizRNT = nullptr;
    OrganizadoraTurismo* raizVencimientoRNT = nullptr;

    const int REGISTRAR = 1;
    const int MOSTRAR_PREORDEN = 2;
    const int MOSTRAR_INORDEN = 3;
    const int MOSTRAR_POSORDEN = 4;
    const int ELIMINAR = 5;
    const int SALIR = 6;

    int opcion;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Registrar organizadora de turismo" << endl;
        cout << "2. Mostrar organizadoras de turismo (Preorden)" << endl;
        cout << "3. Mostrar organizadoras de turismo (Inorden)" << endl;
        cout << "4. Mostrar organizadoras de turismo (Posorden)" << endl;
        cout << "5. Eliminar organizadora de turismo" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese su opcion: ";

        if (!(cin >> opcion)) {
            cout << "Entrada no válida. Por favor ingrese un número." << endl;
            cin.clear(); // Limpia el estado de error del stream
            cin.ignore(); // Limpia el buffer
            continue; // Continúa con el siguiente ciclo
        }

        switch(opcion) {
            case REGISTRAR: {
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

                OrganizadoraTurismo nuevaOrganizadora = { codigo_rnt, dia_vencimiento_rnt, mes_vencimiento_rnt, año_vencimiento_rnt, nombre, nullptr, nullptr };
                insertarPorRNT(raizRNT, nuevaOrganizadora);
                insertarPorVencimientoRNT(raizVencimientoRNT, nuevaOrganizadora);
                break;
            }
            case MOSTRAR_PREORDEN:
                cout << "\nOrganizadoras de turismo (Preorden):" << endl;
                cout << "Árbol por RNT:" << endl;
                preorden(raizRNT);
                cout << "Subárbol por fecha de vencimiento del RNT:" << endl;
                preorden(raizVencimientoRNT);
                break;
            case MOSTRAR_INORDEN:
                cout << "\nOrganizadoras de turismo (Inorden):" << endl;
                cout << "Árbol por RNT:" << endl;
                inorden(raizRNT);
                cout << "Subárbol por fecha de vencimiento del RNT:" << endl;
                inorden(raizVencimientoRNT);
                break;
            case MOSTRAR_POSORDEN:
                cout << "\nOrganizadoras de turismo (Posorden):" << endl;
                cout << "Árbol por RNT:" << endl;
                posorden(raizRNT);
                cout << "Subárbol por fecha de vencimiento del RNT:" << endl;
                posorden(raizVencimientoRNT);
                break;
            case ELIMINAR: {
                string codigo_rnt;
                cout << "Ingrese el código RNT de la organizadora de turismo a eliminar: ";
                cin >> codigo_rnt;
                eliminarNodo(raizRNT, codigo_rnt);
                eliminarNodoEspejo(raizVencimientoRNT, codigo_rnt);
                break;
            }
            case SALIR:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, ingrese una opción válida." << endl;
        }

    } while (opcion != SALIR);

    // Liberar memoria antes de salir
    liberarArbol(raizRNT);
    liberarArbol(raizVencimientoRNT);

    return 0;
}


