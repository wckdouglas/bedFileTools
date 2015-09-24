#!/bin/env python

import fileinput

for line in fileinput.input():
    column = line.split('\t')
    length = column[10].split(',')
    start = column[11].split(',')
    for i in range(len(start)-2):
        intronStart = int(column[1]) + int(length[i]) + int(start[i]) +1
        intronEnd = int(column[1]) + int(start[i+1]) -1 
        print '%s\t%s\t%s\t%s\t%s\t%s' %(column[0],intronStart,intronEnd,column[3],str(i),column[5])
