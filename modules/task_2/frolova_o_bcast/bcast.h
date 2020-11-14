// Copyright 2018 Nesterov Alexander
#ifndef MODULES_TASK_2_FROLOVA_O_BCAST_BCAST_H_
#define MODULES_TASK_2_FROLOVA_O_BCAST_BCAST_H_
#include <mpi.h>
#include <vector>
#include <string>

std::vector<int> getRandomArray(int size);
int checkSum(std::vector<int> array, int size);
void my_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);
int forProc(int cur, int root, int procNum);
int fromProc(int cur, int root, int procNum);
void getSum(std::vector<int> array, int size, int *sum, int root);
void difOfTime(int count, int root);

#endif  // MODULES_TASK_2_FROLOVA_O_BCAST_BCAST_H_
