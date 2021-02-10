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

int main()
{
    doctest::Context().run();
}

