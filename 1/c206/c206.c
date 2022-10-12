/* ******************************* c206.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c206 - Dvousměrně vázaný lineární seznam                            */
/*  Návrh a referenční implementace: Bohuslav Křena, říjen 2001               */
/*  Vytvořil: Martin Tuček, říjen 2004                                        */
/*  Upravil: Kamil Jeřábek, září 2020                                         */
/*           Daniel Dolejška, září 2021                                       */
/*           Daniel Dolejška, září 2022                                       */
/* ************************************************************************** */
/*
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int. Seznam bude jako datová
** abstrakce reprezentován proměnnou typu DLList (DL znamená Doubly-Linked
** a slouží pro odlišení jmen konstant, typů a funkcí od jmen u jednosměrně
** vázaného lineárního seznamu). Definici konstant a typů naleznete
** v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ obousměrně
** vázaný lineární seznam:
**
**      DLL_Init ........... inicializace seznamu před prvním použitím,
**      DLL_Dispose ........ zrušení všech prvků seznamu,
**      DLL_InsertFirst .... vložení prvku na začátek seznamu,
**      DLL_InsertLast ..... vložení prvku na konec seznamu,
**      DLL_First .......... nastavení aktivity na první prvek,
**      DLL_Last ........... nastavení aktivity na poslední prvek,
**      DLL_GetFirst ....... vrací hodnotu prvního prvku,
**      DLL_GetLast ........ vrací hodnotu posledního prvku,
**      DLL_DeleteFirst .... zruší první prvek seznamu,
**      DLL_DeleteLast ..... zruší poslední prvek seznamu,
**      DLL_DeleteAfter .... ruší prvek za aktivním prvkem,
**      DLL_DeleteBefore ... ruší prvek před aktivním prvkem,
**      DLL_InsertAfter .... vloží nový prvek za aktivní prvek seznamu,
**      DLL_InsertBefore ... vloží nový prvek před aktivní prvek seznamu,
**      DLL_GetValue ....... vrací hodnotu aktivního prvku,
**      DLL_SetValue ....... přepíše obsah aktivního prvku novou hodnotou,
**      DLL_Previous ....... posune aktivitu na předchozí prvek seznamu,
**      DLL_Next ........... posune aktivitu na další prvek seznamu,
**      DLL_IsActive ....... zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce explicitně
* uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c206.h"

int error_flag;
int solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě.
 * Tato funkce bude volána z některých dále implementovaných operací.
 */
void DLL_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
 * Provede inicializaci seznamu list před jeho prvním použitím (tzn. žádná
 * z následujících funkcí nebude volána nad neinicializovaným seznamem).
 * Tato inicializace se nikdy nebude provádět nad již inicializovaným seznamem,
 * a proto tuto možnost neošetřujte.
 * Vždy předpokládejte, že neinicializované proměnné mají nedefinovanou hodnotu.
 *
 * @param list Ukazatel na strukturu dvousměrně vázaného seznamu
 */
void DLL_Init(DLList *list) {
	list->firstElement = NULL;
	list->activeElement = NULL;
	list->lastElement = NULL;
}

/**
 * Zruší všechny prvky seznamu list a uvede seznam do stavu, v jakém se nacházel
 * po inicializaci.
 * Rušené prvky seznamu budou korektně uvolněny voláním operace free.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Dispose(DLList *list) {
	// Odstránenie aktivity zoznamu
	list->activeElement = NULL;

	// Uloženie ukazateľa na prvý prvok do pomocnej premennej
	DLLElementPtr element = list->firstElement;

	// Postupné vymazávanie a posúvanie prvého prvku zoznamu, dokým zoznam zostane prázdny.
	while (element != NULL) {
		DLLElementPtr nextElement = element->nextElement;
		free(element);
		element = nextElement;
	}

	// Nastavenie ukazateľov na prvý a posledný prvok na NULL
	list->firstElement = NULL;
	list->lastElement = NULL;
}

/**
 * Vloží nový prvek na začátek seznamu list.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 */
void DLL_InsertFirst(DLList *list, int data) {
	// Alokácia pamäte pre nový prvok
	DLLElementPtr element = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (element == NULL) {
		DLL_Error();
		return;
	}

	// Nastavenie hodnoty dátovej zložky nového prvku
	element->data = data;

	// Nastavenie ukazateľa na nasledujúci a predchádzajúci prvok nového prvku
	element->previousElement = NULL;
	element->nextElement = list->firstElement;

	// Posunutie pôvodne-prvého prvku (pokiaľ existuje)
	if (list->firstElement != NULL) {
		list->firstElement->previousElement = element;
	}

	// Vloženie nového prvku na začiatok zoznamu
	list->firstElement = element;

	// Nastavenie nového prvku zároveň ako posledného, pokiaľ bol zoznam prázdny
	if (list->lastElement == NULL) {
		list->lastElement = element;
	}
}

/**
 * Vloží nový prvek na konec seznamu list (symetrická operace k DLL_InsertFirst).
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na konec seznamu
 */
void DLL_InsertLast(DLList *list, int data) {
	// Alokácia pamäte pre nový prvok
	DLLElementPtr element = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (element == NULL) {
		DLL_Error();
		return;
	}

	// Nastavenie hodnoty dátovej zložky nového prvku
	element->data = data;

	// Nastavenie ukazateľov na nasledujúci a predchádzajúci prvok nového prvku
	element->previousElement = list->lastElement;
	element->nextElement = NULL;

	// Posunutie pôvodne-posledného prvku (pokiaľ existuje)
	if (list->lastElement != NULL) {
		list->lastElement->nextElement = element;
	}

	// Vloženie nového prvku na koniec zoznamu
	list->lastElement = element;

	// Nastavenie nového prvku zároveň ako prvého, pokiaľ bol zoznam prázdny
	if (list->firstElement == NULL) {
		list->firstElement = element;
	}
}

/**
 * Nastaví první prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_First(DLList *list) {
	list->activeElement = list->firstElement;
}

/**
 * Nastaví poslední prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Last(DLList *list) {
	list->activeElement = list->lastElement;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu prvního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetFirst(DLList *list, int *dataPtr) {
	// Kontrola, či je zoznam neprázdny
	if (list->firstElement == NULL) {
		DLL_Error();
		return;
	}

	// Vloženie hodnoty dátovej zložky prvého prvku do cielovej premennej
	*dataPtr = list->firstElement->data;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu posledního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetLast(DLList *list, int *dataPtr) {
	// Kontrola, či je zoznam neprázdny
	if (list->lastElement == NULL) {
		DLL_Error();
		return;
	}

	// Vloženie hodnoty dátovej zložky posledného prvku do cielovej premennej
	*dataPtr = list->lastElement->data;
}

/**
 * Zruší první prvek seznamu list.
 * Pokud byl první prvek aktivní, aktivita se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteFirst(DLList *list) {
	// Kontrola, či je zoznam neprázdny
	if (list->firstElement == NULL) {
		return;
	}

	// Uloženie ukazateľa na prvý prvok do pomocnej premennej
	DLLElementPtr element = list->firstElement;

	// Pokiaľ je rušený prvok aktívny, aktivita zoznamu sa stráca
	if (list->activeElement == element) {
		list->activeElement = NULL;
	}

	// Zrušenie celého zoznamu pokiaľ obsahuje iba jeden (rušený) prvok
	if (list->firstElement == list->lastElement) {
		list->firstElement = NULL;
		list->lastElement = NULL;
	} else {
		// Posunutie ukazateľa na prvého prvku na nasledujúci prvok
		list->firstElement = element->nextElement;

		// Zrušenie ukazateľa na predchádzajúci prvok
		list->firstElement->previousElement = NULL;
	}

	// Uvoľnenie pamäte rušeného prvku
	free(element);
}

/**
 * Zruší poslední prvek seznamu list.
 * Pokud byl poslední prvek aktivní, aktivita seznamu se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteLast(DLList *list) {
	// Kontrola, či je zoznam neprázdny
	if (list->lastElement == NULL) {
		return;
	}

	// Uloženie ukazateľa na posledný prvok do pomocnej premennej
	DLLElementPtr element = list->lastElement;

	// Pokiaľ je rušený prvok aktívny, aktivita zoznamu sa stráca
	if (list->activeElement == element) {
		list->activeElement = NULL;
	}

	// Zrušenie celého zoznamu pokiaľ obsahuje iba jeden (rušený) prvok
	if (list->firstElement == list->lastElement) {
		list->firstElement = NULL;
		list->lastElement = NULL;
	} else {
		// Posunutie ukazateľa na posledného prvku na predchádzajúci prvok
		list->lastElement = element->previousElement;

		// Zrušenie ukazateľa na nasledujúci prvok
		list->lastElement->nextElement = NULL;
	}

	// Uvoľnenie pamäte rušeného prvku
	free(element);
}

/**
 * Zruší prvek seznamu list za aktivním prvkem.
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * posledním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteAfter(DLList *list) {
	// Kontrola, či má zoznam aktívny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Kontrola, či má zoznam aktívny prvok nasledujúci prvok
	if (list->activeElement->nextElement == NULL) {
		return;
	}

	// Uloženie ukazateľa na nasledujúci prvok do pomocnej premennej
	DLLElementPtr element = list->activeElement->nextElement;

	// Posunutie ukazateľa na nasledujúci prvok na nasledujúci prvok rušeného prvku
	list->activeElement->nextElement = element->nextElement;

	// Nastavenie ukazateľa na posledný prvok na aktívny, pokiaľ bol rušený prvok posledný
	if (list->lastElement == element) {
		list->lastElement = list->activeElement;
	} else {
		// Nastavenie ukazateľa na predchádzajúci prvok nasledujúceho prvku
		element->nextElement->previousElement = list->activeElement;
	}

	// Uvoľnenie pamäte rušeného prvku
	free(element);
}

/**
 * Zruší prvek před aktivním prvkem seznamu list .
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * prvním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteBefore(DLList *list) {
	// Kontrola, či má zoznam aktívny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Kontrola, či má zoznam aktívny prvok predchádzajúci prvok
	if (list->activeElement->previousElement == NULL) {
		return;
	}

	// Uloženie ukazateľa na predchádzajúci prvok do pomocnej premennej
	DLLElementPtr element = list->activeElement->previousElement;

	// Posunutie ukazateľa na predchádzajúci prvok na predchádzajúci prvok rušeného prvku
	list->activeElement->previousElement = element->previousElement;

	// Nastavenie ukazateľa na prvého prvku na aktívny, pokiaľ bol rušený prvok prvý
	if (list->firstElement == element) {
		list->firstElement = list->activeElement;
	} else {
		// Nastavenie ukazateľa na nasledujúci prvok predchádzajúceho prvku
		element->previousElement->nextElement = list->activeElement;
	}

	// Uvoľnenie pamäte rušeného prvku
	free(element);
}

/**
 * Vloží prvek za aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 */
void DLL_InsertAfter(DLList *list, int data) {
	// Kontrola, či má zoznam aktívny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Alokácia pamäte pre nový prvok
	DLLElementPtr element = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (element == NULL) {
		DLL_Error();
		return;
	}

	// Nastavenie hodnoty dátovej zložky nového prvku
	element->data = data;

	// Nastavenie ukazateľov na nasledujúci a predchádzajúci prvok
	element->previousElement = list->activeElement;
	element->nextElement = list->activeElement->nextElement;

	// Posunutie pôvodne-nasledujúceho prvku (pokiaľ existuje)
	if (list->activeElement->nextElement != NULL) {
		list->activeElement->nextElement->previousElement = element;
	}

	// Vloženie nového prvku za aktívny prvok
	list->activeElement->nextElement = element;

	// Nastavenie nového prvku zároveň ako posledný prvok, pokiaľ bol aktívny prvok posledný
	if (list->lastElement == list->activeElement) {
		list->lastElement = element;
	}
}

/**
 * Vloží prvek před aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu před právě aktivní prvek
 */
void DLL_InsertBefore(DLList *list, int data) {
	// Kontrola, či má zoznam aktívny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Alokácia pamäte pre nový prvok
	DLLElementPtr element = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (element == NULL) {
		DLL_Error();
		return;
	}

	// Nastavenie hodnoty dátovej zložky nového prvku
	element->data = data;

	// Nastavenie ukazateľov na nasledujúci a predchádzajúci prvok
	element->previousElement = list->activeElement->previousElement;
	element->nextElement = list->activeElement;

	// Posunutie pôvodne-predchádzajúceho prvku (pokiaľ existuje)
	if (list->activeElement->previousElement != NULL) {
		list->activeElement->previousElement->nextElement = element;
	}

	// Vloženie nového prvku pred aktívny prvok
	list->activeElement->previousElement = element;

	// Nastavenie nového prvku zároveň ako prvý prvok, pokiaľ bol aktívny prvok prvý
	if (list->firstElement == list->activeElement) {
		list->firstElement = element;
	}
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, volá funkci DLL_Error ().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetValue(DLList *list, int *dataPtr) {
	// Kontrola, či má zoznam aktívny prvok
	if (list->activeElement == NULL) {
		DLL_Error();
		return;
	}

	// Vloženie hodnoty aktívneho prvku do ukazateľa cielovej premennej
	*dataPtr = list->activeElement->data;
}

/**
 * Přepíše obsah aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, nedělá nic.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 */
void DLL_SetValue(DLList *list, int data) {
	// Kontrola, či má zoznam aktívny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Nastavenie hodnoty aktívneho prvku
	list->activeElement->data = data;
}

/**
 * Posune aktivitu na následující prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Next(DLList *list) {
	// Kontrola, či má zoznam aktívny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Posun aktivity na nasledujúci prvok
	list->activeElement = list->activeElement->nextElement;
}

/**
 * Posune aktivitu na předchozí prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Previous(DLList *list) {
	// Kontrola, či má zoznam aktívny prvok
	if (list->activeElement == NULL) {
		return;
	}

	// Posun aktivity na predchádzajúci prvok
	list->activeElement = list->activeElement->previousElement;
}

/**
 * Je-li seznam list aktivní, vrací nenulovou hodnotu, jinak vrací 0.
 * Funkci je vhodné implementovat jedním příkazem return.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 * @returns Nenulovou hodnotu v případě aktivity prvku seznamu, jinak nulu
 */
int DLL_IsActive(DLList *list) {
	return list->activeElement != NULL;
}

/* Konec c206.c */
