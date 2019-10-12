#gnuplot script

reset
#set term svg enhanced size 25,100
#set output 'output_plot.svg'
set multiplot

set size 1, 0.25
unset key

set view 60,60

set xtics 0,1
set ytics 0,1
set ztics 0,1

#Initial
set size 1,0.25
set origin 0.0,0.75
set title "Initial"
splot "./Output/initial.txt" with points lc rgb 'blue'

#Final
set origin 0.0,0.5
set title "After 1000 iterations" 
splot "./Output/final1.txt" with points lc rgb 'red'

set origin 0.0,0.25
set title "After 2000 iterations" 
splot "./Output/final2.txt" with points lc rgb 'green'

set origin 0.0,0.0
set title "After 3000 iterations" 
splot "./Output/final3.txt" with points lc rgb 'black'


set xtics auto
set ytics auto
set ztics auto
unset multiplot
reset