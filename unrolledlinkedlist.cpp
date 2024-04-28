#include <stdio.h>
#include <stdlib.h>

class unrolled_list 
{
private:
    struct Node 
    {
        int data[5];
        int num_elements;
        struct Node* next;
    };

    struct Node* head;

public:
    unrolled_list() 
    {
        head = NULL;
    }

    int insert(int num);
    int delete_num(int num);
    int search(int num);
    void display();
};

int unrolled_list::insert(int num) 
{
    if (head == NULL) 
    {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data[0] = num;
        new_node->num_elements = 1;
        new_node->next = NULL;
        head = new_node;
        return 1;
    }

    struct Node* temp = head;
    while (temp->next != NULL) 
    {
        if (temp->num_elements < 5) 
        {
            temp->data[temp->num_elements] = num;
            temp->num_elements++;
            return 1;
        }
        temp = temp->next;
    }

    if (temp->num_elements < 5) 
    {
        temp->data[temp->num_elements] = num;
        temp->num_elements++;
    } 
    else 
    {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data[0] = num;
        new_node->num_elements = 1;
        new_node->next = NULL;
        temp->next = new_node;
    }
    return 1;
}

int unrolled_list::delete_num(int num) 
{
    if (head == NULL) 
    {
        return 0;
    }

    struct Node* temp = head;
    while (temp != NULL) 
    {
        for (int i = 0; i < temp->num_elements; i++) 
        {
            if (temp->data[i] == num) 
            {
                for (int j = i; j < temp->num_elements - 1; j++) 
                {
                    temp->data[j] = temp->data[j + 1];
                }
                temp->num_elements--;
                if (temp->num_elements == 0) 
                {
                    if (temp == head) 
                    {
                        head = temp->next;
                    } 
                    else 
                    {
                        struct Node* prev = head;
                        while (prev->next != temp) 
                        {
                            prev = prev->next;
                        }
                        prev->next = temp->next;
                    }
                    free(temp);
                }
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

int unrolled_list::search(int num) 
{
    struct Node* temp = head;
    while (temp != NULL) 
    {
        for (int i = 0; i < temp->num_elements; i++) 
        {
            if (temp->data[i] == num) 
            {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

void unrolled_list::display() 
{
    struct Node* temp = head;
    while (temp != NULL) 
    {
        for (int i = 0; i < temp->num_elements; i++) 
        {
            printf("%d ", temp->data[i]);
        }
        temp = temp->next;
    }
    printf("\n");
}

int main() 
{
    unrolled_list ul1;
    int choice, num;
    while (1) 
    {
        printf("\n\nMENU\n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1: 
            {
                printf("Enter the element to be inserted: ");
                scanf("%d", &num);
                if (ul1.insert(num)) 
                {
                    printf("Element inserted successfully!\n");
                } 
                else 
                {
                    printf("Insertion failed!\n");
                }
                break;
            }

            case 2: 
            {
                printf("Enter the element to be deleted: ");
                scanf("%d", &num);
                if (ul1.delete_num(num)) 
                {
                    printf("Element deleted successfully!\n");
                } 
                else 
                {
                    printf("Element not found!\n");
                }
                break;
            }

            case 3: 
            {
                printf("Enter the element to be searched: ");
                scanf("%d", &num);
                if (ul1.search(num)) 
                {
                    printf("Element found!\n");
                } 
                else 
                {
                    printf("Element not found!\n");
                }
                break;
            }

            case 4:
                printf("Elements in the unrolled linked list: ");
                ul1.display();
                break;

            case 5:
                exit(0);
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }
    }
    return 0;
}
