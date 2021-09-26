
/*
CS21MOO7 -HIMANSHU DOLEKAR

PARALLEL COMPUTING
ASSIGNMENT 2

QUESTION NO.5
*/





%%writefile h1.c
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define row 4


int main (int argc, char *argv[])
{
    MPI_Status status;
 
  int	p,a[row],b[row],c=0;             
  int	pid,part,source,dest;                  
	int mtype,rows;           
	int averow, extra, offset, 
  
  MPI_Init(&argc,&argv);
 
  MPI_Comm_rank(MPI_COMM_WORLD,&pid);
  MPI_Comm_size(MPI_COMM_WORLD,&p);
  part = p-1;



   if (pid == 0)
   {
      
      for (int i=0; i<4; i++)
      {
          a[i]=i;
          b[i]=i;
      }
      averow = row/part;
      extra = row%part;
      offset = 0;
      mtype = 1;
      for (dest=1; dest<=part; dest++)
      {
         rows = (dest <= extra) ? averow+1 : averow;   	
      
         MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
         MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
         MPI_Send(&a[offset], row, MPI_INT, dest, mtype,MPI_COMM_WORLD);
         MPI_Send(&b, row, MPI_INT, dest, mtype, MPI_COMM_WORLD);
        offset = offset + rows;
      }
    
      mtype = 2;
      for (int i=1; i<=part; i++)
      {
         source = i;
         MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
         MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
         MPI_Recv(&c, row, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
      
      }

      printf("Result %d\n",c);
     
   }

   if (pid > 0)
   {
      mtype = 1;
      MPI_Recv(&offset, 1, MPI_INT, 0, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, 0, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&a, row, MPI_INT, 0, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&b, row, MPI_INT, 0, mtype, MPI_COMM_WORLD, &status);

      for (int i=0; i<4; i++)
         {
             c=c+a[i]*b[i];
         }
    
      mtype = 2;
      MPI_Send(&offset, 1, MPI_INT, 0, mtype, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, 0, mtype, MPI_COMM_WORLD);
      MPI_Send(&c, row, MPI_INT, 0, mtype, MPI_COMM_WORLD);
   }
   MPI_Finalize();
}