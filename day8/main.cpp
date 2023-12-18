#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <unordered_map>

int main()
{
    // std::fstream file("sample.txt");
    std::fstream file("input.txt");

    std::string inst;
    std::getline(file, inst);


    std::string line;
    std::getline(file, line); // empty line

    std::unordered_map<std::string, std::pair<std::string, std::string>> map;

    std::string tmp;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string name;
        ss >> name;

        ss >> tmp;

        std::string preLeft;
        ss >> preLeft;
        std::string left = preLeft.substr(1, 3);

        std::string preRight;
        ss >> preRight;
        std::string right = preRight.substr(0, 3);

        map.insert(std::make_pair(name, std::make_pair(left, right)));
    }

    /*
    for (auto [name, children] : map)
    {
        auto [left, right] = children;

        std::cout << name << " " << left << " <> " << right << std::endl;
    }
    */

    // part 1
    if (false)
    {
        std::string curr = "AAA";

        unsigned long long steps = 0;
        unsigned long long i = 0;
        while (curr != "ZZZ")
        {
            auto [left, right] = map[curr];
            if (inst[i] == 'L') curr = left;
            if (inst[i] == 'R') curr = right;

            i = (i + 1) % inst.length();

            steps++;
        }

        std::cout << steps << std::endl;
    }

    {
        /*
14257
18023
11567
15871
16409

21251
         */
        std::vector<std::string> currs;

        for (auto [name, _] : map) if (name[2] == 'A') currs.push_back(name);

        std::vector<unsigned long long> ns;
        for (const std::string c : currs)
        {
            std::string curr = c;

            unsigned long long steps = 0;
            unsigned long long i = 0;
            while (curr[2] != 'Z')
            {
                auto [left, right] = map[curr];
                if (inst[i] == 'L') curr = left;
                if (inst[i] == 'R') curr = right;

                i = (i + 1) % inst.length();

                steps++;
            }

            // std::cout << steps << std::endl;
            ns.push_back(steps);
        }

        unsigned long long max = *std::max_element(ns.begin(), ns.end());
        // std::cout << std::endl;
        unsigned long long prod = 1;
        for (unsigned long long n : ns)
        {
            // std::cout << std::endl << n << std::endl;
            prod *= n;
            // std::cout << (double) max / (double) n << std::endl;
        }
        // std::cout << prod << std::endl;
        /*
123456789
  a  a    
 a a a    
        */

        /*
        unsigned long long k = 1;
        while (true)
        {
            bool all = true;
            for (unsigned long long n : ns)
                if (k % n != 0) all = false;

            if (all) break;
            k++;
        }

        std::cout << k << std::endl;
        */

        std::vector<unsigned long long> pos;
        for (auto _ : ns) pos.push_back(0);
        bool over = false;
        auto AllN = [&]() -> bool
        {
            if (!over) return false;
            for (int i = 1; i < pos.size(); i++)
                if (pos[i] != pos[i-1]) return false;
            return true;
        };

        while (!AllN())
        {
            long min = 0;
            for (long i = 0; i < pos.size(); i++)
            {
                if (pos[i] < pos[min]) min = i;
            }
            pos[min] += ns[min];
            over = true;
            // for (auto p : pos) std::cout << p << ", ";
            // std::cout << std::endl;
        }
        std::cout << pos[0] << std::endl;

        exit(0);

        auto All = [&]() -> bool
        {
            for (const std::string& curr : currs)
                if (curr[2] != 'Z') return false;
            return true;
        };

        unsigned long long steps = 0;
        unsigned long long i = 0;
        while (!All())
        {
// #pragma omp parallel for
            for (int j = 0; j < currs.size(); j++)
            {
                auto [left, right] = map[currs[j]];
                if (inst[i] == 'L') currs[j] = left;
                if (inst[i] == 'R') currs[j] = right;
            }

            i = (i + 1) % inst.length();
            if (i == 0 && steps % 10000 == 0)
            {
                std::cout << "cycle " << steps << " ";
                for (const std::string& curr : currs) std::cout << (curr[2] == 'Z'); std::cout  << "\n";
            }


            steps++;
        }

        std::cout << steps << std::endl;
    }

    return 0;
}
