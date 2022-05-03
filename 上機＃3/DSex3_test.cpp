//10828152 πqæ˜§T•“ ±i™l≥« 10824147 πq∏Í§T Ω≤©|≥’
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <iomanip> //setw()
#include <chrono>
#include <sys/timeb.h>
using namespace std;

class collegeType {
	public:
		int serial;
		char sid[10] = {'\0'};
		char sname[10] = {'\0'};
		unsigned char score[6];
		float avg; //4byte
};

string filenumber;

class DataInput {
	public:
		vector<collegeType> cSet;
		int data_size = 0;

		void store_char(char *to, string in) {
			strcpy(to , in.c_str());
		}

		void split(string *buffer, string line, char sp) {
			string reg[9] = {"\0"};
			int k = 0;
			for(int i = 0; i < line.size(); i++) {
				if(line[i] != sp) {
					reg[k] = reg[k] + line[i];
				} else {
					buffer[k] = reg[k];
					k++;
				}
			}
			buffer[8] = reg[8];
		}

		void store(int i, vector<string> buffer) {
			collegeType data;
			data.serial = i + 1;
			//cout << "data.serial = " << data.serial << "\t";

			store_char(data.sid, buffer[0 + i * 9]);
			store_char(data.sname, buffer[1 + i * 9]);

			//cout << "data.sid = " << data.sid << "\t";
			//cout << "data.sname = " << data.sname << "\t";

			int k = 0;
			for(int n = 2; n < 8; n++) {
				data.score[k++] = stoi(buffer[n + i * 9]);
			}
			//cout << "data.score[5] = " << data.score[5] << "\t";
			data.avg = stof(buffer[8 + i * 9]);
			//cout << "data.avg = " << data.avg << "\n";
			//cout << "buffer[9] = " << buffer[9] << "\n";
			cSet.push_back(data);
		}

		void read_txt() {
			fstream file;
			string filename;
			string copy1 = "input";
			string copy2 = ".txt";
			cout << "input a file number:";
			cin >> filenumber;
			filename = copy1 + filenumber + copy2;
			file.open(filename, ios::in);
			if (!file.is_open()) {
				cout << "There is no such txt file\n";
				
			} else {

				cSet.clear();
				string buffer[9];
				vector<string> buffer_split;
				buffer_split.clear();
				string line;
				data_size = 0;

				while(!file.eof()) { //ÂèØ‰ª•ÊîπÊàêfile.peek() != EOF ËºÉÂ•Ω

					getline(file, line, '\n');


					data_size++;
					if (line != "\0") split(buffer, line, '\t');
					else data_size--;

					for(int i = 0; i < 9; i++) {
						buffer_split.push_back(buffer[i]);
						//cout << "buffer size = " << buffer.size() << endl;
						//cout << buffer[i] << "\t";
					}
					//cout << "\n";
				}

				for(int i = 0; i < data_size ; i++) {
					store(i, buffer_split);
				}

				write_binary();
			}
		}

		void write_binary() {
			string filename = "input" + filenumber + ".bin";
			ofstream bin_file(filename, ios::out | ios::binary);

			for(int i = 0; i < data_size; i++) {
				bin_file.write(cSet[i].sid, sizeof(cSet[i].sid));
				bin_file.write(cSet[i].sname, sizeof(cSet[i].sname));
				for(int j = 0; j < 6; j++) {
					bin_file.write((char *)&cSet[i].score[j], sizeof(cSet[i].score[j]));
				}
				bin_file.write("", sizeof('0')*2);
				bin_file.write((char *)&cSet[i].avg, sizeof(float));
			}
			bin_file.close();

			cout << "Write binary file successfully!\n";
		}

		bool read_binary() {
			string filename;
			string copy1 = "input";
			string copy2 = ".bin";

			cout << "input a file number:";
			cin >> filenumber;
			filename = copy1 + filenumber + copy2;
			ifstream bin_file(filename, ios::in | ios::binary);


			if (!bin_file.is_open()) {
				cout << "Only txt file, Please do 0 fisrt\n";
				return false;
			}

			cSet.clear();

			collegeType data_bin;
			char nothing[2];


			int k = 1;
			while(bin_file.peek() != EOF) {

				data_bin.serial = k++;

				bin_file.read(data_bin.sid, sizeof(data_bin.sid));

				bin_file.read(data_bin.sname, sizeof(data_bin.sname));


				for (int i = 0; i < 6; i++) {
					bin_file.read((char *)&data_bin.score[i], sizeof(data_bin.score[i]));
				}

				bin_file.read(nothing, sizeof('\0') * 2);

				bin_file.read((char *)&data_bin.avg, sizeof(data_bin.avg));

				cSet.push_back(data_bin);
			}

			bin_file.close();
			return true;

		}

		void print_cSet() {
			for(int i = 0; i < cSet.size(); i++) {
				cout << cSet[i].serial << "\t";
				cout << cSet[i].sid << "\t";
				cout << cSet[i].sname << "\t";
				for(int j = 0; j < 6; j++) cout << cSet[i].score[j] << "\t";
				cout << cSet[i].avg << "\n";
			}
		}
};

class HashData {
	public:
		int hval ;
		char sid[10] ;
		char sname[10] ;
		float avg ;
		bool empty = true ;
};

class Linear {

	public:

		int size ;
		
		

		void BuildHash( vector<collegeType> &cSet, int fname ) {

			

			int NumOfStudent = cSet.size() ;
			double Success = 0.000 ;
			double Unsucc = 0.000 ;
			double HashSizeDouble = NumOfStudent * 1.2 ;
			int HashSize = GetPrime( HashSizeDouble ) ;
			// cout << HashSize << endl ;
			size = HashSize ;



			HashData Primer[HashSize] ;

			


			for( int i = 0; i < cSet.size(); i++ ) {
				bool InputSuccess = false ;
				int key = Key( cSet[i].sid, HashSize ) ;
				int hvalue = key ;

				while( InputSuccess == false ) {
					if( Primer[key].empty == true ) {
						Primer[key].hval = hvalue ;
						strcpy( Primer[key].sid, cSet[i].sid ) ;
						strcpy( Primer[key].sname, cSet[i].sname ) ;
						Primer[key].avg = cSet[i].avg ;
						Primer[key].empty = false ;
						InputSuccess = true ;
					} // ß‰®Ï®√øÈ§J
					else {
						if( key == HashSize - 1 )
							key = 0 ;
						else
							key++ ;
					}

					Success++ ;
				}

			}
			// cout << Success << "/" << NumOfStudent << endl ;
			Success = Success / NumOfStudent ;

			Unsucc = Unsuccess( Primer ) ;


			WriteFile( Primer, fname, Success, Unsucc ) ;

		} // void buildhash

		int Key( char sid[], int hashsize ) {
			long long int key = 1 ;
			for( int i = 0; i < strlen(sid); i++ ) {
				key = key * sid[i] ;
			}

			return key%hashsize ;
		} // int key

		int GetPrime( int n ) {
			int i ;
			int j ;
			i = n ;
			while(true) {
				i++ ;
				for( j = 2; j <= i; j++ ) {
					if( i == j ) {
						return i ;
					} else if( i%j == 0 ) {
						break ;
					}
				}

			}
		} // getprime ®˙1.2≠ø´·≥Ã§pΩËº∆

		void WriteFile( HashData primer[], int fname, double success, double unsuccess ) {

			string name( std::to_string(fname) ) ;
			string FileName = "linear" + name + ".txt" ;
			ofstream outp(FileName) ;
			outp << "--- Hash Table X --- (linear probing)" << endl ;

			for( int i = 0; i < size; i++ ) {
				outp << "[" << i << "]" ;
				if( primer[i].empty == true ) {
					outp << "\n" ;
				} else {
					outp << "\t" << primer[i].hval << "\t" << "," << primer[i].sid << "\t" << "," << primer[i].sname << "\t" << "," << primer[i].avg << endl ;
				}

			}
			outp.close() ;

			cout << "Hash Table X has been created." << endl ;
			cout << "Unsuccessful search : " << unsuccess << " comparisons on average." << endl ;
			cout << "Successful search : " << success << " comparisons on average."<< endl ;
			

		} // void write

		double Unsuccess( HashData primer[] ) {
			
			double range = 0.000 ;
			double all = 0.000 ;
			for( int i = 0; i < size ; i++ ) {
				if( primer[i].empty == false ) {
					for( int j = i; primer[j].empty == false; j++ ) {
						range++ ;
						if( j == size -1 )
							j = -1 ;
					}
					all = all + range ;
					range = 0.000 ;
				} else {
					all = all + range ;
					range = 0.000 ;
				}
			}
			

			// cout << all << "/" << size << endl ;
			

			return all = all/size ;

		} // Unsuccess

};

class DH_table {
	public:
		int hash_value = -1;
		char sid[10] = {'\0'};
		char sname[10] = {'\0'};
		float avg = 0;
		int flag = 0;//Á¥ÄÈåÑÁ©∫ÈñìÂÖßÊúâÁÑ°Ë≥áÊñô
};

class DoubleHashing {
	public:
		vector<collegeType> data;
		int table_size = 0;
		vector<DH_table> table;

		int is_prime(int a) {
			if (a == 1) return 0;
			else {
				for (int i = 2; i < a; i++) {
					if (a % i == 0) return 0;
				}
				return 1;
			}
		}

		int find_prime(int data_size) {
			int max = data_size + 1;
			int ans = 0;

			while(1) {
				if (is_prime(max) == 1) {
					ans = max;
					break;
				} else max++;
			}

			return ans;
		}

		void build_table() {
			DH_table null_data;
			int max = int(data.size() * 1.2) + 1;
			table_size = find_prime(max);
			//cout << "table size = " << table_size << endl;
			for(int i = 0; i < table_size; i++) {
				table.push_back(null_data);
			}
			//cout << "table actual size = " << table.size() << endl;
		}

		int hash_function1(char *id) {
			int sum = 1;
			for (int i = 0; i < 10; i++) {
				if (id[i] >= '0' && id[i] <= '9') {
					sum *= id[i];
					if (sum >= table_size) {
						sum = sum % table_size;
					}
				}
			}
			return sum;
		}

		int hash_function2(char *id) {
			int Max_step = find_prime(data.size() / 3);
			//cout << "Max_step = " << Max_step << endl;
			int ans = 0;
			int sum = 1;
			for (int i = 0; i < 10; i++) {
				if (id[i] >= '0' && id[i] <= '9') {
					sum *= id[i];
					if (sum >= Max_step) {
						sum = sum % Max_step;
					}
				}
			}

			ans = Max_step - sum;
			return ans;
		}

		void store(collegeType data_store, int start, int orign, int step) {


			if (table[start].flag == 0) {

				//cout << "flag == 0\n";
				table[start].hash_value = orign;
				strcpy(table[start].sid, data_store.sid);
				//cout << table[start].sid << "\t" << data_store.sid << endl;
				strcpy(table[start].sname, data_store.sname);
				//cout << table[start].sname << "\t" << data_store.sname << endl;
				table[start].avg = data_store.avg;
				//cout << table[start].avg << '\t' << data_store.avg << endl;
				//cout << table[start].sname << "store to " << start << endl;
				table[start].flag = 1;

			} else if (table[start].flag == 1) {

				//cout << "flag == 1\n";
				int next = start + step;
				if (next >= table_size) next = next % table_size;
				store(data_store, next, orign, step);

			}

		}

		void hash_insert() {
			build_table();
			int start = 0;
			int step = 0;
			for (int i = 0; i < data.size(); i++) {
				//cout << data[i].sname << endl;
				start = hash_function1(data[i].sid);
				//cout << i << " start = " << start << endl;
				step = hash_function2(data[i].sid);
				//cout << i << " step = " << step << endl;

				store(data[i], start, start, step);

			}


			/*for (int i = 0; i < table_size; i++) {
				cout << i << "\t" << table[i].hash_value << "\t";
				cout << table[i].sid << "\t" << table[i].sname << "\t";
				cout << table[i].avg << '\n';
			}*/

		}

		bool compare_char(char *a, char *b) {
			int times = 0;
			for (int i = 0; i < 10; i++) {
				if (a[i] == b[i]) {
					if (i == 9) return true;
				} else {
					return false;
				}
			}
		}

		void search() {
			int *search_times = new int [data.size()];
			for (int i = 0; i < data.size(); i++) {
				search_times[i] = 0;
				int start = hash_function1(data[i].sid);
				int step = hash_function2(data[i].sid);

				//cout << "data = " << data[i].sid << "\ttable_data = " << table[start].sid << endl;

				while(1) {

					search_times[i]++;

					if (compare_char(data[i].sid, table[start].sid)) {
						//cout << "found!\n";
						break;
					} else {
						//cout << "not found\n";
						start = start + step;
						if (start >= table_size) start = start % table_size;
					}
				}

			}


			int sum = 0;
			double success = 0.0000;

			for (int i = 0; i < data.size(); i++) {
				sum += search_times[i];
				//cout << i << "\tsearch times = " << search_times[i] << endl;
			}

			success = double(sum) / double(data.size());

			cout << setprecision(4) << fixed << "successful search: " << success << " comparisons on average." << endl;
		}

		void write_to_file() {
			ofstream file;
			string filename = "double" + filenumber + ".txt";
			file.open(filename);

			file << " --- Hash Table Y --- (double hashing)\n";

			for (int i = 0; i < table.size(); i++) {


				if (table[i].hash_value == -1) {

					file << "[" << setw(3) << right << i << "]\n";

				} else {
					file << "[" << setw(3) << right << i << "]\t";

					file << table[i].hash_value << "\t";
					file << setw(10) << right << table[i].sid << "\t";
					file << setw(10) << right << table[i].sname << "\t";
					file << setw(5) << right << table[i].avg << "\n";

				}

			}

			file.close();
			table.clear();

			cout << "Hash table Y has been created.\n";


		}

};

class Quadratic{
	
	public:

		int size ;
		
		void BuildHash( vector<collegeType> &cSet, int fname ) {

			
			int NumOfStudent = cSet.size() ;
			double Success = 0.000 ;
			double Unsucc = 0.000 ;
			double HashSizeDouble = NumOfStudent * 1.2 ;
			int HashSize = GetPrime( HashSizeDouble ) ;
			// cout << HashSize << endl ;
			size = HashSize ;

			HashData Primer[HashSize] ;

			


			for( int i = 0; i < cSet.size(); i++ ) {
				bool InputSuccess = false ;
				int key = Key( cSet[i].sid, HashSize ) ;
				int hvalue = key ;
                int n = 0 ;
				while( InputSuccess == false ) {
					if( Primer[key].empty == true ) {
						Primer[key].hval = hvalue ;
						strcpy( Primer[key].sid, cSet[i].sid ) ;
						strcpy( Primer[key].sname, cSet[i].sname ) ;
						Primer[key].avg = cSet[i].avg ;
						Primer[key].empty = false ;
						InputSuccess = true ;
					} // ß‰®Ï®√øÈ§J
					else {
					    Success++ ;
					    n++ ;
					    key = hvalue +(n*n) ;
						while( key >= HashSize ){
							key = key % HashSize ;
						}
							
					}

					
				}
                Success++ ;
			}
			// cout << Success << "/" << NumOfStudent << endl ;
			Success = Success / NumOfStudent ;

			

			Unsucc = Unsuccess( Primer ) ;

			WriteFile( Primer, fname, Success, Unsucc ) ;

		} // void buildhash

		int Key( char sid[], int hashsize ) {
			long long int key = 1 ;
			for( int i = 0; i < strlen(sid); i++ ) {
				key = key * sid[i] ;
			}

			return key%hashsize ;
		} // int key

		int GetPrime( int n ) {
			int i ;
			int j ;
			i = n ;
			while(true) {
				i++ ;
				for( j = 2; j <= i; j++ ) {
					if( i == j ) {
						return i ;
					} else if( i%j == 0 ) {
						break ;
					}
				}

			}
		} // getprime ®˙1.2≠ø´·≥Ã§pΩËº∆

		void WriteFile( HashData primer[], int fname, double success, double unsuccess ) {

			string name( std::to_string(fname) ) ;
			string FileName = "quadratic" + name + ".txt" ;
			ofstream outp(FileName) ;
			outp << "--- Hash Table Z --- (quadratic probing)" << endl ;

			for( int i = 0; i < size; i++ ) {
				outp << "[" << i << "]" ;
				if( primer[i].empty == true ) {
					outp << "\n" ;
				} else {
					outp << "\t" << primer[i].hval << "\t" << "," << primer[i].sid << "\t" << "," << primer[i].sname << "\t" << "," << primer[i].avg << endl ;
				}

			}
			outp.close() ;

			cout << "Hash Table Z has been created." << endl ;
			cout << "Unsuccessful search : " << unsuccess << " comparisons on average." << endl ;
			cout << "Successful search : " << success << " comparisons on average."<< endl ;

		} // void write

		double Unsuccess( HashData primer[] ) {

		

			
			double range = 0.000 ;
			double all = 0.000 ;
			int n = 0 ;
			int temp = 0 ;
			
			for( int i = 0; i < size ; i++ ) {
				n = 0;
				if( primer[i].empty == false ) {
					n++ ;
					temp = i + (n*n) ;
					while( temp >= size ){
					    temp = temp % size ;
					}
					while( primer[temp].empty == false ){//???
						range++ ;
						n++;
						temp = i + (n*n) ;
						while( temp >= size ) temp = temp % size ;
					}
					range++;
						
					} 
					all = all + range ;
					range = 0.000 ;	
					
					
				} 

			
				
			

			// cout << all << "/" << size << endl ;
			
		
			
			return all = all/size ;

		} // Unsuccess
	
};

int main() {

	DataInput input;
	Linear linear ;
	DoubleHashing DH;
	Quadratic q ;
	std::chrono::steady_clock::time_point t1;
	std::chrono::steady_clock::time_point t2;

	int command = 777;
	int fname ;

	while(command != -1) {
		bool type = true;
		cout << endl << "******** Hash Table ********";
		cout << endl << "(-1. QUIT )";
		cout << endl << "* 0. txt to binary  *" ;
		cout << endl << "* 1. Linear Hash    *";
		cout << endl << "* 2. Double Hash    *" ;
		cout << endl << "* 3. Quadratic Hash *" ;
		cout << endl << "****************************";
		cout << endl << "Input a command( -1, 0, 1, 2, 3 ):" ;

		cin >> command;
		switch(command) {
			case 0:
				input.read_txt();
				// cout << "Bulid binary complete!!\n";
				break;

			case 1:
				type = input.read_binary() ;
				if( type == false ) break ;
				fname = stoi(filenumber) ;
				t1 = chrono::steady_clock::now();
				linear.BuildHash( input.cSet, fname ) ;
				t2 = chrono::steady_clock::now();
				cout << "Total spend time =  " << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() << " ns " << endl;
				break;

			case 2:

				if( input.cSet.empty() ) {
					cout << "choose 1 first!" << endl ;
				} else {
	
					DH.data = input.cSet;
					DH.hash_insert();
					DH.write_to_file();
					DH.search();
				}

				break;
				
			case 3:
				if( input.cSet.empty() ) {
					cout << "choose 1 first!" << endl ;
				} else{
					
					t1 = chrono::steady_clock::now();
					q.BuildHash( input.cSet, fname ) ;
					t2 = chrono::steady_clock::now();
					cout << "Total spend time =  " << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() << " ns " << endl;

				
					
					break ;
				}

			case -1:
				break;

			default:
				cout << "command dosent exist!\n";
		}
	}

}
