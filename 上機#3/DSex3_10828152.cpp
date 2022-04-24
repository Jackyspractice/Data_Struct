//10828152 電機三甲 張泓傑
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class collegeType{
    public:
        int serial;
        string sid;
        string sname;
        int score[6];
        float avg;
};

class DataInput{
    public:
        vector<collegeType> cSet;

        void split(string *buffer, string line, char sp){
            string reg[9] = {"\0"};
            int k = 0;
            for(int i = 0; i < line.size(); i++){
                if(line[i] != sp){
                    reg[k] = reg[k] + line[i];
                }
                else{
                    buffer[k] = reg[k];
                    k++;
                }
            }
            buffer[8] = reg[8];
        }

        void store(int i, vector<string> buffer){
            collegeType data;
            data.serial = i + 1;
            cout << "data.serial = " << data.serial << "\t";
            data.sid = buffer[0 + i * 9];
            data.sname = buffer[1 + i * 9];

            cout << "data.sid = " << data.sid << "\t";
            cout << "data.sname = " << data.sname << "\t";

            int k = 0;
            for(int n = 2; n < 8; n++){
                data.score[k++] = stoi(buffer[n + i * 9]);
            }
            cout << "data.score[5] = " << data.score[5] << "\t";
            data.avg = stof(buffer[8 + i * 9]);
            cout << "data.avg = " << data.avg << "\n";
            cout << "buffer[9] = " << buffer[9] << "\n";
            cSet.push_back(data);
        }

        void inputtxtfile(){
            fstream file;
            string filename;
            string copy1 = "input";
            string copy2 = ".txt";
            cout << "input a file number:";
            cin >> filename;
            filename = copy1 + filename + copy2;
            file.open(filename, ios::in);
            if (!file.is_open()){
                cout << "There is no such file\n";
                return;
            }
            cSet.clear();
            string buffer[9];
            vector<string> buffer_split;
            buffer_split.clear();
            string line;

            while(!file.eof()){
                getline(file, line, '\n');

                
                split(buffer, line, '\t');

                for(int i = 0; i < 9; i++){
                    buffer_split.push_back(buffer[i]);
                    //cout << "buffer size = " << buffer.size() << endl;
                    cout << buffer[i] << "\t";
                }
                cout << "\n";
                //cout << line << "\n";
            }


            
            
            for(int i = 0; i < buffer_split.size() / 9; i++){
                store(i, buffer_split);
            }
            
        }
};

int main() {

    DataInput input;
    int command = 777;

    while(command != -1){
        cout << "Please input command[stop, mission0] = [-1. 0]:";
        cin >> command;
        switch(command){
            case 0:
                input.inputtxtfile();
                cout << input.cSet[2].sid << input.cSet[2].sname << endl;
                cout << "complete!!\n";
                break;
            default:
                cout << "command dosent exist!\n";
        }
    }
    
}