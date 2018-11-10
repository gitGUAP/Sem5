x1 = [-3, -1, 0, 1, 2, 3];
x2 = [4, 2, 1, -1, 0, -2];
y = [23, 6, 0, 1, 1, 13];
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
% Fix



%%%%%%%%%%