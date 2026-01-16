#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "transcript.h"

int main(void) {
    int unit_count;
    Details all_units[BUFFER_SIZE];
    un_long longest_row = strlen("Unit Name");
    HeaderInfo header;

    printf("Enter Student Name: ");
    fgets(header.student_name, MID_BUFFER_SIZE, stdin);
    header.student_name[strcspn(header.student_name, "\n")] = 0;

    printf("Enter Registration No: ");
    fgets(header.registration_no, BUFFER_SIZE, stdin);
    header.registration_no[strcspn(header.registration_no, "\n")] = 0;

    printf("Enter Year of Study: ");
    fgets(header.year_of_study, BUFFER_SIZE, stdin);
    header.year_of_study[strcspn(header.year_of_study, "\n")] = 0;

    printf("Enter number of units : ");
    scanf("%d", &unit_count);
    getchar(); // consume newline
    
    if (unit_count > 0 && unit_count <= BUFFER_SIZE) {
        for (int i = 0; i < unit_count; i++) {
            all_units[i] = get_details();

            // get the length of each row to find the longest one for formatting.
            if (strlen(all_units[i].unit_name) > longest_row) {
                longest_row = strlen(all_units[i].unit_name);
            }
        }
    } else {
        printf("Cannot enter marks for %d units!!\n", unit_count);
        return 1;
    }
    
    write_md_file("transcript.md", all_units, unit_count, longest_row, header);

    return 0;
}

Details get_details() {
    Details details;
    
    printf("Enter unit code [CCS 2203] : \n");
    fgets(details.unit_code, BUFFER_SIZE, stdin);
    details.unit_code[strcspn(details.unit_code, "\n")] = 0;

    printf("Enter unit name : ");
    fgets(details.unit_name, BUFFER_SIZE, stdin);
    details.unit_name[strcspn(details.unit_name, "\n")] = 0;
    

    printf("Enter Mark : ");
    scanf("%lf", &details.mark);
    getchar(); // consume newline
    
    return details;
}

void write_md_file(const char* filename, const Details* details, int details_size, un_long longest_row, HeaderInfo header) {
    FILE* fptr;
    fptr = fopen(filename, "w");
    
    if (fptr == NULL) {
        printf("Error opening file!!\n");
        return;
    }

    fprintf(fptr, "**Dedan Kimathi University of Technology**\n");
    fprintf(fptr, "**School of CS & IT**\n");
    fprintf(fptr, "**Year of Study :** %s\n", header.year_of_study);
    fprintf(fptr, "**Student Name :** %s\n", header.student_name);
    fprintf(fptr, "***Registration No :*** %s\n\n", header.registration_no);

    fprintf(fptr, "---\n");

    fprintf(fptr, "| %-*s | %-*s | %-7s |\n", BUFFER_SIZE, "Unit Code", (int)longest_row, "Unit Name", "Grade");
    fprintf(fptr, "|:");
    for(int i=0; i<BUFFER_SIZE; i++) fputc('-', fptr);
    fprintf(fptr, "-|:");
    for(int i=0; i<(int)longest_row; i++) fputc('-', fptr);
    fprintf(fptr, "-|:");
    for(int i=0; i<7; i++) fputc('-', fptr);
    fprintf(fptr, "-|\n");


    for (int index = 0; index < details_size; index++) {
        fprintf(fptr, "| %-*s | %-*s | %-7c |\n", 
                BUFFER_SIZE, details[index].unit_code,
                (int)longest_row, details[index].unit_name,
                get_grade(details[index].mark)
                );
    }
    
    fprintf(fptr, "\n**Aggregate Mean Mark is: %.2f**\n", calculate_mean_mark(details, details_size));
    fclose(fptr);
}

double calculate_mean_mark(const Details* details, int details_size) {
    double sum = 0;

    for (int index = 0; index < details_size; index++) {
        sum += details[index].mark;
    }

    return (sum / details_size);
}

char get_grade(double mark) {
    switch ((int)mark) {
        case 0 ... 39:
            return 'E';
        case 40 ... 49:
            return 'D';
        case 50 ... 59:
            return 'C';
        case 60 ... 69:
            return 'B';
        case 70 ... 100:
            return 'A';
        default:
            printf("Invalid mark %lf!! Mark must be between 0 to 100!!\n", mark);
            return 'Y';
    }
}


