#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string name;
    bool isFile;
    vector<Node*> children;

    Node(string name, bool isFile) {
        this->name = name;
        this->isFile = isFile;
    }
};

// Create new node
Node* createNode(string name, bool isFile) {
    return new Node(name, isFile);
}

// Add child with duplicate check
bool addChild(Node* parent, Node* child) {
    for (auto existing : parent->children) {
        if (existing->name == child->name) {
            cout << "Error: '" << child->name 
                 << "' already exists in this directory.\n";
            return false;
        }
    }

    parent->children.push_back(child);
    return true;
}

// Print tree
void printTree(Node* root, int level = 0) {
    if (!root) return;

    for (int i = 0; i < level; i++) cout << "  ";
    cout << (root->isFile ? "File: " : "Dir: ") << root->name << endl;

    for (auto child : root->children) {
        printTree(child, level + 1);
    }
}

// Search
bool search(Node* root, string name) {
    if (!root) return false;
    if (root->name == name) return true;

    for (auto child : root->children) {
        if (search(child, name)) return true;
    }
    return false;
}

// Count total files
int countFiles(Node* root) {
    if (!root) return 0;

    int count = 0;

    if (root->isFile)
        count++;

    for (auto child : root->children) {
        count += countFiles(child);
    }

    return count;
}

// Delete tree
void deleteTree(Node* root) {
    if (!root) return;

    for (auto child : root->children) {
        deleteTree(child);
    }
    delete root;
}

int main() {
    Node* root = createNode("root", false);

    Node* home = createNode("home", false);
    Node* docs = createNode("docs", false);
    Node* file1 = createNode("file1:", true);
    Node* file2 = createNode("file2:", true);

    addChild(root, home);
    addChild(home, docs);
    addChild(home, file1);

    // Duplicate test
    addChild(home, file1);

    addChild(docs, file2);

    cout << "File System Structure:\n";
    printTree(root);

    cout << "\nSearching file2:\n";
    if (search(root, "file2:"))
        cout << "Found!\n";
    else
        cout << "Not Found!\n";

    // count files
    cout << "\nTotal Files: " << countFiles(root) << endl;

    deleteTree(root);

    return 0;
}
