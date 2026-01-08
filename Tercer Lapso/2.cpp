#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;
#include <vector>
#include <string>
#include <sstream>

//Usé sstream para convertir los números a texto. Eso era necesario para saber cuántos caracteres ocupa cada número y así poder calcular los espacios exactos para que el árbol quedara bien alineado.

// Estructura del nodo del árbol binario
struct Nodo {
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;
};

// Función para crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevo = new Nodo;
    nuevo->dato = valor;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

// Función para insertar un nodo en el árbol binario de búsqueda
Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == NULL) {
        return crearNodo(valor);
    }
    
    if (valor < raiz->dato) {
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    } else if (valor > raiz->dato) {
        raiz->derecho = insertar(raiz->derecho, valor);
    } else {
        cout << "\n¡El valor " << valor << " ya existe en el árbol! (No se permiten duplicados)\n" << endl;
    }
    
    return raiz;
}

// Función para recorrer el árbol en Preorden (Raíz - Izquierdo - Derecho)
void preorden(Nodo* raiz) {
    if (raiz != NULL) {
        cout << raiz->dato << " ";
        preorden(raiz->izquierdo);
        preorden(raiz->derecho);
    }
}

// Función para recorrer el árbol en Inorden (Izquierdo - Raíz - Derecho)
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierdo);
        cout << raiz->dato << " ";
        inorden(raiz->derecho);
    }
}

// Función para recorrer el árbol en Postorden (Izquierdo - Derecho - Raíz)
void postorden(Nodo* raiz) {
    if (raiz != NULL) {
        postorden(raiz->izquierdo);
        postorden(raiz->derecho);
        cout << raiz->dato << " ";
    }
}

// Función para calcular la altura del árbol
int calcularAltura(Nodo* raiz) {
    if (raiz == NULL) {
        return -1;
    }
    
    int alturaIzq = calcularAltura(raiz->izquierdo);
    int alturaDer = calcularAltura(raiz->derecho);
    
    return 1 + max(alturaIzq, alturaDer);
}

// Función para verificar si un nodo es hoja
bool esHoja(Nodo* nodo) {
    return (nodo->izquierdo == NULL && nodo->derecho == NULL);
}

// Función para mostrar los nodos hoja
void mostrarHojas(Nodo* raiz) {
    if (raiz != NULL) {
        if (esHoja(raiz)) {
            cout << raiz->dato << " ";
        }
        mostrarHojas(raiz->izquierdo);
        mostrarHojas(raiz->derecho);
    }
}

// Función para contar el total de nodos
int contarNodos(Nodo* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarNodos(raiz->izquierdo) + contarNodos(raiz->derecho);
}

// Función para contar nodos hoja
int contarHojas(Nodo* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    if (esHoja(raiz)) {
        return 1;
    }
    return contarHojas(raiz->izquierdo) + contarHojas(raiz->derecho);
}

// Función para liberar memoria del árbol
void liberarArbol(Nodo* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierdo);
        liberarArbol(raiz->derecho);
        delete raiz;
    }
}

// Estructura para almacenar la información de impresión del árbol
struct InfoImpresion {
    vector<string> lineas;
    int ancho;
    int altura;
    int posRaiz;
};

// Función para convertir entero a string
string intToString(int val) {
    stringstream ss;
    ss << val;
    return ss.str();
}

// Función recursiva para generar la representación visual del árbol (sstream)
InfoImpresion obtenerInfoImpresion(Nodo* raiz) {
    if (raiz == NULL) {
        return {vector<string>(), 0, 0, 0};
    }

    InfoImpresion infoIzq = obtenerInfoImpresion(raiz->izquierdo);
    InfoImpresion infoDer = obtenerInfoImpresion(raiz->derecho);

    string datoStr = intToString(raiz->dato);
    int anchoDato = datoStr.length();

    InfoImpresion infoActual;

    // Caso 1: Hoja
    if (infoIzq.altura == 0 && infoDer.altura == 0) {
        infoActual.lineas.push_back(datoStr);
        infoActual.ancho = anchoDato;
        infoActual.altura = 1;
        infoActual.posRaiz = anchoDato / 2;
        return infoActual;
    }

    // Caso 2: Solo hijo izquierdo
    if (infoDer.altura == 0) {
        infoActual.altura = infoIzq.altura + 2;
        infoActual.ancho = infoIzq.ancho + 2;
        infoActual.posRaiz = infoIzq.posRaiz + 2; 
        
        stringstream ssDato;
        ssDato << string(infoActual.posRaiz - anchoDato/2, ' ') << datoStr;
        ssDato << string(infoActual.ancho - ssDato.str().length(), ' ');
        infoActual.lineas.push_back(ssDato.str());

        stringstream ssConex;
        ssConex << string(infoActual.posRaiz - 1, ' ') << "/";
        ssConex << string(infoActual.ancho - ssConex.str().length(), ' ');
        infoActual.lineas.push_back(ssConex.str());

        for (const string& linea : infoIzq.lineas) {
            stringstream ssHijo;
            ssHijo << linea << "  ";
            infoActual.lineas.push_back(ssHijo.str());
        }
        return infoActual;
    }

    // Caso 3: Solo hijo derecho
    if (infoIzq.altura == 0) {
        infoActual.altura = infoDer.altura + 2;
        infoActual.ancho = infoDer.ancho + 2;
        
        infoActual.posRaiz = anchoDato / 2;
        
        stringstream ssDato;
        ssDato << datoStr << string(infoDer.ancho + 1, ' ');
        infoActual.lineas.push_back(ssDato.str());
        
        stringstream ssConex;
        ssConex << string(anchoDato, ' ') << "\\";
        ssConex << string(infoDer.ancho, ' ');
        infoActual.lineas.push_back(ssConex.str());
        
        for (const string& linea : infoDer.lineas) {
            stringstream ssHijo;
            ssHijo << string(anchoDato + 1, ' ') << linea;
            infoActual.lineas.push_back(ssHijo.str());
        }
        
        infoActual.ancho = anchoDato + 1 + infoDer.ancho;
        return infoActual;
    }

    // Caso 4: Ambos hijos
    int espacioEntreHijos = 2;
    
    infoActual.altura = max(infoIzq.altura, infoDer.altura) + 2;
    
    int totalAnchoHijos = infoIzq.ancho + espacioEntreHijos + infoDer.ancho;
    
    int posRaizIzqAbs = infoIzq.posRaiz;
    int posRaizDerAbs = infoIzq.ancho + espacioEntreHijos + infoDer.posRaiz;
    
    int posRaizDeseada = (posRaizIzqAbs + posRaizDerAbs) / 2;
    
    infoActual.ancho = max(totalAnchoHijos, posRaizDeseada + anchoDato/2 + 2);
    infoActual.posRaiz = posRaizDeseada;
    
    stringstream ssDato;
    int rellenoInicial = posRaizDeseada - anchoDato/2;
    if (rellenoInicial < 0) rellenoInicial = 0;
    
    ssDato << string(rellenoInicial, ' ') << datoStr;
    if (infoActual.ancho > ssDato.str().length()) {
        ssDato << string(infoActual.ancho - ssDato.str().length(), ' ');
    }
    infoActual.lineas.push_back(ssDato.str());
    
    stringstream ssConex;
    int posConexIzq = posRaizIzqAbs + 1; 
    if (posConexIzq >= posRaizDeseada) posConexIzq = posRaizDeseada - 1;
    
    int posConexDer = posRaizDerAbs - 1;
    if (posConexDer <= posRaizDeseada) posConexDer = posRaizDeseada + 1;
    
    for(int i=0; i<infoActual.ancho; i++) {
        if (i == posConexIzq) ssConex << "/";
        else if (i == posConexDer) ssConex << "\\";
        else ssConex << " ";
    }
    infoActual.lineas.push_back(ssConex.str());
    
    int maxLineas = max(infoIzq.lineas.size(), infoDer.lineas.size());
    for(int i=0; i<maxLineas; i++) {
        stringstream ssHijo;
        
        if (i < infoIzq.lineas.size()) {
            ssHijo << infoIzq.lineas[i];
            int faltante = infoIzq.ancho - infoIzq.lineas[i].length();
            if (faltante > 0) ssHijo << string(faltante, ' ');
        } else {
            ssHijo << string(infoIzq.ancho, ' ');
        }
        
        ssHijo << string(espacioEntreHijos, ' ');
        
        if (i < infoDer.lineas.size()) {
            ssHijo << infoDer.lineas[i];
        }
        
        if (ssHijo.str().length() < infoActual.ancho) {
            ssHijo << string(infoActual.ancho - ssHijo.str().length(), ' ');
        }
        
        infoActual.lineas.push_back(ssHijo.str());
    }
    
    return infoActual;
}

// Función para mostrar el árbol con formato visual mejorado
void visualizarArbol(Nodo* raiz) {
    if (raiz == NULL) {
        cout << "\n¡El árbol está vacío!\n" << endl;
        return;
    }
    
    cout << "\n========== VISUALIZACIÓN DEL ÁRBOL ==========\n" << endl;
    
    InfoImpresion info = obtenerInfoImpresion(raiz);
    
    for (const string& linea : info.lineas) {
        cout << linea << endl;
    }
    
    cout << "\n============================================\n" << endl;
}

// Función para validar entrada numérica
int leerNumeroEntero(const string& mensaje) {
    int numero;
    while (true) {
        cout << mensaje;
        if (cin >> numero) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        } else {
            cout << "\n¡Error! Debe ingresar un número entero válido.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Función para mostrar el menú
void mostrarMenu() {
    cout << "\n╔════════════════════════════════════════════╗" << endl;
    cout << "║         GESTIÓN DE ÁRBOL BINARIO           ║" << endl;
    cout << "╠════════════════════════════════════════════╣" << endl;
    cout << "║  1. Insertar valor                         ║" << endl;
    cout << "║  2. Contar nodos totales                   ║" << endl;
    cout << "║  3. Contar nodos hoja                      ║" << endl;
    cout << "║  4. Calcular altura/nivel del árbol        ║" << endl;
    cout << "║  5. Mostrar árbol                          ║" << endl;
    cout << "║  0. Salir                                  ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
}

// Función para mostrar los recorridos
void mostrarRecorridos(Nodo* raiz) {
    if (raiz == NULL) {
        cout << "\n¡El árbol está vacío!\n" << endl;
        return;
    }
    
    cout << "\n========== RECORRIDOS DEL ÁRBOL ==========" << endl;
    
    cout << "\nPreorden (Raíz-Izq-Der):  ";
    preorden(raiz);
    cout << endl;
    
    cout << "Inorden (Izq-Raíz-Der):   ";
    inorden(raiz);
    cout << endl;
    
    cout << "Postorden (Izq-Der-Raíz): ";
    postorden(raiz);
    cout << endl;
    
    cout << "\n==========================================\n" << endl;
}

// Función para mostrar estadísticas
void mostrarEstadisticas(Nodo* raiz) {
    if (raiz == NULL) {
        cout << "\n¡El árbol está vacío!\n" << endl;
        return;
    }
    
    cout << "\n========== ESTADÍSTICAS DEL ÁRBOL ==========" << endl;
    cout << "Altura del árbol:        " << calcularAltura(raiz) << endl;
    cout << "Total de nodos:          " << contarNodos(raiz) << endl;
    cout << "Total de nodos hoja:     " << contarHojas(raiz) << endl;
    cout << "Total de nodos internos: " << (contarNodos(raiz) - contarHojas(raiz)) << endl;
    cout << "============================================\n" << endl;
}

int main() {
    Nodo* raiz = NULL;
    int opcion, valor;
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║       SISTEMA DE ÁRBOL BINARIO DE BÚSQUEDA (ABB)          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;
    
    do {
        mostrarMenu();
        opcion = leerNumeroEntero("\nIngrese su opción: ");
        
        switch (opcion) {
            case 1:
                cout << "\n--- INSERTAR VALOR ---" << endl;
                valor = leerNumeroEntero("Ingrese el valor a insertar: ");
                raiz = insertar(raiz, valor);
                if (raiz != NULL) {
                    cout << "¡Valor insertado exitosamente!" << endl;
                }
                break;
                
            case 2:
                if (raiz == NULL) {
                    cout << "\n¡El árbol está vacío!\n" << endl;
                } else {
                    cout << "\n========== TOTAL DE NODOS ==========" << endl;
                    cout << "Total de nodos en el árbol: " << contarNodos(raiz) << endl;
                    cout << "====================================\n" << endl;
                }
                break;
                
            case 3:
                if (raiz == NULL) {
                    cout << "\n¡El árbol está vacío!\n" << endl;
                } else {
                    cout << "\n========== NODOS HOJA ==========" << endl;
                    cout << "Nodos hoja del árbol: ";
                    mostrarHojas(raiz);
                    cout << "\nTotal de hojas: " << contarHojas(raiz) << endl;
                    cout << "================================\n" << endl;
                }
                break;
                
            case 4:
                if (raiz == NULL) {
                    cout << "\n¡El árbol está vacío!\n" << endl;
                } else {
                    cout << "\n========== ALTURA DEL ÁRBOL ==========" << endl;
                    cout << "La altura/nivel del árbol es: " << calcularAltura(raiz) << endl;
                    cout << "======================================\n" << endl;
                }
                break;
                
            case 5:
                visualizarArbol(raiz);
                break;
                
            case 0:
                cout << "\n¡Gracias por usar el sistema!" << endl;
                cout << "Liberando memoria y cerrando programa...\n" << endl;
                liberarArbol(raiz);
                break;
                
            default:
                cout << "\n¡Opción inválida! Por favor seleccione una opción válida.\n" << endl;
                break;
        }
        
    } while (opcion != 0);
    
    return 0;
}
