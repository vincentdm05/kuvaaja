#!/usr/bin/env bash

cd "`dirname "$0"`"

for arg in "$@"
do
  case "$arg" in
    -b=*|--build=*)
    build_type="${arg#*=}"
    shift
    ;;
    *)
    shift
    ;;
  esac
done

if [ "`echo $build_type | tr -s  '[:upper:]' '[:lower:]'`" = debug ]; then
  build_type=Debug
  build_dir=Debug
else
  build_type=Release
  build_dir=Release
fi

root_dir=`pwd`
build_dir="$root_dir"/build/$build_dir

errorExit()
{
  printf "$1\n" 1>&2
  exit 1
}

if [[ -e "$build_dir" && ! -d "$build_dir" ]]; then
  errorExit "The build directory cannot be created."
elif [ ! -d "$build_dir" ]; then
  mkdir -p "$build_dir" || errorExit "Could not create ${build_dir}."
fi

cd "$build_dir"

cmake -DCMAKE_BUILD_TYPE=$build_type ../..
make -j `getconf _NPROCESSORS_ONLN`
