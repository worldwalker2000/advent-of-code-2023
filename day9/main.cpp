#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <optional>

int main()
{
    // std::fstream file("sample.txt");
    std::fstream file("input.txt");

    std::vector<std::vector<long>> seqs;

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<long> seq;

        std::stringstream ss(line);

        while (!ss.eof())
        {
            long val;
            ss >> val;
            seq.push_back(val);
        }

        seqs.push_back(seq);
    }

    // part 1
    if (false)
    {
        long sum = 0;
        for (long s = 0; s < seqs.size(); s++)
        {
            std::vector<std::vector<long>> deltass;
            deltass.push_back(seqs[s]);

            auto computeDeltas = [&]() -> bool
            {
                std::optional<long> val;
                bool all = true;
                long n = deltass.size() - 1;
                std::vector<long> deltas;
                for (long i = 1; i < deltass[n].size(); i++)
                {
                    long delta = deltass[n][i] - deltass[n][i-1];
                    if (!val.has_value()) val.emplace(delta);
                    else
                        if (delta != deltas[i-2]) all = false;
                    deltas.push_back(delta);
                }
                deltass.push_back(deltas);

                /*
                for (long delta : deltas)
                    std::cout << delta << ", ";
                std::cout << std::endl;
                */

                return all;
            };

            while (!computeDeltas());

            deltass.back().push_back(deltass.back().back());
            for (long i = deltass.size()-2; i >= 0; i--)
                deltass[i].push_back(deltass[i].back() + deltass[i+1].back());

            sum += deltass.front().back();
        }

        std::cout << sum << std::endl;
    }

    // part 2
    {
        long sum = 0;
        for (long s = 0; s < seqs.size(); s++)
        {
            std::vector<std::vector<long>> deltass;
            deltass.push_back(seqs[s]);

            auto computeDeltas = [&]() -> bool
            {
                std::optional<long> val;
                bool all = true;
                long n = deltass.size() - 1;
                std::vector<long> deltas;
                for (long i = 1; i < deltass[n].size(); i++)
                {
                    long delta = deltass[n][i] - deltass[n][i-1];
                    if (!val.has_value()) val.emplace(delta);
                    else
                        if (delta != deltas[i-2]) all = false;
                    deltas.push_back(delta);
                }
                deltass.push_back(deltas);

                return all;
            };

            while (!computeDeltas());

            deltass.back().insert(deltass.back().begin(), deltass.back().front());
            for (long i = deltass.size()-2; i >= 0; i--)
                deltass[i].insert(deltass[i].begin(), deltass[i].front() - deltass[i+1].front());

            sum += deltass.front().front();
        }

        std::cout << sum << std::endl;
    }

    return 0;
}
