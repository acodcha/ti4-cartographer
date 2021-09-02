#!/bin/sh
set -e
cd "${0%/*}"
../build/bin/ti4cartographer --players 5 --layout regular --aggression medium

