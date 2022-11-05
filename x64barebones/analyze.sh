#!/bin/bash

pvs-studio-analyzer trace  -- make all
pvs-studio-analyzer analyze
plog-converter -a '64:1,2,3;GA:1,2,3;OP:1,2,3' -t tasklist -o report.tasks PVS-Studio.log
