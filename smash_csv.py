#!/usr/bin/env python2

# Takes in 2 CSV files and smashes them together, 
#  with first 3 columns from the first and columns 
#  2 and 3 from the 2nd

import sys
import struct
import array
import csv

fin1 = open(sys.argv[1], 'rb')
fin2 = open(sys.argv[2], 'rb')
fout = open(sys.argv[1]+'_smash.csv', 'wb');

reader1 = csv.reader(fin1)
reader2 = csv.reader(fin2)
writer = csv.writer(fout)

for row in reader1:
	reader2line = reader2.next()
	# timestamp from first file
	writer.writerow(row + [reader2line[1]] + [reader2line[2]])
		
fin1.close()
fin2.close()
fout.close()