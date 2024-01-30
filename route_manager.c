/** @file route_manager.c
 *  @brief A small program to analyze airline routes data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author Taha F.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


// TODO: Make sure to adjust this based on the input files given
#define MAX_LINE_LEN 1024


/**
 * Function: writeCSVq3
 * --------------
 * @brief  prints out the required output on the CSV file
 *
 * @param list linked list that will go on the csv file
 * @param n How many rows the csv file should have 
 *
 */
void writeCSVq3 (node_t *list,char *n)
{
    FILE *fp;

    fp = fopen("output.csv", "w");

    fprintf(fp, "subject,statistic\n");

    int count = 0;
    while (count < atoi(n)) {
        fprintf(fp, "\"%s\",%d\n", list->subject, list->statistic);
        list = list->next;
        count++;
    }

    fclose(fp);
}





/**
 * Function: writeCSV
 * --------------
 * @brief  prints out the required output on the CSV file
 *
 * @param list linked list that will go on the csv file
 * @param n How many rows the csv file should have 
 *
 */
void writeCSV (node_t *list,char *n)
{
    FILE *fp;

    fp = fopen("output.csv", "w");

    fprintf(fp, "subject,statistic\n");

    int count = 0;
    while (count < atoi(n)) {
        fprintf(fp, "%s,%d\n", list->subject, list->statistic);
        list = list->next;
        count++;
    }

    fclose(fp);
}


// **
//  * @brief Serves as an incremental counter for navigating the list.
//  *
//  * @param p The pointer of the node to print.
//  * @param arg The pointer of the index.
//  *
//  **/
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->subject);
}


/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 *
 */
void analysis(node_t *l)
{
    int len = 0;

    apply(l, inccounter, &len);
    printf("Number of words: %d\n", len);

    apply(l, print_node, "%s\n");
}

/**
 * Function: question1
 * --------------
 * @brief  Finds the top N airlines that offer the greatest number of routes with destination country as Canada
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 *
 */
void question1(int argc, char *argv[]){ 
    char line[MAX_LINE_LEN];

    //Extracting the filename form argv
    char *data = strtok(argv[1], "=");
    data = strtok(NULL, "=");

    char *n = strtok(argv[3], "=");
    n = strtok(NULL, "=");


    //opening the file and skipping the first line
    FILE *fp;
    fp = fopen(data, "r");
    fgets(line, MAX_LINE_LEN, fp);
    char *fileByLine = fgets(line, MAX_LINE_LEN, fp);

    //declaring all the variables
    int count = 1;
    char *airlineName;
    char *airlineCode;
    char *destCountry;
    char *subject;
    node_t *list = NULL;
    int firstTime = 1;
    node_t *sortedList = NULL;

    while(fileByLine){

        
        if(count == 13){ //Checking if the current route is over

            count = 0;

        } if(count == 1) { //Getting the Airline Name

            char *token = strtok(line, ":");
            token = strtok(NULL, ":");
            airlineName = strdup(strtok(token, ":"));

            while (*airlineName == ' ') { //removing spaces at the beginning of the word
                airlineName++;
            }

            airlineName[strcspn(airlineName, "\n")] = '\0'; //removing trailing \n


        } if(count == 2) { //Getting the Airline Icao Unique Code

            char *token2 = strtok(line, ":");
            token2 = strtok(NULL, ":");
            airlineCode = strdup(strtok(token2, ":"));

            while (*airlineCode == ' ') { //removing spaces at the beginning of the word
                airlineCode++;
            }

            airlineCode[strcspn(airlineCode, "\n")] = '\0'; //removing trailing \n
        } 
       
        if(count == 11) { //Getting the Destination Country
            char *token3 = strtok(line, ":");
            token3 = strtok(NULL, ":");
            destCountry = strdup(strtok(token3, ":"));

            while (*destCountry == ' ') { //removing spaces at the beginning of the word
                destCountry++;
            }
            destCountry[strcspn(destCountry, "\n")] = '\0';//removing trailing \n


            //Checking whether the Destintation Country is Canada
            if (strcmp(destCountry, "Canada") == 0){

                //Formatting the subject according to the question
                subject = strcat(airlineName, " (");
                subject = strcat(subject, airlineCode);
                subject = strcat(subject, ")");

                //Checking whether or not the Node is in the list
                node_t *newNode = find_in_list(list, subject);
                if (newNode)
                {
                    newNode->statistic ++;
                }
                else
                {
                    list = add_end(list, new_node(subject, firstTime));
                }

            }
        }

        count++;

        fileByLine = fgets(line, MAX_LINE_LEN, fp); //Going to the next line in the YAML file
    }
    node_t *curr = NULL;

    while (list != NULL) {
        curr = list;
        list = list->next;
        curr->next = NULL;

        sortedList = add_inorder(sortedList, curr);
    }

    writeCSV(sortedList,n);
    

    fclose(fp);
}


/**
 * Function: question2
 * --------------
 * @brief  Finds the the top N countries with least appearances as destination country on the routes data
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 *
 */
void question2(int argc, char *argv[]){
    char line[MAX_LINE_LEN];

    //Extracting the filename form argv
    char *data = strtok(argv[1], "=");
    data = strtok(NULL, "=");

    char *n = strtok(argv[3], "=");
    n = strtok(NULL, "=");


    //opening the file and skipping the first line
    FILE *fp;
    fp = fopen(data, "r");
    fgets(line, MAX_LINE_LEN, fp);
    char *fileByLine = fgets(line, MAX_LINE_LEN, fp);

    //declaring all the variables
    int count = 1;
    char *destCountry;
    char *subject;
    node_t *list = NULL;
    int firstTime = 1;
    node_t *sortedList = NULL;

    while(fileByLine){

        
        if(count == 13){  //Checking if the current route is over

            count = 0;

        }
        
        
        if(count == 11) { //Getting the Destination Country
            char *token = strtok(line, ":");
            token = strtok(NULL, ":");
            destCountry = strdup(strtok(token, ":"));

            while (*destCountry == ' ') { //removing spaces at the beginning of the word
                destCountry++;
            }
            destCountry[strcspn(destCountry, "\n")] = '\0';//removing trailing \n

            if(strcmp(destCountry,"\' Sheffield\'")== 0){
                destCountry = "Sheffield";
            }

            if (strcmp(destCountry, "\' Santiago Island\'") == 0){
                destCountry = "Santiago Island";
            }

            //Formatting the subject according to the question
            subject = destCountry;

            //Checking whether or not the Node is in the list
            node_t *newNode = find_in_list(list, subject);
            if (newNode) {
                newNode->statistic ++;
            }
            else {
                list = add_end(list, new_node(subject, firstTime));
            }
        
        }
        count++;

        fileByLine = fgets(line, MAX_LINE_LEN, fp); //Going to the next line in the YAML file
    
    }

    // removing the contents from list and organizing them into a sortedList
    node_t *curr = NULL;

        while (list != NULL) {
        curr = list;
        list = list->next;
        curr->next = NULL;

        sortedList = add_inorder_descending(sortedList, curr);
    }

    writeCSV(sortedList,n);
    
    
    fclose(fp);

}

/**
 * Function: question3
 * --------------
 * @brief  Finds the the top N destination airports
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 *
 */
void question3(int argc, char *argv[]){
    char line[MAX_LINE_LEN];

    //Extracting the filename form argv
    char *data = strtok(argv[1], "=");
    data = strtok(NULL, "=");

    char *n = strtok(argv[3], "=");
    n = strtok(NULL, "=");


    //opening the file and skipping the first line
    FILE *fp;
    fp = fopen(data, "r");
    fgets(line, MAX_LINE_LEN, fp);
    char *fileByLine = fgets(line, MAX_LINE_LEN, fp);

    //declaring all the variables
    int count = 1;
    char *airportCity;
    char *airportCode;
    char *airportName;
    char *airportCountry;

    char *subject = NULL;
    node_t *list = NULL;
    int firstTime = 1;
    node_t *sortedList = NULL;

    while(fileByLine){

        
        if(count == 13){  //Checking if the current route is over

            count = 0;

        }
        if(count == 9) { //Getting the Destination Country
            char *token = strtok(line, ":");
            token = strtok(NULL, ":");
            airportName = strdup(strtok(token, ":"));

            while (*airportName == ' ') { //removing spaces at the beginning of the word
                airportName++;
            }
            airportName[strcspn(airportName, "\n")] = '\0';//removing trailing \n
        }

        if (count == 10){
            char *token2 = strtok(line, ":");
            token2 = strtok(NULL, ":");
            airportCity = strdup(strtok(token2, ":"));

            while (*airportCity == ' ') { //removing spaces at the beginning of the word
                airportCity++;
            }
            airportCity[strcspn(airportCity, "\n")] = '\0';//removing trailing \n
        }

        if(count == 11){
            char *token3 = strtok(line, ":");
            token3 = strtok(NULL, ":");
            airportCountry = strdup(strtok(token3, ":"));

            while (*airportCountry == ' ') { //removing spaces at the beginning of the word
                airportCountry++;
            }
            airportCountry[strcspn(airportCountry, "\n")] = '\0';//removing trailing \n

        }

        if(count == 12) {
            char *token3 = strtok(line, ":");
            token3 = strtok(NULL, ":");
            airportCode = strdup(strtok(token3, ":"));

            while (*airportCode == ' ') { //removing spaces at the beginning of the word
                airportCode++;
            }
            airportCode[strcspn(airportCode, "\n")] = '\0';//removing trailing \n

            //Formatting the subject according to the question
            subject = strcat(airportName, " (");
            subject = strcat(subject, airportCode);
            subject = strcat(subject, "), ");
            subject = strcat(subject, airportCity);
            subject = strcat(subject,", ");
            subject = strcat(subject, airportCountry); 


            //Checking whether or not the Node is in the list

           if(strcmp(airportCity, "\\N")!=0 && strcmp(airportCode,"\\N")!=0 && strcmp(airportCountry,"\\N")!= 0 && strcmp(airportCountry,"\\N")!=0){
                node_t *newNode = find_in_list(list, subject);
                if (newNode) {
                    newNode->statistic ++;
                }
                else {
                    list = add_end(list, new_node(subject, firstTime));
                }
        }
        
        }
        
        
        count++;

        fileByLine = fgets(line, MAX_LINE_LEN, fp); //Going to the next line in the YAML file
    
    }
    node_t *curr = NULL;

        while (list != NULL) {
        curr = list;
        list = list->next;
        curr->next = NULL;

        sortedList = add_inorder(sortedList, curr);
    }

    writeCSVq3(sortedList,n);
    
    
    fclose(fp);
    

}


void findQuestionType(int argc, char *argv[], char *typeOfQuestion){

    if(strcmp(typeOfQuestion,"1") == 0){
        question1(argc,argv);
    } else if(strcmp(typeOfQuestion,"2") == 0){
        question2(argc,argv);
    }else if(strcmp(typeOfQuestion,"3") == 0){
        question3(argc,argv);
    }

}


/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{

    // Initial dummy code
    char *line = NULL;
    char *t;
    int num = 0;
    int n= 1;
    node_t *list = NULL;
    line = (char *)malloc(sizeof(char) * MAX_LINE_LEN);
    strcpy(line, "this is the starting point for A3.");

    // Creating the nodes for the ordered list
    t = strtok(line, " ");
    while (t)
    {
        num++;
        list = add_inorder(list, new_node(t,n));
        t = strtok(NULL, " ");
    }

    // Printing out the content of the sorted list
    analysis(list);

    // Releasing the space allocated for the list and other emalloc'ed elements
    node_t *temp_n = NULL;
    for (; list != NULL; list = temp_n)
    {
        temp_n = list->next;
        free(list->subject);
        free(list);
    }
    free(line);

    char *typeOfQuestion = strtok(argv[2], "=");
    typeOfQuestion = strtok(NULL, "=");
    
    findQuestionType(argc,argv, typeOfQuestion);


    exit(0);
}
