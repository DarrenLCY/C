#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
** Code from "Engineering Computation" assignment completed at the 
** University of Melbourne. In this assignment, my task was to analyse 
** the spatial and temporal distributions of traffic accidents. We
** were given a list of traffic accident records like the one shown below:
** 
** 2693452 145.060689 -37.810373 26/5/12 11 Saturday
** 2693453 144.991172 -37.883156 6/6/12 15 Wednesday
** 2693454 145.009458 -37.826952 24/5/12 09 Thursday
** 2693455 145.134597 -37.841545 6/6/12 17 Wednesday
** 
** Particularly, each line of the list contains the information of a traffic 
** accident separated by spaces (' '), including the unique ID (a 7-digit
** integer), the accident location longitude (a real number with 6 digits 
** after the decimal point), the accident location latitude (a real number 
** with 6 digits after the decimal point), the accident date (three integers in the
** format of day/month/year, between 1/1/2012 and 1/8/2017), the accident time of day 
** (an integer between 0 and 23), and the accident day of week (a string in {"Monday", 
** "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}).
** 
** Task 1 was to write a program that reads the first line of the input data, and prints 
** out for the first record: the unique ID, the longitude, the latitude, the date, the time, 
** and the distance (in kilometres, 2 digits before and after decimal point) between the 
** accident location and a reference point with a coordinate of {144.963123, -37.810592}
** 
** Task 2 was to modify our program so that the distance to the reference point 
** {144.963123, -37.810592} for all of the input accident data are computed and visualised. 
** We assumed that the distance values are within the range of (0, 100). 
** On the same sample input data, the additional output for this stage should be:
** 
** Stage 2
** ==========
** Accident: #2693452, distance to reference: 08.57 |---------
** Accident: #2693453, distance to reference: 08.44 |---------
** Accident: #2693454, distance to reference: 04.46 |-----
** Accident: #2693455, distance to reference: 15.45 |---------+------
** Accident: #2693456, distance to reference: 30.37 |---------+---------+---------+-
** Accident: #2693458, distance to reference: 04.94 |-----
** Accident: #2693459, distance to reference: 22.05 |---------+---------+---
** Accident: #2693460, distance to reference: 28.94 |---------+---------+---------
** Accident: #2693461, distance to reference: 14.70 |---------+-----
** Accident: #2693462, distance to reference: 01.85 |--
** 
** Task 3 was to use strings to store the accident days. The additional output from this stage 
** is the total number of accident records, the day of week with the most accidents, and the 
** corresponding number of accidents on that day of week. In the case of ties, the day earlier 
** in the week should be output ("Monday" is considered the first day in a week and "Sunday" is
** considered the last day in a week).
*/

#define RECORDS_NEEDED 1
#define WHITE_SPACE ' '
#define COMMA ','
#define NEWLINE '\n'
#define LINES "==========\n"
#define NULL_BYTE '\0'
#define DASH '-'
#define PLUS '+'
#define MONDAY "Monday"
#define TUESDAY "Tuesday"
#define WEDNESDAY "Wednesday"
#define THURSDAY "Thursday"
#define FRIDAY "Friday"
#define SATURDAY "Saturday"
#define SUNDAY "Sunday"

/*Coordinates of Melbourne Central in terms of longitude and latitude*/
#define LONG_1 144.963123
#define LAT_1 -37.810592

/* Define (maximum) array sizes */
#define OUTPUT_LINES 100
#define MAX_LINE_LENGTH 55
#define ACCIDENT_ARRAY_SIZE 9
#define MAX_LOC_SIZE 25
#define MAX_DATE_SIZE 9
#define MAX_TIME_SIZE 3
#define MAX_DIST_TO_REF_SIZE 6
#define LONG_2_ARRAY_LENGTH 12
#define LAT_2_ARRAY_LENGTH 11
#define MAX_DIST 100
#define NO_OF_DAYS 7
#define MAX_DAY_LENGTH 10

/*Haversine formula parameters*/
#define TO_RAD_PARAMETERS 3.14159/180

typedef int type_t[NO_OF_DAYS+1];


char
get_file(char record[][MAX_LINE_LENGTH], int output_lines);

void
find_accident(char record_line[], int max_line_length);

void
find_loc(char record_line[], int max_line_length);

void
find_date(char record_line[], int max_line_length);

void
find_time(char record_line[], int max_line_length);

double
find_dist_to_ref(char record_line[], int max_line_length);

double
toRadian(double x);

type_t
fill_in_weekdays_count(char temporary_day_array[], int max_day_length); 

void
print_stage_1(char record[][MAX_LINE_LENGTH], int output_lines);

void 
print_stage_2(char record[][MAX_LINE_LENGTH], int output_lines);

void 
print_stage_3(char record[][MAX_LINE_LENGTH], int output_lines);

int
main(int argc, char *argv[]) {
	int output_lines;
	char record[OUTPUT_LINES][MAX_LINE_LENGTH];
	
	output_lines = get_file(record, OUTPUT_LINES);
	
	printf("Stage 1%c%s", NEWLINE, LINES);
	print_stage_1(record, output_lines);
	
	printf("Stage 2%c%s", NEWLINE, LINES);
	print_stage_2(record, output_lines);
	
	printf("Stage 3%c%s", NEWLINE, LINES);
	print_stage_3(record, output_lines);
	
	return 0;
}

char
get_file(char record[][MAX_LINE_LENGTH], int output_lines) {
	int i=0, j=0;
	char c;
	
	while ((c=getchar()) != EOF) {
		if (c == NEWLINE) {
			i += 1;
			j = 0;
		}
		else {
			record[i][j] = c;
			j += 1;
		}
	}
	return i;
}

void 
print_stage_1(char record[][MAX_LINE_LENGTH], int output_lines) {
	
	find_accident(record[0], MAX_LINE_LENGTH);
	printf("%c", NEWLINE);
	find_loc(record[0], MAX_LINE_LENGTH);
	find_date(record[0], MAX_LINE_LENGTH);
	find_time(record[0], MAX_LINE_LENGTH);
	printf("Distance to reference: %f%c", 
		find_dist_to_ref(record[0], MAX_LINE_LENGTH), NEWLINE);
	printf("%c", NEWLINE);
		
}

void 
print_stage_2(char record[][MAX_LINE_LENGTH], int output_lines) {
	char output[MAX_DIST];
	double dist;
	int count, i;
	
	for (i=0;i<output_lines;i++) {
		dist = find_dist_to_ref(record[i], MAX_LINE_LENGTH);
		
		for (count=0;count<dist;count++) {
			if (count%10 == 0 && count != 0) {
				output[count] = PLUS;
			}
			else {
				output[count] = DASH;
			}
		}
		
		output[count] = NULL_BYTE;
		
		find_accident(record[i], MAX_LINE_LENGTH);
		printf(", distance to reference: %f |%s%c", dist, output, NEWLINE);
	}
}

void 
print_stage_3(char record[][MAX_LINE_LENGTH], int output_lines) {
	int i, j, k, l, max, white_space;
	int weekdays_count[NO_OF_DAYS+1];
	char weekdays[NO_OF_DAYS+1][MAX_DAY_LENGTH] = {'0', MONDAY, TUESDAY, 
	WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};
	char temporary_day_array[MAX_DAY_LENGTH];
	
	for (i=0;i<output_lines;i++) {
		k = 0;
		for (j=0;j<MAX_LINE_LENGTH;j++) {
			if (record[i][j] == WHITE_SPACE) {
				white_space += 1;
			}
			
			if (white_space == 5) {
				temporary_day_array[k] = record[i][j];
				k += 1;
			}
		}
		
		temporary_day_array[k] = NULL_BYTE;
		weekdays_count = fill_in_weekdays_count(temporary_day_array, 
			MAX_DAY_LENGTH);
	}
	
	max = 1;
	for (l=2;l<NO_OF_DAYS+1;l++) {
		if (weekdays_count[l] > weekdays_count[max]) {
			max = l;
		} 
	}
	
	printf("Number of accidents: %d%c", output_lines, NEWLINE);
	printf("Day of week with the most accidents: %s (%d accident(s))",
		weekdays[max], weekdays_count[max]);
}

type_t
fill_in_weekdays_count(char temporary_day_array[], int max_day_length) {
	
	int weekdays_count[NO_OF_DAYS+1] = {0, 0, 0, 0, 0, 0, 0, 0};
		
	if (strcmp(MONDAY, temporary_day_array) == 0) {
		weekdays_count[1] += 1;
	}
	if (strcmp(TUESDAY, temporary_day_array) == 0) {
		weekdays_count[2] += 1;
	}
	if (strcmp(WEDNESDAY, temporary_day_array) == 0) {
		weekdays_count[3] += 1;
	}
	if (strcmp(THURSDAY, temporary_day_array) == 0) {
		weekdays_count[4] += 1;
	}
	if (strcmp(FRIDAY, temporary_day_array) == 0) {
		weekdays_count[5] += 1;
	}
	if (strcmp(SATURDAY, temporary_day_array) == 0) {
		weekdays_count[6] += 1;
	}
	if (strcmp(SUNDAY, temporary_day_array) == 0) {
		weekdays_count[7] += 1;
	}
	
	return weekdays_count; 
}



void
find_accident(char record_line[], int max_line_length) {
	char accident_num[ACCIDENT_ARRAY_SIZE];
	int i=0, white_space=0, count;
	
	for (count=0;count<max_line_length;count++) {
		if (record_line[count] == WHITE_SPACE) {
			white_space += 1;
		}
		if (record_line[count] != WHITE_SPACE && white_space == 0) {
			accident_num[i] = record_line[count];
			i += 1;
		}		
	}
	accident_num[i] = NULL_BYTE;
	
	printf("Accident: #%s", accident_num);

}

void
find_loc(char record_line[], int max_line_length) {
	char loc[MAX_LOC_SIZE];
	int i=0, white_space=0, count;
	
	for (count=0;count<max_line_length;count++) {
		if (record_line[count] == WHITE_SPACE && white_space != 1) {
			white_space += 1;
		}
		
		else if (record_line[count] == WHITE_SPACE && white_space == 1) {
			white_space += 1;
			loc[i] = COMMA;
			i += 1;
			loc[i] = WHITE_SPACE;
			i += 1;
		}
		
		if (record_line[count] != WHITE_SPACE && white_space == 1) {
			loc[i] = record_line[count];
			i += 1;
		}		
		
		if (record_line[count] != WHITE_SPACE && white_space == 2) {
			loc[i] = record_line[count];
			i += 1;
		}
	}
	
	loc[i] = NULL_BYTE;
	
	printf("Location: <%s>%c", loc, NEWLINE);

}

void
find_date(char record_line[], int max_line_length) {
	char date[MAX_DATE_SIZE];
	int i=0, white_space=0, count;
	
	for (count=0;count<max_line_length;count++) {
		if (record_line[count] == WHITE_SPACE) {
			white_space += 1;
		}
		if (record_line[count] != WHITE_SPACE && white_space == 3) {
			date[i] = record_line[count];
			i += 1;
		}		
	}
	date[i] = NULL_BYTE;
	
	printf("Date: %s%c", date, NEWLINE);
	
}

void
find_time(char record_line[], int max_line_length) {
	char time[MAX_TIME_SIZE];
	int i=0, white_space=0, count;
	
	for (count=0;count<max_line_length;count++) {
		if (record_line[count] == WHITE_SPACE) {
			white_space += 1;
		}
		if (record_line[count] != WHITE_SPACE && white_space == 4) {
			time[i] = record_line[count];
			i += 1;
		}		
	}
	time[i] = NULL_BYTE;
	                                                           
	printf("Time: %s%c", time, NEWLINE);
	
}

double
find_dist_to_ref(char record_line[], int max_line_length) {
	char long_2_array[LONG_2_ARRAY_LENGTH], lat_2_array[LAT_2_ARRAY_LENGTH]; 
	double angle_distance, chord_length, long_2, lat_2, dist;
	double lat_1_in_rad, lat_2_in_rad, lat_2_minus_lat_1_in_rad;
	double long_2_minus_long_1_in_rad; 
	int i=0, j=0, count, white_space=0; 
	
	for (count=0;count<max_line_length;count++) {
		if (record_line[count] == WHITE_SPACE) {
			white_space += 1;
		}
		if (record_line[count] != WHITE_SPACE && white_space == 1) {
			long_2_array[i] = record_line[count];
			i += 1;
		}
		
		if (record_line[count] != WHITE_SPACE && white_space == 2) {
			lat_2_array[j] = record_line[count];
			j += 1;
		}
		
	}
	long_2 = atof(long_2_array);
	lat_2 = atof(lat_2_array);
	
	lat_1_in_rad = toRadian(LAT_1);
	lat_2_in_rad = toRadian(lat_2);
	lat_2_minus_lat_1_in_rad = toRadian(lat_2 - LAT_1);
	long_2_minus_long_1_in_rad = toRadian(long_2 - LONG_1);
	
	chord_length = pow(sin(lat_2_minus_lat_1_in_rad/2), 2) + 
	cos(lat_1_in_rad)*cos(lat_2_in_rad)*
	pow(sin(long_2_minus_long_1_in_rad/2), 2);
	
	angle_distance = 2*atan2(sqrt(chord_length), sqrt(1-chord_length));
	dist = 6371*angle_distance;
	return dist;
	
}

double
toRadian(double x) {
	double y;
	y = x*TO_RAD_PARAMETERS;
	return y;
}
