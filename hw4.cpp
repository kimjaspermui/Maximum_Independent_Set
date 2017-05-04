/**
 * Name:            Kim Jasper Mui
 * Date:            May 03 2017
 * Filename:        hw4.cpp
 * Description:     CSE 101 hw4 problem 4 solutions.
 * Sources of help: None.
 */

#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include "util.h"

using namespace std;

void printGraph(vector<vector<int>>* myGraph) {

  for (int i = 0; i < myGraph->size(); i++) {

    for (int j = 0; j < myGraph->size(); j++) {

      cout << (*myGraph)[i][j] << " ";
    }

    cout << endl;
  }
}

void populateGraph(vector<vector<int>>* myGraph, int size) {

  // to generate 0 or 1 with probability 1/2
  random_device r1;
  mt19937 g1(r1());
  uniform_int_distribution<int>  d1(0, 1);

  // populate the matrix with cell and value 0
  for (int i = 0; i < size; i++) {

    myGraph->push_back(vector<int>());

    for (int j = 0; j < size; j++) {

      (*myGraph)[i].push_back(0);
    }
  }

  int randomValue = 0;

  // populate the graph
  for (int i = 0; i < size; i++) {

    for (int j = i + 1; j < size; j++) {

      randomValue = d1(g1);

      // make sure graph is symmetric
      (*myGraph)[i][j] = randomValue;
      (*myGraph)[j][i] = randomValue;
    }
  }
}

int main(int argc, char* argv[]) {

  // check arguments number
  int NUM_ARGUMENTS = 2;

  if (argc != NUM_ARGUMENTS) {

    cout << "Error! Must input the size of the graph" << endl;

    return 1;
  }

  int n = stoi(argv[1]);

  vector<vector<int>> myGraph;
  int indepSet[n];
  memset(indepSet, 0, n * sizeof(int) );

  for (int i = 0; i < n; i++) {

    cout << indepSet[i] << endl;
  }

  populateGraph(&myGraph, n);

}
