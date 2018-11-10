clc;
side = [0, 1, 2, 3, 4, 5, 6, 7];
bins = [0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5];
obsCounts = [4, 12, 27, 23, 21, 10, 3];

n = sum(obsCounts);
pi = obsCounts./n;

figure, bar(bins,pi,1);
title('Histogram');
axis([0 7 0 0.5]);

MX = sum(pi.*bins);
DX = sum((bins - MX).^2.*obsCounts./(n-1));
S = sqrt(DX);

disp('MX:'); disp(MX);
disp('DX:'); disp(DX);
disp('s:'); disp(S);

leftTeprPi = normcdf(side(1:7), MX, S);
rightTeorPi = normcdf(side(2:8), MX, S);
teorPi = rightTeorPi - leftTeprPi;

disp('Frequencies:');
disp(pi.*n);
disp('Theoretical frequencies:');
disp(teorPi.*n);
hold on;
plot(bins, teorPi, 'r');


XI2 = sum((obsCounts - n .* teorPi).^2 ./ (n .* teorPi)); 
k = chi2inv(1 - 0.05,4);
disp('Xi2 Statistics:');
disp(XI2);
disp('Critical point k2:');
disp(k);

if k > XI2
    disp('H0'); 
else 
    disp('H1');
end
