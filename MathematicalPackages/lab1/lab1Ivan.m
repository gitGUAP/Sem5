set(0, 'defaultTextInterpreter', 'latex');
figure;

%Часть 2
subplot(1,3,1);
fplot(@(x) 3.*x.^5 - 8.*x.^3 - 18.*x.^2 +2, [-2 4]);
hold on;
fplot(@(x) 0, [-2, 4] );
hold on;
title('$3*x^5 - 8*x^3 - 18*x^2+20=0$');
plot(-0.35, 0,'ro', 0.3,0, 'ro', 2.29,0, 'ro');
grid on;

subplot (1,3,2);
fplot(@(x) 5.^x);
hold on;
fplot(@(x) 2 + exp(-2*x));
hold on;
title('$5^x = 2 + e^{-2*x}$');
plot(0.53, 2.346, 'ro');
grid on;

subplot (1,3,3);
fimplicit(@(x, y) x.^3 + y.^3 - 8);
title('$x^3 + y^3 = 8; y = 1 - x^\frac{3}{2}$');
hold on;
fimplicit(@(x, y) x.^(3./2) + y - 1);
grid on;

%Часть 3
figure;
 a = 1; b = 2; c = 1.5; h = 5;
% f = fimplicit3(@(x,y,z) x.^2./a.^2 - y.^2./b.^2 + z.^2./c.^2, 'EdgeColor', 'none');
% colormap('jet');
% colorbar;
% 
% title('$\frac{x^2}{a^2}-\frac{y^2}{b^2}+\frac{z^2}{c^2} =0$');
% xlabel('x');
% ylabel('y');
% zlabel('z');

[x, z] = meshgrid(-15:0.5:15);
y = b.*sqrt((x./a).^2 + (z./c).^2);
V = mesh(x,y,z,y);
grid on;
cmap = colormap( 'jet');
colorbar;
rotate(V,[1 0 0], 45);

title('$\frac{x^2}{a^2}-\frac{y^2}{b^2}+\frac{z^2}{c^2} =0$');
xlabel('x');
ylabel('y');
zlabel('z');