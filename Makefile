all: cpp dot pdf

cpp:
	ragel -C rainbows.rl -o rainbows.cpp

dot:
	ragel -V -p rainbows.rl > rainbows.dot

pdf:
	dot rainbows.dot -Tpdf -o rainbows.pdf