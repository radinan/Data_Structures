#include <iostream>
#include <sstream>
#include <queue>

class Expression
{
private:
    std::string input; //user's input
    std::queue<Statement> q_st; //all statements (separated by || )
public:
    Expression(std::string& _input) : input(_input){}
    void parse_expression() //adds to queue
    {
        char delimeter('|');
        std::stringstream ss(input);

        while (std::getline(ss, input, delimeter)) //reads and splits: statement || statement...
        {
            q_st.push(input);
        }
    }
    void do_statements()
    {
        while (!q_st.empty()) //all elements
        {
           // q_st.front().FUNC() -> return 0;
           // q_st.front().FUNC() ->
            q_st.pop();
        }
        //return 1;
    }

};

class Statement
{
private:
    std::string st;
    std::queue<Command> q_co; //all commands (separated by &&)
public:
    Statement(std::string& _st) : st(_st){}
    void parse_statement() //adds to queue
    {
        char delimeter('&');
        std::stringstream ss(st);

        while (std::getline(ss, st, delimeter)) //reads and splits: command && command...
        {
            q_co.push(st);
        }
    }
    void do_commands()
    {
        while (!q_co.empty()) //all elements
        {

        }
    }
};

class Command
{
private:
    std::string co; //think about white spaces

    enum Type { rating, genre, year }; //type
    Type type;
    enum Op {plus = '+', minus = '-', smaller = '<', bigger = '>', equals = '=', only = '!'}; //operator
    Op op;
    std::string opt; //option

public:
    Command(std::string& _co) : co(_co){}
    void parse_command() //think about setters or making it private
    {
        std::string one, two, three;
        std::istringstream ss(co);
        ss >> one; 
        ss >> two;
        ss.get(); //white space
        std::getline(ss, three);
        //think about switch case
        if (one == "rating")
        {
            Command::type = Type::rating;
        }
        else if (one == "genre")
        {
            Command::type = Type::genre;
        }
        else if (one == "year")
        {
            Command::type = Type::year;
        }
        else
        {
            //wrong
        }

        if (two == "+")
        {
            Command::op = Op::plus;
        }
        else if (two == "-")
        {
            Command::op = Op::minus;
        }
        else if(two == "<")
        {
            Command::op = Op::smaller;
        }
        else if(two == ">")
        {
            Command::op = Op::bigger;
        }
        else if(two == "=")
        {
            Command::op = Op::equals;
        }
        else if (two == "!")
        {
            Command::op = Op::only;
        }
        else
        {
            //wrong
        }
 
        opt = three;
    }
    void do_command() //return 
    {
        switch (type)
        {
        case Type::rating:
            switch (op)
            {
            case Op::bigger:
                //AVLTree<Song> rating_bigger(main tree);
                //rating_bigger.FUNC()
            }
        case Type::genre:
            switch (op)
            {
            case Op::plus:
                //AVLTree<Song> add_genre(/*main tree);
                //add_genre.FUNC()
            case Op::minus:
                //AVLTree<Song> remove_genre(/*main tree);
                //add_genre.FUNC()
            case Op::only:
                //AVLTree<Song> fav_genre(/*main tree);
                //add_genre.FUNC()
            }
        case Type::year:
            switch (op)
            {
            case Op::equals:
                //AVLTree<Song> equals_year(/*main tree);
                //equals_year.FUNC()
            case Op::bigger:
                //AVLTree<Song> bigger_year(/*main tree);
                //bigger_year.FUNC()
            case Op::smaller:
                //AVLTree<Song> smaller_year(/*main tree);
                //smaller_year.FUNC()
            }
        }
    }

};

/* bool isWhiteSpace(char c)
 {
     return c <= 32;
 }

 void clearWhiteSpace()
 {
     while (isWhiteSpace(co.peek()))
     {
         in.get();
     }
 }*/

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
