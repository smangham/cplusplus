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
  Particle() : pos(0), vel(0), sym('?') {};
  Particle( const float pos, const float vel, const char sym ) : 
    pos(pos), vel(vel), sym(sym) {};
  virtual ~Particle() {};
  // OPERATORS
  friend void swap(Particle& one, Particle& two);
  friend std::ostream& operator<<(std::ostream&, const Particle&);
  friend std::istream& operator>>(std::istream&, Particle&);
  // MEMBERS
  virtual void move() = 0;
  void draw( Screen& ) const;
protected:
  float pos, vel;
  char sym;
};

class RealParticle : public Particle {
public:
  //CONSTRUCTORS
  RealParticle() : Particle()  {};
  RealParticle( const float pos, const float vel, const char sym ) : 
    Particle(pos, vel, sym)     {};
  //OPERATORS
  RealParticle& operator=( RealParticle );
  friend std::istream& operator>>( std::istream&, RealParticle& );
  // MEMBERS  
  virtual void move();
};

class MagicParticle : public Particle {
public:
  //CONSTRUCTORS
  MagicParticle() : Particle()  {};
  MagicParticle( const float pos, const float vel, const char sym ) : 
    Particle(pos, vel, sym)     {};
  //OPERATORS
  MagicParticle& operator=( MagicParticle );
  friend std::istream& operator>>( std::istream&, MagicParticle& );
  // MEMBERS  
  virtual void move();
};
#endif
