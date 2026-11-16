#include <cmath>
#include <iomanip>
#include <iostream>

struct Point2D {
    double x;
    double y;
};

Point2D transform(Point2D p, double angle_deg, Point2D t) {
    // TODO 1: Convert degrees to radians.
    // TODO 2: Apply counterclockwise rotation and then translation.
    // For now return the input unchanged, so the sample tests will fail.
    (void) angle_deg;
    (void) t;
    return p;
}

int main() {
    Point2D p{}, t{};
    double angle_deg = 0.0;
    std::cout << "Input x y angle_deg tx ty: ";
    if (!(std::cin >> p.x >> p.y >> angle_deg >> t.x >> t.y)) {
        std::cerr << "Invalid input\n";
        return 1;
    }
    const Point2D out = transform(p, angle_deg, t);
    std::cout << std::fixed << std::setprecision(2)
              << "Result: " << out.x << ' ' << out.y << '\n';
}
