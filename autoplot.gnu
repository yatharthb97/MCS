#!/usr/bin/gnuplot -c

reset
set term pngcairo size 800, 800

set output  ARG2
arg3=ARG3
arg4=ARG4
label1_1 = 'Sweeps: '
label1_2 =sprintf('%s', ARG3)
label1 = label1_1.label1_2

label2_1 = 'Energy: '
label2_2 = sprintf('%s', ARG4)
label2 = label2_1.label2_2


#labelfinal = "Simulator X".\n".label1."\n".label2"
labelfinal = sprintf("%s%s%s%s%s", "Simulator X", "\n", label1, "\n", label2)


set title labelfinal

splot ARG1 with points title "Spherocylinder position"

reset