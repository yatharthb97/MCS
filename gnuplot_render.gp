#gnuplot script

set term wxt enhanced
set multiplot

set size 0.5, 1

#Initial
set origin 0.0,0.0
splot "./Output/initial.txt" with points

#Final
set origin 0.5,0.0
splot "./Output/final.txt" with points

unset multiplot

exit