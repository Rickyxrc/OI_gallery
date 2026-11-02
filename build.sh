#!/usr/bin/env bash
# 一键编译脚本。用法：
#   ./build.sh                                # 全部：大合集 + 所有比赛 + 所有单题
#   ./build.sh index                          # 只编译大合集
#   ./build.sh contest Contest/at123          # 只编译某场比赛
#   ./build.sh problem Contest/at123/a/a.typ  # 只编译某道题
#
# 题解开关（关闭 => 习题册样式）：SOLUTION=off ./build.sh ...
#
# 输出到 build/ 目录（结构镜像源文件）。
# 手动编译单文件时记得加 --root .，例如：
#   typst compile Contest/at123/a/a.typ a.pdf --root .
set -euo pipefail
shopt -s nullglob
ROOT=$(cd "$(dirname "$0")" && pwd)
cd "$ROOT"
OUT=${OUT:-build}
case "${SOLUTION:-true}" in
  off|false|0|no) SHOW=false ;;
  *) SHOW=true ;;
esac

c() {
  mkdir -p "$(dirname "$2")"
  echo "=> $1  ->  $2"
  typst compile "$1" "$2" --root "$ROOT" --input "show-solution=$SHOW"
}

case "${1:-all}" in
  index)
    c index.typ "$OUT/index.pdf"
    ;;
  contest)
    c "$2/main.typ" "$OUT/$2/main.pdf"
    ;;
  problem)
    c "$2" "$OUT/${2%.typ}.pdf"
    ;;
  *)
    c index.typ "$OUT/index.pdf"
    for m in Contest/*/main.typ; do
      c "$m" "$OUT/${m%/main.typ}/main.pdf"
    done
    for p in Contest/*/*/*.typ; do
      b=$(basename "$p")
      case "$b" in *.prob.typ|*.sol.typ) continue;; esac
      c "$p" "$OUT/${p%.typ}.pdf"
    done
    ;;
esac
echo "完成，输出目录：$OUT"