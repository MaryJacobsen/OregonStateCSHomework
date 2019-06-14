#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct AdjacencyList {
	int degree;
	int connections[6];
};

int distance(int c1, int c2) {
	//add 1 and 1, 3 and 3,... ect

   	if((c1==1 && c2==3) || (c1==3 && c2==1))
	   	return 27;

	if((c1==1 && c2==5) || (c1==5 && c2==1))
	   	return 30;

	if((c1==3 && c2==5) || (c1==5 && c2==3))
	   	return 12;

	if((c1==1 && c2==0) || (c1==0 && c2==1))
	   	return 32;


	if((c1==0 && c2==5) || (c1==5 && c2==0))
	   	return 20;


	if((c1==0 && c2==3) || (c1==3 && c2==0))
	   	return 19;
}

int main() {
	
	struct AdjacencyList test[6];
	test[0].degree = 3;
	test[0].connections[0] = 1;
	test[0].connections[1] = 2;
	test[0].connections[2] = 3;

	test[1].degree = 1;
	test[1].connections[0] = 0;

	test[2].degree = 2;
	test[2].connections[0] = 0;
	test[2].connections[1] = 4;
	
	test[3].degree = 3;
	test[3].connections[0] = 0;	
	test[3].connections[1] = 4;
	test[3].connections[2] = 5;

	test[4].degree = 2;
	test[4].connections[0] = 3;
	test[4].connections[1] = 2;

	test[5].degree = 1;
	test[5].connections[0] = 3;


	//print hopefully an MST
	int a, b;
	for(a=0; a<6; a++)
	{
		for(b=0; b<test[a].degree; b++)
		{
		   	printf("%d ", test[a].connections[b]);
	
		}
		printf(" \n");
	}
	printf("\n\n");
	
/***************************************************************************
This is the important section.
***************************************************************************/
	//check for odd degree
	//and if odd, add to odd array
	int odd[6];
	int used[6];
	int oddCount = 0;
	int usedCount = 0;
	int i, j, length, closest;
	int U = 0; //flag for used odds

	//fill the odd array
	for(i=0; i<6; i++)
	{
		if(test[i].degree % 2){
			odd[oddCount] = i;
			oddCount++;
		}
	}

	for(i=0; i<oddCount; i++)
	{
	   	printf("%d ", odd[i]);
	}
	printf("\n\n");
	

	//perfect matching
	for(i=0; i<oddCount; i++)
	{
	   	for(a=0; a<usedCount; a++)
		{
			if(used[a]==i){
				U = 1;
			}
		}

		if(U==0){
	   		length = 5000;
			for(j=0; j<oddCount; j++)
			{
		   		//access matrix right here to get weight
				if(distance(odd[i],odd[j]) < length){
				   	//printf("%d\n",distance(i,j));
		   			for(a=0; a<usedCount; a++)
					{
						if(used[a]==j){
							U = 1;
						}
					}
					if(U==0){
				   		length = distance(odd[i],odd[j]);
		     				closest = j;
						used[usedCount] = j;
			       			usedCount++;
						used[usedCount] = i;
						usedCount++;
					}
					U = 0;	
				}
				printf("\n\n%d\n\n",odd[closest]);
			}	
			//add the edge
			test[i].connections[test[i].degree] = odd[closest];
			test[closest].connections[test[closest].degree] = odd[i];
			test[i].degree++;
			test[closest].degree++;
		}
		U=0;
	}

/**************************************************************************

**************************************************************************/

	//print with added edges (perfect matching)
	for(a=0; a<6; a++)
	{
		for(b=0; b<test[a].degree; b++)
		{
		   	printf("%d ", test[a].connections[b]);
	
		}
		printf(" \n");
	}
	printf("\n\n");
	


return 0;
}

