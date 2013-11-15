import sys

#input_file = raw_input('input files name: ')
#input_num = (int)(raw_input('input check num: '))
input_file = "train.csv";

List = []
f = open(input_file, "r")
for line in f:
    strlist = line.split('","')
    ID = strlist[0][1:]
    if (not ID.isdigit()): continue
    st = strlist[1]
    nst = ""
    for i in st:
        if i.isalnum():
            nst += i
        else:
            nst += ' '
    for result in nst.split(' '):
        if (result.isdigit()): continue
        if (len(result) < 2): continue
        List.append((result.lower()))
f.close()
 
List.sort()

g = open("output.out", "w")

output = []
last = ""
num = 0
for x in List:
    if (x != last):
        output.append((last, num));
        num = 1;
    else:
        num = num + 1;
    last = x;
output.append((last, num));
output.sort(key=lambda tup:tup[1], reverse = True);

for x in output:
    g.write("%s %d\n" % x)

g.close()
