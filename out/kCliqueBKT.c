#include <stdio.h>
#include <stdlib.h>

#define MAX 300

int N, K, M;
int graf_legaturi[MAX][MAX];
int muchii[MAX][2];
int grad[MAX];
int retine_nod[MAX]; 

int esteClica(int x)
{
    // Parcurgem toate posibilitatile
    for (int i = 1; i < x; i++) {
        for (int j = i + 1; j < x; j++)
            if (graf_legaturi[retine_nod[i]][retine_nod[j]] == 0)
                return 0;
    }
    return 1;
}

void cautaClica(int i, int l, int K , int N)
{
    for (int j = i + 1; j <= N - (K - l); j++)
        if (grad[j] >= K - 1) { 
            // Gradul nodului trebuie sa fie mai mare decat dimensiunea maxima a unei clici

            //Retinem nodul pentru prelucrare
            retine_nod[l] = j;

            // Verificam daca este clica
            // Daca da si se ajunge la l = k atunci am gasit clica si iesim din functie
            // Altfel reapelam functia pentru l = l + 1
            if (esteClica(l+1)) 
                if (l < K)
                    cautaClica(j, l + 1, K, N);
                else {
                    printf("True\n");
                    exit(0);
                }
        }
}

int main(int argc, char **argv) {

    // Citim fisierul dat ca parametru
    FILE *input = fopen(argv[1] , "r");

    // Verificam daca exista fisierul
    if(input == NULL) {
        printf("Nu s-a putut deschide fisierul");
        exit(1);
    }

    //Retinem valorile in k,N,M
    fscanf(input, "%d", &K);
    fscanf(input, "%d", &N);
    fscanf(input, "%d", &M);

    //Retinem muchiile intr-o matrice de legaturi
    //Retinem matricea de legatura si gradul fiecarui nod
    for(int i=0; i<M; i++) {
        fscanf(input, "%d", &muchii[i][0]);
        fscanf(input, "%d", &muchii[i][1]);

        graf_legaturi[muchii[i][0]][muchii[i][1]] = 1;
        graf_legaturi[muchii[i][1]][muchii[i][0]] = 1;

        // Incrementam gradul nodurilor
        grad[muchii[i][0]]++;
        grad[muchii[i][1]]++;
    }

    // Aplicam functia de cautare
    cautaClica(0, 1, K, N);
    printf("False\n");

    return 0;
}