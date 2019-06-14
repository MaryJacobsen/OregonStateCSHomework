/* CS261- Assignment 1 - Q.5*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
	int i=1;
	if(word[0] < 123 && word[0] > 96){
		word[0] = toUpperCase(word[0]);
	}
	while(word[i] != '\0'){
		if(word[i-1] < 123 && word[i-1] > 96){
			if(word[i] < 123 && word[i] > 96){
				word[i] = toUpperCase(word[i]);
			}
		}
		else{
			if(word[i] > 64 && word[i] < 91){
				word[i] = toLowerCase(word[i]);
			}
		}
		i++;
	}
}

int main(){
    /*Read word from the keyboard using scanf*/
	char *word = malloc(sizeof(char)*20);
	printf("Enter a word\n");
	scanf("%s", word);

    /*Call sticky*/
	sticky(word);
    
    /*Print the new word*/
	printf("%s\n", word);
    
    return 0;
}
