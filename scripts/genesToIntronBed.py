#!/bin/env python

import fileinput
import numpy as np

for line in fileinput.input():
    columns = line.split('\t')
    chrom = columns[0]
    geneStart = int(columns[1])
    geneEnd = int(columns[2])
    name = columns[3]
    strand = columns[5]
    geneLength = geneEnd - geneStart
    blockCount = int(columns[9]) 
    if blockCount > 1:
        exonStartSites = np.array([columns[11].split(',')[i] for i in range(blockCount)],dtype=np.int64)
        assert len(exonStartSites) == blockCount, 'wrong start annotation'
        exonBlock = np.array([columns[10].split(',')[i] for i in range(blockCount)],dtype=np.int64)
        assert len(exonStartSites) == blockCount, 'wrong length annotation'
        for i in range(blockCount-1):
            intronStart = exonStartSites[i] + exonBlock[i] + geneStart + 1
            intronEnd = exonStartSites[i+1] + geneStart - 1
            if intronStart < intronEnd:
                print '%s\t%i\t%i\t%s\t%i\t%s' %(chrom,intronStart,intronEnd,name,i,strand)
