#include "RBtree.h"
#include <stdlib.h>
#include<iostream>
#include<Windows.h>


using namespace std;

struct Node{
	string city;
	Node* left;
	Node* right;
	Node* pred;
	int color = 0;
	Node(string city, int color) :city(city), color(color), left(nullptr), right(nullptr), pred(nullptr){}//1 - красный 0 - черный
};

class  RBTree {
public:
    Node* root;
    void checkRoot(Node* child);
    void uncleBlack(Node* grandpa, Node* parent, Node* child);
    void uncleRed(Node* grandpa, Node* uncle, Node* parent, Node* child);
    void setRoot(string city);
    void insertNode(string city);
    void display(Node* p);
    void preOrderTree(Node* tree);
    void inOrderTree(Node* tree);
    void sumTree(Node* tree, int& sum);
    int heightTree(Node* n) const;
    int maxList(int x, int y) const;
};


void RBTree::setRoot(string city) {
        root = new Node(city, 0);
    }

void RBTree::uncleBlack(Node* grandpa, Node* parent, Node* child) {
    Node* help;

    if ((grandpa->left == parent && parent->right == child) ||
        (grandpa->right == parent && parent->left == child)) {
        if (grandpa->left == parent && parent->right == child) {
            child->pred = grandpa;
            child->left = parent;
            parent->pred = child;
            parent->right = nullptr;
            help = parent;
            parent = child;
            child = help;
        }
        else {
            child->pred = grandpa;
            child->right = parent;
            parent->pred = child;
            parent->left = nullptr;
            help = parent;
            parent = child;
            child = help;
        }
    }

    if (parent->city.length() <= grandpa->city.length()) {
        help = parent->right;
        parent->right = grandpa;
        parent->pred = grandpa->pred;
        if (grandpa->city.length() <= grandpa->pred->city.length())
            grandpa->pred->left = parent;
        else
            grandpa->pred->right = parent;
        grandpa->pred = parent;
        parent->color = 0;
        grandpa->color = 1;
        grandpa->left = help;
    }
    else {
        help = parent->left;
        parent->left = grandpa;
        parent->pred = grandpa->pred;
        if (grandpa->city.length() <= grandpa->pred->city.length())
            grandpa->pred->left = parent;
        else
            grandpa->pred->right = parent;
        grandpa->pred = parent;
        parent->color = 0;
        grandpa->color = 1;
        grandpa->right = help;
    }
}

void RBTree::uncleRed(Node* grandpa, Node* uncle, Node* parent, Node* child) {
    if (child->pred == nullptr)
        return;

    parent->color = 0;
    uncle->color = 0;
    if (grandpa->pred != nullptr)
        grandpa->color = 1;

    checkRoot(grandpa);
}

void RBTree::checkRoot(Node* child) {
    if (child->pred == nullptr || child->pred->pred == nullptr)
        return;

    Node* grandpa = child->pred->pred;
    Node* parent = child->pred;
    Node* uncle = nullptr;

    if (grandpa->city.length() <= parent->city.length()) {
        uncle = grandpa->left;
    }
    else {
        uncle = grandpa->right;
    }

    if (parent->color == 1) {
        if (uncle != nullptr && uncle->color == 1)
            uncleRed(grandpa, uncle, parent, child);
        else
            uncleBlack(grandpa, parent, child);
    }
    
    return;
}

void RBTree::insertNode(string city) {
    Node* child = new Node(city, 1);
    Node* parent = root;
    Node* upper = nullptr;

    while (parent != nullptr) {
        upper = parent;
        if (parent->city.length() >= child->city.length())
            parent = parent->left;
        else
            parent = parent->right;
    }

    child->pred = upper;
    if (upper->city.length() >= child->city.length())
        upper->left = child;
    else
        upper->right = child;

    checkRoot(child);
}

void RBTree::display(Node* p)
{
    if (root == NULL)
    {
        cout << "\nEmpty Tree.";
        return;
    }
    if (p != NULL)
    {
        cout << "\n\t NODE: ";
        cout << "\n CIty: " << p->city;
        cout << "\n Colour: ";
        if (p->color == 0)
            cout << "Black";
        else
            cout << "Red";
        if (p->pred != NULL)
            cout << "\n Parent: " << p->pred->city;
        else
            cout << "\n There is no parent of the node.  ";
        if (p->right != NULL)
            cout << "\n Right Child: " << p->right->city;
        else
            cout << "\n There is no right child of the node.  ";
        if (p->left != NULL)
            cout << "\n Left Child: " << p->left->city;
        else
            cout << "\n There is no left child of the node.  ";
        cout << endl;
        if (p->left)
        {
            cout << "\n\nLeft:\n";
            display(p->left);
        }
        /*else
         cout<<"\nNo Left Child.\n";*/
        if (p->right)
        {
            cout << "\n\nRight:\n";
            display(p->right);
        }
        /*else
         cout<<"\nNo Right Child.\n"*/
    }
}
//Функция прямого обхода дерева
void RBTree::preOrderTree(Node* tree) {
    if (tree != nullptr) {
        cout << tree->city << ' ';
        preOrderTree(tree->left);
        preOrderTree(tree->right);
    }
}
//Функция симметричного прохода дерева
void RBTree::inOrderTree(Node* tree) {
    if (tree != nullptr) {
        inOrderTree(tree->left);
        cout << tree->city << ' ';
        inOrderTree(tree->right);
    }
}

void RBTree::sumTree(Node* tree, int& sum) {
    if (tree != nullptr) {
        sum += tree->city.length();
        sumTree(tree->left, sum);
        sumTree(tree->right, sum);
    }
}

int RBTree::heightTree(Node* n) const {
    if (n == nullptr)
        return -1;
    else
        return maxList(heightTree(n->left), heightTree(n->right)) + 1;
}

int RBTree::maxList(int x, int y) const {
    if (x >= y)
        return x;
    else
        return y;
}



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	string city;
	//cout << "Введите значение корня ";
	//cin >> city;
    RBTree tree;
    tree.setRoot("Москва");
	tree.insertNode("Оренбург");
    tree.insertNode("Кашира");
    tree.insertNode("Ярославль");
    tree.insertNode("Сочи");
    tree.insertNode("Казань");
    tree.insertNode("Волгоград");
    tree.insertNode("Самара");
    tree.insertNode("Безенчук");
    tree.insertNode("Кувандык");

    int sum = 0;
    tree.sumTree(tree.root, sum);
    
    cout << "Сумма узлов: " << sum << endl;
    cout << "Глубина дерева: " << tree.heightTree(tree.root);

	return 0;
}