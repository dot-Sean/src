reset
set samples 36
set isosample 36,36
set hidden3d
set ticslevel 0
set terminal postscript eps noenhanced monochrome dashed \
 defaultplex "Helvetica" 28
set size 2.0, 2.0
set title "Title"
set xlabel "x"
set ylabel "y"
set zlabel "z"
set output
set format x "%g"
set format y "%g"
set format z "%g"
splot [-10:10][-10:10][-0.3:1] sin(x) * sin(y) / x / y  title "Hoge"
