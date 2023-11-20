#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int main(){

	double timeInit=0;
	double timeFin=0;
    double timeInitTrans=0;
	double timeFinTrans=0;

    int matTam = 10000;

    // Reserva de matrices
    double **A = (double **)malloc(matTam * sizeof(double *));
    double **AT = (double **)malloc(matTam * sizeof(double *));
    double **C = (double **)malloc(matTam * sizeof(double *));
    
    for (int i = 0; i < matTam; i++) {
        A[i] = (double *)malloc(matTam * sizeof(double));
        AT[i] = (double *)malloc(matTam * sizeof(double));
        C[i] = (double *)malloc(matTam * sizeof(double));

    }

    // Asignación valores
    for(int i=0; i<matTam; i++){
        for(int j=0; j<matTam; j++){
            A[i][j]= (rand()%1000)/1000;
        }
    }

    // Calculamos A transpuesta
    for (int i = 0; i < matTam; ++i) {
        for (int j = 0; j < matTam; ++j) {
            AT[j][i] = A[i][j];
        }
    }

	timeInit=omp_get_wtime();

    // Producto escalar (No transpuesta)
    for(int i=0; i<matTam; i++){
        for(int j=0; j<matTam; j++){
            C[i][j]=A[i][j]*A[i][j];
        }
    }

    timeFin=omp_get_wtime();

	timeInitTrans=omp_get_wtime();

    // Producto escalar (Transpuesta)
    for(int i=0; i<matTam; i++){
        for(int j=0; j<matTam; j++){
            C[i][j]=A[i][j]*AT[i][j];
        }
    }

    timeFinTrans=omp_get_wtime();

    printf("Multiplicacion de matrices (No Transpuesta) -> %f ms \n",(timeFin-timeInit)*1000);
    printf("Multiplicacion de matrices (Transpuesta) -> %f ms \n",(timeFinTrans-timeInitTrans)*1000);


    // Liberar la memoria de las matrices
    for (int i = 0; i < matTam; i++) {
        free(A[i]);
        free(AT[i]);
        free(C[i]);
    }

    free(A);
    free(AT);
    free(C);

	return 0;
}