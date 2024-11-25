#ifndef COLOR_H
#define COLOR_H

class Color
{
private:
    int r, g, b;

public:
    Color();
    Color(int red, int green, int blue);
    int GetRed() const;
    int GetGreen() const;
    int GetBlue() const;
    bool operator==(const Color &other) const;
    ~Color();
};

#endif // COLOR_H