#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv)
{	
	srand(time(NULL));
	int **map , **musk;	
	int i =1,j=0,edge = atoi(argv[2]);
	//edge is aplitude for map and musk
	map = (int **)malloc(edge*sizeof(int *));
	musk = (int **)malloc(edge*sizeof(int *));
	for(i=0;i<edge;i++)
	{
		map[i] = (int *)malloc(edge *sizeof(int));
		musk[i] = (int *)malloc(edge *sizeof(int));
	}
	for(i=0;i<edge;i++)
		for(j=0;j<edge;j++)
		{
			map[i][j] = 0;
			musk[i][j] = 0;
		}
	musk[edge/2][edge/2] =1;
	map[edge/2][edge/2] =1;
	//initialize  --- a particle at the center of musk and map as "seed"
	int con = 0;
	char CAYSM  =0 ;//call symbol , used to determine where to generate the particle
	while(con++ < atoi(argv[1]))
	{
		//gennerating
		if(con!=0)
		{
		int pos = rand();
		pos = pos%(edge-2);
		switch(CAYSM)
		{
				case 0:
					map[pos+1][1]=1;
					printf("gen:[%d,%d]\n",pos+1,1);
				break;
				case 1:
					map[pos+1][edge-2] =1;
					printf("gen:[%d,%d]\n",pos+1,edge-2);
				break;
				case 2:
					map[edge-2][pos+1] =1;
					printf("gen:[%d,%d]\n",edge-2,pos+1);
				break;
				case 3:
					map[1][pos+1] = 1;
					printf("gen:[%d,%d]\n",1,pos+1);
				break;				
			}	
			CAYSM ++;
			if(CAYSM == 4)
				CAYSM = 0;
		}
		//evolution
		int x,y,n_x,n_y,sym;
		for(i=0;i<edge;i++)
		{
			for(j=0;j<edge;j++)
			{
				n_x = rand()%2*2-1;
				n_y = rand()%2*2-1;
				if(!musk[i][j]&&map[i][j])//move
				{
					if((i+n_x)<edge && (i+n_x)>=0)
						x = i+n_x;
					else if(i+n_x >= edge-1 || i+n_x < 0)
						x = i-n_x;
					if((j+n_y)<edge && (j+n_y)>=0)
						y = j+n_y;
					else if(j+n_y < 0 || j+n_y >= edge-1)
						y = j-n_y;
			
					//check if was at center
			
					if(x<edge-1 && x>1 && y<edge-1 && y>1 )
					{
						sym  = musk[x-1][y]+musk[x-1][y-1]+musk[x-1][y+1]+musk[x][y-1]+musk[x][y+1]+musk[x+1][y]+musk[x+1][y+1]+musk[x+1][y-1];
						if(sym)
						{
							musk[x][y] = 1; 
							printf("%d step %d,%dwas setted\n",con,x,y);
							
						}

					}
					map[i][j] = 0;
					map[x][y] = 1;
			   }		

			}
		}

	}
	FILE *fp = fopen("dla.rec","w");
	for(i=0;i<edge;i++)
			for(j=0;j<edge;j++)
					if(musk[i][j])
							fprintf(fp,"%d\t%d\n",i,j);
	fclose(fp);
	for(i=0;i<edge;i++)
	{
		free(map[i]);
		free(musk[i]);
	}
	free(map);
	free(musk);
}
