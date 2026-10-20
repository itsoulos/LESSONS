#!/usr/bin/env bash
set -euo pipefail
DATA_DIR=${1:-.}
MODE=${2:-live}
FPS=${3:-5}
[[ -d "$DATA_DIR" ]] || { echo "Folder not found: $DATA_DIR" >&2; exit 1; }
[[ "$MODE" == live || "$MODE" == video ]] || { echo 'Mode: live or video' >&2; exit 1; }
[[ "$FPS" =~ ^[0-9]+$ && "$FPS" -gt 0 ]] || { echo 'FPS must be a positive integer' >&2; exit 1; }
mapfile -d '' -t FILES < <(find "$DATA_DIR" -maxdepth 1 -type f -regextype posix-extended -regex '.*/simplex_[0-9]+' -print0 | sort -zV)
((${#FILES[@]})) || { echo "No simplex_N files in $DATA_DIR" >&2; exit 1; }
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
for idx in "${!FILES[@]}"; do
  awk 'NF>=3 {if(n==0) first=$0; print $1,$2,$3; n++} END {if(n!=3) exit 1; print first}' "${FILES[$idx]}" > "$TMP/triangle_$(printf '%06d' "$idx").dat" || { echo "Invalid simplex: ${FILES[$idx]}" >&2; exit 1; }
done
read -r XMIN XMAX YMIN YMAX ZMIN ZMAX < <(awk 'NR==1 {a=b=$1;c=d=$2;e=f=$3} {if($1<a)a=$1;if($1>b)b=$1;if($2<c)c=$2;if($2>d)d=$2;if($3<e)e=$3;if($3>f)f=$3} END {dx=b-a;dy=d-c;dz=f-e;if(dx==0)dx=1;if(dy==0)dy=1;if(dz==0)dz=1;printf "%.16g %.16g %.16g %.16g %.16g %.16g\n",a-.08*dx,b+.08*dx,c-.08*dy,d+.08*dy,e-.08*dz,f+.08*dz}' "$TMP"/triangle_*.dat)
export TMP MODE FPS XMIN XMAX YMIN YMAX ZMIN ZMAX
