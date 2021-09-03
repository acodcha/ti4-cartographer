#!/bin/sh
set -e
cd "${0%/*}"
../build/bin/ti4cartographer --players 8 --layout regular --aggression moderate
