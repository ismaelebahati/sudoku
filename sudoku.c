#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define L 3

char **matInit(){
    char **res = malloc((L*L)*sizeof(char*));
    
    for (int i=0; i<(L*L); i++){
        res[i]=malloc((L*L)*sizeof(char));
        for (int j=0; j<(L*L); j++){
            res[i][j]='-';
        }
    }
    
    return res;
}

void matFree(char **mat){
    for (int i=0; i<(L*L); i++){
        free(mat[i]);
    }
    free(mat);
}


void matPrint(char **mat){


    for (int i=0; i<(L*L); i++){
        for (int j=0; j<(L*L); j++)
            printf("%c  ", mat[i][j]);
        printf("\n");
    }        
    printf("\n");
}


//this function fills n empty elements of mat with random numbers, it does NOT set it to emptymat
void matRandFill(char **mat, int n){
    int cnt=0, pos, i, j;
    while (cnt<n){
        pos = rand()%(L*L*L*L);
        i = pos/(L*L);
        j = pos%(L*L);
        while (mat[i][j]!='-'){
            pos = (pos+1)%(L*L*L*L);
            i = pos/(L*L);
            j = pos%(L*L);
        }
        mat[i][j]=(char) (rand()%(L*L)+48+1);
        cnt++;
        
    }
}

void clearV(int *vec){
    for (int i=0; i<(L*L); i++)
        vec[i]=0;
}

int matCheckS(char **mat){
    int checkL[L*L], checkSQ[L*L], checkC[L*L];
    char a;
    for (int i=0; i<(L*L); i++){
        clearV(checkL);
        clearV(checkC);
        clearV(checkSQ);
        for (int j=0; j<(L*L); j++){
            //this checks for lines
            if ((a=mat[i][j])!='-'){
                if (checkL[a-'0'-1]>0)return 0;
                checkL[a-'0'-1]=1;
            }

            //this checks for columns
            if ((a=mat[j][i])!='-'){
                    if (checkC[a-'0'-1]>0)return 0;
                checkC[a-'0'-1]=1;
            }

            //this checks for squares
            if ((a=mat[j/L+L*(i%L)][j%L+L*(i/L)])!='-'){
                if (checkSQ[a-'0'-1]>0)return 0;
                checkSQ[a-'0'-1]=1;
            }

    
        }
    }return 1;
}

void matCpy(char **src, char **dst){
    for (int i=0; i<(L*L); i++)
        for (int j=0; j<(L*L); j++)
            dst[i][j]=src[i][j];
}

void mat2zero(int mat[L*L][L*L]){
    for (int i=0; i<(L*L); i++)
        for (int j=0; j<(L*L); j++)
            mat[i][j]=0;
}

void matSolveSR(int pos, char **sol, int *found){
    if (!matCheckS(sol)||*found) return;

    
    if (pos>=(L*L*L*L)){
        *found=1;
        return;
    }
    int i=pos/(L*L);
    int j= pos %(L*L);


    if (sol[i][j]=='-'){
        for (int m=0; m<(L*L) && !*found; m++){
            sol[i][j]=(char)(m+48+1);
            matSolveSR(pos+1, sol, found);
            if (!*found)
                sol[i][j]='-';
            }
        }else{
        matSolveSR(pos+1, sol, found);
    }
}

int matSolveS(char **mat){
    char **sol=matInit();
    matCpy(mat, sol);
    int found=0;
    matSolveSR(0, sol, &found);
    if (found) {printf("^^This grid is solvable, here is the solution: \n");matPrint(sol);return 1;}
    if (!found){printf("^^This grid is not solvable\n\n");return 0;}
}

int main(){
    srand(time(NULL));
    char **matrice=matInit();
    int N=22;
    matRandFill(matrice, N);
     while (!matCheckS(matrice)){
        matFree(matrice);
        matrice=matInit();
        matRandFill(matrice, N);
    }
    
    matPrint(matrice);
    while(!matSolveS(matrice)){
        matrice=matInit();
        matrice[0][0]=matrice[0][1]=1;
    while (!matCheckS(matrice)){
        matFree(matrice);
        matrice=matInit();
        matRandFill(matrice, N);
    }
    matPrint(matrice);
    }    
    return 0;
}

