skill = ["sword","spear","bow","axe"]                 #(1)
power = [98.5, 89.2, 100, 79.2]

def printItem(inSkill, idx=0):                        #(2)
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
