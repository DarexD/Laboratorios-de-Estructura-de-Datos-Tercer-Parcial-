#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

//Validar cedula X Ya está listo 

using namespace std;

// Estructura para el nodo de la lista doblemente enlazada
struct Persona {
    int cedula;
    string nombre;
    Persona* anterior;
    Persona* siguiente;
};

// Punteros globales para manejar la lista
Persona* primero = NULL;
Persona* actual = NULL;
Persona* nuevo = NULL;

// Función para insertar un registro de manera descendente por cédula
void insertarDescendente(int cedula, string nombre) {
    // Verificar si la cédula ya existe
    actual = primero;
    while (actual != NULL) {
        if (actual->cedula == cedula) {
            cout << "\n¡Error! Ya existe un registro con la cédula " << cedula << ".\n" << endl;
            return;
        }
        actual = actual->siguiente;
    }
    
    // Crear nuevo nodo
    nuevo = new Persona;
    nuevo->cedula = cedula;
    nuevo->nombre = nombre;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    
    // Si la lista está vacía
    if (primero == NULL) {
        primero = nuevo;
        cout << "\n¡Registro insertado exitosamente!" << endl;
        return;
    }
    
    // Si el nuevo nodo debe ir al inicio (cédula mayor que la primera)
    if (cedula > primero->cedula) {
        nuevo->siguiente = primero;
        primero->anterior = nuevo;
        primero = nuevo;
        cout << "\n¡Registro insertado exitosamente!" << endl;
        return;
    }
    
    // Buscar la posición correcta
    actual = primero;
    while (actual->siguiente != NULL && actual->siguiente->cedula > cedula) {
        actual = actual->siguiente;
    }
    
    // Insertar el nodo en la posición encontrada
    nuevo->siguiente = actual->siguiente;
    nuevo->anterior = actual;
    
    if (actual->siguiente != NULL) {
        actual->siguiente->anterior = nuevo;
    }
    
    actual->siguiente = nuevo;
    cout << "\n¡Registro insertado exitosamente!" << endl;
}

// Función para mostrar la lista
void mostrarLista() {
    if (primero == NULL) {
        cout << "\nLa lista está vacía.\n" << endl;
        return;
    }
    
    cout << "\n========== LISTA DE PERSONAS (Descendente por Cédula) ==========" << endl;
    cout << setw(15) << "CÉDULA" << setw(30) << "NOMBRE" << endl;
    cout << "----------------------------------------------------------------" << endl;
    
    actual = primero;
    while (actual != NULL) {
        cout << setw(15) << actual->cedula << setw(30) << actual->nombre << endl;
        actual = actual->siguiente;
    }
    cout << "================================================================\n" << endl;
}

// Función para eliminar un registro por cédula
void eliminarRegistro(int cedula) {
    if (primero == NULL) {
        cout << "\nLa lista está vacía. No hay registros para eliminar.\n" << endl;
        return;
    }
    
    actual = primero;
    
    // Buscar el nodo con la cédula especificada
    while (actual != NULL && actual->cedula != cedula) {
        actual = actual->siguiente;
    }
    
    // Si no se encuentra el registro
    if (actual == NULL) {
        cout << "\n¡Registro con cédula " << cedula << " no encontrado!\n" << endl;
        return;
    }
    
    // Caso 1: El nodo a eliminar es el primero
    if (actual == primero) {
        primero = actual->siguiente;
        if (primero != NULL) {
            primero->anterior = NULL;
        }
    }
    // Caso 2: El nodo a eliminar está en el medio o al final
    else {
        actual->anterior->siguiente = actual->siguiente;
        if (actual->siguiente != NULL) {
            actual->siguiente->anterior = actual->anterior;
        }
    }
    
    delete actual;
    cout << "\n¡Registro con cédula " << cedula << " eliminado exitosamente!\n" << endl;
}

// Función para liberar toda la memoria de la lista
void liberarLista() {
    actual = primero;
    while (actual != NULL) {
        Persona* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    primero = NULL;
}

// Función para validar entrada numérica positiva
int leerNumeroEntero(const string& mensaje) {
    int numero;
    while (true) {
        cout << mensaje;
        if (cin >> numero) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (numero < 0) {
                cout << "\n¡Error! La cédula no puede ser un número negativo.\n" << endl;
            } else {
                return numero;
            }
        } else {
            cout << "\n¡Error! Debe ingresar un número entero válido.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Función para validar que el nombre no contenga números
string leerNombre(const string& mensaje) {
    string nombre;
    bool valido;
    while (true) {
        cout << mensaje;
        getline(cin, nombre);
        
        if (nombre.empty()) {
            cout << "\n¡Error! El nombre no puede estar vacío.\n" << endl;
            continue;
        }
        
        valido = true;
        for (char c : nombre) {
            if (isdigit(c)) {
                valido = false;
                break;
            }
        }
        
        if (valido) {
            return nombre;
        } else {
            cout << "\n¡Error! El nombre no debe contener números.\n" << endl;
        }
    }
}

// Función para mostrar el menú
void mostrarMenu() {
    cout << "\n╔════════════════════════════════════════════╗" << endl;
    cout << "║        GESTIÓN DE REGISTROS PERSONA        ║" << endl;
    cout << "╠════════════════════════════════════════════╣" << endl;
    cout << "║  1. Insertar nuevo registro                ║" << endl;
    cout << "║  2. Eliminar registro por cédula           ║" << endl;
    cout << "║  3. Mostrar lista completa                 ║" << endl;
    cout << "║ 99. Salir del programa                     ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
}

int main() {
    int opcion;
    int cedula;
    string nombre;
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  SISTEMA DE LISTA DOBLEMENTE ENLAZADA - REGISTROS PERSONA  ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;
    
    do {
        mostrarMenu();
        opcion = leerNumeroEntero("\nIngrese su opción: ");
        
        switch (opcion) {
            case 1:
                cout << "\n--- INSERTAR NUEVO REGISTRO ---" << endl;
                cedula = leerNumeroEntero("Ingrese número de cédula: ");
                nombre = leerNombre("Ingrese nombre completo: ");
                insertarDescendente(cedula, nombre);
                break;
                
            case 2:
                cout << "\n--- ELIMINAR REGISTRO ---" << endl;
                cedula = leerNumeroEntero("Ingrese la cédula del registro a eliminar: ");
                eliminarRegistro(cedula);
                break;
                
            case 3:
                mostrarLista();
                break;
                
            case 99:
                cout << "\n¡Gracias por usar el sistema!" << endl;
                cout << "Liberando memoria y cerrando programa...\n" << endl;
                liberarLista();
                break;
                
            default:
                cout << "\n¡Opción inválida! Por favor seleccione una opción válida.\n" << endl;
                break;
        }
        
    } while (opcion != 99);
    
    return 0;
}
