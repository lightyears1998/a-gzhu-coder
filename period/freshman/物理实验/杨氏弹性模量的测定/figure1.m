% 杨氏弹性模量的测定 Figure 1 %

A = [15.00, 13.85, 12.80, 11.55, 10.35, 9.06, 8.09, 6.80, 5.70, 4.50];
A = A./1e2;
F = [1:1:9];
F = F.*9.8;

detA = zeros(1, 9);
for idx = [1:1:9]
	detA(idx) = abs(A(idx+1)-A(1));
end

P = polyfit(F, detA, 1);

graphics_toolkit("gnuplot");
figure();

hold on;
grid on;
plot(F, detA, '+');
plot([0 F], polyval(P, [0 F]));
print('figure1.png', '-dpng');
hold off;

K = (polyval(P, F(2))-polyval(P, F(1))) / (F(2) - F(1))  % 拟合曲线的斜率
L = 700e-3
D = 180e-2
b = 72e-3
d = 1.002e-3
E = 8*L*D/(pi*(d^2)*b*K)
