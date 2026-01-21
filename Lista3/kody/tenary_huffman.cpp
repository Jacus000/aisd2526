#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;       //czestotliwosc
    char c;         //znak
    vector<Node*> children; //wektor dzieci

    Node(int x, char ch) {
        data = x;
        c = ch;
    }
};

class Compare {
public:
    bool operator() (Node* a, Node* b) {
        return a->data > b->data;
    }
};

// dfs

void generateCodes(Node* root, map<char, string> &ans, string curr) {
    if (root == nullptr) return;

    if (root->children.empty()) {
        if (root->c != '\0') {
            ans[root->c] = curr;
        }
        return;
    }
    for (int i = 0; i < root->children.size(); i++) {
        //dodajemy 0 1 2 w zaleznosci od dziecka
        generateCodes(root->children[i], ans, curr + to_string(i));
    }
}

map<char, string> ternaryHuffmanCodes(string s, vector<int> freq) {
    int n = s.length();
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < n; i++) {
        Node* tmp = new Node(freq[i], s[i]);
        pq.push(tmp);
    }

    if ((pq.size() - 1) % 2 != 0) {
        Node* dummy = new Node(0, '\0');
        pq.push(dummy);
    }

    while (pq.size() > 1) {
        Node* newNode = new Node(0, '\0');

        for (int i = 0; i < 3; i++) {
            if (!pq.empty()) {
                Node* child = pq.top();
                pq.pop();
                newNode->data += child->data; //sumujemy wagi
                newNode->children.push_back(child);
            }
        }
        pq.push(newNode);
    }

    Node* root = pq.top();
    map<char, string> ans;
    generateCodes(root, ans, "");
    
    return ans;
}

int main(){
    string s = "abcdef";
    vector<int> freq = {5, 9, 12, 13, 16, 45};
    
    map<char, string> result = ternaryHuffmanCodes(s, freq);
    
    cout << "Znak : Kod Ternarny" << endl;
    cout << "-------------------" << endl;
    for (auto pair : result) {
        cout << pair.first << "    : " << pair.second << endl;
    }
}