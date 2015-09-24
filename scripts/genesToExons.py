#!/bin/env python

import fileinput

for line in fileinput.input():
    column = line.split('\t')
    length = column[10].split(',')
    start = column[11].split(',')
    for i in range(len(start)-1):
        exonStart = int(column[1]) + int(start[i])
        exonEnd = exonStart + int(length[i])
        print '%s\t%s\t%s\t%s\t%s\t%s' %(column[0],exonStart,exonEnd,column[3],str(i),column[5])
