// DS2ex2_31_10824147_10828152  電資三_蔡尚博 電機三甲_張泓傑
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
		int id ; // int序號
		string number ; // 括號序號
		string scname ; // 學校代碼
		string school ; // college name 學校名稱
		string dname ; // department name 科系代碼
		string department ; //科系名稱
		string dayclub ; //日間
		string level ; //等級
		string sNO ; // number of students學生數
		string tNO ; //number of teachers教師數
		int gNO ; // number of graduates畢業學生
		string counties ; //縣市
		string identity ; //體系別
};

struct NodeData {
	int num ; // 序號
	string SchoolName ; // 學校名稱
	vector<NodeData> SameName ; // 放一樣校名的資料
};

struct Node {
	vector<NodeData> SchoolData ; // 由小到大排
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
				<< data[i].school << " " << data[i].dname 
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
				data.number = Snum ; // 序號
				GetWord( buffer, word, skip ) ;
				data.scname = word ; //學校代碼
				GetWord( buffer, word, skip ) ;
				data.school = word ; // 學校名稱
				GetWord( buffer, word, skip ) ;
				data.dname = word ; // 科系代碼
				GetWord( buffer, word, skip ) ;
				data.department = word ; // 科系名稱
				GetWord( buffer, word, skip ) ;
				data.dayclub = word ; // 日間
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

				data.number = Snum ; // 序號

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

		NodePtr Split( NodePtr cur ) { // 分裂
			NodePtr Big = new Node;
			Big -> LChild = Big -> MChild = Big -> RChild = NULL;
			Big -> SchoolData.push_back( cur -> SchoolData[2] ); // 最大

			cur -> SchoolData.pop_back();

			if ( cur == head ) { // root
				NodePtr promoted = new Node;
				promoted -> SchoolData.push_back( cur -> SchoolData[1] ) ; // 將第二大promote
				cur -> SchoolData.pop_back();
				promoted -> parent = NULL ;
				promoted -> LChild = cur ;
				promoted -> MChild = NULL ;
				promoted -> RChild = Big ;
				cur -> parent = promoted ;
				Big -> parent = promoted ;
				head = promoted ;

			}

			else { // 非root
				NodePtr curParent = cur -> parent ;

				InsertPosition( cur -> SchoolData[1], curParent ) ; // 第二大放進parent
				cur -> SchoolData.pop_back() ;

				if ( curParent -> SchoolData.size() == 2 ) { // parent的schooldata沒有滿
					if ( cur == curParent -> RChild ) { // 調整big位置
						curParent -> MChild = cur ;
						curParent -> RChild = Big ;
					} //

					else
						curParent -> MChild = Big ; // 只有big
					Big -> parent = curParent ;
				}

				else { // parent的schooldata滿了 再次分裂Parent
					NodePtr temp = Split( curParent ) ;
					Rearrange( cur, Big, temp ) ; //
				}

			} // else

			return Big ;

		} // split()

		void InsertNode( NodeData data ) {
			NodePtr cur = head ;

			if ( !IsThereSame( cur, data ) ) { // not same

				cur = head ;
				cur = FindPosition( data.SchoolName ) ;
				InsertPosition( data, cur ) ; //
				if ( cur -> SchoolData.size() == 3 ) {
					Split( cur ) ;
				}
			} else // same
				;

		} // InsertNode

		void Build( vector<collegeType>data ) {
			NodeData node ;
			node.num = data[0].id ;
			node.SchoolName = data[0].school ; // first

			head = NULL;
			head = new Node;
			head -> SchoolData.push_back( node ) ;
			head -> parent = NULL;
			head -> LChild = head -> MChild = head -> RChild = NULL;

			for ( int i = 1; i < data.size() ; i++ ) {
				node.num = data[i].id ;
				node.SchoolName = data[i].school ;
				InsertNode( node ) ;
				// cout << "fffff" ;
			}

		} // Build 將資料一筆筆放入

		bool BiggerThanRight( string left, string right ) {
			if( left > right )
				return true ;
			else
				return false ;
		} // bool check if left string is bigger than right stirng

		void Rearrange( NodePtr cur, NodePtr big , NodePtr temp ) { // 目前node, name最大的node, 分裂後的parent
			NodePtr curParent = cur -> parent;
			string curParentPName = curParent -> parent -> SchoolData[0].SchoolName; // curParent的parent的schoolanme

			if ( BiggerThanRight( big -> SchoolData[0].SchoolName, curParentPName ) ) { // big在temp層
				if ( BiggerThanRight( big -> SchoolData[0].SchoolName, temp -> SchoolData[0].SchoolName ) ) {
					temp -> RChild = big ;
					big -> parent = temp ;
					temp -> LChild = curParent -> RChild ;
				} // 確認big的校名大於祖父節點後 調整big位置

				else {
					temp -> LChild = big ;
					big -> parent = temp ;
					temp -> RChild = curParent -> RChild;
				} //

				curParent -> RChild -> parent = temp ;
				curParent -> RChild = curParent -> MChild;
				curParent -> MChild = NULL;
			}

			else { // big在curParent
				temp -> LChild = curParent -> MChild ;
				temp -> RChild = curParent -> RChild ;

				curParent -> RChild -> parent = curParent -> MChild -> parent = temp;
				curParent -> RChild = big ;
				big -> parent = curParent ;
				curParent -> MChild = NULL ;
			}

		} // Rearrange

		NodePtr FindPosition( string schoolname ) {
			NodePtr cur = head ;
			NodePtr position ;

			while ( cur != NULL ) { // 找到要新增的樹葉
				position = cur ;

				if ( cur -> SchoolData.size() == 1 ) { // node中的school data只有一個
					if ( BiggerThanRight( cur -> SchoolData[0].SchoolName, schoolname ) ) // 原本的較大
						cur = cur -> LChild ;
					else
						cur = cur -> RChild ;
				} //

				else { // 有兩個
					if ( BiggerThanRight( cur -> SchoolData[0].SchoolName, schoolname ) )
						cur = cur -> LChild ;
					else if ( BiggerThanRight( schoolname, cur -> SchoolData[1].SchoolName ) )
						cur = cur -> RChild ;
					else
						cur = cur -> MChild ;
				}
			}    //

			return position ;

		} // FindPosition  找出插入位置

		bool IsThereSame( NodePtr cur, NodeData data ) { // 找校名一樣的
			if ( cur == NULL ) { // no
				return false ;
			} //

			else {

				for ( int i = 0; i < cur -> SchoolData.size() ; i++ ) { // 找在這個node中有沒有一樣的校名
					if ( cur -> SchoolData[i].SchoolName == data.SchoolName )
						return true;

				}


				if ( IsThereSame( cur -> LChild, data ) ) // 找left child 名稱是否一樣
					return true ;
				else if ( IsThereSame( cur -> MChild, data ) ) // 找middle child
					return true ;
				else if ( IsThereSame( cur -> RChild, data ) ) // 找right child
					return true ;
				else
					return false ; // 目前沒有一樣的
			}

		} // IsThereSame

		void InsertPosition( NodeData data, NodePtr cur ) { //


			for ( int i = 0; i < cur -> SchoolData.size() ; i++ ) {
				if( BiggerThanRight( cur -> SchoolData[i].SchoolName, data.SchoolName ) ) {
					cur -> SchoolData.insert( cur -> SchoolData.begin()+i, data ) ;
					i = cur -> SchoolData.size() ; //
				}

				else if ( BiggerThanRight( data.SchoolName, cur -> SchoolData[i].SchoolName ) ) {
					if ( i == cur -> SchoolData.size() - 1  ) {
						cur -> SchoolData.push_back( data ) ;
						i = cur -> SchoolData.size() ; //
					}
				} //
			}

		} // InsertPosition 插入並決定node中資料的大中小位置

		int Height() {

			int h = 0 ;
			NodePtr cur = head ;

			for( ; cur != NULL ; cur = cur -> LChild )
				h ++ ;

			return h ;
		} // 計算樹高


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
		} // FindAndPrint 找出該校名在vector中之資料並依序印出

		/*
		int SizeOfData( string name, vector<collegeType> data ){
			int i = 0 ;
			for( int j = 0; j < data.size(); j++ ){
				if( name == data[j].school ){
				    i++ ;
			    }
			}

			return i ;
		} //
		*/

		void Result( vector<collegeType> data ) {
			NodePtr cur = head ;
			int num = 1, j = 1 ;

			// cout << "ffffff" ;
			int Treeh = Height() ;
			cout << "Tree Height : " << Treeh << endl ;

			if( head -> SchoolData.size() == 1 ) {
				string name = head -> SchoolData[0].SchoolName ;

				FindAndPrint( name, data, num ) ;
			} else {
				// int size1 = SizeOfData( head -> SchoolData[0].SchoolName, data ) ;
				// int size2 = SizeOfData( head -> SchoolData[1].SchoolName, data ) ;
				// int all = size1 + size2 ;
				FindAndPrint( head -> SchoolData[1].SchoolName, data, num ) ; // ?
				// num = size1 ;
				FindAndPrint( head -> SchoolData[0].SchoolName, data, num ) ; // ?
			}

			// data.clear() ;

		} // 23tree輸出結果

		bool Finish() {

			if( head != NULL ) {
				return true ;
			} else
				return false ;
		}

		int FindID( NodePtr find, string schoolname, vector<collegeType> data ) {
			for( int i = 0 ; i < data.size(); i++ ) {
				if( find -> SchoolData[i].SchoolName == schoolname ) {
					return i ;
				}
			}
		}
		
		void mission3StarPrint( string schoolname, vector<collegeType> data ) {
			int t = 1;
			for ( int i = 0 ; i < data.size(); i++ ) {
				if ( schoolname == data[i].school ) {
					cout << t << ": [" << data[i].id << "] " << data[i].school << " " << data[i].department << " " << data[i].dayclub << " " << data[i].level << " " << data[i].sNO << endl;
					t++ ;
				} // if
			} 
		} // 
		
		void findwhere( string schoolname, vector<collegeType> data ){
			for( int i = 0; i < data.size(); i++ ){
				if( schoolname == data[i].school ){
					where.push_back( data[i].id ) ;
				}
			}
		}

        /*
		void ( string schoolname, vector<collegeType> data, int num ) {
			NodePtr find = head ;

			NodeData node ;
			int id ;
			for( int i = 0; i < find -> SchoolData.size(); i++ ){
				while( schoolname != find -> SchoolData[i].SchoolName ){
				    
					if( schoolname < find -> SchoolData[0] ){
						find = find -> LChild ;
					}
					else if( schoolname > find -> SchoolData[1] ){
				    	find = find -> RChild ;
					}
					else
					    find = find -> MChild ;
		    	}
			}
			

            
			id = FindID( find, schoolname, data ) ;

			node.num = id ;
			node.SchoolName = schoolname ; //

			// cout << "ffff" << endl ;
			if ( IsThereSame( find, node ) ) { // same

				find = head ;
				find = FindPosition( schoolname ) ;
				// while( find -> SchoolData[] ){

				// }
				// cout << "ffff" << endl ;
				for( int i = 0; i < find -> SchoolData.size(); i++ ) {
					if( find -> SchoolData[i].SchoolName == schoolname ) {
						// cout << " 123" << endl ;
					}
				}

			}
			

		}*/

};

class node{ 
	
	public:
		collegeType data;
		vector<int> departnumber;//為相同科系後來加入的序號。
		vector<int> departserial;//讀取相同科系的序號
		int height;
		struct node* left;
		struct node* right;

		int max(int a, int b) {return (a >= b)? a : b;}

		int cheight(node* n){ return (n == NULL)? 0 : n->height;}

		int BF(node* x) {
			if(x == NULL) return 0;
			else return cheight(x->left) - cheight(x->right);
		}

		node* ll(node* y){
			cout << "need ll\n";
			node* x = y->left;
			node* xr = x->right;

			x->right = y;
			y->left = xr;

			y->height = max(cheight(y->left), cheight(y->right)) + 1;//先更改的先更新，不然上方的height會錯。
			x->height = max(cheight(x->left), cheight(x->right)) + 1;

			return x;
		}

		node* rr(node* x){
			cout << "need rr\n";
			node* y = x->right;
			node* xr = y->left;

			y->left = x;
			x->right = xr;

			x->height = max(cheight(x->left), cheight(x->right)) + 1;
			y->height = max(cheight(y->left), cheight(y->right)) + 1;

			return y;
		}

		node* rl(node* x){
			//cout << "need rl\n";
			x->right = ll(x->right);
			return rr(x);
		}

		node* lr(node* x){
			//cout << "need lr\n";
			x->left = rr(x->left);
			return ll(x);
		}

		void Result(vector<collegeType> input, node* root){
			
			cout << "tree height = " << max(cheight(root->left), cheight(root->right)) + 1 << "\n"; 
			//cout << "start result\n";
			for(int i = 0; i < root->departnumber.size(); i++){
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
		} // Build 將資料一筆筆放入

		node* insert(collegeType in, node* tree){
			cout << "in depart is " << in.department << "\t";
			
			if(tree == NULL){//當tree為空時，新增至root
				amount_avlnodes++;
				tree = new node();//實體化節點
				tree->data = in;
				tree->departnumber.push_back(in.id);

				cout << "tree is null, serial is " << tree->departnumber[0] << "\n";
				tree->height = 1;
				tree->left = tree->right = NULL;
				return tree;
			}
			
			//cout << tree->data.dname << " tree data depart"<< "\n";

			if(in.department < tree->data.department){//新增資料小於時，指派至左子樹
				cout << "insert to left\n";
				tree->left = insert(in, tree->left);
			}
			else if(in.department > tree->data.department){//新增資料大於時，指派至右子樹
				cout << "insert to right\n";
				tree->right = insert(in, tree->right);
			}
			else{//新增資料等於時，表示科系相同，則紀錄序號
				cout << "input is the same depart, which serial is " << in.id << "\n";
				tree->departnumber.push_back(in.id);
				return tree;
			}

			//新增完後，更改parent的高度
			tree->height = max(cheight(tree->left), cheight(tree->right)) + 1;
			cout << "tree hight is " << tree->height << "\n";

			int bf = BF(tree);
			cout << "BF(tree) is " << bf << "\n";

			if(bf > 1 && in.department < tree->left->data.department) return ll(tree);
			if(bf < -1 && in.department > tree->right->data.department) return rr(tree);
			if(bf > 1 && in.department > tree->left->data.department) return lr(tree);
			if(bf < -1 && in.department < tree->right->data.department) return rl(tree);
			return tree;
		}
	// put your code into here

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
};

class Find {

		string SchoolName ;
		string Department ;

		TwoThreeTree TTTree ;
		DataInput input ;
		bool status ;
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
			if( schoolname == "*" && department == "*" ){
				input.PrintOut( data ) ;
			}
			else if( schoolname != "*" && department == "*" ) {
				TTTree.mission3StarPrint( schoolname, data ) ;
			}
			
			else if( schoolname == "*" && department != "*" ) {
			    // avl
				root->Search(department, root, input.cSet);
				cout << "department size = " << root->departserial.size() << "\n";
				int t = 1;
				for(int i = 0; i < root->departserial.size(); i++){
					int x = root->departserial[i];
					cout << t++ << ": [" << data[x].id << "] " << data[x].school << " " << data[x].department << " " << data[x].dayclub << " " << data[x].level << " " << data[x].sNO << endl;
				}
				
			}
			else{

				TTTree.findwhere( schoolname, data ) ; // 23tree中的vector:where即為該校名id之陣列 
				cout << "school size = " << TTTree.where.size() << "\n";
				/*for( int i = 0; i < TTTree.where.size(); i++ ){
					cout << TTTree.where[i] << endl ;
				}*/

				root->Search(department, root, input.cSet);
				cout << "department size = " << root->departserial.size() << "\n";
				/*for(int i = 0; i < root->departserial.size(); i++){
					cout << root->departserial[i] << endl;
				}*/

				//set
				set(data, root->departserial, TTTree.where);
				root->departserial.clear();
				TTTree.where.clear();
				
			}
		}


};

int main(void) {

	DataInput input ;
	TwoThreeTree TTtree ;
	Find find ;
	node* root;
	bool status = true;
	string departname;

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
				status = input.InputFile() ;
				if(status == false) break;
				root = NULL;
				amount_avlnodes = 0;
				root = root->Build(input.cSet, root);
				root->Result(input.cSet, root);
				cout << "AVL node amount is " << amount_avlnodes << endl;
				root->departserial.clear();
				break ;

			case 3:

                if( input.cSet.empty() ){
                	cout << "choose 1 first!" << endl ;
				} 
				else{
				    status = input.InputFile() ;
			    	if( status == false ) break ;
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
