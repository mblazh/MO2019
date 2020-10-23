set terminal png font "/home/richt3r/.fonts/monaco.ttf" size 1280,720
set title "Newton's base Lagrange interpolation"
set output "graphs/1.png"
set yrange [-0.4 : 0.4]
set xrange [-1 : 1]
set ylabel 'f(x)'
set xlabel 'x'
set grid
plot \
	"graphs/reference" using 1:2 with lines lw 2 title "Interpolated function",\
	"graphs/newtons0" using 1:2 with lines lw 2 title "Newton's base Lagrange interpolation",\
	"graphs/newtonsPoints0" using 1:2 with points lw 2 title "Points used for interpolation"

set title "Newton's base Lagrange interpolation with Chebyshew's points"
set output "graphs/2.png"
plot \
	"graphs/reference" using 1:2 with lines lw 2 title "Interpolated function",\
	"graphs/newtons1" using 1:2 with lines lw 2 title "Newton's base Lagrange interpolation",\
	"graphs/newtonsPoints1" using 1:2 with points lw 2 title "Points used for interpolation"