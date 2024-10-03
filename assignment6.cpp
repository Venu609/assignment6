#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

// A node of the Huffman Tree
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Comparator for the priority queue
struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

// Function to print the Huffman codes
void printCodes(Node* root, string str) {
    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// Function to build the Huffman Tree and print codes
void HuffmanCodes(char data[], int freq[], int size) {
    Node* left;
    Node* right;
    Node* top;

    // Create a priority queue (min heap)
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    // Create leaf nodes for each character and add them to the heap
    for (int i = 0; i < size; ++i)
        minHeap.push(new Node(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
        // Extract the two nodes with the smallest frequency
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with the sum of the frequencies
        top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // Print the Huffman codes by traversing the tree
    printCodes(minHeap.top(), "");
}

int main() {
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);

    return 0;
}