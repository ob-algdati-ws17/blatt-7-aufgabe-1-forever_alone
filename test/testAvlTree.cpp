#include "testAvlTree.h"

using namespace std;

// empty tree

TEST(AvlTreeTest, Empty_Tree) {
    AvlTree b;
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

// insert and search

TEST(AvlTreeTest, Insert_Five_Nodes) {
    AvlTree b;
    b.insert(3);
    b.insert(2);
    b.insert(5);
    b.insert(4);
    b.insert(0);
    EXPECT_TRUE(b.search(3));
    EXPECT_TRUE(b.search(5));
    EXPECT_TRUE(b.search(0));
    EXPECT_FALSE(b.search(7));
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

TEST(AvlTreeTest, RotateRightLeft_6_Nodes) {
    AvlTree b;
    b.insert(100);
    b.insert(50);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(100,50));
    b.insert(150);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(100, 50, 150));
    b.insert(125);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(100, 50, 150, 125));
    b.insert(180);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(100, 50, 150, 125, 180));
    b.insert(130);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(125, 100, 50, 150, 130, 180));

}

TEST(AvlTreeTest, RotateLeft_3_Nodes) {
    AvlTree b;
    b.insert(3);
    b.insert(4);
    b.insert(5);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(4, 3, 5));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(3, 4, 5));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(3, 5, 4));
}

TEST(AvlTreeTest, RotateLeft_6_Nodes) {
    AvlTree b;
    b.insert(12);
    b.insert(25);
    b.insert(10);
    b.insert(30);
    b.insert(15);
    b.insert(28);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(25, 12, 10, 15,30,28));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10, 12, 15,25,28,30));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10, 15, 12,28,30,25));
}

TEST(AvlTreeTest, RotateLeftRigth_6_Nodes) {
    AvlTree b;
    b.insert(50);
    b.insert(25);
    b.insert(75);
    b.insert(10);
    b.insert(40);
    b.insert(30);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(40, 25, 10, 30, 50, 75));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10, 25, 30,40,50,75));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10, 30, 25,75,50,40));
}

// remove root


 TEST(AvlTreeTest, Remove_Lonely_Root) {
    AvlTree b;
    EXPECT_FALSE(b.search(3));
    b.insert(3);
    EXPECT_TRUE(b.search(3));
    EXPECT_FALSE(b.search(2));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(3));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(3));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(3));
    b.remove(3);
    EXPECT_FALSE(b.search(3));
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
    b.insert(3);
    EXPECT_TRUE(b.search(3));
}

// remove leaf

TEST(AvlTreeTest, Remove_Leaf___Rotate_Left) {
    AvlTree b;
    b.insert(5);
    b.insert(3);
    b.insert(8);
    b.insert(7);
    b.insert(2);
    b.insert(10);
    b.insert(9);
    b.insert(12);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(5,3,2,8,7,10,9,12));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(2,3,5,7,8,9,10,12));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(2,3,7,9,12,10,8,5));
    EXPECT_TRUE(b.search(9));
    b.remove(9);
    EXPECT_FALSE(b.search(9));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(5,3,2,8,7,10,12));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(2,3,5,7,8,10,12));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(2,3,7,12,10,8,5));
    EXPECT_TRUE(b.search(7));
    b.remove(7);
    EXPECT_FALSE(b.search(7));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(5,3,2,10,8,12));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(2,3,5,8,10,12));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(2,3,8,12,10,5));
}


TEST(AvlTreeTest, Remove_Leaf___Rotate_Right) {
    AvlTree b;
    b.insert(30);
    b.insert(20);
    b.insert(40);
    b.insert(10);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(30,20,10,40));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,20,30,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10,20,40,30));
    b.remove(40);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(20,10,30));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,20,30));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10,30,20));
}

TEST(AvlTreeTest, Remove_Leaf___Rotate_Right_Left) {
    AvlTree b;
    b.insert(20);
    b.insert(40);
    b.insert(10);
    b.insert(30);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(20,10,40,30));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,20,30,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10,30,40,20));
    b.remove(10);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(30,20,40));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(20,30,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(20,40,30));
}

TEST(AvlTreeTest, Remove_Leaf___Rotate_Left_Right) {
    AvlTree b;
    b.insert(30);
    b.insert(10);
    b.insert(40);
    b.insert(20);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(30,10,20,40));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,20,30,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(20,10,40,30));
    b.remove(40);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(20,10,30));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,20,30));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10,30,20));
}

// remove node with one child - left child

TEST(AvlTreeTest, Remove_Node_With_Left_Child___Without_Rotation) {
    AvlTree b;
    b.insert(30);
    b.insert(20);
    b.insert(40);
    b.insert(10);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(30,20,10,40));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,20,30,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10,20,40,30));
    b.remove(20);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(30,10,40));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,30,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10,40,30));
}

TEST(AvlTreeTest, Remove_Node_With_Left_Child___Rotate_Left) {
    AvlTree b;
    b.insert(20);
    b.insert(30);
    b.insert(10);
    b.insert(40);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(20,10,30,40));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,20,30,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10,40,30,20));
    b.remove(10);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(30,20,40));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(20,30,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(20,40,30));
}

TEST(AvlTreeTest, Remove_Node_With_Left_Child___Rotate_Left_Right) {
    AvlTree b;
    b.insert(30);
    b.insert(10);
    b.insert(40);
    b.insert(20);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(30,10,20,40));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,20,30,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(20,10,40,30));
    b.remove(40);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(20,10,30));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,20,30));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10,30,20));
}

// remove node with one child - right child

TEST(AvlTreeTest, Remove_Node_With_Right_Child___Without_Rotation) {
    AvlTree b;
    b.insert(30);
    b.insert(20);
    b.insert(40);
    b.insert(50);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(30,20,40,50));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(20,30,40,50));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(20,50,40,30));
    b.remove(40);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(30,20,50));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(20,30,50));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(20,50,30));
}

TEST(AvlTreeTest, Remove_Node_With_Right_Child___Rotate_Right) {
    AvlTree b;
    b.insert(20);
    b.insert(30);
    b.insert(10);
    b.insert(0);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(20,10,0,30));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(0,10,20,30));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(0,10,30,20));
    b.remove(30);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(10,0,20));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(0,10,20));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(0,20,10));
}

TEST(AvlTreeTest, Remove_Node_With_Right_Child___Rotate_Right_Left) {
    AvlTree b;
    b.insert(30);
    b.insert(10);
    b.insert(40);
    b.insert(35);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(30,10,40,35));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(10,30,35,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(10,35,40,30));
    b.remove(10);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(35,30,40));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(30,35,40));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(30,40,35));
}

// remove node with two children

