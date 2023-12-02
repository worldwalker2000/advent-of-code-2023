#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Set { Set() { r=g=b=-1; } Set(int r_, int g_, int b_) { r=r_;g=g_;b=b_; } int r, g, b; };

struct Game { int id; std::vector<Set> sets; };

int main()
{
    Set target(12, 13, 14);

    std::fstream file("input.txt");

    std::vector<Game> games;

    std::string line;
    Game game;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string buf;
        ss >> buf; // Game

        int id;
        ss >> id; // id
        game.id = id;

        ss >> buf; // :

        Set set;
        while (!ss.eof())
        {
            int n; ss >> n;

            std::string word; ss >> word;
            char c = word[word.length()-1];
            std::string color;
            if (c == ',' || c == ';') color = word.substr(0, word.length()-1);
            else color = word;

            if (color == "red") set.r = n;
            if (color == "green") set.g = n;
            if (color == "blue") set.b = n;

            if (c != ',') { game.sets.push_back(set); set = Set(); }
        }

        games.push_back(game); game = Game();
    }

    // part 1
    if (false)
    {
        long sum = 0;

        for (const Game& game : games)
        {
            // std::cout << game.id << ": ";

            bool all = true;

            for (const Set& set : game.sets)
            {
                // std::cout << (set.r == -1 ? 0 : set.r) << " " << (set.g == -1 ? 0 : set.g) << " " << (set.b == -1 ? 0 : set.b) << " - ";
                if (set.r > target.r || set.g > target.g || set.b > target.b) all = false;
            }

            if (all) sum += game.id;

            // std::cout << std::endl;
        }

        std::cout << sum << std::endl;
    }

    // part 2
    {
        long sum = 0;

        for (const Game& game : games)
        {
            Set max;
            for (const Set& set : game.sets)
            {
                if (set.r > max.r) max.r = set.r;
                if (set.g > max.g) max.g = set.g;
                if (set.b > max.b) max.b = set.b;
            }
            // std::cout << (max.r == -1 ? 0 : max.r) << " " << (max.g == -1 ? 0 : max.g) << " " << (max.b == -1 ? 0 : max.b) << " - ";

            // long power = (max.r == -1 ? 1 : max.r) * (max.g == -1 ? 1 : max.g) * (max.b == -1 ? 1 : max.b);
            long power = max.r * max.g * max.b;

            sum += power;
        }

        std::cout << sum << std::endl;
    }

    return 0;
}
