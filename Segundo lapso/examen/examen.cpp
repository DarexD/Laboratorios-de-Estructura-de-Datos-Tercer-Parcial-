#include <iostream>
#include <limits>

using namespace std;

// Invierte los elementos del arreglo arr entre las posiciones 'inicio' y 'fin' (inclusive)
// Recursivo: intercambia arr[inicio] y arr[fin] y llama a sí mismo con inicio+1, fin-1.
void invertir(int arr[], int inicio, int fin)
{
    if (inicio >= fin)
        return; // caso base: se cruzaron o igualados
    invertir(arr, inicio + 1, fin - 1);
    int temp = arr[inicio];
    arr[inicio] = arr[fin];
    arr[fin] = temp;
   
}

int main()
{
    const int MAX_N = 1000000; // límite pedido
    int N;
    std::string intento;

    do
    {
        cout << "Ingrese el tamaño del arreglo N ): ";
        if (!(cin >> N))
        {
            cout << "Entrada inválida. N debe ser un entero.\n";
            // limpiar estado y descartar la línea
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            // preguntar al final si desea reintentar
        }
        else if (N <= 0 || N > MAX_N)
        {
            cout << "N debe estar entre 1 y " << MAX_N << ".\n";
        }
        else
        {
            // Arreglo tradicional (reserva dinámica)
            int *arr = new int[N];

            // Lectura de N enteros (validando cada entrada)
            for (int i = 0; i < N; ++i)
            {
                while (true)
                {
                    cout << "Elemento [" << i << "]: ";
                    if (cin >> arr[i])
                        break;
                    cout << "Entrada inválida. Ingrese un entero para el elemento " << i << ".\n";
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            // Mostrar arreglo original
            cout << "Arreglo original: ";
            for (int i = 0; i < N; ++i)
                cout << arr[i] << (i + 1 < N ? " " : "");
            cout << "\n";

            // Llamada a la función recursiva para invertir
            invertir(arr, 0, N - 1);

            // Mostrar arreglo invertido
            cout << "Arreglo invertido: ";
            for (int i = 0; i < N; ++i)
                cout << arr[i] << (i + 1 < N ? " " : "");
            cout << "\n";

            delete[] arr; // liberar memoria
        }

        // Preguntar si desea volver a intentar
        cout << "\n¿Desea intentarlo de nuevo? (s/n): ";
        cin >> intento;
        // normalizar respuesta: tomar primera letra si existe
    } while (!intento.empty() && (intento[0] == 's' || intento[0] == 'S'));

    return 0;
}
