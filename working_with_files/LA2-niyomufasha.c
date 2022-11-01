#include <stdio.h>
#include <string.h> // string library

// define the strucutre of a player
typedef struct 
{
char firstname[50];
char lastname[50];
char position[50];
int age;
int miles;
double height;
} player;
// define the fucntions in the code
void sortRecords(player * players, int * records, int * playerssort, int count);
void displayData(player * players, int * records, int * playerssort, int count);// function to display data
void addRecord(player* players, int * playerssort, int *records, int count); // function to add records
void DeleteRecord(player *players, int * records, player * playerssort); // fucntion to delete record
// void printScreen(player * players, int * records, int count, char filename[50]); // function to print things to a file
void searchRecords(player * players, int * records, int * playerssort);// function for searching a record
void Save(player * players, int * playerssort, int  * records, int count); // fucntion to save
void Menu(player * players, int * playerssort, int * records,  int count); // the menu prompting the user to do something
void quit(); // function to quit

int main(){
  int playerssort[100]; // the sort array containing the indices in a sorted order
  FILE *file;  
  int i = 0; // loop iterator
  int count = 0; // counter for matched like search, and more
  player players[100]; // the array containing the data
  char junk;
  int records = 0; // intializing the variable to keep track of the reacords
  char filechoice; // the integer to keep store the choice of opening file
  char firstfilename[50]; // the holder of the file name entered by the user
  printf("Do you wanna opena new file you would like to work with?  if yes, enter [n], else, enter [o] or \'enter\' key Default[data.txt]:  "); // prompting wether using the available file, or using their own
  scanf("%c", &filechoice);

  if(filechoice == 'n'){ // if the user choose to enter their own file
    printf("enter the name of the file:  ");
    scanf("%s", firstfilename); // storing the name in the filename holder
    scanf("%c", &junk);
    file = fopen(firstfilename, "r");
    if(file == NULL){ // if the file does not exist
       main(); // restarting the main function
    };
  } else{
    file = fopen("data.txt", "r"); // if the user wants to use the default file
    if(file == NULL){
      printf("\n\nFile not found  \n\n"); // if the file is not found
      main(); // restart the main function
      return 1;
    };
    printf("\n\nThis is a dataset about baseball players. It includes their firstnames, lastnames, positions, age, Miles away from dartmouth college, and their height in inches\n\n"); // description of the data
  };
    
  do 
  { // scanning and making sure the program stops scanning when it reaches the comma
    fscanf(file,
                  "%[^,],%[^,], %[^,], %d, %d, %lf\n",// read strings and stop when you reach the comma
                   players[records].firstname, 
                   players[records].lastname, 
                   players[records].position, 
                   &players[records].age,
                   &players[records].miles,
                   &players[records].height);
    records++;
  } while (!feof(file)); // do it as long as the file is not ended, source: youtube video
  fclose(file);
    for(i = 0; i<records; i++){
    playerssort[i] = i;
  }; // initialize the values of playerssort to the same size of the, and the same indices
  Menu(players, playerssort, &records, count);
// }
  return 0;
  };
//display function
void displayData(player * players, int * records, int * playerssort, int count){
  int i = 0; // loop counter
  printf("records =  %d \n", *records); // print the number of records
  printf("\n");
  //accessing the records in an array of structures and printing
  for(i = 0; i<*records; i++){ // using playerssort
        printf("%13s %13s %13s %5d %5d \t%5.2f\n", 
           players[playerssort[i]].firstname, 
           players[playerssort[i]].lastname,
           players[playerssort[i]].position,
           players[playerssort[i]].age,
           players[playerssort[i]].miles,
           players[playerssort[i]].height);
  printf("\n");
  }

  Menu(players, playerssort, records, count); // calling menu after display
};


//sort the records based on the user criteria function
void sortRecords(player * players, int * records, int * playerssort, int count){
  //variable declaration
  int choice;
  int c;
  int i,j;
  int swap;
  char choicesort;
  char junk;
  char namechoice[50];
  //giving user directions
  printf("If you want to sort according to age, enter a, or else if you want to sort according to alphabetical order of first names, enter  b. Default[dispaly]:   ");
  //geting the user choice after they read instruction
  scanf("%c", &choicesort);
  //using each user input with specificity
  if(choicesort == 'a'){
    scanf("%c", &junk);
  //bubble sort for sorting
  for(int i =0; i<*records; i++){
     for(int j = 0; j<*records-1; j++){
      //comparing ages
       if(players[playerssort[j]].age > players[playerssort[j+1]].age){
          // changing the indices of everything below the found index, by moving them up
          c = playerssort[j+1];
          playerssort[j+1] = playerssort[j];
          playerssort[j] = c; 
       }
     }

   }
    
//printing records in the sorted order
    
    for(i = 0; i<*records; i++){
        printf("%13s %13s %13s %5d %5d \t%5.2f\n", 
           players[playerssort[i]].firstname, 
           players[playerssort[i]].lastname,
           players[playerssort[i]].position,
           players[playerssort[i]].age,
           players[playerssort[i]].miles,
           players[playerssort[i]].height);
  printf("\n");
  }
    //checking another possible user input 
    } else if(choicesort == 'b'){
    scanf("%c", &junk);
    printf("\n\nIf you want to sort by firstname, enter firstname, of you want to sort  by lastname, enter lastname:   ");
    scanf("%s", namechoice);
    scanf("%c", &junk);
    if(strcmp(namechoice, "firstname") == 0){
      for( i =0; i<*records; i++){
      for(j = 0; j<*records-1; j++){
       //bubble sorting 
       if(strcmp(players[playerssort[j]].firstname, players[playerssort[j+1]].firstname) > 0){
          c = playerssort[j+1];
          playerssort[j+1] = playerssort[j];
          playerssort[j] = c; 
       }
     }
    
   }
    //accessing records and printing them 
    for(i = 0; i<*records; i++){
        printf("%13s %13s %13s %5d %5d \t%5.2f\n", 
           players[playerssort[i]].firstname, 
           players[playerssort[i]].lastname,
           players[playerssort[i]].position,
           players[playerssort[i]].age,
           players[playerssort[i]].miles,
           players[playerssort[i]].height);
    printf("\n");
   }
 } 
    //comparing instruction to userinput
    else if(strcmp(namechoice, "lastname") == 0)
    { // use bubblesort 
for( i =0; i<*records; i++){
      for(j = 0; j<*records-1; j++){
       //bubble sorting 
       if(strcmp(players[playerssort[j]].lastname, players[playerssort[j+1]].lastname) > 0){
          c = playerssort[j+1];
          playerssort[j+1] = playerssort[j];
          playerssort[j] = c; 
       }
     }
    
   }
    //accessing records and printing them 
    for(i = 0; i<*records; i++){
        printf("%13s %13s %13s %5d %5d \t%5.2f\n", 
           players[playerssort[i]].firstname, 
           players[playerssort[i]].lastname,
           players[playerssort[i]].position,
           players[playerssort[i]].age,
           players[playerssort[i]].miles,
           players[playerssort[i]].height);
    printf("\n");
   }
  }
  else if(choicesort == '\n'){ // default
   displayData(players, records, playerssort, count);
  } else {
    printf("\n\nWrong choice, Please try again.\n\n"); 
    Menu(players, playerssort, records, count);// handling if the user does not use choose to sort by age or name
  };
} else{
   Menu(players, playerssort, records, count);
    // handling another wrong choice for what to do.. 
};
  Menu(players, playerssort, records, count);
}

//search function to look for a record with specificity 
void searchRecords(player * players, int * records, int * playerssort){
  //varible declaration
  char entry[50];
  char entry2[50];
  int count = 0;
  char junk;
  char firstnameholder[50];
  char lastnameholder[50];
  int i;
  printf("What do you want to search for? to Search for a name, enter name, to search for age, enter age:  ");
  scanf("%s", entry);
  //comparing user input to instruction
  if(strcmp(entry, "name") == 0){
    printf("\nDo you want to search by firstname, or lastname? Enter lastname for lastname search, or firstname for firstname search:  ");
    //scanning another possible entry
    scanf("%s", entry2);
    if(strcmp(entry2, "lastname") == 0){
      printf("\nEnter the lastname of the user:  ");
      scanf("%s", lastnameholder);
      scanf("%c", &junk);// scanning the enter kwy after
      for(i = 0; i<*records; i++){
        if(strcmp(lastnameholder, players[i].lastname) == 0){//comparing two names
          count ++;
          printf("\n%13s %13s %13s %5d %5d\t%5.2f\n", 
           players[i].firstname, 
           players[i].lastname,
           players[i].position,
           players[i].age,
           players[i].miles,
           players[i].height);
           printf("\n");
          }
        }
      }
  else if(strcmp(entry2, "firstname") == 0)
  { // when the choice is firstname
    printf("\nEnter the firstname:  ");
    scanf("%s", firstnameholder);
    scanf("%c", &junk);
    for(i =0; i<*records; i++){ // go through the records
      if(strcmp(players[i].firstname, firstnameholder) == 0){//comapring two names 
        count ++; // keep track of how many found
    printf("%13s %13s %13s %5d %5d\t%5.2f\n", 
           players[i].firstname, 
           players[i].lastname,
           players[i].position,
           players[i].age,
           players[i].miles,
           players[i].height);
  printf("\n");
      }
    }
    }  else { // if the choice is wrong
    printf("\n You entered a wrong choice /n");
    searchRecords(players, records, playerssort);
    }
  }

//now searching for age
else if(strcmp(entry, "age") == 0) // if the user choosed age
{
    int ageholder; // for holding the age choice of the user
    int i = 0;
    printf("Enter the age you want ");
    scanf("%d", &ageholder);
    scanf("%c", &junk);
    printf("\n Results of your search:  \n\n");
    for(i = 0; i < *records; i++){
    if(players[i].age == ageholder){//camparing userinput age and data age
       count ++; // keep track of the records found
    printf("%13s %13s %13s %5d %5d\t%5.2f\n", 
           players[i].firstname, 
           players[i].lastname,
           players[i].position,
           players[i].age,
           players[i].miles,
           players[i].height);
  printf("\n");
    }
      }
  } else{
    printf("\nPlease enter enter either age, or name 😔 \n\n");
    searchRecords(players, records, playerssort);//calling search function
  }
   if(count == 0){ // if there is no record found
    printf("No such value");
    Menu(players, playerssort, records,  count);//calling menu function
    }
  scanf("%c", &junk);
  Menu(players, playerssort, records, count);
};

void addRecord(player * players, int *playerssort , int *records, int count){
  char addedfirstName[50]; // declaring variables to hold the added values
  char addedlastName[50];
  char addedPosition[50];
  int addedAge;
  int addedMiles;
  double addedHeight;
  char junk;
  int i;
  int check; // prompting the user to add those records, and putting them into the database
  printf("Enter the firstname:  ");
  scanf("%[^\n]*c", players[*records].firstname);
  scanf("%c", &junk);
  printf("Enter the lastname:  ");
  scanf("%[^\n]*c", addedlastName);
  scanf("%c", &junk);
  strcpy(players[*records].lastname, addedlastName);
  printf("Enter the position:  ");
  scanf("%[^\n]*c", addedPosition);
  scanf("%c", &junk);
  strcpy(players[*records].position, addedPosition);
  printf("Enter the age  ");
  scanf("%d", &addedAge);
  players[*records].age = addedAge;
  printf("Enter the miles away from Dartmouth:  ");
  scanf("%d", &addedMiles);
  players[*records].miles = addedMiles;
  printf("Enter the height of the player ");
  scanf("%lf", &addedHeight);
  players[*records].height = addedHeight;
  playerssort[*records] = *records;

  scanf("%c", &junk);
  *records = *records + 1; // increment the records by 1
  Menu(players, playerssort, records, count);
};

//function to delete criteria with specificity
void DeleteRecord(player *players, int *records, player *playerssort) {
  // variable declaration
  char choice;
  char choice1[50];
  char firstnamechoice[50];
  char lastnamechoice[50];
  int agechoice;
  char junk;
  int i, j;
  int count = 0;
  char multiplechoice; // for choosing whether deleting multiple things
  // user choice being scanned after instruction display
  printf("If you want to delete by name, enter 't', if you want to delete by age, enter 'g' Default[Display]: ");
  scanf("%c", &choice);
  scanf("%c", &junk);
  // checking each user possible inputs and proceed accordingly
  if (choice == 't') {
    printf("Do you want to delete a record using its fistname, or a lastname?");
    scanf("%s", choice1);
    // comapring user input to instruction
    if (strcmp(choice1, "firstname") == 0) {
      printf("Enter the firstname here:  ");
      scanf("%s", firstnamechoice);
      scanf("%c", &junk);
      for (i = 0; i < *records; i++) {
        // comparing user name input to record name
        if (strcmp(players[i].firstname, firstnamechoice) == 0) {
          printf("%d", i);
          printf("%13s %13s %13s %5d %5d \t%5.2f\n", players[i].firstname,
                 players[i].lastname, players[i].position, players[i].age,
                 players[i].miles, players[i].height);
          printf("\n");

          count++; // counting how many records match user inputs
        }
      }
      if (count == 1) {
        // deleting the found data
        for (i = 0; i < *records; i++) {
          if (strcmp(players[i].firstname, firstnamechoice) == 0) {
            for (j = i; j < *records; j++) {
              players[j] = players[j + 1];
            }
          }
        }
      } else if (count > 1) {
        // giving the user an option of deleting all found data or not
        printf("The above data matched your search, do you want to delete all of them? if yes, enter y, if no, enter n default[Deleting all]:   ");
        scanf("%c", &multiplechoice);
        if (multiplechoice == 'y') {
          scanf("%c", &junk);
          for (i = 0; i < *records; i++) {
            // comparing user name input to record name
            if (strcmp(players[i].firstname, firstnamechoice) == 0) {
              for (j = i; j < *records; j++) {
                players[j] = players[j + 1];
              }
            }
          }
        } else if (multiplechoice == 'n') {
          scanf("%c", &junk);
          DeleteRecord(players, records, playerssort); // calling deleterecord function
        } else if(multiplechoice  == '\n'){
                    for (i = 0; i < *records; i++) {
            // comparing user name input to record name
            if (strcmp(players[i].firstname, firstnamechoice) == 0) {
              for (j = i; j < *records; j++) {
                players[j] = players[j + 1];
              }
            }
          }
        }
      } else {
        printf("There is no such value");
      }
    } else if (strcmp(choice1, "lastname") == 0) {
      printf("Enter the lastname here:  ");
      scanf("%s", lastnamechoice);
      for (i = 0; i < *records; i++) {
        // comparing user name input to record name
        if (strcmp(players[i].lastname, lastnamechoice) == 0) {
          count++;
          for (j = i; j < *records; j++) {
            players[j] = players[j + 1];
          }
        }
      }
    }
  } else if (choice == 'g') {
    printf("Enter the age here:  ");
    scanf("%d", &agechoice);
    scanf("%c", &junk);

    for (i = 0; i < *records; i++) {
        // comparing user name input to record name
        if (players[i].age == agechoice) {
          printf("%d", i);
          printf("%13s %13s %13s %5d %5d \t%5.2f\n", players[i].firstname,
                 players[i].lastname, players[i].position, players[i].age,
                 players[i].miles, players[i].height);
          printf("\n");

          count++; // counting how many records match user inputs
        }
      }

    // deleting the found record by moving to the next line
    if (count == 1) {
        // bubble sort
        for (i = 0; i < *records; i++) {
          if (strcmp(players[i].firstname, firstnamechoice) == 0) {
            for (j = i; j < *records; j++) {
              players[j] = players[j + 1];
            }
          }
        }
      } else if (count > 1) {
        // giving the user an option of deleting all found data or not
        printf("The above data matched your search, do you want to delete all of them? if yes, enter y, if no, enter n [default: Delete all]:   ");
        scanf("%c", &multiplechoice);
        if (multiplechoice == 'y') {
          scanf("%c", &junk);
          for (i = 0; i < *records; i++) {
            // comparing user name input to record name
            if (strcmp(players[i].firstname, firstnamechoice) == 0) {
              for (j = i; j < *records; j++) {
                players[j] = players[j + 1];
              }
            }
          }
        } else if (multiplechoice == 'n') {
          scanf("%c", &junk);
          DeleteRecord(players, records,
                       playerssort); // calling deleterecord function
        } else if(multiplechoice  == '\n'){
                    for (i = 0; i < *records; i++) {
            // comparing user name input to record name and deletin them
            if (strcmp(players[i].firstname, firstnamechoice) == 0) {
              for (j = i; j < *records; j++) {
                players[j] = players[j + 1];
              }
            }
          }
        }
      } else {
        printf("There is no such value");
      }
  } else if (choice == '\n') {// default
    displayData(players, records, playerssort, count);
  }
  *records = *records - count;
  Menu(players, playerssort, records, count);
};


//menu function declaration
void Menu(player * players, int * playerssort, int * records,  int count){ 
  // variables used
  char actionChoice;
  int quitchoice;
  int savechoosing;
  char junk;
//givind the user instruction of what to follow
  printf("\n\n-if you want to search, enter search, \n-if you want to sort, enter [o], \n-if you want to Add [a] record, enter add, \n-if you want to delete a record, enter [d], \n-if you want to display the current data, enter [p], \n-if you want to want to save the current enter [s], \n-if you want to quit enter [q] Default[Display]:  ");

  printf("\n\n\nEnter your choice here:   ");
  //getting and scanning user choice
  scanf("%c", &actionChoice);
  //get user options
  if(actionChoice == 'o'){
  scanf("%c", &junk);
    sortRecords(players, records, playerssort, count);
  } else if(actionChoice== 'e'){
    scanf("%c", &junk);
    searchRecords(players, records, playerssort);//calling searchrecord function
  } else if(actionChoice == 'a'){
    scanf("%c", &junk);
    addRecord(players, playerssort, records, count);//calling addrecord function
  } else if(actionChoice == 'd'){
    scanf("%c", &junk);
    DeleteRecord(players, records, playerssort);//calling deleterecord function
  } else if(actionChoice == 's'){
    scanf("%c", &junk);
    Save(players, playerssort, records, count);////calling save function
  } else if(actionChoice == 'p'){
    scanf("%c", &junk);
    displayData(players, records, playerssort, count);////calling display function
  } else if(actionChoice == 'q'){
    scanf("%c", &junk);
    quit();//calling quit function
  } else if(actionChoice == '\n'){
    displayData(players, records, playerssort, count);//calling display data function
  } else{
    printf("Wrong choice");
    Menu(players, playerssort, records,count);
  }

};

//save function definition 

void Save(player * players, int * playerssort, int  * records, int count){
  FILE* filesave;
  char junk;
  int overchoice;
  char filechoice;
  int writechoice;
  char savename [50];
  int i;
  printf("by default, the data will be saved in the \'savefile.txt\' file. If you would like to add another file, enter y, else, enter n:  ");
  scanf("%c", &filechoice);
  if(filechoice == 'y'){
  scanf("%c", &junk);
    //getting and scanning file name from the user
  printf("Enter the name of the file, ending with .txt:  ");
  scanf("%s", savename);
  filesave = fopen(savename, "r");
  if(filesave  == NULL){
    //writing to the opened file
     filesave = fopen(savename, "w");
    for(i = 0; i<*records; i++){
        fprintf(filesave, "%s,%s,%s,%d,%d,%.2f\n", 
           players[playerssort[i]].firstname, 
           players[playerssort[i]].lastname,
           players[playerssort[i]].position,
           players[playerssort[i]].age,
           players[playerssort[i]].miles,
           players[playerssort[i]].height);
  }
    fclose(filesave);//closing the file
  } else if (filesave != NULL){//checking is file doesn't exist
    fclose(filesave);
    filesave = fopen(savename, "w");//writing the file
    printf("This file already exist, do you wanna overwite it? enter 1 for yes, or 0 for no:  ");
    scanf("%d", &overchoice);
    if(overchoice  == 1){
      scanf("%c", &junk);
      for(i = 0; i<*records; i++){
        //writing records to the new file
        fprintf(filesave, "%s,%s,%s,%d,%d,%.2f\n", // 
           players[playerssort[i]].firstname, 
           players[playerssort[i]].lastname,
           players[playerssort[i]].position,
           players[playerssort[i]].age,
           players[playerssort[i]].miles,
           players[playerssort[i]].height);
  }
      fclose(filesave);
  } else {
      scanf('%c', &junk);
      printf("Try saving again!  ");
  }
}
    } 
  else if(filechoice = '\n'){ //for the default value
    filesave = fopen("savefile.txt", "r");
   if(filesave  == NULL){
     //opeing the default file
   filesave = fopen("savefile.txt", "w");
    for(i = 0; i<*records-count; i++){
      //writing to default file
      fprintf(filesave, "%s,%s,%s,%d,%d,%.2f\n", 
         players[playerssort[i]].firstname, 
         players[playerssort[i]].lastname,
         players[playerssort[i]].position,
         players[playerssort[i]].age,
         players[playerssort[i]].miles,
         players[playerssort[i]].height);
}
       fclose(filesave);//closing file
     
  } else if (filesave != NULL){ 
     filesave = fopen("savefile.txt", "w");
    printf("This file already exist, do you wanna overwite it? enter 1 for yes, or 0 for no"); 
// if file exists
    scanf("%d", &overchoice);
    if(overchoice  == 1){
      scanf("%c", &junk);
      for(i = 0; i<*records; i++){
        fprintf(filesave, "%s,%s,%s,%d,%d,%.2f\n", // saving into the file in the current order
         players[playerssort[i]].firstname, 
         players[playerssort[i]].lastname,
         players[playerssort[i]].position,
         players[playerssort[i]].age,
         players[playerssort[i]].miles,
         players[playerssort[i]].height);
  }  
      fclose(filesave);//closing file
      Menu(players, playerssort, records, count);//calling main menu function
  } else {
      printf("Try saving again!  ");
      Save(players, playerssort, records, count);// call function again.. 
  }
}
    } else{
     Menu (players, playerssort, records, count);//calling main menu function
    }
    Menu (players, playerssort, records, count);//calling main menu function
  }

//quit function definition
void quit(){ 
  printf("You quitted!");
};