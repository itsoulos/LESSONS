#!/usr/bin/env bash
set -euo pipefail
DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
source "$DIR/simplex_common.sh" "${1:-.}" video "${2:-5}"
OUT=${3:-simplex_both.mp4}
mkdir -p "$TMP/frames"
for i in "${!FILES[@]}"; do
 F="$TMP/triangle_$(printf '%06d' "$i").dat"
 gnuplot <<GP
set terminal pngcairo size 1600,700 enhanced font 'Sans,14'
set output "$TMP/frames/frame_$(printf '%06d' "$i").png"
set multiplot layout 1,2 title "Simplex $(basename "${FILES[$i]}")"
set grid
set xlabel 'x'
set ylabel 'y'
set xrange [$XMIN:$XMAX]
set yrange [$YMIN:$YMAX]
set size ratio -1
plot "$F" using 1:2 with linespoints lw 2 pt 7 ps 1.5 lc rgb '#2563eb' notitle
set size noratio
set zlabel 'f(x,y)'
set zrange [$ZMIN:$ZMAX]
set view 65,35
splot "$F" using 1:2:3 with linespoints lw 2 pt 7 ps 1.5 lc rgb '#dc2626' notitle
unset multiplot
GP
done
ffmpeg -hide_banner -loglevel error -y -framerate "$FPS" -i "$TMP/frames/frame_%06d.png" -c:v libx264 -pix_fmt yuv420p -crf 20 "$OUT"
echo "Created: $OUT"
