#ifndef Array_hh
#define Array_hh

#include <cstdlib>
#include "Particle.hh"

class Screen;

class Array {
public:
  // CONSTRUCTORS
  Array() : size(0), array(NULL) {};
  Array( unsigned size ) : size(size), array(new Particle[size]) {};  
  Array( const Array& );
  ~Array()   { delete[] array; };
  // OPERATORS
  Particle& operator[]( const unsigned );
  Array& operator=( Array );
  friend std::ostream& operator<<( std::ostream&, Array& );
  friend void swap( Array&, Array& );
  // MEMBERS
  void update( Screen& screen );
  int load( const char *const );
  int push_back( Particle p );
private:
  unsigned size;
  Particle* array;
};
#endif
