#!/bin/sh

xtest(){
	xterm -e true
	return $?
}

dwmpath=$HOME/src/Suckless/dwm/extra/ #"$(dirname "$(readlink $0)")"
echo "$0: dwmpath: $dwmpath" >&2

while true
do
	. "$dwmpath"/env
	dwm
	xtest || break
done

echo "$0: exit" >&2
