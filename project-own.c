#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

//will be used for random number generation
#define MAX_RECORDS 100
#define MAX_HOSTELS 5
#define MAX_COURSES 5
#define MAX_MEMORY_NODES 5
#define MAX_NAME_LENGTH 30

//student record
typedef struct Student{
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char hostel[MAX_HOSTELS];
    char course[MAX_COURSES];
    int id;
    int room_number;
    char dob[11]; 
    int year_of_study;
} std;

typedef struct linkedlist{
    char* stud;
    struct linkedlist* next;
}ll;

ll* head = NULL;
ll node1;
ll node2;
ll node3;
ll node4;
ll node5;
// operation store
void store(char* line){
    node1->stud = line;
    node5.next = NULL;
    while(head)
    head->next = &node1;
    head = head->next;


}

//generate random record
std generate_student_record(char first_names[MAX_RECORDS][MAX_NAME_LENGTH],
                                char last_names[MAX_RECORDS][MAX_NAME_LENGTH],
                                char hostels[MAX_HOSTELS][MAX_NAME_LENGTH],
                                char courses[MAX_COURSES][MAX_NAME_LENGTH]) {
    std student;
    strcpy(student.first_name, first_names[rand() % MAX_NAME_LENGTH]);
    strcpy(student.last_name, last_names[rand() % MAX_NAME_LENGTH]);
    strcpy(student.hostel, hostels[rand() % MAX_HOSTELS]);
    strcpy(student.course, courses[rand() % MAX_COURSES]);
    student.room_number = 100 + rand() % 900;
    sprintf(student.dob, "%02d/%02d/%04d", 1 + rand() % 28, 1 + rand() % 12, 1990 + rand() % 16);
    student.year_of_study = 1 + rand() % 5;
    student.id = rand()%1000 + 1;
    return student;
}

//loading data from files
void load_data_from_files(char first_names[MAX_RECORDS][MAX_NAME_LENGTH],
                         char last_names[MAX_RECORDS][MAX_NAME_LENGTH],
                         char hostels[MAX_HOSTELS][MAX_NAME_LENGTH],
                         char courses[MAX_COURSES][MAX_NAME_LENGTH]) {
    FILE* f;
    int i;

    f = fopen("names.txt", "r");
    for (i = 0; i < MAX_RECORDS; i++) {
        fgets(first_names[i], MAX_NAME_LENGTH, f);
        strtok(first_names[i], "\n");
    }
    fclose(f);

    f = fopen("last_names.txt", "r");
    for (i = 0; i < MAX_RECORDS; i++) {
        fgets(last_names[i], MAX_NAME_LENGTH, f);
        strtok(last_names[i], "\n");
    }
    fclose(f);

    f = fopen("hostels.txt", "r");
    for (i = 0; i < MAX_HOSTELS; i++) {
        fgets(hostels[i], MAX_NAME_LENGTH, f);
        strtok(hostels[i], "\n");
    }
    fclose(f);

    f = fopen("courses.txt", "r");
    for (i = 0; i < MAX_COURSES; i++) {
        fgets(courses[i], MAX_NAME_LENGTH, f);
        strtok(courses[i], "\n");
    }
    fclose(f);
}

// registration function op id 00
void registration() {
    char first_names[MAX_RECORDS][MAX_NAME_LENGTH];
    char last_names[MAX_RECORDS][MAX_NAME_LENGTH];
    char hostels[MAX_HOSTELS][MAX_NAME_LENGTH];
    char courses[MAX_COURSES][MAX_NAME_LENGTH];
    load_data_from_files(first_names, last_names, hostels, courses);
    std student_record = generate_student_record(first_names, last_names, hostels, courses);

    FILE* db_file = fopen("disc.txt", "a");
    if (db_file != NULL) {
        fprintf(db_file, "%d %s %s %s %s %d %s %d \n",student_record.id, student_record.first_name, student_record.last_name,
                student_record.hostel, student_record.course, student_record.room_number, student_record.dob, student_record.year_of_study);
        fclose(db_file);
    }
}

// search function op id 01
char* search(int id){
    FILE* f;
    f = fopen("disk.txt", 'r');
    int searchterm = id;
    char line[1024];

    while(fgets(line, sizeof(line), f)){
        if(strstr(line, searchterm) != NULL){
            printf("%s", line);
            return line;       
        }
    }
}

void update(int id){
  char* record = search(id);

}

void delete(int id){
    
}

int main(){
    server();

    return 0;
}