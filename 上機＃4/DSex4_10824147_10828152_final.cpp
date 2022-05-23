//10824147 蔡尚博 10828152 張泓傑
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<string.h>
#include<queue>
#include<algorithm>

using namespace std;

class NextData {
	public:
		char getID[10] ; // ID
		float weight ; //大到小
		NextData* next ;
};

typedef NextData* NextPtr ;

class Data {
	public:
		char putID[10] ;
		char getID[10] ;
		float weight ;
};

class Student {
    public:
	    char putID[10] ; // ID 小到大
    	bool visit;
		vector<int> child_where;
    	NextPtr head ;
};

class Filecontrol {
    public:

        vector<Data> bin_data;
        string filenumber;

        bool read_bin() {
                string filename;
                string copy1 = "pairs";
                string copy2 = ".bin";

                cout << "input a file number:";
                cin >> filenumber;
                filename = copy1 + filenumber + copy2;
                ifstream bin_file(filename, ios::in | ios::binary);


                if (!bin_file.is_open()) {
                    cout << "File: " << "pairs" << filenumber << ".bin doesn't exist, please retry." << endl ;
                    return false;
                }

                bin_data.clear();

                Data data_line;

                while(bin_file.peek() != EOF) {

                    bin_file.read(data_line.putID, sizeof(data_line.putID));

                    bin_file.read(data_line.getID, sizeof(data_line.getID));

                    bin_file.read((char *)&data_line.weight, sizeof(data_line.weight));

                    bin_data.push_back(data_line);
                }

                bin_file.close();
                return true;

            }

            void print_input() {
                for(int i = 0; i < bin_data.size(); i++) {
                    cout << bin_data[i].putID << "\t";
                    cout << bin_data[i].getID << "\t";
                    cout << bin_data[i].weight << "\n";
                }
            }

};

vector<Student>mainVec ;
vector<int> numberofchild;

class Adjacency {
    public:

        void Insert(NextPtr &head, Data data){
			if ( head == NULL ) {
				head = new NextData ;
				head->next = NULL ;
				strcpy( head->getID, data.getID ) ;
				head->weight = data.weight;
			}  

			else if ( head->weight >= data.weight ) 
				Insert( head->next, data ) ;

			else { 
				NextPtr temp = head ;
				head = new NextData ;
				head->next = temp ;
				strcpy( head->getID, data.getID ) ;
				head->weight = data.weight ;
			} 
		}

        int find_main(char *sid){
            if (mainVec.size() == 0) return -1;
            else {
                for (int i = 0 ; i < mainVec.size(); i++) {
                    if (strcmp(sid, mainVec[i].putID) == 0) return i;
                }
                return -1;
            }
        }

        void GraphBuildUp( string filenumber, vector<Data> Set ) {
            mainVec.clear();
            numberofchild.clear();
            Student Oneset;

            for (int i = 0; i < Set.size(); i++) {
                
                int where = find_main(Set[i].putID);

                if (where != -1) { //putID已經存在main，將新的getID及指派至其底下
                    Insert(mainVec[where].head, Set[i]);
                }

                else if (where == -1){  //main中還未存在此putID，新增其putID至main，同時指派其getID及weight
                    strcpy(Oneset.putID, Set[i].putID) ;
					Oneset.head = NULL ;
					mainVec.push_back(Oneset) ;
                    Insert(mainVec[mainVec.size() - 1].head, Set[i]);
                }
            }

			for (int i = 0; i < Set.size(); i++) {
				int where = find_main(Set[i].getID);
				if (where == -1) {
					strcpy(Oneset.putID, Set[i].getID) ;
					Oneset.head = NULL ;
					mainVec.push_back(Oneset) ;
				}
			}
            
            Sort( 0, mainVec.size()-1 ) ;
            Write( filenumber, mainVec , Set ) ;
        }


        void Write( string filenumber, vector<Student>mainVec , vector<Data>Set ){
			
			string pairs = "pairs" ;
			string txt = ".adj" ;
			string fname = pairs + filenumber + txt ;
			ofstream outp(fname) ;
			NextPtr tmp ;
			
			outp << "<<< There are " << mainVec.size() << " IDs in total. >>>" << endl ;
			for( int i = 0; i < mainVec.size(); i++ ){
				tmp = mainVec[i].head ;
				outp << "["  << (i + 1) << "] " << mainVec[i].putID << ": " << endl ;
				int n = 1 ;
				while( tmp != NULL ){
					outp << "\t(" << n << ") " << tmp->getID << "," << tmp->weight ; 
					tmp = tmp->next ;
					
					if( n%10 == 0 )
				        outp << "\n" ;
				    n++ ;
				}
				outp << "\n" ;
				numberofchild.push_back(n - 1);
			}
			outp << "<<< There are " << Set.size() << " nodes in total. >>>" << endl ;
			outp.close() ;
			
			cout << "<<< There are " << mainVec.size() << " IDs in total. >>>" << endl ;
			cout << "<<< There are " << Set.size() << " nodes in total. >>>" << endl ;
		}

        void Sort(int start, int end) {
			for (int i = end; i > start; i--) {
				for (int j = start; j < i; j++) {
					if (strcmp(mainVec[j].putID, mainVec[j + 1].putID) > 0) {
						swap(mainVec[j], mainVec[j + 1]);
					}
				}
			}
		}
};
class influence {
	public:
		
		deque<int> list;
        vector<int> influence_value;
		vector<Student> temp;
		

		void Clear(){
			list.clear();
			temp.clear();
			mainVec.clear();
			influence_value.clear();
			numberofchild.clear();
		}

		void reset_visit() {
			for (int i = 0; i < mainVec.size(); i++) {
				mainVec[i].visit = false;
			}
		}

		int findwhere(char *sid) {
			for( int i = 0; i < mainVec.size(); i++ ){
				if( strcmp(mainVec[i].putID, sid ) == 0 ){
					//cout << sid << "is at " << i << endl
					return i;
				}
			}
			return -1;
		}

		int findwhere_temp(char *sid) {
			for( int i = 0; i < temp.size(); i++ ){
				if( strcmp(temp[i].putID, sid ) == 0 ){
					//cout << sid << "is at " << i << endl
					return i;
				}
			}
			return -1;
		}

		void BFS(string filenumber) {

			int where = 0; //紀錄child在main的哪裡

			for (int i = 0; i < mainVec.size(); i++) {

				int value = 0; //紀錄influence value
				NextPtr tmp;
				
				list.push_back(i);
				mainVec[i].visit = true;
				//cout << "mark " << mainVec[i].putID << " is visited\n";
				
				while (!list.empty()) {

					int x = list.front();

					tmp = mainVec[x].head;
					list.pop_front();
					//cout << "pop head\n";
					
					for (int j = 0; j < numberofchild[x]; j++){
						where = findwhere(tmp->getID);
						

						if (where == -1) {
							Student missing;
							//cout << "missing\n";
							strcpy(missing.putID, tmp->getID);
							mainVec.push_back(missing);
							numberofchild.push_back(0);
						}

						else if (mainVec[where].visit == false){
							list.push_back(where);
							mainVec[where].visit = true;
							value++;
							mainVec[i].child_where.push_back(where);
						}

						tmp = tmp->next;

					}

					sort(mainVec[i].child_where.begin(), mainVec[i].child_where.begin() + mainVec[i].child_where.size()) ;

				}

				reset_visit(); //重設為沒visit過

				influence_value.push_back(value);

			}
			
			temp.assign(mainVec.begin(), mainVec.begin() + mainVec.size());

			Quicksort(influence_value, 0, influence_value.size() - 1);
			find_group_and_sort();
            Write(filenumber, mainVec, temp) ;
			Clear();
		}

		void find_group_and_sort() {
			int flag = 0;
			int temp = influence_value[0];
			int start = 0, diff = influence_value.size() - 1;
			for (int i = 1; i < mainVec.size(); i++) {
				if (temp != influence_value[i]) {
					//cout << "find diff, origin is " << temp << " next is " << influence_value[i] << endl;
					diff = i;
					Sort(start, diff - 1);
					temp = influence_value[i];
					start = diff;
					flag = 1;
				}
			}
			if (flag == 0) Sort(start, diff);
		}

		void Sort(int start, int end) {
			for (int i = end; i > start; i--) {
				for (int j = start; j < i; j++) {
					if (strcmp(mainVec[j].putID, mainVec[j + 1].putID) > 0) {
						swap(mainVec[j], mainVec[j + 1]);
					}
				}
			}
		}

        void Write(string filenumber, vector<Student> &mainVec, vector<Student> &temp){
			
			string pairs = "pairs" ;
			string txt = ".cnt" ;
			string fname = pairs + filenumber + txt ;
			ofstream outp(fname) ;
			NextPtr tmp ;
			
			outp << "<<< There are " << mainVec.size() << " IDs in total. >>>" << endl ;
			for( int i = 0; i < mainVec.size(); i++ ){
				tmp = mainVec[i].head ;
				outp << "["  << (i + 1) << "] " << mainVec[i].putID << ": ";
                outp << "( " << influence_value[i] << " )" << endl;
				int n = 1 ;
				int where = findwhere_temp(mainVec[i].putID);
				for (int j = 0; j < temp[where].child_where.size(); j++) {
					int loc = temp[where].child_where[j];
					outp << "\t(" << j + 1 << ") " << temp[loc].putID ;
					if( n%10 == 0 )
				        outp << "\n" ;
				    n++ ;
				}
				outp << "\n" ;
			}
			outp.close() ;
			
			cout << "<<< There are " << mainVec.size() << " IDs in total. >>>" << endl ;

			
		}

		int Partition(vector<int> &a, int front, int end){
			int pivot = a[end];
			int i = front;
			for (int j = front; j < end; j++){
				
				if (a[j] > pivot){
					swap(a[i], a[j]);
					swap(mainVec[i], mainVec[j]);
					i++;
				}
				
			}
			
			swap(a[i], a[end]);
			swap(mainVec[i], mainVec[end]);
			return i;
		}

		void Quicksort(vector<int> &a, int front, int end){
			if (front < end){
				int pivot = Partition(a, front, end);
				Quicksort(a, front, pivot - 1);
				Quicksort(a, pivot + 1, end);
    		}
		}

        
};

int main(){
    Filecontrol input;
    Adjacency adj;
    influence inf;

    int command = 777;

    while (command != 0) {
        bool type = true;
		cout << endl << "***** Influence on a Graph *****" ;
		cout << endl << "(0. QUIT )";
		cout << endl << "* 1. Build adjacency list      *" ;
		cout << endl << "* 2. Compute influence values  *" ;
		cout << endl << "* 3. ?                         *" ;
		cout << endl << "********************************";
		cout << endl << "Input a command( 0, 1, 2, 3 ):" ;

        cin >> command;
        switch (command) {
            case 1:

                type = input.read_bin() ;
				if( type == false ) break ;
				adj.GraphBuildUp( input.filenumber, input.bin_data ) ;
				
                break;

            case 2:

                if( input.bin_data.empty() ) {
					cout << "choose 1 first!" << endl ;
				} else {
					inf.BFS(input.filenumber);
				}

                break;

            case 0:

                break;

            default:
                cout << "command doesn't exist!\n";
        }
    }
}
