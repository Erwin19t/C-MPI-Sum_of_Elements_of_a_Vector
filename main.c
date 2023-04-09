//Programa que realiza la suma algebraica de 
//elementos en un arreglo en paralelo

//compilar: gcc -Wall -o ejecutable programa.c -l mpi
//ejecutar: mpirun -oversubscribe -np N ejecutable

#include <stdio.h>
#include <mpi.h>

#define N 10

int main(int argc, char **argv){
	int nproc, id;
	//Inicializacion de MPI
	MPI_Init(&argc, &argv);
	//Asignacion de # de proc e identificacion de proc
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	
	//printf("Hola, soy el procesador  %d de %d\n", id, nproc);
	
	
	if(!id){	//Es equivalente a escribir if(id != 0)
	//Codigo para master
		int * array = NULL;
		int *temp
		int i, size;
		array = (int *) malloc(10*sizeof(int));
		if(array == NULL){
			printf("Codo, saca la ORO de AE\n");
			exit(-1)
		}
		for(i=0; i<N ; i++){
			array[i] = i + 1;
		}
		printf("\n");
		size = N / nproc;
		//For de numero de operacions a realizar
		for(i=1; i<nproc; i++){
			MPI_Send(&size, 1, MPI_INT, i, i,MPI_COMM_WORLD);
		}
		temp = array;
		for(i=1; i<nproc; i++){
			array += size;
			MPI_Send(array, size, MPI_INT, i, i,MPI_COMM_WORLD);
		}
		array = temp
		free(array);
	}
	else{
	//Codigo para slaves
		int nSumas, k;
		int * subArray = NULL;
		
		MIP_Recv(&nSumas, 1, MPI_INT, 0, id,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Comunicacion exitosa\n");
		printf("# de sumas: %d\n",nSumas);
		
		subArray = (int *)malloc(nSumas*sizeof(int));
		if(subArray == NULL){
			printf("Se necesita mas RAM\n");
			exit(-1);
		}
		MIP_Recv(subArray, nSumas, MPI_INT, 0, id,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		for(k = 0; k<nSumas; k++){
			total += subArray[k];
		}
		printf("\n");
	}	
	//Finalizamos MPI
	MPI_Finalize();
	return 0;
}
