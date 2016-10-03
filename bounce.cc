// N.B. This program contains a bug, on purpose.

#include <iostream>

void draw( int particlePosition, char particleSymbol ) {
  for (int i = 0; i < particlePosition; i++) {
    std::cout << " ";
  }
  std::cout << particleSymbol << std::endl;
}

void move( double& particlePosition, double& particleSpeed, 
           int minColumn, int maxColumn ) {
  particlePosition += particleSpeed;

  if (particlePosition >= maxColumn) {
    particlePosition = maxColumn;
    particleSpeed = -particleSpeed;
  } else if (particlePosition < minColumn) {
    particlePosition = minColumn;
    particleSpeed = -particleSpeed;
  } 
}

int main() {
  char particleSymbol = 'x';
  int maxColumn = 80;
  int minColumn = 0;
  int timeStep = 0;
  int stopTime = 60;
  double particlePosition = minColumn;
  double particleSpeed = 6.3;

  while (timeStep < stopTime) {
    draw(particlePosition, particleSymbol);
    move(particlePosition, particleSpeed, minColumn, maxColumn);
    timeStep++;
  }
}
