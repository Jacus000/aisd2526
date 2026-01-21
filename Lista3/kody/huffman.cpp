#include <bits/stdc++.h>
using namespace std;

class Node {
public:
	int data;
	Node *left, *right;
	Node(int x) {
		data = x;
		left = nullptr;
		right = nullptr;
	}
};

class Compare {
public:
	bool operator() (Node* a, Node* b) {
		return a->data > b->data;
	}
};

void preOrder(Node* root, vector<string> &ans, string curr) {
	if (root == nullptr) return;

	if (root->left == nullptr && root->right==nullptr) {
		ans.push_back(curr);
		return;
	}

	preOrder(root->left, ans, curr + '0');
	preOrder(root->right, ans, curr + '1');
}

vector<string> huffmanCodes(string s,vector<int> freq) {
	int n = s.length();
    
	priority_queue<Node*, vector<Node*>, Compare> pq;
	for (int i=0; i<n; i++) {
		Node* tmp = new Node(freq[i]);
		pq.push(tmp);
	}
	while (pq.size()>=2) {
	    
	    //left node 
		Node* l = pq.top();
		pq.pop();
        
        //right node 
		Node* r = pq.top();
		pq.pop();

		Node* newNode = new Node(l->data + r->data);
		newNode->left = l;
		newNode->right = r;

		pq.push(newNode);
	}

	Node* root = pq.top();
	vector<string> ans;
	preOrder(root, ans, "");
	return ans;
}

int main() {
	string s = "abcdef";
	vector<int> freq = {5, 9, 12, 13, 16, 45};
	vector<string> ans = huffmanCodes(s, freq);
	for (int i=0; i< ans.size(); i++) {
	    cout << ans[i] << " ";
	}
	
	return 0;
}