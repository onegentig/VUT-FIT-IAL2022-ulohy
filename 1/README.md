# IAL — 1. Domácí Úloha

*(merged zadání)*

## Odevzdání

Odovzdáváte jenom soubory `c201.c`, `c203.c` a `c206.c` prostřednictvím STUDISu (nezabalené a kódované v UTF8) do [zadání "1. domácí úloha"](https://www.vut.cz/studis/student.phtml?script_name=zadani_detail&apid=230956&zid=50549). Jestliže Vaše implementace daného příkladu generuje správné výsledky pro základní testovací aplikaci (`make run`), při překladu a spuštění na serveru `eva.fit.vutbr.cz`, získáváte za příklad **2 body**. Jestliže Vaše implementace vyhoví i pokročilým testům (ty v zadání domácí úlohy nenajdete), získáváte za příklad i zbývající body (tedy **1 bod** za příklad C201 a C203 a **2 body** za příklad C206).

*Doporučuji Vám proto, abyste si zkusili základní testovací aplikaci rozšířit a odhalit tak co nejvíce chyb ve své implementaci. Případnou upravenou testovací aplikaci ale do STUDISu neodevzdávejte.*

*Pokud se dostanete do časové tísně, nesnažte se řešit všechny příklady najednou v naději, že za částečné řešení něco dostanete. V takovém případě je výhodnější dokončit alespoň jeden či dva příklady pořádně.*

**Nedodržení zadání (např. zásahy do kostry programu) bude mít za následek ztrátu všech bodů za domácí úlohu!**

**Stejně tak budou 0 body hodnoceny příklady nepřeložitelné a ty, které se nekonečně zacyklí** - příklad se se zlou potáže (přesněji řečeno s `kill -9`), pokud bude potřebovat k řešení více jak 15s.

**V případě odhalení plagiátorství či nedovolené spolupráce nebude udělen zápočet a dále bude zváženo zahájení disciplinárního řízení.**

*Případné dotazy primárně nesměřujte na garanta předmětu ani přednášející ale na vedoucího zadání a to prostřednictvím fakultního emailu.*

## Poznámky

* (c203) V poli je vždy minimálně jeden prvek nevyužitý.
* (c203) Při libovolné operaci se žádný z indexů nesnižuje, vyjma případu, kdy index přesáhne hranici `QUEUE_SIZE`. V tom případě se "posunuje" znovu na začátek pole. Za tímto účelem budete deklarovat pomocnou funkci `nextIndex`, která pro kruhový pohyb přes indexy pole využívá operaci "modulo".
* (c201+c206) Při implementaci funkcí nevolejte žádnou z funkcí impelmentovaných v rámci tohoto příkladu, není-li to u dané funkce explicitně uvedeno.
* (c201+c206) Není třeba ošetřovat situaci, kdy místo legálního ukazatele na seznam předá někdo jako parametr hodnotu NULL.
* **Svou implementaci vhodně komentujte!**

## Jednosměrný lineární seznam (c201)

Implementujte abstraktní datový typ **jednosměrný lineární seznam** (*singly linked list*), kde užitečným obsahem prvku seznamu je celé číslo typu int. Tenhle seznam bude jako datová abstrakce reprezentována jako proměnná typu List:

```c
typedef struct {
  /** Ukazatel na první prvek seznamu */
  ListElementPtr firstElement;
  /** Ukazatel na aktivní prvek seznamu */
  ListElementPtr activeElement;
} List;
```

List je tedy struktura, která obsahuje dva ukazatele. První ukazuje na první prvek seznamu, druhý ukazuje na aktivní prvek seznamu. Ukazatele jsou typu ListElementPtr:

```c
typedef struct ListElement {
  /** Užitečná data */
  int data;
  /** Ukazatel na následující prvek seznamu */
  struct ListElement *nextElement;
} *ListElementPtr;
```

### Funkce

* **`void List_Init(List *list)`** : Inicializuje seznam `list` před jeho prvním použitím. Funkce vytvoří prázdný seznam (neobsahuje žádné prvky). Očekávejte, že seznam `list` byl před voláním této funkce vytvořen pomocí `malloc()` a není inicializován.
* **`int List_IsActive(List *list)`** : Vrací hodnotu 1, pokud je seznam `list` aktivní, jinak vrací hodnotu 0.
* **`void List_GetValue(List *list, int *dataPtr)`** : Vrací hodnotu aktivního prvku seznamu `list` do proměnné `dataPtr`. Pokud není aktivní žádný prvek, volá funkci `List_Error()`.
* **`void List_SetValue(List *list, int data)`** : Nastaví hodnotu aktivního prvku seznamu `list` na hodnotu `data`. Pokud není aktivní žádný prvek, volá funkci `List_Error()`. Funkce přepisuje jakékoliv předchozí hodnoty aktivního prvku seznamu.
* **`void List_InsertFirst(List *list, int data)`** : Vloží prvek s hodnotou `data` na začátek seznamu `list`. Pokud není dostatek paměti, nebo `malloc()` selže, volá funkci `List_Error()`.
* **`void List_First(List *list)`** : Nastaví aktivitu na první prvek seznamu `list`. Funkci implementujte jako jediný příkaz - netestujte, zda seznam `list` není prázdný.
* **`void List_GetFirst(List *list, int *dataPtr)`** : Vrací hodnotu prvního prvku seznamu `list` do proměnné `dataPtr`. Pokud je seznam prázdný, volá funkci `List_Error()`.
* **`void List_Next(List *list)`** : Posune aktivitu na následující prvek seznamu `list`. Pokud není aktivní žádný prvek, nic nedělá. Pokud je aktivní poslední prvek seznamu, aktivita se strácí.
* **`void List_InsertAfter(List *list, int data)`** : Vloží prvek s hodnotou `data` za aktivní prvek seznamu `list`. Pokud není dostatek paměti, nebo `malloc()` selže, volá funkci `List_Error()`. Pokud není aktivní žádný prvek, nic se neděje.
* **`void List_DeleteFirst(List *list)`** : Odstraní první prvek seznamu `list` a uvolní paměť, kterou zabíral. Pokud byl rušený prvek aktivní, aktivita se ztrácí. Pokud je seznam prázdný, nic se neděje.
* **`void List_DeleteAfter(List *list)`** : Odstraní prvek za aktivním prvkem seznamu `list` a uvolní paměť, kterou zabíral. Pokud seznam není aktivní nebo je aktivní poslední prvek seznamu, nic se neděje.
* **`void List_Dispose(List *list)`** : Uvolní všechny prvky seznamu `list` a uvede ho do stavu, v jakém se nacházel po inicializaci. Veškerá paměť seznamu bude korektně uvolněna pomocí `free()`.

### Referenční výstup testu

<details>
<summary>c201-test.output</summary>

```text
C201 - Linked List, Basic Tests
===============================

[test_init] Inicializace struktury
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Active element : not initialised (no item is active)


[test_get_first_empty] Získání hodnoty prvního prvku v prázdném seznamu
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Active element : not initialised (no item is active)
*ERROR* The program has performed an illegal operation.


[test_first_empty] Aktivace prvního prvku v prázdném seznamu
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Active element : not initialised (no item is active)
Active element : not initialised (no item is active)


[test_insert_first] Vkládání nových prvků na první místo
List elements  : 1 2 3 4
First element  : 1
Active element : not initialised (no item is active)


[test_get_value_inactive] Získání hodnoty prvku v seznamu bez aktivního prvku
List elements  : 1 2 3
First element  : 1
Active element : not initialised (no item is active)
*ERROR* The program has performed an illegal operation.


[test_set_value_inactive] Aktualizace hodnoty prvku v seznamu bez aktivního prvku
List elements  : 1 2 3
First element  : 1
Active element : not initialised (no item is active)
List elements  : 1 2 3
First element  : 1
Active element : not initialised (no item is active)


[test_next_inactive] Aktivace následujícího prvku v seznamu bez aktivního prvku
List elements  : 1 2 3
First element  : 1
Active element : not initialised (no item is active)
Active element : not initialised (no item is active)


[test_get_first] Získání hodnoty prvního prvku
List elements  : 1 2 3
First element  : 1
Active element : not initialised (no item is active)
Returned value : 1


[test_get_value] Získání hodnot aktivních prvků
List elements  : 1 2 3
First element  : 1
Active element : not initialised (no item is active)
Returned value : 1
Returned value : 2
Returned value : 3


[test_set_value] Aktualizace hodnot aktivních prvků
List elements  : 1 2 3
First element  : 1
Active element : not initialised (no item is active)
List elements  : 3 2 3
First element  : 3
Active element : 3
List elements  : 3 2 1
First element  : 3
Active element : 1


[test_is_active] Aktivita seznamu
List elements  : 1 2 3
First element  : 1
Active element : not initialised (no item is active)
Is list element active? No
Is list element active? Yes
Is list element active? Yes
Is list element active? Yes
Is list element active? No


[test_first_next_activity] Nastavení aktivity na následnících
Active element : not initialised (no item is active)
List elements  : 1 2 3
First element  : 1
Active element : 1
Active element : 2
Active element : 3
Active element : not initialised (no item is active)


[test_insert_after] Vložení několika prvků na poslední místo
List elements  : 1
First element  : 1
Active element : not initialised (no item is active)
List elements  : 1 2
First element  : 1
Active element : 1
List elements  : 1 2 3
First element  : 1
Active element : 2
List elements  : 1 2 3 4
First element  : 1
Active element : 3


[test_delete_first] Zrušení prvního prvku v seznamu
List elements  : 3 2 1
First element  : 3
Active element : not initialised (no item is active)
List elements  : 2 1
First element  : 2
Active element : not initialised (no item is active)
List elements  : 1
First element  : 1
Active element : not initialised (no item is active)
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Active element : not initialised (no item is active)
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Active element : not initialised (no item is active)


[test_delete_after] Zrušení prvku po aktivním prvku
List elements  : 1 1 2 2 3 3
First element  : 1
Active element : not initialised (no item is active)
List elements  : 1 2 2 3 3
First element  : 1
Active element : 1
List elements  : 1 2 3 3
First element  : 1
Active element : 2
List elements  : 1 2 3
First element  : 1
Active element : 3


[test_dispose] Zrušení prvků seznamu
List elements  : 1 2 3
First element  : 1
Active element : not initialised (no item is active)
List elements  : none (list is empty)
First element  : not initialised (list is empty)
Active element : not initialised (no item is active)
```

</details>

## Fronta znaků v poli (c203)

Implementujte **frontu znaků v poli** (*character array queue*). Fronta (*queue*) je abstraktní datový typ, který umožňuje ukládat a získávat hodnoty podle principu *FIFO* (angl. *first in, first out*). Tedy první hodnota, která byla do fronty vložena, je také první, která bude získána.

```c
typedef struct {
  /** Pole pro uložení hodnot. */
  char array[MAX_QUEUE];
  /** Index prvního prvku. */
  int firstIndex;
  /** Index první volné pozice. */
  int freeIndex;
} Queue;
```

Fronta je abstrakce statického pole znaků (*char[]*). Všechny implementované funkce musí předpokádat velikost pole `QUEUE_SIZE`, i když ve skutečnosti jsou rozměry pole definovány `MAX_QUEUE`. Hodnota `QUEUE_SIZE` může být v rozsahu od 1 do `MAX_QUEUE`. 
Index `firstIndex` ukazuje vždy na první prvek ve front, index `freeIndex` ukazuje na první volný prvek ve frontě. Pokud je fronta prázdná, ukazují oba indexy na stejné místo. Po inicializaci ukazují na první prvek pole, obsahují tedy hodnotu 0.

### Funkce

* **`void Queue_Init(Queue *queue)`** : Inicializuje frontu `queue` nastavením všech hodnot v poli `queue->array` na `*` a obou indexů na 0. Pokud je ukazatel na frontu neplatný (*NULL*), volá `Queue_Error(QERR_INIT)`.
* **`int nextIndex(int index)`** : Vrací index následujícího prvku v poli (implementujte jako jediný příkaz využívající operátor `%`).
* **`int Queue_IsEmpty(const Queue *queue)`** : Vrací 1, pokud je fronta prázdná, jinak 0.
* **`int Queue_IsFull(const Queue *queue)`** : Vrací 1, pokud je fronta plná, jinak 0.
* **`void Queue_Front(const Queue *queue, char *dataPtr)`** : Vloží ukazatele prvního prvku fronty `queue` do proměnné `dataPtr`. Pokud je fronta prázdná, volá `Queue_Error(QERR_FRONT)`. Při implementaci využijte funkci `Queue_IsEmpty`.
* **`void Queue_Remove(Queue *queue)`** : Odstraní první prvek fronty `queue`. Pokud je fronta prázdná, volá `Queue_Error(QERR_REMOVE)`. Při implementaci využijte funkce `Queue_IsEmpty` a `nextIndex`.
* **`void Queue_Enqueue(Queue *queue, char data)`** : Vloží hodnotu proměnné `data` na konec fronty `queue`. Pokud je fronta plná, volá `Queue_Error(QERR_ENQUEUE)`. Při implementaci využijte funkce `Queue_IsFull` a `nextIndex`.
* **`void Queue_Dequeue(Queue *queue, char *dataPtr)`** : Vloží ukazatele na poslední prvek fronty `queue` do proměnné `dataPtr` a odstraní tenhle prvek z fronty. Pokud je fronta prázdná, volá `Queue_Error(QERR_DEQUEUE)`. Při implementaci využijte funkce `Queue_IsEmpty`, `Queue_Front` a `Queue_Remove`.

### Referenční výstup testu

</details>
<summary>c203-test.output</summary>

```text
C203 - Linked List, Basic Tests
===============================

[test_init] Inicializace fronty
Queue elements : **********
                 ^         
                 E         


[test_empty_empty] Kontrola prázdnosti fronty v prázdné frontě
Queue elements : **********
                 ^         
                 E         
Is queue empty? Yes


[test_full_empty] Kontrola plnosti fronty v prázdné frontě
Queue elements : **********
                 ^         
                 E         
Is queue full? No


[test_front_empty] Výpis čela v prázdné frontě
Queue elements : **********
                 ^         
                 E         
Queue error: FRONT


[test_remove_empty] Odstranění čela v prázdné frontě
Queue elements : **********
                 ^         
                 E         
Queue error: REMOVE


[test_get_empty] Uvolnění čela v prázdné frontě
Queue elements : **********
                 ^         
                 E         
Queue error: DEQUEUE


[test_up] Vložení do fronty
Queue elements : **********
                 ^         
                 E         
Queue elements : H*********
                 ^^        
                 FB        
Queue elements : He********
                 ^ ^       
                 F B       
Queue elements : Hel*******
                 ^  ^      
                 F  B      
Queue elements : Hell******
                 ^   ^     
                 F   B     
Queue elements : Hello*****
                 ^    ^    
                 F    B    


[test_up_full] Vložení do plné fronty
Queue elements : 012345678*
                 ^        ^
                 F        B
Queue error: ENQUEUE
Queue error: ENQUEUE
Queue error: ENQUEUE
Queue elements : 012345678*
                 ^        ^
                 F        B


[test_empty_full] Kontrola prázdnosti fronty v plné frontě
Queue elements : 012345678*
                 ^        ^
                 F        B
Is queue empty? No


[test_full_full] Kontrola plnosti fronty v plné frontě
Queue elements : 012345678*
                 ^        ^
                 F        B
Is queue full? Yes


[test_remove] Odstranění z čela fronty
Queue elements : 012*******
                 ^  ^      
                 F  B      
Queue elements : 012*******
                  ^ ^      
                  F B      
Queue elements : 012*******
                   ^^      
                   FB      
Queue elements : 012*******
                    ^      
                    E      


[test_get] Uvolnění z čela fronty
Queue elements : 012*******
                 ^  ^      
                 F  B      
Queue elements : 012*******
                  ^ ^      
                  F B      
Returned value : 0
Queue elements : 012*******
                   ^^      
                   FB      
Returned value : 1
Queue elements : 012*******
                    ^      
                    E      
Returned value : 2
```

</details>

## Dvousměrně vázaný lineární seznam (c206)

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

### Referenční výstup testu

<details>
<summary>c206-test.output</summary>

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

</details>