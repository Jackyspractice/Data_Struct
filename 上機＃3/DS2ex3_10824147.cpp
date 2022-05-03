// 10824147 蔡尚博 

#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<vector>
#include<cstdlib>
#include<iomanip>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

using namespace std ;

class Data {
	public:
		char sid[10] ; // student ID
		char sname[10] ; // student name
		unsigned char score[6] ;
		float avg ; // score average
};

class HashData {
	public:
		int hval ;
		char sid[10] ;
		char sname[10] ;
		float avg ;
		bool empty = true ;
};

class DataInput {
	public:

		vector<Data> Set ;
        int f ;

		void PrintOut(vector<Data> data) {
			for( int i = 0; i < data.size(); i++ ) {
				cout << data[i].sid << " " << data[i].sname
				     << " " << data[i].score[0] << " " << data[i].score[1]
				     << " " << data[i].score[2] << " " << data[i].score[3]
				     << " " << data[i].score[4] << " " << data[i].score[5]
				     << " " << data[i].avg << endl ;
			}
		}


		string GetWord( string buffer, string &word, int &skip ) {

			string temp = "	" ;
			char ch = '\0' ;
			word.clear() ;
			word = "\0" ;
			while ( skip < buffer.size() ) {
				ch = buffer.at( skip ) ;

				if ( ch == '\t' ) { // || ch == ' ' || ch == '\n' || ch == '\r'){
					if( strcmp(word.c_str(), "\0") == 0 ) {
						skip ++ ;

						return "\0" ;
					} else {
						skip ++ ;
						return word ;
					}

				} else {

					word = word + ch ;

				}
				skip++;

			}  // while now ch == '\t'
			return word ;

		} // get word from file

		bool InputFile() {
			int skip = 0, num = 1 ;
			string word ;
			string number = "\0" ;
			string copy1 = "input" ;
			string copy2 = ".txt" ;
			string lb = "[" ;
			string rb = "]" ;

			string buffer ;
			fstream file ;
			cout << "input a file number:" ;
			cin >> number;
			copy1 = copy1.append(number);
			copy1 = copy1.append(copy2);
			//cout << copy1 << "\n";
			file.open (copy1,ios::in) ;
			if(!file.is_open()) {
				cout << "fail to open file, please restart\n";
				return false;
			}
			f = stoi(number) ;
			string temp ;
			getline( file, buffer ) ;
			// vector<Data> Set;
			//
			Set.clear() ;

			Data data ;
			while( !file.eof() ) {

				GetWord( buffer, word, skip ) ;
				strcpy(data.sid, word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				strcpy( data.sname, word.c_str() ) ;
				GetWord( buffer, word, skip ) ;
				data.score[0] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.score[1] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.score[2] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.score[3] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.score[4] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.score[5] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.avg = atof( word.c_str() ) ;
				// cout << word << endl ; ;

				Set.push_back(data);

				getline( file, buffer ) ;
				word.clear() ;
				skip = 0 ;

				num++ ;
			}
			if( buffer != "\0" ) {
				GetWord( buffer, word, skip ) ;
				strcpy(data.sid, word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				strcpy( data.sname, word.c_str() ) ;
				GetWord( buffer, word, skip ) ;
				data.score[0] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.score[1] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.score[2] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.score[3] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.score[4] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.score[5] = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.avg = atof( word.c_str() ) ;

				Set.push_back(data);
			}


			file.close() ;


			// PrintOut( Set ) ;

			return true;
		} // input and read file


}; // DataInput

class Linear {

	public:
		
		int size ;

		void BuildHash( vector<Data> &Set, int fname ) {

			int NumOfStudent = Set.size() ;
			double Success = 0.000 ;
			double Unsucc = 0.000 ;
			double HashSizeDouble = NumOfStudent * 1.2 ;
			int HashSize = GetPrime( HashSizeDouble ) ;
			// cout << HashSize << endl ;
			size = HashSize ;
			


			HashData Primer[HashSize] ;


			for( int i = 0; i < Set.size(); i++ ) {
				bool InputSuccess = false ;
				int key = Key( Set[i].sid, HashSize ) ;
				int hvalue = key ;

				while( InputSuccess == false ) {
					if( Primer[key].empty == true ) {
						Primer[key].hval = hvalue ;
						strcpy( Primer[key].sid, Set[i].sid ) ;
						strcpy( Primer[key].sname, Set[i].sname ) ;
						Primer[key].avg = Set[i].avg ;
						Primer[key].empty = false ;
						InputSuccess = true ;
					} // 找到並輸入 
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
		
		int GetPrime( int n ){
			int i ;
			int j ;
			i = n ;
			while(true){
				i++ ;
				for( j = 2; j <= i; j++ ){
				    if( i == j ){
				    	return i ;
					}
					else if( i%j == 0 ){
						break ;
					}
				} 
				
			}
		} // getprime 取1.2倍後最小質數 

		void WriteFile( HashData primer[], int fname, double success, double unsuccess ) {
			
			string name( std::to_string(fname) ) ;
            string FileName = "linear" + name + ".txt" ;
            ofstream outp(FileName) ;
            outp << "--- Hash Table X --- (linear probing)" << endl ;
            
            for( int i = 0; i < size; i++ ){
            	outp << "[" << i << "]" ;
            	if( primer[i].empty == true ){
            		outp << "\n" ;
				}
				else{
					outp << "\t" << primer[i].hval << "\t" << "," << primer[i].sid << "\t" << "," << primer[i].sname << "\t" << "," << primer[i].avg << endl ;
				}
				    
			}
			outp.close() ;
			
			cout << "Hash Table X has been created." << endl ;
			cout << "Unsuccessful search : " << unsuccess << "comparisons on average." << endl ;
			cout << "Successful search : " << success << "comparisons on average."<< endl ;
			
		} // void write
		
		double Unsuccess( HashData primer[] ){
			double range = 0.000 ;
			double all = 0.000 ;
			for( int i = 0; i < size ; i++ ){
				if( primer[i].empty == false ){
					for( int j = i; primer[j].empty == false; j++ ){
						range++ ;
						if( j == size -1 )
						    j = -1 ;
					}
					all = all + range ;
					range = 0.000 ;
				}
				else{
					all = all + range ;
					range = 0.000 ;
				}
			}
			
			// cout << all << "/" << size << endl ;
		    
			return all = all/size ;
			
		} // Unsuccess

};

class Double {
		// code here
};

int main(void) {

	DataInput input ;
	Linear linear ;
	Double dou ;

	bool status = true;

	int command = 0;
	do {

		cout << endl << "******** Hash Table ********";
		cout << endl << "* 0. QUIT *";
		cout << endl << "* 1. Linear Hash *";
		cout << endl << "* 2. Double Hash *" ;
		// cout << endl << "* 3.  *" ;
		cout << endl << "****************************";
		cout << endl << "Input a command( 0, 1, 2 ):" ;
		// cout << "fffff" ;
		cin >> command; // get a command
		switch (command) {
			case 0:
				break;

			case 1:
				status = input.InputFile() ;
				if(status == false) break;
				linear.BuildHash( input.Set, input.f ) ;
				
				//

				break ;

			case 2:
				if( input.Set.empty() ) {
					cout << "choose 1 first!" << endl ;
				} else {
					// dou.
					//
				}

				break ;
				/*
				case 3:

				 if( input.Set.empty() ){
				 	cout << "choose 1 first!" << endl ;
				}
				else{


				}


				break ;
				*/
			default:
				cout << endl << "Command does not exist!" << endl;
		} // end switch
	} while (command != 0); // '0': stop the program, 'false': cant finf the file.
	system("pause"); // pause the display
	return 0;

} // end main

