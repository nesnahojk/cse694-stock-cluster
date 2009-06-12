load changedata.txt


newData=zeros(1353,32);


t=0
j=1;
x=princomp(changedata);
while t<313-24,

x=princomp(changedata(:,t+1:t+24));

y3=kMeans(changedata(:,t+1:t+24),3);
y4=kMeans(changedata(:,t+1:t+24),4);
y5=kMeans(changedata(:,t+1:t+24),5);
y6=kMeans(changedata(:,t+1:t+24),6);

for i=1:1353,
    newData(i,j)=changedata(i,t+1:t+24)*x(:,1);
    newData(i,j+1)=changedata(i,t+1:t+24)*x(:,2);
    newData(i,j+2)=y3(i);
    newData(i,j+3)=y4(i);
    newData(i,j+4)=y5(i);
    newData(i,j+5)=y6(i);
endfor

t=t+24;
j=j+6;
endwhile
