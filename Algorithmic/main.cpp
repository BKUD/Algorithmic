#include <iostream>
#include <memory>

// Определение структуры узла
struct Node {
    int key;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

// Функция для печати дерева
void printTree(const std::unique_ptr<Node>& node, const std::string& prefix = "", bool isLeft = true) {
    if (!node) return;
    std::cout << prefix;
    std::cout << (isLeft ? "|-- " : "\\-- ");
    std::cout << node->key << std::endl;
    printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
    printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
}

// Функция для создания узла
std::unique_ptr<Node> createNode() {
    int key;
    std::cout << "Введите ключ для узла (или -1 для завершения): ";
    std::cin >> key;
    if (key == -1) return nullptr;
    std::unique_ptr<Node> node = std::make_unique<Node>(key);
    std::cout << "Создание левого потомка узла " << key << std::endl;
    node->left = createNode();
    std::cout << "Создание правого потомка узла " << key << std::endl;
    node->right = createNode();
    return node;
}

// Функция для удаления поддерева с заданным ключом
void deleteSubtree(std::unique_ptr<Node>& node, int key) {
    if (node == nullptr) {
        return;
    }
    if (node->key == key) {
        node.reset();
        return;
    }
    deleteSubtree(node->left, key);
    deleteSubtree(node->right, key);
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Создание корня дерева\n";
    std::unique_ptr<Node> root = createNode();
    std::cout << "Дерево до удаления:\n";
    printTree(root);
    deleteSubtree(root, 3);  // Удаление поддерева с ключом 3
    std::cout << "Дерево после удаления:\n";
    printTree(root);
    return 0;
}
