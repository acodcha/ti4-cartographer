#!/bin/sh
set -e
cd "${0%/*}"
../build/bin/ti4cartographer --players 8 --layout large --aggression moderate
