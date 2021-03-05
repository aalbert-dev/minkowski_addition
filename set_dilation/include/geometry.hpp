#include <vector>
#include <math.h>

#define PI M_PI

#define SQUARED(x) ((x) * (x))

using namespace std;

struct Point
{
    float x, y, z;
    Point() : x(0), y(0){};
    Point(float x, float y) : x(x), y(y), z(0){};
    Point(float x, float y, float z) : x(x), y(y), z(z){};
    bool operator==(const Point &other) { return x == other.x && y == other.y && z == other.z; }
    Point operator+(const Point &other) { return Point(x + other.x, y + other.y, z + other.z); }
    Point operator-(const Point &other) { return Point(x - other.x, y - other.y, z - other.z); }
};

Point rotate(Point a, float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    float x = a.x * c - a.y * s;
    float y = a.x * s - a.y * c;
    return Point(x, y);
}

Point rotate_about(Point a, Point b, float angle)
{
    return rotate(b - a, angle) + a;
}

vector<Point> rotate_vector(vector<Point> pts, Point ref, float angle)
{
    vector<Point> new_pts;
    for (int i = 0; i < pts.size(); i++)
    {
        Point cur_point = pts.at(i);
        Point new_point = rotate_about(cur_point, ref, angle);
        new_pts.push_back(new_point);
    }
    return new_pts;
}

float distance(Point a, Point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<Point> interpolate(Point a, Point b, int num_points)
{
    vector<Point> pts;
    float angle = atan((b.y - a.y) / (b.x - a.x));
    float dist = distance(a, b);
    float step = dist / num_points;
    for (int i = 0; i < num_points + 1; i++)
    {
        float x = a.x + step * i * cos(angle);
        float y = a.y + step * i * sin(angle);
        pts.push_back(Point(x, y));
    }
    return pts;
}

vector<Point> interp_lines(vector<Point> pts, int num_points)
{
    vector<Point> interp_pts;
    for (int i = 0; i < pts.size() - 1; i++)
    {
        Point cur_point = pts.at(i);
        Point next_point = pts.at(i + 1);
        vector<Point> new_pts = interpolate(cur_point, next_point, num_points);
        interp_pts.insert(interp_pts.end(), new_pts.begin(), new_pts.end());
    }
    Point cur_point = pts.at(0);
    Point next_point = pts.at(pts.size() - 1);
    vector<Point> new_pts = interpolate(cur_point, next_point, num_points);
    interp_pts.insert(interp_pts.end(), new_pts.begin(), new_pts.end());
    return interp_pts;
}