#!/usr/bin/gnuplot -c

reset

set term pngcairo size 2000, 1000
set datafile separator ":"

outfile = sprintf("%s%s", ARG2, "energy.png")
set output  outfile

label1_1 = 'RunID: '
label1_2 =sprintf('%s', ARG3)
label1 = label1_1.label1_2
labelfinal = sprintf("%s%s%s", "Simulator X", "\n", label1)
set title labelfinal

plot ARG1 using 1:2 with lines lc rgb "red" title "Box Energy"

reset


reset

set term pngcairo size 1600, 2000
set datafile separator ":"

outfile = sprintf("%s%s", ARG2, "parameters.png")
set output  outfile

label1_1 = 'RunID: '
label1_2 =sprintf('%s', ARG3)
label1 = label1_1.label1_2
labelfinal = sprintf("%s%s%s", "Simulator X", "\n", label1)
set title labelfinal

plot ARG1 using 1:3 with lines lc rgb "grey" title "Total Displacement", ARG1 using 1:4 with lines lc "black" title "Total Displacement Squared", ARG1 using 1:5 with lines lc "blue" title "Acceptance Count",ARG1 using 1:6 with lines lc "orange" title "Rejection Count"

reset