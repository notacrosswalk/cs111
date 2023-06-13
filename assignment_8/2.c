#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 50

struct patient_t
{
    int id;
    char name[30];
    int priority;
};

struct binary_heap_t
{
    struct patient_t patients[MAX_SIZE];
    int size;
};

void swap(struct patient_t* a, struct patient_t* b)
{
    struct patient_t temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(struct binary_heap_t* heap, int index)
{
    if(index == 0) 
        return;

    int parent_index = (index - 1) / 2;

    if(heap->patients[index].priority < heap->patients[parent_index].priority)
    {
        swap(&heap->patients[index], &heap->patients[parent_index]);
        heapify_up(heap, parent_index);
    }
}

void heapify_down(struct binary_heap_t* heap, int index)
{
    int smallest = index;

    int l_child = 2*index + 1;
    int r_child = 2*index + 2;

    if(l_child < heap->size && heap->patients[l_child].priority < heap->patients[index].priority)
    {
        smallest = l_child;
    }

    if(r_child < heap->size && heap->patients[r_child].priority < heap->patients[smallest].priority)
    {
        smallest = r_child;
    }

    if(smallest != index)
    {
        swap(&heap->patients[index], &heap->patients[smallest]);
        heapify_down(heap, smallest);
    }
}

void add_patient(struct binary_heap_t* heap)
{
    if(heap->size == MAX_SIZE)
    {
        printf("The queue is full. Insertions are not possible.\n");
        return;
    }

    struct patient_t new_patient;
    
    printf("Enter patient ID:\n");
    scanf("%d", &new_patient.id);
    printf("Enter patient name:\n");
    scanf("\n%[^\n]s", &new_patient.name);
    printf("Enter patient priority:\n");
    scanf("%d", &new_patient.priority);

    heap->patients[heap->size] = new_patient;
    heapify_up(heap, heap->size);
    heap->size++;

    printf("Patient added successfully.\n");
}

void treat_patient(struct binary_heap_t* heap)
{
    if(heap->size == 0)
    {
        printf("Queue is empty.\n");
        return;
    }

    struct patient_t treated_patient = heap->patients[0];
    printf("Treating patient - ID: %d, Name: %s, Priority: %d\n", treated_patient.id, treated_patient.name, treated_patient.priority);

    heap->patients[0] = heap->patients[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
}

void display_queue(struct binary_heap_t* heap) 
{
    if (heap->size == 0) 
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue:\n");
    for (int i = 0; i < heap->size; i++) 
    {
        printf("ID: %d, Name: %s, Priority: %d\n", heap->patients[i].id, heap->patients[i].name, heap->patients[i].priority);
    }
}

void check_patient_count(struct binary_heap_t* heap)
{
    printf("%d patients are waiting.\n", heap->size);
}

void update_patient_priority(struct binary_heap_t* heap)
{
    if(heap->size == 0)
    {
        printf("Queue is empty!\n");
        return;
    }

    int id;
    printf("Enter the patient ID to update priority:\n");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < heap->size; i++) 
    {
        if (heap->patients[i].id == id) 
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        printf("A patient with that ID was not found.\n");
        return;
    }

    int new_priority = 0;
    printf("Enter the new priority:\n");
    scanf("%d", &new_priority);

    bool up = true;

    if(new_priority > heap->patients[index].priority)
    {
        up = false;
    }

    heap->patients[index].priority = new_priority;

    if(index == 0)
    {
        heapify_down(heap, index);
    }
    else if(up)
    {
        heapify_up(heap, index);
    }
    else
    {
        heapify_down(heap, index);
    }
    
    printf("Patient priority updated successfully.\n");
}

void clear_queue(struct binary_heap_t* heap) 
{
    if (heap->size == 0) 
    {
        printf("Queue is already empty.\n");
        return;
    }

    heap->size = 0;
    printf("Queue has been cleared.\n");
}

void run_menu()
{
    struct binary_heap_t heap;
    heap.size = 0;

    int choice = 0;
    do 
    {
        printf("\nPatient Queue\n");
        printf("1. Add a Patient\n");
        printf("2. Treat a Patient\n");
        printf("3. Display Waiting Queue\n");
        printf("4. Check Patient Count\n");
        printf("5. Update Patient Priority\n");
        printf("6. Clear Waiting Queue\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                add_patient(&heap);
                break;
            case 2:
                treat_patient(&heap);
                break;
            case 3:
                display_queue(&heap);
                break;
            case 4:
                check_patient_count(&heap);
                break;
            case 5:
                update_patient_priority(&heap);
                break;
            case 6:
                clear_queue(&heap);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
}

int main()
{
    run_menu();
    return 0;
}
