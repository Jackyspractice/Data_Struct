class collegeType:
    def __init__(self) -> None:
        pass

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
    print("store complete!", lines)
    return myclassdata

def input_file():
    cSet = [] ##collegeType的array
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
        lines = (amount % 11) ##some bug here, lines wont over 11
        cSet.append(store(buffer, lines))
    file.close()
    print("size of cSet is = ", len(cSet))
    print(cSet[10].dname)

class avl_node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1

class AVL:
    
    def insert(self, root, data):
        if not root:
            return avl_node(data)
    

if __name__ == "__main__":
    command = 777
    while command != 0:
        print("\n*** Search Tree Utilities ***")
        print("* 0. QUIT *")
        print("* 1. Build 2-3 tree *")
        print("* 2. Build AVL tree *")
        print("*****************************")
        command = int(input("Input a command( 0, 1, 2, 3 ):"))

        ##if (command == 1): ##23
        if (command == 2):
            input_file()
        ##if (command == 3): ##set 
