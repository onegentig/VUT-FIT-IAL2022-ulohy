# IAL — Fronta znaků v poli (c203)

## Popis úlohy

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

## Funkce

* **`void Queue_Init(Queue *queue)`** : Inicializuje frontu `queue` nastavením všech hodnot v poli `queue->array` na `*` a obou indexů na 0. Pokud je ukazatel na frontu neplatný (*NULL*), volá `Queue_Error(QERR_INIT)`.
* **`int nextIndex(int index)`** : Vrací index následujícího prvku v poli (implementujte jako jediný příkaz využívající operátor `%`).
* **`int Queue_IsEmpty(const Queue *queue)`** : Vrací 1, pokud je fronta prázdná, jinak 0.
* **`int Queue_IsFull(const Queue *queue)`** : Vrací 1, pokud je fronta plná, jinak 0.
* **`void Queue_Front(const Queue *queue, char *dataPtr)`** : Vloží ukazatele prvního prvku fronty `queue` do proměnné `dataPtr`. Pokud je fronta prázdná, volá `Queue_Error(QERR_FRONT)`. Při implementaci využijte funkci `Queue_IsEmpty`.
* **`void Queue_Remove(Queue *queue)`** : Odstraní první prvek fronty `queue`. Pokud je fronta prázdná, volá `Queue_Error(QERR_REMOVE)`. Při implementaci využijte funkce `Queue_IsEmpty` a `nextIndex`.
* **`void Queue_Enqueue(Queue *queue, char data)`** : Vloží hodnotu proměnné `data` na konec fronty `queue`. Pokud je fronta plná, volá `Queue_Error(QERR_ENQUEUE)`. Při implementaci využijte funkce `Queue_IsFull` a `nextIndex`.
* **`void Queue_Dequeue(Queue *queue, char *dataPtr)`** : Vloží ukazatele na poslední prvek fronty `queue` do proměnné `dataPtr` a odstraní tenhle prvek z fronty. Pokud je fronta prázdná, volá `Queue_Error(QERR_DEQUEUE)`. Při implementaci využijte funkce `Queue_IsEmpty`, `Queue_Front` a `Queue_Remove`.

### Poznámky

* V poli je vždy minimálně jeden prvek nevyužitý.
* Při libovolné operaci se žádný z indexů nesnižuje, vyjma případu, kdy index přesáhne hranici `QUEUE_SIZE`. V tom případě se "posunuje" znovu na začátek pole. Za tímto účelem budete deklarovat pomocnou funkci `nextIndex`, která pro kruhový pohyb přes indexy pole využívá operaci "modulo".
* Při implementaci funkcí nevolejte žádnou z funkcí impelmentovaných v rámci tohoto příkladu, není-li to u dané funkce explicitně uvedeno.
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