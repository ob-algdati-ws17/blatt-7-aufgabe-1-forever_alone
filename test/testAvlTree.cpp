#include "testAvlTree.h"
#include <memory>

using namespace std;

// empty tree

TEST(AvlTreeTest, Test_EmptyTree) {

    string test = "first test";

    EXPECT_TRUE(test == "first test");
}


TEST(AvlTreeTest, Empty_Tree) {
    AvlTree b;
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

// insert and search

TEST(AvlTreeTest, Insert_Five_Nodes) {
    AvlTree b;
    EXPECT_FALSE(b.search(3));

    b.insert(3);
    b.insert(2);
    b.insert(5);
    b.insert(4);
    b.insert(0);

    EXPECT_TRUE(b.search(3));
    EXPECT_TRUE(b.search(5));
    EXPECT_TRUE(b.search(0));
    EXPECT_FALSE(b.search(7));
    EXPECT_EQ(0, b.getRootBalance());

    EXPECT_THAT(*b.preorder(), testing::ElementsAre(3,2,0,5,4));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(0,2,3,4,5));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(0,2,4,5,3));
}


TEST(AvlTreeTest, One_Node) {
    AvlTree b;
    b.insert(12213);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123));
    EXPECT_FALSE(b.search(-123));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(12213));
}

TEST(AvlTreeTest, Two_Nodes) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 12213));
}

TEST(AvlTreeTest, Three_Nodes) {
    AvlTree b;
    b.insert(2);
    b.insert(1);
    b.insert(3);
    EXPECT_TRUE(b.search(2));
    EXPECT_TRUE(b.search(3));
    EXPECT_TRUE(b.search(1));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(1, 3, 2));
}

TEST(AvlTreeTest, RotateRight_3_Nodes) {
    AvlTree b;
    b.insert(5);
    b.insert(4);
    b.insert(3);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(4, 3, 5));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(3, 4, 5));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(3, 5, 4));
}

TEST(AvlTreeTest, RotateRight_6_Nodes) {
    AvlTree b;
    b.insert(5);
    b.insert(10);
    b.insert(3);
    b.insert(1);
    b.insert(4);
    b.insert(2);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(3, 1, 2, 5,4,10));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(1, 2, 3,4,5,10));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(2, 1, 4,10,5,3));
}
