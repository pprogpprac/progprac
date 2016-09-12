#include <stdio.h>
#include <stdlib.h>

struct person
{
    char name[20];
    int age;
    struct person *next;
} *root;

void insert(struct person **root, struct person *new_person)
{
    struct person *temp = malloc(sizeof temp);
    new_person->next = NULL;

    if(*root == NULL)
        *root = new_person;

    else
    {
        temp = *root;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = new_person;
    }
}

void list(struct person *root)
{
    printf("~~~~~~~~~ List of people ~~~~~~~~~~\n");

    while(root != NULL)
    {
        printf("Name: %s Age: %d\n", root->name, root->age);
        root = root->next;
    }

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void main()
{
    while(1)
    {
        struct person *new_person;
        new_person = malloc(sizeof new_person);
        printf("Name and age for new person:\n");
        scanf("%s %d", new_person->name, &new_person->age);
        insert(&root, new_person);
        list(root);
    }
}
