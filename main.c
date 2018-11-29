#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 30
#define MAXIMUM_FILE_LINES 2000
/*Enum declaration*/
enum race_locations {
    ParisRoubaix = 0, AmstelGoldRace = 1, LaFlecheWallonne = 2, LiegeBastogneLiege = 3
};
/*Declaration of structs*/
struct race_stats {
    int participated;
    int number_of_participants;
    int points;
    char biker_position[4];
    char race_time[10];
    char racename[MAX_NAME_SIZE];
} race_stats;

struct racer {
    char biker_first_name[MAX_NAME_SIZE];
    char biker_last_name[MAX_NAME_SIZE];
    double biker_age;
    char biker_team[4];
    char biker_nation[4];
    int total_points;
    int time_in_PR_AG;
    char time_in_PR_AG_string[14];
    struct race_stats race_stats[4];
} racer;

struct input_lines {
    char race_name[MAX_NAME_SIZE];
    char biker_first_name[MAX_NAME_SIZE];
    char biker_last_name[MAX_NAME_SIZE];
    double biker_age;
    char biker_team[4];
    char biker_nation[4];
    char biker_position[4];
    char bike_time[10];
} input_lines;

/*Prototype declarations*/
void parser(struct input_lines current_result[]);

int string_counter(char *search_string);

void italian_bikers(struct racer result[]);

void danish_bikers(struct racer input[], struct racer output[], int *races_participated_in);

void danes_printer(struct racer input[], int races_participated_in[], int number_of_danes);

int number_of_nationality(struct racer input[]);

void cleaner(struct input_lines input[], struct racer output[]);

void cleaner_copier(struct input_lines input[], struct racer output[], int k, int i);

int sorter(const void *a, const void *b);

void
race_copier(struct input_lines input[], struct racer output[], int i, int j, int participants, char racename[], int k);

int point_calculator(struct input_lines input, int m);

int participated_races(struct racer input);

void top_ten(struct racer input[]);

void total_point_calculator(struct racer input[]);

int top_ten_compare(const void *a, const void *);

int time_to_seconds_converter(int hours, int minutes, int seconds);

void time_calculator(struct racer input[]);

void shortest_time_two_races(struct racer input[]);

int seconds_sorter(const void *a, const void *b);

void shortest_time_printer(struct racer input[]);

void seconds_to_string_converter(struct racer input[]);

int main() {
    struct input_lines *input_arrary;
    struct racer *races_array;
    struct racer *danes;
    int lines;
    char input[2] = "\n";
    int *races_participated_in;
    int number_of_danes;


    lines = string_counter(input);
    races_array = (struct racer *) calloc(lines, sizeof(struct racer));
    input_arrary = (struct input_lines *) calloc(lines, sizeof(struct input_lines));


    /*Populating array of results*/
    parser(input_arrary);
    /*printf("Result test: %s \n",input_arrary[i].biker_first_name);*/
    cleaner(input_arrary, races_array);
    number_of_danes = number_of_nationality(races_array);

    free(input_arrary);
    races_participated_in = (int *) calloc(number_of_danes, sizeof(int));
    danes = (struct racer *) calloc(number_of_danes, sizeof(struct racer));

    italian_bikers(races_array);
    danish_bikers(races_array, danes, races_participated_in);
    danes_printer(danes, races_participated_in, number_of_danes);
    free(danes);

    top_ten(races_array);
    shortest_time_two_races(races_array);

    return 0;
}

/*Functions */
int string_counter(char *search_string) {
    FILE *file;
    file = fopen("cykelloeb.txt", "r");
    int n = 0;
    char line[MAXIMUM_FILE_LINES];

    while (fgets(line, MAXIMUM_FILE_LINES, file) != NULL) {
        if (strstr(line, search_string) != NULL) {
            n++;
        }
    }
    fclose(file);
    return n;
}

void parser(struct input_lines current_result[]) {
    FILE *file;
    file = fopen("cykelloeb.txt", "r");
    int i, lines;
    lines = string_counter("\n");
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

void cleaner(struct input_lines input[], struct racer output[]) {
    int ParisRoubaoix_participants, AmstelGoldRace_participants,
            LaFlecheWallonne_participants, LiegeBastogneLiege_participants,
            i, k = -1, lines;


    ParisRoubaoix_participants = string_counter("ParisRoubaix");
    AmstelGoldRace_participants = string_counter("AmstelGoldRace");
    LaFlecheWallonne_participants = string_counter("LaFlecheWallonne");
    LiegeBastogneLiege_participants = string_counter("LiegeBastogneLiege");
    lines = string_counter("\n");


    /*Starts by sorting array*/
    qsort(input, lines, sizeof(input_lines), sorter);
    /*Start of setup regarding race_stats structs, these lines insert the required information into:
     * Number of participants
     * Race location
     *
     *  */
    for (i = 0; i <= lines; ++i) {
        if (strcmp(input[i].biker_first_name, input[i - 1].biker_first_name) == 0) {
            if (strcmp(input[i].race_name, "ParisRoubaix") == 0) {
                race_copier(input, output, k, ParisRoubaix, ParisRoubaoix_participants, "ParisRoubaix", i);
            } else if (strcmp(input[i].race_name, "AmstelGoldRace") == 0) {
                race_copier(input, output, k, AmstelGoldRace, AmstelGoldRace_participants, "AmstelGoldRace", i);
            } else if (strcmp(input[i].race_name, "LaFlecheWallonne") == 0) {
                race_copier(input, output, k, LaFlecheWallonne, LaFlecheWallonne_participants, "LaFlecheWallonne", i);
            } else if (strcmp(input[i].race_name, "LiegeBastogneLiege") == 0) {
                race_copier(input, output, k, LiegeBastogneLiege, LiegeBastogneLiege_participants,
                            "LiegeBastogneLiege", i);
            }
        } else {
            k++;
            cleaner_copier(input, output, k, i);
            if (strcmp(input[i].race_name, "ParisRoubaix") == 0) {
                race_copier(input, output, k, ParisRoubaix, ParisRoubaoix_participants, "ParisRoubaix", i);
            } else if (strcmp(input[i].race_name, "AmstelGoldRace") == 0) {
                race_copier(input, output, k, AmstelGoldRace, AmstelGoldRace_participants, "AmstelGoldRace", i);
            } else if (strcmp(input[i].race_name, "LaFlecheWallonne") == 0) {
                race_copier(input, output, k, LaFlecheWallonne, LaFlecheWallonne_participants, "LaFlecheWallonne", i);
            } else if (strcmp(input[i].race_name, "LiegeBastogneLiege") == 0) {
                race_copier(input, output, k, LiegeBastogneLiege, LiegeBastogneLiege_participants,
                            "LiegeBastogneLiege", i);
            }

        }
    }
}

void cleaner_copier(struct input_lines input[], struct racer output[], int k, int i) {
    /*Check igennem arrayet, checker hvorvidt navnet er i arrayet allerede, ellers tilføjes det til arrayet.*/
    /*Person inputs*/
    strcpy(output[k].biker_first_name, input[i].biker_first_name);
    strcpy(output[k].biker_last_name, input[i].biker_last_name);
    strcpy(output[k].biker_team, input[i].biker_team);
    strcpy(output[k].biker_nation, input[i].biker_nation);
    output[k].biker_age = input[i].biker_age;
    //printf("String test %s \n",output[j].biker_nation);
}

void
race_copier(struct input_lines input[], struct racer output[], int k, int j, int participants, char racename[], int i) {
    strcpy(output[k].race_stats[j].biker_position, input[i].biker_position);
    strcpy(output[k].race_stats[j].race_time, input[i].bike_time);
    output[k].race_stats[j].number_of_participants = participants;
    output[k].race_stats[j].participated = 1;
    strcpy(output[k].race_stats[j].racename, racename);
    output[k].race_stats[j].points = point_calculator(input[i], participants);
}


void italian_bikers(struct racer result[]) {
    int i, k = 0, lines;
    lines = string_counter("\n");
    printf("Italian bikers and their times: \n \n");
    for (i = 0; i < lines; ++i) {
        if (strcmp(result[i].biker_nation, "ITA") == 0 && result[i].biker_age > 30) {
            printf(" The driver %s %s participated in:  \n", result[i].biker_first_name, result[i].biker_last_name);
            for (k = 0; k <= LiegeBastogneLiege; ++k) {
                if (result[i].race_stats[k].participated == 1) {
                    printf("    %s with the position %s and time %s \n", result[i].race_stats[k].racename,
                           result[i].race_stats[k].biker_position, result[i].race_stats[k].race_time);
                }
            }
        }
    }
}

int sorter(const void *a, const void *b) {
    /* Sorter taken from http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml */

    struct input_lines *ia = (struct input_lines *) a;
    struct input_lines *ib = (struct input_lines *) b;
    return strcmp(ia->biker_last_name, ib->biker_last_name);
}

int point_calculator(struct input_lines input, int m) {
    int i, participation_points = 0, placements_points = 0, podium_points = 0;
    for (i = 0; i <= LiegeBastogneLiege; ++i) {
        if (strcmp(input.biker_position, "DNF") != 0 && strcmp(input.biker_position, "OTL") != 0) {
            participation_points = 3;
            placements_points = (m - atoi(input.biker_position)) / 13;
            if (atoi(input.biker_position) == 1) {
                podium_points = 10;
            } else if (atoi(input.biker_position) == 2) {
                podium_points = 5;
            } else if (atoi(input.biker_position) == 3) {
                podium_points = 2;
            }
        } else {
            if (strcmp(input.biker_position, "OTL") == 0) {
                participation_points = 1;
            }
        }
    }
    return participation_points + placements_points + podium_points;
}

void danish_bikers(struct racer input[], struct racer output[], int *races_participated_in) {
    int i, k = -1;
    for (i = 0; i <= string_counter("\n"); ++i) {
        if (strcmp(input[i].biker_nation, "DEN") == 0) {
            if (participated_races(input[i]) > 0) {
                k++;
                strcpy(output[k].biker_first_name, input[i].biker_first_name);
                strcpy(output[k].biker_last_name, input[i].biker_last_name);
                races_participated_in[k] = participated_races(input[i]);

            }
        }
    }
}

int participated_races(struct racer input) {
    int j, count = 0;
    for (j = 0; j <= LiegeBastogneLiege; ++j) {
        if (strcmp(input.race_stats[j].biker_position, "DNF") != 0) {
            if (input.race_stats[j].participated == 1) {
                count++;
            }
        }
    }
    return count;
}

void danes_printer(struct racer input[], int races_participated_in[], int number_of_danes) {
    int i;
    printf("\nThe danes: \n");
    for (i = 0; i < number_of_danes; ++i) {
        if (races_participated_in[i] > 0) {
            printf("The danish rider %s %s has finnished in %d race(s)\n", input[i].biker_first_name,
                   input[i].biker_last_name,
                   races_participated_in[i]);
        }
    }
}

int number_of_nationality(struct racer input[]) {
    int i, count = 0;
    for (i = 0; i < string_counter("\n"); ++i) {
        if (strcmp(input[i].biker_nation, "DEN") == 0) {
            count++;
        }
    }
    return count;
}

void total_point_calculator(struct racer input[]) {
    int total = 0, i, j;
    for (i = 0; i < string_counter("\n"); ++i) {
        total = 0;
        for (j = 0; j <= LiegeBastogneLiege; ++j) {
            //printf("Current points %d \n",input[i].race_stats[j].points);

            total += input[i].race_stats[j].points;
        }
        input[i].total_points = total;
        //printf("Total points %d \n",input[i].total_points);
    }
}

void top_ten(struct racer input[]) {
    //Start med at qsort alle input variablerne, det er variablen: input.[i].racestats.points.
    // Disse skal dog ligges over i en variabel hvori de bliver lagt sammen.
    printf("\n \n \n");
    int i;
    total_point_calculator(input);

    qsort(input, string_counter("\n"), sizeof(struct racer), top_ten_compare);

    printf("Top 10: \n \n");
    for (i = 0; i < 10; ++i) {
        printf(" Name : %s %s | Points %d \n", input[i].biker_first_name, input[i].biker_last_name,
               input[i].total_points);
    }

}

int top_ten_compare(const void *a, const void *b) {
    struct racer *ia = (struct racer *) a;
    struct racer *ib = (struct racer *) b;

    int result = ib->total_points - ia->total_points;

    if (result < 0) {
        return -1;
    }

    if (result > 0) {
        return 1;
    }

    result = strcmp(ia->biker_last_name, ib->biker_last_name);

    return result;
}

void shortest_time_two_races(struct racer input[]) {
    time_calculator(input);
    qsort(input, string_counter("\n"), sizeof(struct racer), seconds_sorter);
    seconds_to_string_converter(input);
    shortest_time_printer(input);


}

void shortest_time_printer(struct racer input[]) {
    int i = 0, k = 0, j = 0;
    while (input[i].time_in_PR_AG == -1) {
        i++;
    }
    k = i;

    while (input[k].time_in_PR_AG == input[k + 1].time_in_PR_AG) {
        k++;
    }
    printf("\n \nTop rider%s on ParisRoubaix and AmstelGoldRace\n", k > 1 ? "s" : "");
    for (j = i; j <= k; ++j) {
        printf("  The biker%s: %s came first with the time %s h\n", k > 1 ? "s" : "", input[j].biker_first_name,
               input[j].time_in_PR_AG_string);
    }
}

void time_calculator(struct racer input[]) {
    int i, j;
    int hours = 0, seconds = 0, minutes = 0, result = 0, totalhours = 0, totalminutes = 0, totalseconds = 0;
    for (i = 0; i < string_counter("\n"); ++i) {
        result = 0;
        totalhours = 0;
        totalminutes = 0;
        totalseconds = 0;

        for (j = 0; j <= AmstelGoldRace; ++j) {
            if (input[i].race_stats[j].participated == 1) {
                if (strcmp(input[i].race_stats[j].race_time, "-") != 0) {
                    sscanf(input[i].race_stats[j].race_time, " %d : %d : %d ", &hours, &minutes, &seconds);
                    totalhours += hours;
                    totalminutes += minutes;
                    totalseconds += seconds;
                    if (result != -1) {
                        result = time_to_seconds_converter(totalhours, totalminutes, totalseconds);
                    } else {
                        result = -1;
                    }
                } else {
                    result = -1;
                }
            } else {
                result = -1;
            }
        }
        input[i].time_in_PR_AG = result;
    }
}

int time_to_seconds_converter(int hours, int minutes, int seconds) {
    hours = hours * 3600;
    minutes = minutes * 60;
    return hours + minutes + seconds;
}

int seconds_sorter(const void *a, const void *b) {
    struct racer *ia = (struct racer *) a;
    struct racer *ib = (struct racer *) b;

    return ia->time_in_PR_AG - ib->time_in_PR_AG;
}

void seconds_to_string_converter(struct racer input[]) {
    int i, hours, minutes, seconds, remainder;
    for (i = 0; i < string_counter("\n"); ++i) {
        if (input[i].time_in_PR_AG > 0) {
            hours = input[i].time_in_PR_AG / 3600;
            remainder = input[i].time_in_PR_AG % 3600;
            minutes = remainder / 60;
            seconds = remainder % 60;
            sprintf(input[i].time_in_PR_AG_string, "%d:%d:%d", hours, minutes, seconds);
        }
    }
}

void average_age() {

}