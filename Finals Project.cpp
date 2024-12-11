#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

// Creature structure
struct Creature {
    string name;
    int power;
    Creature(string n, int p) : name(n), power(p) {}
};

// Node structure for Binary Tree and Binary Search Tree
struct Node {
    Creature creature;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    Node(Creature c) : creature(c), left(nullptr), right(nullptr) {}
};

// BST insertion
shared_ptr<Node> insertBST(shared_ptr<Node> root, Creature c) {
    if (!root) return make_shared<Node>(c);
    if (c.power < root->creature.power)
        root->left = insertBST(root->left, c);
    else
        root->right = insertBST(root->right, c);
    return root;
}

// BST search
shared_ptr<Node> searchBST(shared_ptr<Node> root, int power) {
    if (!root || root->creature.power == power)
        return root;
    if (power < root->creature.power)
        return searchBST(root->left, power);
    return searchBST(root->right, power);
}

// BST deletion
shared_ptr<Node> deleteBST(shared_ptr<Node> root, int power) {
    if (!root) return nullptr;

    if (power < root->creature.power) {
        root->left = deleteBST(root->left, power);
    } else if (power > root->creature.power) {
        root->right = deleteBST(root->right, power);
    } else {
        // Node with one or no child
        if (!root->left) return root->right;
        if (!root->right) return root->left;

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        shared_ptr<Node> temp = root->right;
        while (temp->left) temp = temp->left;
        root->creature = temp->creature;
        root->right = deleteBST(root->right, temp->creature.power);
    }
    return root;
}

// Preorder Traversal
void preorder(shared_ptr<Node> root) {
    if (!root) return;
    cout << root->creature.name << " (" << root->creature.power << ") ";
    preorder(root->left);
    preorder(root->right);
}

// Inorder Traversal
void inorder(shared_ptr<Node> root) {
    if (!root) return;
    inorder(root->left);
    cout << root->creature.name << " (" << root->creature.power << ") ";
    inorder(root->right);
}

// Postorder Traversal
void postorder(shared_ptr<Node> root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->creature.name << " (" << root->creature.power << ") ";
}
//function of bt
// Delete node from Binary Tree (BT)
// Forward declaration of deleteDeepestNode
void deleteDeepestNode(shared_ptr<Node> root, shared_ptr<Node> deepestNode);

// Function to delete a node in Binary Tree
shared_ptr<Node> deleteBT(shared_ptr<Node> root, int power) {
    if (!root) return nullptr;

    // Perform level order traversal to find the deepest node
    queue<shared_ptr<Node>> q;
    q.push(root);
    shared_ptr<Node> temp = nullptr;
    shared_ptr<Node> nodeToDelete = nullptr;

    // Standard level order traversal
    while (!q.empty()) {
        temp = q.front();
        q.pop();

        // If we find the node to delete, store it
        if (temp->creature.power == power) {
            nodeToDelete = temp;
        }

        // Push children of the current node into the queue
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }

    // If we found the node to delete, replace it with the deepest node's value
    if (nodeToDelete) {
        // Copy the deepest node's value into the node to be deleted
        nodeToDelete->creature = temp->creature;

        // Now delete the deepest node (temp) from the tree
        deleteDeepestNode(root, temp);
    }

    return root;
}

// Helper function to delete the deepest node
void deleteDeepestNode(shared_ptr<Node> root, shared_ptr<Node> deepestNode) {
    queue<shared_ptr<Node>> q;
    q.push(root);

    // Standard level order traversal
    shared_ptr<Node> temp = nullptr;
    while (!q.empty()) {
        temp = q.front();
        q.pop();

        // If this is the deepest node, remove it
        if (temp->left == deepestNode) {
            temp->left = nullptr;
            return;
        } else if (temp->right == deepestNode) {
            temp->right = nullptr;
            return;
        }

        // Push children of the current node into the queue
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
}


// Search node in Binary Tree (BT)
shared_ptr<Node> searchBT(shared_ptr<Node> root, int power) {
    if (!root) return nullptr;

    queue<shared_ptr<Node>> q;
    q.push(root);

    while (!q.empty()) {
        shared_ptr<Node> current = q.front();
        q.pop();

        if (current->creature.power == power) {
            return current; // Return the node if power matches
        }

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }

    return nullptr; // Return nullptr if the creature is not found
}
// Preorder Traversal for Binary Tree (BT)
void preorderBT(shared_ptr<Node> root) {
    if (!root) return;
    // Visit the root node
    cout << root->creature.name << " (" << root->creature.power << ") ";
    // Traverse the left subtree
    preorderBT(root->left);
    // Traverse the right subtree
    preorderBT(root->right);
}

// Inorder Traversal for Binary Tree (BT)
void inorderBT(shared_ptr<Node> root) {
    if (!root) return;
    inorder(root->left);
    cout << root->creature.name << " (" << root->creature.power << ") ";
    inorder(root->right);
}
// Postorder Traversal for Binary Tree (BT)
void postorderBT(shared_ptr<Node> root) {
    if (!root) return;
    postorderBT(root->left);
    postorderBT(root->right);
    cout << root->creature.name << " (" << root->creature.power << ") ";
}


// Binary Tree (BT) insertion
void insertBT(shared_ptr<Node>& root, Creature c) {
    if (!root) {
        root = make_shared<Node>(c);
        return;
    }

    queue<shared_ptr<Node>> q;
    q.push(root);

    while (!q.empty()) {
        shared_ptr<Node> current = q.front();
        q.pop();

        if (!current->left) {
            current->left = make_shared<Node>(c);
            return;
        } else {
            q.push(current->left);
        }

        if (!current->right) {
            current->right = make_shared<Node>(c);
            return;
        } else {
            q.push(current->right);
        }
    }
}

// Max-Heap and Min-Heap insertion
void addCreatureToMaxHeap(priority_queue<int>& maxHeap, Creature c) {
    maxHeap.push(c.power);
}

void addCreatureToMinHeap(priority_queue<int, vector<int>, greater<int>>& minHeap, Creature c) {
    minHeap.push(c.power);
}
// Heapify function to maintain heap property for integer arrays
void heapify(vector<int>& arr, int n, int i, bool isMaxHeap) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (isMaxHeap) {
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
    } else {
        if (left < n && arr[left] < arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] < arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, isMaxHeap);
    }
}

// Function to build a Max-Heap or Min-Heap from an unsorted array
void buildHeap(vector<int>& arr, bool isMaxHeap) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i, isMaxHeap);
    }
}

//need here a function for heapify
void heapify_creatures(vector<int>& powers, bool isMaxHeap) {
    if (isMaxHeap) {
        make_heap(powers.begin(), powers.end());  // Max-Heap
    } else {
        make_heap(powers.begin(), powers.end(), greater<int>());  // Min-Heap
    }

    // Display heap structure
    cout << (isMaxHeap ? "Max-Heap (strongest creatures first): " : "Min-Heap (weakest creatures first): ");

    if (isMaxHeap) {
        // For Max-Heap
        priority_queue<int> tempHeap(powers.begin(), powers.end());
        while (!tempHeap.empty()) {
            cout << tempHeap.top() << " ";
            tempHeap.pop();
        }
    } else {
        // For Min-Heap
        priority_queue<int, vector<int>, greater<int>> tempHeap(powers.begin(), powers.end(), greater<int>());
        while (!tempHeap.empty()) {
            cout << tempHeap.top() << " ";
            tempHeap.pop();
        }
    }
    cout << endl;
}

// Display all creatures
void displayCreatures(const vector<Creature>& creatures) {
    cout << "\nAll Creatures:" << endl;
    for (const auto& creature : creatures) {
        cout << "- " << creature.name << " (Power: " << creature.power << ")" << endl;
    }
}

// Function to handle BST operations
void handleBST(shared_ptr<Node>& bstRoot) {
    int choice;
    bool bstRunning = true;
    while (bstRunning) {
        cout << "\n=== BST Menu ===" << endl;
        cout << "1. Insert Creature" << endl;
        cout << "2. Delete Creature" << endl;
        cout << "3. Search Creature" << endl;
        cout << "4. Preorder Traversal" << endl;
        cout << "5. Inorder Traversal" << endl;
        cout << "6. Postorder Traversal" << endl;
        cout << "7. Exit BST Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int power;
            cout << "Enter the creature's name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter the creature's power: ";
            cin >> power;
            bstRoot = insertBST(bstRoot, Creature(name, power));
            break;
        }
        case 2: {
            int power;
            cout << "Enter the power level to delete: ";
            cin >> power;
            bstRoot = deleteBST(bstRoot, power);
            break;
        }
        case 3: {
            int power;
            cout << "Enter the power level to search for: ";
            cin >> power;
            shared_ptr<Node> result = searchBST(bstRoot, power);
            if (result)
                cout << "Found: " << result->creature.name << " (Power: " << result->creature.power << ")" << endl;
            else
                cout << "Creature not found!" << endl;
            break;
        }
        case 4:
            cout << "Preorder Traversal (BST): ";
            preorder(bstRoot);
            cout << endl;
            break;
        case 5:
            cout << "Inorder Traversal (BST): ";
            inorder(bstRoot);
            cout << endl;
            break;
        case 6:
            cout << "Postorder Traversal (BST): ";
            postorder(bstRoot);
            cout << endl;
            break;
        case 7:
            bstRunning = false;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}

// Function to handle BT operations
// Handle BT operations
void handleBT(shared_ptr<Node>& btRoot) {
    int choice;
    bool btRunning = true;
    while (btRunning) {
        cout << "\n=== BT Menu ===" << endl;
        cout << "1. Insert Creature" << endl;
        cout << "2. Delete Creature" << endl;
        cout << "3. Search Creature" << endl;
        cout << "4. Preorder Traversal" << endl;
        cout << "5. Inorder Traversal" << endl;
        cout << "6. Postorder Traversal" << endl;
        cout << "7. Exit BT Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int power;
            cout << "Enter the creature's name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter the creature's power: ";
            cin >> power;
            insertBT(btRoot, Creature(name, power));
            break;
        }
        case 2: {
            int power;
            cout << "Enter the power level to delete: ";
            cin >> power;
            btRoot = deleteBT(btRoot, power); // Delete creature from BT
            break;
        }
        case 3: {
            int power;
            cout << "Enter the power level to search for: ";
            cin >> power;
            shared_ptr<Node> result = searchBT(btRoot, power); // Search for creature in BT
            if (result) {
                cout << "Found: " << result->creature.name << " (Power: " << result->creature.power << ")" << endl;
            } else {
                cout << "Creature not found!" << endl;
            }
            break;
        }
        case 4:
            cout << "Preorder Traversal (BT): ";
            preorderBT(btRoot); // Use preorder traversal for BT
            cout << endl;
            break;
        case 5:
            cout << "Inorder Traversal (BT): ";
            inorderBT(btRoot); // Use inorder traversal for BT
            cout << endl;
            break;
        case 6:
            cout << "Postorder Traversal (BT): ";
            postorderBT(btRoot); // Use postorder traversal for BT
            cout << endl;
            break;
        case 7:
            btRunning = false;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}

// Function to handle Heap operations
// Function to handle Heap operations
// Corrected function signature for handleHeap
void handleHeap(priority_queue<int>& maxHeap,
                priority_queue<int, vector<int>, greater<int>>& minHeap,
                vector<int>& powers,
                vector<Creature>& creatures) {
    int choice;
    bool heapRunning = true;
    while (heapRunning) {
        cout << "\n=== Heap Menu ===" << endl;
        cout << "1. Insert Creature to Max-Heap" << endl;
        cout << "2. Insert Creature to Min-Heap" << endl;
        cout << "3. Display Max-Heap" << endl;
        cout << "4. Display Min-Heap" << endl;
        cout << "5. Display Heapify" << endl;
        cout << "6. Exit Heap Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int power;
            cout << "Enter the creature's name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter the creature's power: ";
            cin >> power;
            addCreatureToMaxHeap(maxHeap, Creature(name, power));
            powers.push_back(power);  // Add power to the powers vector
            creatures.push_back(Creature(name, power)); // Also add creature to the creatures list
            break;
        }
        case 2: {
            string name;
            int power;
            cout << "Enter the creature's name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter the creature's power: ";
            cin >> power;
            addCreatureToMinHeap(minHeap, Creature(name, power));
            powers.push_back(power);  // Add power to the powers vector
            creatures.push_back(Creature(name, power)); // Also add creature to the creatures list
            break;
        }
        case 3: {
            cout << "Max-Heap: ";
            priority_queue<int> tempMaxHeap = maxHeap;
            while (!tempMaxHeap.empty()) {
                cout << tempMaxHeap.top() << " ";
                tempMaxHeap.pop();
            }
            cout << endl;
            break;
        }
        case 4: {
            cout << "Min-Heap: ";
            priority_queue<int, vector<int>, greater<int>> tempMinHeap = minHeap;
            while (!tempMinHeap.empty()) {
                cout << tempMinHeap.top() << " ";
                tempMinHeap.pop();
            }
            cout << endl;
            break;
        }
        case 5: {
            cout << "Heapify: ";
            if (powers.empty()) { // This checks if the 'powers' vector is empty
                cout << "No creatures to heapify." << endl;
            } else {
                cout << "Heapifying Creatures..." << endl;
                cout << "Max-Heap of Creature Powers: ";
                heapify_creatures(powers, true);  // Max-Heap
                cout << "Min-Heap of Creature Powers: ";
                heapify_creatures(powers, false);  // Min-Heap
            }
            break;
        }
        case 6:
            heapRunning = false;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}



// Main function to start the Creature Game
// Corrected call in playGame
void playGame() {
    shared_ptr<Node> bstRoot = nullptr;
    shared_ptr<Node> btRoot = nullptr;
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    vector<int> powers;
    vector<Creature> creatures;

    cout << "Welcome to the Creature Game!" << endl;
    cout << "You need to add at least 5 creatures to start.\n";

    // Input at least 5 creatures
    while (creatures.size() < 5) {
        string name;
        int power;
        cout << "Enter the creature's name: ";
        cin >> name;

        cout << "Enter the creature's power level: ";
        cin >> power;

        Creature newCreature(name, power);
        creatures.push_back(newCreature);
        bstRoot = insertBST(bstRoot, newCreature);  // BST insertion
        insertBT(btRoot, newCreature);              // BT insertion
        addCreatureToMaxHeap(maxHeap, newCreature); // Max-Heap insertion
        addCreatureToMinHeap(minHeap, newCreature); // Min-Heap insertion
        powers.push_back(power); // Add power to the powers vector
    }

    displayCreatures(creatures);

    bool gameRunning = true;
    while (gameRunning) {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Work with BST" << endl;
        cout << "2. Work with BT" << endl;
        cout << "3. Work with Heaps" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            handleBST(bstRoot);
            break;
        case 2:
            handleBT(btRoot);
            break;
        case 3:
            handleHeap(maxHeap, minHeap, powers, creatures); // Pass powers and creatures
            break;
        case 4:
            gameRunning = false;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}

int main() {
    playGame();


    cout<<"Thank you mwa!";
    return 0;
}


