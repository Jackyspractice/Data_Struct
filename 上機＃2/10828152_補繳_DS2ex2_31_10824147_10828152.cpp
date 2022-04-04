// DS2ex2_31_10824147_10828152  �q��T_���|�� �q���T��_�i�l��
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

int amount_avlnodes = 0;

class collegeType {
	public :
		int id ; // int�Ǹ�
		string number ; // �A���Ǹ�
		string scname ; // �ǮեN�X
		string school ; // college name �ǮզW��
		string dname ; // department name ��t�N�X
		string department ; //��t�W��
		string dayclub ; //�鶡
		string level ; //����
		string sNO ; // number of students�ǥͼ�
		string tNO ; //number of teachers�Юv��
		int gNO ; // number of graduates���~�ǥ�
		string counties ; //����
		string identity ; //��t�O
};

struct NodeData {
	
	string SchoolName ; // �ǮզW��

};

struct Node {
	vector<NodeData> SchoolData ; // �Ѥp��j��
	Node *parent ;
	Node *LChild ;
	Node *MChild ;
	Node *RChild ;
};

typedef Node * NodePtr ;

class DataInput {
	public:

		vector<collegeType> cSet ;

		
		void PrintOut(vector<collegeType> data){
			for( int i = 0; i < data.size(); i++ ){
				cout << (i+1) << ":[" << (i+1) << "]" 
				<< data[i].school << " " << data[i].department 
				<< " " << data[i].dayclub << " " << data[i].level 
				<< " " << data[i].sNO << endl ;
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
			string temp ;
			getline( file, buffer ) ;
			getline( file, buffer ) ;
			getline( file, buffer ) ;
			getline( file, buffer ) ;
			// vector<collegeType> cSet;
			//
			cSet.clear() ;

			collegeType data ;
			while( !file.eof() ) {
				data.id = num ; // id

				string sNum(std::to_string(num)) ; //
				string Snum = lb + sNum + rb ;
				data.number = Snum ; // �Ǹ�
				GetWord( buffer, word, skip ) ;
				data.scname = word ; //�ǮեN�X
				GetWord( buffer, word, skip ) ;
				data.school = word ; // �ǮզW��
				GetWord( buffer, word, skip ) ;
				data.dname = word ; // ��t�N�X
				GetWord( buffer, word, skip ) ;
				data.department = word ; // ��t�W��
				GetWord( buffer, word, skip ) ;
				data.dayclub = word ; // �鶡
				data.level = GetWord( buffer, word, skip ) ;


				GetWord( buffer, word, skip ) ;
				data.sNO = word ;
				GetWord( buffer, word, skip ) ;
				data.tNO = word ;
				GetWord( buffer, word, skip ) ;
				data.gNO = atoi(word.c_str()) ;

				GetWord( buffer, word, skip ) ;
				data.counties = word ;
				GetWord( buffer, word, skip ) ;
				data.identity = word ;
				cSet.push_back(data);

				getline( file, buffer ) ;
				word.clear() ;
				skip = 0 ;

				num++ ;
			}
			if( buffer != "\0" ) {
				string sNum(std::to_string(num)) ;
				string Snum = lb + sNum + rb ;

				data.number = Snum ; // �Ǹ�

				GetWord( buffer, word, skip ) ;
				data.scname = word ;
				word.clear() ;
				GetWord( buffer, word, skip ) ;
				data.school = word ;
				GetWord( buffer, word, skip ) ;
				data.dname = word ;
				GetWord( buffer, word, skip ) ;
				data.department = word ;
				GetWord( buffer, word, skip ) ;
				data.dayclub = word ;
				GetWord( buffer, word, skip ) ;
				data.level = word ;
				GetWord( buffer, word, skip ) ;
				data.sNO = word ;
				GetWord( buffer, word, skip ) ;
				data.tNO = word ;
				GetWord( buffer, word, skip ) ;
				data.gNO = atoi(word.c_str()) ;
				GetWord( buffer, word, skip ) ;
				data.counties = word ;
				GetWord( buffer, word, skip ) ;
				data.identity = word ;

				cSet.push_back(data);
			}


			file.close() ;

			// TwoThreeTree(cSet, deap) ;

			// PrintOut( cSet ) ;
			return true;
		} // input and read file

    
}; // DataInput

class TwoThreeTree {

	public:
		NodePtr head ;
        vector<int>where ;
        int nodenum = 0 ;

		void Build( vector<collegeType>data ) {
			NodeData temp ;
			// temp.num = data[0].id ;
			temp.SchoolName = data[0].school ;

			head = NULL;
			head = new Node ; nodenum++ ;
			head -> SchoolData.push_back( temp ) ;
			head -> parent = NULL;
			head -> LChild = head -> MChild = head -> RChild = NULL;

			for ( int i = 1; i < data.size() ; i++ ) {
				// temp.num = data[i].id ;
				temp.SchoolName = data[i].school ;

				Insert( temp ) ;
		
			}

		} // Build �N��ƨ̧ǩ�J

		void Insert( NodeData temp ) {

			NodePtr cur = head ;
			FindAndInput( cur, temp ) ;

		} // insert

		bool BiggerThanRight( string left, string right ) {
			if( left > right )
				return true ;
			else
				return false ;
		} // biggerthanright

		bool IsThereSame( NodePtr cur, string schoolname ) { // ��զW�@�˪�
			if ( cur == NULL ) { // no
				return false ;
			} //

			else {

				for ( int i = 0; i < cur -> SchoolData.size() ; i++ ) { // ��b�o��node�����S���@�˪��զW
					if ( cur -> SchoolData[i].SchoolName == schoolname )
						return true;
				}

				if ( IsThereSame( cur -> LChild, schoolname ) ) // ��left child ��same
					return true ;
				else if ( IsThereSame( cur -> MChild, schoolname ) ) // ��middle child ��same
					return true ;
				else if ( IsThereSame( cur -> RChild, schoolname ) ) // ��right child ��same
					return true ;

				else
					return false ; // �ثe�S���@�˪�

			}

		} // IsThereSame

		void FindAndInput( NodePtr cur, NodeData temp ) { //
			if( IsThereSame( cur, temp.SchoolName ) ) {
				;
			} else {
				InsertPosition( FindPosition( temp.SchoolName ), temp ) ;
				if( FindPosition( temp.SchoolName ) -> SchoolData.size() == 3 ) {
					Split( FindPosition( temp.SchoolName ) ) ;
				}
			}

		} // FindAndInsert

		NodePtr FindPosition( string schoolname ) {

			NodePtr cur = head ;
			NodePtr position ;

			while( cur != NULL ) {
				position = cur ;

				if ( cur -> SchoolData.size() == 1 ) { // node����school data�u���@��
					if ( BiggerThanRight( cur -> SchoolData[0].SchoolName, schoolname ) ) // �쥻�����j
						cur = cur -> LChild ;
					else
						cur = cur -> RChild ;
				} //

				else { // �����
					if ( BiggerThanRight( cur -> SchoolData[0].SchoolName, schoolname ) )
						cur = cur -> LChild ;
					else if ( BiggerThanRight( schoolname, cur -> SchoolData[1].SchoolName ) )
						cur = cur -> RChild ;
					else
						cur = cur -> MChild ;
				}
			}
			return position ;

		} // findposition

		void InsertPosition( NodePtr cur, NodeData temp ) {

			for ( int i = 0; i < cur -> SchoolData.size() ; i++ ) {
				if( BiggerThanRight( cur -> SchoolData[i].SchoolName, temp.SchoolName ) ) {
					cur -> SchoolData.insert( cur -> SchoolData.begin()+i, temp ) ;
					i = cur -> SchoolData.size() ; //
				}

				else if ( BiggerThanRight( temp.SchoolName, cur -> SchoolData[i].SchoolName ) ) {
					if ( i == cur -> SchoolData.size() - 1  ) {
						cur -> SchoolData.push_back( temp ) ;
						i = cur -> SchoolData.size() ; //
					}
				}
			}
		} // InsertPosition


		NodePtr Split( NodePtr cur ) {

			// NodeData promoted ;
			NodePtr big = new Node ; nodenum++ ;
			big -> LChild = big -> MChild = big -> RChild = NULL ;
			big -> SchoolData.push_back( cur -> SchoolData[2] ) ;
			// promoted.num = .SchoolName ;
			cur -> SchoolData.pop_back() ;

			if( cur == head ) { // root
				NodePtr promoted = new Node ; nodenum++ ;

				promoted -> LChild = cur ;
				promoted -> MChild = NULL ;
				promoted -> RChild = big ;
				promoted -> parent = NULL ;
				cur -> parent = promoted ;
				big -> parent = promoted ;
				promoted -> SchoolData.push_back( cur -> SchoolData[1] ) ;
				cur -> SchoolData.pop_back() ;

				head = promoted ;
			} else { // not root
				NodePtr curParent = cur -> parent ;
				InsertPosition( curParent, cur -> SchoolData[1] ) ;
				cur -> SchoolData.pop_back() ;

				if ( curParent -> SchoolData.size() == 2 ) { // parent��schooldata�S����
					if ( cur == curParent -> RChild ) { // �bcur�bcurP�k��
						curParent -> MChild = cur ;
						curParent -> RChild = big ;
					} //

					else // cur = curParent -> LChild
						curParent -> MChild = big ; // �u��big
					big -> parent = curParent ;
				}

				else { // parent��schooldata���F �A������Parent
					NodePtr curPBig = Split( curParent ) ;
					Rearrange( cur, big, curPBig ) ; //
				}

			} // else

			return big ; // ���ɪ�parent node��schooldata.size() == 1

		} // split()

		void Rearrange( NodePtr cur, NodePtr big , NodePtr temp ) { // �ثenode, cur�̤j��node, �����᪺parent��big node 
			NodePtr curParent = cur -> parent;
			string curParentPName = curParent -> parent -> SchoolData[0].SchoolName; // curParent��parent��schoolanme

			if ( BiggerThanRight( big -> SchoolData[0].SchoolName, curParentPName ) ) { // �b�k�� 
				if ( BiggerThanRight( big -> SchoolData[0].SchoolName, temp -> SchoolData[0].SchoolName ) ) {
					temp -> RChild = big ;
					big -> parent = temp ;
					temp -> LChild = curParent -> RChild ;
					curParent -> RChild -> parent = temp ;
					curParent -> RChild = curParent -> MChild ;
					curParent -> MChild = NULL ;
				} // big��curParent�����ᤧbig�j  ex. insert 1 2 3 4 5 6 7 split ndoe �b�k�� 

				else {
					temp -> LChild = big ;
					big -> parent = temp ;
					temp -> RChild = curParent -> RChild ;
					curParent -> RChild -> parent = temp ;
					curParent -> RChild = curParent -> MChild ;
					curParent -> MChild = NULL ;
				} // big��curParent�����ᤧbig�p �Nbig����temp�U�� ex. insert 1 10 2 9 3 8 4 split ndoe �b���� 

				
			} // 

			else { // �b���� 
				temp -> LChild = curParent -> MChild ;
				temp -> RChild = curParent -> RChild ;

				curParent -> RChild -> parent = curParent -> MChild -> parent = temp;
				curParent -> RChild = big ;
				big -> parent = curParent ;
				curParent -> MChild = NULL ;
			} // ex.insert 6 7 8 9 10 1 2 3 4 5 split node �b���� 

		} // Rearrange

        int Height() {

			int h = 0 ;
			NodePtr cur = head ;
			
			while( cur != NULL ){
				h++ ;
				cur = cur -> LChild ;
			}
            
			return h ;
		} // �p���
		
		void FindAndPrint( string name, vector<collegeType>data, int &num ) {
			// int num = 1 ;

			for( int i = 0 ; i < data.size(); i++ ) {
				if( data[i].school == name ) {
					cout << num << ":" ;
					cout << "[" << data[i].id << "]" ;
					cout << data[i].school << " " ;
					cout << data[i].department << " " ;
					cout << data[i].dayclub << " " ;
					cout << data[i].level << " " ;
					cout << data[i].sNO << endl ;
					num++ ;
				}
			}
		} // FindAndPrint ��X�ӮզW�bvector������ƨȩ̀ǦL�X

		void Result( vector<collegeType> data ) {
			NodePtr cur = head ;
			int num = 1, j = 1 ;
 
			int Treeh = Height() ;
			cout << "Tree Height : " << Treeh << endl ;
			// cout << "nodenum: " << nodenum << endl ;
			nodenum = 0 ;

			if( head -> SchoolData.size() == 1 ) {
				string name = head -> SchoolData[0].SchoolName ;

				FindAndPrint( name, data, num ) ;
			} else {
				// int size1 = SizeOfData( head -> SchoolData[0].SchoolName, data ) ;
				// int size2 = SizeOfData( head -> SchoolData[1].SchoolName, data ) ;
				// int all = size1 + size2 ;
				FindAndPrint( head -> SchoolData[1].SchoolName, data, num ) ; // ?

				FindAndPrint( head -> SchoolData[0].SchoolName, data, num ) ; // ?
			}
 

		} // 23tree��X���G
		
		NodePtr SearchName( string schoolname ){
			NodePtr find = head ;
			
			while( find != NULL ){
				if( find -> SchoolData.size() == 1 ){
					if( schoolname == find -> SchoolData[0].SchoolName ){
						return find ;
					}
					else if( schoolname > find -> SchoolData[0].SchoolName ){
						find = find -> RChild ;
					}
					else
					    find = find -> LChild ;
				}
				else if( find -> SchoolData.size() == 2 ){
					if( schoolname == find -> SchoolData[0].SchoolName ){
						return find ;
					}
					else if( schoolname == find -> SchoolData[1].SchoolName ){
						return find ;
					}
					else if( schoolname > find -> SchoolData[1].SchoolName ){
						find = find -> RChild ;
					}
					else if( schoolname < find -> SchoolData[0].SchoolName ){
						find = find -> LChild ;
					}
					else 
					    find = find -> MChild ;
				}
			}
			// return find ;
		} // search name 

        void mission3StarPrint( vector<int> where, vector<collegeType> data ) {
		    	int t = 1 ;
		    	for ( int i = 0 ; i < where.size(); i++ ) {
				
		    		cout << t << ": [" << data[where[i]-1].id << "] " << data[where[i]-1].school << " " << data[where[i]-1].dname << " " << data[where[i]-1].dayclub << " " << data[where[i]-1].level << " " << data[where[i]-1].sNO << endl;
                    t++ ;
		 			
				}
 
		} // mission3 star print 
		
		void findwhereID( string schoolname, vector<collegeType> data ){
			// cout << "dsa" ;
			NodePtr find = SearchName( schoolname ) ;
			// cout << "hewe" ;
			if( find -> SchoolData.size() == 1 ){
				// where.push_back( find -> SchoolData[0].num ) ;
				for( int i = 0; i < data.size(); i++ ){
					if( schoolname == data[i].school ){
						where.push_back( data[i].id ) ;
					}
					
				}
			}
			else if( find -> SchoolData.size() == 2 ){
				if( schoolname == find -> SchoolData[0].SchoolName ){ // �P�Ĥ@���ۦP 
					// where.push_back( find -> SchoolData[0].num ) ;
					for( int i = 0; i < data.size(); i++ ){
						if( schoolname == data[i].school ){
							where.push_back( data[i].id ) ;
						}
						
					} 
				}
				else{ // �P�ĤG���ۦP 
					// where.push_back( find -> SchoolData[1].num ) ;
					for( int i =0; i < data.size(); i++ ){
						if( schoolname == data[i].school ){
							where.push_back( data[i].id ) ;
						}
					}
				}
			}
			
			/*
			for( int i = 0; i < data.size(); i++ ){
				if( schoolname == data[i].school ){
					where.push_back( data[i].id ) ;
				}
			}
			*/
		} // findwhereID

};

class node {

	public:
		collegeType data;
		vector<int> departnumber;//���ۦP��t��ӥ[�J���Ǹ��C
		vector<int> departserial;//Ū���ۦP��t���Ǹ�
		int height;
		struct node* left;
		struct node* right;

		int max(int a, int b) {
			return (a >= b)? a : b;
		}

		int cheight(node* n) {
			return (n == NULL)? 0 : n->height;
		}

		int BF(node* x) {
			if(x == NULL) return 0;
			else return cheight(x->left) - cheight(x->right);
		}

		node* ll(node* y) {
			//cout << "need rr\n";
			node* x = y->left;
			node* xr = x->right;

			x->right = y;
			y->left = xr;

			y->height = max(cheight(y->left), cheight(y->right)) + 1;//����諸����s�A���M�W�誺height�|���C
			x->height = max(cheight(x->left), cheight(x->right)) + 1;

			return x;
		}

		node* rr(node* x) {
			//cout << "need ll\n";
			node* y = x->right;
			node* xr = y->left;

			y->left = x;
			x->right = xr;

			x->height = max(cheight(x->left), cheight(x->right)) + 1;
			y->height = max(cheight(y->left), cheight(y->right)) + 1;

			return y;
		}

		node* rl(node* x) {
			//cout << "need rl\n";
			x->right = ll(x->right);
			return rr(x);
		}

		node* lr(node* x) {
			//cout << "need lr\n";
			x->left = rr(x->left);
			return ll(x);
		}

		void Result(vector<collegeType> input, node* root) {

			cout << "tree height = " << max(cheight(root->left), cheight(root->right)) + 1 << "\n";
			//cout << "start result\n";
			for(int i = 0; i < root->departnumber.size(); i++) {
				int vectorserial = root->departnumber[i];
				//cout << "vectorserial = \n" << vectorserial;
				cout << i + 1 << ":[" << vectorserial << "]" << input[vectorserial - 1].school;
				cout << "\t" << input[vectorserial - 1].department << "\t" << input[vectorserial - 1].dayclub;
				cout << "\t" << input[vectorserial - 1].level << "\t" << input[vectorserial - 1].sNO << "\n";
			}
			//node* root = NULL;
		}

		node* Build(vector<collegeType>data, node* root) {

			//cout << "data size = " << data.size() << "\n";
			for ( int i = 0; i < data.size(); i++ ) {
				//cout << "insert data " << data[i].dname << "\n";
				root = insert( data[i],  root) ;
			}
			return root;
			//cout << "Build end\n";
		} // Build �N��Ƥ@������J

		node* insert(collegeType in, node* tree) {
			if(tree == NULL) { //��tree���ŮɡA�s�W��root
				tree = new node();//����Ƹ`�I
				tree->data = in;
				tree->departnumber.push_back(in.id);
				//cout << "tree is null, serial is " << tree->departnumber[0] << "\n";
				tree->height = 1;
				tree->left = tree->right = NULL;
				return tree;
			}

			//cout << "in depart is " << in.dname << "\t";
			//cout << tree->data.dname << " tree data depart"<< "\n";

			if(in.department < tree->data.department) { //�s�W��Ƥp��ɡA�����ܥ��l��
				//cout << "insert to left\n";
				tree->left = insert(in, tree->left);
			} else if(in.department > tree->data.department) { //�s�W��Ƥj��ɡA�����ܥk�l��
				//cout << "insert to right\n";
				tree->right = insert(in, tree->right);
			} else { //�s�W��Ƶ���ɡA��ܬ�t�ۦP�A�h�����Ǹ�
				//cout << "input is the same depart, which serial is " << in.id << "\n";
				tree->departnumber.push_back(in.id);
				return tree;
			}

			//�s�W����A���parent������
			tree->height = max(cheight(tree->left), cheight(tree->right)) + 1;
			//cout << "tree hight is " << tree->height << "\n";

			int bf = BF(tree);
			//cout << "BF(tree) is " << bf << "\n";

			if(bf > 1 && in.department < tree->left->data.department) return ll(tree);
			if(bf < -1 && in.department > tree->right->data.department) return rr(tree);
			if(bf > 1 && in.department > tree->left->data.department) return lr(tree);
			if(bf < -1 && in.department < tree->right->data.department) return rl(tree);
			return tree;
		}
		
		void Search(string departname, node* tree, vector<collegeType> input){
			//cout << "depart input is " << departname << "\ntree depart name is " << tree->data.department << "\n";
			if(departname == "*") return;
			if(departname == tree->data.department){
				//cout << "departname == tree->data.department\n";
				for(int i = 0; i < tree->departnumber.size(); i++){
					int vectorserial = tree->departnumber[i];
					departserial.push_back(vectorserial - 1);
					//cout << "vectorserial = " << vectorserial - 1 << endl;
					//cout << i + 1 << ":[" << vectorserial << "]" << input[vectorserial - 1].school;
					//cout << "\t" << input[vectorserial - 1].department << "\t" << input[vectorserial - 1].dayclub;
					//cout << "\t" << input[vectorserial - 1].level << "\t" << input[vectorserial - 1].sNO << "\n";
				}
				return;
			}
			if(departname < tree->data.department){
				if(tree->left == NULL){
					cout << "no this department here\n";
					return;
				}
				Search(departname, tree->left, input);
			}
			if(departname > tree->data.department){
				if(tree->right == NULL){
					cout << "no this department here\n";
					return;
				}
				Search(departname, tree->right, input);
			}
		}
		// put your code into here

};

class Find {

		string SchoolName ;
		string Department ;

		TwoThreeTree TTTree ;
		DataInput input ;

	public:

		void Input( vector<collegeType> data, node* root ) {

			// status = input.InputFile() ;

			cout << "Enter a college name to search[*]: " << endl ;
			cin >> SchoolName ;
			cout << "Enter a department name to search[*]: " << endl ;
			cin >> Department ;

			Search( SchoolName, Department, data, root ) ;
		}

        void set(vector<collegeType> data, vector<int> avl, vector<int> two){
			int t = 1;
			for(int i = 0; i < avl.size(); i++){
				for(int j = 0; j < two.size(); j++){
					if(avl[i] == two[j] - 1){
						cout << t++ << ": [" << data[avl[i]].id << "] " << data[avl[i]].school << " " << data[avl[i]].department << " " << data[avl[i]].dayclub << " " << data[avl[i]].level << " " << data[avl[i]].sNO << endl;
					}
				}
			}
		}

		void Search( string schoolname, string department, vector<collegeType> data, node* root ) {
			//
			// cout << schoolname << department ;
			TTTree.Build( data ) ;
			TTTree.where.clear() ;
			if( schoolname == "*" && department == "*" ){
				input.PrintOut( data ) ;
			}
			else if( schoolname != "*" && department == "*" ) {
				TTTree.findwhereID( schoolname, data ) ;
				
				TTTree.mission3StarPrint( TTTree.where, data ) ;
			}
			
			else if( schoolname == "*" && department != "*" ) {
			    // avl
			    root->Search(department, root, input.cSet);
				// cout << "department size = " << root->departserial.size() << "\n";
				int t = 1;
				for(int i = 0; i < root->departserial.size(); i++){
					int x = root->departserial[i];
					cout << t++ << ": [" << data[x].id << "] " << data[x].school << " " << data[x].department << " " << data[x].dayclub << " " << data[x].level << " " << data[x].sNO << endl;
				}
			}
			else{
				// cout << "here" ;
				TTTree.findwhereID( schoolname, data ) ; // 23tree����vector:where�Y���ӮզWid���}�C 
				// cout << "school size = " << TTTree.where.size() << "\n";
				/*for( int i = 0; i < TTTree.where.size(); i++ ){
					cout << TTTree.where[i] << endl ;
				}*/

				root->Search(department, root, input.cSet);
				// cout << "department size = " << root->departserial.size() << "\n";
				/*for(int i = 0; i < root->departserial.size(); i++){
					cout << root->departserial[i] << endl;
				}*/

				//set
				set(data, root->departserial, TTTree.where);
				root->departserial.clear();
			}
			    
			
			
				
			
		}


};

int main(void) {

	DataInput input ;
	TwoThreeTree TTtree ;
	Find find ;
	node* root;
	bool status = true;

	int command = 0;
	do {
		// List list ;
		cout << endl << "*** Search Tree Utilities ***";
		cout << endl << "* 0. QUIT *";
		cout << endl << "* 1. Build 2-3 tree *";
		cout << endl << "* 2. Build AVL tree *" ;
		cout << endl << "* 3. Intersection query *" ;
		cout << endl << "*****************************";
		cout << endl << "Input a command( 0, 1, 2, 3 ):" ;
		// cout << "fffff" ;
		cin >> command; // get a command
		switch (command) {
			case 0:
				break;

			case 1:
				status = input.InputFile() ;
				if(status == false) break;
				TTtree.Build( input.cSet ) ;
				TTtree.Result( input.cSet ) ;
				break ;

			case 2:
				if( input.cSet.empty() ){
					cout << "choose 1 first!" << endl ;
				}
				else{
					root = NULL;
			    	amount_avlnodes = 0;
		    		root = root->Build(input.cSet, root);
		    		root->Result(input.cSet, root);
		    		// cout << "AVL node amount is " << amount_avlnodes << endl;
		    		root->departserial.clear();
			    
				}
				
				break ;

			case 3:

                if( input.cSet.empty() ){
                	cout << "choose 1 first!" << endl ;
				} 
				else{
				    // status = input.InputFile() ;
			    	// if( status == false ) break ;
			    	/*
			    	TTtree.Build( input.cSet ) ;
			    	root = NULL;
		    		root = root->Build(input.cSet, root);
		    		*/
		    		// find.Input( input.cSet ) ;
		    		root = NULL;
					root = root->Build(input.cSet, root);
		    		find.Input( input.cSet, root) ;
				}
				

				break ;
			default:
				cout << endl << "Command does not exist!" << endl;
		} // end switch
	} while (command != 0); // '0': stop the program, 'false': cant finf the file.
	system("pause"); // pause the display
	return 0;

} // end main

