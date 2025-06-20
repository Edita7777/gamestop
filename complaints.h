#ifndef COMPLAINTS_H
#define COMPLAINTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void prikazi_knjigu_zalbi() {

    FILE* f = fopen("knjiga_zalbi.txt", "r");


    if (f == NULL) {
        perror("Ne mogu otvoriti datoteku 'knjiga_zalbi.txt' za čitanje");
        return;
    }

    char zalba[500];

    printf("--- Knjiga Zalbi ---\n"); 

    while (fgets(zalba, sizeof(zalba), f) != NULL) {
        printf("%s", zalba);
    }

    fclose(f);
}

void pozali_se() {
    FILE* f = fopen("knjiga_zalbi.txt", "a");

    if (f == NULL) {
        perror("Ne mogu otvoriti datoteku 'knjiga_zalbi.txt' za pisanje");
        return;
    }

    char zalba[500];

    printf("Unesite vasu prituzbu: ");

    fgets(zalba, sizeof(zalba), stdin); 

    if (zalba[0] == '\n') {
        printf("Pritužba nije unešena.\n");
        fclose(f);
        return;
    }

    int status = fprintf(f, "Žalba: %s\n", zalba); 

    if (status < 0) {
        perror("Greška prilikom pisanja u datoteku");
    }
    else {
        printf("Vaša žalba je uspješno zabilježena.\n");
    }

    fclose(f);
}

#endif
