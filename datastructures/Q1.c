/***************************************************************
** CS261- Assignment 1 - Q.1
** Name: Mary Jacobsen
** Date: 7/2/16
** Solution description: Allocated memory for 10 students, gave
** the 10 students 10 unique random IDs and random scores,
** printed out the scores in order of IDs, computed the lowest,
** highest, and average of the 10 scores, freed the memory
***************************************************************/
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

/***************************************************************
** Function: allocate
** Description: allocates memory for 10 students
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns a pointer to struct student
***************************************************************/
struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student* students;
	students = malloc(sizeof(struct student) * 10);
     
     /*return the pointer*/
	return students;
}

/***************************************************************
** Function: generate
** Description: generates random and unique ID and scores for ten
** students, ID being between 1 and 10, scores between 0 and 100
** Parameters: pointer to a struct student
** Pre-Conditions: the array of students must have 10 students
** Post-Conditions: the students have IDs and scores
***************************************************************/
void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	int i, num;
    srand(time(NULL));
    for(i=0; i<10; i++){
    	students[i].id = 0;
    }
    for(i=1; i<11; i++){
    	num = rand()%10;
    	if(students[num].id == 0){
    		students[num].id = i;
    	}
    	else{
    		i = i-1;
    	}
    }
    for(i=0; i<10; i++){
    	students[i].score = rand()%101;
    }
}

/***************************************************************
** Function: output
** Description: outputs information about the ten students
** Parameters: pointer to a struct student
** Pre-Conditions: the array of students must have 10 students
** Post-Conditions: none
***************************************************************/
void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	int j, k;
	for(j=1; j<11; j++){
		for(k=0; k<10; k++){
			if(students[k].id == j){
				printf("ID%d %d\n", students[k].id, students[k].score);
			}
		}
	}

}

/***************************************************************
** Function: summary
** Description: computes and print the minimum, maximum and
** average scores of the ten students
** Parameters: pointer to a struct student
** Pre-Conditions: the array of students must have 10 students
** Post-Conditions: none
***************************************************************/
void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int i, min = 0, max = 0, avg = 0;
	for(i=0; i<10; i++){
		if(students[min].score > students[i].score){
			min = i;
		}
	}
	printf("Minimum score: %d\n", students[min].score);
    for(i=0; i<10; i++){
    	if(students[max].score < students[i].score){
    		max = i;
    	}
    }
    printf("Maximum score: %d\n", students[max].score);
    for(i=0; i<10; i++){
    	avg = avg + students[i].score;
    }
    avg = avg/10;
    printf("Average score: %d\n", avg);
}

/***************************************************************
** Function: deallocate
** Description: deallocates memory from stud
** Parameters: pointer to a struct student
** Pre-Conditions: none
** Post-Conditions: the memory of what is passed in is freed
***************************************************************/
void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	free(stud);
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    
    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);
    
    /*call summary*/
    summary(stud);
    
    /*call deallocate*/
    deallocate(stud);

    return 0;
}
