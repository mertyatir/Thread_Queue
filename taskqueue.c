#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


//sorted list (in ascending order) with no duplicates


/* Struct for list nodes */
struct list_node_s {
int data;
struct list_node_s* next;
};


/* List operations */
int Insert(int value);
int Delete(int value);
int Search(int value);




int numberOfTasks=0;


int THREAD_NUM;
int TASK_NUM;
int number_of_tasks_left;
 

struct list_node_s* head =NULL;  //head node for Sorted List


//Search an element in the list. returns 1 if found else returns 0

int Search(int value) 
{
    struct list_node_s* temp = head;
    
    // traversing entire linked list
    while(temp != NULL)
    {
        if(value==temp->data)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;

}

// adding element in the linked list as sorted order and no duplicates
int Insert(int data)
{
    if(Search(data)==1)
    {
        return 0;
    }
    struct list_node_s *temp, *tail;
    temp = head;
    tail = malloc( sizeof (struct list_node_s));                                   
    tail->data = data;  
    tail->next = NULL;

    // if linked list is empty or data is smaller than the head.data, add as first node.
    if(head == NULL || (head)->data > data)
    {

        head = tail;
        (head)->next = temp;
        return 1;
    }
    // else search the position and add the element
    else
    {
        //Travel through the list
        while(temp != NULL)
        {
            if(temp->data <= data && (temp->next == NULL || temp->next->data > data ))
            {
                tail->next = temp->next;
                temp->next = tail;
                return 1;
            }
            // move to the next node
            temp = temp->next;
        }
    }
    return 0; 
}

// displays the sorted linked list
void display()
{
    struct list_node_s* temp = head;
    
    // traversing entire linked list
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


// Deletes the any element in the sorted linked list
int Delete(int data)
{
    struct list_node_s *old, *temp;
    temp = head;

    while(temp != NULL)
    {
        if(temp->data == data)
        {
            // deleting first node if data matches
            if(temp == head)
            {
                head = temp->next;
                free(temp);
                return 1;
            }
            // deleting other nodes except first node
            else
            {
                old->next = temp->next;
                free(temp);
                return 1;
            }
        }
        // old points to the previous node
        old = temp;
        temp = temp->next;
    }
    return 0;
}

/* Struct for task nodes */
struct task_node_s {
int task_num;
int task_type; // insert:0, delete:1, search:2
int value;
struct task_node_s* next;
};

/* Task queue functions */
void Task_queue(int n); //generate random task for the task queue and returns a pointer to task_node_s
void Task_enqueue(int task_num, int task_type, int value); //insert a new task into task queue
int Task_dequeue(int* task_num_p, int* task_type_p, int* value_p); //take a task from task queue


struct task_node_s* task_node_head;

void Task_enqueue(int task_num, int task_type, int value)
{

    
    
    struct task_node_s *temp, *tail;
    temp = task_node_head;
    tail = malloc( sizeof (struct task_node_s));                                   
    tail->task_num = task_num;  
    tail->task_type= task_type;
    tail->value= value;
    tail->next = NULL;

    

    // if linked list is empty add as first node.
    if(task_node_head == NULL)
    {

        task_node_head = tail;
        (task_node_head)->next = temp;
    }
    // else search the position and add the element
    else
    {
        //Travel to the end of the list
        while(temp->next!= NULL)
        {
            temp = temp->next;
        }

        temp->next = tail;
    }
}


// displays the task queue
void Task_display()
{
    struct task_node_s* temp = task_node_head;
    
    // traversing entire task queue
    printf("\nhead==>");
    while(temp != NULL)
    {
        printf("Task num: %d,Task type: %d,Task value: %d\n-->", temp->task_num,temp->task_type,temp->value);
        temp = temp->next;
    }
    printf("tail");
    printf("\n");
}




//generate n random tasks for the task queue
void Task_queue(int n)
{

    int r;
    int r2;
    struct task_node_s *temp;
    int task_number=0;

    

    for (int i = 0; i < n; i++)
    {

    r = rand() % 3; /* random int between 0 and 2 */
    r2= rand() % 100;  /* random int between 0 and 99 */
    temp = malloc( sizeof (struct task_node_s));  
    temp->task_num= task_number;
    task_number++;

    temp->task_type=r; // insert:0, delete:1, search:2
    temp->value=r2;
    temp->next=NULL;

    Task_enqueue(temp->task_num, temp->task_type, temp->value);
    numberOfTasks++;
    }

}


//take a task from task queue
int Task_dequeue(int* task_num_p, int* task_type_p, int* value_p)
{
    if(task_node_head==NULL)
    {
        return 0;
    }
    else
    {
        struct task_node_s* temp;
        temp=task_node_head;
        *task_num_p=temp->task_num;
        *task_type_p=temp->task_type;
        *value_p=temp->value;
        task_node_head=task_node_head->next;
        numberOfTasks--;
        return 1;
    }
}




void executeTask(struct task_node_s* task) 
{
    int task_num= task->task_num;
    int task_type=task->task_type;
    int value= task->value;

    
    switch( task_type )
{
    case 0: //Insert
        if(Insert(value))
        {
            printf("Task %d: %d is inserted\n",task_num,value);
        }
        else
        {
            printf("Task %d: %d could NOT inserted\n",task_num,value);
        }
        
        break;
    case 1: //Delete
        if(Delete(value))
        {
            printf("Task %d: %d is deleted\n",task_num,value);
        }
        else
        {
            printf("Task %d: %d could NOT deleted\n",task_num,value);
        }

        break;
    case 2: //Search
        if(Search(value))
        {
            printf("Task %d: %d is searched and found\n",task_num,value);
        }
        else
        {
            printf("Task %d: %d is searched and NOT found\n",task_num,value);
        }
        break;
    default :
        break;
}
    
}



void* startThread(void* args)   //Thread Function
{
    while(number_of_tasks_left>0)
    {
        struct task_node_s* task;
        task= malloc( sizeof (struct task_node_s));

        Task_dequeue(&(task->task_num), &(task->task_type), &(task->value));

        executeTask(task);  
    
        number_of_tasks_left--; 
        printf("Number of Tasks Left is %d\n",number_of_tasks_left);
    
    }

}

int main(int argc, char* argv[]) 
{
    THREAD_NUM= atoi(argv[1]); //Number of threads taken from the user
    TASK_NUM= atoi(argv[2]);  //Number of tasks taken from the user


    number_of_tasks_left=TASK_NUM;


    pthread_t th[THREAD_NUM];


    for (int i = 0; i < THREAD_NUM; i++) 
    {
        if (pthread_create(&th[i], NULL, &startThread, NULL) != 0) // Starting threads
        {
            perror("Failed to create the thread");
        }
        
    }

    Task_queue(TASK_NUM);   //Generating random tasks and enqueueing them to Task Queue

    for (int i = 0; i < THREAD_NUM; i++) 
    {
        
        if (pthread_join(th[i], NULL) != 0)  //Waiting threads to finish their execution
        {
            perror("Failed to join the thread");
        }
    }

    printf("main: Final list: \n");
    display(); //Displaying Final version of Sorted Linked List

    return 0;
}



