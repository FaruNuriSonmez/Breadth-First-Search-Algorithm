#include <stdio.h>
#include <stdlib.h>
#define N 5 /* !!!!!! Düğüm sayısı burada elle değiştirilmeli. !!!!!*/
int n,m;
int cal[100],indis=0;
struct Queue
{
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*) malloc(queue->capacity * sizeof(int));
    return queue;
}

struct Node {
	int dest,distance;
	struct Node* next;
};

struct Edge {
	int src, dest, distance;
};

struct Graph {
	struct Node* head[N];
};


// adjacency list oluşturuyor
struct Graph* createGraph(struct Edge edges[], int n)
{
	unsigned i;

	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

	for (i = 0; i < n; i++)
		graph->head[i] = NULL;

	for (i = 0; i < m; i++)
	{
		int src = edges[i].src;
		int dest = edges[i].dest;
		int dist = edges[i].distance;

		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = dest;
		newNode->distance = dist;

		newNode->next = graph->head[src];


		graph->head[src] = newNode;
	}

	return graph;
}

// adjacency list yazdırıyor
int printGraph(struct Graph* graph)
{
	int i,max,neighboor;
	max = 0;
	printf("\n");
	for (i = 0; i < N; i++)
	{
	    printf("%d | ",i);
		struct Node* ptr = graph->head[i];
		neighboor = 0;
		while (ptr != NULL)
		{
			printf("(%d -> %d) distance:%d ",i, ptr->dest,ptr->distance);
			ptr = ptr->next;
			neighboor++;
		}
        if(neighboor > max)
            max = neighboor;
		printf("\n");
	}
	return max;
}

void BFS(struct Graph* graph,int source,int dest){
    int marked[N],prior[N];
    int i,curr;
    for(i=0;i<N;i++){
        marked[i] = prior[i] = -1;
    }
    struct Queue* queue = createQueue(1000);
    marked[source] = 1; //visited
    enqueue(queue,source);
    i = 0;
    while(isEmpty(queue) != 0){
        curr = dequeue(queue);
        if(curr == dest){
            printf("\npath is : ");
            printPath(graph,prior,dest,0);
            printf("\nMinimum Distance beetwen %d and %d is %d\n",source,dest,calcu(graph,cal,source,0));
        }
        struct Node* ptr = graph->head[curr];
            while (ptr != NULL)
            {
                if(marked[ptr->dest] == -1){
                    marked[ptr->dest] = 1;
                    enqueue(queue,ptr->dest);
                    prior[ptr->dest] = curr;

                }
                ptr = ptr->next;
            }
            i++;
    }

}

//en kısa yolu yazdırıyor
int printPath(struct Graph* graph,int prior[],int v,int dist){
    int cost;
    cal[indis] = v;
    indis++;
    if(v >= 0){
        cost = printPath(graph,prior,prior[v],dist);
        struct Node* ptr = graph->head[v];
        if(v < N){
            printf("%d ",v);

        }

    }
    return dist;
}
// source ve dest dugumlerı arasındakı mesafeyı hesaplıyor
int calcu(struct Graph* graph,int cal[],int v,int dist){
    indis = indis - 2;
    while(indis >= 1){
        struct Node* ptr = graph->head[cal[indis]];
        while(ptr->dest != cal[indis-1]){
            ptr = ptr->next;
        }
        dist = dist + ptr->distance;
        indis--;
    }

return dist;
}

// kuyruk dolu mu kontrolu
int isFull(struct Queue* queue)
{  return (queue->size == queue->capacity);  }

// kuyruk bos mu kontrolu
int isEmpty(struct Queue* queue)
{
    if(queue->size == 0)
        return 0;
}

//kuyruğa eleman eklıyor
void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)%queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    //printf("%d enqueued to queue\n", item);
}

/*
kuyruktan eleman siliyor
*/
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue) == 0)
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)%queue->capacity;
    queue->size = queue->size - 1;
    //printf("%d dequeued to queue\n", item);
    return item;
}

int main(){
    FILE *fp;
    int inf[100];
    int i,j,source,dest;
    int max;
    fp = fopen("Graf2.txt","r");
    if(fp == NULL)
        printf("File couldn't open.");
    i = 0;
    while(!feof(fp)){
        fscanf(fp,"%d",&inf[i]); /* dosyadan bir kelime okuyalim */
        i++;
    }
    n = inf[0]; // düðüm sayýsý
    m = inf[1]; // baðlantý sayýsý
    source = inf[2]; // baþlangýç düðümü
    dest = inf[3]; // varýþ düðümü
    printf("n=%d m=%d source=%d dest=%d\n",n,m,source,dest);
    struct Edge edges[m*3];
    j = 0;
    for(i=4;i<m*3+4;i=i+3){
        edges[j].src = inf[i];
        edges[j].dest = inf[i+1];
        edges[j].distance = inf[i+2];
        printf("%d %d %d ",edges[j].src,edges[j].dest,edges[j].distance);
        j++;
    }

    struct Graph *graph = createGraph(edges, n);

	max = printGraph(graph);
    printf("\n\n\n");
    BFS(graph,source,dest);
    printf("\nMaximum neigboor count is :%d\n",max);
    return 0;
}
