//IMPORTANT: WRITTEN ON XCODE. PLEASE COMPILE IT THROUGH XCODE.
//IMPORTANT: OPEN TXT FILE WITH THE NAME OF "input.txt".

//NAME: EMİR
//SURNAME: BALKAN

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<algorithm>
using namespace std;

struct Node {
    vector<int> numArrays;
    Node* down;
    Node* up;
};

void is_fail(ifstream & file) {
    if (file.fail()) {
        cout << "File could not be opened" << endl;
    }
}

void open_file(ifstream & file, string & filename) {
    file.open(filename.c_str());
    is_fail(file);
}

void create_a_new_node(Node* &n, Node* & t, Node* &h, int &lineCount) {
    n = new Node;
    if (t == NULL)
    {
        if (lineCount > 1)
        {
            h->down = n;
            n->up = h;
        }
        h = n;
        t = n;
        t->down = NULL;
       
    }
    else {
        t->down = n;
        n->up = t;
        t = n;
        t->down = NULL;
    }
}

void add_num_into_node(int & number, Node* & t) {
    t->numArrays.push_back(number);
}

void get_number(string &line, Node* & t , Node* & n) {
    int number;
    istringstream s(line);
    while(s >> number) {
        add_num_into_node(number, t);
    }
}

bool is_prime(int & choice) {
    for (int i = 2; i < choice; i++) {
        if (choice % i == 0) {
            return false;
        }
    }
    return true;
}
    
    
    
void convert_primes_zero(Node* & h)
{
    for (int i = 0; i < h->numArrays.size(); i++) {
        if (is_prime(h->numArrays[i])) {
            h->numArrays[i] = 0;
        }
    }
}
    
int make_comparison(int & index, Node* & h, int & total)
{
    if (h->numArrays.size() != 1)
    {
        h = h->up;
    }
    else{
        return total;
    }
    cout << "index: " << index << endl;
    if (index == 0 || index == h->numArrays.size())
    {
        if (index == 0) {
            if (is_prime(h->numArrays[index])) {
                total = 0;
                cout << "total is reseted." << endl;
                while (h->down != NULL) {
                    h = h->down;
                }
                return total;
            }
            total += h->numArrays[index];
            cout << h->numArrays[index] << " is addded to total." << endl;
        }
        else
        {
            if (is_prime(h->numArrays[index - 1])) {
                total = 0;
                cout << "total is reseted." << endl;
                while (h->down != NULL) {
                    h = h->down;
                }
                return total;
            }
            total += h->numArrays[index - 1];
            cout << h->numArrays[index - 1] << " is addded to total." << endl;
            index--;
        }
        make_comparison(index, h, total);
    }
    else
    {
        if (h->numArrays[index - 1] > h->numArrays[index])
        {
            cout << h->numArrays[index - 1] << " is addded to total." << endl;
            total += h->numArrays[index - 1];
            index--;
        }
        else
        {
            if (h->numArrays[index] == 0 && h->numArrays[index - 1] == 0)
            {
                total = 0;
                cout << "total is reseted." << endl;
                while (h->down != NULL) {
                    h = h->down;
                }
                return total;
            }
            cout << h->numArrays[index] << " is addded to total." << endl;
            total += h->numArrays[index];
        }
        make_comparison(index, h, total);
    }
    
        
    return total;
}

void find_max_sum(Node* & h)
{
    int choice1;
    int choice2;
    int total = 0;
    int index;
    convert_primes_zero(h);
    
    for (int i = 0; i < h->numArrays.size() - 1; i++)
    {
        choice1 = h->numArrays[i];
        choice2 = h->numArrays[i + 1];
        if (choice1 == 0 && choice2 == 0)
        {
            continue;
        }
        else
        {
            if (choice1 > choice2) //Problem is here, When we compare two num and take bigger one we are ignoring the fact that other path could has bigger total at the top of the pyramid.
            {
                cout << choice1 << " is addded to total." << endl;
                total += choice1;
                index = i;
                
            }
            else
            {
                cout << choice2 << " is addded to total." << endl;
                total += choice2;
                index = i + 1;
               
            }
            total = make_comparison(index, h, total);
            if (total == 0) {
                continue;
            }
            else
            {
                cout << total << endl;
            }
        }
    }
}


void get_line(ifstream & file, Node* & t, Node* & n,  Node* & h){
    string line;
    int lineCount = 0;
    while (getline(file, line)) {
        if (!line.empty()) {
            lineCount++;
            create_a_new_node(n, t ,h, lineCount);
            get_number(line, t, n);
        }
        t = NULL;
        
    }
    find_max_sum(h);
}








int main() {
    ifstream file;
    string filename = "input.txt";
    Node* n = NULL;
    Node* t = NULL;
    Node* h = NULL;
    open_file(file, filename);
    
    get_line(file ,t ,n ,h);
    file.close();
    
    return 0;
}


