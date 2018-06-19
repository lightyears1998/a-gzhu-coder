% 变温粘滞系数 Figure %

nw = [.548, .469, .343, .222, .182];
t  = [  30,   35,   40,   45,   50];

function rslt = fun(var, data)
  rslt = var(1) * exp(-var(2) * data);
endfunction

var0 = [0 0];
P = lsqcurvefit(@fun, var0, t, nw);

graphics_toolkit("gnuplot");
figure();

hold on;
grid off;
axis([25, 55, 0, 0.6]);
plot(t, nw, '+', 'MarkerSize', 12);
plot([25:1:55], fun(P, [25:1:55]), 'LineWidth', 5);
print('figure.png', '-dpng');
hold off;
