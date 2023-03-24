#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE(x) ( (sizeof(x))  /  (sizeof(x[0]))  )
#define DEC 10

typedef struct node {
  int data;
  struct node *next;
} Node;

typedef struct {
  Node *front, *back;
} Queue;


/* Queue utility functions prototypes */
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int front(const Queue *queue);
bool empty(const Queue *queue);
/* ---------------------------------- */

size_t loop_iterations(int* arr, size_t len);
void print_array(int* arr, size_t len);

/*
    radix_sort function
    Parameter 1 - Array of Queue pointers
    Parameter 2 - reference to the array to be sorted
    Parameter 3 - the size of the array to be sorted
*/
void radix_sort(Queue** qs, int*, size_t N);
void initialize_queue_array(Queue **qs, size_t N);


int main()
{

    int nums[] = {237, 146, 259, 348, 152, 163, 235, 48, 36, 62};
    size_t N = SIZE(nums);

    int nums2[] = {9, 8, 7, 6, 5, 3, 11};
    size_t N2 = SIZE(nums2);

    int nums3[] = {19999, 21233, 897801, 18312, 16315, 12101, 2023};
    size_t N3 = SIZE(nums3);

    Queue *qs[DEC];
    initialize_queue_array(qs, DEC);

    Queue *qs2[DEC];
    initialize_queue_array(qs2, DEC);

    Queue *qs3[DEC];
    initialize_queue_array(qs3, DEC);

    printf("Before Radix sort: ");
    print_array(nums2, N2);
    radix_sort(qs2, nums2, N2);
    printf("After Radix sort: ");
    print_array(nums2, N2);

    printf("\n");

    printf("Before Radix sort: ");
    print_array(nums, N);
    radix_sort(qs, nums, N);
    printf("After Radix sort: ");
    print_array(nums, N);

    printf("\n");

    printf("Before Radix sort: ");
    print_array(nums3, N3);
    radix_sort(qs3, nums3, N3);
    printf("After Radix sort: ");
    print_array(nums3, N3);

    printf("\n");

    return 0;
}

void enqueue(Queue *queue, int data)
{
  Node* newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;

  if(!queue->front)
  {
    queue->front = newNode;
    queue->back = newNode;
    return;
  }

  queue->back->next = newNode;
  queue->back = newNode;

  return;
}

int dequeue(Queue *queue)
{
  int data = queue->front->data;
  Node* del = queue->front;
  queue->front = queue->front->next;
  free(del);
  return data;
}

int front(const Queue *queue)
{
  return queue->front->data;
}

bool empty(const Queue *queue)
 {
  return !queue->front;
}

size_t loop_iterations(int* arr, size_t len)
{
    int largest = arr[0];
    for (size_t i = 1; i < len; i++)
        if (arr[i] > largest)
            largest = arr[i];

    size_t c = 1;
    while (largest /= 10)
        c++;
    return c;
}

void print_array(int* arr, size_t len)
{
    for(size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void radix_sort(Queue** qs, int* nums, size_t N)
{
    int divisor = 1;
    size_t loops = loop_iterations(nums, N);
    for(size_t i = 0; i < loops; i++, divisor *= 10)
    {
        for(size_t j = 0; j < N; j++)
        {
            size_t index = (nums[j] / divisor) % 10;
            enqueue(qs[index], nums[j]);
        }

        size_t count = 0;
        for(size_t k = 0; k < DEC; k++)
        {
            if(qs[k])
                while(!empty(qs[k]))
                    nums[count++] = dequeue(qs[k]);
        }
    }
}

void initialize_queue_array(Queue **qs, size_t N)
{
    for(size_t i = 0; i < N; i++)
    {
        Queue *q = malloc(sizeof(Queue));
        q->front = NULL;
        q->back = NULL;
        qs[i] = q;
    }
}
