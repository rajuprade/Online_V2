#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
//when using gcc compiler you need to "gcc -lm main.c" in order to link it to the math library//
 
// Opens the file and reads in the stream //
void load_data(char fname[200])
{
double data[7][5];//declare array (random number)
int j , i; 
 double num;
 
  FILE *fp = fopen(fname, "r");
  FILE *fp2 = fopen("/home/teleset/Desktop/My_program/Results", "w"); //opens up a file called "Results"
                                                               // and allows writing//
     
    if (fp == NULL) //checks for the file
    { printf("\n Can’t open %s\n",fname);
        exit;
    }   
 
//reads in the data to an array, analyzes, and the prints the array
  
                  
for(j = 0; j < 5; j++) //repeats for max number of columns
  {
    for (i=0; i< 7; i++)
      {
        fscanf(fp, "%d", &num);
          data[i][j] = num;
      }
   }    
 
for(j = 0; j < 5; j++) //repeats for max number of columns
  {
    for (i=0; i< 7; i++)
      { num = data[i][j];
    fprintf(fp2, "%d ", num);
      }
    fprintf(fp2, "\n");
  }
 
// add in laterz fprintf(fp2,"%f%f", radius, velocity);//
                 
    fclose(fp2);
    fclose(fp);
}
 
 
 
//Main Function //
     
    int main (void)
    {
        char path[200], basename[200], input_fname[200]; 
        // Stores path & basename of file, input_fname: combines path and basename//
        char str[50] = {0}; //stores filename
         
        printf("please input the file name: ");
        scanf("%s", str); // gets input from user, %s reads characters, variable i//
          
        sprintf(path, "/home/teleset/Desktop"); //Change pathway as needed //
        snprintf(basename, 50, "%s", str); // stores basename from i//
        sprintf (input_fname, "%s/%s", path, basename); //combines path and basename to get input_fname//
         
        printf("Using file: %s\n", input_fname); //tells user which file is being used
 
        load_data(input_fname); //function to load input data //
         
                    
                        
        return 0;
    }
