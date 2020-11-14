// Copyright 2018 Nesterov Alexander
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "./bcast.h"

TEST(Parallel_Operations_MPI, Test_Negative_Size) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> vec;
  const int size = -1;
  if (rank == 0) {
  ASSERT_ANY_THROW(getRandomArray(size));
  }
}

TEST(Parallel_Operations_MPI, Test_Get_Random_Array) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  const int size = 100;
  if (rank == 0) {
  ASSERT_NO_THROW(getRandomArray(size));
  }
}

TEST(Parallel_Operations_MPI, TEST_Check_checkSum) {
    int rank, sum;
    sum = -666;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> array{4, 5, 2, 9, 4, 3};
    if (rank == 0) {
       sum = checkSum(array, 6);
       EXPECT_EQ(sum, 27);
    }
}


TEST(Parallel_Operations_MPI, TEST_Get_Sum1) {
    int rank, sum1, sum2;
    int root = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> array;
    if (rank == root) array = getRandomArray(5);
    MPI_Barrier(MPI_COMM_WORLD);
    getSum(array, 5, &sum1, root);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == root) {
       sum2 = checkSum(array, 5);
       EXPECT_EQ(sum1, sum2);
    }
}

TEST(Parallel_Operations_MPI, TEST_Get_Sum2) {
    int rank, sum1, sum2;
    int root = 1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> array;
    if (rank == root) array = getRandomArray(11);
    MPI_Barrier(MPI_COMM_WORLD);
    getSum(array, 11, &sum1, root);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == root) {
       sum2 = checkSum(array, 11);
       EXPECT_EQ(sum1, sum2);
    }
}


TEST(Parallel_Operations_MPI, TEST_Get_Sum3) {
    int rank, sum1, sum2;
    int root = 2;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> array;
    if (rank == root) array = getRandomArray(8);
    MPI_Barrier(MPI_COMM_WORLD);
    getSum(array, 8, &sum1, root);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == root) {
       sum2 = checkSum(array, 8);
       EXPECT_EQ(sum1, sum2);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);
    difOfTime(100, 0);
    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
