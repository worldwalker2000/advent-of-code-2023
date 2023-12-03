#include <cstring>
#include <functional>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define C(x, y) (x + width * y)

struct Point
{
    long x;
    long y;

    inline bool operator<(const Point& p) const { return x < p.x && y < p.y; }
    inline bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

namespace std
{
    template<>
    struct hash<Point>
    {
        inline size_t operator()(const Point& p) const
        {
            // https://stackoverflow.com/a/682485
            return (p.x * 0x1f1f1f1f) ^ p.y;
        }
    };
}

int main()
{
    // std::ifstream file("sample.txt");
    std::ifstream file("input.txt");
    int width, height;

    std::vector<std::string> lines;

    std::string buf;
    while (std::getline(file, buf))
        lines.push_back(buf);

    width = lines[0].length();
    height = lines.size();

    char* grid = new char[width*height];
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            grid[C(i, j)] = lines[j][i];

    // part 1
    if (false)
    {
        Point dirs[] = {
            { -1, -1 },
            { 0, -1 },
            { 1, -1 },
            { -1, 0 },
            { 0, 0 },
            { 1, 0 },
            { -1, 1 },
            { 0, 1 },
            { 1, 1 },
        };

        char buf[256];
        int k = 0;
        bool valid = false;

        unsigned long sum = 0;

        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (isdigit(grid[C(i, j)]))
                {
                    buf[k++] = grid[C(i, j)], buf[k] = '\0';

                    for (int d = 0; d < sizeof(dirs) / sizeof(Point); d++)
                    {
                        int ii = i + dirs[d].x, jj = j + dirs[d].y;
                        if (ii < 0 || ii >= width || jj < 0 || jj >= height) continue;
                        char c = grid[C(ii, jj)];
                        if (ispunct(c) && c != '.') valid = true;
                    }
                }
                else
                {
                    if (valid) sum += atoi(buf);
                    valid = false;
                    k = 0;
                    memset(buf, 0, 256);
                }
            }

            if (valid) sum += atoi(buf);
            valid = false;
            k = 0;
            memset(buf, 0, 256);
        }

        std::cout << sum << std::endl;
    }

    // part 2
    {
        Point dirs[] = {
            { -1, -1 },
            { 0, -1 },
            { 1, -1 },
            { -1, 0 },
            { 0, 0 },
            { 1, 0 },
            { -1, 1 },
            { 0, 1 },
            { 1, 1 },
        };

        std::unordered_map<unsigned long, std::unordered_set<Point>> map;

        char buf[256];
        int k = 0;
        bool valid = false;
        std::unordered_set<Point> points;

        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (isdigit(grid[C(i, j)]))
                {
                    buf[k++] = grid[C(i, j)], buf[k] = '\0';

                    for (int d = 0; d < sizeof(dirs) / sizeof(Point); d++)
                    {
                        int ii = i + dirs[d].x, jj = j + dirs[d].y;
                        if (ii < 0 || ii >= width || jj < 0 || jj >= height) continue;
                        char c = grid[C(ii, jj)];
                        if (c == '*')
                        {
                            valid = true;
                            points.insert({ ii, jj });
                        }
                    }
                }
                else
                {
                    if (valid)
                    {
                        long l = atol(buf);
                        if (map.count(l)) map[l].insert(points.begin(), points.end());
                        else map.insert(std::make_pair(atol(buf), points));
                    }
                    valid = false;
                    k = 0;
                    memset(buf, 0, 256);
                    points.clear();
                }
            }

            if (valid)
            {
                long l = atol(buf);
                if (map.count(l)) map[l].insert(points.begin(), points.end());
                else map.insert(std::make_pair(atol(buf), points));
            }
            valid = false;
            k = 0;
            memset(buf, 0, 256);
            points.clear();
        }

        std::unordered_set<Point> used;
        unsigned long sum = 0;

        for (const auto& [id1, points1] : map)
        {
            /*
            std::cout << std::setw(4) << id1 << ": ";
            for (const Point& point : points1)
                std::cout << "(" << point.x << " " << point.y << "), ";
            std::cout << std::endl;
            */
            for (const auto& [id2, points2] : map)
            {
                if (id1 == id2) continue;

                for (const Point& p1 : points1)
                    for (const Point& p2 : points2)
                        if (p1 == p2 && !used.count(p1))
                        {
                            sum += id1 * id2;
                            used.insert(p1);
                        }
            }
        }

        std::cout << sum << std::endl;
    }

    delete[] grid;

    return 0;
}
