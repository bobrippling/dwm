#!/bin/sh

if [ $# -ne 1 ]
then
	echo "Usage: $0 window" >&2
	exit 1
fi

win=$(lsw -i|grep "$1"|awk '{print $NF}'|head -1)

if [ -n "$win" ]
then xprop -root -f _DWM_FOCUS 32c -set _DWM_FOCUS $win
else
	echo no win
	exit 1
fi
