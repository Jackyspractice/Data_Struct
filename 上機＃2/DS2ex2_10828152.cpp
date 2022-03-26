#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;
class collegeType{
    public:
        int number;//serial
        string school;//2
        int department_number;//3
        string department;//4
        string dayclub;//5
        string level;//6
        int sNO;//7nuber of students
};collegeType input;

class node{
    public:
    collegeType data;
    vector<int> departnumber;//第一筆資料必為科系代碼，第二筆開始為相同科系後來加入的序號。
    int height;
    struct node* left;
    struct node* right;
};

node* insert(collegeType in, node* tree);
void store(int i, vector<string> &buffer, collegeType &input);
string check(string input);
int max(int a, int b) {return (a > b)? a : b;}
int height(node* n){ return (n == NULL)? 0 : n->height;}
int BF(node* x) {
    if(x == NULL) return 0;
    else return height(x->left) - height(x->right);
}
node* rr(node* y);
node* ll(node* x);
node* rl(node* x);
node* lr(node* x);

int main(){

    while(1){
        //which
        int which = 777;
        cout << "哈囉(Stop, 23Tree, AVL) = (0, 1, 2)\n";
        cin >> which;
        if (which == 0) return 0;
        else if (which != 1 && which != 2 && which != 3){
            cout << "Enter error!!!\n";
            continue;
        }
        //read file
        cout << "Please input file name...\nEX:204\n";
        ifstream file;
        string fileinput = "input";
        string filenumber;
        cin >> filenumber;
        string fileopen =  fileinput.append(filenumber);
        fileopen = fileopen.append(".txt");
        file.open(fileopen);
        vector<string> buffer;

        if(!file.is_open()){
            cout << "fail to open file\n";
        }

        else{
            string line;
            for(int i = 0; i < 3; i++) getline(file, line);
            int i = 0;
            while(!file.eof()){
                getline(file, line, '\t');
                buffer.push_back(line);
                //cout << i  << " = " << buffer[i] << "\n";
                i++;
            }
            file.close();


            if(which == 1){//23

            }


            else if(which == 2){//AVL
                int size = (buffer.size() - 1) / 10;
                cout << "size = " << size << "\n";
                //cout << "buffersize = " << buffer.size() << "\n";
                if(size <= 0){
                    cout <<"there is no data legal\n";
                    return 0;
                }
                collegeType input[size];
                node* root = NULL;
                for(int i = 0; i < size; i++){
                    cout << "input " << i + 1 << " data\n";
                    store(i, buffer, input[i]);
                    //cout << "insert input in root...\n";
                    root = insert(input[i], root);
                    cout << "serial = " << input[i].department_number << ", sNO = " << input[i].sNO << "\n";
                }

                cout << "root->departnumber.size() = " << root->departnumber.size() << "\n";
                cout << "tree height = " << height(root) << "\n";

                for(int i = 0; i < root->departnumber.size(); i++){
                    cout << root->departnumber[i] << "\n";
                }

            }
        }
    }
}

node* insert(collegeType in, node* tree){
    if(tree == NULL){//當tree為空時，新增至root
        tree = new node;
        tree->data = in;
        tree->departnumber.push_back(in.number);
        cout << "tree is null, departnumber is " << tree->departnumber[0] << "\n";
        tree->height = 1;
        tree->left = tree->right = NULL;
        return tree;
    }

    cout << "in depart is " << in.department_number << "\n";
    cout << "tree data depart is " << tree->data.department_number << "\n";

    if(in.department_number < tree->data.department_number){//新增資料小於時，指派至左子樹
        cout << "insert to left\n";
        tree->left = insert(in, tree->left);
    }
    else if(in.department_number > tree->data.department_number){//新增資料大於時，指派至右子樹
        cout << "insert to right\n";
        tree->right = insert(in, tree->right);
    }
    else{//新增資料等於時，表示科系相同，則紀錄序號
        cout << "input is the same depart, which serial is " << in.number << "\n";
        tree->departnumber.push_back(in.number);
    };

    //新增完後，更改parent的高度
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    //cout << tree->height;

    if(BF(tree) > 1 && in.department_number < tree->left->data.department_number) return rr(tree);
    if(BF(tree) < -1 && in.department_number > tree->right->data.department_number) return ll(tree);
    if(BF(tree) > 1 && in.department_number > tree->left->data.department_number) return lr(tree);
    if(BF(tree) < -1 && in.department_number < tree->right->data.department_number) return rl(tree);
    return tree;
}

node* rr(node* y){
    node* x = y->left;
    node* xr = x->right;

    x->right = y;
    y->left = xr;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node* ll(node* x){
    node* y = x->right;
    node* xr = y->left;

    y->left = x;
    x->right = xr;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return y;
}

node* rl(node* x){
    x->left = ll(x->left);
    return rr(x);
}

node* lr(node* x){
    x->right = rr(x->right);
    return ll(x);
}

void store(int i, vector<string> &buffer, collegeType &input){
    int whereis = i * 10 + 1;
    //if(i == 0 || i == 1) whereis++;
    input.number = i + 1;
    input.school = buffer[whereis];
    input.department_number = stoi(buffer[whereis + 1]);
    input.department = buffer[whereis + 2];
    input.dayclub = buffer[whereis + 3];
    input.level = buffer[whereis + 4];
    input.sNO = stoi(check(buffer[whereis + 5]));
    //cout << "serial = " << input.number << ", sNO = " << input.sNO << "\n";
    cout << "store finish\n";
}

string check(string input){
    for(int i = 0; i < input.length(); i++){
        if(input[i] < 48 || input[i] > 57){
            if(i == 0) input.erase(0, 1);
            else if(i == input.length() - 1) input[i] = '\0';
            else input.erase(i, 1);
        }
    }
    //cout << input << "\n";
    return input;
}