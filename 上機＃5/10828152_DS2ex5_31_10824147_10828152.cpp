 // 10824147 10828152
  
#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<cstdio>
#include<iomanip>
#include<vector>
#include<time.h>

using namespace std ;

class Data {
	public:
		char putID[10] ;
		char getID[10] ;
		float weight ;
};

class head{
	public:
		float weight;
		int offset;
};

class Index{
	public:

		vector<head> indexs;
		int size = 0;
		int q = 0;

		void buffer(vector<Data> &input) {
			int buffer_max = 200;
			size = input.size();
			int current = 0;
			//int act_size = 0;
			while (current < size) {


				vector<Data> input_buffer;
				for (int i = current; i < current + buffer_max && i < size; i++) {
					input_buffer.push_back(input[i]);
					//act_size++;
				}
				//build(input_buffer);
				find_and_link(input_buffer, current);
				input_buffer.clear();

				current += 200;
			}

			cout << endl << "index size = " << indexs.size() << endl;
			
			cout << "(key, index)\n";
			for (int i = 0; i < indexs.size(); i++) {
				cout << "[" << i + 1 << "]" ;
				cout << ": (" << indexs[i].weight << ", " << indexs[i].offset << " )" << endl;
			}
			indexs.clear();
			q = 0;
			
			//cout << endl << "act size = " << act_size << endl;
		}

		void find_and_link(vector<Data> Maxset, int where) {
			
			float tem = 0;
			int offset = 0;
			head oneset;

			if (where == 0) {
				oneset.weight = Maxset[0].weight;
				oneset.offset = 0;
				indexs.push_back(oneset);
			}

			//cout << Maxset.size() << endl;
			for (int i = 0 ; i < Maxset.size(); i++) {
				q++;
				int next = i + 1;
				if (next < Maxset.size()) {

					if (Maxset[i].weight != Maxset[next].weight) {
						int x = indexs.size();
						oneset.offset = q;
						oneset.weight = Maxset[next].weight;
						indexs.push_back(oneset);
					}

					else if (Maxset[i].weight != indexs[indexs.size() - 1].weight && i == 0) {
						int x = indexs.size();
						oneset.offset = q;
						oneset.weight = Maxset[i].weight;
						indexs.push_back(oneset);
					}

				}
			}
		}


};

class Filecontrol {
	public:

		vector<Data> bin_data;
		vector<Data> sort_data;
		string filenumber;

		bool read_bin( string command ) {
			string filename;
			string copy1 = "pairs";
			string copy2 = ".bin";

			// cout << "input a file number:";
			// cin >> filenumber;
			filename = copy1 + command + copy2;
			ifstream bin_file(filename, ios::in | ios::binary);


			if (!bin_file.is_open()) {
				cout << "File: " << "pairs" << command << ".bin doesn't exist, please retry." << endl ;
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
			// print_input() ;	
			return true;

		}

		bool read_sort_bin( string command ) {
			string filename;
			string copy1 = "sorted";
			string copy2 = ".bin";

			// cout << "input a file number:";
			// cin >> filenumber;
			filename = copy1 + command + copy2;
			ifstream bin_file(filename, ios::in | ios::binary);


			if (!bin_file.is_open()) {
				cout << "File: " << "sorted" << command << ".bin doesn't exist, please retry." << endl ;
				return false;
			}

			sort_data.clear();

			Data data_line;

			while(bin_file.peek() != EOF) {

				bin_file.read(data_line.putID, sizeof(data_line.putID));

				bin_file.read(data_line.getID, sizeof(data_line.getID));

				bin_file.read((char *)&data_line.weight, sizeof(data_line.weight));

				sort_data.push_back(data_line);
			}

			bin_file.close();
			// print_input() ;	
			return true;

		}

		void print_input() {
			for(int i = 0; i < bin_data.size(); i++) {
				cout << "[ " << i+1 << " ]" ;
				cout << bin_data[i].putID << "\t";
				cout << bin_data[i].getID << "\t";
				cout << bin_data[i].weight << "\n";
			}
		}

}; // class Filecontrol

class Sort{
	public:
		vector<Data>tmp ;
		int total ; // fixed
		int files = 0 ;
		
		void parting( string filenum, vector<Data> input ){
			
			total = input.size()/200 ;  // cout << " size "<< input.size() << endl ;
			
			for( int i = 0; i < input.size(); ){
				for( int j = 0; j < 200 && i < input.size() ; j++ ){
					tmp.push_back( input[i] ) ; // cout << i << endl ;
					i++ ;
				}
				
				// cout << tmp.size() << endl ;
				sort( tmp ) ;
				Write( filenum, total, files, tmp ) ;
				files++ ;
				
			}
			files = 0 ;
		}
		
		void sort( vector<Data>&tmp ){
			vector<Data>sorted ;
			int max = 0 ;
			int test = 0 ;
			bool stop = false ;
			 
			while( stop != true ){
				for( int i = 0; i < tmp.size(); i++ ){
			    	if( tmp[i].weight > tmp[max].weight ){
			    		max = i ;
		    		}
		    	}
		    	sorted.push_back( tmp[max] ) ; // cout << max << endl ;
		    	tmp[max].weight = -1 ;
		    	
				if( sorted.size() == tmp.size() ) 
				    stop = true ;
			
			}
			// 
			tmp.clear() ;  
			tmp = sorted ;  // cout << tmp.size() << endl ;
		}
		
		void Write( string filenum, int total, int files, vector<Data>&tmp ){
			string filename = "sorted" + filenum + "_" + to_string(total) + "-" + to_string(files) + ".bin" ;
			fstream outp ;
			Data oneset ; // cout << tmp.size() << endl ;

			outp.open( filename.c_str(), ios::out | ios::binary ) ; // cout << tmp.size() << endl ;
			for( int i = 0 ; i < tmp.size() ; i++ ) {
				oneset = tmp[i] ;
				outp.write( (char*)&oneset, sizeof(oneset) ) ;
			} // for

			outp.close() ;
			tmp.clear() ;
		} // void write
		
		void merge( int first, int second, int runs, string filenum ){
			
			vector<Data>buffer1 ;
			vector<Data>buffer2 ;
			vector<Data>mer ;
			
			string firstfilen = "sorted" + filenum + "_" + to_string( total ) + "-" + to_string( first ) + ".bin" ;
			string secondfilen = "sorted" + filenum + "_" + to_string( total ) + "-" + to_string( second ) + ".bin" ;
			// string merfilen = "sorted" + filenum + "_" + to_string( total/2 ) + "-" + to_string( runs ) + ".bin" ;
			
			ifstream firstfile( firstfilen, ios::in | ios::binary  ) ;
			ifstream secondfile( secondfilen, ios::in | ios::binary  ) ;
			// ifstream merfile( merfilen, ios::out | ios::binary  ) ;
			
			buffer1.clear() ;
			buffer2.clear() ;

			Data data_line ;

			while( firstfile.peek() != EOF ) {

				firstfile.read(data_line.putID, sizeof(data_line.putID));

				firstfile.read(data_line.getID, sizeof(data_line.getID));

				firstfile.read((char *)&data_line.weight, sizeof(data_line.weight));

				buffer1.push_back( data_line );
			} // firstfile
			firstfile.close() ;

			while( secondfile.peek() != EOF ) {

				secondfile.read( data_line.putID, sizeof(data_line.putID) ) ;

				secondfile.read( data_line.getID, sizeof(data_line.getID) ) ;

				secondfile.read( (char *)&data_line.weight, sizeof(data_line.weight) ) ;

				buffer2.push_back( data_line ) ;
			} // secondfile
			secondfile.close() ;
			
			while( !buffer1.empty() && !buffer2.empty() ) {
				if ( buffer1[0].weight >= buffer2[0].weight ) {
					data_line = buffer1[0] ;
					buffer1.erase( buffer1.begin() ) ; 
 
				} // if

				else {
					data_line = buffer2[0];
					buffer2.erase(buffer2.begin());
 
				} // else

				mer.push_back( data_line ) ;
			} // while
			// 
			
		    while( !buffer1.empty() ){
				data_line = buffer1[0] ;
				buffer1.erase( buffer1.begin() ) ;
				mer.push_back( data_line ) ;
			}
			
			while( !buffer2.empty() ){
				data_line = buffer2[0] ;
				buffer2.erase( buffer2.begin() ) ;
				mer.push_back( data_line ) ;
			}
			// cout << "here" << endl ;
			// cout << "mer size " << mer.size() << endl;
			Write( filenum, total/2, runs, mer ) ;
			
			remove( firstfilen.c_str() ) ;
			remove( secondfilen.c_str() ) ;
		} // void merge 
		
		void external( string filenum ){
			int runs ;
			string name ;
			string out ;
			
			while( total != 0 ){
				runs = 0 ;
				for( int i = 0; i < total; i=i+2 ){
					merge( i, i+1, runs, filenum ) ;
					runs++ ;
				}
				
				if ( runs - 1 != total / 2 ) {
				    name = "sorted" + filenum + "_" + to_string( total ) + "-" + to_string( total ) + ".bin"  ;
					out = "sorted" + filenum + "_" + to_string( total/2 ) + "-" + to_string( total/2 ) + ".bin"  ;
					rename( name.c_str(), out.c_str() ) ;
					runs++;
				} // if

				total = total / 2 ;
				cout << "\nNow there are " << (runs) << " runs." << endl ;
				
			}
			
			name = "sorted" + filenum + "_0-0.bin"  ;
			out = "sorted" + filenum + ".bin" ;
			remove( out.c_str() ) ;
			rename( name.c_str(), out.c_str() ) ;
		} // void external
		
}; // class Sort

int main() {
	
    Filecontrol input ;
    Sort sort ;
	Index index ;
    
	string command ;
	string check ;
	int fname ;
	int internal ;
	int external ;

	while(command != "0") {
		bool type = true;
		
		cout << endl << "***********************************************" ;
		cout << endl << " On-machine Exercise 05                       *" ;
		cout << endl << " Mission 1: External Merge Sort on a Big File *";
		cout << endl << " Mission 2: Construction of Primary Index     *" ;
		// cout << endl << "* 3.   *" ;
		cout << endl << "***********************************************";
		cout << endl << "########################################################" ;
		cout << endl << "Mission 1: External merge sort" ;
		cout << endl << "########################################################" ;
		cout << endl ;
		cout << endl << "Input a file name: [0]Quit\n";

		cin >> command ;
		if( command != "0" ){
			type = input.read_bin( command ) ;
			if( type == false )
			    command = "777" ;
			else{
				int start = clock() ; 
				sort.parting( command, input.bin_data ) ; 
				int end = clock() ;
				internal = end - start ;
				
				cout << "\nThe internal sort is completed. Check the initial sorted runs!" << endl ;
				int exstart = clock() ;
				sort.external( command ) ;
				int exend = clock() ;
				external = exend - exstart ;
				
				cout << "\nThe execution time ..." << endl ;
		    	cout << "Internal Sort = " << internal << " ms" << endl ;
		    	cout << "External Sort = " << external << " ms" << endl ;
		    	cout << "Total Execution Time = " << internal+external << " ms" << endl ;
				
				// cout << "請按任意鍵繼續..." << endl ; 
				system("pause") ;
				// mission 2
				cout << endl << "########################################################" ;
				cout << endl << "Mission 2: Construction of Primary Index" ;
				cout << endl << "########################################################" ;
				type = input.read_sort_bin( command ) ;
				if (type) {

					index.buffer( input.sort_data );
					input.sort_data.clear();
					input.bin_data.clear();


				}
			}
			    
			
		} else {
			cout << endl << "[0]Quit or [Any other key]continue? \n" ;
			cin >> check ;
			if( check == "0" )
			    break ;
			else
			    command = "777" ;
		}
		
		
		
	}

}
