#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Creates nodes for tree with name, id, left pointer, right pointer
struct Node {
    string sName;
    int sID;
    Node* left;
    Node* right;
        Node() {
            sName = "";
            sID = 0;
            left = nullptr;
            right = nullptr;
        }
        Node(string sName, int sID) {
            this->sName = sName;
            this->sID = sID;
            left = nullptr;
            right = nullptr;
        }
};
class avl {
private:
    Node* root;
public:
    //Default constructor
    avl() {
        root = nullptr;
    }
    //Removes a node from the tree
    Node* remove(Node* root, int id) {
       if(root == nullptr) {
           cout << "unsuccessful" << endl;
           return nullptr;
       }
       if(id > root->sID) {
           root->right = remove(root->right, id);
       }
       else if(id < root->sID) {
           root->left = remove(root->left, id);
       }
       else {
           if((root->right == nullptr) && (root->left == nullptr)) {
               delete root;
               root = nullptr;
               cout << "successful" << endl;
               return root;
           }
           else if(root->left == nullptr) {
               Node* temp = root;
               root = root->right;
               delete temp;
               cout << "successful" << endl;
               return root;
           }
           else if(root->right == nullptr) {
               Node* temp = root;
               root = root->left;
               delete temp;
               cout << "successful" << endl;
               return root;
           }
           //Goes to the inorder successor
           else {
               Node* temp = root->right;
               while (temp->left != nullptr) {
                   temp = temp->left;
               }
               root->sID = temp->sID;
               root->sName = temp->sName;
               root->right = remove(root->right, root->sID);
               return root;
           }
       }
       return root;
    }
    //Sort nodes in order and returns a vector with the nodes
    void inorderRemoveHelp(Node* root, vector<Node*>& res) {
        if (root == nullptr) {
            return;
        }
        inorderRemoveHelp(root->left, res);
        res.push_back(root);
        inorderRemoveHelp(root->right, res);
    }
    //Removes the specified node when nodes are inorder
    Node* removeInorder(Node* root, int n) {
        vector<Node*> nodes;
        inorderRemoveHelp(root, nodes);
        if(root == nullptr || (nodes.size() < (n + 1))) {
            cout << "unsuccessful" << endl;
            return root;
        }
        root = remove(root, nodes[n]->sID);
        return root;
    }
    //Sorts nodes in preorder and returns a vector with the nodes
    void preorderSearch(Node* root, string name, vector<Node*>& res) {
        if(root == nullptr) {
            return;
        }
        if(root->sName == name) {
            res.push_back(root);
        }
        preorderSearch(root->left, name, res);
        preorderSearch(root->right, name, res);
    }
    void search(Node* root, int id, string name, bool number) {
        if(root == nullptr) {
            cout << "unsuccessful" << endl;
            return;
        }
        //Searches for the ID and returns the name
        if(number) {
            if(id == root->sID) {
                cout << root->sName << endl;
                return;
            }
            else if(id > root->sID) {
                search(root->right, id, "", true);
            }
            else {
                search(root->left, id, "", true);
            }
        }
        else {
            //Goes through the vector with the nodes in preorder and prints the ID's of the names that match
            vector<Node*> ids;
            preorderSearch(root, name, ids);
            if(ids.size() == 0) {
                cout << "unsuccessful" << endl;
                return;
            }
            for(int i = 0; i < ids.size(); i++) {
                string z = "0";
                string tempString = to_string(ids.at(i)->sID);
                //Adds the leading 0's that are removed when using stoi()
                if(tempString.length() != 8) {
                    int zero = 8 - tempString.length();
                    while((zero - 1) > 0) {
                        z = z + "0";
                        zero--;
                    }
                    tempString = z + tempString;
                }
                cout << tempString << endl;
            }
        }
    }
    //Gets height
    int height(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        return 1 + max(height(root->left), height(root->right));
    }
    //Prints level count
    void printLevelCount(Node* root) {
        int count;
        if(root != nullptr) {
            count = height(root);
            cout << count << endl;
        }
        else {
            count = 0;
            cout << count << endl;
        }
    }
    //Returns vector with inorder traversal
    void inorderTraversal(Node* root, vector<string>& res) {
        if (root == nullptr) {
            return;
        }
        inorderTraversal(root->left, res);
        res.push_back(root->sName);
        inorderTraversal(root->right, res);
    }
    //Returns vector with preorder traversal
    void preorderTraversal(Node* root, vector<string>& res) {
        if (root == nullptr) {
            return;
        }
        res.push_back(root->sName);
        preorderTraversal(root->left, res);
        preorderTraversal(root->right, res);
    }
    //Returns vector with postorder traversal
    void postorderTraversal(Node* root, vector<string>& res) {
        if (root == nullptr) {
            return;
        }
        postorderTraversal(root->left, res);
        postorderTraversal(root->right, res);
        res.push_back(root->sName);
    }
    //Left rotation
    Node* rotateLeft(Node *node)
    {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        return rightChild;
    }
    //Right rotation
    Node* rotateRight(Node *node)
    {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        return leftChild;
    }
    //Rotates left node right
    Node* rotateLeftRight(Node *node)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    //Rotates right node left
    Node* rotateRightLeft(Node *node)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    //Gets balance factor
    int balance(Node* root) {
        if(root == nullptr) {
            return 0;
        }
        int bFactor = height(root->left) - height(root->right);
        return bFactor;
    }
    //Handles all the right rotations for insert
    Node* rRotations(Node* root, int id) {
        if(id < root->left->sID) {
            return rotateRight(root);
        }
        return rotateLeftRight(root);
    }
    //Handles all the left rotations for insert
    Node* lRotations(Node* root, int id) {
        if(id > root->right->sID) {
            return rotateLeft(root);
        }
        return rotateRightLeft(root);
    }
    //Inserts a node and balances the tree
    Node* insert(Node* root, string sName, int sID) {
        if(root == nullptr) {
            cout << "successful" << endl;
            return new Node(sName, sID);
        }
        if(root->sID < sID) {
            root->right = insert(root->right, sName , sID);
        }
        else if(root->sID > sID) {
            root->left = insert(root->left, sName, sID);
        }
        else {
            cout << "unsuccessful" << endl;
            return root;
        }
        int bFactor = balance(root);
        if(bFactor < -1) {
            return lRotations(root, sID);
        }
        if(bFactor > 1) {
            return rRotations(root, sID);
        }
        return root;
    }
    bool checkInt(string temp, bool n) {
        bool works = true;
        //Checks if it is a valid number for removeInorder
        if(n) {
            if(temp.length() != 0) {
                for(int i = 0; i < temp.length(); i++) {
                    if(!isdigit(temp[i])) {
                        works = false;
                        cout << "unsuccessful" << endl;
                        break;
                    }
                }
            }
            else {
                works = false;
                cout << "unsuccessful" << endl;
            }
        }
        //Checks if it is a valid ID number
        else {
            if(temp.length() == 8) {
                for(int i = 0; i < temp.length(); i++) {
                    if(!isdigit(temp[i])) {
                        works = false;
                        cout << "unsuccessful" << endl;
                        break;
                    }
                }
            }
            else {
                works = false;
                cout << "unsuccessful" << endl;
            }
        }
        return works;
    }
    //Checks if it is a valid name
    bool checkString(string temp) {
        bool works = true;
        for(int i = 0; i < temp.length(); i++) {
            if(!(isalpha(temp[i]) || (temp[i] == ' '))) {
                works = false;
                cout << "unsuccessful" << endl;
                break;
            }
        }
        return works;
    }
    //Manages user inputs
    void orgData(string line) {
        string firstWord = line.substr(0, line.find_first_of(' '));
        //Gets name and ID when user inputs insert
        if(firstWord == "insert") {
            try {
                string name = line.substr(line.find_first_of('"') + 1, (line.find_last_of('"'))-(line.find_first_of('"') + 1));
                string id = line.substr(line.find_last_of("\"") + 2, line.length());
                if(!name.empty()) {
                    if(checkInt(id,false) && checkString(name)) {
                        int tempNum = stoi(id);
                        root = insert(root ,name, tempNum);
                    }
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            catch(exception) {
                cout << "unsuccessful" << endl;
            }
        }
        //Gets ID when user inputs remove
        else if(firstWord == "remove") {
            string tempString = line.substr(line.find_first_of(' ') + 1, line.length());
            if(checkInt(tempString,false)) {
                int tempNum = stoi(tempString);
                root = remove(root, tempNum);
            }
        }
        //Gets name or ID depending on if there are quotes or not when user inputs search
        else if(firstWord == "search") {
            string tempString = line.substr(line.find_first_of(' ') + 1, 1);
            if(tempString == "\"") {
                tempString = line.substr(line.find_first_of('"') + 1, line.length());
                if(!tempString.empty()) {
                    tempString.pop_back();
                }
                string twoQuoteCheck = line.substr(line.find_first_of('"') + 1, (line.find_last_of('"'))-(line.find_first_of('"') + 1));
                if(tempString == twoQuoteCheck) {
                    if(checkString(tempString)) {
                        search(root, 0, tempString, false);
                    }
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            else {
                tempString = line.substr(line.find_first_of(' ') + 1, line.length());
                if(checkInt(tempString,false)) {
                    int tempNum = stoi(tempString);
                    search(root, tempNum, "", true);
                }
            }
        }
        //Prints inorder when user inputs command
        else if(firstWord == "printInorder") {
            vector<string> names;
            inorderTraversal(root, names);
            for(int i = 0; i < names.size(); i++) {
                cout << names.at(i);
                if(i < names.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        //Prints preorder when user inputs command
        else if(firstWord == "printPreorder") {
            vector<string> names;
            preorderTraversal(root, names);
            for(int i = 0; i < names.size(); i++) {
                cout << names.at(i);
                if(i < names.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        //Prints postorder when user inputs command
        else if(firstWord == "printPostorder") {
            vector<string> names;
            postorderTraversal(root, names);
            for(int i = 0; i < names.size(); i++) {
                cout << names.at(i);
                if(i < names.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        //Prints level count when user inputs command
        else if(firstWord == "printLevelCount") {
            printLevelCount(root);
        }
        //Calls removeInorder function when user inputs command
        else if(firstWord == "removeInorder") {
            string tempString = line.substr(line.find_first_of(' ') + 1, line.length());
            if(checkInt(tempString,true)) {
                int tempNum = stoi(tempString);
                root = removeInorder(root, tempNum);
            }
        }
        //When command is invalid
        else  {
            cout << "unsuccessful" << endl;
        }
    }
};
//Gets number of commands and ends code when all commands are executed
int main() {
    avl tree;
    int input;
    string line;
    getline(cin, line);
    input = stoi(line);

    while(getline(cin, line)) {
        tree.orgData(line);
        input--;
        if(input == 0) {
            break;
        }
    }
    return 0;
}