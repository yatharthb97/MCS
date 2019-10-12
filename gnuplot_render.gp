#gnuplot script

reset
set multiplot

#set term eps enhanced
#set output "$RunID.eps"

set size 1, 0.25
unset key

#Initial
set origin 0.0,0.75
set title "Initial"
splot "./Output/initial.txt" with points

#Final
set origin 0.0,0.5
set title "After 1000 iterations"
splot "./Output/final1.txt" with points

set origin 0.0,0.25
set title "After 2000 iterations"
splot "./Output/final2.txt" with points

set origin 0.0,0.0
set title "After 3000 iterations"
splot "./Output/final3.txt" with points

unset multiplot
reset