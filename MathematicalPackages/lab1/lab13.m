figure;

a = 2;
b = 1.5;
c = 3;
h = 4;

[x, z] = meshgrid(-10:1:10);
y1 = b.*sqrt((x./a).^2 + (z./c).^2);
y2 = -b.*sqrt((x./a).^2 + (z./c).^2);
V1 = surf(x,y1,z,'EdgeColor','none');
hold on;
V2 = surf(x,y2,z,'EdgeColor','none');

grid on;
colormap spring;
colorbar;

rotate([V1, V2],[0 0 1], 60);

title('$-\frac{x^2}{a^2}+\frac{y^2}{b^2}+\frac{z^2}{c^2} = 0$');
xlabel('x');
ylabel('y');
zlabel('z');