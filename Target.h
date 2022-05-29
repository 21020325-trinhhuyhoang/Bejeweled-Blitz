#ifndef Target_h
#define Target_h

struct Target {
    int x;
    int y;
public:
    Target(int _x = 0, int _y = 0) {
        x = _x;
        y = _y;
    }
    void up() { x--; }
    void down() { x++; }
    void left() { y--; }
    void right() { y++; }
};

#endif