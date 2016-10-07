#ifndef Screen_hh
#define Screen_hh

class Screen {
public:
  // CONSTRUCTORS
  Screen( unsigned width ) : width(width), buffer(new char[width]) { return; }
  Screen( const Screen& );
  ~Screen() { delete [] this->buffer; };
  // OPERATORS
  friend void swap( Screen&, Screen& );
  char& operator[] ( const unsigned );
  Screen& operator=( Screen );
  // MEMBERS
  void clear();
  void print() const;
private:
  unsigned width;
  char *buffer, junk;
  bool charvalid( const char );
};
#endif
