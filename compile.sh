#!/usr/bin/env bash

cd `dirname "$0"`

root_dir=`pwd`
build_dir="$root_dir"/build

if [[ -e "$build_dir" && ! -d "$build_dir" ]]; then
  printf "The build directory cannot be created." 1>&2
  exit 1
elif [ ! -d "$build_dir" ]; then
  mkdir "$build_dir"
fi

cd "$build_dir"

cmake ..
make
