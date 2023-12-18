#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void printTreeStructure(Node* node, int space) {
    if (node == NULL)
        return;

    space += 10;

    printTreeStructure(node->right, space);

    std::cout << std::endl;
    for (int i = 10; i < space; i++)
        std::cout << " ";
    std::cout << node->data << "\n";

    printTreeStructure(node->left, space);
}

int main() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    printTreeStructure(root, 0);

    return 0;
}
