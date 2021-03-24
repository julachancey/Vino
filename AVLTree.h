#pragma once

#include <sstream>
#include <istream>
#include <cctype>
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

class Tree{
public:
    struct Node{ 
        string name; 
        string type;
        string location;
        string province;
        string region;
        float pricePerPoint;
        int price;
        Node* right = nullptr;
        Node* left = nullptr;

        Node(string name, string type, string location, string province, string region, float pricePerPoint, int price){
            this->name = name;
            this->type = type;
            this->location = location;
            this->province = province;
            this->region = region;
            this->pricePerPoint = pricePerPoint;
            this->price = price;
        }

    };

    void addNode(string name, string type, string location, string province, string region, float pricePerPoint, int price);
    Node* insertNewNode(Node* node, string name, string type, string location, string province, string region, float pricePerPoint, int price);

    void checkBalanceInorder(Node* currNode);
    void reBalance(Node* node);
    int getHeight(Node* currNode);
    Node* getParent(Node* node);

    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* rotateLeftRight(Node* node);

    void print(); 
    Node* Inorder(Node* currNode); // prints biggest to smallest values 

private:
    Node* root = nullptr;
    int numTracker = 0;
};

// creates and adds new node 
void Tree::addNode(string name, string type, string location, string province, string region, float pricePerPoint, int price){

    if (root == nullptr){
        Node* newNode = new Node(name, type, location, province, region, pricePerPoint, price);
        root = newNode;
    }
    else{
        insertNewNode(root, name, type, location, province, region, pricePerPoint, price);
        Node* currNode = root;

        while (currNode!= nullptr){ // iterate and find added node so as to rebalance below 
            if (currNode->pricePerPoint == pricePerPoint)
                break;
            else if (currNode->pricePerPoint > pricePerPoint){
                currNode = currNode->left;
            }
            else{
                currNode = currNode->right;
            }
        }

        checkBalanceInorder(root); // goes through each node inorder, checking the balance factor 
        
    }

}

Tree::Node* Tree::insertNewNode(Node* node, string name, string type, string location, string province, string region, float pricePerPoint, int price){
    // from https://stepik.org/submissions/1480362/296162976?unit=379727
    if (node == nullptr){
        Node* newnode = new Node(name, type, location, province, region, pricePerPoint, price);
        return newnode;
    }
    if (pricePerPoint == node->pricePerPoint){
        return nullptr;
    }
    else if (pricePerPoint < node->pricePerPoint){
        node->left = insertNewNode(node->left, name, type, location, province, region, pricePerPoint, price);
    }
    else{
        node->right = insertNewNode(node->right, name, type, location, province, region, pricePerPoint, price);
    }
    return node;
}

// goes through entire tree postorder (bottom up) and rebalances it  
void Tree::checkBalanceInorder(Node* currNode){
    if (currNode != nullptr){
        checkBalanceInorder(currNode->left);
        checkBalanceInorder(currNode->right);
        reBalance(currNode);
    }
}

// checks if node passed in is unbalanced 
void Tree::reBalance(Node* node){
    if (node->pricePerPoint == root->pricePerPoint){ // reassign to root 
        int balanceParent = getHeight(node->left) - getHeight(node->right); // balance factor 
        if (balanceParent > 1){ // left heavy (3-1 = 2) 
            if (getHeight(node->left->left) - getHeight(node->left->right) == 1){ // needs right rotation 
                root = rotateRight(node);
                
            }
            else if (getHeight(node->left->left) - getHeight(node->left->right) == -1){ // needs left right 
                root = rotateLeftRight(node);
            }
        }
        else if (balanceParent < -1){ // right heavy (1-3 = -2)
            if (getHeight(node->right->left) - getHeight(node->right->right) == -1){ // needs left rotation 
                root = rotateLeft(node);
            }
            else if (getHeight(node->right->left) - getHeight(node->right->right) == 1){ // needs right left 
                root = rotateRightLeft(node);
            }

        }
        
    }
    else{
        Node* parent = getParent(node); // so as to link back to tree 

        int balanceParent = getHeight(node->left) - getHeight(node->right);
        if (balanceParent > 1){ // left heavy (3-1 = 2) 
            if (getHeight(node->left->left) - getHeight(node->left->right) == 1){ // needs right rotation 
                if (parent->left->pricePerPoint == node->pricePerPoint) // links back to tree 
                    parent->left = rotateRight(node);
                else
                    parent->right = rotateRight(node);
                
            }
            else if (getHeight(node->left->left) - getHeight(node->left->right) == -1){ // needs left right 
                if (parent->left->pricePerPoint == node->pricePerPoint) // links back to tree 
                    parent->left = rotateLeftRight(node);
                else
                    parent->right = rotateLeftRight(node);
            }
        }
        else if (balanceParent < -1){ // right heavy (1-3 = -2)
            if (getHeight(node->right->left) - getHeight(node->right->right) == -1){ // needs left rotation 
                if (parent->left->pricePerPoint == node->pricePerPoint) // links back to tree 
                    parent->left = rotateLeft(node);
                else
                    parent->right = rotateLeft(node);
                
            }
            else if (getHeight(node->right->left) - getHeight(node->right->right) == 1){ // needs right left 
                if (parent->left->pricePerPoint == node->pricePerPoint) // links back to tree 
                    parent->left = rotateRightLeft(node);
                else
                    parent->right = rotateRightLeft(node);
            }

        }
          
    }

}

int Tree::getHeight(Node* currNode){ 
    // concept from https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
    // doubles as height function 
    if (currNode != nullptr){
        int leftHeight = getHeight(currNode->left);
        int rightHeight = getHeight(currNode->right);
        if (leftHeight < rightHeight)
            return rightHeight + 1;
        return leftHeight + 1;
    }
    return 0;
}

// get parent 
Tree::Node* Tree::getParent(Node* node){
    // returns the parent of the node passed in, or null if root passed in 
    stack<Node*> s;
    Node* currNode = root;
    while (currNode != nullptr){
        s.push(currNode);
        if (currNode->pricePerPoint == node->pricePerPoint)
            break;
        if (currNode->pricePerPoint > node->pricePerPoint){
            currNode = currNode->left;
        }
        else{
            currNode = currNode->right;
        }
    }
    s.pop();
    if (s.size() == 0)
        return nullptr; // if the node passed in was the root
    return s.top(); 
}

Tree::Node* Tree::rotateLeft(Node* node){
    // from lecture slides Trees-3, Amanpreet Kapoor 
    // https://ufl.instructure.com/courses/406617/files/folder/Fall%202020/Powerpoints/Aman%20Presentations?preview=52890028
    Node* grandchild = node->right->left;
    Node* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    return newParent;
}

Tree::Node* Tree::rotateRight(Node* node){
    // from lecture slides Trees-3, Amanpreet Kapoor 
    // https://ufl.instructure.com/courses/406617/files/folder/Fall%202020/Powerpoints/Aman%20Presentations?preview=52890028
    Node* grandchild = node->left->right;
    Node* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;
    return newParent;
}

Tree::Node* Tree::rotateLeftRight(Node* node){ 
    // pass in grandparent 
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Tree::Node* Tree::rotateRightLeft(Node* node){
    // pass in grandparent 
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

void Tree::print(){
    Inorder(root);
}

Tree::Node* Tree::Inorder(Node* currNode){
    if (currNode != nullptr){
        Inorder(currNode->left);
        
            cout << numTracker+1 << ". " << currNode->name << " | " << currNode->type << " | " << currNode->location 
            << ", " << currNode->region << ", " << currNode->province << " | $" << currNode->price << endl;
        
        numTracker++;
        Inorder(currNode->right);
    }
    return nullptr;
}