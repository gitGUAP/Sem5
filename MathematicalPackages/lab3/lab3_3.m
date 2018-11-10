x1 = [1, 0.5, 0, 2, 1.5, 3];
x2 = [1, 0.5, 1, 3, 2, 4];
y = [4.2, 3.4, 0, 2.1, 3.2, 2.5];
a = 0.05;

n = size(x1);
n = n(2);

x1 = x1';
x2 = x2';
y = y';

X = [ones(n, 1), x1, x2];
A = X' * X;
C = X' * y;
B = XtX\XtY;
 
disp("y = " + B(1) + " + "+ B(2) + "x1 + " + B(3) + "x2");

%%%%%%%%%%

Ym = mean(y);
Yemp = B(3).*x2 + B(2).*x1 + B(1);
disp('Y mean: ');
disp(Ym);
disp('Y emp: ');
disp(Yemp);

m = 2;
F = (sum((Yemp - Ym).^2)./m)./(sum((y - Yemp).^2)./(n - m - 1));
disp('F: ');
disp(F);
Fk = finv(1 - a, m, n - m - 1);
disp('Fk:');
disp(Fk);

if F > Fk
    disp("Since the value of F > Fk, the coefficient of determination is statistically significant.");
else
    disp("Since the value of F < Fk, the coefficient of determination is not statistically significant.");
end

%%%%%%%%%%
S2 = ((y - Yemp)') * (y - Yemp)./(n-m-1);
V = S2.*inv(X' * X);

t = [abs(B(1))/V(1,1),abs(B(2))/V(2,2),abs(B(3))/V(3,3)];

disp("Student's t-test:");
disp(t)

tk = tinv(1 - 0.025, n - m - 1);
disp("Tabular value::");
disp(tk);


[Xg,Yg]=meshgrid((min(x1)-1):0.1:(max(x1) + 1), (min(x1)-1):0.1:(max(x1) + 1)); 
Zg= B(1) + B(2) * Xg + B(3) * Yg; 
figure('Color','w'); 
hS=mesh(Xg,Yg,Zg'); 
hold on; 
plot3(x2, x1, B(1) + B(2) * x1 + B(3) * x2, 'rx','MarkerSize',10);