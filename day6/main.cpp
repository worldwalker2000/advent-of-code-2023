#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

int main()
{
    std::ifstream file("input.txt");

    std::vector<long> times;
    std::vector<long> distances;

    std::string buf;
    std::string tmp;
    std::getline(file, buf);
    {
        std::stringstream ss(buf);
        ss >> tmp; // label
        while (!ss.eof())
        {
            long time; ss >> time;
            times.push_back(time);
        }
    }

    std::getline(file, buf);
    {
        std::stringstream ss(buf);
        ss >> tmp; // label
        while (!ss.eof())
        {
            long distance; ss >> distance;
            distances.push_back(distance);
        }
    }

    const long N = times.size();

    // for (long i = 0; i < N; i++) std::cout << "(" << times[i] << " " << distances[i] << ")" << std::endl;

    // part 1
    if (false)
    {
        long prod = 1;

        for (long i = 0; i < N; i++)
        {
            // long timeDown = 0;
            // bool over = false;
            // long winners = 0;
            /*
            while (true)
            {
                long d = timeDown * (times[i] - timeDown);
                if (over && d < distances[i]) break;
                if (d > distances[i])
                {
                    winners++;
                    over = true;
                }

                timeDown++;
            }
            */
            long min = std::ceil(0.5*(times[i] - std::sqrt(times[i]*times[i]-4*distances[i])));
            long max = std::floor(0.5*(times[i] + std::sqrt(times[i]*times[i]-4*distances[i])));

            // prod *= winners;
            prod *= max-min+1;
        }

        std::cout << prod << std::endl;
    }

    // part 2
    {
        std::stringstream timeString;
        std::stringstream distString;
        for (long i = 0; i < N; i++)
        {
            timeString << times[i];
            distString << distances[i];
        }

        long time = std::atol(timeString.str().c_str());
        long distance = std::atol(distString.str().c_str());

        long min = std::ceil(0.5*(time - std::sqrt(time*time-4*distance)));
        long max = std::floor(0.5*(time + std::sqrt(time*time-4*distance)));

        std::cout << max-min+1 << std::endl;
    }

    return 0;
}
