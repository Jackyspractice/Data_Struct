#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class collegeType{
    public:
        string number;//serial
        string school;//2
        string department;//4
        string dayclub;//5
        string level;//6
        string sNO;//7nuber of students
};

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
        cout << "Please input file name...\n";
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
            while(!file.eof()){
                getline(file, line, '\t');
                buffer.push_back(line);
                cout << line << "\n";
            }
            file.close();
        }
    }
}