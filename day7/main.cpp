#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <array>

enum HandType
{
    FIVE = 7,
    FOUR = 6,
    FULL = 5,
    THREE = 4,
    TWO = 3,
    ONE = 2,
    HIGH = 1,
    MIN = 0,
};

struct Hand
{
    std::array<char, 5> cards;
    long bid;
};

int main()
{
    std::fstream file("input.txt");

    std::string line;
    std::string tmp;

    std::vector<Hand> hands;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        Hand hand;

        char cards[5];
        ss >> cards;
        ss >> hand.bid;

        for (long i = 0; i < 5; i++) hand.cards[i] = cards[i];

        hands.push_back(hand);
    }

    /*
    for (const Hand& hand : hands)
    {
        for (int i = 0; i < 5; i++) std::cout << hand.cards[i] << ", ";
        std::cout << ": " << hand.bid << std::endl;
    }
    */

    // part 1
    if (false)
    {
        std::unordered_map<char, long> cardStrength = {
            { '2', 2 },
            { '3', 3 },
            { '4', 4 },
            { '5', 5 },
            { '6', 6 },
            { '7', 7 },
            { '8', 8 },
            { '9', 9 },

            { 'T', 10 },
            { 'J', 11 },
            { 'Q', 12 },
            { 'K', 13 },
            { 'A', 14 },
        };

        auto GetHandType = [](const std::array<char, 5>& cards) -> HandType
        {
            std::unordered_map<char, long> counts;
            std::unordered_map<long, long> countCounts;
            for (long i = 0; i < 5; i++)
            {
                if (counts.count(cards[i])) counts[cards[i]] += 1;
                else counts.insert({ cards[i], 1 });
            }

            for (auto [_, c] : counts)
            {
                if (countCounts.count(c)) countCounts[c] += 1;
                else countCounts.insert({ c, 1 });
            }

            /*
            std::cout << std::endl;
            for (auto [c, cnt] : counts) std::cout << c << " -> " << cnt << std::endl;
            std::cout << std::endl;
            for (auto [cnt, cnt2] : countCounts) std::cout << cnt << " -> " << cnt2 << std::endl;
            */

            if (counts.size() == 1) return FIVE;
            if (counts.size() == 2 && countCounts[1]) return FOUR;
            if (counts.size() == 2 && countCounts[2] && countCounts[3]) return FULL;
            if (counts.size() == 3 && countCounts[3]) return THREE;
            if (counts.size() == 3 && countCounts[2] == 2) return TWO;
            if (counts.size() == 4 && countCounts[1] == 3) return ONE;
            if (counts.size() == 5) return HIGH;

            assert(false);
        };

        auto CompareHand = [&](const Hand& a, const Hand& b) -> bool
        {
            HandType aType = GetHandType(a.cards);
            HandType bType = GetHandType(b.cards);

            // if (aType != bType) return aType < bType ? -1 : 1;
            if (aType != bType) return aType < bType;

            long i;
            for (i = 0; i < 5; i++)
                if (a.cards[i] != b.cards[i]) break;

            long aStrength = cardStrength[a.cards[i]];
            long bStrength = cardStrength[b.cards[i]];

            // return aStrength < bStrength ? -1 : 1;
            return aStrength < bStrength;
        };

        std::sort(hands.begin(), hands.end(), CompareHand);

        long sum = 0;
        for (long i = 0; i < hands.size(); i++)
        {
            // for (int j = 0; j < 5; j++) std::cout << hands[i].cards[j];
            // std::cout << " " << GetHandType(hands[i].cards) << std::endl;
            // std::cout << hand;
            sum += hands[i].bid * (i+1);
        }

        std::cout << sum << std::endl;
    }

    // part 2
    {
        std::unordered_map<char, long> cardStrength = {
            { '2', 2 },
            { '3', 3 },
            { '4', 4 },
            { '5', 5 },
            { '6', 6 },
            { '7', 7 },
            { '8', 8 },
            { '9', 9 },

            { 'T', 10 },
            // { 'J', 11 },
            { 'J', 1 },
            { 'Q', 12 },
            { 'K', 13 },
            { 'A', 14 },
        };

        auto GetHandType = [](const std::array<char, 5>& cards) -> HandType
        {
            std::unordered_map<char, long> counts;
            std::unordered_map<long, long> countCounts;
            for (long i = 0; i < 5; i++)
            {
                if (counts.count(cards[i])) counts[cards[i]] += 1;
                else counts.insert({ cards[i], 1 });
            }

            for (auto [_, c] : counts)
            {
                if (countCounts.count(c)) countCounts[c] += 1;
                else countCounts.insert({ c, 1 });
            }

            /*
            std::cout << std::endl;
            for (auto [c, cnt] : counts) std::cout << c << " -> " << cnt << std::endl;
            std::cout << std::endl;
            for (auto [cnt, cnt2] : countCounts) std::cout << cnt << " -> " << cnt2 << std::endl;
            */

            if (counts.size() == 1) return FIVE;
            if (counts.size() == 2 && countCounts[1]) return FOUR;
            if (counts.size() == 2 && countCounts[2] && countCounts[3]) return FULL;
            if (counts.size() == 3 && countCounts[3]) return THREE;
            if (counts.size() == 3 && countCounts[2] == 2) return TWO;
            if (counts.size() == 4 && countCounts[1] == 3) return ONE;
            if (counts.size() == 5) return HIGH;

            assert(false);
        };

        auto GetHandTypeWithJoker = [&](const std::array<char, 5>& cards) -> HandType
        {
            std::vector<long> Js;
            std::unordered_set<char> have;
            for (long i = 0; i < 5; i++)
            {
                if (cards[i] == 'J') Js.push_back(i);
                have.insert(cards[i]);
            }

            HandType best = MIN;

            for (char c : have)
            {
                std::array<char, 5> copy = cards;
                for (long i = 0; i < 5; i++)
                    if (cards[i] == 'J') copy[i] = c;
                HandType r = GetHandType(copy);

                if (r > best) best = r;
            }

            for (auto [c, _] : cardStrength)
                if (!have.count(c))
                {
                    std::array<char, 5> copy = cards;
                    for (long i = 0; i < 5; i++)
                        if (cards[i] == 'J') copy[i] = c;
                    HandType r = GetHandType(copy);

                    if (r > best) best = r;

                    break;
                }

            return best;
        };

        auto CompareHand = [&](const Hand& a, const Hand& b) -> bool
        {
            HandType aType = GetHandTypeWithJoker(a.cards);
            HandType bType = GetHandTypeWithJoker(b.cards);

            // if (aType != bType) return aType < bType ? -1 : 1;
            if (aType != bType) return aType < bType;

            long i;
            for (i = 0; i < 5; i++)
                if (a.cards[i] != b.cards[i]) break;

            long aStrength = cardStrength[a.cards[i]];
            long bStrength = cardStrength[b.cards[i]];

            // return aStrength < bStrength ? -1 : 1;
            return aStrength < bStrength;
        };

        std::sort(hands.begin(), hands.end(), CompareHand);

        long sum = 0;
        for (long i = 0; i < hands.size(); i++)
        {
            // for (int j = 0; j < 5; j++) std::cout << hands[i].cards[j];
            // std::cout << " " << GetHandType(hands[i].cards) << std::endl;
            // std::cout << hand;
            sum += hands[i].bid * (i+1);
        }

        std::cout << sum << std::endl;

    }


    return 0;
}
