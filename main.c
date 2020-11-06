#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
typedef char *matrice;
typedef int *matrices;
int main() {
    int size=1;
    int n=5;
//calcul le nombre de case pour stocker chaque configuration de spin d'une molecule de taille n*n
    for (int i = 0; i < n*n; ++i) {
        size=size*2;
    }
//declaration d'un tableau de matrice de taille size et qui contient dans chaque case une matrice de taille n*n
    matrice *m;

    m=(matrice* )malloc(sizeof(matrice* )*size);
    for (int i = 0; i <size ; ++i) {
        m[i]=(matrice)malloc(sizeof(char)*n*n);
    }
//fin declaration
//initatialisation premeire config
    for (int i = 0; i <n ; ++i) {
        for (int j = 0; j <n ; ++j) {
            m[0][n*i+j]=0;
        }
    }
    int p=1;
    int indice=1;

    int puissance=2;
//on va faire pour chaque case toutes les combinaison possible en commancant par la dernier on aura 2 combi la suivante c'est 4 puis 8.....
    for (int i = 0; i <n ; ++i) {
        for (int j = 0; j <n ; ++j) {
            //c'est la qu'on fait les combinaison
            int indicef=indice;
            for (int k = 0; k < indicef; ++k) {

                for (int w = 0; w <n ; ++w) {
                    for (int z = 0; z <n ; ++z) {
                        m[indice][w*n+z]=m[k][w*n+z];

                    }
                }

                m[indice][i*n+j]=1;
                indice++;
            }

        }
    }
    //declaration de la matrice sc qui va stocker la densité d(m,s) comme suite d(m,s)=sc[m][s]
    matrices *sc;
    sc=(matrices* )malloc(sizeof(matrices* )*(((n*n)+1)*2));
    for (int i = 0; i <((n*n)+1)*2 ; ++i) {
        sc[i]=(matrices)malloc(sizeof(int )*(((n-1)*(n+n)+1)*2));
    }
    for (int i = 0; i < ((n*n)+1)*2; ++i) {
        for (int j = 0; j <((n-1)*(n+n)+1)*2 ; ++j) {
            sc[i][j]=0;
        }
    }


    int s,s1;
    int temp;
    if(n%2==1) {
        //debut de calcul de m,s
        for (int i = 0; i < size; ++i) {

            s = 0;
            s1 = 0;
            //calcul de s
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    s = s + m[i][j * n + k];


                }
            }
            //calcul de m
            //on va d'abord calculer les voisin de gauche et droite
            for (int k = 0; k < n; ++k) {
                for (int j = 1; j < n; j += 2) {
                    s1 = s1 + (-1 + (2 * m[i][k * n + j])) * (m[i][k * n + j - 1] - (1 - m[i][k * n + j - 1]));
                    s1 = s1 + (-1 + (2 * m[i][k * n + j])) * (m[i][k * n + j + 1] - (1 - m[i][k * n + j + 1]));

                }
            }
            //puis calculer les voisin de haut et bas
            for (int k = 1; k < n; k += 2) {
                for (int j = 0; j < n; ++j) {
                    s1 = s1 + (-1 + (2 * m[i][(k) * n + j])) * (m[i][(k + 1) * n + j] - (1 - m[i][(k + 1) * n + j]));
                    s1 = s1 + (-1 + (2 * m[i][(k) * n + j])) * (m[i][(k - 1) * n + j] - (1 - m[i][(k - 1) * n + j]));
                }
            }

            s = (s - ((n * n) - s));

            sc[s + (n * n)][s1 + (n - 1) * (n + n)] = sc[s + (n * n)][s1 + (n - 1) * (n + n)] + 1;

        }
    } else
    {
        //debut de calcul de m,s
        for (int i = 0; i < size; ++i) {

            s = 0;
            s1 = 0;
            //calcul de s
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    s = s + m[i][j * n + k];


                }
            }
            //calcul de m
            //on va d'abord calculer les voisin de gauche et droite
            for (int k = 0; k < n; ++k) {
                for (int j = 1; j < n-1; j += 2) {
                    s1 = s1 + (-1 + (2 * m[i][k * n + j])) * (m[i][k * n + j - 1] - (1 - m[i][k * n + j - 1]));
                    s1 = s1 + (-1 + (2 * m[i][k * n + j])) * (m[i][k * n + j + 1] - (1 - m[i][k * n + j + 1]));

                }
                s1 = s1 + (-1 + (2 * m[i][k * n + n-1])) * (m[i][k * n + n-2] - (1 - m[i][k * n +n-2]));

            }
            //puis calculer les voisin de haut et bas
            for (int k = 1; k < n-1; k += 2) {
                for (int j = 0; j < n; ++j) {
                    s1 = s1 + (-1 + (2 * m[i][(k) * n + j])) * (m[i][(k + 1) * n + j] - (1 - m[i][(k + 1) * n + j]));
                    s1 = s1 + (-1 + (2 * m[i][(k) * n + j])) * (m[i][(k - 1) * n + j] - (1 - m[i][(k - 1) * n + j]));
                }
            }
            for (int j = 0; j <n ; ++j) {
                s1 = s1 + (-1 + (2 * m[i][(n-1) * n + j])) * (m[i][(n-2) * n  + j] - (1 - m[i][(n-2) * n+ j]));

            }
            s = (s - ((n * n) - s));

            sc[s + (n * n)][s1 + (n - 1) * (n + n)] = sc[s + (n * n)][s1 + (n - 1) * (n + n)] + 1;

        }
    }


    //affichage d(m,s)
    printf("\n m: \n");
    for (int i = 0; i <(n*n+1)*2; ++i) {
        for (int j = ((n-1)*(n+n))*2; j >0 ; --j) {


                if (sc[i][j]!=0)

                    printf("%i %i %i \n", (i)-n*n, j-(n-1)*(n+n), sc[i][j]);

            }


    }










    /*
    for (int i = 0; i < size; ++i) {
        printf("matrice %i: \n",i);
        for (int j = 0; j <n ; ++j) {
            for (int k = 0; k <n ; ++k) {
                printf("%i ",m[i][j*n+k]);
            }
            printf("\n");
        }
    }
    */

    return 0;
}
