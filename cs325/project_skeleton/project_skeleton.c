//BASIC FILE I/O: https://stackoverflow.com/questions/2372813/reading-one-line-at-a-time-in-c
//SPLITTING THE LINE: https://stackoverflow.com/questions/13652631/read-each-line-from-a-file-and-split-the-line-into-a-string-and-an-array-in-c
//DISTANCE CALCULATIONS: outlined in assignment directions 
//CONCATENATING STRINGS: https://stackoverflow.com/questions/308695/how-do-i-concatenate-const-literal-strings-in-c
//DYNAMICALLY ALLOCATE 2D ARRAY: https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
//TSP Algorithm: http://www.codingalpha.com/christofides-algorithm-c-program/ 

//Necessary libraries 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Function prototypes
int** read_input(char *filename, int *count, int *array_size);
int** resize_arrays(int **cities, int size);
void free_arrays(int **cities, int size);
int** adjacency_matrix(int **cities, int *matrix_size);
int find_distance(int xOne, int yOne, int xTwo, int yTwo);
int write_output(char *filename, int total, int *order, int size);





//Main function used to read and write the contents of a file
int main(int argc, char *argv[]) {

	int count = 0;
	int list_size = 10;
	int matrix_size = 0;
	int **raw_list;
	int **matrix;

	//Displays an error if the user hasn't provided a command line argument to be used as the input file
	if(argc != 2) {
		printf("Invalid number of arguments! Must also enter an input file to be read in\n"); 
		return 1;
	}

	//Transfers data from the input file to raw_list, then makes an adjacency matrix out of that info. More
	//details can be found in the individual functions
	else {
		raw_list = read_input(argv[1], &count, &list_size);
		matrix_size = count + 1;
		matrix = adjacency_matrix(raw_list, &matrix_size);
		free_arrays(raw_list, list_size);
	
//ONLY INCLUDED THIS BLOCK FOR TESTING PURPOSES; NOT SIGNIFICANT TO THE PROGRAM'S FUNCTION
int x;
int y;
for(x=0; x<matrix_size; x++) {
	for(y=0; y<matrix_size; y++) {
		printf("%d\t", matrix[y][x]); 
	}
	printf("\n");
}  	

//UNCOMMENT BELOW TO FREE matrix WHEN FINISHED WORKING WITH IT
//free_arrays(matrix, matrix_size);		


	}

	//Returns with no errors
	return 0;
}





//Function to read the file and split each line into the location, the x-coordinate, and the y-coordinate  
int** read_input(char *filename, int *count, int *list_size) {

	FILE *fin;
	int x;

	//Dynamically allocates a 2D array to store the location and x/y coordinates of the cities 
	int **cities = (int**)malloc(*list_size*sizeof(int*));
	for(x=0; x<*list_size; x++) {
		cities[x] = (int*)malloc(3*sizeof(int));
	}

	//Opens the file in read-only mode 
	fin = fopen(filename, "r");

	//If the file is valid, reads through them line-by-line, splitting each line into its three parts
	//and then transferring them to the dynamic array   
	if(fin != NULL) {
		char line[1000];
		char *piece; 
		
		//As long as the line is valid, print the line's contents 
		while(fgets(line, sizeof(line), fin) != NULL) {

			//Convert the location's number from a char to an int
  			piece = strtok(line, " ");
			int location = atoi(piece);	

			//Convert the location's x-coordinate from a char to an int
			piece = strtok(NULL, " ");
			int xCoord = atoi(piece);

			//Convert the location's y-coordinate from a char to an int
			piece = strtok(NULL, " ");
			int yCoord = atoi(piece);

			//Doubles the size of the array when necessary 
			if(location >= *list_size) {
				cities = resize_arrays(cities, *list_size);
				*list_size = *list_size * 2;
			}

			//Sets the first slot equal to the location, the second slot equal to the
			//x-coordinate, and the third slot equal to the y-coordinate 
			cities[location][0] = location;
			cities[location][1] = xCoord;
			cities[location][2] = yCoord; 
	
			//Keeps track of the number of cities (this may differ from the size of the array) 
			*count = *count + 1;
		}

		//Closes the file	
		fclose(fin);
	}

	//If the file was NULL, print out an error 
	else {
		printf("There was an error open the file '%s'", filename);
	}

	//Returns a 2D dynamically allocated array holding all locations and their coordinates
	return cities;
}





//Function to double the size of the dynamic array 
int** resize_arrays(int **cities, int size) {

	int x;

	//Allocates a new table double the size of the old one
	int **new_cities = (int**)malloc(size*2*sizeof(int*));
	for(x=0; x<size*2; x++) {
		new_cities[x] = (int*)malloc(3*sizeof(int)); 
	} 

	//Copies values from the old table over
	for(x=0; x<size; x++) {
		new_cities[x][0] = cities[x][0];
		new_cities[x][1] = cities[x][1];
		new_cities[x][2] = cities[x][2]; 
	}

	//Frees the old table
	free_arrays(cities, size);

	//Returns the new table
	return new_cities;
}





//Function to free the old table
void free_arrays(int **cities, int size) {
	int x;
	
	//Frees data in reverse-order from the way it was created
	for(x=0; x<size; x++) {
		free(cities[x]);
	} 

	//Frees the initial pointer and sets it to NULL 
	free(cities);
	cities = NULL;
}





//Function to create an adjacency matrix from the input info
int** adjacency_matrix(int **cities, int *matrix_size) {
	int x;
	int y;
	int cur_row;
	int cur_col;

	//Dynamically allocates an array to be used as an adjacency list
	int **matrix = (int**)malloc(*matrix_size*sizeof(int*));
	for(x=0; x<*matrix_size; x++) {
		matrix[x] = (int*)malloc(*matrix_size*sizeof(int));
	}

	//Sets the top left corner to 0. Not particularly important, just looks better when the matrix is printed out
	matrix[0][0] = 0;

	//Numbers the first column from 1 to n (used to keep track of which city is being referred to)
	for(x=1; x<*matrix_size; x++) {
		matrix[x][0] = x-1;
	}


	//Numbers the first row from 1 to n (used to keep track of which city is being referred to) 
	for(x=1; x<*matrix_size; x++) {
		matrix[0][x] = x-1;
	}  	

	//Iterates through the matrix slot-by-slot calculating the distance between the column and row. If the column and the row are the same,
	//will leave a weight of infinity  
	for(x=1; x<*matrix_size; x++) {
		for(y=1; y<*matrix_size; y++) {
			cur_row = matrix[0][x];
			cur_col = matrix[y][0]; 	
			matrix[y][x] = find_distance(cities[cur_row][1], cities[cur_row][2], cities[cur_col][1], cities[cur_col][2]);
		}
	}

	//Returns the dynamically allocated adjacency matrix
	return matrix;
}




 
//Function to calculate the distance between two locations to the nearest int
int find_distance(int xOne, int yOne, int xTwo, int yTwo) {

	//Squares the results of xOne - xTwo and yOne - yTwo, adds them, finds the square root, and then rounds appropriately.
	//Also threw in an absolute value clause here (wasn't positive this would be necessary, just in case)   
	int result = (int) fabs(round(pow(pow((xOne - xTwo), 2) + pow((yOne - yTwo), 2), 0.5))); 
	
	//If the edge has no weight, then we have calculate the distance from a point to itself. Set the value to infinity rather 
	//than 0 (or some other recognizable number) so it won't be chosen when making greedy choices, etc.  
	if(result == 0) {
//		result = INFINITY;
		result = 777;
	} 

	//Return the distance between the parameter points as a rounded int 
	return result;
}





//Function to open the output file and write to it
int write_output(char *filename, int total, int *order, int size) {

	FILE *fout;
	int x;

	//Concatenates the '.tour' to the end of the original file's name 	
	strncat(filename, ".tour", 6);

	//Opens the file in write-only mode	
	fout = fopen(filename, "w");

	//If the file is valid, writes to it line-by-line
	if(fout != NULL) {
		
		//Writes the total distance on the first line
		fprintf(fout, "%d\n", total);

		//Loops through the array holding the (near) optimal order , writing the order to the file
		for(x=0; x<size; x++) {
			fprintf(fout, "%d\n", order[x]);
		} 	
	}

	//If there was an error, let the user know
	else {
		printf("There was an error open the file '%s'", filename);
	}

	return 0;  
}
