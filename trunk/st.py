import csv


c5=[]
c6=[]
c7=[]
c8=[]


finalData=[]

newData=[]
sp=csv.reader(open('newdata.csv'),delimiter=' ')
for row in sp:
    nd=[]
    for i in range(1,len(row)):
        nd.append(float(row[i]))
    newData.append(nd);


sp=csv.reader(open('cluster5.csv'),delimiter=' ')
for row in sp:
    c=[]
    for i in range(1,len(row)):
        c.append(int(float(row[i])))
    c5.append(c)
        

stab5=[]
for i in range(0,400):
    tt=[0]
    for i in range(1,35):
        stayed=0
        were=0
        cc_old=c5[0][i-1]
        cc_new=c5[0][i]
    #find all points in t and t+1 with same cluster as j
        for k in range(0,400):
            if(c5[k][i-1]==cc_old):
                were=were+1  
            
                if(c5[k][i-1]==cc_old) and (c5[k][i]==cc_new):
                    stayed=stayed+1
        tt.append(float(stayed)/float(were));   
    stab5.append(tt)
    

sp=csv.reader(open('cluster6.csv'),delimiter=' ')
for row in sp:
    c=[]
    for i in range(1,len(row)):
        c.append(int(float(row[i])))
    c6.append(c)
        

stab6=[]
for i in range(0,400):
    tt=[0]
    for i in range(1,35):
        stayed=0
        were=0
        cc_old=c6[0][i-1]
        cc_new=c6[0][i]
    #find all points in t and t+1 with same cluster as j
        for k in range(0,400):
            if(c6[k][i-1]==cc_old):
                were=were+1  
            
                if(c6[k][i-1]==cc_old) and (c6[k][i]==cc_new):
                    stayed=stayed+1
        tt.append(float(stayed)/float(were));   
    stab6.append(tt)


sp=csv.reader(open('cluster7.csv'),delimiter=' ')
for row in sp:
    c=[]
    for i in range(1,len(row)):
        c.append(int(float(row[i])))
    c7.append(c)
        

stab7=[]
for i in range(0,400):
    tt=[0]
    for i in range(1,35):
        stayed=0
        were=0
        cc_old=c7[0][i-1]
        cc_new=c7[0][i]
    #find all points in t and t+1 with same cluster as j
        for k in range(0,400):
            if(c7[k][i-1]==cc_old):
                were=were+1  
            
                if(c7[k][i-1]==cc_old) and (c7[k][i]==cc_new):
                    stayed=stayed+1
        tt.append(float(stayed)/float(were));   
    stab7.append(tt)



sp=csv.reader(open('cluster8.csv'),delimiter=' ')
for row in sp:
    c=[]
    for i in range(1,len(row)):
        c.append(int(float(row[i])))
    c8.append(c)
        

stab8=[]
for i in range(0,400):
    tt=[0]
    for i in range(1,35):
        stayed=0
        were=0
        cc_old=c8[0][i-1]
        cc_new=c8[0][i]
    #find all points in t and t+1 with same cluster as j
        for k in range(0,400):
            if(c8[k][i-1]==cc_old):
                were=were+1  
            
                if(c8[k][i-1]==cc_old) and (c8[k][i]==cc_new):
                    stayed=stayed+1
        tt.append(float(stayed)/float(were));   
    stab8.append(tt)







for i in range(0,400):
    c=[]
    t=0
    for j in range(0,245,7):
        for k in range(0,7):
            c.append(newData[i][j+k])
        c.append(stab5[i][t])
        c.append(stab6[i][t])
        c.append(stab7[i][t])
        c.append(stab8[i][t])
        t=t+1
    finalData.append(c)


sw = csv.writer(open('finaldata.csv', 'w'), delimiter=',')
for i in finalData:
    sw.writerow(i);


sr = csv.reader(open('finaldata.csv'), delimiter=',')
