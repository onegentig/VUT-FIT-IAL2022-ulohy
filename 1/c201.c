/**
 * @file c201.c
 * @author GitHub User (xplagi00@stud.fit.vutbr.cz)
 * @brief Implementace jednosměrného seznamu (Singly-Linked List ADT)
 * @date 2022-10-12
 *
 */

#include "c201.h"

#include <stdio.h>
#include <stdlib.h>

int error_flag;
int solved;

/**
 * @brief Vytiskne upozornění na to, že došlo k chybě a nastaví error_flag na 1
 *
 */
void List_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
 * @brief Inicializuje seznam
 *
 */
void List_Init(List *list) {
	list->firstElement = NULL;
	list->activeElement = NULL;
}

/**
 * @brief Zruší všechny prvky seznamu a uvede ho do stavu, v jakém se nacházel po inicializaci
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 *
 */
void List_Dispose(List *list) {
	// Odstranění aktivity seznamu
	list->activeElement = NULL;

	// Postupní odstraňování a posouvání prvního prvku seznamu, dokud seznam nezůstane prázdný
	while (list->firstElement != NULL) {
		ListElementPtr element = list->firstElement;
		list->firstElement = element->nextElement;
		free(element);
	}
}

/**
 * @brief Vloží prvek s hodnotou data na začátek seznamu
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 *
 */
void List_InsertFirst(List *list, int data) {
	// Alokace paměti pro nový prvek
	ListElementPtr element = (ListElementPtr)malloc(sizeof(struct ListElement));
	if (element == NULL) {
		List_Error();
		return;
	}

	// Nastavení hodnoty datové složky nového prvku
	element->data = data;

	// Nastavení ukazatele na další prvek nového prvku (původní první prvek)
	element->nextElement = list->firstElement;

	// Vložení nového prvku na začátek seznamu
	list->firstElement = element;
}

/**
 * @brief Nastaví aktivitu seznamu na jeho první prvek
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 *
 */
void List_First(List *list) {
	list->activeElement = list->firstElement;
}

/**
 * @brief Vloží hodnotu prvního prvku seznamu do ukazatele
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 *
 */
void List_GetFirst(List *list, int *dataPtr) {
	// Kontrola, zda je seznam neprázdný
	if (list->firstElement == NULL) {
		List_Error();
		return;
	}

	// Vložení hodnoty datové složky prvního prvku do cílové proměnné
	*dataPtr = list->firstElement->data;
}

/**
 * @brief Zruší první prvek seznamu
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 *
 */
void List_DeleteFirst(List *list) {
	// Kontrola, zda je seznam neprázdný
	if (list->firstElement == NULL) {
		return;
	}

	// Uložení ukazatele na první prvek do pomocné proměnné
	ListElementPtr element = list->firstElement;

	// Pokud je rušený prvek aktivní, aktivita seznamu se ztratí
	if (list->activeElement == element) {
		list->activeElement = NULL;
	}

	// Posunutí ukazatele prvního prvku seznamu na následující prvek
	list->firstElement = element->nextElement;

	// Uvolnění paměti rušeného prvku
	free(element);
}

/**
 * @brief Zruší prvek seznamu za aktivním prvkem
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 *
 */
void List_DeleteAfter(List *list) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Kontrola, zda následuje prvek za aktivním prvkem (je co rušit)
	if (list->activeElement->nextElement == NULL) {
		return;
	}

	// Uložení ukazatele na rušený prvek do pomocné proměnné
	ListElementPtr element = list->activeElement->nextElement;

	// Posunutí ukazatele aktivního prvku seznamu na další prvek
	list->activeElement->nextElement = element->nextElement;

	// Uvolnění paměti rušeného prvku
	free(element);
}

/**
 * @brief Vloží prvek za aktivní prvek seznamu
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 *
 */
void List_InsertAfter(List *list, int data) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Alokace paměti pro nový prvek
	ListElementPtr element = (ListElementPtr)malloc(sizeof(struct ListElement));
	if (element == NULL) {
		List_Error();
		return;
	}

	// Nastavení hodnoty datové složky nového prvku
	element->data = data;

	// Nastavení ukazatele na následující prvek nového prvku (původní následující prvek aktivního prvku)
	element->nextElement = list->activeElement->nextElement;

	// Vložení nového prvku za aktivní prvek
	list->activeElement->nextElement = element;
}

/**
 * @brief Vloží hodnotu aktivního prvku seznamu do ukazatele
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 *
 */
void List_GetValue(List *list, int *dataPtr) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		List_Error();
		return;
	}

	// Vložení hodnoty datové složky aktivního prvku do cílové proměnné
	*dataPtr = list->activeElement->data;
}

/**
 * @brief Přepíše data aktivního prvku seznamu
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 *
 */
void List_SetValue(List *list, int data) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Nastavení hodnoty datové složky aktivního prvku
	list->activeElement->data = data;
}

/**
 * @brief Posune aktivitu na následující prvek seznamu
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 *
 */
void List_Next(List *list) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Posunutí ukazatele aktivní položky na následující položku
	list->activeElement = list->activeElement->nextElement;
}

/**
 * @brief Zjistí, zda je seznam aktivní
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @return Nenulová hodnota, pokud je seznam aktivní, jinak 0
 *
 */
int List_IsActive(List *list) {
	return list->activeElement != NULL;
}