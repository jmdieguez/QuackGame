#ifndef COLOR_H
#define COLOR_H

#include <string>

class Color
{
private:
    int r, g, b;
    std::string text;

public:
    Color();
    Color(int red, int green, int blue);
    Color(int red, int green, int blue, std::string text);
    int get_red() const;
    int get_green() const;
    int get_blue() const;
    std::string get_text() const;
    bool operator==(const Color &other) const;
    ~Color();
};

#endif // COLOR_H