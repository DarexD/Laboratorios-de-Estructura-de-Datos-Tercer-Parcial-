#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <cctype>  // Para toupper() y isalpha()

using namespace std;

// Estructura del nodo del árbol binario (Template)
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* izquierdo;
    Nodo<T>* derecho;
};

// Función para crear un nuevo nodo
template <typename T>
Nodo<T>* crearNodo(T valor) {
    Nodo<T>* nuevo = new Nodo<T>;
    nuevo->dato = valor;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

//.

// Función para insertar un nodo en el árbol binario de búsqueda
template <typename T>
Nodo<T>* insertar(Nodo<T>* raiz, T valor, bool mostrarMensaje = true) {
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
template <typename T>
Nodo<T>* buscar(Nodo<T>* raiz, T valor) {
    if (raiz == NULL || raiz->dato == valor) {
        return raiz;
    }
    
    if (valor < raiz->dato) {
        return buscar(raiz->izquierdo, valor);
    }
    
    return buscar(raiz->derecho, valor);
}

// Función auxiliar para encontrar el nodo con el valor mínimo
template <typename T>
Nodo<T>* encontrarMinimo(Nodo<T>* nodo) {
    Nodo<T>* actual = nodo;
    while (actual && actual->izquierdo != NULL) {
        actual = actual->izquierdo;
    }
    return actual;
}

// Función auxiliar para encontrar el nodo con el valor máximo
template <typename T>
Nodo<T>* encontrarMaximo(Nodo<T>* nodo) {
    Nodo<T>* actual = nodo;
    while (actual && actual->derecho != NULL) {
        actual = actual->derecho;
    }
    return actual;
}

// Función para eliminar un nodo del árbol
template <typename T>
Nodo<T>* eliminar(Nodo<T>* raiz, T valor, int estrategia = 2) {
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
            Nodo<T>* temp = raiz->derecho;
            delete raiz;
            return temp;
        } else if (raiz->derecho == NULL) {
            Nodo<T>* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        }
        // Caso 3: Nodo con dos hijos
        else {
            if (estrategia == 1) {
                // Estrategia 1: Mayor de los Menores
                Nodo<T>* temp = encontrarMaximo(raiz->izquierdo);
                raiz->dato = temp->dato;
                raiz->izquierdo = eliminar(raiz->izquierdo, temp->dato, estrategia);
            } else {
                // Estrategia 2: Menor de los Mayores
                Nodo<T>* temp = encontrarMinimo(raiz->derecho);
                raiz->dato = temp->dato;
                raiz->derecho = eliminar(raiz->derecho, temp->dato, estrategia);
            }
        }
    }
    return raiz;
}

// --- LÓGICA AVL (TEMPLATE) ---

template <typename T>
int getAltura(Nodo<T>* n) {
    if (n == NULL) return 0;
    int alturaIzq = getAltura(n->izquierdo);
    int alturaDer = getAltura(n->derecho);
    return 1 + max(alturaIzq, alturaDer);
}

template <typename T>
int getBalance(Nodo<T>* n) {
    if (n == NULL) return 0;
    return getAltura(n->izquierdo) - getAltura(n->derecho);
}

template <typename T>
Nodo<T>* rotacionDerecha(Nodo<T>* y) {
    Nodo<T>* x = y->izquierdo;
    Nodo<T>* T2 = x->derecho;
    x->derecho = y;
    y->izquierdo = T2;
    return x;
}

template <typename T>
Nodo<T>* rotacionIzquierda(Nodo<T>* x) {
    Nodo<T>* y = x->derecho;
    Nodo<T>* T2 = y->izquierdo;
    y->izquierdo = x;
    x->derecho = T2;
    return y;
}

template <typename T>
Nodo<T>* balancearNodo(Nodo<T>* r, bool& rotacionAplicada) {
    int balance = getBalance(r);

    if (balance > 1 && getBalance(r->izquierdo) >= 0) {
        cout << "Desbalance en nodo " << r->dato << " (Factor: " << balance << "). Aplicando Caso 1 (LL): Rotación Derecha" << endl;
        rotacionAplicada = true;
        Nodo<T>* nuevaRaiz = rotacionDerecha(r);
        cout << "Subárbol resultante:" << endl;
        visualizarArbol(nuevaRaiz);
        cout << "(Presione ENTER para continuar...)" << endl;
        cin.get();
        return nuevaRaiz;
    }
    if (balance < -1 && getBalance(r->derecho) <= 0) {
        cout << "Desbalance en nodo " << r->dato << " (Factor: " << balance << "). Aplicando Caso 2 (RR): Rotación Izquierda" << endl;
        rotacionAplicada = true;
        Nodo<T>* nuevaRaiz = rotacionIzquierda(r);
        cout << "Subárbol resultante:" << endl;
        visualizarArbol(nuevaRaiz);
        cout << "(Presione ENTER para continuar...)" << endl;
        cin.get();
        return nuevaRaiz;
    }
    if (balance > 1 && getBalance(r->izquierdo) < 0) {
        cout << "Desbalance en nodo " << r->dato << " (Factor: " << balance << "). Aplicando Caso 3 (LR): Rotación Izq-Der" << endl;
        rotacionAplicada = true;
        r->izquierdo = rotacionIzquierda(r->izquierdo);
        Nodo<T>* nuevaRaiz = rotacionDerecha(r);
        cout << "Subárbol resultante:" << endl;
        visualizarArbol(nuevaRaiz);
        cout << "(Presione ENTER para continuar...)" << endl;
        cin.get();
        return nuevaRaiz;
    }
    if (balance < -1 && getBalance(r->derecho) > 0) {
        cout << "Desbalance en nodo " << r->dato << " (Factor: " << balance << "). Aplicando Caso 4 (RL): Rotación Der-Izq" << endl;
        rotacionAplicada = true;
        r->derecho = rotacionDerecha(r->derecho);
        Nodo<T>* nuevaRaiz = rotacionIzquierda(r);
        cout << "Subárbol resultante:" << endl;
        visualizarArbol(nuevaRaiz);
        cout << "(Presione ENTER para continuar...)" << endl;
        cin.get();
        return nuevaRaiz;
    }
    return r;
}

template <typename T>
Nodo<T>* convertirAAVL(Nodo<T>* raiz, bool& rotacionAplicada) {
    if (raiz == NULL) return NULL;
    raiz->izquierdo = convertirAAVL(raiz->izquierdo, rotacionAplicada);
    raiz->derecho = convertirAAVL(raiz->derecho, rotacionAplicada);
    return balancearNodo(raiz, rotacionAplicada);
}

// --- UTILIDADES GENÉRICAS ---

// Entrada de datos genérica
template <typename T>
T leerDato(const string& mensaje) {
    T dato;
    while (true) {
        cout << mensaje;
        if (cin >> dato) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return dato;
        } else {
            cout << "\n¡Error! Entrada inválida. Intente de nuevo.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Especialización para leer caracteres (valida longitud 1 y convierte a mayúscula)
template <>
char leerDato<char>(const string& mensaje) {
    string entrada;
    while (true) {
        cout << mensaje;
        getline(cin, entrada);
        
        // Si el usuario solo presionó Enter sin escribir nada, getline lee vacio. 
        // En cin >> normal esto se salta espacios. Aqui debemos manejarlo.
        if (entrada.empty()) {
            continue; 
        }

        if (entrada.length() == 1 && isalpha(entrada[0])) {
            return toupper(entrada[0]);
        } else {
            cout << "\n¡Error! Debe ingresar una única letra (A-Z).\n" << endl;
        }
    }
}

// Especialización simple para leerEntero (usado para opciones de menú)
int leerOpcion(const string& mensaje) {
    return leerDato<int>(mensaje);
}

// Generación aleatoria (Sobrecarga para int y char)
template <typename T>
T generarAleatorio();

template <>
int generarAleatorio<int>() {
    return rand() % 100 + 1; // 1 a 100
}

template <>
char generarAleatorio<char>() {
    return (char)(rand() % 26 + 65); // A a Z
}

template <typename T>
void insertarAleatorios(Nodo<T>*& raiz, int cantidad) {
    cout << "\nInsertando " << cantidad << " valores aleatorios: ";
    for (int i = 0; i < cantidad; ++i) {
        T valor = generarAleatorio<T>();
        cout << valor << " ";
        raiz = insertar(raiz, valor, false);
    }
    cout << "\n\nInserción aleatoria completada.\n";
}

// --- VISUALIZACIÓN ---

struct InfoImpresion {
    vector<string> lineas;
    int ancho;
    int altura;
    int posRaiz;
};

template <typename T>
string datoToString(T val) {
    stringstream ss;
    ss << val;
    return ss.str();
}

template <typename T>
int getBalance(Nodo<T>* n); // Forward declaration just in case, though it should be visible if defined above

template <typename T>
InfoImpresion obtenerInfoImpresion(Nodo<T>* raiz) {
    if (raiz == NULL) {
        return {vector<string>(), 0, 0, 0};
    }

    InfoImpresion infoIzq = obtenerInfoImpresion(raiz->izquierdo);
    InfoImpresion infoDer = obtenerInfoImpresion(raiz->derecho);

    string datoStr = datoToString(raiz->dato);
    
    // AGREGADO: Mostrar factor de equilibrio
    int balance = getBalance(raiz);
    stringstream ssBal;
    ssBal << "(" << balance << ")";
    datoStr += ssBal.str();

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

template <typename T>
void visualizarArbol(Nodo<T>* raiz) {
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

// --- MAIN ---

template <typename T>
void liberarArbol(Nodo<T>* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierdo);
        liberarArbol(raiz->derecho);
        delete raiz;
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

// Función template para ejecutar el menú con el tipo seleccionado
template <typename T>
void ejecutarMenu() {
    Nodo<T>* raiz = NULL;
    int opcion;
    T valor;
    int cantidad;

    do {
        mostrarMenu();
        opcion = leerOpcion("\nIngrese su opción: ");
        
        switch (opcion) {
            case 1:
                cout << "\n--- INSERTAR VALOR (MANUAL) ---" << endl;
                valor = leerDato<T>("Ingrese el valor a insertar: ");
                raiz = insertar(raiz, valor);
                cout << "¡Proceso de inserción finalizado!" << endl;
                break;
                
            case 2:
                cout << "\n--- INSERTAR VALORES ALEATORIOS ---" << endl;
                cantidad = leerOpcion("¿Cuántos valores desea generar?: ");
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
                    valor = leerDato<T>("Ingrese el valor a buscar: ");
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
                    valor = leerDato<T>("Ingrese el valor a eliminar: ");
                    Nodo<T>* nodoA = buscar(raiz, valor);
                    if (nodoA != NULL) {
                        int estrategia = 2; 
                        if (nodoA->izquierdo != NULL && nodoA->derecho != NULL) {
                            cout << "\nEl nodo tiene dos hijos. Seleccione estrategia de reemplazo:" << endl;
                            cout << "1. Mayor de los Menores (Predecesor)" << endl;
                            cout << "2. Menor de los Mayores (Sucesor)" << endl;
                            do {
                                estrategia = leerOpcion("Opción (1 o 2): ");
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
                cout << "\n========== EXAMEN: CONVERSIÓN A AVL ==========" << endl;
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
                    
                    bool algunaRotacion = false;
                    bool rotacionEnPasada;
                    int pasada = 1;

                    do {
                        rotacionEnPasada = false;
                        raiz = convertirAAVL(raiz, rotacionEnPasada);
                        
                        if (rotacionEnPasada) {
                            algunaRotacion = true;
                            // Opcional: Mostrar mensaje de fin de pasada si queremos ser muy detallados
                            // cout << "--- Fin de pasada " << pasada++ << ". Verificando nuevamente... ---" << endl;
                        }
                    } while (rotacionEnPasada);
                    
                    if (!algunaRotacion) {
                        cout << "(El árbol ya cumple con las propiedades AVL. No es necesario balancear)" << endl;
                    }
                    
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
}

int main() {
    srand(time(0)); // Inicializar semilla aleatoria
    
    int tipoDato;
    cout << "╔════════════════════════════════════════════╗" << endl;
    cout << "║     SELECCIÓN DE TIPO DE DATO DE ARBOL     ║" << endl;
    cout << "╠════════════════════════════════════════════╣" << endl;
    cout << "║  1. Trabajar con NÚMEROS (int)             ║" << endl;
    cout << "║  2. Trabajar con LETRAS (char)             ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
    
    do {
        tipoDato = leerOpcion("\nSeleccione una opción (1 o 2): ");
        if (tipoDato != 1 && tipoDato != 2) {
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (tipoDato != 1 && tipoDato != 2);
    
    if (tipoDato == 1) {
        cout << "\nInicializando sistema para NÚMEROS..." << endl;
        ejecutarMenu<int>();
    } else {
        cout << "\nInicializando sistema para LETRAS..." << endl;
        ejecutarMenu<char>();
    }
    
    return 0;
}
