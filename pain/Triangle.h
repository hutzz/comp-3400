#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
    public:
        Triangle(float base, float height);
        float getBase();
        float getHeight();
    private:
        float base;
        float height;
};

#endif