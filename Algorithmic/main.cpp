#include <iostream>
#include <memory>

// ����������� ��������� ����
struct Node {
    int key;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

// ������� ��� ������ ������
void printTree(const std::unique_ptr<Node>& node, const std::string& prefix = "", bool isLeft = true) {
    if (!node) return;
    std::cout << prefix;
    std::cout << (isLeft ? "|-- " : "\\-- ");
    std::cout << node->key << std::endl;
    printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
    printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
}

// ������� ��� �������� ����
std::unique_ptr<Node> createNode() {
    int key;
    std::cout << "������� ���� ��� ���� (��� -1 ��� ����������): ";
    std::cin >> key;
    if (key == -1) return nullptr;
    std::unique_ptr<Node> node = std::make_unique<Node>(key);
    std::cout << "�������� ������ ������� ���� " << key << std::endl;
    node->left = createNode();
    std::cout << "�������� ������� ������� ���� " << key << std::endl;
    node->right = createNode();
    return node;
}

// ������� ��� �������� ��������� � �������� ������
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
    std::cout << "�������� ����� ������\n";
    std::unique_ptr<Node> root = createNode();
    std::cout << "������ �� ��������:\n";
    printTree(root);
    deleteSubtree(root, 3);  // �������� ��������� � ������ 3
    std::cout << "������ ����� ��������:\n";
    printTree(root);
    return 0;
}
