#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::uint64_t time() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()
    .time_since_epoch()).count();
}

// Définition du type noeud de l'arbre ...
typedef struct node {
    uint64_t data;
    int height;
    struct node *left;
    struct node *right;
} node;

int calculateHeight(node* n) {
    if (n == NULL) return 0;
    return n->height;
}

// Balance Factor BF
int bf(node *n) {
    int leftHeight, rightHeight;
    node* left = n->left;
    node* right = n->right;

    if (n == NULL) {
        return 0;

    } 
    if (left == NULL) {
        leftHeight = 0;

    } else {
        leftHeight = left->height;
    }
    
    if (right == NULL) {
        rightHeight = 0;

    } else {
        rightHeight = right->height;
    } 

    return leftHeight - rightHeight;
}

// Rotation LL
node* llrotation(node *n) {
    node *tp;
    tp = n->left;

    n->left = tp->right;
    tp->right = n;

    int nLeftHeight  = calculateHeight(n->left);
    int nRightHeight = calculateHeight(n->right);
    int tpLeftHeight = calculateHeight(tp->left);

    n->height  = max(nLeftHeight, nRightHeight) + 1;
    tp->height = max(tpLeftHeight, n->height) + 1;

    return tp; 
}

// Rotation RR
node* rrrotation(node *n) {
    node *tp;
    tp = n->right;

    n->right = tp->left;
    tp->left = n;

    int nLeftHeight  = calculateHeight(n->left);
    int nRightHeight = calculateHeight(n->right);
    int tpLeftHeight = calculateHeight(tp->left);

    n->height  = max(nLeftHeight, nRightHeight) + 1;
    tp->height = max(tpLeftHeight, n->height) + 1;

    return tp; 
}

// Rotation RL
node * rlrotation(node *n) {
    node* tp;
    node* right = n->right;

    n->right = llrotation(right);

    tp = rrrotation(n);
    return tp; 
}

// Rotation LR
node* lrrotation(node *n) {
    node* tp;
    node* left = n->left;

    n->left = rrrotation(left);

    tp = llrotation(n);
    return tp; 
}

// Insertion
node* insert(node *&root, uint64_t data) {
    if (!root) {
        return new node{data, 1, nullptr, nullptr};
    }

    uint64_t rootData = root->data;
    node* rootLeft  = root->left;
    node* rootRight = root->right;
    int bfRoot = bf(root);

    if (data < rootData) {
        root->left = insert(rootLeft, data);

        if (bfRoot == 2) {
            data < rootLeft->data ? root = llrotation(root) : root = rrrotation(root);
        }
    } else if (data > rootData) {
        root->right = insert(rootRight, data);

        if (bfRoot == -2) {
            data < rootRight->data ? root = rrrotation(root) : root = llrotation(root);
        }
    }

    int rootLeftHeight  = calculateHeight(root->left);
    int rootRightHeight = calculateHeight(root->right);

    root->height = max(rootLeftHeight, rootRightHeight) + 1;
    return root;
}

// Suppresion
node* deleteNode(node *root, uint64_t data) {
    if (!root) {
        return nullptr;
    }

    uint64_t rootData = root->data;
    node* rootLeft  = root->left;
    node* rootRight = root->right;
    int bfRoot = bf(root);

    if (data < rootData) {
        root->left = deleteNode(rootLeft, data);

    } else if (data > rootData) {
        root->right = deleteNode(rootRight, data);

    } else {
        if (!rootLeft) {
            node* tmp = rootRight;
            delete root;
            return tmp;
        } else if (!rootRight) {
            node* tmp = rootLeft;
            delete root;
            return tmp;
        }

        node* tmp = rootRight;

        while (tmp->left) {
            tmp = tmp->left;
        }

        uint64_t tmpData = tmp->data;
        root->data = tmpData;
        root->right = deleteNode(rootRight, tmpData);
    }

    int rootLeftHeight  = calculateHeight(root->left);
    int rootRightHeight = calculateHeight(root->right);

    root->height = max(rootLeftHeight, rootRightHeight) + 1;

    int rootBalance = bf(root);
    int rootLeftBalance  = bf(root->left);
    int rootRightBalance = bf(root->right);

    if (rootBalance > 1 && rootLeftBalance >= 0) {
        return llrotation(root);

    } else if (rootBalance > 1 && rootLeftBalance < 0) {
        root->left = rrrotation(root->left);
        return llrotation(root);

    } else if (rootBalance < -1 && rootLeftBalance <= 0) {
        return rrrotation(root);

    } else if (rootBalance < -1 && rootLeftBalance > 0) {
        root->right = llrotation(root->right);
        return rrrotation(root);
    }

    return root;
}

node* searchNode(node* root, uint64_t data) {
    if (root) {

        uint64_t rootData = root->data;

        if (rootData == data) {
            return root;

        } else if (rootData > data) {
            node* rootLeft = root->left;
            return searchNode(rootLeft, data);

        } else if (rootData < data) {
            node* rootRight = root->right;
            return searchNode(rootRight, data);
        }
    } else {
        return NULL;
    }
}

void show(node* root) {
    if (root) {
        cout << "left : ";
        show(root->left);
        cout << "data " << root->data << " ";
        cout << "right : ";
        show(root->right);
    }
}

    
int main() {
    node* root = NULL;
    // remplir l'arbre
    // faire des tests
    std::cout << "HelloWorld" << std::endl;
    return 0;
}