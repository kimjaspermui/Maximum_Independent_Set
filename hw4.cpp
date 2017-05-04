/**
 * Name:            Kim Jasper Mui
 * Date:            May 03 2017
 * Filename:        hw4.cpp
 * Description:     CSE 101 hw4 problem 4 solutions.
 * Sources of help: None.
 */

#include <iostream>
#include <vector>
#include <random>
#include <set>

using namespace std;

typedef pair<int, int> degreeIndexPair;
const double MAX = 10;

int countNodes(vector<int>* indepSet) {

  int count = 0;

  for (int i = 0; i < indepSet->size(); i++) {

    if ((*indepSet)[i] == 1) {

      count++;
    }
  }

  return count;
}

int countOnes(vector<int>* myVector) {

  int count = 0;

  for (int i = 0; i < myVector->size(); i++) {

    if ((*myVector)[i] == 1) {

      count++;
    }
  }

  return count;
}

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

void populateSet(vector<vector<int>>* myGraph, set<degreeIndexPair>* mySet) {

  for (int i = 0; i < myGraph->size(); i++) {

    mySet->insert({countOnes(&(*myGraph)[i]), i});
  }
}

void populateIndepSet(vector<vector<int>>* myGraph, set<degreeIndexPair>* mySet,
vector<int>* indepSet) {

  for (auto myPair : *mySet) {

    int rowIndex = myPair.second;
    vector<int> myVector = (*myGraph)[rowIndex];
    bool fail = false;

    for (int i = 0; i < myVector.size(); i++) {

      if (myVector[i] == 1 && (*indepSet)[i] == 1) {

        fail = true;
        break;
      }
    }

    if (!fail) {

      (*indepSet)[rowIndex] = 1;
    }
  }
}

void initIndepSet(vector<int>* indepSet, int n) {

  indepSet->clear();

  for (int i = 0; i < n; i++) {

    indepSet->push_back(0);
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
  vector<int> indepSet;
  set<degreeIndexPair> mySet;

  double sum = 0;

  for (int j = 1; j <= n; j++) {

    sum = 0;

    for (int i = 0; i < MAX; i++) {

      myGraph.clear();
      mySet.clear();
      initIndepSet(&indepSet, j);

      populateGraph(&myGraph, j);
      // printGraph(&myGraph);
      populateSet(&myGraph, &mySet);
      populateIndepSet(&myGraph, &mySet, &indepSet);

      // cout << "Size of Independent Set: " << countNodes(&indepSet) << endl;
      sum += countNodes(&indepSet);
    }

    // cout << "Average Independent Set of size " << j << " is: " << sum / MAX
    // << endl;

    cout << sum / MAX << endl;
  }
}
