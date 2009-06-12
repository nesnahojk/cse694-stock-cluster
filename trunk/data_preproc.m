clear
load changedata.txt


changedata(232,:)=[];
changedata(1090,:)=[];
changedata(1089,:)=[];

num=400;

newData=zeros(num,210);


t=25
j=1;
x=princomp(changedata);


pp=1;
ss={};
while t<(313-8),

x=princomp(changedata(1:num,t-24:t));

y3=kMeans(changedata(1:num,t-24:t),3);
y4=kMeans(changedata(1:num,t-24:t),4);
y5=kMeans(changedata(1:num,t-24:t),5);
y6=kMeans(changedata(1:num,t-24:t),6);



for i=1:num,
    newData(i,j)=changedata(i,t-24:t)*x(:,1);

if newData(i,j)>1,
  ss{pp}=i;
pp=pp+1;
endif

if newData(i,j)<-1,
  ss{pp}=i;
pp=pp+1;
endif

    newData(i,j+1)=changedata(i,t-24:t)*x(:,2);

if newData(i,j+1)>1,
  ss{pp}=i;
pp=pp+1;
endif

if newData(i,j+1)<-1,
  ss{pp}=i;
pp=pp+1;
endif

    newData(i,j+2)=y3(i);
    newData(i,j+3)=y4(i);
    newData(i,j+4)=y5(i);
    newData(i,j+5)=y6(i);
endfor

t=t+8;
j=j+6;
endwhile


ss=unique(cell2mat(ss));



for i=1:size(ss)(2),
	newData(ss(i)-(i-1),:)=[];
endfor


save -ascii newdata.csv newData
