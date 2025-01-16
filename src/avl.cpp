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

// Définition du type node de l'arbre ...
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
    if (n == NULL) return 0;
    return calculateHeight(n->left) - calculateHeight(n->right);
}

// Rotation LL
node* llrotation(node *n) {
    node *tp = n->left;
    n->left = tp->right;
    tp->right = n;

    n->height = max(calculateHeight(n->left), calculateHeight(n->right)) + 1;
    tp->height = max(calculateHeight(tp->left), n->height) + 1;

    return tp; 
}

// Rotation RR
node* rrrotation(node *n) {
    node *tp = n->right;
    n->right = tp->left;
    tp->left = n;

    n->height = max(calculateHeight(n->left), calculateHeight(n->right)) + 1;
    tp->height = max(calculateHeight(tp->right), n->height) + 1;

    return tp; 
}

// Rotation RL
node * rlrotation(node *n) {
    n->right = llrotation(n->right);
    return rrrotation(n);
}

// Rotation LR
node* lrrotation(node *n) {
    n->left = rrrotation(n->left);
    return llrotation(n);
}

// insert
node* insert(node *&root, uint64_t data) {
    if (!root) {
        root = new node{data, 1, nullptr, nullptr};
        return root;
    }

    if (data < root->data) {
        root->left = insert(root->left, data);

        if (bf(root) == 2) {
            root = (data < root->left->data) ? llrotation(root) : lrrotation(root);
        }
    } else if (data > root->data) {
        root->right = insert(root->right, data);

        if (bf(root) == -2) {
            root = (data > root->right->data) ? rrrotation(root) : rlrotation(root);
        }
    }

    root->height = max(calculateHeight(root->left), calculateHeight(root->right)) + 1;
    return root;
}

// Suppression
node* deleteNode(node *root, uint64_t data) {
    if (!root) return nullptr;

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (!root->left) {
            node* tmp = root->right;
            delete root;
            return tmp;
        } else if (!root->right) {
            node* tmp = root->left;
            delete root;
            return tmp;
        }

        node* tmp = root->right;
        while (tmp->left) tmp = tmp->left;

        root->data = tmp->data;
        root->right = deleteNode(root->right, tmp->data);
    }

    root->height = max(calculateHeight(root->left), calculateHeight(root->right)) + 1;

    int balance = bf(root);

    if (balance > 1 && bf(root->left) >= 0) return llrotation(root);
    if (balance > 1 && bf(root->left) < 0) {
        root->left = rrrotation(root->left);
        return llrotation(root);
    }
    if (balance < -1 && bf(root->right) <= 0) return rrrotation(root);
    if (balance < -1 && bf(root->right) > 0) {
        root->right = llrotation(root->right);
        return rrrotation(root);
    }

    return root;
}

node* searchNode(node* root, uint64_t data) {
    if (!root) return NULL;
    if (data == root->data) return root;
    return (data < root->data) ? searchNode(root->left, data) : searchNode(root->right, data);
}

void show(node* root) {
    if (root) {
        show(root->left);
        cout << root->data << " ";
        show(root->right);
    }
}

int main() {

    vector<uint64_t> insertTime, searchTime, deleteTime;
    for (int i = 5; i <= 15; i += 5) {
        cout << "Benchmarking " << i << "th file" << endl;

        ifstream f1("Values_" + to_string(i) + ".txt");
        ifstream f2("Search_" + to_string(i) + ".txt");
        ifstream f3("Delete_" + to_string(i) + ".txt");

        if (!f1.is_open() || !f2.is_open() || !f3.is_open()) {
            cerr << "Erreur : Impossible d'ouvrir les fichiers pour l'itération " << i << endl;
            continue;
        }

        uint64_t start = time();
        node *benchmarkRoot = NULL;
        uint64_t v;

        while (f1 >> v) {
            benchmarkRoot = insert(benchmarkRoot, v);
        }
        insertTime.push_back(time() - start);

        start = time();
        while (f2 >> v) {
            searchNode(benchmarkRoot, v);
        }
        searchTime.push_back(time() - start);

        start = time();
        while (f3 >> v) {
            benchmarkRoot = deleteNode(benchmarkRoot, v);
        }
        deleteTime.push_back(time() - start);

        f1.close();
        f2.close();
        f3.close();
    }

    // Affichage des temps
    cout << "Temps d'insertion : ";
    for (auto t : insertTime) cout << t << " ";
    cout << endl;

    cout << "Temps de recherche : ";
    for (auto t : searchTime) cout << t << " ";
    cout << endl;

    cout << "Temps de suppression : ";
    for (auto t : deleteTime) cout << t << " ";
    cout << endl;

    return 0;
}
