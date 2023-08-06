#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_RECORDS 100
#define MAX_HOSTELS 5
#define MAX_COURSES 5
#define MAX_MEMORY_NODES 5
#define MAX_NAME_LENGTH 30

typedef struct {
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char hostel[MAX_NAME_LENGTH];
    char course[MAX_NAME_LENGTH];
    int room_number;
    char dob[11]; 
    int year_of_study;
} Student;

typedef struct Node {
    Student student;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

void init_linked_list(LinkedList* list) {
    list->head = NULL;
}

int count_linked_list(LinkedList* list) {
    int count = 0;
    Node* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void insert_linked_list(LinkedList* list, Student student) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->student = student;
    new_node->next = list->head;
    list->head = new_node;

    if (count_linked_list(list) > MAX_MEMORY_NODES) {
        // Remove the last node to maintain the maximum node constraint
        Node* prev = NULL;
        Node* current = list->head;
        while (current->next != NULL) {
            prev = current;
            current = current->next;
        }
        free(current);
        if (prev != NULL) {
            prev->next = NULL;
        } else {
            list->head = NULL;
        }
    }
}

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

Student generate_student_record(char first_names[MAX_RECORDS][MAX_NAME_LENGTH],
                                char last_names[MAX_RECORDS][MAX_NAME_LENGTH],
                                char hostels[MAX_HOSTELS][MAX_NAME_LENGTH],
                                char courses[MAX_COURSES][MAX_NAME_LENGTH]) {
    Student student;
    strcpy(student.first_name, first_names[rand() % MAX_RECORDS]);
    strcpy(student.last_name, last_names[rand() % MAX_RECORDS]);
    strcpy(student.hostel, hostels[rand() % MAX_HOSTELS]);
    strcpy(student.course, courses[rand() % MAX_COURSES]);
    student.room_number = 100 + rand() % 900;
    sprintf(student.dob, "%02d/%02d/%04d", 1 + rand() % 28, 1 + rand() % 12, 1990 + rand() % 16);
    student.year_of_study = 1 + rand() % 5;
    return student;
}

void registration() {
    char first_names[MAX_RECORDS][MAX_NAME_LENGTH];
    char last_names[MAX_RECORDS][MAX_NAME_LENGTH];
    char hostels[MAX_HOSTELS][MAX_NAME_LENGTH];
    char courses[MAX_COURSES][MAX_NAME_LENGTH];
    load_data_from_files(first_names, last_names, hostels, courses);
    Student student_record = generate_student_record(first_names, last_names, hostels, courses);

    FILE* db_file = fopen("disc.csv", "a");
    if (db_file != NULL) {
        fprintf(db_file, "%s, %s, %s, %s, %d, %s, %d\n", student_record.first_name, student_record.last_name,
                student_record.hostel, student_record.course, student_record.room_number,
                student_record.dob, student_record.year_of_study);
        fclose(db_file);
    }
}

void server() {
    LinkedList main_memory;
    init_linked_list(&main_memory);
    

    srand(time(NULL));

    while (1) {
        int operation_id;
        printf("Enter operation id (0: registration, 1: search, 2: update, 3: delete, -1: exit): ");
        scanf("%d", &operation_id);

        if (operation_id == -1) {
            break;
        } else if (operation_id == 0) {
            registration();
        } else if (operation_id == 1) {
            // Perform search operation
        } else if (operation_id == 2) {
            // Perform update operation
        } else if (operation_id == 3) {
            // Perform delete operation
        } else {
            printf("Invalid operation id.\n");
        }

        // Simulate disk and main memory access times
        sleep(2); // Disk access time (2 seconds)
        sleep(1); // Main memory access time (1 second)
    }
}

int main() {
    server();
    return 0;
}