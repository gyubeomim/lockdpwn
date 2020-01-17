#story of "hong gil dong"
skill = ["sword","spear","bow","axe"]
power = [98.5, 89.2, 100, 79.2]

#start of function 
def printItem(inSkill, idx=0):                             #(1)
    name = "Hong Gil Dong"
    age = 18
    weight = 69.3

    print "\n"
    print "----------------------------------------"
    print "1.name:", name
    print "2.age:", age
    print "3.weight:", weight

    print "4.armed weapon:",inSkill, "[ power", power[idx],"]"
    print ">>>i am ready to fight"
#end of function
    
querySkill = raw_input("select weapon: ")

i=0

for each_item in skill:
    if(each_item == querySkill):
        printItem(querySkill, i)                            #(2)
    i = i+1
        
print "----------------------------------------"
print "\n"
