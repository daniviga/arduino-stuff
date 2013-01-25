set term pdfcairo size 29cm,21cm font "Arial,12"
set output "tempLightPlot.pdf"

set lmargin at screen 0.10
set rmargin at screen 0.92
set bmargin at screen 0.10
set tmargin at screen 0.90

set datafile separator ","
set datafile missing "NaN"

set xlabel "Time" font "Arial,16"
set ylabel "Temp °C" font "Arial,16"
set y2label "Light" font "Arial,16"

set tics nomirror
set ytics 1 format "%.2f" tc rgb "#ff0000"
set yrange [18:28]
set y2tics 100 tc rgb "#0000ff"
set y2range [0:1000]
set xdata time
set timefmt "%s"
set format x "%H:%M\n%y-%m-%d"

set grid xtics ytics lw 1 lt 1 lc rgb "#BFBFBF"

plot "arduino.csv" using 1:4 smooth sbezier lc rgb "#ff0000" lw 2 title "Temperature", "arduino.csv" using 1:5 smooth sbezier lc rgb "#0000ff" lw 2 title "Light" axes x1y2
