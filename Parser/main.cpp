#include <iostream>
#include <sstream>
#include <queue>

int main()
{
   // std::queue<std::string> aa;
    std::string input;
    std::getline(std::cin, input);
    //char delimeter('|');
    std::string one;
    std::string two;
    std::string three;

    std::istringstream ss(input); //input only stringstream

    /*while (std::getline(ss, input, delimeter))
    {
        aa.push(input);
    }
    while (!aa.empty())
    {
        std::cout << aa.front(); // << " ";
        aa.pop();
    }*/
    ss >> one;
    ss >> two;
    ss.get(); //white space
    std::getline(ss, three);

    std::cout << one<<"______" << std::endl << two <<"______" << std::endl << three << "______" << std::endl; //checks for whitespaces
    // rating > 8
    
    // rating______
    // >______
    // 8______
    //(tested also for genre + heavy metal)
    
return 0;
}
