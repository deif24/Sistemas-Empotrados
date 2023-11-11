#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int d=100;

int main(){
	double timeInit=0;
	double timeFin=0;

	printf("Tamaño matrices   Tiempo tardado secuencial \n");
	for(int i=0; i<19; i++){

		// Reserva de matrices
		double **A = (double **)malloc(d * sizeof(double *));
		double **B = (double **)malloc(d * sizeof(double *));
		double **C = (double **)malloc(d * sizeof(double *));
		double **R = (double **)malloc(d * sizeof(double *));
		int **K = (int **)malloc(d * sizeof(int *));
		for (int i = 0; i < d; i++) {
		    A[i] = (double *)malloc(d * sizeof(double));
		    B[i] = (double *)malloc(d * sizeof(double));
		    C[i] = (double *)malloc(d * sizeof(double));
		    R[i] = (double *)malloc(d * sizeof(double));
		    K[i] = (int *)malloc(d * sizeof(int));
		}

		timeInit=0, timeFin=0;
		timeInit=omp_get_wtime();
		// Asignación valores
		for(int i=0; i<d; i++){
			for(int j=0; j<d; j++){
				A[i][j]= (rand()%1000)/1000;
				B[i][j]= (rand()%1000)/1000;
				K[i][j]= rand()%255;
			}
		}

		// Producto vectorial
		for (int i = 0; i < d; i++) {
	        for (int j = 0; j < d; j++) {
	            C[i][j] = 0;
	            for (int k = 0; k < d; k++) {
	                C[i][j] += A[i][k] * A[k][j];
	            }
			}
		}

		// Producto escalar 
		for(int i=0; i<d; i++){
			for(int j=0; j<d; j++){
				R[i][j]=K[i][j]*C[i][j];
			}
		}

		timeFin=omp_get_wtime();

		printf("     %d \t        %f ms \n",d ,(timeFin-timeInit)*1000);
	
		// Liberar la memoria de las matrices
	    for (int i = 0; i < d; i++) {
	        free(A[i]);
	        free(B[i]);
	        free(C[i]);
	        free(K[i]);
	        free(R[i]);
	    }
	    free(A);
	    free(B);
	    free(C);
	    free(K);
	    free(R);

	    d+=50;
	}

	return 0;
}
