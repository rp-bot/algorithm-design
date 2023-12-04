#include <fstream>
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <sstream>

using namespace std;

struct Node {
    char character;
    unsigned frequency;
    Node *left, *right;

    Node(char character, unsigned frequency) {
        this->character = character;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

void generateHuffmanCodes(Node* root, string str, map<char, string> &huffmanCode) {
    if (root == nullptr) return;

    if (root->character != '$') {
        huffmanCode[root->character] = str;
    }

    generateHuffmanCodes(root->left, str + "0", huffmanCode);
    generateHuffmanCodes(root->right, str + "1", huffmanCode);
}

int main() {
    ifstream file("freq.txt");

    if (file.fail()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    map<char, unsigned> frequencies;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        char character;
        unsigned frequency;
        ss >> character >> frequency;

        if (character == 'L' && line[1] == 'F') { // Handle special case for line feed
            character = '\n';
            ss >> frequency;
        }

        frequencies[character] = frequency;
    }

    file.close();

    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (auto pair : frequencies) {
        minHeap.push(new Node(pair.first, pair.second));

    }
    cout<< minHeap.top();

    while (minHeap.size() != 1) {

        Node *left = minHeap.top();
        minHeap.pop();

        Node *right = minHeap.top();
        minHeap.pop();

        Node *sum = new Node('$', left->frequency + right->frequency);
        sum->left = left;
        sum->right = right;

        minHeap.push(sum);
    }

    map<char, string> huffmanCode;
    generateHuffmanCodes(minHeap.top(), "", huffmanCode);

    ofstream outputFile("codetable.txt");
    for (auto pair : huffmanCode) {
        if (pair.first == '\n') {
            outputFile << "LF " << pair.second << "\n";
        } else {
            outputFile << pair.first << " " << pair.second << "\n";
        }
    }
    outputFile.close();

    return 0;
}
