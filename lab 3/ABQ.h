///////////////////////////////////////////////////////////////////////////////
///////////////////////ONLY WORK IN THIS FILE//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

template<class T>
class ABQ {
  static double scale;
  unsigned int size;
  unsigned int capacity;
  T *data;
  void resize(double scale);

public:
  ABQ();
  ABQ(int capacity);
  ABQ(const ABQ &d);
  ABQ& operator = (const ABQ &d);
  ~ABQ();
  void enqueue(T data);
  T dequeue();
  T peek();
  unsigned int getSize();
  unsigned int getMaxCapacity();
  T* getData();
};

template <class T>
double ABQ<T>::scale = 2.0;
template <class T>
ABQ<T>::ABQ() {
  capacity = 1;
  size = 0;
  data = new T[capacity];
}

template <class T>
ABQ<T>::ABQ(int capacity){
  this-> capacity = capacity;
  size=0;
  data = new T[this-> capacity];
}

template <class T>
ABQ<T>::ABQ(const ABQ<T> &d){
  capacity = d.capacity;
  size = d.size;
  data = new T[capacity];
  for(int i=0; i<size; i++)
    data[i] = d.data[i];
}

template <class T>
ABQ<T>& ABQ<T>::operator = (const ABQ<T> &d){
  if(this != &d){
    delete [] data;
    size = d.size;
    data = new T[capacity];
    for(int i=0; i<size; i++)
      data[i] = d.data[i];
  }
  return *this;
}

template <class T>
ABQ<T>::~ABQ(){
  delete [] data;
}

template <class T>
void ABQ<T>:: enqueue(T data){
  if(size == capacity){
    resize(scale);
  }
  this-> data[size] = data;
  size++;
}

template <class T>
T ABQ<T>::dequeue() {
  if(size ==0)
    throw runtime_error("Cannot dequeue from an empty queue.");
  T item = data[0];
  for(int i=0; i<size-1; i++)
    data[i] = data[i+1];
  size--;
  if(capacity > 1){
    if((((double)size)/capacity) < ((double)1/scale))
      resize((double)1/scale);
  }
  return item;
}

template <class T>
T ABQ<T>::peek(){
  if(size==0)
    throw runtime_error("Cannot dequeue from an empty queue.");
  return data[0];
}

template <class T>
unsigned int ABQ<T>:: getSize(){
  return size;
}

template <class T>
unsigned int ABQ<T>::getMaxCapacity(){
  return capacity;
}

template <class T>
T* ABQ<T>::getData(){
  return data;
}

template <class T>
void ABQ<T>::resize(double scale){
  T *tempData = new T[(int)(capacity*scale)];
  for(int i=0; i<size; i++)
    tempData[i] = data[i];
  capacity = capacity*scale;
  delete [] data;
  data = tempData;
}