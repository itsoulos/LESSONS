# Simplex visualization — Bash + Gnuplot + FFmpeg

Requires: `sudo apt install gnuplot ffmpeg`

Input files must be named `simplex_1`, `simplex_2`, etc. and each contain exactly three rows with `x y f(x,y)`.

```bash
chmod +x simplex*.sh
./simplex2d.sh /path/to/data live
./simplex3d.sh /path/to/data live
./simplex2d.sh /path/to/data video 5 simplex2d.mp4
./simplex3d.sh /path/to/data video 5 simplex3d.mp4
./simplex_both.sh /path/to/data 5 simplex_both.mp4
```

The 3D graph shows the triangle connecting the three `(x,y,f)` vertices, not the full objective-function surface. The scale is fixed across frames.
