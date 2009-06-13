clear
%load changedata.txt
load logData.txt
load returns.txt


changedata=logData;
num=400;

newData=zeros(num,245);
cluster5=zeros(num,35);
cluster6=zeros(num,35);
cluster7=zeros(num,35);
cluster8=zeros(num,35);

t=25
j=1;
q=1;
x=princomp(changedata);


while t<(313-8),

x=princomp(changedata(1:num,t-24:t));

y5=kMeans(changedata(1:num,t-24:t),5);
y6=kMeans(changedata(1:num,t-24:t),6);
y7=kMeans(changedata(1:num,t-24:t),7);
y8=kMeans(changedata(1:num,t-24:t),8);



for i=1:num,
    newData(i,j)=changedata(i,t-24:t)*x(:,1);


    newData(i,j+1)=changedata(i,t-24:t)*x(:,2);


    newData(i,j+2)=y5(i);
    cluster5(i,q)=y5(i);
    newData(i,j+3)=y6(i);
    cluster6(i,q)=y6(i);
    newData(i,j+4)=y7(i);
    cluster7(i,q)=y7(i);
    newData(i,j+5)=y8(i);
    cluster8(i,q)=y8(i);
    newData(i,j+6)=returns(i,t);
endfor
q=q+1;
t=t+8;
j=j+7;
endwhile




save -ascii newdata.csv newData




ss=unique(cell2mat(ss));



for i=1:size(ss)(2),
	newData(ss(i)-(i-1),:)=[];
endfor
