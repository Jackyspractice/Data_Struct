#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;
class collegeType{
    public:
        int number;//serial
        string school;//2
        string department;//4
        string dayclub;//5
        string level;//6
        int sNO;//7nuber of students
};collegeType input;

struct node{
    collegeType data;
    int height;
    struct node* left;
    struct node* right;
};

node* insert(collegeType in, node* tree){
    if(tree == NULL){//當tree為空時，新增至root
        tree = new node;
        tree->data = in;
        tree->height = 0;
        tree->left = tree->right = NULL;
    }
    if(in.sNO < tree->data.sNO){//新增資料小於時，指派至左子樹
        tree->left = insert(in, tree->left);
    }
    
}


/*class AVL{
    struct node{
        collegeType data;
        int height;
        struct node* left;
        struct node* right;
    };
    node* root;
    node* insert(collegeType in, node* avl){
        if(avl == NULL){//當tree為空時，新增至root
            avl = new node;
            avl->data = in;
            avl->height = 0;
            avl->left = avl->right = NULL;
        }
        else if(in.sNO < avl->data.sNO){
            //新增資料小於其parent，插入其left
            avl->left = insert(in, avl->left);
            //判斷BF是否超出
            if
        }
    }
};*/

void store(int i, vector<string> &buffer, collegeType &input);
string check(string input);
void AVL_insert(collegeType &input);

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
                cout << i  << " = " << buffer[i] << "\n";
                i++;
            }
            file.close();


            if(which == 1){//23

            }





            else if(which == 2){//AVL
                int size = (buffer.size() - 1) / 10;
                cout << "size = " << size << "\n";
                cout << "buffersize = " << buffer.size() << "\n";
                if(size <= 0){
                    cout <<"there is no data legal\n";
                    return 0;
                }
                collegeType input[size];
                for(int i = 0; i < size; i++){
                    store(i, buffer, input[i]);
                    cout << "serial = " << input[i].number << ", sNO = " << input[i].sNO << "\n";
                    AVL_insert(input[i]);
                }



            }
        }
    }
}

void AVL_insert(collegeType &input){
    
}

void store(int i, vector<string> &buffer, collegeType &input){
    int whereis = i * 10 + 1;
    //if(i == 0 || i == 1) whereis++;
    input.number = i + 1;
    input.school = buffer[whereis];
    input.department = buffer[whereis + 2];
    input.dayclub = buffer[whereis + 3];
    input.level = buffer[whereis + 4];
    input.sNO = stoi(check(buffer[whereis + 5]));
    //cout << "serial = " << input.number << ", sNO = " << input.sNO << "\n";
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