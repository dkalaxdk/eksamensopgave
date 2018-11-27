#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAME_SIZE 30

struct total_points {
    char    biker_first_name[MAX_NAME_SIZE];
    char    biker_last_name[MAX_NAME_SIZE];
    char    biker_team[MAX_NAME_SIZE];
    int     points;

};

struct result {
    char    race_name[MAX_NAME_SIZE];
    char    biker_first_name[MAX_NAME_SIZE];
    char    biker_last_name[MAX_NAME_SIZE];
    double  biker_age;
    char    biker_team[4];
    char    biker_nation[4];
    char    biker_position[4];
    char    bike_time[10];

}result;


struct result parser(struct result current_result,FILE *file);
int lines_counter();
struct result point_counter(struct result *result,const int lines);
void itallian_bikers(struct result result[]);

int main() {
    int i, lines =0;
    struct result *results_array;
    FILE *file;
    file = fopen("cykelloeb.txt","r");
    lines=lines_counter();
    results_array = (struct result *) calloc (lines, sizeof(struct result));

    /*Populating array of results*/
    for (i = 0; i < lines; ++i) {
        results_array[i]=parser(results_array[i],file);
        /*printf("Result test: %s \n",results_array[i].biker_first_name);*/
    }
    fclose(file);

    itallian_bikers(results_array);

    /*point_counter(results_array,lines);*/


    return 0;
}

struct result parser(struct result current_result,FILE *file) {
    int i;

    /*ScanF for basic information*/
    fscanf(file," %[a-zA-Z] "
                " \"%[a-zA-Z-] "
                " %[a-zA-Z ']\" "
                "| %lf "
                " %s "
                " %s |"
                " %s "
                " %[0-9:-]" , current_result.race_name,current_result.biker_first_name,current_result.biker_last_name,
                &current_result.biker_age,current_result.biker_team,current_result.biker_nation,
                current_result.biker_position,current_result.bike_time);
    /*Handle middlenames*/
    for (i = strlen(current_result.biker_last_name); 0 <= i ; --i) {
        /*Starts by checking if a letter (Starting from the back) is uppercase*/
        if (isupper(current_result.biker_last_name[i])) {
            /*Checks whether the next letter is a small letter.
             * If this letter is a small letter the code has hit the middlename.*/
            if(islower(current_result.biker_last_name[i-1])){
                /*Copies the remainder of the string into biker_last_name, hereby updating the string, to only contain capitalized lastnames.*/
                strcpy(current_result.biker_last_name, current_result.biker_last_name + i);
                return current_result;
            }
        }
    }
    return current_result;
}

int lines_counter() {
    FILE *file;
    file = fopen("cykelloeb.txt","r");
    int lines=0;
    char test;
    while (!feof(file)) {
        test = fgetc(file);
        if (test=='\n') {
            lines ++;
        }
    }
    fclose(file);
    return lines;
}

struct result point_counter(struct result *result,const int lines) {
    int i;
    for (i = 0; i < lines; ++i) {

    }
    return *result;
}

void itallian_bikers(struct result result[]) {
    int i;
    printf("Itallian bikers and their times: \n");
    for (i = 0; i <lines_counter(); ++i) {
        if (strcmp(result[i].biker_nation,"ITA")) {
            printf("The biker: %s %s | %s | %s |\n",result[i].biker_first_name,result[i].biker_last_name,result[i].race_name,result[i].bike_time);
        }

    }
}

void danish_bikers() {

}

void top_ten() {

}

void top_two() {

}

void average_age() {

}