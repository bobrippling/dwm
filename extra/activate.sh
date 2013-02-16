#!/bin/sh

[ $# -ne 0 ] && echo "$0: ignoring args" >&2

arg=$(
for i in $(xdotool search --onlyvisible ".*")
do
	win_id="${i}"
	win_class=$(xprop -id ${win_id} WM_CLASS | cut -d'"' -f2)
	win_title=$(xprop -id ${win_id} _NET_WM_NAME | cut -d'"' -f2)

	echo "${win_title}|${win_class}|${win_id}"
done | grep -v ':\s*not found' | dmenu -l 5 | cut -d'|' -f3)

[ -n "$arg" ] && xdotool windowactivate "$arg"
