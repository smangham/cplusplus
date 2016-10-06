// N.B. This program contains a bug, on purpose.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Particle.hh"
#include "Screen.hh"

int main() {
  int timeStep = 0;
  const int stopTime = 60;
  int num_particles;
  double pos, vel;
  char sym;
  Particle* p;
  Screen screen(1+(maxColumn-minColumn));

  //Particle P = {Particle(0,  6.3, 'x'), Particle(79, -4.4, 'o'), Particle(50,  3.0, '+')}; Better declaration
  std::ifstream in("particles.csv");
  if(!in) {
    std::cerr << "Could not open file!" << std::endl;
    return EXIT_FAILURE;
  } else {
    in >> num_particles;
    std::cout << "Reading in " << num_particles << " particles..." << std::endl;
    p = new Particle[num_particles];
  }

  for(int i=0; i<num_particles; i++) {
    in >> pos >> vel >> sym;
    if(in.good()) {
      p[i] = Particle(pos, vel, sym);
      std::cout << "(" << i+1 << "/" << num_particles << ") " << p[i] << std::endl;
    } else { 
      std::cerr << "Error!" << std::endl;
      return EXIT_FAILURE;
    } 
  }

  while (timeStep < stopTime) {
    screen.clear();
    for(int i=0; i<num_particles; i++)
    {
      p[i].draw(screen);
      p[i].move();
    }
    screen.print();
    timeStep++;
  }
  std::cout << "Listing " << num_particles << " particles:" << std::endl;
  for(int i=0; i<num_particles; i++) {
    std::cout << p[i] << std::endl;
  }
}

