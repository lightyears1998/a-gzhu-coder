% 变温粘滞系数 Figure %

nw = [.548, .469, .343, .222, .182];
t  = [  30,   35,   40,   45,   50];

P = polyfit(t, nw, 2);

graphics_toolkit("gnuplot");
figure();

hold on;
grid on;
axis([25, 55, 0, 0.6]);
plot(t, nw, '+', 'MarkerSize', 12);
plot([25 t 55], polyval(P, [25 t 55]), 'LineWidth', 5);
print('figure.png', '-dpng');
hold off;
