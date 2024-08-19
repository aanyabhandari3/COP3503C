#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
using namespace std;

void TestAddHead();
void TestAddTail();
void TestAddingArrays();
void addHeadFullTest();
void addTailFullTest();

int main()
{
//FREEZE CODE BEGIN
    int testNum;
    cin >> testNum;
    if (testNum == 1)
        TestAddHead();
    else if (testNum == 2)
        TestAddTail();
    else if (testNum == 3)
        TestAddingArrays();
    else if (testNum == 4)
        addHeadFullTest();
    else if (testNum == 5)
        addTailFullTest();
//FREEZE CODE END
    
    
    return 0;
}

void TestAddHead()
{
    cout << "=====Testing AddHead() functionality====" << endl;
    LinkedList<int> data;
    for (int i = 0; i < 12; i += 2)
        data.AddHead(i);
    cout << "Node count: " << data.NodeCount() << endl;
    cout << "Print list forward:" << endl;
    data.PrintForward();
    cout << "Print list in reverse:" << endl;
    data.PrintReverse();
}

void TestAddTail()
{
    cout << "=====Testing AddTail() functionality====" << endl;
    LinkedList<int> data;
    for (int i = 0; i <= 21; i += 3)
        data.AddTail(i);
    cout << "Node count: " << data.NodeCount() << endl;
    cout << "Print list forward:" << endl;
    data.PrintForward();
    cout << "Print list in reverse:" << endl;
    data.PrintReverse();
}

void TestAddingArrays()
{
    cout << "=====Testing AddNodesHead() and AddNodesTail() =====" << endl;

    string values[5];
    values[0] = "*";
    values[1] = "**";
    values[2] = "***";
    values[3] = "****";
    values[4] = "*****";

    LinkedList<string> list;
    list.AddHead("**");
    list.AddHead("***");
    list.AddHead("****");
    list.AddHead("*****");
    list.AddHead("******");
    list.AddHead("*******");
    list.AddHead("********");
    list.AddHead("*********");
    list.AddHead("********");
    list.AddHead("*******");
    list.AddHead("******");

    list.AddNodesHead(values, 5);
    list.AddNodesTail(values, 5);
    list.PrintForward();
}

void addHeadFullTest() {
	LinkedList<int> list;
	list.AddHead(1);
	list.AddHead(2);
	list.AddHead(3);
  list.AddHead(4);
  LinkedList<int>::Node* start = list.Head();
  
  if(start->prev!=nullptr){
      std::cout << "Your head doesnt have a prev pointer to nullptr after using AddHead";
      return;
  }
  

  int count = 4;
  while(start!=nullptr){
  
    if(start->data == count){
      count--;
      start = start->next;
    }
    else{
      std::cout << "Numbers are not in the right order" << std::endl;
      return;
    }
  }

  if(count != 0){
    std::cout << "The while loop above didn't good through 4 iterations" << std::endl;
  }

  std::cout << "Passed Test Case" << std::endl;
}

void addTailFullTest() {
	LinkedList<int> list;
	list.AddTail(4);
	list.AddTail(3);
	list.AddTail(2);
  list.AddTail(1);
  LinkedList<int>::Node* start = list.Head();
  
  if(start->prev!=nullptr){
      std::cout << "Your head doesnt have a prev pointer to nullptr after using AddTail";
      return;
  }
  

  int count = 4;
  while(start!=nullptr){

    if(start->data == count){
      count--;
      start = start->next;
    }
    else{
      std::cout << "Numbers are not in the right order" << std::endl;
      return;
    }
  }
  
  if(count != 0){
    std::cout << "The while loop above didn't good through 4 iterations" << std::endl;
  }

  std::cout << "Passed Test Case" << std::endl;
}