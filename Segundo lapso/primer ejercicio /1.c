#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int R, C;

    printf("Ingrese numero de distritos (filas): ");
    if (scanf("%d", &R) != 1 || R <= 0)
    {
        fprintf(stderr, "Entrada invalida para distritos.\n");
        return 1;
    }

    printf("Ingrese numero de candidatos (columnas): ");
    if (scanf("%d", &C) != 1 || C <= 0)
    {
        fprintf(stderr, "Entrada invalida para candidatos.\n");
        return 1;
    }
    // matriz en la pila (stack). Para matrices muy grandes
    long long mat[R + 1][C + 1];
    // Inicializamos a cero
    for (int ii = 0; ii <= R; ++ii)
        for (int jj = 0; jj <= C; ++jj)
            mat[ii][jj] = 0;

    // Captura y acumulación de totales en la misma matriz
    printf("\nIngrese los votos por cada par (Distrito i, Candidato j).\n");
    for (int i = 0; i < R; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            long long v;
            // Mensaje claro de a quién pertenecen los votos que se ingresan
            if (C == 3)
            {
                char nombre = (char)('A' + j);
                printf("Ingrese votos para Distrito %d, Candidato %c: ", i + 1, nombre);
            }
            else
            {
                printf("Ingrese votos para Distrito %d, Candidato %d: ", i + 1, j + 1);
            }
            fflush(stdout);
            if (scanf("%lld", &v) != 1)
            {
                fprintf(stderr, "Entrada invalida en fila %d, columna %d.\n", i + 1, j + 1);
                return 1;
            }
            mat[i][j] = v;  // valor original
            mat[i][C] += v; // total por distrito (ultima columna)
            mat[R][j] += v; // total por candidato (ultima fila)
            mat[R][C] += v; // total general (esquina)
        }
    }

    // Determinar ganador (candidato con mayor total en la ultima fila)
    int idxGanador = 0; // indice de candidato ganador (0..C-1)
    long long maxVotos = (C > 0) ? mat[R][0] : 0;
    for (int j = 1; j < C; ++j)
    {
        if (mat[R][j] > maxVotos)
        {
            maxVotos = mat[R][j];
            idxGanador = j;
        }
    }

    // Impresion de resultados
    printf("\nTotal de votos por candidato:\n");
    for (int j = 0; j < C; ++j)
    {
        // Si C es 3, usamos etiquetas A/B/C; si no, numerico
        if (C == 3)
        {
            char nombre = (char)('A' + j);
            printf("Candidato %c: %lld\n", nombre, mat[R][j]);
        }
        else
        {
            printf("Candidato %d: %lld\n", j + 1, mat[R][j]);
        }
    }

    printf("\nTotal de votos por distrito:\n");
    for (int i = 0; i < R; ++i)
    {
        printf("Distrito %d: %lld\n", i + 1, mat[i][C]);
    }

    printf("\nTotal general de votos: %lld\n", mat[R][C]);

    // Si la matriz es pequena, mostrar la tabla completa con totales
    if (R <= 10 && C <= 10)
    {
        printf("\nTabla completa de votos (incluye totales en ultima fila/columna):\n");
        // Encabezados
        const int W = 16; // ancho de columna para cabeceras y valores
        printf("%*s", W, "Distrito");
        if (C == 3)
        {
            printf("%*s%*s%*s", W, "Candidato A", W, "Candidato B", W, "Candidato C");
        }
        else
        {
            for (int j = 0; j < C; ++j)
            {
                char nombre[40];
                snprintf(nombre, sizeof(nombre), "Votos Candidato %d", j + 1);
                printf("%*s", W, nombre);
            }
        }
        printf("%*s\n", W, "Total Distrito");

        for (int i = 0; i <= R; ++i)
        {
            if (i < R)
                printf("%*d", W, i + 1);
            else
                printf("%*s", W, "Total por Candidato");
            for (int j = 0; j <= C; ++j)
            {
                printf("%*lld", W, mat[i][j]);
            }
            printf("\n");
        }
    }

    // Anunciar ganador
    if (C == 3)
    {
        char nombre = (char)('A' + idxGanador);
        printf("\nGanador: Candidato %c con %lld votos.\n", nombre, maxVotos);
    }
    else
    {
        printf("\nGanador: Candidato %d con %lld votos.\n", idxGanador + 1, maxVotos);
    }

    // Con VLA no hay que liberar; si se usara calloc (heap), habría que free(mat).
    return 0;
}