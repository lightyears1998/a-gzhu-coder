% 光电效应与普朗克常数的测定 Figure 2 %

v = [5.20, 5.49, 6.88, 7.40, 8.21];
u = [0.516, 0.600, 1.070, 1.346, 1.678];
v = v .* 1e14;

P = polyfit(v, u, 1);

graphics_toolkit("gnuplot");
figure();

hold on;
grid on;
axis([0, 1e15, 0, 1.8]);
plot(v, u, '+');
plot([0 v], polyval(P, [0 v]));
print('figure2.png', '-dpng');
hold off;

k = (polyval(P, v(2)) - polyval(P, v(1))) / (v(2) - v(1))  % 拟合曲线的斜率
e = 1.602e-19;
h = k * e  % 测得普朗克常量

h0 = 6.626e-34;  % 普朗克常量的公认值
Re = abs(h-h0)/h0  % 相对误差
