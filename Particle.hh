#ifndef Particle_hh
#define Particle_hh

#include <iostream>

class Screen; // Easier than including whole screen header!
// Give as little information as possible. We prevent cyclical inclusions.

extern const int maxColumn;
extern const int minColumn;
extern const char tail_short;
extern const char tail_long;

class Particle {
public:
  // CONSTRUCTORS
  Particle() : pos(0), vel(0), sym('?')  { return; };
  Particle( const float pos, const float vel, const char sym ) : 
    pos(pos), vel(vel), sym(sym)          { return; };
  // OPERATORS
  friend void swap(Particle& one, Particle& two);
  friend std::ostream& operator<<(std::ostream&, const Particle&);
  friend std::istream& operator>>(std::istream&, Particle&);
  Particle& operator=( Particle );
  // MEMBERS
  void move();
  void draw( Screen& ) const;
private:
  float pos, vel;
  char sym;
};

#endif
