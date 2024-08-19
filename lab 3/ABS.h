///////////////////////////////////////////////////////////////////////////////
///////////////////////ONLY WORK IN THIS FILE//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

template <class T>
class ABS {
private:
    static double scale;
    unsigned int size;
    unsigned int capacity;
    T *data;
    void resize(double scale);

public:
    // Constructors
    ABS(); // Default constructor
    ABS(int capacity); //capacity constructor
    ABS(const ABS &d); // Copy constructor
    ABS& operator=(const ABS &d);
    ~ABS();  // Destructor

    void push(T data);
    T pop();
    T peek();
    unsigned int getSize();
    unsigned int getMaxCapacity();
    T* getData();
};

template <class T>
double ABS<T>::scale = 2.0;

template <class T>
ABS<T>::ABS(){
  capacity = 1;
  size = 0;
  data = new T[capacity];
}

template <class T>
ABS<T>::ABS(int capacity) {
  this->capacity = capacity;
  size = 0;
  data = new T[this->capacity];
}

template <class T>
ABS<T>::ABS(const ABS<T> &d)
{
  capacity = d.capacity;
  size = d.size;
  data = new T[capacity];
  for(int i=0; i<size; i++)
    data[i] = d.data[i];
}

template <class T>
ABS<T>& ABS<T>::operator=(const ABS<T> &d)
{
  if (this != &d){
    delete [] data;
    capacity = d.capacity;
    size = d.size;
    data = new T[capacity];
    for (int i=0; i<size; i++)
      data[i] = d.data[i];
  }
  return *this;
}

template <class T>
ABS<T>::~ABS() {
  delete [] data;
}

template <class T>
void ABS<T>::push(T data){
  if(size == capacity) {
    resize(scale);
  }
  this->data[size] = data;
  size++;
}

template <class T>
T ABS<T>::pop(){
  if(size == 0)
    throw runtime_error("Cannot pop from an empty stack.");
  T item = data[size-1];
  size--;
  if(capacity > 1){
    if((((double)size)/capacity) < ((double)1/scale))
      resize((double)1/scale);
  }
  return item;
}

template <class T>
T ABS<T>::peek(){
  if(size==0)
    throw runtime_error("Cannot peek from an empty stack.");
  T item = data[size-1];
  return item;
}

template <class T>
unsigned int ABS<T>::getSize() {
  return size;
}

template <class T>
unsigned int ABS<T>::getMaxCapacity() {
  return capacity;
}

template <class T>
T* ABS<T>::getData() {
  return data;
}

template <class T>
void ABS<T>::resize(double scale) {
  T *tempData = new T[(int)(capacity*scale)];
  for(int i =0; i<size; i++)
    tempData[i] = data[i];
  capacity = capacity*scale;
  delete [] data;
  data = tempData;
}