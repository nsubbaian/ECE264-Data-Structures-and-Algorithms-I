//Nithilam Subbaian
//DSA Programming Assignment #1
/*
This main file uses a base class called SimpleList to implement a singly linked
list with the functions of inserting a node at the start of the list, inserting
a node at the end of the list and removing a node from the start of the list.

This base class, along with other included features, as well as a function to
read from a file and three other functions to parse the information from the file,
allow the program to create, push and pop onto a stack or queue based on the
instruction, and output the result into a text file, based on the guidelines
provided in the DSA Programming Assignment #1 Document.
*/

#include <cstdlib>
#include <string>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename T>
class SimpleList {
private:
  typedef struct node{
      T data;
      node* next;
  }* nodePtr;

  nodePtr head;
  nodePtr curr;  //curr and temp are both used to implement the linked list
  nodePtr temp;
  nodePtr lastnode;

  string Listname;

protected:
  void AddNodeatStart(T addstartdata);
  void AddNodeatEnd (T addData);
  T RemoveNodeatStart();

public:
  void PrintListName();
  std::string retrieveListName();
  explicit SimpleList(string nameoflist);
  bool Empty() const;
  virtual void push(T entry)= 0;
  virtual T pop()= 0;

};

template <typename T>
class queue: public SimpleList<T>{
public:
  void push(T entry){
    SimpleList<T>::AddNodeatEnd(entry);
  }
  T pop(){
    return SimpleList<T>::RemoveNodeatStart();
  }
  explicit queue(string queuename);
};

template <typename T>
queue<T>::queue(string queueName):SimpleList<T>(queueName)
{}


  template <typename T>
  class stack: public SimpleList<T>{
  public:
    void push(T entry){
      SimpleList<T>::AddNodeatStart(entry);
    }
    T pop(){
      return SimpleList<T>::RemoveNodeatStart();
    }
    explicit stack(string stackname);
  };

  template <typename T>
  stack<T>::stack(string stackName):SimpleList<T>(stackName){}


    template <typename T>
    SimpleList<T>::SimpleList(string nameoflist){
      head = NULL;
      curr = NULL;
      temp = NULL;
      lastnode = NULL;
      Listname = nameoflist;
    }


    template <typename T>
    string SimpleList<T>::retrieveListName(){
      return Listname;
    }


    template <typename T>
    bool SimpleList<T>::Empty() const
    {
      return (head == NULL);
    }

    template <typename T>
    void SimpleList<T>::AddNodeatStart(T addstartdata){
      nodePtr noo = new node;
      noo-> next = NULL;
      noo-> data = addstartdata;

      if(head != NULL){
        temp = head;
        noo->next = temp;
        head = noo;
        }
      else{
        head = noo;
      }
    }

    template <typename T>
    void SimpleList<T>::AddNodeatEnd(T addData){
      nodePtr n = new node;
      n-> next = NULL;
      n-> data = addData;

      if(head != NULL){
        curr = head;
        while(curr->next != NULL){
          curr = curr->next;
        }
        curr->next = n;
        lastnode = n;
      }
      else{
        head = n;
      }
    }

    template <typename T>
    T SimpleList<T>::RemoveNodeatStart(){
      T thing;
      if(head != NULL){
      nodePtr soo = NULL;
      soo = head;
      temp = head->next;
      head = temp;
      thing = soo->data;
      delete soo;
      }
    else{
  //    cout<<"the list is empty";
      }
      return thing;
    }


ifstream inFile;
ofstream outFile;

list<SimpleList<int> *> listSLi;
list<SimpleList<double> *> listSLd;
list<SimpleList<string> *> listSLs;

template <typename T>
SimpleList<T>* search(list<SimpleList<T> *> &chosenlist, string listName){
  for (typename list<SimpleList<T> *>::const_iterator itr = chosenlist.begin(); itr != chosenlist.end(); ++itr){
    if ((*itr)->retrieveListName() == listName){
      return *itr;
    }
  }
  return NULL;
}

template <typename T>
void creation(list<SimpleList<T> *> &listSL, string command, string name, T value, string valuetwo){
    if(command.substr(0,1) == "c"){
      if (search(listSL, name) != NULL)
        {
            outFile << "ERROR: This name already exists!" << endl;
        }
      else if(valuetwo == "stack"){
        stack<T>* ptrSL = new stack<T>(name);
        listSL.push_front(ptrSL);
      }
      else if(valuetwo =="queue"){
        queue<T>* ptrSL = new queue<T>(name);
        listSL.push_front(ptrSL);
      }
      else{
    //    cout<<"error in reading 1";
      }
    }
      else if(command.substr(0,2) == "po"){
        SimpleList<T> *ptr = search(listSL, name);
            if (ptr == NULL){
              outFile << "ERROR: This name does not exist!" << endl;
            }
            else if (ptr-> Empty()) {      //This function is used because private information needs to be accessed from within.
              outFile << "ERROR: This list is empty!" << endl;
            }
            else {
              outFile << "Value popped: " << ptr->pop() << endl;
            }
      }
      else if (command.substr(0,2) == "pu"){
        SimpleList<T> *ptr = search(listSL, name);
        if (ptr == NULL){
          outFile << "ERROR: This name does not exist!" << endl;
          }
        else{
            ptr-> push(value);
        }
      }
    }


void process(string eachline){
        outFile << "PROCESSING COMMAND: " << eachline << endl;
        string command;
        string name;
        string value;
        istringstream in(eachline);
        in >> command>> name>>value;
        int intmidway = 0;
        double doublemidway = 0.00;
        if (name.substr(0,1) == "i"){
          string valuetwo =value;
          intmidway = atoi(value.c_str());
            creation<int>(listSLi, command, name, intmidway, valuetwo); //valuetwo and intmidway is used as the creation function needs the data as different types
        }
        else if (name.substr(0,1) == "d"){
          string valuetwo=value;
          doublemidway = atof(value.c_str());
            creation<double>(listSLd, command, name, doublemidway, valuetwo); //see above for doublemidway and valuetwo
        }
        else if(name.substr(0,1) == "s"){
          string valuetwo=value;
            creation<string>(listSLs,command,name, value, valuetwo);
        }
      }

int main() {

  string inputname;
  cout << "Enter name of input file:";
  cin >> inputname;
  inFile.open(inputname.c_str());
  string outputname;
  cout <<"Enter name of output file: ";
  cin >> outputname;
  outFile.open(outputname.c_str());

  string eachline;
  while(getline(inFile, eachline)) {
    process(eachline);
    }
    if (inFile.bad()){
    perror("error while reading file");   //error ouput in case file can't be read
    }
    return 0;
}
