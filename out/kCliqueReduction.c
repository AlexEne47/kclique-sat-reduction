#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 300

int N, K, M;
int graf_legaturi[MAX][MAX];
int muchii[MAX][2];
int grad[MAX];

int main(int argc, char **argv) {

    FILE *input = fopen(argv[1] , "r");

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
        
        grad[muchii[i][0]]++;
        grad[muchii[i][1]]++;
    }
    
    //Clauza 1
    for(int p=1; p<=K; p++) {
        if(p == 1)
        printf("(");
        else
        printf("^(");
        
        for(int i=1; i<=N; i++) {
        printf("x");
        printf("%d%d",i,p);

        if(i != N)
        printf("V");
        }

        printf(")");
    }

    //Clauza 2
    for(int i=1; i<=N; i++) {
        for(int s=2; s<=K; s++) {
            for(int p=1; p<s; p++) {
            printf("^(~x");
            printf("%d%d", i, p);
            printf("V~x");
            printf("%d%d", i ,s);
            printf(")");
            }
        }
    }

    //Clauza 3
    for(int i=1; i<N; i++) {
        for(int j=i+1; j<=N; j++) {
            if(graf_legaturi[i][j] == 0)
            for(int p=1; p<=K; p++) {
                for(int s=1; s<=K; s++) 
                if(p != s) {
                    printf("^(~x");
                    printf("%d%d",i,p);
                    printf("V");
                    printf("~x");
                    printf("%d%d",j,s);
                    printf(")");
                }
            }
        }
    }

    return 0;
}