#ifndef INC_3D_GRAPHICS_CUBE_H
#define INC_3D_GRAPHICS_CUBE_H

#include <vector>

struct color {
    double red;
    double green;
    double blue;
    double alpha; // Opacity (0 is transparent, 1 is solid)

    /* Constructors */
    color();

    color(double r, double g, double b);

    color(double r, double g, double b, double a);

    /* Overloaded Operator */
    friend bool operator==(const color &lhs, const color &rhs) {
        if (lhs.blue != rhs.blue) {
            return false;
        } else if (lhs.red != rhs.red) {
            return false;
        } else if (lhs.green != rhs.green) {
            return false;
        } else if (lhs.alpha != rhs.alpha) {
            return false;
        }
        return true;
    }
};

struct point {
    double x;
    double y;
    double z;
};

class Cube {
private:
    unsigned int edgeLength;
    std::vector<point> corners;
    color fill;
    point center;
    bool shadow;

    // Private helper methods
    void resetCorners();

    void drawPoint(const point &p) const;

    void updateCorners(double delta_x, double delta_y, double delta_z);

public:
    // Constructors
    Cube();

    Cube(point center, unsigned int edge_length);

    // Getters
    unsigned int getEdgeLength();

    color getFill();

    point getCenter();

    bool getShadow();

    // Setters
    void setEdgeLength(unsigned int e);

    void setFill(color c);

    void setCenter(point p);

    void setShadow(bool s);

    // Draw the cube
    void draw() const;

    void draw(color c) const;

    // Rotate the cube
    void rotate(double theta_x, double theta_y, double theta_z);

    // Move the cube
    void move(double delta_x, double delta_y, double delta_z);

    // Resize the cube (growing or shrinking depending on the given bool)
    void resize(double scaleFactor);

    // Returns true if the two cubes are overlapping
    bool isOverlapping(const Cube &c) const;
};


#endif //INC_3D_GRAPHICS_CUBE_H
