#ifndef CUSTOMERS_H
#define CUSTOMERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strukture.h"

#define MAX_BROJ_KUPACA 500 

int generator_customer_id = 0;

void show_customers() {
    FILE* f = fopen("kupci.txt", "r");
    int id;
    char first_name[20], last_name[20], address[30]; //static arrayi da ne kompliciramo

    if (f == NULL) {
        perror("Ne mogu otvoriti datoteku za čitanje");
        return;
    }

    printf("--- Popis kupaca ---\n");
    while (fscanf(f, "%d | %[^|] | %[^|] | %[^\n]", &id, first_name, last_name, address) == 4) {
        printf("ID: %d | IME: %s | PREZIME: %s | ADRESA: %s\n", id, first_name, last_name, address);
    }

    fclose(f);
}

void add_customer(customer* customer, char* first_name, char* last_name, char* address) {
    FILE* f = fopen("kupci.txt", "a");
    if (f == NULL) {
        perror("Ne mogu otvoriti datoteku za pisanje");
        return;
    }

    generator_customer_id++;
    strcpy(customer->first_name, first_name);
    strcpy(customer->last_name, last_name);
    strcpy(customer->address, address);

    int status = fprintf(f, "%d | %s | %s | %s\n", generator_customer_id, customer->first_name, customer->last_name, customer->address);
    if (status < 0) {
        perror("Greška prilikom pisanja u datoteku");
    }

    fclose(f);
}

int load_all_customers(customer customers[]) {
    FILE* f = fopen("kupci.txt", "r");
    if (f == NULL) return 0;

    int count = 0;
    while (count < MAX_BROJ_KUPACA &&
        fscanf(f, "%d | %19[^|] | %19[^|] | %[^\n]",
            &customers[count].id,
            customers[count].first_name,
            customers[count].last_name,
            customers[count].address) == 4) {
        count++;
    }

    fclose(f);
    
    return count;
}

void save_all_customers(customer customers[], int count) {
    FILE* f = fopen("kupci.txt", "w");
    if (f == NULL) return;

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d | %s | %s | %s\n",
            customers[i].id,
            customers[i].first_name,
            customers[i].last_name,
            customers[i].address);
    }

    fclose(f);
}

int find_customer_index(customer customers[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (customers[i].id == id) {
            return i;
        }
    }
    return -1;
}

void edit_customer_info(int id) {
    customer customers[MAX_BROJ_KUPACA];
    int count = load_all_customers(customers);

    int index = find_customer_index(customers, count, id);
    if (index < 0) {
        printf("Kupac s ID-jem %d nije pronađen.\n", id);
        return;
    }

    int choice;
    printf("Unesite:\n");
    printf("1 za promjenu adrese kupca\n");
    printf("2 za promjenu imena kupca\n");
    printf("3 za promjenu prezimena kupca\n");
    printf("Vaš izbor: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        printf("Unesi novu adresu: ");
        char new_adress[20];
        scanf("%s", new_adress);
        strcpy(customers[index].address, new_adress);
        break;
    }
    case 2: {
        printf("Unesi novo ime: ");
        char new_first_name[30];
        scanf("%s", new_first_name);
        strcpy(customers[index].first_name, new_first_name);
        break;
    }
    case 3: {
        printf("Unesi novo prezime: ");
        char new_last_name[30];
        scanf("%s", new_last_name);
        strcpy(customers[index].last_name, new_last_name);
        break;
    }
    default:
        printf("Nevažeći izbor.\n");
        return;
    }

    save_all_customers(customers, count);
    printf("Podaci kupca su ažurirani.\n");
}

void delete_customer(int id) {
    customer customers[MAX_BROJ_KUPACA];
    int count = load_all_customers(customers);

    int index = find_customer_index(customers, count, id);
    if (index < 0) {
        printf("Kupac s ID-jem %d nije pronađen.\n", id);
        return;
    }

    for (int i = index; i < count - 1; i++) {
        customers[i] = customers[i + 1];
    }

    count--;

    save_all_customers(customers, count);

    printf("Kupac s ID-jem %d je uspješno obrisan.\n", id);

}

#endif
