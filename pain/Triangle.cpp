#include <iostream>
#include "Triangle.h"

Triangle::Triangle(float base, float height) {
    this->base = base;
    this->height = height;
}
float Triangle::getBase() {
    return base;
}
float Triangle::getHeight() {
    return height;
}
