#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;

class collegeType{
    public:
        int serial;
        char sid[10] = {'\0'};
        char sname[10] = {'\0'};
        unsigned char score[6];
        float avg; //4byte
};

class DataInput{
    public:
        vector<collegeType> cSet;
        string filenumber;
        int data_size = 0;

        void store_char(char *to, string in){
            strcpy(to , in.c_str());
        }

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
            //cout << "data.serial = " << data.serial << "\t";

            store_char(data.sid, buffer[0 + i * 9]);
            store_char(data.sname, buffer[1 + i * 9]);

            //cout << "data.sid = " << data.sid << "\t";
            //cout << "data.sname = " << data.sname << "\t";

            int k = 0;
            for(int n = 2; n < 8; n++){
                data.score[k++] = stoi(buffer[n + i * 9]);
            }
            //cout << "data.score[5] = " << data.score[5] << "\t";
            data.avg = stof(buffer[8 + i * 9]);
            //cout << "data.avg = " << data.avg << "\n";
            //cout << "buffer[9] = " << buffer[9] << "\n";
            cSet.push_back(data);
        }

        void read_txt(){
            fstream file;
            string filename;
            string copy1 = "input";
            string copy2 = ".txt";
            cout << "input a file number:";
            cin >> filenumber;
            filename = copy1 + filenumber + copy2;
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
            data_size = 0;

            while(!file.eof()){//可以改成file.peek() != EOF 較好

                getline(file, line, '\n');


	            data_size++;
                if (line != "\0") split(buffer, line, '\t');
		        else data_size--;

                for(int i = 0; i < 9; i++){
                    buffer_split.push_back(buffer[i]);
                    //cout << "buffer size = " << buffer.size() << endl;
                    //cout << buffer[i] << "\t";
                }
                //cout << "\n";
            }

            for(int i = 0; i < data_size ; i++){
                store(i, buffer_split);
            }

            write_binary();
        }

        void write_binary(){
            string filename = "input" + filenumber + ".bin";
            ofstream bin_file(filename, ios::out | ios::binary);
            
            for(int i = 0; i < data_size; i++){
                bin_file.write(cSet[i].sid, sizeof(cSet[i].sid));
                bin_file.write(cSet[i].sname, sizeof(cSet[i].sname));
                for(int j = 0; j < 6; j++){
                    bin_file.write((char *)&cSet[i].score[j], sizeof(cSet[i].score[j]));
                }
                bin_file.write("", sizeof('0')*2);
                bin_file.write((char *)&cSet[i].avg, sizeof(float));
            }
            bin_file.close();

            cout << "write binary file successfully\n";
        }

        bool read_binary(){
            string filename;
            string copy1 = "input";
            string copy2 = ".bin";

            cout << "input a file number:";
            cin >> filenumber;
            filename = copy1 + filenumber + copy2;
            ifstream bin_file(filename, ios::in | ios::binary);


            if (!bin_file.is_open()){
                cout << "Only bin file, Please do 0 fisrt\n";
                return false;
            }

            cSet.clear();
            
            collegeType data_bin;
            char nothing[2];


            int k = 1;
            while(bin_file.peek() != EOF){

                data_bin.serial = k++;
                
                bin_file.read(data_bin.sid, sizeof(data_bin.sid));
                
                bin_file.read(data_bin.sname, sizeof(data_bin.sname));
                
                
                for (int i = 0; i < 6; i++){
                    bin_file.read((char *)&data_bin.score[i], sizeof(data_bin.score[i]));
                }
                
                bin_file.read(nothing, sizeof('\0') * 2);

                bin_file.read((char *)&data_bin.avg, sizeof(data_bin.avg));

                cSet.push_back(data_bin);
            }

            bin_file.close();
            return true;

        }

        void print_cSet(){
            for(int i = 0; i < cSet.size(); i++){
                    cout << cSet[i].serial << "\t";
                    cout << cSet[i].sid << "\t";
                    cout << cSet[i].sname << "\t";
                    for(int j = 0; j < 6; j++) cout << cSet[i].score[j] << "\t";
                    cout << cSet[i].avg << "\n";
                }
        }
};

class DH_table{
    public:
        int hash_value;
        char sid[10] = {'\0'};
        char sname[10] = {'\0'};
        float avg;
};

class DoubleHashing{
    public:
        vector<collegeType> data;

        int is_prime(int a){
            if (a == 1) return 0;
            else{
                for (int i = 2; i < a; i++){
                    if (a % i == 0) return 0;
                }
                return 1;
            }
        }

        int find_prime(int data_size){
            int max = int(data_size * 1.2) + 1;
            int ans = 0;
            
            while(1){
                if (is_prime(max) == 1){
                    ans = max;
                    break;
                }
                else max++;
            }

            return ans;
        }

        void bulid_hash_table(){
            int table_size = find_prime(data.size());
            //cout << "table_size = " << table_size << "\n";
            
        }
};

int main() {

    DataInput input;
    DoubleHashing DH;
    int command = 777;
    

    while(command != -1){
        bool type = true;
        cout << "Please input command[Stop, TXT to Binary, Linear Hashing, Double Hashing] = [-1, 0, 1, 2]:";
        cin >> command;
        switch(command){
            case 0:
                input.read_txt();
                cout << "bulid binary complete!!\n";
                break;

            case 1:
                break;

            case 2:
                type = input.read_binary();
                if (type == false)  continue;
                input.print_cSet();
                DH.data = input.cSet;
                DH.bulid_hash_table();


                break;

            case -1:
                break;

            default:
                cout << "command dosent exist!\n";
        }
    }
    
}