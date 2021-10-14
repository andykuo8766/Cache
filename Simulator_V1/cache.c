#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define STRLEN      80
enum { FIFO = 0, LRU = 1 };
enum { DATA_READ = 0, DATA_WRITE = 1, INSTRUCTION_FETCH = 2 };
#define FULLY_ASSOCIATIVE 0

unsigned int Cache_hit, Cache_miss, Read_data, Write_data;
unsigned int nWrite_back, nRead_block;

double logbase(double a, double base)
{
	return log(a) / log(base);
}

int _str_to_long(char *str, unsigned int* p_val, unsigned char base)
{
	char*     p;
	long int  val;

	base = (base == 8 || base == 10 || base == 16 || base == 32) ? base : 0;
	//	if (strncmp(str, "ffffffff", 8)==0){  //strtol() return 0x7fffffff
	//		printf("%s\n",p_val);
	//	}

	val = strtol(str, &p, base);

	if (*p == '\0') {
		*p_val = val;
		return 1;
	}

	return 0;
}


typedef struct QNode
{
	struct QNode *prev, *next;
	unsigned int tagNumber;
	unsigned int dirty;
} QNode;

typedef struct Queue
{
	unsigned int count;
	unsigned int numberOfFrames;
	QNode *front, *rear;
} Queue;

typedef struct Hash
{
	int capacity;
	Queue **array;
} Hash;

QNode* newQNode(unsigned int tagNumber)
{
	QNode* temp = (QNode *)malloc(sizeof(QNode));
	temp->tagNumber = tagNumber;
	temp->dirty = 0;
	temp->prev = temp->next = NULL;
	return temp;
}

Queue* createQueue(int numberOfFrames)
{
	Queue* queue = (Queue *)malloc(sizeof(Queue));
	queue->count = 0;
	queue->front = queue->rear = NULL;
	queue->numberOfFrames = numberOfFrames;

	return queue;
}


Hash* createHash(int capacity)
{
	Hash* hash = (Hash *)malloc(sizeof(Hash));
	hash->capacity = capacity;
	hash->array = (Queue **)malloc(hash->capacity * sizeof(Queue*));
	int i;
	for (i = 0; i < hash->capacity; ++i)
		hash->array[i] = NULL;

	return hash;
}

int AreAllFramesFull(Queue* queue)
{
	return queue->count == queue->numberOfFrames;
}

QNode* SearchTagInQueue(Queue* queue, unsigned int tagNumber)
{
	QNode *SearchTag;
	if (queue->count == 0)
		return NULL;
	else {
		SearchTag = queue->front;
		while (SearchTag != NULL) {
			if (SearchTag->tagNumber == tagNumber)
				break;
			else
				SearchTag = SearchTag->next;
		}
	}
	return SearchTag;

}

int isQueueEmpty(Queue* queue)
{
	return queue->rear == NULL;
}

void deQueue(Queue* queue)
{
	if (isQueueEmpty(queue))
		return;

	if (queue->front == queue->rear)
		queue->front = NULL;

	QNode* temp = queue->rear;
	queue->rear = queue->rear->prev;

	if (queue->rear)
		queue->rear->next = NULL;
	if (temp->dirty)
		nWrite_back++;
	free(temp);

	queue->count--;
}

void Enqueue(Queue* queue, Hash* hash, unsigned int tagNumber, unsigned int RW)
{

	if (AreAllFramesFull(queue))
	{
		//hash->array[ queue->rear->tagNumber ] = NULL;
		deQueue(queue);
	}

	QNode* temp = newQNode(tagNumber);
	nRead_block++;
	if (RW == DATA_WRITE)
		temp->dirty = 1;
	temp->next = queue->front;

	if (isQueueEmpty(queue))
		queue->rear = queue->front = temp;
	else
	{
		queue->front->prev = temp;
		queue->front = temp;
	}
	queue->count++;

}

void ReadWriteTag(Hash* hash, unsigned int index, unsigned int tagNumber, unsigned int RW, unsigned int replace_policy)
{
	Queue* queue = hash->array[index];
	QNode* reqTag;

	reqTag = SearchTagInQueue(queue, tagNumber);

	if (reqTag == NULL)
		Cache_miss++;
	else {
		Cache_hit++;
		if (RW == DATA_WRITE)
			reqTag->dirty = 1;
	}

	if (reqTag == NULL)
	{
		Enqueue(queue, hash, tagNumber, RW);
	}
	else if (reqTag != queue->front && replace_policy == LRU) //move node to front
	{
		reqTag->prev->next = reqTag->next;
		if (reqTag->next)
			reqTag->next->prev = reqTag->prev;
		if (reqTag == queue->rear)
		{
			queue->rear = reqTag->prev;
			queue->rear->next = NULL;
		}
		reqTag->next = queue->front;
		reqTag->prev = NULL;
		reqTag->next->prev = reqTag;

		queue->front = reqTag;
	}
}

void printfoutQueue(Queue* queue)
{
	QNode *tmp = queue->front;
	printf("queue->count/numberOfFrames = %d/%d =>", queue->count, queue->numberOfFrames);
	while (tmp != NULL) {
		printf("%d ", tmp->tagNumber);
		tmp = tmp->next;
	}
	printf("\n");
}

int main(int argc, char* argv[])//////////////////////////////////////////////////////////////////////////////////
{
	unsigned int cache_size, block_size, associativity, replace_policy;
	unsigned int tag, index, block;
	unsigned int ntag_bits, nindex_bits, nblock_bits;

	FILE *inputf;
	char inputline[STRLEN];
	char *ptr;
	char * pch;
	char *next_token = NULL;
	int ret;
	unsigned int type, address;

	unsigned int index_size;
	Hash* hash;
	QNode *tmp;
	int i;

	if (argc != 6) {
		printf("Please use:\n cache 8 32 1 FIFO gcc.din \n");
		exit(1);
	}

#if 0
	for (i = 0; i < argc; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
	printf("\n");
#endif
	ret = _str_to_long(argv[1], &cache_size, 10);
	cache_size = cache_size * 1024;
	if (!ret) { printf("ret = %d\n", ret); printf("errno = %d\n", errno); printf("cache_size = %x\n", cache_size); }
	ret = _str_to_long(argv[2], &block_size, 10);
	if (!ret) { printf("ret = %d\n", ret); printf("errno = %d\n", errno); printf("block_size = %x\n", block_size); }
	if (strncmp(argv[3], "f", 1) == 0)
		associativity = FULLY_ASSOCIATIVE;
	else {
		ret = _str_to_long(argv[3], &associativity, 10);
		if (!ret) { printf("ret = %d\n", ret); printf("errno = %d\n", errno); printf("associativity = %x\n", associativity); }
	}
	if (strncmp(argv[4], "FIFO", 4) == 0)
		replace_policy = FIFO;
	else
		replace_policy = LRU;
	if (associativity == FULLY_ASSOCIATIVE) {
		index_size = 0;
		nblock_bits = logbase(block_size, 2);
		nindex_bits = 0;
		ntag_bits = 32 - (nindex_bits + nblock_bits);
	}
	else {
		index_size = cache_size / block_size / associativity;
		nblock_bits = logbase(block_size, 2);
		nindex_bits = logbase(index_size, 2);
		ntag_bits = 32 - (nindex_bits + nblock_bits);
	}
#if 0
	printf("cache_size = %d\n", cache_size);
	printf("block_size = %d\n", block_size);
	printf("associativity = %d\n", associativity);
	printf("replace_policy = %d\n", replace_policy);
	printf("index_size = %d\n", index_size);
	printf("field bits %d %d %d\n", ntag_bits, nindex_bits, nblock_bits);
#endif

	if (associativity == FULLY_ASSOCIATIVE)
	{
		hash = createHash(1);
		hash->array[0] = createQueue(cache_size / block_size);
	}
	else
	{
		hash = createHash(index_size);
		for (i = 0; i < index_size; i++)
			hash->array[i] = createQueue(associativity);
	}

	inputf = fopen(argv[5], "r");
	if (inputf == NULL) { printf("Read file cannot open!!\n"); exit(1); }
	while ((ptr = fgets(inputline, STRLEN, inputf)) != NULL) {
		pch = strtok_s(inputline, " ,.-\n", &next_token);
		//printf("%s\n", pch);
		//	ret = from_string<int>(price, pch, dec);
		ret = _str_to_long(pch, &type, 16);
		if (!ret) { printf("ret = %d\n", ret); printf("errno = %d\n", errno); printf("type = %x\n", type); }

		pch = strtok_s(NULL, " ,.-\n", &next_token);
		//printf("%s\n", pch);
		if (strncmp(pch, "ffffffff", 8) == 0)
			continue;
		ret = _str_to_long(pch, &address, 16);
		if (!ret) { printf("ret = %d\n", ret); printf("errno = %d\n", errno); printf("type = %x\n", address); }

		//printf("%d %x\n",type,address);
		tag = address >> (nindex_bits + nblock_bits);
		if (associativity == FULLY_ASSOCIATIVE)
			index = 0;
		else
			index = (address << ntag_bits) >> (ntag_bits + nblock_bits);
		block = address & ((unsigned int)-1 >> (31 - nblock_bits));
		//printf("address = 0x%08x\n",address);
		//printf("%x %x %x\n",tag,index,block);
		switch (type)
		{
		case DATA_READ:
			Read_data++;
			ReadWriteTag(hash, index, tag, DATA_READ, replace_policy);
			break;
		case DATA_WRITE:
			Write_data++;
			ReadWriteTag(hash, index, tag, DATA_WRITE, replace_policy);
			break;
		case INSTRUCTION_FETCH:
			ReadWriteTag(hash, index, tag, DATA_READ, replace_policy);
			break;
		default:
			printf("type error !! type = %d\n", type);
		}

	}

	//flush dirty block
	if (associativity == FULLY_ASSOCIATIVE) {
		QNode *tmp;
		tmp = hash->array[0]->front;
		while (tmp != NULL) {
			if (tmp->dirty == 1)
				++nWrite_back;
			tmp = tmp->next;
		}
	}
	else {
		for (i = 0; i < index_size; i++) {
			QNode *tmp;
			tmp = hash->array[i]->front;
			while (tmp != NULL) {
				if (tmp->dirty == 1)
					++nWrite_back;
				tmp = tmp->next;
			}
		}
	}


	printf("Input file = %s\n", argv[5]);
	printf("Demand fetch = %d\n", Cache_hit + Cache_miss);
	printf("Cache hit = %d\n", Cache_hit);
	printf("Cache miss = %d\n", Cache_miss);
	printf("Miss rate = %.4f\n", (float)Cache_miss / (Cache_hit + Cache_miss));
	printf("Read data = %d\n", Read_data);
	printf("Write data = %d\n", Write_data);
	printf("Bytes from Memory = %d\n", nRead_block*block_size);
	printf("Byte to memory = %d\n", nWrite_back*block_size);

	//	system("pause");

}

























/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int main(int argc, char *argv[]) {
//argv[0] = cache
//argv[1] = cache_size
//argv[2] = block_size
//argv[3] = associativity
//argv[4] = replace_policy
//argv[5] = file


int main(){
	int label = 0;
	int read_data = 0;
	int write_data = 0;
	int countfetch = 0;
	char *pch;
	char *delim = " ";
	char c;
	char line[10000];
	char cache[10];
	char cache_size[10];
	char block_size[10];
	char associativity[10];
	char replace_policy[10];
	char file[1000];

	FILE *pFile;
	char buffer[1024];





	//scanf("%s", cache_size);
	//scanf("%s", block_size);
	//scanf("%s", associativity);
	//scanf("%s", replace_policy);
	scanf("%s", file);



	pFile = fopen(file, "r");
	if (NULL == pFile) {
		printf("Open failure");
		return 1;
	}
	while (fgets(line, 1000,pFile) != EOF) {
		countfetch++;
		pch = strtok(line, delim);
		label = atoi(pch);
		if (label == 0) {
			read_data++;
		}
		else if (label == 1) {
			write_data++;
		}
		else if (label == 2) {

		}
	}

	fclose(pFile);



	printf("\n\n");
	printf("Input file = %s\n", file);
	printf("Demand fetch = %d\n", countfetch);
	printf("Cache hit = \n");
	printf("Cache miss = \n");
	printf("Read data = %d\n", read_data);
	printf("Write data = %d\n", write_data);
	printf("Bytes from memory = \n");
	printf("Bytes to memory = \n");


	system("pause");
}


/*
#include <stdio.h>
#include <stdlib.h>


typedef struct QNode
{
	struct QNode *prev, *next;
	unsigned pageNumber;
} QNode;

typedef struct Queue
{
	unsigned count;
	unsigned numberOfFrames;
	QNode *front, *rear;
} Queue;

typedef struct Hash
{
	int capacity;
	QNode* *array;
} Hash;

QNode* newQNode(unsigned pageNumber)
{
	QNode* temp = (QNode *)malloc(sizeof(QNode));
	temp->pageNumber = pageNumber;
	temp->prev = temp->next = NULL;
	return temp;
}

Queue* createQueue(int numberOfFrames)
{
	Queue* queue = (Queue *)malloc(sizeof(Queue));
	queue->count = 0;
	queue->front = queue->rear = NULL;
	queue->numberOfFrames = numberOfFrames;

	return queue;
}


Hash* createHash(int capacity)
{
	Hash* hash = (Hash *)malloc(sizeof(Hash));
	hash->capacity = capacity;
	hash->array = (QNode **)malloc(hash->capacity * sizeof(QNode*));
	int i;
	for (i = 0; i < hash->capacity; ++i)
		hash->array[i] = NULL;

	return hash;
}

int AreAllFramesFull(Queue* queue)
{
	return queue->count == queue->numberOfFrames;
}


int isQueueEmpty(Queue* queue)
{
	return queue->rear == NULL;
}

void deQueue(Queue* queue)
{
	if (isQueueEmpty(queue))
		return;

	if (queue->front == queue->rear)
		queue->front = NULL;

	QNode* temp = queue->rear;
	queue->rear = queue->rear->prev;

	if (queue->rear)
		queue->rear->next = NULL;

	free(temp);

	queue->count--;
}

void Enqueue(Queue* queue, Hash* hash, unsigned pageNumber)
{

	if (AreAllFramesFull(queue))
	{
		hash->array[queue->rear->pageNumber] = NULL;
		deQueue(queue);
	}

	QNode* temp = newQNode(pageNumber);
	temp->next = queue->front;

	if (isQueueEmpty(queue))
		queue->rear = queue->front = temp;
	else
	{
		queue->front->prev = temp;
		queue->front = temp;
	}

	hash->array[pageNumber] = temp;


	queue->count++;
}


void ReferencePage(Queue* queue, Hash* hash, unsigned pageNumber)
{
	QNode* reqPage = hash->array[pageNumber];

	if (reqPage == NULL)
		Enqueue(queue, hash, pageNumber);

	else if (reqPage != queue->front)
	{
		reqPage->prev->next = reqPage->next;
		if (reqPage->next)
			reqPage->next->prev = reqPage->prev;
		if (reqPage == queue->rear)
		{
			queue->rear = reqPage->prev;
			queue->rear->next = NULL;
		}
		reqPage->next = queue->front;
		reqPage->prev = NULL;
		reqPage->next->prev = reqPage;

		queue->front = reqPage;
	}
}


int main()
{

	Queue* q = createQueue(4);
	Hash* hash = createHash(10);
	ReferencePage(q, hash, 1);
	ReferencePage(q, hash, 2);
	ReferencePage(q, hash, 3);
	ReferencePage(q, hash, 1);
	ReferencePage(q, hash, 4);
	ReferencePage(q, hash, 5);
	printf("%d ", q->front->pageNumber);
	printf("%d ", q->front->next->pageNumber);
	printf("%d ", q->front->next->next->pageNumber);
	printf("%d ", q->front->next->next->next->pageNumber);

	return 0;
}


*/