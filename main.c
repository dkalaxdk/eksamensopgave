#include <stdio.h>
#include <malloc.h>

struct result {
    char    race_name[17];
    char    biker_first_name[20];
    char    biker_last_name[20];
    int     biker_age;
    char    biker_team[4];
    char    biker_nation[4];
    int     biker_position;
    char    bike_time[10];
}result;
struct result parser(FILE *file,struct result current_result);
int lines_counter(FILE *file);

int main() {
    int i, lines =0;
    struct result *results_array;
    FILE *file;
    file = fopen("cykelloeb.txt","r");


    lines = lines_counter(file);
    results_array = (struct result *) calloc (lines, sizeof(struct result));

    rewind(file);

    for (i = 270; i < lines; ++i) {
        results_array[i]=parser(file,results_array[i]);
    }

    printf("Result test: %s \n",results_array[1].biker_first_name);





    return 0;
}

struct result parser(FILE *file,struct result current_result) {
    fscanf(file," %s "
                " \"%[a-zA-Z] "
                " %[A-Z ]\" "
                "| %d "
                " %s "
                " %s |"
                " %d "
                " %[0-9:]" , current_result.race_name,current_result.biker_first_name,current_result.biker_last_name,
                &current_result.biker_age,current_result.biker_team,current_result.biker_nation,
                &current_result.biker_position,current_result.bike_time);
    printf("Current result: %s \n",current_result.biker_last_name);
    printf("Current result. racename: %s \n",current_result.race_name);

    return current_result;
}

int lines_counter(FILE *file) {
    int lines=0;
    char test;
    while (!feof(file)) {
        test = fgetc(file);
        if (test=='\n') {
            lines ++;
        }
    }
    return lines;
}

void itallian_bikers() {

}

void danish_bikers() {

}

void top_ten() {

}

void top_two() {

}

void average_age() {

}