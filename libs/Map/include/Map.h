// Position.h

#ifndef Position_h
#define Position_h

class Position {
public:

    // constructor
    Position(int x, int y);
    Position();

    // const members
    int x() const {return x_; }
    int y() const {return y_; }

    // non-const members

private:
    int x_;
    int y_;
}

#endif