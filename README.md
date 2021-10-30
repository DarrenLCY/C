# C
Repo for sample C codes

Code from "Engineering Computation" assignment completed at the 
University of Melbourne. In this assignment, my task was to analyse 
the spatial and temporal distributions of traffic accidents. We
were given a list of traffic accident records like the one shown below:
 
2693452 145.060689 -37.810373 26/5/12 11 Saturday
2693453 144.991172 -37.883156 6/6/12 15 Wednesday
2693454 145.009458 -37.826952 24/5/12 09 Thursday
2693455 145.134597 -37.841545 6/6/12 17 Wednesday

Particularly, each line of the list contains the information of a traffic 
accident separated by spaces (' '), including the unique ID (a 7-digit
integer), the accident location longitude (a real number with 6 digits 
after the decimal point), the accident location latitude (a real number 
with 6 digits after the decimal point), the accident date (three integers in the
format of day/month/year, between 1/1/2012 and 1/8/2017), the accident time of day 
(an integer between 0 and 23), and the accident day of week (a string in {"Monday", 
"Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}).
 
Task 1 was to write a program that reads the first line of the input data, and prints 
out for the first record: the unique ID, the longitude, the latitude, the date, the time, 
and the distance (in kilometres, 2 digits before and after decimal point) between the 
accident location and a reference point with a coordinate of {144.963123, -37.810592}
 
Task 2 was to modify our program so that the distance to the reference point 
{144.963123, -37.810592} for all of the input accident data are computed and visualised. 
We assumed that the distance values are within the range of (0, 100). 
On the same sample input data, the additional output for this stage should be:

Stage 2

Accident: #2693452, distance to reference: 08.57 |---------  
Accident: #2693453, distance to reference: 08.44 |---------  
Accident: #2693454, distance to reference: 04.46 |-----
Accident: #2693455, distance to reference: 15.45 |---------+------
Accident: #2693456, distance to reference: 30.37 |---------+---------+---------+-
Accident: #2693458, distance to reference: 04.94 |-----
Accident: #2693459, distance to reference: 22.05 |---------+---------+---
Accident: #2693460, distance to reference: 28.94 |---------+---------+---------
Accident: #2693461, distance to reference: 14.70 |---------+-----
Accident: #2693462, distance to reference: 01.85 |--

Task 3 was to use strings to store the accident days. The additional output from this stage 
is the total number of accident records, the day of week with the most accidents, and the 
corresponding number of accidents on that day of week. In the case of ties, the day earlier 
in the week should be output ("Monday" is considered the first day in a week and "Sunday" is
considered the last day in a week).
