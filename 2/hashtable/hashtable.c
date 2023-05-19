/**
 * @file hashtable.c
 * @author Onegen Something <xkrame00@vutbr.cz>
 * @brief Tabuľka s rozptýlenými položkami
 * @date 2022-11-04
 *
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

int HT_SIZE = MAX_HT_SIZE;

/*
 * Rozptyľovacia funkcia ktorá pridelí zadanému kľúču index z intervalu
 * <0,HT_SIZE-1>. Ideálna rozptyľovacia funkcia by mala rozprestrieť kľúče
 * rovnomerne po všetkých indexoch. Zamyslite sa nad kvalitou zvolenej funkcie.
 */
int get_hash(char *key) {
	int result = 1;
	int length = strlen(key);
	for (int i = 0; i < length; i++) {
		result += key[i];
	}
	return (result % HT_SIZE);
}

/*
 * Inicializácia tabuľky — zavolá sa pred prvým použitím tabuľky.
 */
void ht_init(ht_table_t *table) {
	for (int i = 0; i < HT_SIZE; i++) {
		(*table)[i] = NULL;
	}
}

/*
 * Vyhľadanie prvku v tabuľke.
 *
 * V prípade úspechu vráti ukazovateľ na nájdený prvok; v opačnom prípade vráti
 * hodnotu NULL.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) {
	ht_item_t *currentItem = (*table)[get_hash(key)];

	// Postupné prechádzanie zoznamu
	while (currentItem != NULL) {
		if (strcmp(currentItem->key, key) == 0) {
			// Prvok nájdený
			return currentItem;
		}
		// Prechod na ďalší prvok
		currentItem = currentItem->next;
	}

	// Prvok nebol nájdený
	return NULL;
}

/*
 * Vloženie nového prvku do tabuľky.
 *
 * Pokiaľ prvok s daným kľúčom už v tabuľke existuje, nahraďte jeho hodnotu.
 *
 * Pri implementácii využite funkciu ht_search. Pri vkladaní prvku do zoznamu
 * synonym zvoľte najefektívnejšiu možnosť a vložte prvok na začiatok zoznamu.
 */
void ht_insert(ht_table_t *table, char *key, float value) {
	ht_item_t *currentItem = ht_search(table, key);

	// Prepis hodnoty, pokiaľ prvok s daným kľúčom už existuje
	if (currentItem != NULL) {
		currentItem->value = value;
		return;
	}

	// Vytvorenie nového prvku
	ht_item_t *newItem = (ht_item_t *)malloc(sizeof(ht_item_t));
	if (newItem == NULL) {
		return; // Chyba alokácie pamäte
	}

	// Vloženie nového prvku do tabuľky
	newItem->key = key;
	newItem->value = value;
	newItem->next = (*table)[get_hash(key)];
	(*table)[get_hash(key)] = newItem;
}

/*
 * Získanie hodnoty z tabuľky.
 *
 * V prípade úspechu vráti funkcia ukazovateľ na hodnotu prvku, v opačnom
 * prípade hodnotu NULL.
 *
 * Pri implementácii využite funkciu ht_search.
 */
float *ht_get(ht_table_t *table, char *key) {
	// Nájdenie prvku
	ht_item_t *item = ht_search(table, key);

	// Prvok nebol nájdený
	if (item == NULL) {
		return NULL;
	}

	// Prvok bol nájdený
	return &(item->value);
}

/*
 * Zmazanie prvku z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje priradené k danému prvku.
 * Pokiaľ prvok neexistuje, nerobte nič.
 *
 * Pri implementácii NEVYUŽÍVAJTE funkciu ht_search.
 */
void ht_delete(ht_table_t *table, char *key) {
	int hash = get_hash(key);
	ht_item_t *currentItem = (*table)[hash];
	ht_item_t *parentItem = NULL;

	bool found = false;
	while (currentItem != NULL && !found) {
		// Prvok nájdený
		if (strcmp(currentItem->key, key) == 0) {
			if (parentItem == NULL) {
				// Prvok je na začiatku zoznamu
				(*table)[hash] = currentItem->next;
			} else {
				// Prvok je na konci alebo uprostred zoznamu
				parentItem->next = currentItem->next;
			}

			// Uvoľnenie pamäte prvku
			free(currentItem);
			return;
		}

		// Prechod na ďalší prvok
		parentItem = currentItem;
		currentItem = currentItem->next;
	}
}

/*
 * Zmazanie všetkých prvkov z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje a uvedie tabuľku do stavu po
 * inicializácii.
 */
void ht_delete_all(ht_table_t *table) {
	for (int i = 0; i < HT_SIZE; i++) {
		ht_item_t *currentItem = (*table)[i];

		// Žiaden prvok k indexu neexistuje
		if (currentItem == NULL) {
			continue;
		}

		// Postupné odstraňovanie a uvoľňovanie pamäte prvkov
		ht_item_t *nextItem;
		while (currentItem != NULL) {
			nextItem = currentItem->next;
			free(currentItem);
			currentItem = nextItem;
		}

		// Odstránenie ukazateľa na prvok
		(*table)[i] = NULL;
	}
}
