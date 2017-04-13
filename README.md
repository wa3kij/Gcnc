# Gcnc
CncG.tds-----Borlands setup file.
Mill1.tap----Sample output file
Mill2.tap----Sample output file
Mill3.tap----Sample output file
View.Mate – Sample Viewmate input file.
ReadMe.docx---This file.

bot.gbr ------Sample gerber file from Eagle 5.11 using ULP: 
				PCB-GCODE Version 3.6.0.4 
				John T. Johnson 
				pcbgcode@pcbgcode.org 
				January 16, 2013

CncG.cpp -----C code for splitting up a gerber file for use with a free version of Mach3 
			which is limited to 500 lines of input g code.
CncG.exe-----Executable copy of the above code, compiled with Borland C++ 5.5.1


To run this program you will need an input file like bot.ggr

It will ask for the Zetch depth to be reloaded into each extra file to continue 
where the last file left off.

It will ask for a Zsafe value which is the Z position where the cutter will be parked
when changing files.

Then it will ask for the full file name.
It then will make as many files as necessary with less then 500 lines 
to mill your board.

Please enter the etch depth, -0.007 would be 7 mils etch down.
-0.010
Please enter the Z safe height 0.75 would be 750 mills above your Z 0.0.
0.400
Please enter the input file name.
bot.gbr

These responses would give an 
			etch depth of 10 mills 
			safe Z location of 400 mils above the board 
			input file of bot.gbr
			create 3 files
			Mill1.tap----Sample output file
			Mill2.tap----Sample output file
			Mill3.tap----Sample output file

Have fun.
