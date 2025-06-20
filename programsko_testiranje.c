#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complaints.h"
#include "games.h"
#include "customers.h"
#include "strukture.h"
 
#define MAX_IME 20
#define MAX_PREZIME 20
#define MAX_ADRESA 30
#define MAX_NAZIV_IGRE 30 

void pokazi_izbornik() { 
    int choice;

    do {
        printf("\n--- Izbornik ---\n");
        printf("1. PrikaŽi knjigu žalbi\n");
        printf("2. Unesi novu žalbu\n");
        printf("3. Dodaj novu igru\n");
        printf("4. Prikaži sve igre\n");
        printf("5. Prodaj igru\n");
        printf("6. Prikaži sve kupce\n");
        printf("7. Dodaj novog kupca\n");
        printf("8. Uredi podatke kupca\n");
        printf("9. Obriši kupca\n");
        printf("0. Izlaz\n");
        printf("Unesite vaš izbor: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            prikazi_knjigu_zalbi();
            break;
        case 2:
            pozali_se();
            break;
        case 3: {
            char name[MAX_NAZIV_IGRE];
            int copy_count;
            int console_choice;
            float price;
            console_platform console;

            printf("Unesite naziv igre: ");
            fgets(name, sizeof(name), stdin);

            printf("Unesite broj kopija: ");
            scanf("%d", &copy_count);
            getchar();

            printf("Odaberite konzolu:\n");
            printf("0. PS5\n");
            printf("1. XBOX\n");
            printf("2. Switch\n");
            printf("3. PC\n");
            printf("Broj različit od prethodnih za neponuđeno");
            printf("Unesite broj ispred konzole: ");
            scanf("%d", &console_choice);
            getchar();

            switch (console_choice) {
            case 0: console = CONSOLE_PS5; break;
            case 1: console = CONSOLE_XBOX; break;
            case 2: console = CONSOLE_SWITCH; break;
            case 3: console = CONSOLE_PC; break;
            default: console = CONSOLE_UNKNOWN; printf("Nepoznata konzola.\n"); break; 
            }

            printf("Unesite cijenu igre: ");
            scanf("%f", &price);
            getchar(); 

            add_game(name, copy_count, console, price);
            break;
        }
        case 4:
            show_games();
            break;
        case 5: {
            int game_id;
            customer kupac; 

            printf("Unesite ID igre (npr. 9000): G");
            scanf("%d", &game_id);
            getchar();

            printf("Unesite podatke o kupcu:\n");
            printf("Ime: ");
            fgets(kupac.first_name, sizeof(kupac.first_name), stdin);

            printf("Prezime: ");
            fgets(kupac.last_name, sizeof(kupac.last_name), stdin);

            kupac.id = generator_customer_id + 1;
            sell_game(game_id, kupac);
            break;
        }
        case 6:
            show_customers();
            break;
        case 7: {
            customer novi_kupac;
            char first_name[MAX_IME], last_name[MAX_PREZIME], address[MAX_ADRESA];

            printf("Unesite ime kupca: ");
            fgets(first_name, sizeof(first_name), stdin);

            printf("Unesite prezime kupca: ");
            fgets(last_name, sizeof(last_name), stdin);

            printf("Unesite adresu kupca: ");
            fgets(address, sizeof(address), stdin);

            add_customer(&novi_kupac, first_name, last_name, address);
            break;
        }
        case 8: {
            int id;
            printf("Unesite ID kupca kojeg želite urediti: ");
            scanf("%d", &id);
            edit_customer_info(id);
            break;
        }
        case 9: {
            int id;
            printf("Unesite ID kupca kojeg želite obrisati: ");
            scanf("%d", &id);
            delete_customer(id);
            break;
        }
        case 0:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Neispravan izbor. Pokušajte ponovo.\n");
        }
    } while (choice != 0);
}

int main() {
    pokazi_izbornik();
    return 0;
}
