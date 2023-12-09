#include <climits>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <fstream>

struct Map
{
    long dst;
    long src;
    long len;
};

int main()
{
    std::fstream file("sample.txt");

    std::vector<long> seeds;

    std::string line;
    std::string temp;

    // parse seeds
    {
        std::getline(file, line);
        std::stringstream ss(line);
        ss >> temp; // seeds:
        while (!ss.eof())
        {
            long seed; ss >> seed;
            seeds.push_back(seed);
        }

        // for (long seed : seeds) std::cout << seed << ", ";
        // std::cout << std::endl;
    }

    std::getline(file, line); // blank line

    std::vector<Map> seedToSoil;
    {
        std::getline(file, line); // word line
        std::getline(file, line); // first map

        while (line.length() > 0)
        {
            long dst, src, len;

            std::stringstream ss(line);
            ss >> dst >> src >> len;
            seedToSoil.push_back({ dst, src, len });

            std::getline(file, line); // next map
        }

    }

    std::vector<Map> soilToFertilizer;
    {
        std::getline(file, line); // word line
        std::getline(file, line); // first map

        while (line.length() > 0)
        {
            long dst, src, len;

            std::stringstream ss(line);
            ss >> dst >> src >> len;
            soilToFertilizer.push_back({ dst, src, len });

            std::getline(file, line); // next map
        }

    }

    std::vector<Map> fertilizerToWater;
    {
        std::getline(file, line); // word line
        std::getline(file, line); // first map

        while (line.length() > 0)
        {
            long dst, src, len;

            std::stringstream ss(line);
            ss >> dst >> src >> len;
            fertilizerToWater.push_back({ dst, src, len });

            std::getline(file, line); // next map
        }

    }

    std::vector<Map> waterToLight;
    {
        std::getline(file, line); // word line
        std::getline(file, line); // first map

        while (line.length() > 0)
        {
            long dst, src, len;

            std::stringstream ss(line);
            ss >> dst >> src >> len;
            waterToLight.push_back({ dst, src, len });

            std::getline(file, line); // next map
        }

    }

    std::vector<Map> lightToTemperature;
    {
        std::getline(file, line); // word line
        std::getline(file, line); // first map

        while (line.length() > 0)
        {
            long dst, src, len;

            std::stringstream ss(line);
            ss >> dst >> src >> len;
            lightToTemperature.push_back({ dst, src, len });

            std::getline(file, line); // next map
        }

    }

    std::vector<Map> temperatureToHumidity;
    {
        std::getline(file, line); // word line
        std::getline(file, line); // first map

        while (line.length() > 0)
        {
            long dst, src, len;

            std::stringstream ss(line);
            ss >> dst >> src >> len;
            temperatureToHumidity.push_back({ dst, src, len });

            std::getline(file, line); // next map
        }

    }

    std::vector<Map> humidityToLocation;
    {
        std::getline(file, line); // word line
        std::getline(file, line); // first map

        while (line.length() > 0)
        {
            long dst, src, len;

            std::stringstream ss(line);
            ss >> dst >> src >> len;
            humidityToLocation.push_back({ dst, src, len });

            std::getline(file, line); // next map
        }

    }

    // part 1
    if (false)
    {
        auto ApplyMap = [](long value, const Map& map, long& mapped) -> bool
        {
            if (!(value >= map.src && value < map.src+map.len)) return false;
            mapped = map.dst+value-map.src;
            // std::cout << "mapping " << value << " -> " << mapped << std::endl;
            return true;
        };

        long min = LONG_MAX;

        // for (const Map& map : fertilizerToWater) std::cout << map.dst << " " << map.src << " " << map.len << std::endl;
        // exit(1);

        for (long seed : seeds)
        {
            long result = seed;

            // std::cout << result << std::endl;
            for (const Map& map : seedToSoil) if (ApplyMap(result, map, result)) break;
            // std::cout << result << std::endl;
            for (const Map& map : soilToFertilizer) if (ApplyMap(result, map, result)) break;
            // std::cout << result << std::endl;
            for (const Map& map : fertilizerToWater) if (ApplyMap(result, map, result)) break;
            // std::cout << result << std::endl;
            for (const Map& map : waterToLight) if (ApplyMap(result, map, result)) break;
            // std::cout << result << std::endl;
            for (const Map& map : lightToTemperature) if (ApplyMap(result, map, result)) break;
            // std::cout << result << std::endl;
            for (const Map& map : temperatureToHumidity) if (ApplyMap(result, map, result)) break;
            // std::cout << result << std::endl;
            for (const Map& map : humidityToLocation) if (ApplyMap(result, map, result)) break;
            // std::cout << result << std::endl;

            if (result < min) min = result;
        }

        std::cout << min << std::endl;
    }

    // part 2
    {
        auto ApplyMap = [](long value, const Map& map, long& mapped) -> bool
        {
            if (!(value >= map.src && value < map.src+map.len)) return false;
            mapped = map.dst+value-map.src;
            std::cout << "mapping " << value << " -> " << mapped << std::endl;
            return true;
        };

        long min = LONG_MAX;

        // for (const Map& map : fertilizerToWater) std::cout << map.dst << " " << map.src << " " << map.len << std::endl;
        // exit(1);

        for (long i = 0; i < seeds.size(); i+=2)
        // for (long i = 0; i < seeds.size(); i++)
        {
            // for (long seed = seeds[i]; seed < seeds[i] + seeds[i+1]; seed++)
            {
                // long result = seed;
                long result = seeds[i];

                for (const Map& map : seedToSoil) if (ApplyMap(result, map, result)) break;
                // std::cout << result << std::endl;
                for (const Map& map : soilToFertilizer) if (ApplyMap(result, map, result)) break;
                // std::cout << result << std::endl;
                for (const Map& map : fertilizerToWater) if (ApplyMap(result, map, result)) break;
                // std::cout << result << std::endl;
                for (const Map& map : waterToLight) if (ApplyMap(result, map, result)) break;
                // std::cout << result << std::endl;
                for (const Map& map : lightToTemperature) if (ApplyMap(result, map, result)) break;
                // std::cout << result << std::endl;
                for (const Map& map : temperatureToHumidity) if (ApplyMap(result, map, result)) break;
                // std::cout << result << std::endl;
                for (const Map& map : humidityToLocation) if (ApplyMap(result, map, result)) break;
                // std::cout << result << std::endl;

                // if (result < min) min = result;
                std::cout << seeds[i] << " -> " << result << std::endl;
            }
        }

        // std::cout << min << std::endl;
    }

    return 0;
}
