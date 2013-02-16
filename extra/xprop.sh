#!/bin/sh

echo Class, Instance, Title
xprop | awk -F '"' '/^WM_CLASS/ { printf("\"%s\":\"%s\":",$4,$2) }; /^WM_NAME/ { printf("\"%s\"\n",$2) }'
