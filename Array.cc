#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Particle.hh"
#include "Array.hh"

Array::Array( const Array& other ) : 
  size(other.size), array(new Particle[other.size]) {
  std::copy(other.array, other.array+other.size, this->array);
}

Array& Array::operator=( Array other) {
  swap(*this, other);
  //This lets us swap every member easily. 
  //We just need a swap function for each type in the same scope the type is defined in 
  return *this;
}

std::ostream& operator<<(std::ostream& os, Array& a) {
  os << a.size << " particles:" << std::endl;
  for(int i=0; i<a.size; i++) {
    os << a[i] << std::endl;
  }
  return os;
}

void swap(Array& one, Array& two) {
  using std::swap;
  swap(one.size, two.size);
  swap(one.array, two.array);
}

Particle& Array::operator[]( const unsigned pos ) {
  //std::cout << "Looking for " << pos << "/" << this->size << std::cout;
  if(pos < this->size) {
  	return this->array[pos];
  } else {
    //WELL BUGGER
  }
}

int Array::load_pb( const char *const filename ) {
  std::ifstream in(filename);
  std::cout << "Reading from "<<filename;
 
  if(!in) {
    std::cerr << "Could not open file " << filename << std::endl;
    return EXIT_FAILURE;
  } else {
    while(in) {
      Particle p;
      in >> p;
      std::cout << ".";
      if(!in) {
        break;
      } else {
        this->push_back(p);
      }
    }
  }
  std::cout << " " << *this;
  return EXIT_SUCCESS; 
}

int Array::load( const char *const filename ) {
  std::ifstream in(filename);
  if(!in) {
    std::cerr << "Could not open file " << filename << std::endl;
    return EXIT_FAILURE;
  } else {
    double pos, vel;
    char sym;
      
    std::cout << "Reading";
    this->size = 0;
    delete [] this;
    in >> sym >> pos >> vel;
    while(!in.eof() && in.good()) {
      std::cout << ".";
      this->size++;
      in >> sym >> pos >> vel;
    }
    if(this->size < 1) {
      std::cerr << "No particles in file " << filename << std::endl;
      return EXIT_FAILURE;
    }

    this->array = new Particle[this->size];
    in.clear(); // Couldn't find reset
    in.seekg(0, std::ios::beg);
  }

  std::cout << " found " << this->size << " particles." << std::endl;

  for(int i=0; i<this->size; i++) {        
    in >> this->array[i];
  }

  std::cout << *this;
  return EXIT_SUCCESS;
}

void Array::update( Screen& screen ) {
  for(int i=0; i<this->size; i++)
  {
    this->array[i].draw(screen);
    this->array[i].move();
  }
}

int Array::push_back( Particle& p ) {
  Particle* array_copy = new Particle[this->size+1];
  std::copy(this->array, this->array+size, array_copy);
  swap(array_copy[size], p);
  delete[] this->array;
  this->array = array_copy;
  return this->size++;
}
