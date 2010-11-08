#!/bin/sh

egrep '\binit_task\b' $1 | cut -d' ' -f1 > init_task_vaddr

