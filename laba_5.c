#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string_size 256

void Viewing_file(FILE *file)
{
	int i;
	do {
		fread(&i,sizeof(int),1,file);
		if(feof(file)) break;
		printf("%5d",i);
	}
	while(!feof(file));
	printf("\n");
}

void Create_file(FILE* file)
{
	int i;
	char str[string_size],*str_pointer;
	str_pointer=str;
	do {
		fgets(str, string_size, stdin);
		if (*str == '\n') return;
		i=strtol(str, &str_pointer, 10);
		if(*str_pointer == '\n') {
			fwrite(&i,sizeof(int), 1, file);
		}
		else{
			printf("ERROR INPUT! ENTER NUMBER");
			continue;
		}	
	}
	while(1);
}

void Append(FILE *file, FILE* out_file, int i)
{
     while(1){
        	fwrite(&i,sizeof(int),1,out_file);
            if(fseek(file,-2*sizeof(int),1)) return;
          	fread(&i,sizeof(int),1,file);
        }
}

int Rewrite(FILE* file, FILE* out_file,int i1, int i2)
{
	while(i1>=i2){
        fwrite(&i1,sizeof(int),1,out_file);
		if(fseek(file,-2*sizeof(int),1)) {
		    fseek(file,0,0);
		    break;
		}
		fread(&i1,sizeof(int),1,file);
    }
    return i1;
}

void Sorting(FILE* in_file_1, FILE* in_file_2, FILE* out_file)
{
	int i1,i2;
    fseek(in_file_1,-sizeof(int),2);
    fseek(in_file_2,-sizeof(int),2);
  	fread(&i1,sizeof(int),1,in_file_1);
	fread(&i2,sizeof(int),1,in_file_2);
    do{ 
        if (i1>=i2) {
        	i1= Rewrite(in_file_1, out_file, i1, i2);
        }	
		else {  
      		i2= Rewrite(in_file_2, out_file, i2, i1);
        }
    }
	while(ftell(in_file_1)>0 && ftell(in_file_2)>0);
    if(ftell(in_file_1)){
    	Append(in_file_1,out_file,i1);
    }
    if(ftell(in_file_2)){
     	Append(in_file_2,out_file,i2);
     }
return;
}

void Help(void)
{
    printf
        ("================================================================================\n"
         "MANUAL:\n"
         "Enter the number in  files in ascending.\n"
         "================================================================================\n"
         "Program to merge the files in ascending to descending file.\n"
         "================================================================================\n");
}

FILE* Open_file(char* file_name, char* mode)
{
	FILE *file;
	if(!(file=fopen(file_name,mode))) {
		puts("ERROR unable to open file");
		exit(1);
	}
	return file;
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if (!(strcmp(argv[1], "-h")))
            Help();
    }
	FILE *in_file_1, *in_file_2, *out_file;
	in_file_1=Open_file("file1","wb");
	in_file_2=Open_file("file2","wb");
	out_file=Open_file("file3","wb");
	puts("Enter the number in the first file in ascending:");
	Create_file(in_file_1);
	puts("Enter the number in the second file in ascending:");
	Create_file(in_file_2);
	fclose(in_file_1);
	fclose(in_file_2);
	in_file_1=Open_file("file1","rb");
	in_file_2=Open_file("file2","rb");
	Sorting(in_file_1,in_file_2,out_file);
	fclose(in_file_1);
	fclose(in_file_2);
	fclose(out_file);
	out_file=Open_file("file3","rb");
	puts("THE OUTPUT FILE:");
	Viewing_file(out_file);
	return 0;
}



