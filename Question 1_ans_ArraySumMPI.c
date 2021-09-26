/*
CS21MOO7 -HIMANSHU DOLEKAR

PARALLEL COMPUTING
ASSIGNMENT 2

QUESTION NO.1
*/


%%writefile que.c
#include <mpi.h>
#include <stdio.h>
#define n 10

int main(int argc, char* argv[])
{
		int a[n];

for(int i=0;i<n;i++)
	a[i]=i;


int temp_arr[1000];


	int pid, np,	ep,	rec;

	MPI_Status status;

	MPI_Init(&argc, &argv);


	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &np);


	if (pid == 0) {
		int index, i;
		ep = n / np;

	
		if (np > 1) 
	{
			for (i = 1; i < np - 1; i++) 
	 	{
				index = i * ep;
				MPI_Send(&ep,1, MPI_INT, i, 0,MPI_COMM_WORLD);
				MPI_Send(&a[index],	ep,MPI_INT, i, 0,MPI_COMM_WORLD);
		}			
			index = i * ep;
			int remain = n - index;

			MPI_Send(&remain,1, MPI_INT,i, 0,MPI_COMM_WORLD);
			MPI_Send(&a[index],remain,MPI_INT, i, 0,MPI_COMM_WORLD);
		}

		int sum = 0;
		for (i = 0; i < ep; i++)
			sum += a[i];

		int x;
		for (i = 1; i < np; i++) 
		{
			MPI_Recv(&x, 1, MPI_INT,	MPI_ANY_SOURCE, 0,	MPI_COMM_WORLD,	&status);
			int sender = status.MPI_SOURCE;
			sum += x;
		}
		printf("Sum : %d\n", sum);
	}

	else 
	{
		MPI_Recv(&rec,1, MPI_INT, 0, 0,MPI_COMM_WORLD,&status);
		MPI_Recv(&temp_arr, rec,	MPI_INT, 0, 0,MPI_COMM_WORLD,	&status);

		int result = 0;
		for (int i = 0; i < rec; i++)
			result += temp_arr[i];

		MPI_Send(&result, 1, MPI_INT,	0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
