// N.B. This program contains a bug, on purpose.
#include <iostream>
#include <cstdlib>
#include "Screen.hh"
#include "Particle.hh"
#include "Array.hh"

myswap(int one, int two) {
  swap(one, two);
  int temp;
  
}

int main() {
  int timeStep = 0, index;
  const int stopTime = 60;

  std::string filename("particles.dat");
  
  Array p;
  Screen screen(1+(maxColumn-minColumn));

  //Particle P = {Particle(0,  6.3, 'x'), Particle(79, -4.4, 'o'), Particle(50,  3.0, '+')}; Better declaration
  if(p.load_pb(filename.c_str()) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  Particle p_add(1.0,1.0,'#');
  index = p.push_back(p_add);
  std::cout << "Added " << (p[index]) << std::endl;

  while (timeStep < stopTime) {
    screen.clear();
    p.update(screen);
    screen.print();
    timeStep++;
  }
  std::cout << p;
  return EXIT_SUCCESS;
}

