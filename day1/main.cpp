#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_map>

int main()
{
    std::ifstream file("input.txt");

    const char* orders[9] = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
    };

    int sum = 0;

    std::string line;
    while (std::getline(file, line))
    {
        int L = line.length();

        char buf[255];

        int a = 0;
        int b = 0;

        {
            int start = 0;
            int k = 0;

            for (int i = 0; start < L && a == 0; i++)
            {
                if (isdigit(line[i]) && k == 0) a = line[i] - '0';

                buf[k++] = line[i]; buf[k] = '\0';

                for (int j = 0; j < 9; j++)
                    if (strcmp(buf, orders[j]) == 0) a = j+1;

                if (k >= 5)
                {
                    start++;
                    i = start-1;
                    k = 0;
                }
            }
        }

        {
            int start = L-1;
            int k = 0;

            for (int i = L-1; start >= 0 && b == 0; i--)
            {
                if (isdigit(line[i]) && k == 0) b = line[i] - '0';

                buf[k+1] = '\0';
                for (int kk = k-1; kk >= 0; kk--)
                {
                    buf[kk+1] = buf[kk];
                }
                buf[0] = line[i];
                k++;

                for (int j = 0; j < 9; j++)
                    if (strcmp(buf, orders[j]) == 0) b = j+1;

                if (k >= 5)
                {
                    start--;
                    i = start+1;
                    k = 0;
                }
            }

            // if (a == 0 || b == 0) std::cout << line << " " << a << " " << b << std::endl;
        }

        sum += a*10+b;
    }

    std::cout << sum << std::endl;

    return 0;
}
