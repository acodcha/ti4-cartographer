#!/bin/sh
set -e
cd "${0%/*}"
../build/bin/ti4cartographer --players 7 --layout regular --aggression high
