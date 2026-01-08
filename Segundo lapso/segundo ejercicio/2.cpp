// Calcular capital final con interés compuesto: M = m * (1 + x/100)^n
// Requisitos: validar entradas, no permitir letras, usar recursividad y una sola operación para la fórmula.

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cctype>

using namespace std;

// Potencia recursiva por exponenciación por cuadrados (n >= 0)
// Firma: potencia(base, n)
double potencia(double base, int n)
{
    if (n == 0)
        return 1.0;
    if (n % 2 == 0)
    {
        double half = potencia(base, n / 2);
        return half * half;
    }
    else
    {
        return base * potencia(base, n - 1);
    }
}


// Helpers de entrada robusta
// (validan y repreguntan si el usuario escribe letras)
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
    cout << fixed << setprecision(2);

    while (true)
    {
        double monto;   // capital inicial (M)
        double interes; // tasa en % (x)
        int tiempo;     // número de periodos (n)

        // Captura con validación de reglas de negocio
        while (true)
        {
            leerDouble("Ingrese el capital inicial (Monto): ", monto);
            leerDouble("Ingrese la tasa de interés (x%) como porcentaje: ", interes);
            leerInt("Ingrese el número de periodos (Tiempo): ", tiempo);

            if (monto <= 0.0)
            {
                cout << "El Monto debe ser mayor que 0." << '\n';
                continue;
            }
            if (interes <= 0.0)
            {
                cout << "El Interés debe ser mayor que 0." << '\n';
                continue;
            }
            if (tiempo < 0)
            {
                cout << "El Tiempo no puede ser negativo." << '\n';
                continue; // no permitir continuar; se vuelve a pedir
            }
            // Si tiempo == 0, la fórmula devolverá monto (porque potencia(...,0)=1)
            break;
        }

        // Cálculo en UNA única expresión de la fórmula compuesta:
        // M = monto * (1 + interes/100)^tiempo
        double resultado = monto * potencia(1.0 + interes / 100.0, tiempo);

        cout << "El capital final es: " << resultado << '\n';

        // Preguntar si desea repetir
        cout << "¿Desea repetir el programa? (Sí/No): ";
        string resp;
        cin >> resp;
        for (char &ch : resp)
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
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
