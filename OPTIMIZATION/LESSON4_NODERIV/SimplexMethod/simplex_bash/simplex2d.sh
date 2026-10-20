#!/usr/bin/env bash
set -euo pipefail
DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
source "$DIR/simplex_common.sh" "${1:-.}" "${2:-live}" "${3:-5}"
OUT=${4:-simplex2d.mp4}
if [[ "$MODE" == video ]]; then mkdir -p "$TMP/frames"; fi
for i in "${!FILES[@]}"; do
  F="$TMP/triangle_$(printf '%06d' "$i").dat"
  if [[ "$MODE" == video ]]; then
    TERMINAL='pngcairo size 960,720 enhanced font "Sans,14"'
    OUTPUT="$TMP/frames/frame_$(printf '%06d' "$i").png"
  else
    TERMINAL='qt size 960,720'
    OUTPUT=''
  fi
  gnuplot -persist <<GP
set terminal $TERMINAL
$(if [[ "$MODE" == video ]]; then printf 'set output "%s"' "$OUTPUT"; fi)
set title "Simplex $(basename "${FILES[$i]}")"
set xlabel 'x'
set ylabel 'y'
set grid
set size ratio -1
set xrange [$XMIN:$XMAX]
set yrange [$YMIN:$YMAX]
plot "$F" using 1:2 with linespoints lw 2 pt 7 ps 1.5 lc rgb '#2563eb' notitle
$(if [[ "$MODE" == live ]]; then echo 'pause 0.2'; fi)
GP
done
if [[ "$MODE" == video ]]; then
 ffmpeg -hide_banner -loglevel error -y -framerate "$FPS" -i "$TMP/frames/frame_%06d.png" -c:v libx264 -pix_fmt yuv420p -crf 20 "$OUT"
 echo "Created: $OUT"
fi
