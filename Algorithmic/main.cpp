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
        return 0;
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
            node->right = createTreeFromUserInput(depth - 1, "правого");  // Right child is created second
            node->left = createTreeFromUserInput(depth - 1, "левого");  // Left child is created first
            return node;
        }
    }
    else {
        return nullptr;
    }
}

void calculateHeightDifferences(Node* node) {
    if (node != nullptr) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        node->value = abs(leftHeight - rightHeight);
        calculateHeightDifferences(node->left);
        calculateHeightDifferences(node->right);
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
            if (j < (1 << i) - 1) {  // Only print spaces between values, not after the last value
                for (int k = 0; k < (1 << (MAX_DEPTH - i)) - 1; ++k) {
                    std::cout << "  ";
                }
            }
        }
        std::cout << "\n";
    }
}

void deleteTree(Node* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    Node* tree = createTreeFromUserInput(MAX_DEPTH);  // Create a tree from user input with depth MAX_DEPTH
    calculateHeightDifferences(tree);  // Calculate height differences after the tree has been created

    int matrix[MAX_DEPTH][MAX_NODES];
    for (int i = 0; i < MAX_DEPTH; ++i) {
        for (int j = 0; j < MAX_NODES; ++j) {
            matrix[i][j] = -1;
        }
    }

    fillMatrix(tree, 0, 0, matrix);
    printMatrix(matrix);
    deleteTree(tree);
    return 0;
}
