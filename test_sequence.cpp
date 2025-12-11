#include "examen.cpp"

void probarSecuencia() {
    Nodo<int>* raiz = NULL;
    int valores[] = {163, 106, 30, 24, 25, 17, 3, 20, 70, 42, 22, 40, 10, 12, 46};
    int n = sizeof(valores) / sizeof(valores[0]);

    cout << "--- SIMULACIÓN DE SECUENCIA ---" << endl;
    for (int i = 0; i < n; i++) {
        raiz = insertar(raiz, valores[i], false);
    }
    
    cout << "Balanceando..." << endl;
    bool rotacion = false;
    raiz = convertirAAVL(raiz, rotacion);
    
    cout << "\n--- ÁRBOL FINAL ---" << endl;
    visualizarArbol(raiz);
}

int main() {
    probarSecuencia();
    return 0;
}
