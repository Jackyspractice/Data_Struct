##DS2ex2_31_10824147_10828152  電資三_蔡尚博 電機三甲_張泓傑
amount_avlnodes = 0
class collegeType:
    def __init__(self) -> None:
        pass
class TwoThreeNode(object):
    def __init__(self, data, parent = None, LChild = None, MChild = None, RChild = None ):   
        self.parent = parent
        self.SchoolData = [data]
        self.LChild = LChild 
        self.MChild = MChild
        self.RChild = RChild  

class TwoThreeTree:
    def __init__(self):
        self.head = None

    def Build( self, data ):
        self.head = TwoThreeNode( data[0].school, None, None, None, None )

        for i in range (1, len(data)):
            self.FindAndInput(self.head, data[i].school)
            

    def IsThereSame(self, cur, schoolname):
        if(cur == None):
            return False
        else:
            for i in range (0, len(cur.SchoolData)):
                if( cur.SchoolData[i] == schoolname):
                    return True
            if( self.IsThereSame(cur.LChild, schoolname) ):
                return True
            elif( self.IsThereSame(cur.MChild, schoolname) ):
                return True
            elif( self.IsThereSame(cur.RChild, schoolname) ):
                return True
            else:
                return False

    def FindPosition( self, dataname ):
        cur = self.head
        find = cur
        while( cur != None ):
            find = cur
            if(len(cur.SchoolData) == 1 ):
                if( dataname > cur.SchoolData[0] ):
                    cur = cur.RChild
                else:
                    cur = cur.LChild
            else:
                if( dataname > cur.SchoolData[1] ):
                    cur = cur.RChild
                elif( dataname < cur.SchoolData[0] ):
                    cur = cur.LChild
                else:
                    cur = cur.MChild
        

        return find

    def InsertPosition(self, find, dataname):
        for i in range (0, len(find.SchoolData)-1):
            if(find.SchoolData[i] > dataname):
                find.SchoolData.insert( i+1, dataname)
                i = len(find.SchoolData)
            elif(find.SchoolData[i] < dataname):
                if( i == len(find.SchoolData)-1):
                    find.SchoolData.append(dataname)
                    i = len(find.SchoolData)

    def FindAndInput(self, head, dataname):
        if( self.IsThereSame(head, dataname) != True ):
            find = self.FindPosition(dataname)
            self.InsertPosition( find, dataname)
            if len(self.FindPosition(dataname).SchoolData) == 3:
                self.Split( self.FindPosition(dataname) )
            
    def Rearrange(self, cur, big, temp):
        curParent = cur.parent
        curParentName = curParent.parent.SchoolData[0]

        if(big.SchoolData[0]>curParentName):
            if(big.SchoolData[0] > temp.SchoolData[0]):
                temp.RChild = big
                big.parent = temp
                temp.LChild = curParent.RChild
                curParent.RChild.parent = temp
                curParent.RChild = curParent.MChild
                curParent.MChild = None
            else:
                temp.LChild = big
                big.parent = temp
                temp.RChild = curParent.RChild
                curParent.RChild.parent = temp
                curParent.RChild = curParent.MChild
                curParent.MChild = None
        
        else:
            temp.LChild = curParent.MChild
            temp.RChild = curParent.RChild

            curParent.RChild.parent = curParent.MChild.parent = temp
            curParent.RChild = big
            big.parent = curParent
            curParent.MChild = None

    
    def Split(self, cur):
        big = TwoThreeNode(cur.SchoolData[2],None,None,None,None)
        del cur.SchoolData[2]

        if(cur == self.head):
            promoted = TwoThreeNode( cur.SchoolData[1], None, cur, None, big)
            del cur.SchoolData[1]
            self.head = promoted
        else:
            curParent = cur.parent
            self.InsertPosition( curParent, cur.SchoolData[1])
            del cur.SchoolData[1]

            if(len(curParent.SchoolData) == 2):
                if(cur == curParent.RChild):
                    curParent.MChild = cur
                    curParent.RChild = big
                else:
                    curParent.MChlid = big
                big.parent = curParent
            
            else:
                curPBig = self.Split(curParent)
                self.Rearrange( cur, big, curPBig)
            
        return big

    def Height(self):
        h = 0
        cur = self.head

        while(cur != None):
            h = h + 1
            cur = cur.LChild
        
        return h

    def FindAndPrint(self, name, data, num ):

        for i in range (0, len(data)-1):
            if(data[i].school == name):
                print(num, ":")
                print("[", data[i].id, "]")
                print(data[i].scname, " ")
                print(data[i].school," ")
                print(data[i].department, " ")
                print(data[i].dayclub," ")
                print(data[i].level," ")
                print(data[i].sNO, "\n")
                num = num + 1

    def Result(self, data):
        cur = self.head
        num = 1
        j = 1

        Treeh = self.Height()
        print("Tree Height : ", Treeh)

        if(len(cur.SchoolData) == 1):
            name = cur.SchoolData[0]
            self.FindAndPrint(name, data, num)
        else:
            self.FindAndPrint(cur.SchoolData[1], data, num)
            self.FindAndPrint(cur.SchoolData[0], data, num)

def store(buffer, lines):
    myclassdata = collegeType()
    myclassdata.id = lines  ##int 序號
    myclassdata.scname = buffer[0]  ## 學校代碼
    myclassdata.school = buffer[1]  ## 學校名稱
    myclassdata.dname = buffer[2]   ## 科系代碼
    myclassdata.department = buffer[3]  ##科系名稱
    myclassdata.dayclub = buffer[4] ##日間
    myclassdata.level = buffer[5]   ##等級
    myclassdata.sNO = buffer[6] ##學生數
    myclassdata.tNO = buffer[7] ##教師數
    myclassdata.gNO = buffer[8] ##畢業學生數
    myclassdata.counties = buffer[9]    ##縣市
    myclassdata.identity = buffer[10]  ##體系別
    ##print("store complete!", lines)
    return myclassdata

def input_file():
    cSet = [] ##collegeType的array
    cSet.clear()
    number = input("input a file name:")
    copy1 = "input"
    copy2 = ".txt"
    filename = copy1 + number + copy2
    print("filename = ", filename)
    file = open(filename, 'r', encoding="cp950") ###windows = cp950, linux = utf-8
    for i in range(0, 3):
        line = file.readline()
    amount = 0
    while True:
        line = file.readline();
        if not line: break
        buffer = line.split('\t')
        amount += 1
        cSet.append(store(buffer, amount))
    file.close()
    print("size of cSet is = ", len(cSet))

    ##for i in range (0, len(cSet)):
        ##print(cSet[i].id, cSet[i].scname, cSet[i].school, cSet[i].dname, cSet[i].department, cSet[i].dayclub, cSet[i].sNO, cSet[i].identity)

    return cSet
class avl_node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1
        self.departnumber = []

class AVL:

    def cheight(self, tree):
        return 0 if (tree == None) else tree.height

    def max(self, a, b):
        return a if (a >= b) else b 

    def BF(self, tree):
        return 0 if (tree == None) else ( self.cheight(tree.left) - self.cheight(tree.right) )
    
    def ll(self, y):
        ##print("need ll")
        x = y.left
        xr = x.right

        x.right = y
        y.left = xr

        y.height = self.max(self.cheight(y.left), self.cheight(y.right)) + 1
        x.height = self.max(self.cheight(x.left), self.cheight(x.right)) + 1

        return x

    def rr(self, x):
        ##print("need rr")
        y = x.right
        xr = y.left

        y.left = x
        x.right = xr

        x.height = self.max(self.cheight(x.left), self.cheight(x.right)) + 1
        y.height = self.max(self.cheight(y.left), self.cheight(y.right)) + 1

        return y

    def lr(self, x):
        ##print("need lr")
        x.left = self.rr(x.left)
        return self.ll(x)

    def rl(self, x):
        ##print("need rl")
        x.right = self.ll(x.right)
        return self.rr(x)

    def insert(self, root, data):
        
        global amount_avlnodes
        global departserial
        ##print("input data is ", data.department)
        ##print("root data is ", root.data.department)

        if not root: ##root 為空
            ##print("root is NULL")
            amount_avlnodes += 1
            root = avl_node(data)
            root.departnumber.append(data.id)
            return root

        if (data.dname) < (root.data.dname):
            ##print("insert to left, in data is ", data.department, "node data is ", root.data.department)
            root.left = self.insert(root.left, data)

        elif (data.dname) > (root.data.dname):
            ##print("insert to right, in data is ", data.department, "node data is ", root.data.department)
            root.right = self.insert(root.right, data)

        else :
            ##print("equal, in data is ", data.department, "node data is ", root.data.department)
            root.departnumber.append(data.id)
            return root

        root.height = self.max(self.cheight(root.left), self.cheight(root.right)) + 1
        ##print("height = ", root.height)

        bf = self.BF(root)
        ##print("bf = ", bf)

        if(bf > 1 and data.dname < root.left.data.dname): return self.ll(root)
        if(bf < -1 and data.dname > root.right.data.dname): return self.rr(root)
        if(bf > 1 and data.dname > root.left.data.dname): return self.lr(root)
        if(bf < -1 and data.dname < root.right.data.dname): return self.rl(root)

        return root

    def build(self, root, data):

        for i in range (0, len(data)):
            root = self.insert(root, data[i])
            ##print("i is ", i, "data is ", data[i].department)

        return root
    
    def Result(self, tree, data):

        print("tree height = ", self.max(self.cheight(tree.left), self.cheight(tree.right)) + 1)
        
        for i in range (0, len(tree.departnumber)):
            vectorserial = tree.departnumber[i]
            print(i + 1, ":[", vectorserial, "]", data[vectorserial - 1].school, end = "\t")
            print(data[vectorserial - 1].department, "\t", data[vectorserial - 1].dayclub, end = "\t")
            print(data[vectorserial - 1].level, "\t", data[vectorserial - 1].sNO)

    def Search(self, searchdepart, tree):
        
        if searchdepart == "*": return;

        if searchdepart == tree.data.dname:
            for i in range (0, len(tree.departnumber)):
                departserial.append(tree.departnumber[i] - 1)
            return
        
        if searchdepart < tree.data.dname:
            if tree.left == None:
                print("no this department here")
                return
            self.Search(searchdepart, tree.left)

        if searchdepart > tree.data.dname:
            if tree.right == None:
                print("no this department here")
                return
            self.Search(searchdepart, tree.right)

if __name__ == "__main__":
    command = 777
    while command != 0:
        print("\n*** Search Tree Utilities ***")
        print("* 0. QUIT *")
        print("* 1. Build 2-3 tree *")
        print("* 2. Build AVL tree *")
        print("*****************************")
        command = int(input("Input a command( 0, 1, 2, 3 ):"))

        if (command == 1):
            input_cSet = input_file()
            TTTree = TwoThreeTree()
            TTTree.Build( input_cSet )
            TTTree.Result( input_cSet )
            

        if (command == 2):
            input_cSet = input_file()
            tree = AVL()
            root = None
            amount_avlnodes = 0
            root = tree.build(root, input_cSet)
            tree.Result(root, input_cSet)
            print("amount of nodes = ", amount_avlnodes)


        if (command == 3):
            input_cSet = input_file()
            searchdepart = input("Enter a department code 代碼 to search[*]: ")
            departserial = []
            tree = AVL()
            root = None
            root = tree.build(root, input_cSet)
            tree.Search(searchdepart, root)
            ##for i in range (0, len(departserial)):
                ##print(departserial[i])
            for i in range (0, len(departserial)):
                vectorserial = departserial[i]
                print(i + 1, ":[", vectorserial + 1, "]", input_cSet[vectorserial].school, end = "\t")
                print(input_cSet[vectorserial].department, "\t", input_cSet[vectorserial].dayclub, end = "\t")
                print(input_cSet[vectorserial].level, "\t", input_cSet[vectorserial].sNO)
