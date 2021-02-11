#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "doctest.h"
#include "BinTree.cpp"


TEST_CASE("insert, get")
{
    BinTree<int> tr;
    tr.insert(1, ""); 
    CHECK(tr.get("") == 1);
    tr.insert(2, "L");
    CHECK(tr.get("L") == 2);
    tr.insert(3, "R");
    CHECK(tr.get("R") == 3);
    tr.insert(4, "LL");
    CHECK(tr.get("LL") == 4);
    tr.insert(5, "LR");
    CHECK(tr.get("LR") == 5);
}
TEST_CASE("[] ")
{
    BinTree<int> tr;
    tr.insert(1, "");
    tr.insert(2, "L");
    tr.insert(3, "R");
    tr.insert(4, "LL");
    tr.insert(5, "LR");
    tr[""] = 10;
    tr["L"] = 20;
    tr["R"] = 30;
    tr["LL"] = 40;
    tr["LR"] = 50;
    CHECK(tr[""] == 10);
    CHECK(tr["L"] == 20);
    CHECK(tr["R"] == 30);
    CHECK(tr["LL"] == 40);
    CHECK(tr["LR"] == 50);
}
TEST_CASE("isMember")
{
    BinTree<int> tr;
    tr.insert(1, "");
    tr.insert(2, "L");
    tr.insert(3, "R");
    tr.insert(4, "LL");
    tr.insert(5, "LR");

    CHECK(tr.isMember(1));
    CHECK(tr.isMember(2));
    CHECK(tr.isMember(3));
    CHECK(tr.isMember(4));
    CHECK(tr.isMember(5));
    CHECK(!tr.isMember(100));

}
TEST_CASE("sum")
{
    BinTree<int> tr;
    CHECK(tr.sum() == 0);
    tr.insert(1, "");
    CHECK(tr.sum() == 1);
    tr.insert(2, "L");
    CHECK(tr.sum() == 3);
    tr.insert(3, "R");
    CHECK(tr.sum() == 6);
    tr.insert(4, "LL");
    CHECK(tr.sum() == 10);
    tr.insert(5, "LR");
    CHECK(tr.sum() == 15);
}
TEST_CASE("count")
{
    BinTree<int> tr;
    CHECK(tr.count() == 0);
    tr.insert(1, "");
    CHECK(tr.count() == 1);
    tr.insert(2, "L");   
    CHECK(tr.count() == 2);
    tr.insert(3, "R");
    CHECK(tr.count() == 3);
    tr.insert(4, "LL");
    CHECK(tr.count() == 4);
    tr.insert(5, "LR");
    CHECK(tr.count() == 5);
}
TEST_CASE("countEvens")
{
    size_t countE = 0;
    BinTree<int> tr;

    countE = tr.countEvens();
    CHECK(countE == 0);

    tr.insert(1, "");
    countE = tr.countEvens();
    CHECK(countE == 0);

    tr.insert(2, "L");
    countE = tr.countEvens();
    CHECK(countE == 1);

    tr.insert(3, "R");
    countE = tr.countEvens();
    CHECK(countE == 1);

    tr.insert(4, "LL");
    countE = tr.countEvens();
    CHECK(countE == 2);
}
TEST_CASE("searchCount")
{
    BinTree<int> tr;
    int num = tr.searchCount([](const int& el) { return el % 2 == 0; });
    CHECK(num == 0);
    tr.insert(2, "");
    num = tr.searchCount([](const int& el) { return el % 2 == 0; });
    CHECK(num == 1);
    tr.insert(1, "L");
    tr.insert(6, "R");
    num = tr.searchCount([](const int& el) { return el % 2 == 0; });
    CHECK(num == 2);


}
TEST_CASE("height")
{
    BinTree<int> tr;
    CHECK(tr.height() == -1);
    tr.insert(1, "");
    CHECK(tr.height() == 0);
    tr.insert(2, "L");
    tr.insert(3, "R");
    CHECK(tr.height() == 1);
    tr.insert(4, "LR");
    CHECK(tr.height() == 2);
}
TEST_CASE("countLeaves")
{
    BinTree<int> tr;
    CHECK(tr.countLeaves() == 0);
    tr.insert(1, "");
    CHECK(tr.countLeaves() == 1);
    tr.insert(2, "L");
    tr.insert(3, "R");
    tr.insert(4, "LL");
    tr.insert(5, "LR");
    tr.insert(6, "RL");
    tr.insert(7, "RR");
    CHECK(tr.countLeaves() == 4);
}
TEST_CASE("maxLeaf")
{
    BinTree<int> tr;

    tr.insert(1, "");
    int leaf = tr.maxLeaf();
    CHECK(leaf == 1);

    tr.insert(2, "L");
    leaf = tr.maxLeaf();
    CHECK(leaf == 2);

    tr.insert(3, "R");
    leaf = tr.maxLeaf();
    CHECK(leaf == 3);

    tr.insert(4, "LL");
    tr.insert(55, "LR");
    tr.insert(6, "RL");
    tr.insert(7, "RR");

    leaf = tr.maxLeaf();
    CHECK(leaf == 55);
}
TEST_CASE("Scheme - serialize, parse; equal")
{
    BinTree<int> tr;
    tr.insert(10, "");
    tr.insert(5, "L");
    tr.insert(20, "R");
    tr.insert(15, "RL");
    tr.insert(25, "RR");

    std::ofstream out("Scheme.txt");
    tr.serializeTreeScheme(out);
    out.close();

    BinTree<int> tr1;
    std::ifstream in("Scheme.txt");
    tr1.parseTreeScheme(in);
    in.close();

    CHECK(tr1[""] == 10);
    CHECK(tr1["L"] == 5);
    CHECK(tr1["R"] == 20);
    CHECK(tr1["RL"] == 15);
    CHECK(tr1["RR"] == 25);

    bool equality = tr1 == tr;
    CHECK(equality);

    BinTree<int> tr2;
    std::ofstream out1("Scheme2.txt");
    tr2.serializeTreeScheme(out1);
    out1.close();

    BinTree<int> tr3;
    std::ifstream in1("Scheme2.txt");
    tr3.parseTreeScheme(in1);
    in1.close();
    equality = tr2 == tr3;
    CHECK(equality);

    equality = tr1 == tr3;
    CHECK(!equality);
}
TEST_CASE("getNodeLevel")
{
    BinTree<int> e;
    e.insert(10, "");
    e.insert(5, "L");
    e.insert(20, "R");
    e.insert(15, "RL");
    e.insert(25, "RR");
    CHECK(e.getNodeLevel(10) == 0);
    CHECK(e.getNodeLevel(5) == 1);
    CHECK(e.getNodeLevel(20) == 1);
    CHECK(e.getNodeLevel(15) == 2);
    CHECK(e.getNodeLevel(25) == 2);

}
TEST_CASE("Haskell - serialize, parse; equal")
{
    BinTree<int> tr;
    tr.insert(10, "");
    tr.insert(5, "L");
    tr.insert(20, "R");
    tr.insert(15, "RL");
    tr.insert(25, "RR");

    std::ofstream out("haskell.txt");
    tr.serializeTreeHaskell(out);
    out.close();

    BinTree<int> tr1;
    std::ifstream in("haskell.txt");
    tr1.parseTreeHaskell(in);
    in.close();

    CHECK(tr1[""] == 10);
    CHECK(tr1["L"] == 5);
    CHECK(tr1["R"] == 20);
    CHECK(tr1["RL"] == 15);
    CHECK(tr1["RR"] == 25);

    bool equality = tr1 == tr;
    CHECK(equality);

    BinTree<int> tr2;
    std::ofstream out1("haskell2.txt");
    tr2.serializeTreeHaskell(out1);
    out1.close();

    BinTree<int> tr3;
    std::ifstream in1("haskell2.txt");
    tr3.parseTreeHaskell(in1);
    in1.close();
    equality = tr2 == tr3;
    CHECK(equality);

    equality = tr1 == tr3;
    CHECK(!equality);
}
TEST_CASE("listLEaves")
{
    BinTree<int> tree;
    tree.insert(10, "");
    tree.insert(5, "L");
    tree.insert(20, "R");
    tree.insert(1, "LL");
    tree.insert(2, "LR");
    tree.insert(3, "RL");
    tree.insert(4, "RR");    

    
    std::vector<int> vect = tree.listLeaves();
    int counter = 1;
    for (auto& i : vect)
    {
        CHECK(i == counter);
        counter++;
    }
}
TEST_CASE("findTrace")
{
    BinTree<int> t;
    t.insert(10, "");
    t.insert(5, "L");
    t.insert(20, "R");
    t.insert(15, "RL");
    t.insert(25, "RR");
    t.insert(7, "RRL");
    t.insert(8, "RRR");

    std::string trace = t.findTrace(7);
    CHECK(trace == "RRL");

    trace = t.findTrace(100);
    CHECK(trace == "_");

    trace = t.findTrace(5);
    CHECK(trace == "L");

    trace = t.findTrace(15);
    CHECK(trace == "RL");
}
int main()
{
    /*BinTree<int> e;
    e.insert(10, "");
    e.insert(5, "L");
    e.insert(20, "R");
    e.insert(15, "RL");
    e.insert(25, "RR");
    e.serializeTreeHaskell(std::cout);
    //std::cout << e.getNodeLevel(25);*/
    doctest::Context().run();
}

