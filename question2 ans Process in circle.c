

/*
CS21MOO7 -HIMANSHU DOLEKAR

PARALLEL COMPUTING
ASSIGNMENT 2

QUESTION NO.2
*/


%%writefile q2.c

#include <stdio.h>
#include <mpi.h>
#define next 1


int main (int argc, char *argv[])
{
  int pid, np;
 
  int tosend, toreceive;
  int right, left;
  int sum;

  MPI_Status  status;
  MPI_Request request;


  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  MPI_Comm_size(MPI_COMM_WORLD, &np);

right = pid + 1;          
 if (right == np)
  right = 0; 
 
 left = pid - 1;           
 if (left == -1) 
 left = np-1;

  sum = 0;
  tosend = 10;//any data to send in circle.

  for( int i = 0; i < np; i++) 
  {
    MPI_Issend(&tosend, 1, MPI_INT, right, next, MPI_COMM_WORLD, &request);
   
    MPI_Recv(&toreceive, 1, MPI_INT, left, next, MPI_COMM_WORLD, &status);
    
    MPI_Wait(&request, &status);
    
  if(tosend==toreceive)
    sum =sum + tosend;
   
  }

printf("%d\n",sum);


  MPI_Finalize();
}
