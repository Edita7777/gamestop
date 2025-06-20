#ifndef GAMES_H
#define GAMES_H
#include "strukture.h"
#define MAX_GAMES 1000 

int generator_game_id = 9000; 

game games[MAX_GAMES];
int game_count = 0;


const char* get_console_name(console_platform console) {
    switch (console) {
    case CONSOLE_PS5: return "PS5";
    case CONSOLE_XBOX: return "XBOX";
    case CONSOLE_SWITCH: return "Switch";
    case CONSOLE_PC: return "PC";
    default: return "Unknown"; 
    }
}


void update_file() {
    FILE* f = fopen("igre.txt", "w");
    if (f == NULL) {
        perror("Ne mogu otvoriti datoteku 'igre.txt' za ažuriranje");
        return;
    }

    for (int i = 0; i < game_count; i++) {
        if (games[i].copies_number > 0) {
            fprintf(f, "G%d | %s | %d | %s | %.2f\n",
                games[i].id,
                games[i].name,
                games[i].copies_number,
                get_console_name(games[i].console),
                games[i].price);
        }
    }

    fclose(f);
}



void add_game(const char name[], int copies_number, console_platform console, float price) {
    if (game_count >= MAX_GAMES) { 
        printf("Baza igara je puna!\n");
        return;
    }

    game new_game = { 0 }; 
    new_game.id = generator_game_id++;
    strcpy(new_game.name, name); 
    new_game.copies_number = copies_number;
    new_game.console = console;
    new_game.price = price;

    games[game_count++] = new_game;

    FILE* f = fopen("igre.txt", "a");  
    if (f == NULL) {
        perror("Ne mogu otvoriti datoteku 'igre.txt' za pisanje");
        return;
    }

    int status = fprintf(f, "G%d | %s | %d | %s | %.2f\n", new_game.id, new_game.name, new_game.copies_number, get_console_name(new_game.console), new_game.price);
    if (status < 0) {
        perror("Greška prilikom pisanja u datoteku");
    }

    fclose(f);
}

int usporedi_igre(const void* a, const void* b) { 
    const game* igraA = (const game*)a;
    const game* igraB = (const game*)b;
    return strcmp(igraA->name, igraB->name);
}

void sortiraj_igre_abecedno() {
    if (game_count > 1) {
        qsort(games, game_count, sizeof(game), usporedi_igre);
        printf("Popis igara je sortiran abecedno.\n");
    }
    else if (game_count == 0) {
        printf("Nema igara za sortiranje.\n");
    }
    else {
        printf("Samo je jedna igra u popisu, nema potrebe za sortiranjem.\n");
    }
}

void show_games() {
    sortiraj_igre_abecedno();
    FILE* f = fopen("igre.txt", "r");
    if (f == NULL) {
        perror("Ne mogu otvoriti datoteku za čitanje");
        return;
    }

    int id;
    char name[30];
    int copies_number;
    char console_str[20];
    float price;

    printf("--- Popis igara ---\n");

    while (fscanf(f, "G%d | %29[^|] | %d | %19[^|] | %f\n", &id, name, &copies_number, console_str, &price) == 5) {
        printf("ID: G%d | IME: %s | KOPIJE: %d | KONZOLA: %s | CIJENA: %.2f\n", id, name, copies_number, console_str, price);
    }

    fclose(f);
}

int search_game(int game_id) { 
    for (int i = 0; i < game_count; i++) {
        if (games[i].id == game_id) {
            return i;
        }
    }
    return -1;
}

void sell_game(int game_id, customer customer) {
    int game_index = search_game(game_id);
    if (game_index == -1) {
        printf("Igra s ID-jem G%d nije pronađena.\n", game_id);
        return;
    }

    if (games[game_index].copies_number <= 0) {
        printf("Nema više kopija igre \"%s\" na stanju.\n", games[game_index].name);
        return;
    }

    games[game_index].copies_number--;

    update_file();

    FILE* f = fopen("prodaja.txt", "a");
    if (f == NULL) {
        perror("Ne mogu otvoriti datoteku 'prodaja.txt' za pisanje");
        return;
    }

    fprintf(f, "Kupac: %s %s (ID: %d) | Igra: %s (ID: G%d) | Konzola: %s | Cijena: %.2f\n",
        customer.first_name, customer.last_name, customer.id, games[game_index].name, games[game_index].id,
        get_console_name(games[game_index].console),
        games[game_index].price);

    fclose(f);

    printf("Prodana igra \"%s\" kupcu %s %s.\n", games[game_index].name, customer.first_name, customer.last_name);
}

#endif
