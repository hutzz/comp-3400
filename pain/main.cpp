#include <iostream>

void modifyInt(int& a, int b) {
    a = b;
}

int main() {
    typedef struct Rectangle {
        int length;
        int width;
    } Rect;

    Rect* r = new Rect {5, 3};
    modifyInt(r->length, 6);
    std::cout << r->length << std::endl;

    enum class Color { red, blue, green };
    Color c = Color::red;
    std::cout << static_cast<std::underlying_type<Color>::type>(c) << std::endl;
    return 0;
}