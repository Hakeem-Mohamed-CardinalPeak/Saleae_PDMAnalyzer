#!/usr/bin/env python2

# Takes in a CSV file with 4 PDM channels in 
#  rows 1, 2, 3, 4 and produces a binary output
#  containing raw PCM data calculated via a 
#  first order CIC filter

import sys
import struct
import array
import csv

fin = open(sys.argv[1], 'rb')			# input file
fout = open(sys.argv[1]+'.hex', 'wb');	# output file
decim_r	= int(sys.argv[2])				# decimation factor
bitdepth = 255	#int(sys.argv[3])				# bit depth, max value, eg 255

reader = csv.reader(fin)
rownum = 0

# keep a list each channel for the running average
ch1 = []
ch2 = []
ch3 = []
ch4 = []

for row in reader:
	if rownum == 0:
		print "ignoring header"
	else:
		# integrate
		# grab pdm sample for each channel, add to list for running average
		ch1.append(int(row[1], 10))
		ch2.append(int(row[2], 10))
		ch3.append(int(row[3], 10))
		ch4.append(int(row[4], 10))
		
		# comb
		# get rid of oldest sample once decimation factor reached
		if len(ch1) >= decim_r+1:
			ch1.pop(0)
			ch2.pop(0)
			ch3.pop(0)
			ch4.pop(0)
		
		# decimate - check against decimation factor
		if (rownum % decim_r) == 0:
			# write pcm sample to fout
			# calculate average of list, multiply by bitdepth
			outval = (float(sum(ch1))/float(decim_r))*bitdepth
			fout.write(struct.pack('>B', int(outval)))
			outval = (float(sum(ch2))/float(decim_r))*bitdepth
			fout.write(struct.pack('>B', int(outval)))
			outval = (float(sum(ch3))/float(decim_r))*bitdepth
			fout.write(struct.pack('>B', int(outval)))
			outval = (float(sum(ch4))/float(decim_r))*bitdepth
			fout.write(struct.pack('>B', int(outval)))
			
	rownum+=1
		
fin.close()
fout.close()