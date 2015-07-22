# bedFileTools

bedpeTobed:
This is a prgram to convert bedpe file to bed file

* the leftmost start site will be used 
* the rightmost start site will be used 
* the strand for 1st read in the pair

usage: 
		
	./bedpeTobed <bedpeFile> | <stdin>

filterPairToBed:
This program help to resovle the bug in ***bedtools pairtobed***, where ***-type both*** does not output very well.

* require both reads mapped to the feature
* tune ***-f option***  for desirable overlaping region

usage: 

	./filterPairToBed -i <pairtobed File> | <stdin> [-f <fraction>]


