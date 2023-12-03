#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAX_DEPTH 5
#define MAX_NODES (1 << MAX_DEPTH) - 1

struct Node {
    int value;
    Node* left;
    Node* right;
};

int height(Node* node) {
    if (node == nullptr) {
        return -1;  // Return -1 for missing nodes
    }
    else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

Node* createTreeFromUserInput(int depth, const std::string& direction = "корневой") {
    if (depth > 0) {
        Node* node = new Node;
        std::cout << "Введите значение для " << direction << " узла на глубине " << depth << ": ";
        std::cin >> node->value;
        if (node->value == -1) {
            delete node;
            return nullptr;
        }
        else {
            node->right = createTreeFromUserInput(depth - 1, "правого");  // Right child is created first
            node->left = createTreeFromUserInput(depth - 1, "левого");  // Left child is created second
            int leftHeight = (node->left != nullptr) ? height(node->left) : -1;  // Get height of left subtree, or -1 if it doesn't exist
            int rightHeight = (node->right != nullptr) ? height(node->right) : -1;  // Get height of right subtree, or -1 if it doesn't exist
            node->value = abs(leftHeight - rightHeight);  // Store height difference in node
            return node;
        }
    }
    else {
        return nullptr;
    }
}

void fillMatrix(Node* node, int depth, int pos, int(&matrix)[MAX_DEPTH][MAX_NODES]) {
    if (node != nullptr) {
        matrix[depth][pos] = node->value;
        fillMatrix(node->left, depth + 1, pos * 2, matrix);
        fillMatrix(node->right, depth + 1, pos * 2 + 1, matrix);
    }
}

void printMatrix(int(&matrix)[MAX_DEPTH][MAX_NODES]) {
    for (int i = 0; i < MAX_DEPTH; ++i) {
        for (int j = 0; j < (1 << (MAX_DEPTH - i - 1)); ++j) {
            std::cout << "  ";
        }
        for (int j = 0; j < (1 << i); ++j) {
            std::cout << matrix[i][j];  // Print -1 where there is no node
            for (int k = 0; k < (1 << (MAX_DEPTH - i)) - 1; ++k) {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    Node* tree = createTreeFromUserInput(MAX_DEPTH);  // Create a tree from user input with depth MAX_DEPTH

    int matrix[MAX_DEPTH][MAX_NODES];
    for (int i = 0; i < MAX_DEPTH; ++i) {
        for (int j = 0; j < MAX_NODES; ++j) {
            matrix[i][j] = -1;
        }
    }

    fillMatrix(tree, 0, 0, matrix);
    printMatrix(matrix);

    return 0;
}
