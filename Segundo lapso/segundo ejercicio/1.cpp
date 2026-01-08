// Calcule la potencia a^b usando recursividad (C++) con soporte de exponentes negativos

#include <iostream>
#include <limits>
#include <string>
#include <cctype>

using namespace std;

// Potencia recursiva con exponentes negativos usando exponenciación por cuadrados
// Firma: calcular_potencia(base, exponente)
double calcular_potencia(double base, int exponente)
{
    if (exponente == 0)
        return 1.0;
    if (exponente < 0)
        return 1.0 / calcular_potencia(base, -exponente);

    // Exponente positivo
    if (exponente % 2 == 0)
    {
        double half = calcular_potencia(base, exponente / 2);
        return half * half;
    }
    else
    {
        return base * calcular_potencia(base, exponente - 1);
    }
}



bool leerDouble(const string &prompt, double &out)
{
    while (true)
    {
        cout << prompt;
        if (cin >> out)
            return true;
        cout << "Entrada inválida. Intente de nuevo." << '\n';
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool leerInt(const string &prompt, int &out)
{
    while (true)
    {
        cout << prompt;
        if (cin >> out)
            return true;
        cout << "Entrada inválida. Intente de nuevo." << '\n';
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main()
{
    while (true)
    {
        // Leer datos válidos
        double a;
        int b;

        // Limpiar cualquier resto en el buffer antes de pedir
        cin.clear();
        // No hacemos ignore aquí para no saltarnos entradas válidas al comienzo

        // Bucle de captura que también valida 0^negativo
        while (true)
        {
            leerDouble("Ingrese la base: ", a);
            leerInt("Ingrese el exponente: ", b);

            if (a == 0.0 && b < 0)
            {
                cout << "0 elevado a un exponente negativo es indefinido. Intente de nuevo." << '\n';
                continue; // volver a pedir base y exponente
            }
            break;
        }

        double resultado = calcular_potencia(a, b);
        cout << "El resultado es: " << resultado << '\n';

        // Preguntar si desea repetir
        cout << "¿Desea repetir el programa? (Sí/No): ";
        string resp;
        cin >> resp;
        // normalizar respuesta a minúsculas y sin tildes simples (aceptamos 'si' o 's')
        for (char &ch : resp)
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));

        if (resp == "si" || resp == "s" || resp == "sí")
        {
            // limpiar fin de línea pendiente
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