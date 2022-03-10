from cmath import log
import math

sizeofstudent = 0

def minheapinsert(insert):
    place = insert
    parent = (place - 1) / 2
    while (parent > 0) and (student[place][0] < student[parent][0]):
        temp = student[place][0]
        student[place][0] = student[parent][0]
        student[parent][0] = temp
        temp = student[place][1]
        student[place][1] = student[parent][1]
        student[parent][1] = temp
        place = parent
        parent = (place - 1) / 2


def maxheapinsert(insert):
    place = insert
    parent = (place - 1) / 2
    while (parent > 0) and (student[place][0] > student[parent][0]):
        temp = student[place][0]
        student[place][0] = student[parent][0]
        student[parent][0] = temp
        temp = student[place][1]
        student[place][1] = student[parent][1]
        student[parent][1] = temp
        place = parent
        parent = (place - 1) / 2


def min_maxheapinsert(new_input):
    global sizeofstudent
    #print("ss = %d" % sizeofstudent) 
    student[sizeofstudent][0] = new_input
    student[sizeofstudent][1] = sizeofstudent
    place = sizeofstudent
    #if place == 1 or place == 0:   place = -8
    parent = (sizeofstudent - 1) / 2;
    layer = int(math.log(sizeofstudent + 1, 2))

    if (parent >= 0) and ((layer + 1) % 2 != 0):
        if(student[sizeofstudent][0] > student[parent][0]):
            temp = student[place][0]
            student[place][0] = student[parent][0]
            student[parent][0] = temp
            temp = student[place][1]
            student[place][1] = student[parent][1]
            student[parent][1] = temp

            place = parent
            if place == 1 or place == 0 or place == 2: place = -8
            parent = (((place - 1) / 2) - 1) / 2

            while (parent >= 0) and (student[place][0] > student[parent][0]):
                temp = student[place][0]
                student[place][0] = student[parent][0]
                student[parent][0] = temp
                temp = student[place][1]
                student[place][1] = student[parent][1]
                student[parent][1] = temp
                place = parent
                if place == 1 or place == 0 or place == 2: place = -8
                parent = (((place - 1) / 2) - 1) / 2


        elif (parent >= 0) and (student[sizeofstudent][0] < student[parent][0]):
            if place == 1 or place == 0 or place == 2: place = -8
            parent = (((place - 1) / 2) - 1) / 2
            while (parent >= 0) and (student[place][0] < student[parent][0]):
                temp = student[place][0]
                student[place][0] = student[parent][0]
                student[parent][0] = temp
                temp = student[place][1]
                student[place][1] = student[parent][1]
                student[parent][1] = temp
                place = parent
                if place == 1 or place == 0 or place == 2: place = -8
                parent = (((place - 1) / 2) - 1) / 2


    elif (parent >= 0) and ((layer + 1) % 2 == 0):
        if student[sizeofstudent][0] < student[parent][0]:
            temp = student[place][0]
            student[place][0] = student[parent][0]
            student[parent][0] = temp
            temp = student[place][1]
            student[place][1] = student[parent][1]
            student[parent][1] = temp

            place = parent
            if(place == 1 or place == 0 or place == 2): place = -8
            parent = (((place - 1) / 2) - 1) / 2

            while (parent >= 0) and (student[place][0] < student[parent][0]):
                temp = student[place][0]
                student[place][0] = student[parent][0]
                student[parent][0] = temp
                temp = student[place][1]
                student[place][1] = student[parent][1]
                student[parent][1] = temp
                place = parent
                if place == 1 or place == 0 or place == 2: place = -8
                parent = (((place - 1) / 2) - 1) / 2

        elif (parent >= 0) and (student[sizeofstudent][0] > student[parent][0]):
            if place == 1 or place == 0 or place == 2: place = -8
            parent = (((place - 1) / 2) - 1) / 2
            while (parent >= 0) and (student[place][0] > student[parent][0]):
                temp = student[place][0]
                student[place][0] = student[parent][0]
                student[parent][0] = temp
                temp = student[place][1]
                student[place][1] = student[parent][1]
                student[parent][1] = temp
                place = parent
                if place == 1 or place == 0 or place == 2: place = -8
                parent = (((place - 1) / 2) - 1) / 2
    sizeofstudent = sizeofstudent + 1


def deapinsert(new_input):
    global sizeofstudent
    global size
    if sizeofstudent == 0:
        sizeofstudent = 1
    
    #print("ss = %d" % sizeofstudent) 

    student[sizeofstudent][0] = new_input
    student[sizeofstudent][1] = sizeofstudent

    

    layer = int(math.log(sizeofstudent + 1, 2))
    midleft = (pow(2, layer) - 1) + (pow(2, layer - 1) - 1)

    if sizeofstudent <= midleft:
        mirro = sizeofstudent + pow(2, layer - 1)
        if mirro > sizeofstudent: mirro = (mirro - 1) / 2

        if mirro > 0:
            if student[sizeofstudent][0] > student[mirro][0]:
                temp = student[sizeofstudent][0]
                student[sizeofstudent][0] = student[mirro][0]
                student[mirro][0] = temp
                temp = student[sizeofstudent][1]
                student[sizeofstudent][1] = student[mirro][1]
                student[mirro][1] = temp
                maxheapinsert(mirro)
            else:
                minheapinsert(sizeofstudent)
    else:
        mirro = sizeofstudent - pow(2, layer - 1)
        if student[sizeofstudent][0] < student[mirro][0]:
            temp = student[sizeofstudent][0]
            student[sizeofstudent][0] = student[mirro][0]
            student[mirro][0] = temp
            temp = student[sizeofstudent][1]
            student[sizeofstudent][1] = student[mirro][1]
            student[mirro][1] = temp
            minheapinsert(mirro)
        else:
            maxheapinsert(sizeofstudent)
    sizeofstudent = sizeofstudent + 1


def heapinsert(new_input):
    global sizeofstudent
    student[sizeofstudent][0] = new_input
    student[sizeofstudent][1] = sizeofstudent
    place = sizeofstudent
    parent = (place - 1) / 2
    while (parent >= 0) and (student[place][0] > student[parent][0]):
        temp = student[place][0]
        student[place][0] = student[parent][0]
        student[parent][0] = temp
        temp = student[place][1]
        student[place][1] = student[parent][1]
        student[parent][1] = temp
        place = parent
        parent = (place - 1) / 2
    sizeofstudent = sizeofstudent + 1
    #print("ss = %d" % sizeofstudent) 

#size = 0
#student = [[0] * 2 for i in range(0, size)]

while 1:
    print("(Stop, Max Heap, Deap, min-Max Heap) = (0, 1, 2, 3):")
    which = 100
    which = int(input())
    if which == 0:
        break
    elif which != 1 and which != 2 and which != 3:
        print("Enter error!!\n")
        continue
    print("Please input file name..\nEx:input101")
    tab = '\t'
    file = int(input())
    #fileopen = input()
    #filename = fileopen + ".txt"

    if (file == 101):
        f = open("input101.txt", 'r')
    elif (file == 102):
        f = open("input102.txt", 'r')
    elif (file == 103):
        f = open("input103.txt", 'r')
    elif (file == 104):
        f = open("input104.txt", 'r')
    elif (file == 105):
        f = open("input105.txt", 'r')
    elif (file == 106):
        f = open("input106.txt", 'r')
    else:
        print("cant read this file")
        continue

    # if f.readable() != True:
    #print("Fail to open file")
    for i in range(0, 3):
        line = f.readline()

    size = 0
    while True:
        line = f.readline()
        if not line:
            break
        buffer = line.split('\t')
        size = size + 1
    f.close()

    student = [[0] * 2 for i in range(0, size)]

    if (file == 101):
        f = open("input101.txt", 'r')
    elif (file == 102):
        f = open("input102.txt", 'r')
    elif (file == 103):
        f = open("input103.txt", 'r')
    elif (file == 104):
        f = open("input104.txt", 'r')
    elif (file == 105):
        f = open("input105.txt", 'r')
    elif (file == 106):
        f = open("input106.txt", 'r')
    
    for i in range(0, 3):
        line = f.readline()

    #for i in range(0, size):
        #print(student[i][1])

    j = 0
    if which == 1:
        sizeofstudent = 0
        while True:
            line = f.readline()
            if not line:
                break
            buffer = line.split('\t')
            heapinsert(int(buffer[6]))
            #print(int(buffer[6]))
            # student[j][0] = buffer[6] //0 data
            # student[j][1] = j + 1 //1 serial
            j = j + 1
        f.close()

        print("<MAX Heap>")
        print("serial = %d, root = %d" % (student[0][1] + 1, student[0][0]))
        print("serial = %d, bottom = %d" % (student[size - 1][1] + 1, student[size - 1][0]))

        n = int(math.log(size + 1, 2))
        x = pow(2, n) - 1
        print("serial = %d, leftbottom = %d" % (student[x][1] + 1, student[x][0]))

        #for i in range(0, size):
            #print(student[i][0])
        

    elif which == 2:
        student = [[0] * 2 for i in range(0, size + 1)]
        sizeofstudent = 0
        while True:
            line = f.readline()
            if not line:
                break
            buffer = line.split('\t')
            deapinsert(int(buffer[6]))
            #print(buffer[6])
            # student[j][0] = buffer[6] //0 data
            # student[j][1] = j + 1 //1 serial
            j = j + 1
        f.close()

        print("<Deap>")
        print("serial = %d, bottom = %d" % (student[size][1], student[size][0]))
        n = int(math.log(size + 1, 2))
        x = pow(2, n) - 1
        print("serial = %d, leftbottom = %d" % (student[x][1], student[x][0]))

    elif which == 3:
        sizeofstudent = 0
        while True:
            line = f.readline()
            if not line:
                break
            buffer = line.split('\t')
            min_maxheapinsert(int(buffer[6]))
            # student[j][0] = buffer[6] //0 data
            # student[j][1] = j + 1 //1 serial
            j = j + 1
        f.close()

        print("<min-MAX Heap>")
        print("serial = %d, root = %d" % (student[0][1] + 1, student[0][0]))
        print("serial = %d, bottom = %d" % (student[size - 1][1] + 1, student[size - 1][0]))

        n = int(math.log(size + 1, 2))
        x = pow(2, n) - 1
        print("serial = %d, bottom = %d" % (student[x][1] + 1, student[x][0]))

