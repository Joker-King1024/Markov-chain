%载入数据集
A=load('6.csv')

%2:t(ns)   7:a_x   8:a_y   9:t(s)
B=A(:,[2 7 8 9])
x=A(:,[9])
a_x=A(:,[7])
a_y=A(:,[8])

plot(x,a_x)
hold on;
plot(x,a_y)
hold on;