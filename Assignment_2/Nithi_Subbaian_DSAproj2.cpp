#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " "
	   << (*ipD)->val2 << " "
	   << (*ipD)->val3 << " "
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }

  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.


list<Data *>::iterator i;
list<Data *>::iterator listone;
list<Data *>::iterator listtwo;
Data *bucketone[94][50000*sizeof(Data*)];
int buckettwo[94];
Data* arr[1010000];

//Code for Column One - Insertion sort
void Insertion_Sort(list<Data *> &l){
  i = l.begin();
  for (i++; i != l.end(); i++){
    listone = i;
    listtwo = i;
    listtwo--;
    while ((*listone)->val1 < (*listtwo) ->val1  && listone != l.begin()){
      iter_swap(listone--, listtwo--);
    }
  }
}


//Code for Column 2 - Uses the baseline sort but converts the linked list into an array
struct baseline_col2 {
bool operator()(const Data* A, const Data* B){return A->val2 < B->val2;}
};

void ArrayConversion_col2(list<Data *> &l) {
    int i = 0;
    for(auto iterator = l.begin(); iterator!=l.end(); iterator++){
        arr[i] = *iterator;
        i++;
    }

    stable_sort(arr, arr + l.size(), baseline_col2());

    i=0;
    for(auto iterator = l.begin(); iterator!=l.end(); iterator++)
    {
        *iterator = arr[i];
        i++;
    }
}

//Code for Column 3 - Bucket Sort, all the numbers chosen(ex. 33) correspond to the
//data input parameters given in the project description
void BucketSort(list<Data *> &l){
  for(list<Data*>::iterator io = l.begin(); io != l.end(); io++){
    char c = (*io)->val3;
    c -= 33;
    bucketone[c][buckettwo[c]++] = *io;
  }
  list<Data*>::iterator io = l.begin();
  for(int x = 0; x < 94; x++){
    for(int y = 0; y < buckettwo[x]; y++){
      (*io) = bucketone[x][y];
      io++;
    }
  }
}

//Code for Column 4 - same as used for Column 3
struct baseline_col4 {
bool operator()(const Data* A, const Data* B){return A->val4 < B->val4;}
};

void ArrayConversion_col4(list<Data *> &l) {
    int i = 0;
    for(auto iterator = l.begin(); iterator!=l.end(); iterator++){
        arr[i] = *iterator;
        i++;
    }

    stable_sort(arr, arr + l.size(), baseline_col4());

    i=0;
    for(auto iterator = l.begin(); iterator!=l.end(); iterator++)
    {
        *iterator = arr[i];
        i++;
    }
}

void sortDataList(list<Data *> &l, int field) {
  switch(field) {
    case 1:
    Insertion_Sort(l);
    break;
    case 2:
    ArrayConversion_col2(l);
      break;
    case 3:
    BucketSort(l);
      break;
    case 4:
    ArrayConversion_col4(l);
      break;
  }
}
