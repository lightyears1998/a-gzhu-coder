% 霍尔效应测量磁场 Figure 3 %

Im = [100:100:400];
U1 = [44.7, 88.9, 133.3, 178.5];
U2 = [-47.0, -91.9, -136.5, -180.2];
U3 = [47.1, 91.2, 136.1, 180.7];
U4 = [-44.7, -89.1, -133.7, -178.3];
Uh = (abs(U1)+abs(U2)+abs(U3)+abs(U4)) ./ 4

graphics_toolkit("gnuplot");
figure();

hold on;
grid on;
axis([0, 180, 0, 400]);
plot(Uh, Im, '+');
plot(Uh, Im);
print('figure3.png', '-dpng');
hold off;
