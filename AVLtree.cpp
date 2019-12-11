#include "heap headers//AVLtree.h"

#include <stdexcept>
#include <iostream>

using namespace std;

Tree::Node::Node(int key): left(0), right(0), parent(0),
    key(key), height(1) {}

Tree::Tree(): root(0) {}

bool Tree::Empty() const {
    return root == 0;
}

void Print (Tree::Node* node) {
    if (node == 0) {
        return;
    }
    Print(node->left);
    cout << node->key << " ";
    Print(node->right);
}

void Tree::Print () {
    ::Print (root);
    cout << endl;
}

void smallRightRotation (Tree::Node* a) {
    if (a == 0 || a->left == 0) {
        throw runtime_error ("incorrect srr argument");
    }
    Tree::Node* b = a->left;
    if (b->right != 0) {
        b->right->parent = a;
    }
    if (a->parent != 0) {
        if (a == a->parent->left) {
            a->parent->left = b;
        } else {
            a->parent->right = b;
        }
    }
    a->left = b->right;
    b->parent = a->parent;
    b->right = a;
    a->parent = b;
}

void smallLeftRotation (Tree::Node* a) {
    if (a == 0 || a->right == 0) {
        throw runtime_error ("incorrect slr argument ");
    }
    Tree::Node* b = a->right;
    if (b->left != 0) {
        b->left->parent = a;
    }
    if (a->parent != 0) {
        if (a == a->parent->left) {
            a->parent->left = b;
        } else {
            a->parent->right = b;
        }
    }
    a->right = b->left;
    b->parent = a->parent;
    b->left = a;
    a->parent = b;
}

void bigRightRotation (Tree::Node* a) {
    try {
        smallLeftRotation(a->left);
        smallRightRotation(a);
    } catch (exception& e) {
        throw runtime_error ("incorrect brr argument");
    }
}

void bigLeftRotation (Tree::Node* a) {
    try {
		smallRightRotation(a->right);
		smallLeftRotation(a);
    } catch (exception& e) {
        throw runtime_error ("incorrect blr argument");
    }
}

int getH (Tree::Node* node) {
    return node == 0 ? 0 : node->height;
}

void updateHeight (Tree::Node* node) {
    if (node == 0) {
        throw runtime_error ("can't updateHeight for 0 node");
    }
    node->height = 1 +
            max(getH(node->left), getH(node->right));
}

Tree::Node* least (Tree::Node* start) {
    if (start == 0) {
        throw runtime_error ("no least found");
    }
    while (start->left != 0) {
        start = start->left;
    }
    return start;
}

const int& Tree::GetMin () const {
    if (root == 0) {
        throw runtime_error ("no min to get");
    }
    return least(root)->key;
}

void Tree::ExtractMin () {
    Delete (GetMin());
}

Tree::Node* upperBound (Tree::Node* start) {
    if (start == 0) {
        throw runtime_error ("no upperBound found");
    }
    return least (start->right);
}

Tree::Node* most (Tree::Node* start) {
    if (start == 0) {
        throw runtime_error ("no most found");
    }
    while (start->right != 0) {
        start = start->right;
    }
    return start;
}

Tree::Node* antiUpperBound (Tree::Node* start) {
    if (start == 0) {
        throw runtime_error ("no antiUpperBound found");
    }
    return most (start->left);
}

Tree::Node* Search (Tree::Node* node, int key) {
    if (node == 0) {
        throw runtime_error ("search didn't find anything");
    }
    if (node->key == key) {
        return node;
    } else if (key < node->key) {
        return Search (node->left, key);
    } else {
        return Search (node->right, key);
    }
}

void Tree::fix (Tree::Node* node) {
    if (node == 0) {
        throw runtime_error ("can't fix 0 node");
    }
    updateHeight(node);
    if (abs(getH(node->left) - getH(node->right)) < 2) {
    } else if (getH(node->left) < getH(node->right)) {
        if (getH(node->right->right) == getH(node->left) + 1 &&
                getH(node->right->right) >= getH(node->right->left)) {
            smallLeftRotation(node);
            updateHeight(node);
            updateHeight(node->parent);
        } else {
            bigLeftRotation(node);
            updateHeight(node);
            updateHeight(node->parent);
            updateHeight(node->parent->right);
        }
    } else { /// getH(node->left) > getH(node->right)
        if (getH(node->left->left) == getH(node->right) + 1 &&
                getH(node->left->left) >= getH(node->left->right)) {
            smallRightRotation(node);
            updateHeight(node);
            updateHeight(node->parent);
        } else {
            bigRightRotation(node);
            updateHeight(node);
            updateHeight(node->parent);
            updateHeight(node->parent->left);
        }
    }
    if (node->parent != 0) {
        fix(node->parent);
    } else {
        root = node;
    }
}

void Tree::Insert (int key) {
    Node* node = new Node(key);
    if (root == 0) {
        root = node;
        return;
    }
    Node* cur = root;
    while (true) {
        if (key <= cur->key) {
            if (cur->left == 0) {
                cur->left = node;
                node->parent = cur;
                fix(cur);
                break;
            } else {
                cur = cur->left;
            }
        } else {
            if (cur->right == 0) {
                cur->right = node;
                node->parent = cur;
                fix(cur);
                break;
            } else {
                cur = cur->right;
            }
        }
    }
}

void Tree::Delete (int key) {
    Node* node = Search (root, key);
    if (node->left == 0 && node->right == 0) { // leaf
        if (node == root) {
            delete root;
            root = 0;
            return;
        } else {
            if (node->parent->left == node) {
                node->parent->left = 0;
            } else {
                node->parent->right = 0;
            }
            Node* temp = node->parent;
            delete node;
            fix(temp);
        }
    } else {
			Node* newNode = 0;
			if (node->right != 0) {
				newNode = upperBound(node);
			} else {
				newNode = antiUpperBound(node);
			}
			if (newNode == node->right) {
				node->key = newNode->key;
				node->right = newNode->right;
				if (node->right != 0) {
					node->right->parent = node;
				}
				delete newNode;
				fix(node);
			} else if (newNode == node->left) {
				node->key = newNode->key;
				node->left = newNode->left;
				if (node->left != 0) {
					node->left->parent = node;
				}
				delete newNode;
				fix(node);
			} else {
			Node* singleChild = (newNode->left == 0) ?
					newNode->right : newNode->left;
			if (singleChild != 0) {
				singleChild->parent = newNode->parent;
			}
			newNode->left = node->left;
			if (newNode->left != 0) {
				newNode->left->parent = newNode;
			}
			newNode->right = node->right;
			if (newNode->right != 0) {
				newNode->right->parent = newNode;
			}
			if (node->parent != 0) {
				if (node->parent->left == node) {
					node->parent->left = newNode;
				} else {
					node->parent->right = newNode;
				}
			} else {
				root = newNode;
			}
			if (newNode->parent->left == newNode) {
				newNode->parent->left = singleChild;
			} else {
				newNode->parent->right = singleChild;
			}
			Node* temp = newNode->parent;
			newNode->parent = node->parent;
			delete node;
			fix(temp);
        }
    }
}

void Tree::Merge (IHeap& ih) {
	Tree& tr = dynamic_cast<Tree&> (ih);
    while (!tr.Empty()) {
        Insert(tr.root->key);
        tr.Delete(tr.root->key);
    }
}
