#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    char character;
    long long frequency;
    int order;
    Node* left;
    Node* right;
};

struct CompareNodes {
    bool operator()(const Node* a, const Node* b) const {
        if (a->frequency != b->frequency) {
            return a->frequency > b->frequency;
        }
        return a->order > b->order;
    }
};

void printCodes(const Node* root, const string& code) {
    if (root == nullptr) {
        return;
    }

    // Print a code only for a character leaf.
    if (root->left == nullptr && root->right == nullptr) {
        cout << root->character << ": "
             << (code.empty() ? "0" : code) << '\n';
        return;
    }

    // Visit left first, then right.
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

void deleteTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string characters;

    // Enter the distinct characters as one string, for example: abcdef
    if (!(cin >> characters)) {
        return 1;
    }

    int n = static_cast<int>(characters.size());
    vector<long long> frequencies(n);

    // Enter one frequency for each character, in the same order.
    for (int i = 0; i < n; ++i) {
        if (!(cin >> frequencies[i])) {
            return 1;
        }
    }

    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;
    int nextOrder = 0;

    for (int i = 0; i < n; ++i) {
        Node* leaf = new Node{
            characters[i],
            frequencies[i],
            nextOrder++,
            nullptr,
            nullptr
        };
        minHeap.push(leaf);
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        Node* parent = new Node{
            '\0',
            left->frequency + right->frequency,
            nextOrder++,
            left,
            right
        };

        minHeap.push(parent);
    }

    Node* root = minHeap.empty() ? nullptr : minHeap.top();

    printCodes(root, "");
    deleteTree(root);

    return 0;
}