#include <iostream>
#include <sstream>
#include <queue>

int main()
{
//testing the usage of stringstream
    std::queue<std::string> aa;
    std::string input;
    std::getline(std::cin, input);

    std::stringstream ss(input);

    while (std::getline(ss, input, delimeter)) //splits the string when sees '|' (works for ||)
    {
        aa.push(input); //adds splitted elements to the queue
    }
    while (!aa.empty())
    {
        std::cout << aa.front(); // << " ";
        aa.pop();
    }
    
return 0;
}
