#include <stdio.h>
#include <iostream.h>
#include <conio.h>
#include <string.h>
#define  BS 0x5c
class Mach3Splitter 
{
public:
	~Mach3Splitter();
	Mach3Splitter();
	char in_file[25],out_file[25],in_line[80],LastZ[80];
	char out_line[132];
	FILE *in, *out;
	int x,iout,getch_count;
	void Preamble();
	void EndFile();
};
void Mach3Splitter::Preamble()
{
	fprintf(out,"G20\n");
//	fprintf(out,"\(Absolute Coordinates\)\n");
	fprintf(out,"G90\n");
//	fprintf(out,"S30000\n");
	fprintf(out,"G00 Z0.7500  \n");

	fprintf(out,"M03\n");
	fprintf(out,"G04 P3.000000\n");
	fprintf(out,"G01 Z-0.0070 F5  \n");
	//fprintf(out,"\n");	
};
void Mach3Splitter::EndFile()
{
	fprintf(out,"G01 Z0.4000 F5   \n");
	fprintf(out,"M05\n");
	fprintf(out,"M02\n");
};
Mach3Splitter::Mach3Splitter ()
{
	in_file[0]=0x00;
	out_file[0]=0x00;
	in_line[0]=0x00;
	out_line[0]=0x00;
	iout=0;
	getch_count=0;
	cout <<"Constructor \n";
};
Mach3Splitter::~Mach3Splitter ()
{

	cout <<"Destructor \n";
	fclose(in);
	fprintf(out,"}\n");
	fclose(out);
};



int main()
{
	int lineCount = 0;
	int File_Count = 1;
	Mach3Splitter Help;
	printf(" Please enter the input file name.\n");
	cin >> Help.in_file;
//	strcat(Help.out_file,Help.in_file);
//	strcat(Help.out_file,"1.gbr");
	printf("%s infile %s outfile \n",Help.in_file,Help.out_file);
sprintf(Help.out_file,"Mill%d.tap",File_Count);
	Help.in = fopen(Help.in_file,"r");
	Help.out = fopen(Help.out_file,"w");
	
	
	while(!feof(Help.in))
	{
		lineCount++;
		fgets(Help.in_line,80,Help.in);
		fprintf(Help.out,"%s",Help.in_line);
		//     G00 Z0
		Help.LastZ[0]=0x00;
		if (strncmp (Help.in_line,"G00 Z0",6) == 0)
			strcat(Help.LastZ,Help.in_line);
		if(lineCount>480)
		{
		Help.EndFile();
		lineCount=0;
		File_Count++;
		Help.out_file[0]=0x00;
		sprintf(Help.out_file,"Mill%d.tap",File_Count);
		fclose(Help.out);
		Help.out = fopen(Help.out_file,"w");
		
		Help.Preamble();
		fprintf(Help.out,Help.LastZ);
		}
	}

	return 0;
}

// ' = 0x27
// / = 0x2f
// \ = 0x5c
// " = 0x22


