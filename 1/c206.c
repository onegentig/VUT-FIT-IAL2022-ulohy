/**
 * @file c206.c
 * @author GitHub User (xplagi00@stud.fit.vutbr.cz)
 * @brief Implementace dvousměrného seznamu (Doubly-Linked List ADT)
 * @date 2022-10-12
 *
 */

#include "c206.h"

int error_flag;
int solved;

/**
 * @brief Vytiskne upozornění na to, že došlo k chybě a nastaví error_flag na 1
 *
 */
void DLL_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
 * @brief Inicializuje seznam
 * @param list Ukazatel na strukturu dvousměrně vázaného seznamu
 *
 */
void DLL_Init(DLList *list) {
	list->firstElement = NULL;
	list->activeElement = NULL;
	list->lastElement = NULL;
}

/**
 * @brief Zruší všechny prvky seznamu a uvede ho do stavu, v jakém se nacházel po inicializaci
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 */
void DLL_Dispose(DLList *list) {
	// Odstranění aktivity seznamu
	list->activeElement = NULL;

	// Uložení ukazatele na první prvek do pomocné proměnné
	DLLElementPtr element = list->firstElement;

	// Postupné odstraňování a posouvání prvního prvku seznamu, dokud seznam nezůstane prázdný.
	while (element != NULL) {
		DLLElementPtr nextElement = element->nextElement;
		free(element);
		element = nextElement;
	}

	// Nastavení ukazatelů na první a poslední prvek na NULL
	list->firstElement = NULL;
	list->lastElement = NULL;
}

/**
 * @brief Vloží prvek s hodnotou data na začátek seznamu
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 *
 */
void DLL_InsertFirst(DLList *list, int data) {
	// Alokace paměti pro nový prvek
	DLLElementPtr element = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (element == NULL) {
		DLL_Error();
		return;
	}

	// Nastavení hodnoty datové složky nového prvku
	element->data = data;

	// Nastavení ukazatele na další a předchozí prvek nového prvku
	element->previousElement = NULL;
	element->nextElement = list->firstElement;

	// Posunutí původně prvního prvku (pokud existuje)
	if (list->firstElement != NULL) {
		list->firstElement->previousElement = element;
	}

	// Vložení nového prvku na začátek seznamu
	list->firstElement = element;

	// Nastavení nového prvku jako posledního, pokud byl seznam prázdný
	if (list->lastElement == NULL) {
		list->lastElement = element;
	}
}

/**
 * @brief Vloží prvek s hodnotou data na konec seznamu
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na konec seznamu
 *
 */
void DLL_InsertLast(DLList *list, int data) {
	// Alokace paměti pro nový prvek
	DLLElementPtr element = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (element == NULL) {
		DLL_Error();
		return;
	}

	// Nastavení hodnoty datové složky nového prvku
	element->data = data;

	// Nastavení ukazatele na další a předchozí prvek nového prvku
	element->previousElement = list->lastElement;
	element->nextElement = NULL;

	// Posunutí původně posledního prvku (pokud existuje)
	if (list->lastElement != NULL) {
		list->lastElement->nextElement = element;
	}

	// Vložení nového prvku na konec seznamu
	list->lastElement = element;

	// Nastavení nového prvku jako prvního, pokud byl seznam prázdný
	if (list->firstElement == NULL) {
		list->firstElement = element;
	}
}

/**
 * @brief Nastaí aktivitu na první prvek seznamu
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 */
void DLL_First(DLList *list) {
	list->activeElement = list->firstElement;
}

/**
 * @brief Nasatví aktivitu na poslední prvek seznamu
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 */
void DLL_Last(DLList *list) {
	list->activeElement = list->lastElement;
}

/**
 * @brief Vloží hodnotu prvního prvku seznamu do ukazatele
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 *
 */
void DLL_GetFirst(DLList *list, int *dataPtr) {
	// Kontrola, zda je seznam neprázdný
	if (list->firstElement == NULL) {
		DLL_Error();
		return;
	}

	// Vložení hodnoty datové složky prvního prvku do cílové proměnné
	*dataPtr = list->firstElement->data;
}

/**
 * @brief Vloží hodnotu posledního prvku seznamu do ukazatele
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 *
 */
void DLL_GetLast(DLList *list, int *dataPtr) {
	// Kontrola, zda je seznam neprázdný
	if (list->lastElement == NULL) {
		DLL_Error();
		return;
	}

	// Vložení hodnoty datové složky posledního prvku do cílové proměnné
	*dataPtr = list->lastElement->data;
}

/**
 * @brief Vymaže první prvek seznamu
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 */
void DLL_DeleteFirst(DLList *list) {
	// Kontrola, zda je seznam neprázdný
	if (list->firstElement == NULL) {
		return;
	}

	// Uložení ukazatele na první prvek do pomocné proměnné
	DLLElementPtr element = list->firstElement;

	// Pokud je rušený prvek aktivní, aktivita seznamu se ztratí
	if (list->activeElement == element) {
		list->activeElement = NULL;
	}

	// Zrušení celého seznamu, pokud obsahuje pouze jeden (rušený) prvek.
	if (list->firstElement == list->lastElement) {
		list->firstElement = NULL;
		list->lastElement = NULL;
	} else {
		// Posunutí ukazatele prvního prvku na následující prvek
		list->firstElement = element->nextElement;

		// Zrušení ukazatele na předchozí prvek
		list->firstElement->previousElement = NULL;
	}

	// Uvolnění paměti rušeného prvku
	free(element);
}

/**
 * @brief Vymaže poslední prvek seznamu
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 */
void DLL_DeleteLast(DLList *list) {
	// Kontrola, zda je seznam neprázdný
	if (list->lastElement == NULL) {
		return;
	}

	// Uložení ukazatele na poslední prvek do pomocné proměnné
	DLLElementPtr element = list->lastElement;

	// Pokud je rušený prvek aktivní, aktivita seznamu se ztratí
	if (list->activeElement == element) {
		list->activeElement = NULL;
	}

	// Zrušení celého seznamu, pokud obsahuje pouze jeden (rušený) prvek.
	if (list->firstElement == list->lastElement) {
		list->firstElement = NULL;
		list->lastElement = NULL;
	} else {
		// Posunutí ukazatele posledního prvku na předcházející prvek
		list->lastElement = element->previousElement;

		// Zrušení ukazatele na následujúcí prvek
		list->lastElement->nextElement = NULL;
	}

	// Uvolnění paměti rušeného prvku
	free(element);
}

/**
 * @brief Vymaže prvek seznamu za aktivním prvkem
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 */
void DLL_DeleteAfter(DLList *list) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Kontrola, zda aktivní prvek má následující prvek
	if (list->activeElement->nextElement == NULL) {
		return;
	}

	// Uložení ukazatele na následující prvek do pomocné proměnné
	DLLElementPtr element = list->activeElement->nextElement;

	// Posunutí ukazatele na následující prvek na následující prvek rušeného prvku
	list->activeElement->nextElement = element->nextElement;

	// Nastavení ukazatele na poslední prvek na aktivní, pokud byl rušený prvek poslední
	if (list->lastElement == element) {
		list->lastElement = list->activeElement;
	} else {
		// Nastavení ukazatele na předchozí prvek následujícího prvku
		element->nextElement->previousElement = list->activeElement;
	}

	// Uvolnění paměti rušeného prvku
	free(element);
}

/**
 * @brief Vymaže prvek seznamu před aktivním prvkem
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 */
void DLL_DeleteBefore(DLList *list) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Kontrola, zda aktivní prvek má předcházející prvek
	if (list->activeElement->previousElement == NULL) {
		return;
	}

	// Uložení ukazatele na předcházející prvek do pomocné proměnné
	DLLElementPtr element = list->activeElement->previousElement;

	// Posunutí ukazatele na předcházející prvek na předcházející prvek rušeného prvku
	list->activeElement->previousElement = element->previousElement;

	// Nastavení ukazatele na první prvek na aktivní, pokud byl rušený prvek poslední
	if (list->firstElement == element) {
		list->firstElement = list->activeElement;
	} else {
		// Nastavení ukazatele na následující prvek předchozího prvku
		element->previousElement->nextElement = list->activeElement;
	}

	// Uvolnění paměti rušeného prvku
	free(element);
}

/**
 * @brief Vloží prvek za aktivní prvek
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 *
 */
void DLL_InsertAfter(DLList *list, int data) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Alokace paměti pro nový prvek
	DLLElementPtr element = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (element == NULL) {
		DLL_Error();
		return;
	}

	// Nastavení hodnoty datové složky nového prvku
	element->data = data;

	// Nastavení ukazatelů na následující a předchozí prvek
	element->previousElement = list->activeElement;
	element->nextElement = list->activeElement->nextElement;

	// Posunutí původně následujícího prvku (pokud existuje)
	if (list->activeElement->nextElement != NULL) {
		list->activeElement->nextElement->previousElement = element;
	}

	// Vložení nového prvku za aktivní prvek
	list->activeElement->nextElement = element;

	// Nastavení nového prvku jako posledního, pokud byl aktivní prvek poslední
	if (list->lastElement == list->activeElement) {
		list->lastElement = element;
	}
}

/**
 * @brief Vloží prvek před aktivní prvek
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu před právě aktivní prvek
 *
 */
void DLL_InsertBefore(DLList *list, int data) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Alokace paměti pro nový prvek
	DLLElementPtr element = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (element == NULL) {
		DLL_Error();
		return;
	}

	// Nastavení hodnoty datové složky nového prvku
	element->data = data;

	// Nastavení ukazatelů na následující a předchozí prvek
	element->previousElement = list->activeElement->previousElement;
	element->nextElement = list->activeElement;

	// Posunutí původně předcházejícího prvku (pokud existuje)
	if (list->activeElement->previousElement != NULL) {
		list->activeElement->previousElement->nextElement = element;
	}

	// Vložení nového prvku před aktivní prvek
	list->activeElement->previousElement = element;

	// Nastavení nového prvku jako prvního, pokud byl aktivní prvek první
	if (list->firstElement == list->activeElement) {
		list->firstElement = element;
	}
}

/**
 * @brief Vloží hodnotu aktivního prvku do ukazatele
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 *
 */
void DLL_GetValue(DLList *list, int *dataPtr) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		DLL_Error();
		return;
	}

	// Vložení hodnoty aktivního prvku do ukazatele cílové proměnné
	*dataPtr = list->activeElement->data;
}

/**
 * @brief Nastaví hodnotu aktivního prvku
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 *
 */
void DLL_SetValue(DLList *list, int data) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Nastavení hodnoty aktivního prvku
	list->activeElement->data = data;
}

/**
 * @brief Posune aktivitu na prvek následující za aktivním
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 */
void DLL_Next(DLList *list) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Přesun aktivity na následující prvek
	list->activeElement = list->activeElement->nextElement;
}

/**
 * @brief Posune aktivitu na prvek předcházející aktivnímu
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 */
void DLL_Previous(DLList *list) {
	// Kontrola, zda má seznam aktivní prvek
	if (list->activeElement == NULL) {
		return;
	}

	// Přesun aktivity na předcházející prvek
	list->activeElement = list->activeElement->previousElement;
}

/**
 * @brief Zjistí, zda má seznam aktivní prvek
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @returns Nenulovou hodnotu v případě aktivity prvku seznamu, jinak nulu
 *
 */
int DLL_IsActive(DLList *list) {
	return list->activeElement != NULL;
}