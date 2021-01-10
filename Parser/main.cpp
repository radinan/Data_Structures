#include <iostream>
#include <sstream>
#include <queue>

class Expression //WHITE SPACES!!!!!
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
            Statement st (input); //dynamic cast?
            q_st.push(st);
        }
    }
    AVL<Song>& do_expression() //bool or node* or tree&
    {
        while (!q_st.empty()) //all elements
        {
            AVL<Song> pl_tree = q_st.front().do_statement(); //playlist tree
            if (pl_tree.empty()) //if no tree for the criteria => empty
                q_st.pop(); //check next statement
            else
                return pl_tree; //return the playlist
        }
        //return?
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
    AVL<Song>& do_statement() //bool node* or tree&
    {
        AVL<Song> original;//(lib.all_songs);

        while (!q_co.empty()) //all elements
        {
            original = q_co.front().do_command(original); //change the playlist tree
            if (original.empty()) //doesn't find matching songs
                break;
            q_co.pop(); //get next command
        }
        return original; //returns either empty or playlist tree
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
        //perfect case with valid input
        std::string one, two, three; //allowing further validation inside this func
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
        
        //validation?
        opt = three;
    }
    AVL<Song>& do_command(AVL<Song>& original) //return type???
    {
        switch (type) //depending on the type and operator calling diff funcs
        {
        case Type::rating:
            switch (op)
            {
            case Op::bigger: //rating > [opt]
                Song::priority = Priority::rating;
                AVL<Song> prior(original);
                //prior.FUNC
                return prior;
            }
        case Type::genre:
            switch (op)
            {
            case Op::plus:
                Song::priority = Priority::genre;
                AVL<Song> prior(original);
                //prior.FUNC
                return prior;
            case Op::minus:
                Song::priority = Priority::genre;
                AVL<Song> prior(original);
                //prior.FUNC
                return prior;
            case Op::only:
                Song::priority = Priority::genre;
                AVL<Song> prior(original);
                //prior.FUNC
                return prior;
            }
        case Type::year:
            switch (op)
            {
            case Op::equals:
                Song::priority = Priority::year;
                AVL<Song> prior(original);
                //prior.FUNC
                return prior;
            case Op::bigger:
                Song::priority = Priority::year;
                AVL<Song> prior(original);
                //prior.FUNC
                return prior;
            case Op::smaller:
                Song::priority = Priority::year;
                AVL<Song> prior(original);
                //prior.FUNC
                return prior;
            }
        }
    }
};

/* bool is_white_space(char c)
 {
     return c <= 32;
 }

 void clear_white_space()
 {
     while (is_white_space(co.peek()))
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
