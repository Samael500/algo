#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <utility>
#include <cmath>

struct Point {
    int x_coord;
    int y_coord;
};

struct Section {
    double x_coord;
    bool begin;
};

typedef std::vector<Point> vector;

inline bool operator<(const Point& first, const Point& last) {
    return (first.x_coord < last.x_coord) || (
        (first.x_coord == last.x_coord) && (first.y_coord < last.y_coord));
}

inline bool operator<(const Section& first, const Section& last) {
    return (first.x_coord < last.x_coord) || (
        (first.x_coord == last.x_coord) && (first.begin > last.begin));
}

double CalcDistance(double center, const Point& target) {
    return (center - target.x_coord) * (
        center - target.x_coord) + (target.y_coord * target.y_coord);
}

size_t FindPoinCoverage(const vector& points, double radius) {
    std::vector<Section> segments;
    for (const auto& point : points) {
        double distance = radius * radius - point.y_coord * point.y_coord;
        if (distance < 0.0) {
            continue;
        }
        segments.push_back(Section{point.x_coord - sqrt(distance), true});
        segments.push_back(Section{point.x_coord + sqrt(distance), false});
    }
    std::sort(segments.begin(), segments.end());
    size_t coverage = 0;
    size_t max_coverage = 0;
    Section s{0.0, false};
    for (const auto& segment : segments) {
        if (segment.begin) {
            ++coverage;
        } else {
            --coverage;
        }
        max_coverage = std::max(coverage, max_coverage);
        s = segment;
    }
    return max_coverage;
}

double SolveTask(size_t min_points, const vector& points) {
    double radius_min = 0;
    double radius_max = sqrt(2 * 1000 * 1000);
    double radius = 0;
    const double eps = 1e-5;

    while ((radius_max - radius_min) > eps) {
        radius = radius_min + (radius_max - radius_min) / 2.0;
        size_t point_cover = FindPoinCoverage(points, radius);
        if (point_cover >= min_points) {
            radius_max = radius;
        } else {
            radius_min = radius;
        }
    }
    return radius;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t min_points, size;
    int min_x, max_x;
    vector points;

    std::cin >> size >> min_points;
    min_x = std::numeric_limits<int>::max();
    max_x = std::numeric_limits<int>::min();
    for (size_t i = 0; i < size; ++i) {
        Point point;
        std::cin >> point.x_coord >> point.y_coord;
        min_x = std::min(min_x, point.x_coord);
        max_x = std::max(max_x, point.x_coord);
        points.push_back(point);
    }

    double distance = SolveTask(min_points, points);
    std::cout << std::fixed << std::setprecision(6) << distance;
    return 0;
}
