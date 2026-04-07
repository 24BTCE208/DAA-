#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Node structure for Huffman Tree
struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char d, int f) {
        data = d;
        freq = f;
        left = right = NULL;
    }
};

// Comparator for priority queue (min-heap)
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Function to print Huffman Codes
void printCodes(Node* root, string code) {
    if (!root)
        return;

    // If leaf node, print character and code
    if (root->data != '$')
        cout << root->data << ": " << code << endl;

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

// Function to build Huffman Tree
void huffmanCoding(vector<char> chars, vector<int> freq, int n) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create leaf nodes and push into queue
    for (int i = 0; i < n; i++) {
        pq.push(new Node(chars[i], freq[i]));
    }

    // Build the tree
    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        Node *newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    // Print Huffman Codes
    Node* root = pq.top();
    printCodes(root, "");
}

// Driver code
int main() {
    vector<char> chars = {'A', 'B', 'C', 'D', 'E', 'F'};
    vector<int> freq  = {5, 9, 12, 13, 16, 45};

    int n = chars.size();

    cout << "Huffman Codes:\n";
    huffmanCoding(chars, freq, n);

    return 0;
}
