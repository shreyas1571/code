#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return root;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp->left != NULL)
            q.push(temp->left);
        else {
            temp->left = createNode(data);
            return root;
        }

        if (temp->right != NULL)
            q.push(temp->right);
        else {
            temp->right = createNode(data);
            return root;
        }
    }
    return root;
}

void BFS(Node* root) {
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left)
                q.push(current->left);

            if (current->right)
                q.push(current->right);
        }
        cout << endl;
    }
}

int main() {
    Node* root = NULL;
    int numNodes;
    int data;

    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    for (int i = 0; i < numNodes; i++) {
        cout << "Enter data for node " << i + 1 << ": ";
        cin >> data;
        root = insertNode(root, data);
    }

    cout << "BFS Traversal: ";
    BFS(root);

    return 0;
}

