% 重力加速度的测定 Figure 1 %

h = [10:5:55];
h = h./ 1e2;
t = [.0607, .0843, .1067, .1272, .1461, .1635, .1803, .1963, .2117, .2259];

ht = h ./ t;

P = polyfit(t, ht, 1);

graphics_toolkit("gnuplot");
figure();

hold on;
grid on;
axis([0 0.25 0 2.5]);
plot(t, ht, '+');
plot([0 t], polyval(P, [0 t]));
print('figure1.png', '-dpng');
hold off;

k = (polyval(P, t(2)) - polyval(P, t(1))) / (t(2) - t(1))
g = 2*k
