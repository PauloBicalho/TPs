set terminal pdf
set style fill solid 1.00 border
set encoding iso_8859_1
set output "graf.pdf"
#set xrange[0:]
#set yrange[900:]
set xlabel "Iteração"
set ylabel "Fitness"
plot 'valores' using 1 with linespoints pointsize 0.2 pt 7 title "Melhor até agora", \
     'valores' using 5 with linespoints pointsize 0.2 pt 7 title "Melhor", \
     'valores' using 9 with linespoints pointsize 0.2 pt 7 title "Média", \
     'valores' using 13 with linespoints pointsize 0.2 pt 7 title "Pior", \
      (x*0+666) title "Ótima"
