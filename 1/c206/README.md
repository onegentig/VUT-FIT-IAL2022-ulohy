# IAL — Dvousměrně vázaný lineární seznam (c206)

## Popis úlohy

Implementujte abstraktní datový typ (ADT) **dvousměrně-vázaný lineární seznam** (*doubly-linked list*) s obsahem typu `int`. Abstrakce bude reprezentována typem `DLList`:

```c
typedef struct {
  /** Ukazatel na první prvek seznamu. */
  DLLElementPtr firstElement;
  /** Ukazatel na aktuální prvek seznamu. */
  DLLElementPtr activeElement;
  /** Ukazatel na posledni prvek seznamu. */
  DLLElementPtr lastElement;
} DLList;
```

Typ `DLLElementPtr` bude definován jako ukazatel na strukturu `DLLElement`:

```c
typedef struct DLLElement {
  /** Užitečná data. */
  int data;
  /** Ukazatel na předcházející prvek seznamu. */
  struct DLLElement *previousElement;
  /** Ukazatel na následující prvek seznamu. */
  struct DLLElement *nextElement;
} *DLLElementPtr;
```

### Funkce

* **`void DLL_Init(DLList *list)`** : Inicializuje seznam `list` před jeho prvním použitím. Funkce vytvoří prázdný seznam (neobsahuje žádné prvky). Vždy předpokládejte, že neinicializované proměnné mají nedefinovanou hodnotu.
* **`void DLL_Dispose(DLList *list)`** : Uvolní všechny prvky seznamu `list` a uvede ho do stavu, v jakém se nacházel po inicializaci. Veškerá paměť seznamu bude korektně uvolněna pomocí `free()`.
* **`void DLL_InsertFirst(DLList *list, int data)`** : Vloží nový prvek na začátek seznamu `list`. Nový prvek bude obsahovat hodnotu `data`. Volá `DLL_Error()` v případě chyby alokace paměti.
* **`void DLL_InsertLast(DLList *list, int data)`** : Vloží nový prvek na konec seznamu `list`. Nový prvek bude obsahovat hodnotu `data`. Volá `DLL_Error()` v případě chyby alokace paměti.
* **`void DLL_First(DLList *list)`** : Nastaví první prvek seznamu `list` jako aktivní. Případ prázdého seznamu ignoruje. Funkci implementujte jako jediný příkaz.
* **`void DLL_Last(DLList *list)`** : Nastaví poslední prvek seznamu `list` jako aktivní. Případ prázdého seznamu ignoruje. Funkci implementujte jako jediný příkaz.
* **`void DLL_GetFirst(DLList *list, int *dataPtr)`** : Vloží hodnotu obsaženou v prvním prvku seznamu `list` do proměnné `dataPtr`. Volá `DLL_Error()` v případě prázdého seznamu.
* **`void DLL_GetLast(DLList *list, int *dataPtr)`** : Vloží hodnotu obsaženou v posledním prvku seznamu `list` do proměnné `dataPtr`. Volá `DLL_Error()` v případě prázdého seznamu.
* **`void DLL_DeleteFirst(DLList *list)`** : Odstraní první prvek seznamu `list`. Pokud je tento prvek aktivní, aktivita se ztrácí. V případě prázdého seznamu se nic neděje.
* **`void DLL_DeleteLast(DLList *list)`** : Odstraní poslední prvek seznamu `list`. Pokud je tento prvek aktivní, aktivita se ztrácí. V případě prázdého seznamu se nic neděje.
* **`void DLL_DeleteAfter(DLList *list)`** : Odstraní prvek za aktivním prvkem seznamu `list`. Pokud žádny prvek není aktivní, nebo je aktivní poslední prvek seznamu, nic se neděje.
* **`void DLL_DeleteBefore(DLList *list)`** : Odstraní prvek před aktivním prvkem seznamu `list`. Pokud žádny prvek není aktivní, nebo je aktivní první prvek seznamu, nic se neděje.
* **`void DLL_InsertAfter(DLList *list, int data)`** : Vloží nový prvek za aktivní prvek seznamu `list`. Nový prvek bude obsahovat hodnotu `data`. Volá `DLL_Error()` v případě chyby alokace paměti.
* **`void DLL_InsertBefore(DLList *list, int data)`** : Vloží nový prvek před aktivní prvek seznamu `list`. Nový prvek bude obsahovat hodnotu `data`. Volá `DLL_Error()` v případě chyby alokace paměti.
* **`void DLL_GetValue(DLList *list, int *dataPtr)`** : Vloží hodnotu obsaženou v aktivním prvku seznamu `list` do proměnné `dataPtr`. Volá `DLL_Error()` v případě, že žádný prvek není aktivní.
* **`void DLL_SetValue(DLList *list, int data)`** : Přepíše hodnotu obsaženou v aktivním prvku seznamu `list` na hodnotu `data`. Pokud žádný prvek není aktivní, nic se neděje.
* **`void DLL_Next(DLList *list)`** : Posune aktivitu na další prvek seznamu `list`. Pokud je aktivní poslední prvek seznamu, aktivita se ztrácí. V případě prázdého seznamu se nic neděje.
* **`void DLL_Previous(DLList *list)`** : Posune aktivitu na předchozí prvek seznamu `list`. Pokud je aktivní první prvek seznamu, aktivita se ztrácí. V případě prázdého seznamu se nic neděje.
* **`int DLL_IsActive(DLList *list)`** : Vrací nenulovou hodnotu, pokud je nějaký prvek seznamu `list` aktivní, jinak vrací nulu. Funkci implementujte jako jediný příkaz.

### Poznámky

* Při implementaci funkcí nevolejte žádnou z funkcí impelmentovaných v rámci tohoto příkladu, není-li to u dané funkce explicitně uvedeno.
* Není třeba ošetřovat situaci, kdy místo legálního ukazatele na seznam předá někdo jako parametr hodnotu NULL.
* **Svou implementaci vhodně komentujte!**

### Odevzdání

Odovzdáváte jenom soubory `c201.c`, `c203.c` a `c206.c` prostřednictvím STUDISu (nezabalené a kódované v UTF8) do [zadání "1. domácí úloha"](https://www.vut.cz/studis/student.phtml?script_name=zadani_detail&apid=230956&zid=50549). Jestliže Vaše implementace daného příkladu generuje správné výsledky pro základní testovací aplikaci (`make run`), při překladu a spuštění na serveru `eva.fit.vutbr.cz`, získáváte za příklad **2 body**. Jestliže Vaše implementace vyhoví i pokročilým testům (ty v zadání domácí úlohy nenajdete), získáváte za příklad i zbývající body (tedy **1 bod** za příklad C201 a C203 a **2 body** za příklad C206).

*Doporučuji Vám proto, abyste si zkusili základní testovací aplikaci rozšířit a odhalit tak co nejvíce chyb ve své implementaci. Případnou upravenou testovací aplikaci ale do STUDISu neodevzdávejte.*

*Pokud se dostanete do časové tísně, nesnažte se řešit všechny příklady najednou v naději, že za částečné řešení něco dostanete. V takovém případě je výhodnější dokončit alespoň jeden či dva příklady pořádně.*

**Nedodržení zadání (např. zásahy do kostry programu) bude mít za následek ztrátu všech bodů za domácí úlohu!**

**Stejně tak budou 0 body hodnoceny příklady nepřeložitelné a ty, které se nekonečně zacyklí** - příklad se se zlou potáže (přesněji řečeno s `kill -9`), pokud bude potřebovat k řešení více jak 15s.

**V případě odhalení plagiátorství či nedovolené spolupráce nebude udělen zápočet a dále bude zváženo zahájení disciplinárního řízení.**

*Případné dotazy primárně nesměřujte na garanta předmětu ani přednášející ale na vedoucího zadání a to prostřednictvím fakultního emailu.*

### Referenční výstup testu

```text
C206 - Doubly Linked List, Basic Tests
======================================

[test_init] Inicializace seznamu
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)


[test_get_first_empty] Získání hodnoty prvního prvku v prázdném seznamu
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)
*ERROR* The program has performed an illegal operation.


[test_get_last_empty] Získání hodnoty posledního prvku v prázdném seznamu
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)
*ERROR* The program has performed an illegal operation.


[test_first_empty] Aktivace prvního prvku v prázdném seznamu
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)
Active element : not initialised (no item is active)


[test_last_empty] Aktivace posledního prvku v prázdném seznamu
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)
Active element : not initialised (no item is active)


[test_insert_first] Vkládání nových prvků na začátek seznamu
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)
List elements  : 4
First element  : 4
Last element   : 4
Active element : not initialised (no item is active)
List elements  : 3 4
First element  : 3
Last element   : 4
Active element : not initialised (no item is active)
List elements  : 2 3 4
First element  : 2
Last element   : 4
Active element : not initialised (no item is active)
List elements  : 1 2 3 4
First element  : 1
Last element   : 4
Active element : not initialised (no item is active)


[test_insert_last] Vkládání nových prvků na konec seznamu
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)
List elements  : 1
First element  : 1
Last element   : 1
Active element : not initialised (no item is active)
List elements  : 1 2
First element  : 1
Last element   : 2
Active element : not initialised (no item is active)
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
List elements  : 1 2 3 4
First element  : 1
Last element   : 4
Active element : not initialised (no item is active)


[test_get_value_inactive] Získání hodnoty prvku v seznamu bez aktivního prvku
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
*ERROR* The program has performed an illegal operation.


[test_set_value_inactive] Aktualizace hodnoty prvku v seznamu bez aktivního prvku
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)


[test_next_inactive] Aktivace následujícího prvku v seznamu bez aktivního prvku
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)


[test_previous_inactive] Aktivace předcházejícího prvku v seznamu bez aktivního prvku
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)


[test_get_first] Získání hodnoty prvního prvku
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
Returned value : 1


[test_get_last] Získání hodnoty posledního prvku
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
Returned value : 3


[test_get_value] Získání hodnot aktivních prvků
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
Returned value : 1
Returned value : 2
Returned value : 3


[test_set_value] Aktualizace hodnot aktivních prvků
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
List elements  : 3 2 3
First element  : 3
Last element   : 3
Active element : 3
List elements  : 3 2 1
First element  : 3
Last element   : 1
Active element : 1


[test_first_next_activity] Nastavení aktivity na následnících
Active element : not initialised (no item is active)
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : 1
Active element : 2
Active element : 3
Active element : not initialised (no item is active)


[test_last_previous_activity] Nastavení aktivity na předchůdcích
Active element : not initialised (no item is active)
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : 3
Active element : 2
Active element : 1
Active element : not initialised (no item is active)


[test_is_active] Aktivita seznamu
List elements  : 1 2
First element  : 1
Last element   : 2
Active element : not initialised (no item is active)
Is list element active? No
Is list element active? Yes
Is list element active? Yes
Is list element active? Yes
Is list element active? Yes
Is list element active? No


[test_insert_after] Vložení několika prvků po aktivním prvku
List elements  : 1
First element  : 1
Last element   : 1
Active element : not initialised (no item is active)
List elements  : 1 2
First element  : 1
Last element   : 2
Active element : 1
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : 2
List elements  : 1 2 3 4
First element  : 1
Last element   : 4
Active element : 3


[test_insert_before] Vložení několika prvků po před aktivní prvek
List elements  : 4
First element  : 4
Last element   : 4
Active element : not initialised (no item is active)
List elements  : 3 4
First element  : 3
Last element   : 4
Active element : 4
List elements  : 2 3 4
First element  : 2
Last element   : 4
Active element : 3
List elements  : 1 2 3 4
First element  : 1
Last element   : 4
Active element : 2


[test_delete_first] Zrušení prvního prvku v seznamu
List elements  : 3 2 1
First element  : 3
Last element   : 1
Active element : not initialised (no item is active)
List elements  : 2 1
First element  : 2
Last element   : 1
Active element : not initialised (no item is active)
List elements  : 1
First element  : 1
Last element   : 1
Active element : not initialised (no item is active)
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)


[test_delete_last] Zrušení posledního prvku v seznamu
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
List elements  : 1 2
First element  : 1
Last element   : 2
Active element : not initialised (no item is active)
List elements  : 1
First element  : 1
Last element   : 1
Active element : not initialised (no item is active)
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)


[test_delete_before] Zrušení prvku před aktivním prvkem
List elements  : 1 1 2 2 3 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
List elements  : 1 1 2 2 3
First element  : 1
Last element   : 3
Active element : 3
List elements  : 1 1 2 3
First element  : 1
Last element   : 3
Active element : 2
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : 1


[test_delete_after] Zrušení prvku po aktivním prvku
List elements  : 1 1 2 2 3 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
List elements  : 1 2 2 3 3
First element  : 1
Last element   : 3
Active element : 1
List elements  : 1 2 3 3
First element  : 1
Last element   : 3
Active element : 2
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : 3


[test_dispose] Zrušení prvků seznamu
List elements  : 1 2 3
First element  : 1
Last element   : 3
Active element : not initialised (no item is active)
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Last element   : not initialised (list is empty)
Active element : not initialised (no item is active)


```