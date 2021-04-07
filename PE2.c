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

Full Name: Diego Santosuosso
Student Number: 217339987
Course Section: M
eecs user id: nicodemo
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 30
#define fieldLength 200


#define diskFile "diskFile.dat"
#define courseFile "coursefinal.txt"    //REMEMBER CHANGE 

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
int counter = 0; //global variable counter (counts records of students added to DB)
     

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
   
   if(! strcmp(c3, "y\n")){
       init_list(pArr);
       counter = 0;
   }  
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
    printf("Case Insensitive\t|\n");
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
    char c9[9]; //input
    char cf[9]; //fixed input


    //get user input
    printf("course code (or 'a')? ");
    fgets(c9,9,stdin);
    // c9[strlen(c9-1)] = '\0';

    // PART (A) if input is 'a'
    if (strlen(c9) == 2 && c9[0] == 'a'){
        int i = 0;
        printf("===================================================================================\n");  
        while(strcmp("EECS0000", courseArr[i].code) != 0){
            printf("%s\t%-40s%-5s %s-%s   %s\n",courseArr[i].code,courseArr[i].title,courseArr[i].date,courseArr[i].time_start,courseArr[i].time_end,courseArr[i].location);
            i++;
        }
        printf("===================================================================================\n");    
    }

    // PART (B) if input is course number only (e.g. 2031)
    else if (strlen(c9)==5){
        int i = 0;
        int var = -20;  //arbitrary number picked to represent errors
        strcpy(cf, "EECS");
        strcat(cf,c9);

        while(strcmp("EECS0000", courseArr[i].code) != 0){
            if(strstr(cf, courseArr[i].code) != NULL){
                var = i;
            }
            i++;
        }
        print_course(var); 
    }

    // PART (C) if input is full course (e.g. EECS2031)
    else{
        int i = 0;
        int var = -20;  //arbitrary number picked to represent errors

        while(strcmp("EECS0000", courseArr[i].code) != 0){
            if(strstr(c9, courseArr[i].code) != NULL){
                var = i;
            }
            i++;
        }
        print_course(var); 
    }
}

int print_course(int i){
    if (i==-20){
        printf("error! course does not exist");
    } else{
        printf("%s\t%-40s%-5s %s-%s   %s\n",courseArr[i].code,courseArr[i].title,courseArr[i].date,courseArr[i].time_start,courseArr[i].time_end,courseArr[i].location);
    }
    return 0;
}

float cast_time(char str1[10]){
    if (strcmp(str1, "00:00")){
        return 0.0;
    }
    else if(strcmp(str1, "00:30")){
        return 0.5;
    }
    else if(strcmp(str1, "01:00")){
        return 1.0;
    }
    else if(strcmp(str1, "01:30")){
        return 1.5;
    }
    else if(strcmp(str1, "02:00")){
        return 2.0;
    }
    else if(strcmp(str1, "02:30")){
        return 2.5;
    }
    else if(strcmp(str1, "03:00")){
        return 3.0;
    }
    else if(strcmp(str1, "03:30")){
        return 3.5;
    }
    else if(strcmp(str1, "04:00")){
        return 4.0;
    }
    else if(strcmp(str1, "04:30")){
        return 4.5;
    }
    else if(strcmp(str1, "05:00")){
        return 5.0;
    }
    else if(strcmp(str1, "05:30")){
        return 5.5;
    }
    else if(strcmp(str1, "06:00")){
        return 6.0;
    }
    else if(strcmp(str1, "06:30")){
        return 6.5;
    }
    else if(strcmp(str1, "07:00")){
        return 7.0;
    }
    else if(strcmp(str1, "07:30")){
        return 7.5;
    }
    else if(strcmp(str1, "08:00")){
        return 8.0;
    }
    else if(strcmp(str1, "08:30")){
        return 8.5;
    }
    else if(strcmp(str1, "09:00")){
        return 9.0;
    }
    else if(strcmp(str1, "09:30")){
        return 9.5;
    }
    else if(strcmp(str1, "10:00")){
        return 10.0;
    }
    else if(strcmp(str1, "10:30")){
        return 10.5;
    }
    else if(strcmp(str1, "11:00")){
        return 11.0;
    }
    else if(strcmp(str1, "11:30")){
        return 11.5;
    }
    else if(strcmp(str1, "12:00")){
        return 12.0;
    }
    else if(strcmp(str1, "12:30")){
        return 12.5;
    }
    else if(strcmp(str1, "13:00")){
        return 13.0;
    }
    else if(strcmp(str1, "13:30")){
        return 13.5;
    }
    else if(strcmp(str1, "14:00")){
        return 14.0;
    }
    else if(strcmp(str1, "14:30")){
        return 14.5;
    }
    else if(strcmp(str1, "15:00")){
        return 15.0;
    }
    else if(strcmp(str1, "15:30")){
        return 15.5;
    }
    else if(strcmp(str1, "16:00")){
        return 16.0;
    }
    else if(strcmp(str1,"16:30\n")){
        return 16.5;
    }
    else if(strcmp(str1, "17:00")){
        return 17.0;
    }
    else if(strcmp(str1, "17:30")){
        return 17.5;
    }
    else if(strcmp(str1, "18:00")){
        return 18.0;
    }
    else if(strcmp(str1, "18:30")){
        return 18.5;
    }
    else if(strcmp(str1, "19:00")){
        return 19.0;
    }
    else if(strcmp(str1, "19:30")){
        return 19.5;
    }
    else if(strcmp(str1, "20:00")){
        return 20.0;
    }
    else if(strcmp(str1, "20:30")){
        return 20.5;
    }
    else if(strcmp(str1, "21:00")){
        return 21.0;
    }
    else if(strcmp(str1, "21:30")){
        return 21.5;
    }
    else if(strcmp(str1, "22:00")){
        return 22.0;
    }
    else if(strcmp(str1, "22:30")){
        return 22.5;
    }
    else if(strcmp(str1, "23:00")){
        return 23.0;
    }
    else if(strcmp(str1, "23:30")){
        return 23.5;
    }
    else{
        return 24.0;
    }
}

/* input items into the list */
void enterNew(struct db_type * pArr[SIZE]){

    //get input for name 
    printf("name:");
    char name[50];   //input
    // fgets(name,50,stdin);
    // name[strlen(name-1)] = '\0';
    scanf("%[^\n]", &name);
    // name[strlen(name-1)]='\0'; //fixed


    // ignore
    // int test_ = start_time_helper("EECS2031");
    // printf("%d", test_);

    //get input for age
    printf("age:");
    int age;   //input
    scanf("%d%*c",&age); //no need to fix (int)

    //get input for course1
    printf("course-1:");
    char course1[10];   //input
    scanf("%s", &course1);
    // course1[strlen(course1-1)]='\0'; //fixed

    char course1_fixed[50]; //fixed input

    if (strlen(course1) == 4){
        strcpy(course1_fixed, "EECS");
        strcat(course1_fixed,course1);
    }
    else{
        strcat(course1_fixed,course1);
    }

    //course1 times
    int course1_start = start_time_helper(course1_fixed);
    int course1_end = end_time_helper(course1_fixed);

    while(course1_start == 0 && course1_end == 0){
        printf("course does not exist, enter again: ");
        char course1[10];   //input
        scanf("%s", &course1);
        // course1[strlen(course1-1)]='\0'; //fixed

        if (strlen(course1) == 4){
        strcpy(course1_fixed, "EECS");
        strcat(course1_fixed,course1);
        }
        else{
        strcat(course1_fixed,course1);
        }

        course1_start = start_time_helper(course1_fixed);
        course1_end = end_time_helper(course1_fixed);
    }

    //get input for course2
    printf("course-2:");
    char course2[50];   //input
    scanf("%s", &course2);
    // course2[strlen(course2-1)]='\0'; //fixed

    char course2_fixed[50]; //fixed input

    if (strlen(course2) == 4){
        strcpy(course2_fixed, "EECS");
        strcat(course2_fixed,course2);
    }
    else{
        strcat(course2_fixed,course2);
    }

    //course2 times
    int course2_start = start_time_helper(course2_fixed);
    int course2_end = end_time_helper(course2_fixed);

    while(course2_start == course1_end && course2_end == course1_end){
        printf("course does not exist, enter again: ");
        char course2[10];   //input
        scanf("%s", &course2);
        // course2[strlen(course2-1)]='\0'; //fixed

        if (strlen(course2) == 4){
        strcpy(course2_fixed, "EECS");
        strcat(course2_fixed,course2);
        }
        else{
        strcat(course2_fixed,course2);
        }

        course2_start = start_time_helper(course2_fixed);
        course2_end = end_time_helper(course2_fixed);
    }

    char course1_date[50];
    char course2_date[50];

    int index1 = 0;
    int index2 = 0;

    while(strcmp("EECS0000", courseArr[index1].code) != 0){
            if(strstr(course1_fixed, courseArr[index1].code) != NULL)
            {
                strcpy(course1_date,courseArr[index1].date);
            }
            index1++;
    }

    while(strcmp("EECS0000", courseArr[index2].code) != 0){
            if(strstr(course2_fixed, courseArr[index2].code) != NULL)
            {
                strcpy(course2_date, courseArr[index2].date);
            }
            index2++;
    }

    bool dates_overlap = (strstr(course1_date, course2_date) || strstr(course2_date, course1_date));
    bool overlap = course1_start < course2_end && course1_end > course2_start && dates_overlap;

    //** ignore: used for testing **
    // printf("COURSE1 IS %s\n", course1_fixed);
    // printf("%d\n", course1_start);
    // printf("%d\n", course1_end);
    // printf("BOOL IS %d", course_check(course1_fixed));
    // int variable1 = course_check(course1_fixed);
    // printf("COURSE2 IS %s\n", course2_fixed);
    // printf("%d\n", course2_start);
    // printf("%d\n", course2_end);
    // int variable2 = course_check(course2_fixed);
    // printf("BOOL IS %d", variable2);

    struct db_type stud[SIZE];
    
    if (overlap){
        // strcpy(stud[counter].status, "ATTENTION! time conflict\n");
        strcpy(stud[counter].status, "ATTENTION! time conflict");
        printf("ATTENTION! time conflict");
    }
    else{
        // strcpy(stud[counter].status, "SUCCESSFUL! no time conflict\n");
        strcpy(stud[counter].status, "SUCCESSFUL! no time conflict");
        printf("SUCCESSFUL! no time conflict");
    }

    //add name to student struct
    // strcpy(stud[counter].name, name);
    strcpy(stud[counter].name, name);

    //add age to student struct
    stud[counter].age = age;

    strcpy(stud[counter].course1, course1_fixed);
    strcpy(stud[counter].course2, course2_fixed);

    //pArr cell points to address of stud
    pArr[counter] = &stud[counter];
    counter++;
    // printf("Name is: s\n", *stud[0]);
}

int cast_to_int(char time_[50]){
    char str[50];
    char *p = &str[0];

    *p = time_[0];
    *(p+1) = time_[1];
    *(p+2) = time_[3];
    *(p+3) = time_[4];
    *(p+4) = '\0';

    int x = atoi(str);
    return x;
}

// helper function returns start time of course
int start_time_helper(char course_[9]){
    int i = 0;
    char final[50];
    
    while(strcmp("EECS0000", courseArr[i].code) != 0){
        if(strstr(course_, courseArr[i].code) != NULL){
            strcpy(final,courseArr[i].time_start);
        }
        i++;
    }
    int result = cast_to_int(final);
    return result;
}

// helper function returns end time of course
int end_time_helper(char course_[9]){
    int i = 0;
    char final[50];
    
    while(strcmp("EECS0000", courseArr[i].code) != 0){
        if(strstr(course_, courseArr[i].code) != NULL){
            strcpy(final,courseArr[i].time_end);
        }
        i++;
    }
    int result = cast_to_int(final);
    return result;
}

/* display records */
void displayDB(struct db_type * pArr[]){

    printf("===============================\n");


    for (int i = 0; i < SIZE; i++){
        if (pArr[i] != NULL){
            int j = find_course_index(pArr[i]->course1);
            int k = find_course_index(pArr[i]->course2);

            printf("name: %s\n", pArr[i]->name);
            printf("age: %d\n", pArr[i]->age);
            printf("course1: %s\t%-40s%-5s %s-%s   %s\n", courseArr[j].code,courseArr[j].title,courseArr[j].date,courseArr[j].time_start,courseArr[j].time_end,courseArr[j].location);
            printf("course2: %s\t%-40s%-5s %s-%s   %s\n", courseArr[k].code,courseArr[k].title,courseArr[k].date,courseArr[k].time_start,courseArr[k].time_end,courseArr[k].location);
            printf("remarks: %s\n", pArr[i]->status);
        }
    }
  printf("========== %d records ==========", counter);
  printf("\n");
}

int find_course_index(char course_[SIZE]){
    int result;
    int i = 0;
    while(strcmp("EECS0000", courseArr[i].code) != 0){
        if(strstr(course_, courseArr[i].code) != NULL){
            result = i;
        }
        i++;
    }
    return result;
}


/* remove an existing item */
void removeRecord (struct db_type * pArr[])	
{
  printf("enter full name to remove:");
  char name_[fieldLength];   //input
  scanf("%[^\n]", &name_);
//   name_[strlen(name_-1)]='\0'; //fixed
  
  bool var1 = false;

  // ignore, used for testing
//   printf("NAME IS %s\n", name_);
//   printf("NAME IS %s\n", pArr[0]->name);
//   int result = strcmp(name_,pArr[0]->name);
//   printf("NUMBER IS %d\n", result);
  
  for (int i = 0; i < counter; i++){
      if (pArr[i] != NULL){
          if (strcmp(name_, pArr[i]->name)==0){
            //   printf("We are here 2\n");
              pArr[i] = NULL;
              var1 = true;
              counter = counter - 1;
              break;
            }
        }
    }

  if (var1){
      printf("record [%s] removed successfully", name_);
    //   counter--;
    }
  else{
      printf("record not found");
    }
}

/* swap records */
void swap(struct db_type * pArr[]){
   for (int i = 0; i < SIZE; i= i + 2){
       struct db_type * tempArr[SIZE];
       tempArr[i] = pArr[i];
       pArr[i] = pArr[i+1];
       pArr[i+1] = tempArr[i];
   }
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
    
/******** DISK IO ***********************/

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

/*bonus****************************/

/* sort the records by ages */
void sort(struct db_type * pArr[])
{
    //Bubble Sort Algorithm
    for (int k = 0; k < counter; k++){
        helper(pArr);
    }
} 

// helper function for sort(struct db_type * pArr[])
void helper(struct db_type * pArr[]){
    //one iteration of bubble sort algorithm
    bool swapped;
    struct db_type * tempArr[SIZE];
    int i;
    int j;

    for (j = 0; j < counter - 1; j++){
        swapped = false;
        for (i = 0; i < counter - j - 1; i++)
        {
            int age_left = pArr[i]->age;
            int age_right = pArr[i+1]->age;

            if (age_left > age_right)
            {
                tempArr[i] = pArr[i];
                pArr[i] = pArr[i+1];
                pArr[i+1] = tempArr[i];
            }
        }
        if (!swapped){
            break;
        }
    }
}

//swaps index i and j
void swapping(struct db_type * pArr[], int i, int j){
    struct db_type * tempArr[SIZE];
    tempArr[i] = pArr[i];
    pArr[i] = pArr[j];
    pArr[j] = pArr[i];
}
