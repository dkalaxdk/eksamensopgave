#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAME_SIZE 30
#define MAXIMUM_FILE_LINES 2000
#define MAXIMUM_RACERS 300

enum race_locations {ParisRiybaix=0,AmstelGoldRace=1,LaFlecheWallonne=2,LiegeBastogneLiege=3};

struct racer {
    char                biker_first_name[MAX_NAME_SIZE];
    char                biker_last_name[MAX_NAME_SIZE];
    double              biker_age;
    char                biker_team[4];
    char                biker_nation[4];
    char                biker_position[4];
    char                bike_time[10];
    char                position[4];
    int                 points;
    char                race_time[10];
} racer;

struct  race_stats{
    int                 races_locations;
    int                 number_of_participants;
    struct racer        participants[MAXIMUM_RACERS];

} race_stats;



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
int string_counter(char *search_string);
void itallian_bikers(struct input_lines result[]);
char danish_bikers(struct input_lines result[]);
void cleaner(struct input_lines input[], struct race_stats output[]);


int main() {
    struct input_lines *results_array;
    struct race_stats *races_array;
    int lines;
    char input[2] = "\n";
    lines = string_counter(input);
    races_array =  (struct race_stats *)        calloc (4, sizeof(struct race_stats));
    results_array = (struct input_lines *)  calloc (lines, sizeof(struct input_lines));
    /*Populating array of results*/

    parser(results_array);
    /*printf("Result test: %s \n",results_array[i].biker_first_name);*/
    cleaner(results_array,races_array);
    //itallian_bikers(results_array);
    //danish_bikers(results_array);

    /*point_counter(results_array,lines);*/

    //free(results_array);
    return 0;
}

int string_counter(char *search_string){
    FILE *file;
    file = fopen("cykelloeb.txt","r");
    int n = 0;
    char line[MAXIMUM_FILE_LINES];

    while (fgets(line, MAXIMUM_FILE_LINES, file) != NULL){
        if (strstr(line, search_string) != NULL){
            n++;
        }
    }
    fclose(file);
    return n;
}

void parser(struct input_lines current_result[]) {
    FILE *file;
    file = fopen("cykelloeb.txt","r");
    int i,lines;
    lines=string_counter("\n");
    for (i = 0; i < lines; ++i) {
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
        //j=strlen(current_result[i].biker_last_name);
        //while (!islower(current_result[i].biker_last_name[j])) {
        //    j--;
        //}
    }
    fclose(file);
}
void cleaner(struct input_lines input[], struct race_stats output[]) {
    int ParisRoubaoix_participants,AmstelGoldRace_participants,LaFlecheWallonne_participants,LiegeBastogneLiege_participants;
    int i,j;
    ParisRoubaoix_participants =        string_counter("ParisRoubaix");
    AmstelGoldRace_participants =       string_counter("AmstelGoldRace");
    LaFlecheWallonne_participants =     string_counter("LaFlecheWallonne");
    LiegeBastogneLiege_participants =   string_counter("LiegeBastogneLiege");

    /*
     * Hvert ræs skal have en mængde af associerede køre, samt antallet af køre i ræset.
     *
     */
    output[ParisRiybaix].number_of_participants = ParisRoubaoix_participants;
    output[ParisRiybaix].races_locations = ParisRiybaix;
    for ( i = 0; i < string_counter("\n"); ++i) {
        if (i < ParisRoubaoix_participants) {
            strcpy(output->participants[i].biker_first_name, input[i].biker_first_name);
            strcpy(output->participants[i].biker_last_name, input[i].biker_last_name);
            strcpy(output->participants[i].biker_first_name, input[i].biker_first_name);
            strcpy(output->participants[i].biker_position, input[i].biker_position);
            strcpy(output->participants[i].biker_nation, input[i].biker_nation);
            strcpy(output->participants[i].biker_team, input[i].biker_team);
            strcpy(output->participants[i].race_time, input[i].bike_time);
            output->participants[i].biker_age = input[i].biker_age;
        }
    }



}

void itallian_bikers(struct input_lines result[]) {
    int i;
    printf("Itallian bikers and their times: \n \n");
    for (i = 0; i < string_counter("\n"); ++i) {
        if (strcmp(result[i].biker_nation,"ITA") == 0 && result[i].biker_age > 30) {
                printf("The biker: %s %s | %s | %s |\n",result[i].biker_first_name,result[i].biker_last_name,result[i].race_name,result[i].bike_time);
        }
    }
}

char danish_bikers(struct input_lines result[]) {

}



void top_ten() {

}

void top_two() {

}

void average_age() {

}