% 霍尔效应测量磁场 Figure 1 %

Ih = [2:1:10];
U1 = [36.2, 54.3, 72.4, 90.4, 108.4, 126.4, 144.4, 162.4, 180.5];
U2 = [-36.4, -54.7, -72.8, -90.9, -109.1, -127.1, -145.8, -163.1, -181.3];
U3 = [36.4, 54.6, 72.8, 91.0, 109.1, 127.2, 145.3, 163.4, 181.4];
U4 = [-35.9, -53.8, -71.6, -89.5, -107.3, -125.2, -143.1, -160.9, -178.8];
Uh = (abs(U1)+abs(U2)+abs(U3)+abs(U4)) ./ 4

Kh = 173.2;
B1 = zeros(1, 9);
for idx = [1:9]
	B1(idx) = Uh(idx) / (Kh * Ih(idx));
end
B1

P = polyfit(Uh, Ih, 1);

graphics_toolkit("gnuplot");
figure();

hold on;
grid on;
axis([0, 180, 0, 12]);
plot(Uh, Ih, '+');
plot([0 Uh], polyval(P, [0 Uh]));
print('figure1.png', '-dpng');
hold off;

K1 = (polyval(P, Uh(2))-polyval(P, Uh(1))) / (Uh(2)-Uh(1))
B = 1/K1/Kh
