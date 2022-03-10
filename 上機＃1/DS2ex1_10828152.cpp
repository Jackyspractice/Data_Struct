//10828152 張泓傑 電機三甲
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>

using namespace std;

void heapRebuild(int root);
void heapinsert(int new_input);
void deapinsert(int new_input);
void min_maxheapinsert(int new_input);
void maxheapinsert(int mirro);
void minheapinsert(int mirro);
string check(string input);

class maxheap{
public:
    int size = 0;//我的資料總數，計算出的
    int sizeofstudent = 0;//初始化學生數陣列，一次一次累加，為了紀錄序號
    int **students = new int*[size];
};maxheap read;

int main(){
    while(1){

        //輸入判斷
        cout << "(Stop, Max Heap, Deap, min-Max Heap) = (0, 1, 2, 3): \n";
        int which = 100;
        cin >> which;
        if (which == 0) return 0;
        else if (which != 1 && which != 2 && which != 3){
            cout << "Enter error!!!\n";
            continue;
        }

        //將檔案中的資料去掉前3行，讀取除了'\t'以外的資料
        cout << "Please input file name...\nEx:input101\n";
        ifstream file;
        string line;
        char tab = '\t';
        string fileopen;
        cin >> fileopen;
        string filename = fileopen.append(".txt");
        file.open(filename);
        vector<string> buffer;

        if(!file.is_open()){
            cout << "fail to open file\n";
        }

        //主要程式開始
        else{

            for(int j = 0; j < 3; j++) getline(file, line);//略過檔案中的前3行
            while(!file.eof()){
                getline(file, line, tab);
                /*
                char charline[line.length()];
                char *ptrline;
                for(int i = 0; i < line.length(); i++) charline[i] = line[i]; 
                ptrline = strtok(charline, " \n");
                while(ptrline != NULL){
                    //cout << "line = " << ptrline << "\n";
                    buffer.push_back(ptrline);
                    ptrline = strtok(NULL, " ");
                }*/
                buffer.push_back(line);
            }
            file.close();


            //將讀取出的資料擷取出我要的學生數，其位置是第7/9個開始，下一個是往下10/14個
            read.size = (buffer.size() - 6) / 10 + 1;//計算有多少筆學生數
            //cout << "size = " << read.size << '\n';
            if (read.size <= 0){
                cout << "there is no data legal\n";
                return 0;
            }
            
            //max heap
            if(which == 1){
                read.students = new int*[read.size];//重新配置陣列大小
                read.sizeofstudent = 0;//重置陣列數
                for(int i = 0; i < read.size; i++) read.students[i] = new int[2];//宣告兩欄資料，一欄第一欄放學生數，二欄放序號

                for(int i = 6; i < buffer.size(); i += 10){
                    //cout << buffer[i] << "\n";
                    buffer[i] = check(buffer[i]);
                    //read.students[j] = buffer[i];
                    //read.students.push_back(buffer[i]);
                    //cout << buffer[i] << "\n";
                    
                    int intbuffer = stoi(buffer[i]); //將buffer裡的string 轉成 int，目的是要能夠宣告int的2維陣列
                    //Max Heap
                    heapinsert(intbuffer);
                    //Deap
                    //deapinsert(intbuffer);
                    //cout  << j + 1 << " = " << read.students[j] << "\n";
                    //j++;
                }buffer.clear();

                cout << "<MAX Heap>\n";
                cout << "serial = " << read.students[0][1] + 1 << ", root = " << read.students[0][0] << "\n";
                cout << "serial = " << read.students[read.size - 1][1] + 1 << ", bottom = " << read.students[read.size - 1][0] << "\n";

                //leftbottom 的位置
                int n = int(log2(read.size)); 
                int x = pow(2, n) - 1;
                cout << "serial = " << read.students[x][1] + 1 << ", leftbottom = " << read.students[x][0] << "\n";
                delete [] read.students;//釋出
                //system("pause");
            }

            else if(which == 2){
                read.size++;//要多一個，因root不用
                read.students = new int*[read.size];//重新配置陣列大小
                read.sizeofstudent = 0;//重置陣列數
                for(int i = 0; i < read.size; i++) read.students[i] = new int[2];//宣告兩欄資料，一欄第一欄放學生數，二欄放序號

                for(int i = 6; i < buffer.size(); i += 10){
                    buffer[i] = check(buffer[i]);
                    //cout << buffer[i] << "\n";
                    //read.students[j] = buffer[i];
                    //read.students.push_back(buffer[i]);
                    string toint = buffer[i];
                    int intbuffer = stoi(toint); //將buffer裡的string 轉成 int，目的是要能夠宣告int的2維陣列
                    //Max Heap
                    //heapinsert(intbuffer);
                    //Deap
                    deapinsert(intbuffer);
                    //cout  << j + 1 << " = " << read.students[j] << "\n";
                    //j++;
                }buffer.clear();

                cout << "<Deap>\n";
                cout << "serial = " << read.students[read.size - 1][1]<< ", bottom = " << read.students[read.size - 1][0] << "\n";

                //leftbottom 的位置
                int n = int(log2(read.size)); 
                int x = pow(2, n) - 1;
                cout << "serial = " << read.students[x][1]<< ", leftbottom = " << read.students[x][0] << "\n";
                delete [] read.students;
                //system("pause");
            }

            //min-max heap
            else if(which == 3){
                read.students = new int*[read.size];//重新配置陣列大小
                read.sizeofstudent = 0;//重置陣列數
                for(int i = 0; i < read.size; i++) read.students[i] = new int[2];//宣告兩欄資料，一欄第一欄放學生數，二欄放序號

                for(int i = 6; i < buffer.size(); i += 10){
                    buffer[i] = check(buffer[i]);
                    //cout << buffer[i] << "\n";
                    //read.students[j] = buffer[i];
                    //read.students.push_back(buffer[i]);
                    string toint = buffer[i];
                    int intbuffer = stoi(toint); //將buffer裡的string 轉成 int，目的是要能夠宣告int的2維陣列
                    //Max Heap
                    min_maxheapinsert(intbuffer);
                    
                }buffer.clear();

                cout << "<min-Max Heap>\n";
                //root
                cout << "serial = " << read.students[0][1] + 1 << ", root = " << read.students[0][0] << "\n";
                //bottom
                cout << "serial = " << read.students[read.size - 1][1] + 1 << ", bottom = " << read.students[read.size - 1][0] << "\n";
                //leftbottom
                int n = int(log2(read.size)); 
                int x = pow(2, n) - 1;
                cout << "serial = " << read.students[x][1] + 1 << ", leftbottom = " << read.students[x][0] << "\n";

                delete [] read.students;//釋出
                //system("pause");
            }
        }
    }
}

void min_maxheapinsert(int new_input){
    read.students[read.sizeofstudent][0] = new_input;//新增資料
    read.students[read.sizeofstudent][1] = read.sizeofstudent;//加入序號
    int place = read.sizeofstudent;
    //if(place == 1 || place == 0) place = -8;
    int parent = (read.sizeofstudent - 1) / 2;
    int layer = int(log2(read.sizeofstudent + 1));
    //判斷新增資料在奇數還偶數
    if((parent >= 0) && ((layer + 1) % 2 != 0)){//奇數min heap
        //再判斷是否大於其parent
        if(read.students[read.sizeofstudent][0] > read.students[parent][0]){
            swap(read.students[read.sizeofstudent][0], read.students[parent][0]);
            swap(read.students[read.sizeofstudent][1], read.students[parent][1]);

            place = parent;
            if(place == 1 || place == 0 || place == 2) place = -8;
            parent = (((place - 1) / 2) - 1) / 2;
            
            
            //cout << "place = " << place << ", serial of parent = " << read.sizeofstudent << ", parent = " << parent << "\n";

            while((parent >= 0) && (read.students[place][0] > read.students[parent][0])){
                swap(read.students[place][0], read.students[parent][0]);
                swap(read.students[place][1], read.students[parent][1]);
                place = parent;
                if(place == 1 || place == 0 || place == 2) place = -8;
                parent = (((place - 1) / 2) - 1) / 2;
            }
        }

        else if ((parent >= 0) && (read.students[read.sizeofstudent][0] < read.students[parent][0])){
            if(place == 1 || place == 0 || place == 2) place = -8;
            parent = (((place - 1) / 2) - 1) / 2;
            while((parent >= 0) && (read.students[place][0] < read.students[parent][0])){
                swap(read.students[place][0], read.students[parent][0]);
                swap(read.students[place][1], read.students[parent][1]);
                place = parent;
                if(place == 1 || place == 0 || place == 2) place = -8;
                parent = (((place - 1) / 2) - 1) / 2;
            }
        }
    }

    else if((parent >= 0) && ((layer + 1) % 2 == 0)){//偶數max heap
        //再判斷是否小於其parent
        if(read.students[read.sizeofstudent][0] < read.students[parent][0]){
            swap(read.students[read.sizeofstudent][0], read.students[parent][0]);
            swap(read.students[read.sizeofstudent][1], read.students[parent][1]);

            place = parent;
            if(place == 1 || place == 0 || place == 2) place = -8;
            parent = (((place - 1) / 2) - 1) / 2;

            while((parent >= 0) && (read.students[place][0] < read.students[parent][0])){
                swap(read.students[place][0], read.students[parent][0]);
                swap(read.students[place][1], read.students[parent][1]);
                place = parent;
                if(place == 1 || place == 0 || place == 2) place = -8;
                parent = (((place - 1) / 2) - 1) / 2;
            }
        }
        //沒有小於parent
        else if ((parent >= 0) && (read.students[read.sizeofstudent][0] > read.students[parent][0])){
            if(place == 1 || place == 0 || place == 2) place = -8;
            parent = (((place - 1) / 2) - 1) / 2;
            while((parent >= 0) && (read.students[place][0] > read.students[parent][0])){
                swap(read.students[place][0], read.students[parent][0]);
                swap(read.students[place][1], read.students[parent][1]);
                place = parent;
                if(place == 1 || place == 0 || place == 2) place = -8;
                parent = (((place - 1) / 2) - 1) / 2;
            }
        }
    }
    read.sizeofstudent++;
}

void deapinsert(int new_input){
    if (read.sizeofstudent == 0){
        read.sizeofstudent = 1;//去掉root
    }
    //int x = read.sizeofstudent; Debug中斷檢視read.sizeofstudent的值

    read.students[read.sizeofstudent][0] = new_input;//新增資料
    read.students[read.sizeofstudent][1] = read.sizeofstudent;//加入序號
    //判斷資料是新增在左子樹，還是右子樹
    int layer = int(log2(read.sizeofstudent + 1));
    //算出那一層tree的中間左值，方法為先找到那層的leftbottom位置，再向右位移pow(2, layer - 1) - 1即是中間左值
    int midleft = (pow(2, layer) - 1) + (pow(2, layer - 1) - 1);
    //如果新資料的位置小於等於中間左值，表示資料是新增在min heap
    if(read.sizeofstudent <= midleft){
        //先找出對應在max heap的位置，其值為mirro
        int mirro = read.sizeofstudent + pow(2, layer - 1);
        //先判斷mirro位置是否為空
        if(mirro > read.sizeofstudent) mirro = (mirro - 1) / 2; // 導向其parent
        //和mirro位比大小
        if(mirro > 0){//排除mirro為0的情況
            if(read.students[read.sizeofstudent][0] > read.students[mirro][0]){
                swap(read.students[read.sizeofstudent][0], read.students[mirro][0]);
                swap(read.students[read.sizeofstudent][1], read.students[mirro][1]);
                //新增資料被換至 max heap 的 mirro位
                maxheapinsert(mirro);
            }
            //新增資料沒有比 max heap 的 mirro位大，故和min heap的 parent比較
            else{
                minheapinsert(read.sizeofstudent);
            }
        }
    }
    //else在max heap，不會有mirro位置為空的問題
    else{
        int mirro = read.sizeofstudent - pow(2, layer - 1);
        if(read.students[read.sizeofstudent][0] < read.students[mirro][0]){
            swap(read.students[read.sizeofstudent][0], read.students[mirro][0]);
            swap(read.students[read.sizeofstudent][1], read.students[mirro][1]);
            //新增資料被換至 min heap 的 mirro位
            minheapinsert(mirro);
        }
        //新增資料沒有比 min heap 的 mirro位小，故和max heap的 parent比較
        else{
            maxheapinsert(read.sizeofstudent);
        }
    }
    //cout << "[ " << read.students[read.sizeofstudent][1] << " ] :" << read.students[read.sizeofstudent][0] << "\n"; 
    read.sizeofstudent++;
}

void minheapinsert(int insert){
    int place = insert;
    int parent = (place - 1) / 2;
    while((parent > 0) && (read.students[place][0] < read.students[parent][0])){
        swap(read.students[place][0], read.students[parent][0]);
        swap(read.students[place][1], read.students[parent][1]);
        place = parent;
        parent = (place - 1) / 2;
    }
}


void maxheapinsert(int insert){
    int place = insert;
    int parent = (place - 1) / 2;
    while((parent > 0) && (read.students[place][0] > read.students[parent][0])){
        swap(read.students[place][0], read.students[parent][0]);
        swap(read.students[place][1], read.students[parent][1]);
        place = parent;
        parent = (place - 1) / 2;
    }
}

void heapinsert(int new_input){
    read.students[read.sizeofstudent][0] = new_input;//新增資料
    read.students[read.sizeofstudent][1] = read.sizeofstudent;//加入序號
    int place = read.sizeofstudent;
    int parent = (place - 1) / 2;
    while((parent >= 0) && (read.students[place][0] > read.students[parent][0])){
        swap(read.students[place][0], read.students[parent][0]);
        swap(read.students[place][1], read.students[parent][1]);
        place = parent;
        parent = (place - 1) / 2;
    }
    read.sizeofstudent++;
}


//用錯的function，能將陣列直接轉為max heap，但其結果會與一筆筆新增不同
void heapRebuild(int root){
    int max = 2 * root + 1;
    if(max < read.size){
        int rightchild = max + 1;
        if((rightchild < read.size) && (read.students[rightchild][0] > read.students[max][0])){
            max = rightchild;
        } // 右邊子值大於左子值，故要跟root換的人是右邊
        if(read.students[root][0] < read.students[max][0]){
            swap(read.students[root][0], read.students[max][0]);
            swap(read.students[root][1], read.students[max][1]);
            heapRebuild(max);
        }
    }
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

