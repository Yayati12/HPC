#include <iostream> 
#include <queue> 
#include <omp.h> 
using namespace std; 
class Node { 
public: 
Node *left, *right; 
int data; 
}; 
class Breadthfs { 
public: 
Node* insert(Node* root, int data); 
void bfs(Node* head); 
}; 
Node* Breadthfs::insert(Node* root, int data) { 
if (!root) { 
root = new Node; 
root->left = root->right = nullptr; 
root->data = data; 
return root; 
} 
queue<Node*> q; 
q.push(root); 
while (!q.empty()) { 
Node* temp = q.front(); 
q.pop(); 
if (!temp->left) { 
temp->left = new Node; 
temp->left->left = temp->left->right = nullptr; 
temp->left->data = data; 
return root; 
} else { 
q.push(temp->left); 
} 
 
        if (!temp->right) { 
            temp->right = new Node; 
            temp->right->left = temp->right->right = nullptr; 
            temp->right->data = data; 
            return root; 
        } else { 
            q.push(temp->right); 
        } 
    } 
    return root; 
} 
 
void Breadthfs::bfs(Node* head) { 
    if (!head) return; 
queue<Node*> q; 
    q.push(head); 
 
    while (!q.empty()) { 
        int qSize = q.size(); 
 
        #pragma omp parallel for 
        for (int i = 0; i < qSize; i++) { 
            Node* currNode; 
 
            #pragma omp critical 
            { 
                currNode = q.front(); 
                q.pop(); 
                cout << currNode->data << " "; 
            } 
 
            #pragma omp critical 
            { 
                if (currNode->left) q.push(currNode->left); 
                if (currNode->right) q.push(currNode->right); 
            } 
        } 
        cout << endl; 
    } 
} 
 
int main() { 
    Node* root = nullptr; 
    Breadthfs bfsHandler; 
    int data; 
    char ans; 
do { 
cout << "\nEnter data => "; 
cin >> data; 
root = bfsHandler.insert(root, data); 
cout << "Do you want to insert one more node? (y/n) "; 
cin >> ans; 
} while (ans == 'y' || ans == 'Y'); 
cout << "\nBreadth-First Search (BFS) Output:\n"; 
bfsHandler.bfs(root); 
return 0; 
}