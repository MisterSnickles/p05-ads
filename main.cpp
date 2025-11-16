#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include "Sortable.h"

using namespace std;

/*
 * Handle exception when accessing a file/folder
 */
struct FileException {
  FileException(const string file) {
    cout << endl << "'" << file << "'" << " could not be accessed." << endl;
  }
};

/*
 * Generate random elements for the input array.
 */
void GenerateArray(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    int num = (rand()) % (size * 2);
    arr[i] = num;
  }
}

/*
 * Print all the elements in int array arr to output stream o.
 * Elements are separated by a single space.
 */
void PrintArrayToStream(int* arr, int size, ostream& o) {
  for (int i = 0; i < size; i++) {
    o << arr[i] << " ";
  }
  o << endl;
}

/*
 * Print all the elements in the Sortable to output stream o.
 * Elements are separated by a single space.
 */
void PrintSortedToStream(Sortable<int> sorted, ostream& o) {
  for (int i = 0; i < sorted.size(); i++) {
    int n;
    sorted.retrieve(i, n);
    o << n << " ";
  }
  o << endl;
}

/*
 * Test four different pivot strategies.
 * The pivot option 0: last element as pivot. 
 * (from the textbook, 0 is not an option in Sortable: just here.)
 * The pivot option 1: first element as pivot.
 * The pivot option 2: randomly choosing the pivot.
 * The pivot option 3: choose the median of 3 randomly selected elements as pivot.
 * The pivot option 4: choose the median of first, center, and last elements as pivot.
 */
void TestQuicksort() {
  clock_t start, finish;

  // create the output repository
  string path = "./output";

  // if you are not using Windows, there might be an error for the following mkdir() function
  // and then try the one commented below or fix it by own method
  // int status = mkdir(path.c_str(), 0755);
  int status = mkdir(path.c_str());
  if (status == 0) {
    cout << "Diretory created." << endl;
  }
  else {
    if (errno == EEXIST) {
      cout << "Directory exists." << endl;
    }
    else {
      throw FileException(path);
    }
  }

  string unsorted = path + "/unsorted.dat";
  ofstream origin(unsorted);
  if (!origin) {
    throw FileException(unsorted);
  }

  // manage test output files
  const int max_option = 6; // option 0 = left center quick sort from lecture. options 1-4 = different pivot strategies. option 5 = merge sort
  ofstream sorted[max_option];
  ofstream durations[max_option];
  for (int idx = 0; idx < max_option; idx++) {
    string sorted_file = path + "/sorted" + to_string(idx) + ".dat";
    string run_time = path + "/time" + to_string(idx) + ".dat";
    sorted[idx].open(sorted_file);
    durations[idx].open(run_time);
    if (!sorted[idx]){
      throw FileException(sorted_file);
    }
    if (!durations[idx]){
      throw FileException(run_time);
    }
  }

  // randomly generate test arrays with a certain size: run multipe tests for each size
  for (int size = 2000; size <= 20000; size += 2000) {
    int* arr = new int[size];

    // since the test arrays are randomly generated, we need to run multiple tests
    // to have a fair evaluation.
    // for each size, run 5 tests: get the average performance of these 5 tests
    for (int repeat = 0; repeat < 5; repeat++) {
      // gererate the array randomly
      GenerateArray(arr, size);
      PrintArrayToStream(arr, size, origin);
      
      for (int idx = 0; idx < max_option; idx++) {
        // TODO 3: modify this part to include merge_sort in the comparison
        
        Sortable<int> sortable(arr, size);
        start = clock();
        if (idx == 0) {
          sortable.quick_sort();
        }
        else if(idx >=1 && idx <=4){ 
          sortable.quick_sort(idx);
        } else if(idx == 5){
          sortable.merge_sort(); 
        }
        finish = clock();

        // output to files
        PrintSortedToStream(sortable, sorted[idx]);
        durations[idx] << (double)(finish - start) / CLOCKS_PER_SEC << endl;
      }
    }

    delete arr;
    arr = nullptr;
  }

  // clean up
  for (int idx = 0; idx < max_option; idx++) {
    sorted[idx].close();
    durations[idx].close();
  }
}

int main(int argc, char* argv[])
{
  try {
    srand(time(NULL));  // seed for generating random numbers
    TestQuicksort();
  }
  catch(...)
  {
      cout << "Program ended." << endl;
      exit(EXIT_FAILURE);
  }
  return 0;
}