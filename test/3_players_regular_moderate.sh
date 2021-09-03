#!/bin/sh
set -e
cd "${0%/*}"
../build/bin/ti4cartographer --players 3 --layout regular --aggression moderate
