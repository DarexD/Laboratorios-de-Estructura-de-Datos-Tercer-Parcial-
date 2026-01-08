// Calcular la suma de la diagonal principal de una matriz n x n (recursivo)

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <cctype>

using namespace std;

// Suma recursiva de la diagonal principal: m[0][0] + m[1][1] + ... + m[n-1][n-1]
// Firma: suma_diagonal(matriz, tamaño_n, índice_actual)
int suma_diagonal(int **m, int n, int i)
{
    // Caso base: cuando el índice alcanza n, no hay más elementos que sumar
    if (i == n)
        return 0;
    // Paso recursivo: sumar m[i][i] y avanzar al siguiente índice
    return m[i][i] + suma_diagonal(m, n, i + 1);
}


// Función que lee un entero validando que no se ingresen letras.
bool leerInt(const string &prompt, int &out)
{
    while (true)
    {
        cout << prompt;
        string line;

        // Leer la línea completa para poder detectar entradas compuestas como "-50-50-50+50-50-12"
        if (!std::getline(cin, line)) {
            // Si getline falla (EOF o error), intentar limpiar estado y pedir de nuevo
            cin.clear();
            cout << "Entrada inválida. Intente de nuevo." << '\n';
            continue;
        }

        // Trim simple: quitar espacios al inicio y final
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            cout << "Entrada inválida. Intente de nuevo." << '\n';
            continue;
        }
        size_t last = line.find_last_not_of(" \t\r\n");
        string token = line.substr(first, last - first + 1);

        // Validar formato: opcional signo + o - seguido únicamente de dígitos
        size_t idx = 0;
        if (token[0] == '+' || token[0] == '-') idx = 1;
        if (idx >= token.size()) {
            cout << "Entrada inválida. Intente de nuevo." << '\n';
            continue;
        }
        bool ok = true;
        for (; idx < token.size(); ++idx) {
            if (!isdigit(static_cast<unsigned char>(token[idx]))) { ok = false; break; }
        }
        if (!ok) {
            cout << "Entrada inválida. Intente de nuevo." << '\n';
            continue;
        }

        // Convertir a entero comprobando rango
        try {
            long long v = stoll(token);
            if (v < numeric_limits<int>::min() || v > numeric_limits<int>::max()) {
                cout << "Número fuera de rango. Intente de nuevo." << '\n';
                continue;
            }
            out = static_cast<int>(v);
            return true;
        } catch (...) {
            cout << "Entrada inválida. Intente de nuevo." << '\n';
            continue;
        }
    }
}

int main()
{
    while (true)
    {
        int n;

        // Leer tamaño n con validación (n > 0)
        while (true)
        {
            leerInt("Ingrese el tamaño de la matriz (n): ", n);
            if (n <= 0)
            {
                cout << "El tamaño debe ser un entero positivo." << '\n';
                continue;
            }
            break;
        }

        // Crear matriz tradicional (array de punteros a filas)
        int **matriz = new int *[n];
        for (int i = 0; i < n; ++i)
            matriz[i] = new int[n];

        vector<int> valores_diag;
        valores_diag.reserve(n);

        // Leer elementos de la matriz (sin imprimir la matriz como estructura)
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int val;
                string prompt = string("Elemento [") + to_string(i + 1) + "][" + to_string(j + 1) + "]: ";
                leerInt(prompt, val);
                matriz[i][j] = val;
                if (i == j)
                    valores_diag.push_back(val);
            }
        }

        int resultado = suma_diagonal(matriz, n, 0);

        // Mostrar solo el resultado (requisito principal)
        cout << "El resultado de la diagonal es: " << resultado << '\n';

        // Opción: mostrar los valores que se sumaron (no la matriz completa)
        cout << "¿Desea ver los valores sumados? (Sí/No): ";
        string verVals;
        cin >> verVals;
        for (char &ch : verVals)
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        if (verVals == "si" || verVals == "s" || verVals == "sí")
        {
            cout << "Valores sumados: ";
            for (size_t k = 0; k < valores_diag.size(); ++k)
            {
                if (k)
                    cout << " + ";
                cout << valores_diag[k];
            }
            cout << '\n';
        }

        // Preguntar si desea repetir
        cout << "¿Desea repetir el programa? (Sí/No): ";
        string resp;
        cin >> resp;
        for (char &ch : resp)
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        // Liberar memoria de la matriz tradicional
        for (int i = 0; i < n; ++i)
            delete[] matriz[i];
        delete[] matriz;

        if (resp == "si" || resp == "s" || resp == "sí")
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else
        {
            break;
        }
    }

    return 0;
}
