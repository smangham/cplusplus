#ifndef Array_hh
#define Array_hh
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdlib>
#include "Particle.hh"

class Screen;

template<typename T>
class Array {
public:
  // CONSTRUCTORS
  Array() : size(0), array(NULL) {};
  Array( unsigned size ) : size(size), array(new Particle[size]) {};  
  Array( const Array& );
  ~Array()   { delete[] array; };
  // OPERATORS
  T& operator[]( const unsigned );
  Array& operator=( Array );

  friend std::ostream& operator<<( std::ostream& os, Array& a) {
    os << a.size << " entries:" << std::endl;
    for(unsigned i=0; i<a.size; i++) {
      os << a[i] << std::endl;
    }
    return os;
  };
  
  friend void swap( Array&, Array& );
  // MEMBERS
  void update( Screen& screen );
  int load( const char *const );
  int load_pb( const char *const );
  int push_back( T& p );
  int entries() { return size; };
private:
  unsigned size;
  T* array;
};

template<typename T>
Array<T>::Array( const Array<T>& other ) : 
  size(other.size), array(new T[other.size]) {
  std::copy(other.array, other.array+other.size, this->array);
}

template<typename T>
Array<T>& Array<T>::operator=( Array<T> other) {
  swap(*this, other);
  //This lets us swap every member easily. 
  //We just need a swap function for each type in the same scope the type is defined in 
  return *this;
}

// template<typename T>
// std::ostream& operator<<(std::ostream& os, Array<T>& a) {
//   os << a.size << " entries:" << std::endl;
//   for(int i=0; i<a.size; i++) {
//     os << a[i] << std::endl;
//   }
//   return os;
// }

template<typename T>
void swap(Array<T>& one, Array<T>& two) {
  using std::swap;
  swap(one.size, two.size);
  swap(one.array, two.array);
}

template<typename T>
T& Array<T>::operator[]( const unsigned pos ) {
  if(pos < this->size) {
    return this->array[pos];
  } else {
    return this->array[0];
  }
}

template<typename T>
int Array<T>::load_pb( const char *const filename ) {
  std::ifstream in(filename);
  std::cout << "Reading from "<<filename;
 
  if(!in) {
    std::cerr << "Could not open file " << filename << std::endl;
    return EXIT_FAILURE;
  } else {
    while(in) {
      T temp;
      in >> temp;
      std::cout << ".";
      if(!in) {
        break;
      } else {
        this->push_back(temp);
      }
    }
  }
  std::cout << " " << *this;
  return EXIT_SUCCESS; 
}

// int Array::load( const char *const filename ) {
//   std::ifstream in(filename);
//   if(!in) {
//     std::cerr << "Could not open file " << filename << std::endl;
//     return EXIT_FAILURE;
//   } else {
//     double pos, vel;
//     char sym;
      
//     std::cout << "Reading";
//     this->size = 0;
//     delete [] this;
//     in >> sym >> pos >> vel;
//     while(!in.eof() && in.good()) {
//       std::cout << ".";
//       this->size++;
//       in >> sym >> pos >> vel;
//     }
//     if(this->size < 1) {
//       std::cerr << "No particles in file " << filename << std::endl;
//       return EXIT_FAILURE;
//     }

//     this->array = new Particle[this->size];
//     in.clear(); // Couldn't find reset
//     in.seekg(0, std::ios::beg);
//   }

//   std::cout << " found " << this->size << " particles." << std::endl;

//   for(int i=0; i<this->size; i++) {        
//     in >> this->array[i];
//   }

//   std::cout << *this;
//   return EXIT_SUCCESS;
// }


template<typename T> 
int Array<T>::push_back( T& t ) {
  T* array_copy = new T[this->size+1];
  std::copy(this->array, this->array+size, array_copy);
  swap(array_copy[size], t);
  delete[] this->array;
  this->array = array_copy;
  return this->size++;
}

#endif
