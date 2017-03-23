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
	
	void Preamble();
	void EndFile();
	void ViewMate(char *);  //char *
	void PreambleVM();
	char in_file[25],out_file[25],in_line[80],LastZ[80];
	char out_line[132];
	double Zetch,Zsafe;
	FILE *in, *out, *ViewMateFile;
	int x,iout,getch_count;
};
void Mach3Splitter::Preamble()
{
	fprintf(out,"G20\n");
	fprintf(out,"G90\n");
	fprintf(out,"G00 Z%6.4f  \n",Zsafe);
	fprintf(out,"M03\n");
	fprintf(out,"G04 P3.000000\n");
	fprintf(out,"G01 Z%6.4f F5  \n",Zetch);
};

void Mach3Splitter::PreambleVM()
{
	char xxx;
	xxx='%';
	fprintf(ViewMateFile,"G75*\n");
	fprintf(ViewMateFile,"G70*\n");
	fprintf(ViewMateFile,"%cFSLAX24Y24*%\n",xxx);
	fprintf(ViewMateFile,"D10*\n"); 	
};



void Mach3Splitter::ViewMate(char *s1)   // char []s1
{
	double x,y;
	int x1,y1,D01=0;
	int i,ii,ystart=0;
	char  junk[35];
	for(i=0;i<25;i++)junk[i]=0X00;
	
	junk[0]='X';
	//if(strncmp(s1,"G00 Z0.4000",11)==0)printf("Start of Block at  ##%s## \n",s1);
	if(strncmp(s1,"G00 X",5)==0)D01=0;
	if(strncmp(s1,"G01 X",5)==0)D01=1;
	if(strncmp(s1,"G01 Z",5)==0)
	{
		//	printf("Start of Block at ##%s## \n",s1);
	}
	else 
	
	if((strncmp(s1,"G01 X",5)==0)||(strncmp(s1,"G00 X",5)==0))
	{
		if(s1[4]==junk[0])
		{         
			junk[0]='X';
			ii=1;
			for(i=5;i<14;i++)
			{
				if((s1[i]!=' ')&&(s1[i]!='.'))
				{
					junk[ii]=s1[i];
					ii++;
					ystart=i+1;
				}
			}	
			junk[ii]='Y';
			for(i=ystart;i<21;i++)
			{
				if((s1[i]!=' ')&&(s1[i]!='.'))
				{
					junk[ii]=s1[i];
					ii++;
				}
			}	
			junk[ii]='D';
			ii++;
			junk[ii]='0';
			ii++;
			junk[ii]='0';
			if(D01>0)junk[ii]='1';
			ii++;
			junk[ii]='*';
			
			// G01 X1.7632  Y1.3551 
			// G01 X27.9633 Y13.2752 
			// 012345678901234567892
			//            1111111112  
			
		}
		fprintf(ViewMateFile,"%s\n",junk);		
	}
	s1[0]=0x00;
}

void Mach3Splitter::EndFile()
{
	fprintf(out,"G01 Z%6.4f F5   \n",Zsafe);
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
	//	cout <<"Constructor \n";
};
Mach3Splitter::~Mach3Splitter ()
{
	//	cout <<"Destructor \n";
	fclose(in);
	fprintf(out,"}\n");
	fclose(out);
};

int main()
{
	int lineCount = 0;
	int File_Count = 1;
	Mach3Splitter PCB;
	PCB.Zetch = -0.007;
	PCB.Zsafe = 0.7500;
	char YesNo='n';
	
	printf(" Would an etch depth of  -0.007 and a safe Z height work, y or n.\n");
	cin >> YesNo;
	if(YesNo != 'y')
	{
		printf(" Please enter the etch depth, -0.007 would be 7 mils etch down.\n");
		cin >> PCB.Zetch;
		printf(" Please enter the Z safe height 0.75 would be 750 mills above your Z 0.0.\n");
		cin >> PCB.Zsafe;
	}
	printf(" Please enter the input file name.\n");
	cin >> PCB.in_file;
	sprintf(PCB.out_file,"Mill%d.tap",File_Count);
	PCB.in = fopen(PCB.in_file,"r");
	if(PCB.in ==NULL)
	{
		printf("File not found, try again. %s\n",PCB.in_file);
		exit (0);
	}
	PCB.out = fopen(PCB.out_file,"w");
	PCB.ViewMateFile = fopen("View.Mate","w");
	PCB.PreambleVM();
	while(!feof(PCB.in))
	{
		lineCount++;
		fgets(PCB.in_line,80,PCB.in);
		fprintf(PCB.out,"%s",PCB.in_line);
		//     G00 Z0
		PCB.LastZ[0]=0x00;
		if (strncmp (PCB.in_line,"G00 Z0",6) == 0)
		strcat(PCB.LastZ,PCB.in_line);
		if(lineCount>480)
		{
			PCB.EndFile();
			lineCount=0;
			File_Count++;
			PCB.out_file[0]=0x00;
			sprintf(PCB.out_file,"Mill%d.tap",File_Count);
			fclose(PCB.out);
			PCB.out = fopen(PCB.out_file,"w");
			
			PCB.Preamble();
			fprintf(PCB.out,PCB.LastZ);
		}
			PCB.ViewMate(PCB.in_line);
	}

	return 0;
}

// ' = 0x27
// / = 0x2f
// \ = 0x5c
// " = 0x22


