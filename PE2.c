/* PLEASE DO NOT MODIFY A SINGLE STATEMENT IN THE TEXT BELOW.
READ THE FOLLOWING CAREFULLY AND FILL IN THE GAPS

I hereby declare that all the work that was required to 
solve the following problem including designing the algorithms
and writing the code below, is solely my own and that I received
no help in creating this solution and I have not discussed my solution 
with anybody. I affirm that I have read and understood
the Senate Policy on Academic honesty at 
https://secretariat-policies.info.yorku.ca/policies/academic-honesty-senate-policy-on/
and I am well aware of the seriousness of the matter and the penalties that I will face as a 
result of committing plagiarism in this assignment.

BY FILLING THE GAPS,YOU ARE SIGNING THE ABOVE STATEMENTS.

Full Name:
Student Number:
Course Section:
eecs user id:
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define fieldLength 200


#define diskFile "diskFile.dat"
#define courseFile "course.txt"

struct db_type
{
   char name[fieldLength];
   int age;
   char course1[fieldLength];
   char course2[fieldLength];
   char status[fieldLength];
 };

struct courseInfo
{ 
  char code [20]; // e.g., EECS2030
  char title [fieldLength];
  char  date [20];
  char time_start [20];
  char time_end [20];
  char  location [20]; 
};
 
 
struct courseInfo courseArr[SIZE]; // global variable  array of struc
     

char prompt_menu(void);
void init_list(struct db_type * pArr[]); 
void clearDB(struct db_type * pArr[]);
void init_courseArr(void);

void writeDisk(struct db_type * pArr[]); 
void emptyDisk(void); 
void loadDisk(struct db_type * pArr[]); 





int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    init_courseArr();  // load course from diskfile
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
         case 'w': writeDisk(db_pArr);  break;    
         case 'l': loadDisk(db_pArr); break;
         case 's': sort(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
         case 'e': emptyDisk();break;

         case 'v': displayCourses();break;
         case 'p': swap(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}

void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

void clearDB(struct db_type * pArr[]){
   char c3[3];
   printf("are you sure to clear db? (y) or (n)? ");
 
   fgets(c3,3,stdin);
   
   if(! strcmp(c3, "y\n"))  
      init_list(pArr);
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
    printf("|    %-20s","(L)oad disk");
    printf("%-20s","(W)rite disk");
    printf("(E)mpty disk\t|\n");
  
    printf("|    %-20s", "(V)iew courses");//|\tSwa(p) record\t(Q)uit\t\t\t\t|\n");
    printf("%-20s","(Q)uit");
    printf("*Case Insensitive*\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
   
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
	 
 }
}

/* display all or specified course */
void displayCourses(void){ 
    printf("DISPLAY COURSES");
}
//     char course[9];
//     char chk[20] = "EECS0000"; 
//     // the provide PE2.out uses "%s\t%-40s%-5s %s-%s   %s\n" as formatting string for printing each course info
//     printf("course code (or 'a')? ");
//     fgets(course,8,stdin);
//     if (course[0]=='a'){ 
//         printf("===================================================================================\n");  
//         //printf("%d\n",checker("EECS0000",courseArr[3].code)) ;
//         int i=0; 
//         while(strcmp(chk,courseArr[i].code)!=0)
//         {
//             printf("%s\t%-40s%-5s %s-%s   %s\n",courseArr[i].code,courseArr[i].title,courseArr[i].date,courseArr[i].time_start,courseArr[i].time_end,courseArr[i].location);
//             i++;
//         }
//         printf("===================================================================================\n");
//         // upper part Works
//     }
    
//     else if ((int) strlen(course) > 1 && (int) strlen(course) < 6){
//         char EE[9]="EECS";
//         strcat(EE,course);
//         int post1 = postion(EE);
//         print(post1);
//     }
    
//     else{
//         int post = postion(course);
//         print(post);
//     }
     
//   }

// int print(int post){
//   if (post!=-1)
//     {
//       printf("%s\t%-40s%-5s %s-%s   %s\n",courseArr[post].code,courseArr[post].title,courseArr[post].date,courseArr[post].time_start,courseArr[post].time_end,courseArr[post].location);
//     } else{
//       printf("error! course does not exist");
//     }
// }
// int postion(char comp1[9]){
//   int result=-1;
//   char chk[20] = "EECS0000"; 
//   int x = 0 ;
  
//   while(strcmp(chk,courseArr[x].code)!=0){
//     if(strstr(courseArr[x].code,comp1) != NULL){
//       result=x;    
      
//     }
//     x++;
//   }
//   return result ;
//   }

/* input items into the list */
void enterNew(struct db_type * pArr[SIZE]){  
	;
   

}

/* display records */
void displayDB(struct db_type * pArr[]){
  ;
 
}


/* remove an existing item */
void removeRecord (struct db_type * pArr[])	
{
  ;

}

/* swap records */
void swap(struct db_type * pArr[]){
   
	; 
} 

/* load from course.txt, store into (global) array of courses  */
void init_courseArr(void){ 
 
   FILE *fr; //file pointer
   fr = fopen (courseFile, "r");
   char arr[50];  
   int count = 0;
   while ((fgets(arr,100,fr)) != NULL)
   {  
     strncpy(courseArr[count].code,  arr, strlen(arr)-1); // remove \n  
     courseArr[count].code[strlen(arr)-1] = '\0';  //to be safe
	 
     fgets(arr,100,fr);  
     strncpy(courseArr[count].title ,  arr, strlen(arr)-1);
     courseArr[count].title[strlen(arr)-1] = '\0';  //to be safe
     
          
     fgets(arr,100,fr); 
     strncpy(courseArr[count].date,  arr, strlen(arr)-1);
     courseArr[count].date[strlen(arr)-1] = '\0';  //to be safe
	   
     // other ways, remove \n before
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_start,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_end,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].location,  arr); 
	  
     count++;
     fgets(arr,100,fr); // read the empty line
   }

   strcpy(courseArr[count].code, "EECS0000"); // a terminator token structure

   fclose(fr);
	 
 }
    
/************************ DISK IO *****************************************************************/

void writeDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;

  if ( (fp=fopen(diskFile,"ab")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  
  for (i=0; i< SIZE ; i++)
  {
     if ( pArr[i] != NULL)
     {  
       if (fwrite( pArr[i], sizeof(struct db_type), 1, fp) != 1)
       { 
          printf("file write error\n");
       }
     } 
   }
   fclose(fp);

}

void emptyDisk(void){

  FILE *fp;
  
  char c3[3];
  printf("are you sure to empty disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;
 
  //else
  if ( (fp = fopen(diskFile,"w")) == NULL)
  {
     printf("no file to open\n");
     return;
  }
  fclose(fp); // open close, will empty the file
}


void loadDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;
  char c3[3];
  printf("will overwrite current records. are you sure to load disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;

  struct db_type * tmp;  
  
  if ( (fp = fopen(diskFile,"r")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  init_list(pArr);
  for (i=0; i < SIZE ; i++)
  {    
     
     tmp =  (struct db_type *) malloc (sizeof(struct db_type));   
	   
     if (fread( tmp, sizeof(struct db_type), 1, fp) != 1)
     {
       if (feof(fp))
       { fclose(fp); 
         return;
       }
       printf("file read error\n");
     }
     else pArr[i] = tmp;
  }
}

/****bonus*************************************************************************************/

/* sort the records by ages */
void sort(struct db_type * pArr[])
{
 

}  

 
 
