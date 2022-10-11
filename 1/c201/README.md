# IAL — Jednosměrný lineární seznam (c201)

## Popis úlohy

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