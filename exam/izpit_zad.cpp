#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <unordered_set>
#include <sstream>
#include <unordered_map>
#include <map>

//2 zad
class WordTree
{
private:
    struct WordNode
    {
        std::string data;
        std::vector<WordNode*> children;
        WordNode* parent;

        WordNode(const std::string& _data, WordNode* _parent) : data(_data), parent(_parent) {}
    };
    WordNode* root;
public:
    //a
    void read(std::istream& in)
    {
        std::string treeStr;
        std::getline(in, treeStr);
        std::stringstream ss(treeStr);

        if (ss.peek() == 'E') //Empty => empty tree
        {
            root = nullptr;
        }
        else //tree is not empty
        {
            root = read_helper(ss, nullptr);
        }
    }
    WordNode* read_helper(std::stringstream& in, WordNode* root)
    {
        std::string node;
        in >> node; // "Node"

        std::string word;
        in >> word;

        unsigned int size;
        in >> size; // 0 <= K <= 5

        WordNode* childNode = new WordNode(word, root);
        for (unsigned int i = 0; i < size; ++i)
        {
            childNode->children.push_back(read_helper(in, childNode));
        }

        return childNode;
    }

    int height()
    {
        return height_helper(root);
    }
    int height_helper(WordNode* root)
    {
        if (root == nullptr)
            return -1;

        int max = -1;
        for (int i = 0; i < root->children.size(); ++i)
        {
            int h = height_helper(root->children[i]);
            if (h > max)
                max = h;
        }

        return 1 + max;
    }
    //b
    void print()
    {
        std::stack<WordNode*> s;
        if (root != nullptr)
        {
            s.push(root);
            print_helper(s, root);

            while (!s.empty()) //...
            {
                std::cout << s.top()->data << " ";
                s.pop();
            }
        }
    }
    void print_helper(std::stack<WordNode*>& s, WordNode* root)
    {
        if (root == nullptr)
            return;

        for (auto i : root->children)
        {
            s.push(i);
        }
        for (auto i : root->children)
        {
            print_helper(s, i);
        }
    }
    //v
    void best_level()
    {
        std::vector<std::vector<WordNode*>> lvls; //0 position = 0 lvl
        //lvls[i] = all nodes from lvl i

        int h = height(); //max lvl
        if (h < 0)
            return;

        for (int i = 0; i <= h; ++i)
        {
            std::vector<WordNode*> empt;
            lvls.push_back(empt);
        }

        best_level_helper(root, 0, lvls);

        if (!lvls.empty())
        {
            int max_s = 0;
            std::vector<WordNode*> max;

            for (auto it : lvls)
            {
                if (it.size() > max_s)
                {
                    max = it;
                    max_s = it.size();
                }
            }

            for (auto it : max)
            {
                std::cout << it->data << " ";
            }
        }

    }
    void best_level_helper(WordNode* root, int lvl, std::vector<std::vector<WordNode*>>& vec)
    {
        if (root == nullptr)
            return; 

        vec[lvl].push_back(root);
        for (auto i : root->children)
        {
            best_level_helper(i, lvl + 1, vec);
        }
    }
};

//3 zad
//a
void change(std::string& str)
{
    for(int i = 0; str[i] != '\0' ; ++i)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] - ('A' - 'a');
        else if (str[i] < 'a' || str[i] > 'z')
            str[i] = ' ';
    }
}
void parse(std::string& str, std::unordered_set<std::string>& s)
{
    std::stringstream ss(str);
    while (std::getline(ss, str, ' '))
    {
        s.insert(str);
    }
}
void common_words(std::string& t1, std::string& t2)
{
    std::unordered_set<std::string> s1;
    std::unordered_set<std::string> s2;

    change(t1);
    change(t2);

    parse(t1, s1);
    parse(t2, s2);

    for (auto& i : s1)
    {
        if (s2.count(i) > 0)
            std::cout << i << " ";
    }
}
//b
struct Graph
{
    std::unordered_map <std::string, std::map<std::string, int>> verteces;

    void addEdge(std::string& v1, std::string& v2)
    {
        if (verteces.count(v1) == 0 && verteces.count(v2) == 0) 
        {
            verteces[v1];
            verteces[v2];
            verteces[v1][v2] = 1;
            verteces[v2][v1] = 1;
        }
        else if (verteces.count(v1) == 0)
        {
            verteces[v2][v1] = 1;
            verteces[v1][v2] = 1; //check
        }
        else if (verteces.count(v2) == 0)
        {
            verteces[v1][v2] = 1;
            verteces[v2][v1] = 1; //check
        }
        else
        {
            verteces[v1][v2]++;
            verteces[v2][v1]++;
        }
    }
};
void parse(std::string& str, std::vector<std::string>& v)
{
    std::stringstream ss(str);
    while (std::getline(ss, str, ' '))
    {
        if (str != "")
            v.push_back(str);
    }
}
void max_pair_words(std::string& t)
{
    std::vector<std::string> v;

    change(t);
    parse(t, v);
    Graph g;

    for (int i = 0; i < v.size() - 1; ++i)
    {
        g.addEdge(v[i], v[i + 1]);
    }

    int max_size = 0;
    std::pair<std::string, std::string> max_pair;

    for (auto& i : g.verteces)
    {
        for (auto& j : i.second)
        {
            if (j.second > max_size)
            {
                max_size = j.second;
                max_pair = std::make_pair(i.first, j.first);
            }
        }
    }

    std::cout << max_size << " times: " << max_pair.first << ", " << max_pair.second << std::endl;
}
//v
void helper(std::string& s, std::vector <std::string>& container, std::unordered_map<std::string, std::vector<int>>& u)
{
    change(s);

    parse(s, container);

    for (int i = 0; i < container.size(); ++i)
    {
        u[container[i]].push_back(i);
    }
}
bool substitution(std::string& s1, std::string& s2)
{
    std::unordered_map<std::string, std::vector<int>> u1; //word , positions
    std::unordered_map<std::string, std::vector<int>> u2;

    std::vector <std::string> container1;
    std::vector <std::string> container2;
    helper(s1, container1, u1);
    helper(s2, container2, u2);

    if (container1.size() != container2.size())
        return false;

    for (int i = 0; i < container1.size(); ++i)
    {
        if (u1[container1[i]] != u2[container2[i]])
            return false;
    }
    return true;
}


int main()
{
    WordTree tr;
    tr.read(std::cin);
    tr.print();
    std::cout << std::endl;
    tr.best_level();
    //Node king 3 Node are 1 Node you 0 Node you 0 Node glad 2 Node are 0 Node king 0

    std::cout << std::endl;
    std::string t1 = "What an easy exam today, what an opportunity!", t2 = "What a difficult exam today, I give up!";
    //std::getline(std::cin, t1);
    //std::getline(std::cin, t2);
    common_words(t1, t2);

    std::cout << std::endl;
    std::string t = "In computing, a hash table (hash map) is a data structure that implements an associative array abstract data type, a structure that can map keys to values. A hash table uses a hash function to compute an index, also called a hash code, into an array of buckets or slots, from which the desired value can be found.";
    max_pair_words(t);

    std::string k1 = "The brown fox jumps over the brown dog",
                k2 = "What an easy exam today, what an opportunity!",
                k3 = "What a difficult exam today, I give up!";
    std::cout << substitution(k1, k2);


}

