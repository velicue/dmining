# Train Entry Show:
# Given index q, return the entry which has the closest id in training set.
# If input "", return next entry.

import sys

symbol_s = ["I can't tell","Negative","Neutral / author is just sharing information","Positive","Tweet not related to weather condition"]

symbol_w = ["current (same day) weather","future (forecast)","I can't tell","past weather"]

symbol_k = ["clouds","cold","dry","hot","humid","hurricane","I can't tell","ice","other","rain","snow","storms", "sun", "tornado", "wind"]

f = open("train.csv", "r")
myList = []
myIndex = []
i = 0
for line in f:
    myList.append(line)
    strlist = line.split('","')
    if (i == 0): 
        myIndex.append(0)
    else:
        myIndex.append((int)(strlist[0][1:]))
    i = i + 1
f.close()

listlen = len(myList)
i = 0

def show(i):
    strlist = myList[i].split('","')

    print("ID: " + strlist[0]);
    print("TWEET: " + strlist[1]);
    print("");
    print("S:")
    for s in range(1, 6):
        if (strlist[3 + s] != "0"):
            print (symbol_s[s - 1] + ": " + strlist[3 + s])
    print("W:")
    for w in range(1, 5):
        if (strlist[8 + w] != "0"):
            print (symbol_w[w - 1] + ": " + strlist[8 + w])
    print("K:")
    for k in range(1, 16):
        if (strlist[12 + k] != "0" and (k != 15 or strlist[12 + k] != "0\"\n")):
            if (k == 15):
                print (symbol_k[k - 1] + ": " + strlist[12 + k][:-2])
            else:
                print (symbol_k[k - 1] + ": " + strlist[12 + k])
    print("");
    print("");
    return;

def findIndex(i):
    left = 1
    right = len(myList)
    ans = 1
    while (left <= right):
        mid = (left + right) / 2;
        if (myIndex[mid] <= i):
            ans = mid
            left = mid + 1
        else:
            right = mid - 1
    return ans

while 1:
    input_st = raw_input('######################: ')
    if (input_st == ""): 
        i = i + 1
    else:
        if (i < 0): break
        i = findIndex((int)(input_st))

    if (i >= listlen): continue
    
    show(i)
