#ifndef TRANSCRIPT_H
#define TRANSCRIPT_H

#include <stddef.h>
#include <sys/types.h>
#define BUFFER_SIZE 20
#define MID_BUFFER_SIZE 50
#define un_long unsigned long

typedef struct {
    char student_name[MID_BUFFER_SIZE];
    char registration_no[BUFFER_SIZE];
    char year_of_study[BUFFER_SIZE];
} HeaderInfo;

typedef struct {
    double mark;
    char unit_code[BUFFER_SIZE];
    char unit_name[BUFFER_SIZE];
}Details;

Details get_details();
void write_md_file(const char* filename, const Details* details, int details_size, un_long longest_row, HeaderInfo header);
void write_pdf_file(const char* filename);

double calculate_mean_mark(const Details* details, int details_size);
char get_grade(double mark);

#endif // !TRANSCRIPT_H
