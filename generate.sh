#!/bin/sh
ragel -C rainbows.rl -o rainbows.cpp
ragel -V -p rainbows.rl > rainbows.dot
dot rainbows.dot -Tpdf -o rainbows.pdf
