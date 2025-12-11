#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

using namespace std;

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
Nodo* insertar(Nodo* raiz, int valor, bool mostrarMensaje = true) {
    if (raiz == NULL) {
        return crearNodo(valor);
    }
    
    if (valor < raiz->dato) {
        raiz->izquierdo = insertar(raiz->izquierdo, valor, mostrarMensaje);
    } else if (valor > raiz->dato) {
        raiz->derecho = insertar(raiz->derecho, valor, mostrarMensaje);
    } else {
        if (mostrarMensaje) {
            cout << "\n¡El valor " << valor << " ya existe en el árbol! (No se permiten duplicados)\n" << endl;
        }
    }
    
    return raiz;
}

// Función para buscar un valor en el árbol
Nodo* buscar(Nodo* raiz, int valor) {
    if (raiz == NULL || raiz->dato == valor) {
        return raiz;
    }
    
    if (valor < raiz->dato) {
        return buscar(raiz->izquierdo, valor);
    }
    
    return buscar(raiz->derecho, valor);
}

// Función auxiliar para encontrar el nodo con el valor mínimo (para eliminación)
Nodo* encontrarMinimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual && actual->izquierdo != NULL) {
        actual = actual->izquierdo;
    }
    return actual;
}

// Función para eliminar un nodo del árbol
// Función auxiliar para encontrar el nodo con el valor máximo (para eliminación por predecesor)
Nodo* encontrarMaximo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual && actual->derecho != NULL) {
        actual = actual->derecho;
    }
    return actual;
}

// Función para eliminar un nodo del árbol
// estrategia: 1 = Mayor de los Menores (Predecesor), 2 = Menor de los Mayores (Sucesor)
Nodo* eliminar(Nodo* raiz, int valor, int estrategia = 2) {
    if (raiz == NULL) {
        cout << "\nEl valor " << valor << " no se encuentra en el árbol.\n";
        return raiz;
    }

    if (valor < raiz->dato) {
        raiz->izquierdo = eliminar(raiz->izquierdo, valor, estrategia);
    } else if (valor > raiz->dato) {
        raiz->derecho = eliminar(raiz->derecho, valor, estrategia);
    } else {
        // Caso 1: Nodo sin hijos (hoja)
        if (raiz->izquierdo == NULL && raiz->derecho == NULL) {
            delete raiz;
            return NULL;
        }
        // Caso 2: Nodo con un solo hijo
        else if (raiz->izquierdo == NULL) {
            Nodo* temp = raiz->derecho;
            delete raiz;
            return temp;
        } else if (raiz->derecho == NULL) {
            Nodo* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        }
        // Caso 3: Nodo con dos hijos
        else {
            if (estrategia == 1) {
                // Estrategia 1: Mayor de los Menores (Predecesor Inorden del subárbol izquierdo)
                Nodo* temp = encontrarMaximo(raiz->izquierdo);
                raiz->dato = temp->dato;
                raiz->izquierdo = eliminar(raiz->izquierdo, temp->dato, estrategia);
            } else {
                // Estrategia 2: Menor de los Mayores (Sucesor Inorden del subárbol derecho)
                Nodo* temp = encontrarMinimo(raiz->derecho);
                raiz->dato = temp->dato;
                raiz->derecho = eliminar(raiz->derecho, temp->dato, estrategia);
            }
        }
    }
    return raiz;
}

// Función para insertar valores aleatorios
void insertarAleatorios(Nodo*& raiz, int cantidad) {
    cout << "\nInsertando " << cantidad << " valores aleatorios: ";
    for (int i = 0; i < cantidad; ++i) {
        int valor = rand() % 100 + 1; // Valores entre 1 y 100
        cout << valor << " ";
        raiz = insertar(raiz, valor, false); // false para no mostrar mensaje de duplicados repetidamente
    }
    cout << "\n\nInserción aleatoria completada.\n";
}

// --- LÓGICA AVL (BALANCEO) ---

// Función para obtener la altura de un nodo
int getAltura(Nodo* n) {
    if (n == NULL) return 0;
    int alturaIzq = getAltura(n->izquierdo);
    int alturaDer = getAltura(n->derecho);
    return 1 + max(alturaIzq, alturaDer);
}

// Función para obtener el factor de equilibrio
int getBalance(Nodo* n) {
    if (n == NULL) return 0;
    return getAltura(n->izquierdo) - getAltura(n->derecho);
}

// CASO 1 (LL) y CASO 2 (RR): Rotaciones Simples

// Rotación a la Derecha (para Caso 1: Izquierda-Izquierda)
Nodo* rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    // Rotación
    x->derecho = y;
    y->izquierdo = T2;

    // Retorna nueva raíz
    return x;
}

// Rotación a la Izquierda (para Caso 2: Derecha-Derecha)
Nodo* rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    // Rotación
    y->izquierdo = x;
    x->derecho = T2;

    // Retorna nueva raíz
    return y;
}

// Función para balancear un nodo individual aplicando los 4 casos
Nodo* balancearNodo(Nodo* r) {
    int balance = getBalance(r);

    // Caso 1: Izquierda-Izquierda (LL) -> Rotación Derecha
    if (balance > 1 && getBalance(r->izquierdo) >= 0) {
        cout << "Aplicando Caso 1 (LL): Rotación Derecha en nodo " << r->dato << endl;
        return rotacionDerecha(r);
    }

    // Caso 2: Derecha-Derecha (RR) -> Rotación Izquierda
    if (balance < -1 && getBalance(r->derecho) <= 0) {
        cout << "Aplicando Caso 2 (RR): Rotación Izquierda en nodo " << r->dato << endl;
        return rotacionIzquierda(r);
    }

    // Caso 3: Izquierda-Derecha (LR) -> Rotación Izquierda en hijo + Rotación Derecha
    if (balance > 1 && getBalance(r->izquierdo) < 0) {
        cout << "Aplicando Caso 3 (LR): Rotación Izq-Der en nodo " << r->dato << endl;
        r->izquierdo = rotacionIzquierda(r->izquierdo);
        return rotacionDerecha(r);
    }

    // Caso 4: Derecha-Izquierda (RL) -> Rotación Derecha en hijo + Rotación Izquierda
    if (balance < -1 && getBalance(r->derecho) > 0) {
        cout << "Aplicando Caso 4 (RL): Rotación Der-Izq en nodo " << r->dato << endl;
        r->derecho = rotacionDerecha(r->derecho);
        return rotacionIzquierda(r);
    }

    return r; // No requiere balanceo
}

// Función recursiva para convertir todo el árbol en AVL (Post-orden)
Nodo* convertirAAVL(Nodo* raiz) {
    if (raiz == NULL) return NULL;

    // Primero balanceamos los subárboles (de abajo hacia arriba)
    raiz->izquierdo = convertirAAVL(raiz->izquierdo);
    raiz->derecho = convertirAAVL(raiz->derecho);

    // Luego balanceamos el nodo actual con la nueva altura de sus hijos
    return balancearNodo(raiz);
}

// --- LÓGICA DE VISUALIZACIÓN (RECICLADA DE 2.cpp) ---

struct InfoImpresion {
    vector<string> lineas;
    int ancho;
    int altura;
    int posRaiz;
};

string intToString(int val) {
    stringstream ss;
    ss << val;
    return ss.str();
}

InfoImpresion obtenerInfoImpresion(Nodo* raiz) {
    if (raiz == NULL) {
        return {vector<string>(), 0, 0, 0};
    }

    InfoImpresion infoIzq = obtenerInfoImpresion(raiz->izquierdo);
    InfoImpresion infoDer = obtenerInfoImpresion(raiz->derecho);

    string datoStr = intToString(raiz->dato);
    int anchoDato = datoStr.length();

    InfoImpresion infoActual;

    if (infoIzq.altura == 0 && infoDer.altura == 0) {
        infoActual.lineas.push_back(datoStr);
        infoActual.ancho = anchoDato;
        infoActual.altura = 1;
        infoActual.posRaiz = anchoDato / 2;
        return infoActual;
    }

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

// --- FIN LÓGICA DE VISUALIZACIÓN ---

void liberarArbol(Nodo* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierdo);
        liberarArbol(raiz->derecho);
        delete raiz;
    }
}

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

void mostrarMenu() {
    cout << "\n╔════════════════════════════════════════════╗" << endl;
    cout << "║         GESTIÓN DE ÁRBOL BINARIO (ABB)     ║" << endl;
    cout << "╠════════════════════════════════════════════╣" << endl;
    cout << "║  1. Insertar valor (Manual)                ║" << endl;
    cout << "║  2. Insertar valores aleatorios            ║" << endl;
    cout << "║  3. Buscar valor                           ║" << endl;
    cout << "║  4. Eliminar valor                         ║" << endl;
    cout << "║  5. Mostrar árbol                          ║" << endl;
    cout << "║  6. Balancear Árbol (Convertir a AVL)      ║" << endl;
    cout << "║  0. Salir                                  ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
}

int main() {
    srand(time(0)); // Inicializar semilla aleatoria
    Nodo* raiz = NULL;
    int opcion, valor, cantidad;
    

    
    do {
        mostrarMenu();
        opcion = leerNumeroEntero("\nIngrese su opción: ");
        
        switch (opcion) {
            case 1:
                cout << "\n--- INSERTAR VALOR (MANUAL) ---" << endl;
                valor = leerNumeroEntero("Ingrese el valor a insertar: ");
                raiz = insertar(raiz, valor);
                cout << "¡Proceso de inserción finalizado!" << endl;
                break;
                
            case 2:
                cout << "\n--- INSERTAR VALORES ALEATORIOS ---" << endl;
                cantidad = leerNumeroEntero("¿Cuántos valores desea generar?: ");
                if (cantidad > 0) {
                    insertarAleatorios(raiz, cantidad);
                } else {
                    cout << "La cantidad debe ser mayor a 0." << endl;
                }
                break;
                
            case 3:
                cout << "\n--- BUSCAR VALOR ---" << endl;
                if (raiz == NULL) {
                    cout << "¡El árbol está vacío!" << endl;
                } else {
                    valor = leerNumeroEntero("Ingrese el valor a buscar: ");
                    if (buscar(raiz, valor) != NULL) {
                        cout << "\n¡El valor " << valor << " SÍ se encuentra en el árbol!" << endl;
                    } else {
                        cout << "\nEl valor " << valor << " NO se encuentra en el árbol." << endl;
                    }
                }
                break;
                
            case 4:
                cout << "\n--- ELIMINAR VALOR ---" << endl;
                if (raiz == NULL) {
                    cout << "¡El árbol está vacío!" << endl;
                } else {
                    valor = leerNumeroEntero("Ingrese el valor a eliminar: ");
                    Nodo* nodoA = buscar(raiz, valor);
                    if (nodoA != NULL) {
                        int estrategia = 2; // Por defecto: Menor de los Mayores
                        // Solo preguntamos si el nodo tiene dos hijos, ya que es el único caso donde importa
                        if (nodoA->izquierdo != NULL && nodoA->derecho != NULL) {
                            cout << "\nEl nodo tiene dos hijos. Seleccione estrategia de reemplazo:" << endl;
                            cout << "1. Mayor de los Menores (Predecesor)" << endl;
                            cout << "2. Menor de los Mayores (Sucesor)" << endl;
                            do {
                                estrategia = leerNumeroEntero("Opción (1 o 2): ");
                                if (estrategia != 1 && estrategia != 2) {
                                  cout << "Opción inválida. Intente de nuevo." << endl;
                                }
                            } while (estrategia != 1 && estrategia != 2);
                        }
                        
                        raiz = eliminar(raiz, valor, estrategia);
                        cout << "\n¡Valor eliminado exitosamente!" << endl;
                    } else {
                         cout << "\nEl valor " << valor << " NO existe en el árbol, no se puede eliminar." << endl;
                    }
                }
                break;
                
            case 5:
                visualizarArbol(raiz);
                break;
                
            case 6:
                if (raiz == NULL) {
                    cout << "¡El árbol está vacío!" << endl;
                } else {
                    // 1. Mostrar Árbol Inicial
                    cout << "\n1. ESTADO INICIAL DEL ÁRBOL (DESBALANCEADO):" << endl;
                    visualizarArbol(raiz);
                    cout << "\n------------------------------------------------" << endl;
                    cout << "Presione ENTER para comenzar el balanceo..." << endl;
                    cin.get(); cin.get(); 

                    // 2. Mostrar Pasos (Casos Aplicados)
                    cout << "\n2. PROCEDIMIENTO DE BALANCEO (CASOS DETECTADOS):" << endl;
                    raiz = convertirAAVL(raiz);
                    cout << "\n------------------------------------------------" << endl;
                    cout << "¡Proceso de balanceo completado!" << endl;
                    cout << "Presione ENTER para ver el resultado final..." << endl;
                    cin.get(); // Pausa para visualizar los pasos

                    // 3. Mostrar Árbol Final
                    cout << "\n3. ÁRBOL RESULTANTE (AVL BALANCEADO):" << endl;
                    visualizarArbol(raiz);
                }
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
