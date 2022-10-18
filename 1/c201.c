/**
 * @file c201.c
 * @author Onegenimasu <https://github.com/Onegenimasu>
 * @brief Implementácia jednosmerného zoznamu (Singly-Linked List ADT)
 * @date 2022-10-12
 *
 */

#include "c201.h"

#include <stdio.h>
#include <stdlib.h>

int error_flag;
int solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě. Nastaví error_flag na logickou 1.
 * Tato funkce bude volána z některých dále implementovaných operací.
 */
void List_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
 * Provede inicializaci seznamu list před jeho prvním použitím (tzn. žádná
 * z následujících funkcí nebude volána nad neinicializovaným seznamem).
 * Tato inicializace se nikdy nebude provádět nad již inicializovaným
 * seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
 * že neinicializované proměnné mají nedefinovanou hodnotu.
 *
 * @param list Ukazatel na strukturu jednosměrně vázaného seznamu
 */
void List_Init(List *list) {
	list->firstElement = NULL;
	list->activeElement = NULL;
}

/**
 * Zruší všechny prvky seznamu list a uvede seznam list do stavu, v jakém se nacházel
 * po inicializaci. Veškerá paměť používaná prvky seznamu list bude korektně
 * uvolněna voláním operace free.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 **/
void List_Dispose(List *list) {
	// Odstránenie aktivity zoznamu
	list->activeElement = NULL;

	// Postupné vymazávanie a posúvanie prvého prvku zoznamu, dokým zoznam zostane prázdny.
	while (list->firstElement != NULL) {
		ListElementPtr element = list->firstElement;
		list->firstElement = element->nextElement;
		free(element);
	}
}

/**
 * Vloží prvek s hodnotou data na začátek seznamu list.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci List_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 */
void List_InsertFirst(List *list, int data) {
	// Alokácia pamäte pre nový prvok
	ListElementPtr element = (ListElementPtr)malloc(sizeof(struct ListElement));
	if (element == NULL) {
		List_Error();
		return;
	}

	// Nastavenie hodnoty dátovej zložky nového prvku
	element->data = data;

	// Nastavenie ukazateľa na nasledujúci prvok nového prvku (pôvodný prvý prvok)
	element->nextElement = list->firstElement;

	// Vloženie nového prvku na začiatok zoznamu
	list->firstElement = element;
}

/**
 * Nastaví aktivitu seznamu list na jeho první prvek.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 */
void List_First(List *list) {
	list->activeElement = list->firstElement;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu prvního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci List_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void List_GetFirst(List *list, int *dataPtr) {
	// Kontrola, či je zoznam neprázdny
	if (list->firstElement == NULL) {
		List_Error();
		return;
	}

	// Vloženie hodnoty dátovej zložky prvého prvku do cielovej premennej
	*dataPtr = list->firstElement->data;
}

/**
 * Zruší první prvek seznamu list a uvolní jím používanou paměť.
 * Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 */
void List_DeleteFirst(List *list) {
	// Kontrola, či je zoznam neprázdny
	if (list->firstElement == NULL) {
		return;
	}

	// Uloženie ukazateľa na prvý prvok
	ListElementPtr element = list->firstElement;

	// Pokiaľ je rušený prvok aktívny, aktivita zoznamu sa stráca
	if (list->activeElement == element) {
		list->activeElement = NULL;
	}

	// Posunutie ukazateľa prvého prvku zoznamu na nasledujúci prvok
	list->firstElement = element->nextElement;

	// Uvoľnenie pamäte rušeného prvku
	free(element);
}

/**
 * Zruší prvek seznamu list za aktivním prvkem a uvolní jím používanou paměť.
 * Pokud není seznam list aktivní nebo pokud je aktivní poslední prvek seznamu list,
 * nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 */
void List_DeleteAfter(List *list) {
	// Kontrola, či zoznam má aktivny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Kontrola, či nasleduje prvok za aktívnym (je čo rušiť)
	if (list->activeElement->nextElement == NULL) {
		return;
	}

	// Uloženie ukazateľa na rušený prvok
	ListElementPtr element = list->activeElement->nextElement;

	// Posunutie ukazateľa aktívneho prvku zoznamu na nasledujúci prvok
	list->activeElement->nextElement = element->nextElement;

	// Uvoľnenie pamäte rušeného prvku
	free(element);
}

/**
 * Vloží prvek s hodnotou data za aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje!
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * zavolá funkci List_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 */
void List_InsertAfter(List *list, int data) {
	// Kontrola, či zoznam má aktivny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Alokácia pamäte pre nový prvok
	ListElementPtr element = (ListElementPtr)malloc(sizeof(struct ListElement));
	if (element == NULL) {
		List_Error();
		return;
	}

	// Nastavenie hodnoty dátovej zložky nového prvku
	element->data = data;

	// Nastavenie ukazateľa na nasledujúci prvok nového prvku (pôvodný nasledujúci prvok aktívneho prvku)
	element->nextElement = list->activeElement->nextElement;

	// Vloženie nového prvku za aktivny prvok
	list->activeElement->nextElement = element;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu aktivního prvku seznamu list.
 * Pokud seznam není aktivní, zavolá funkci List_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void List_GetValue(List *list, int *dataPtr) {
	// Kontrola, či zoznam má aktívny prvok
	if (list->activeElement == NULL) {
		List_Error();
		return;
	}

	// Vloženie hodnoty dátovej zložky aktivneho prvku do cielovej premennej
	*dataPtr = list->activeElement->data;
}

/**
 * Přepíše data aktivního prvku seznamu list hodnotou data.
 * Pokud seznam list není aktivní, nedělá nic!
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 */
void List_SetValue(List *list, int data) {
	// Kontrola, či zoznam má aktívny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Nastavenie hodnoty dátovej zložky aktívneho prvku
	list->activeElement->data = data;
}

/**
 * Posune aktivitu na následující prvek seznamu list.
 * Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
 * Pokud není předaný seznam list aktivní, nedělá funkce nic.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 */
void List_Next(List *list) {
	// Kontrola, či zoznam má aktívny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Posunutie ukazateľa aktívneho prvku na nasledujúci prvok
	list->activeElement = list->activeElement->nextElement;
}

/**
 * Je-li seznam list aktivní, vrací nenulovou hodnotu, jinak vrací 0.
 * Tuto funkci je vhodné implementovat jedním příkazem return.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 */
int List_IsActive(List *list) {
	return list->activeElement != NULL;
}

/* Konec c201.c */
