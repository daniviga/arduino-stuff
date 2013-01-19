set term pdfcairo size 29cm,21cm font "Arial,8"
set output "temp.pdf"

set lmargin at screen 0.10
set rmargin at screen 0.92
set bmargin at screen 0.10
set tmargin at screen 0.90

set datafile separator ","
set datafile missing "NaN"

set xlabel "Time" font "Arial,12"
set ylabel "Temp °C" font "Arial,12"

set tics nomirror
set ytics format "%.2f"
set xdata time
set timefmt "%s"
set format x "%H:%M\n%y-%m-%d"

set grid xtics ytics lw 1 lt 1 lc rgb "#BFBFBF"

plot "arduino.csv" using 1:4 smooth sbezier lc rgb "#ff0000" lw 2 title "Temperature"

set term pdfcairo size 29cm,21cm font "Arial,8"
set output "lights.pdf"

set lmargin at screen 0.10
set rmargin at screen 0.92
set bmargin at screen 0.10
set tmargin at screen 0.90

set datafile separator ","
set datafile missing "NaN"

set xlabel "Time" font "Arial,12"
set ylabel "Light value" font "Arial,12"

set tics nomirror
set ytics format "%.0f"
set xdata time
set timefmt "%s"
set format x "%H:%M\n%y-%m-%d"

set grid xtics ytics lw 1 lt 1 lc rgb "#BFBFBF"

plot "arduino.csv" using 1:5 smooth sbezier lc rgb "#ff0000" lw 2 title "Light"
