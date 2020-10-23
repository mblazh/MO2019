set terminal png font "/home/richt3r/.fonts/monaco.ttf" size 1280,720
set grid

set title 'Graph for error dependence on h parameter for maximum t'
set output "graphs/1.1.png"
set xrange [-1 : 0]
set yrange [-3 : 0]
set ylabel 'log10(max error(h))'
set xlabel 'log10(h)'
plot \
	"graphs/CDMhErrors" using 1:2 with lines lw 2 title "Classic Direct Method",\
	"graphs/CNMhErrors" using 1:2 with lines lw 2 title "Crank Nicolson Method",\
	"graphs/errorReference" using 1:2 with lines lw 2 title "Theoretical accuracy row (reference line)"

set title 'Graph for Classic Direct Method for t = 0.004'
set output "graphs/2.1.png"
set xrange [-10 : 10]
set yrange [0 : 1.1]
set ylabel 'U(x)'
set xlabel 'x'
plot \
	"graphs/CDMreference_t1" using 1:2 with lines lw 2 title "Analytical reference",\
	"graphs/CDMresults_t1" using 1:2 with points pt 26 lc rgb "red" title "Classic Direct Method"

set title 'Graph for Classic Direct Method for t = 1.0'
set output "graphs/2.2.png"
plot \
	"graphs/CDMreference_t251" using 1:2 with lines lw 2 title "Analytical reference",\
	"graphs/CDMresults_t251" using 1:2 with points pt 26 lc rgb "red" title "Classic Direct Method"

set title 'Graph for Classic Direct Method for t = 2.0'
set output "graphs/2.3.png"
plot \
	"graphs/CDMreference_t500" using 1:2 with lines lw 2 title "Analytical reference",\
	"graphs/CDMresults_t500" using 1:2 with points pt 26 lc rgb "red" title "Classic Direct Method"

set title 'Graph for Crank Nicolson Method for t = 0.01'
set output "graphs/2.4.png"
plot \
	"graphs/CNMreference_t1" using 1:2 with lines lw 2 title "Analytical reference",\
	"graphs/CNMresults_t1" using 1:2 with points pt 26 lc rgb "red" title "Crank Nicolson Method"

set title 'Graph for Crank Nicolson Method for t = 1.0'
set output "graphs/2.5.png"
plot \
	"graphs/CNMreference_t101" using 1:2 with lines lw 2 title "Analytical reference",\
	"graphs/CNMresults_t101" using 1:2 with points pt 26 lc rgb "red" title "Crank Nicolson Method"

set title 'Graph for Crank Nicolson Method for t = 2.0'
set output "graphs/2.6.png"
plot \
	"graphs/CNMreference_t200" using 1:2 with lines lw 2 title "Analytical reference",\
	"graphs/CNMresults_t200" using 1:2 with points pt 26 lc rgb "red" title "Crank Nicolson Method"

set title 'Graph for error dependence on t parameter for Classic Direct Method'
set output "graphs/3.1.png"
set xrange [0 : 2]
set yrange [0 : 0.3]
set ylabel 'max error(t)'
set xlabel 't'
plot \
	"graphs/CDMtErrors" using 1:2 with lines lw 2 title "Maximum error"

set title 'Graph for error dependence on t parameter for Crank Nicolson Method'
set output "graphs/3.2.png"
plot \
	"graphs/CNMtErrors" using 1:2 with lines lw 2 title "Maximum error"