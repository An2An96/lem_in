#!/bin/sh
RES=`norminette srcs/*.c srcs/core srcs/visual includes`
echo $RES | grep 'Error'