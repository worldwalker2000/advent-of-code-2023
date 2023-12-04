#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <fstream>

struct Card
{
    int id;
    std::vector<int> win;
    std::vector<int> ns;
};

int main()
{
    std::ifstream file("input.txt");

    std::vector<Card> cards;

    std::string buf;
    while (std::getline(file, buf))
    {
        std::stringstream ss(buf);

        std::string tmp;
        ss >> tmp; // Card

        int id;
        ss >> id; // n
        ss >> tmp; // :

        std::vector<int> win;
        while (tmp != "|")
        {
            win.push_back(atoi(tmp.c_str()));
            ss >> tmp;
        }

        std::vector<int> ns;
        while (!ss.eof())
        {
            int i;
            ss >> i;
            ns.push_back(i);
        }

        cards.push_back({ id, win, ns });
    }

    /*
    for (const Card& card : cards)
    {
        std::cout << card.id << ": ";
        for (int w : card.win) std::cout << w << ", ";
        std::cout << " | ";
        for (int n : card.ns) std::cout << n << ", ";
        std::cout << std::endl;
    }
    */

    // part 1
    if (false)
    {
        long sum = 0;

        for (const Card& card : cards)
        {
            long c = 0;
            for (int w : card.win)
                for (int n : card.ns)
                    if (w == n) c++;

            sum += pow(2, c-1);
        }

        std::cout << sum << std::endl;
    }

    // part 2
    {
        std::unordered_map<int, int> nCards;
        for (const Card& card : cards) nCards.insert(std::make_pair(card.id, 1));

        for (const Card& card : cards)
        {
            long c = 0;
            for (int w : card.win)
                for (int n : card.ns)
                    if (w == n) c++;

            for (int k = 0; k < nCards[card.id]; k++)
                for (int i = 0; i < c; i++) nCards[card.id+i+1]++;
        }

        long sum = 0;
        for (auto [id, n] : nCards) sum += n;
        std::cout << sum << std::endl;

    }

    return 0;
}
