#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAME_SIZE 30

enum race_locations {ParisRiybaix=0,AmstelGoldRace=1,LaFlecheWallonne=2,LiegeBastogneLiege=3};


struct  race_stats{
    int                 races_locations[LiegeBastogneLiege][];
    int                 points;
    int                 participants;

} race_stats;

struct racer {
    char                biker_first_name[MAX_NAME_SIZE];
    char                biker_last_name[MAX_NAME_SIZE];
    double              biker_age;
    char                biker_team[4];
    char                biker_nation[4];
    char                biker_position[4];
    char                bike_time[10];
    struct race_stats   race_stats;
} racer;

struct input_lines {
    char                race_name[MAX_NAME_SIZE];
    char                biker_first_name[MAX_NAME_SIZE];
    char                biker_last_name[MAX_NAME_SIZE];
    double              biker_age;
    char                biker_team[4];
    char                biker_nation[4];
    char                biker_position[4];
    char                bike_time[10];
}input_lines;


void parser(struct input_lines current_result[]);
int lines_counter();
struct input_lines point_counter(struct input_lines result,const int lines);
void itallian_bikers(struct input_lines result[]);
char danish_bikers(struct input_lines result[]);
int danes_counter(struct input_lines result[]);
void cleaner();


int main() {
    struct input_lines *results_array;
    results_array = (struct input_lines *) calloc (lines_counter(), sizeof(struct input_lines));

    /*Populating array of results*/
    parser(results_array);
    /*printf("Result test: %s \n",results_array[i].biker_first_name);*/
    cleaner(results_array,);
    itallian_bikers(results_array);
    danish_bikers(results_array);

    /*point_counter(results_array,lines);*/

    free(results_array);
    return 0;
}

void parser(struct input_lines current_result[]) {
    FILE *file;
    file = fopen("cykelloeb.txt","r");
    int i,j,lines;
    lines=lines_counter();
    for (i = 0; i < lines(); ++i) {
        /*ScanF for basic information*/
        fscanf(file, " %[a-zA-Z] "
                     " \"%[a-zA-Z-] "
                     " %[a-zA-Z ']\" "
                     "| %lf "
                     " %s "
                     " %s |"
                     " %s "
                     " %[0-9:-]", current_result[i].race_name, current_result[i].biker_first_name,
               current_result[i].biker_last_name,
               &current_result[i].biker_age, current_result[i].biker_team, current_result[i].biker_nation,
               current_result[i].biker_position, current_result[i].bike_time);
        /*Handle middlenames*/
        j= strlen(current_result.biker_last_name[i]);
        while (!islower(current_result[i].biker_last_name[j])) {
            j--;
        }
    }
    fclose(file);
}
void cleaner() {

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

/*struct input_lines point_counter(struct input_lines *result,const int lines) {
    int i;
    for (i = 0; i < lines; ++i) {

    }
    return *result;
}*/

void itallian_bikers(struct input_lines result[]) {
    int i;
    printf("Itallian bikers and their times: \n \n");
    for (i = 0; i <lines_counter(); ++i) {
        if (strcmp(result[i].biker_nation,"ITA") == 0 && result[i].biker_age > 30) {
                printf("The biker: %s %s | %s | %s |\n",result[i].biker_first_name,result[i].biker_last_name,result[i].race_name,result[i].bike_time);
        }
    }
}

char danish_bikers(struct input_lines result[]) {

}

int string_counter(struct input_lines result[]) {
    int i,danes_counter=0;
    for (i = 0; i < lines_counter(); ++i) {
        if (strcmp(result[i].biker_nation,"DEN")==0) {
            danes_counter++;
        }
    }
    return danes_counter;
}

void top_ten() {

}

void top_two() {

}

void average_age() {

}