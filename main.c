#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 30
#define MAXIMUM_FILE_LINES 2000
#define POS_COUNTRY_TEAM_LENGTH 4
/*Enum declaration*/
enum race_locations {
    ParisRoubaix = 0, AmstelGoldRace = 1, LaFlecheWallonne = 2, LiegeBastogneLiege = 3
};
/*Declaration of structs*/
struct race_stats {
    int participated;
    int number_of_participants;
    int points;
    char biker_position[POS_COUNTRY_TEAM_LENGTH];
    char race_time[10];
    char racename[MAX_NAME_SIZE];
} race_stats;

struct racer {
    char biker_first_name[MAX_NAME_SIZE];
    char biker_last_name[MAX_NAME_SIZE];
    double biker_age;
    char biker_team[POS_COUNTRY_TEAM_LENGTH];
    char biker_nation[POS_COUNTRY_TEAM_LENGTH];
    int total_points;
    int temp_time_cmp;
    char temp_time_cmp_string[14];
    struct race_stats race_stats[4];
} racer;

struct input_lines {
    char race_name[MAX_NAME_SIZE];
    char biker_first_name[MAX_NAME_SIZE];
    char biker_last_name[MAX_NAME_SIZE];
    double biker_age;
    char biker_team[POS_COUNTRY_TEAM_LENGTH];
    char biker_nation[POS_COUNTRY_TEAM_LENGTH];
    char biker_position[POS_COUNTRY_TEAM_LENGTH];
    char bike_time[10];
} input_lines;

/*Prototype declarations*/
void parser(struct input_lines current_result[]);

int string_counter(char *search_string);

void italian_bikers(struct racer result[]);

void danish_bikers(struct racer input[], struct racer danes_array[], int *races_participated_in);

void danes_printer(struct racer input[], int races_participated_in[], int number_of_danes);

int number_of_nationality(struct racer input[]);

void cleaner(struct input_lines input[], struct racer output[]);

void cleaner_copier(struct input_lines input[], struct racer output[], int k, int i);

int sorter(const void *a, const void *b);

void
race_copier(struct input_lines input[], struct racer output[], int i, int j, int participants, char racename[], int k);

void race_populator(struct input_lines input[], struct racer output[], int k, int i);

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

void middlename_clearer(struct input_lines current_result[], int i);

void average_age(struct racer input[]);

void assignment_1(struct racer races_array[]);

void assignment_2(struct racer races_array[]);

void assignment_3(struct racer races_array[]);

void assignment_4(struct racer races_array[]);

void assignment_5(struct racer races_array[]);

void input_prompt(struct racer races_array[]);


int main(int argc, char *argv[]) {
    struct input_lines *input_arrary;
    struct racer *races_array;
    int lines;
    char input[2] = "\n";

    lines = string_counter(input);
    races_array = (struct racer *) calloc(lines, sizeof(struct racer));
    input_arrary = (struct input_lines *) calloc(lines, sizeof(struct input_lines));

    /*Populating array of results*/
    parser(input_arrary);
    cleaner(input_arrary, races_array);
    free(input_arrary);

    if (argc == 2) {
        if (strcmp(argv[1], "--print") == 0) {
            assignment_1(races_array);
            assignment_2(races_array);
            assignment_3(races_array);
            assignment_4(races_array);
            assignment_5(races_array);
        }
    } else {
        input_prompt(races_array);
    }

    return 0;
}

void input_prompt(struct racer races_array[]) {
    int user_input;
    do {
        printf("\n \nPlease enter your choice of: \n \n"
               "\t Assignment 1 (Itallian bikers) \n"
               "\t Assignment 2 (Regarding danish bikers) \n"
               "\t Assignment 3 (Top ten racers) \n"
               "\t Assignment 4 (Shortest time in ParisRoubaix and AmstelGold) \n"
               "\t Assignment 5 (Average age of riders having finished top 10) \n"
               "\t Any other input to quit. \n");
        scanf("%d", &user_input);
        switch (user_input) {
            case 1:
                assignment_1(races_array);
                break;
            case 2:
                assignment_2(races_array);
                break;
            case 3:
                assignment_3(races_array);
                break;
            case 4:
                assignment_4(races_array);
                break;
            case 5:
                assignment_5(races_array);
                break;
            default:
                exit(1);
        }
    } while (user_input > 0);


}

/*Functions */
void assignment_1(struct racer races_array[]) {
    italian_bikers(races_array);

}

void assignment_2(struct racer races_array[]) {
    /*Assignment regarding the number of danish riders.*/
    int number_of_danes;
    int *races_participated_in;
    struct racer *danes;
    number_of_danes = number_of_nationality(races_array);

    races_participated_in = (int *) calloc(number_of_danes, sizeof(int));
    danes = (struct racer *) calloc(number_of_danes, sizeof(struct racer));
    danish_bikers(races_array, danes, races_participated_in);
    danes_printer(danes, races_participated_in, number_of_danes);
    free(danes);
}

void assignment_3(struct racer races_array[]) {
    top_ten(races_array);
}

void assignment_4(struct racer races_array[]) {
    shortest_time_two_races(races_array);
}

void assignment_5(struct racer races_array[]) {
    average_age(races_array);
}

int string_counter(char *search_string) {
    /*Taken from Julius (Other student)*/
    int n = 0;
    char line[MAXIMUM_FILE_LINES];
    FILE *file;
    file = fopen("cykelloeb", "r");
    while (fgets(line, MAXIMUM_FILE_LINES, file) != NULL) {
        if (strstr(line, search_string) != NULL) {
            n++;
        }
    }
    fclose(file);
    return n;
}

void parser(struct input_lines current_result[]) {
    int i, lines;
    FILE *file;
    file = fopen("cykelloeb", "r");
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
        middlename_clearer(current_result, i);
    }
    fclose(file);
}

void middlename_clearer(struct input_lines current_result[], int i) {
    int j;
    j = strlen(current_result[i].biker_last_name);
    /*Itterates through the bikers last name from behind, then splits the string when it hits a midddlename.
     * (The middlename defined by the first lowercase letter, as all lastnames are in uppercase)*/
    while (!isupper(current_result[i].biker_last_name[j])) {
        if (!isupper(current_result[i].biker_last_name[j - 1])) {
            strcpy(current_result[i].biker_last_name, current_result[i].biker_last_name - j);
        }
        j--;
    }
}

void cleaner(struct input_lines input[], struct racer output[]) {
    int i, k = -1, lines;
    /*The cleaner takes the input_array and sorts it into the new array: racer, this is done to make it easier to
     * finnish the later assignments based on the new structure,*/
    lines = string_counter("\n");
    qsort(input, lines, sizeof(input_lines), sorter);
    /*The qsort above sorts the input array in alphabetic order of lastnames.
     * after this the if statement below uses the functions to combine dublicates and merge these, to ensure only one
     * representation of each rider.
     *  */
    for (i = 0; i <= lines; ++i) {
        if (strcmp(input[i].biker_first_name, input[i - 1].biker_first_name) == 0) {
            race_populator(input, output, k, i);
        } else {
            k++;
            cleaner_copier(input, output, k, i);
            race_populator(input, output, k, i);
        }
    }
}

void cleaner_copier(struct input_lines input[], struct racer output[], int k, int i) {
    /*Adds persons not already in the race array, to the race array.*/
    strcpy(output[k].biker_first_name, input[i].biker_first_name);
    strcpy(output[k].biker_last_name, input[i].biker_last_name);
    strcpy(output[k].biker_team, input[i].biker_team);
    strcpy(output[k].biker_nation, input[i].biker_nation);
    output[k].biker_age = input[i].biker_age;
}

void race_populator(struct input_lines input[], struct racer output[], int k, int i) {
    int ParisRoubaoix_participants, AmstelGoldRace_participants,
            LaFlecheWallonne_participants, LiegeBastogneLiege_participants;
    /*Checks what race the itteration is taken from*/
    ParisRoubaoix_participants = string_counter("ParisRoubaix");
    AmstelGoldRace_participants = string_counter("AmstelGoldRace");
    LaFlecheWallonne_participants = string_counter("LaFlecheWallonne");
    LiegeBastogneLiege_participants = string_counter("LiegeBastogneLiege");
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

void
race_copier(struct input_lines input[], struct racer output[], int k, int j, int participants, char racename[], int i) {
    /*This function is called whenever a rider allready exists within the sorted race_array struct, and therefor it
    * adds the race to the rider.*/
    strcpy(output[k].race_stats[j].biker_position, input[i].biker_position);
    strcpy(output[k].race_stats[j].race_time, input[i].bike_time);
    output[k].race_stats[j].number_of_participants = participants;
    output[k].race_stats[j].participated = 1;
    strcpy(output[k].race_stats[j].racename, racename);
    output[k].race_stats[j].points = point_calculator(input[i], participants);
}


void italian_bikers(struct racer input[]) {
    /*This function finds and returns all itallian bikers, over the age of thirty, int the array, input (race_array)*/
    int i, k = 0, lines;
    lines = string_counter("\n");
    printf("Italian bikers and their times: \n \n");
    for (i = 0; i < lines; ++i) {
        if (strcmp(input[i].biker_nation, "ITA") == 0 && input[i].biker_age > 30) {
            printf("   \nThe driver %s %s participated in:  \n", input[i].biker_first_name, input[i].biker_last_name);
            for (k = 0; k <= LiegeBastogneLiege; ++k) {
                if (input[i].race_stats[k].participated == 1) {
                    printf("\t %s with the position %s and time %s \n", input[i].race_stats[k].racename,
                           input[i].race_stats[k].biker_position, input[i].race_stats[k].race_time);
                }
            }
        }
    }
}

int sorter(const void *a, const void *b) {
    /* Sorter taken from http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
     * Assist to qsort, sorting from cleaner*/

    struct input_lines *ia = (struct input_lines *) a;
    struct input_lines *ib = (struct input_lines *) b;
    return strcmp(ia->biker_last_name, ib->biker_last_name);
}

int point_calculator(struct input_lines input, int m) {
    /*Calculates the a biker, based on on the one race passed through input*/
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

void danish_bikers(struct racer input[], struct racer danes_array[], int *races_participated_in) {
    /*Finds danes within the race_array, and puts these into danes_array as well as updates the array of the amount of races
     * they've participated in. The array key in danes_array and races_participated in is the same, and therefor
     * one can link the inputs.*/
    int i, k = -1;
    for (i = 0; i <= string_counter("\n"); ++i) {
        if (strcmp(input[i].biker_nation, "DEN") == 0) {
            if (participated_races(input[i]) > 0) {
                k++;
                strcpy(danes_array[k].biker_first_name, input[i].biker_first_name);
                strcpy(danes_array[k].biker_last_name, input[i].biker_last_name);
                races_participated_in[k] = participated_races(input[i]);
            }
        }
    }
}

int participated_races(struct racer input) {
    /*Counts the anount of races a dane has completed*/
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

int number_of_nationality(struct racer input[]) {
    /*Helper function for danes_printer, returns the amount of danish riders*/
    int i, count = 0;
    for (i = 0; i < string_counter("\n"); ++i) {
        if (strcmp(input[i].biker_nation, "DEN") == 0) {
            count++;
        }
    }
    return count;
}

void danes_printer(struct racer input[], int races_participated_in[], int number_of_danes) {
    /*Helper function for danish bikers, prints the result.*/
    int i;
    printf("\nThe danes: \n");
    for (i = 0; i < number_of_danes; ++i) {
        if (races_participated_in[i] > 0) {
            printf("\t The danish rider %s %s has finnished in %d race%s\n", input[i].biker_first_name,
                   input[i].biker_last_name,
                   races_participated_in[i], races_participated_in[i] > 1 ? "s" : "");
        }
    }
}

void top_ten(struct racer input[]) {
    /*Top ten calculater, this function calculates the top ten riders based on the input array*/
    int i;
    printf("\n \n \n");
    /*This function is called to calculate the total amount of points gathered through the races.*/
    total_point_calculator(input);
    /*Sorts the riders in order of the above calculated points (Highest to lowest)*/
    qsort(input, string_counter("\n"), sizeof(struct racer), top_ten_compare);
    /*Prints the first 10 entries in the sorted struct array. (Top ten)*/
    printf("Top 10: \n \n");
    for (i = 0; i < 10; ++i) {
        printf(" \t [%d] Name : %s %s | Points %d \n", i + 1, input[i].biker_first_name, input[i].biker_last_name,
               input[i].total_points);
    }

}

void total_point_calculator(struct racer input[]) {
    /*Helper function for top ten, calculates the total amount of points*/
    int total = 0, i, j;
    for (i = 0; i < string_counter("\n"); ++i) {
        total = 0;
        for (j = 0; j <= LiegeBastogneLiege; ++j) {
            total += input[i].race_stats[j].points;
        }
        input[i].total_points = total;
    }
}


int top_ten_compare(const void *a, const void *b) {
    /*Top ten comparison helper for qsort in the top_ten function*/
    struct racer *ia = (struct racer *) a;
    struct racer *ib = (struct racer *) b;
    int result = ib->total_points - ia->total_points;

    if (result == 0) {
        return strcmp(ia->biker_last_name, ib->biker_last_name);
    } else {
        return result;
    }
}

void shortest_time_two_races(struct racer input[]) {
    time_calculator(input);
    qsort(input, string_counter("\n"), sizeof(struct racer), seconds_sorter);
    seconds_to_string_converter(input);
    shortest_time_printer(input);
}

void time_calculator(struct racer input[]) {
    /*Calculates the amount of time spent on both races combined. Returns this in seconds added to the tmp_time_cmp
     * part of the race struct.*/
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
        input[i].temp_time_cmp = result;
    }
}

int seconds_sorter(const void *a, const void *b) {
    struct racer *ia = (struct racer *) a;
    struct racer *ib = (struct racer *) b;

    return ia->temp_time_cmp - ib->temp_time_cmp;
}

void seconds_to_string_converter(struct racer input[]) {
    /*Converts the seconds back into a string, to make it easier to print*/
    int i, hours, minutes, seconds, remainder;
    for (i = 0; i < string_counter("\n"); ++i) {
        if (input[i].temp_time_cmp > 0) {
            hours = input[i].temp_time_cmp / 3600;
            remainder = input[i].temp_time_cmp % 3600;
            minutes = remainder / 60;
            seconds = remainder % 60;
            sprintf(input[i].temp_time_cmp_string, "%d:%d:%d", hours, minutes, seconds);
        }
    }
}

int time_to_seconds_converter(int hours, int minutes, int seconds) {
    /*Convets hours,minutes and seconds into seconds*/
    hours = hours * 3600;
    minutes = minutes * 60;
    return hours + minutes + seconds;
}

void shortest_time_printer(struct racer input[]) {
    /*Helper function for shortest_time_two_races, prints the result.*/
    int i = 0, k = 0, j = 0;
    while (input[i].temp_time_cmp == -1) {
        i++;
    }
    k = i;

    while (input[k].temp_time_cmp == input[k + 1].temp_time_cmp) {
        k++;
    }
    printf("\n \nTop rider%s on ParisRoubaix and AmstelGoldRace\n", k > 1 ? "s" : "");
    for (j = i; j <= k; ++j) {
        printf("\t The biker%s: %s %s came first with the time %s h\n", k > 1 ? "s" : "", input[j].biker_first_name,
               input[j].biker_last_name, input[j].temp_time_cmp_string);
    }
}

void average_age(struct racer input[]) {
    /*Finds and calculates the average age of top 10.*/
    int i, j, count_racers = 0;
    double sum = 0.0, average_age;
    for (i = 0; i <= string_counter("\n"); ++i) {
        for (j = 0; j <= LiegeBastogneLiege; ++j) {
            if (strcmp(input[i].race_stats[j].biker_position, "DNF") != 0 &&
                strcmp(input[i].race_stats[j].biker_position, "OTL") != 0) {
                if (atoi(input[i].race_stats[j].biker_position) <= 10 && input[i].race_stats[j].participated == 1) {
                    sum += input[i].biker_age;
                    count_racers++;
                    i++;
                    j = 0;
                }
            }
        }
    }
    average_age = (sum / count_racers);
    printf("\n \n Average age of top 10 is: %f \n \n", average_age);
}