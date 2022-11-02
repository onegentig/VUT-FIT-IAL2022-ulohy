# IAL — 2. Domácí Úloha

*(merged zadání; TODO)*

Ve druhém domácím úkolu jsou tři následující příklady:

* `hashtable`: tabuľka s rozptýlenými položkami (3b)
* `btree/rec`: binární vyhledávací strom a operace nad ním implementované rekurzivně (3.5b)
* `btree/iter`: binární vyhledávací strom a operace nad ním implementované iterativně (3.5b)

Vaším úkolem je doplnit těla funkcí v souborech `hashtable/hashtable.c`, `btree/rec/btree.c` a `btree/iter/btree.c` a odevzdat je pomocí [STUDISu](https://moodle.vut.cz/mod/folder/view.php?id=249031) jako archiv tar se zachováním adresářové struktury (nekomprimované v kódování UTF-8).

## Tabuľka s rozptýlenými položkami (hashtable)

```c
// Prvok tabuľky
typedef struct ht_item {
  char *key;            // kľúč prvku
  float value;          // hodnota prvku
  struct ht_item *next; // ukazateľ na ďalšie synonymum
} ht_item_t;
```

```c
// Tabuľka o reálnej veľkosti MAX_HT_SIZE
typedef ht_item_t *ht_table_t[MAX_HT_SIZE];
```

S využitím zadaných dátových typov implementujte tabuľku s rozptýlenými položkami s explicitne zreťazenými synonimami. Za veľkosť tabuľky uvažujte `HT_SIZE`.

### Funkce hashtable

* **`int get_hash(char *key)`** : Rozptyľovacia funkcia, ktorá pridelí zadanému kľúču index z intervalu <0, HT_SIZE - 1>. Ideálna funkcia by mala rozprestriať kľúče rovnomerne po všetkých indexoch.
* **`void ht_init(ht_table_t *table)`** : Inicializácia tabuľky, zavolá sa pred prvým použitím tabuľky.
* **`ht_item_t *ht_search(ht_table_t *table, char *key)`** : Vyhľadanie prvku v tabuľke, vráti ukazateľ na nájdený prvok alebo NULL ak nebol nájdený.
* **`void ht_insert(ht_table_t *table, char *key, float data)`** : Vloženie nového prvku do tabuľky. Pokiaľ je prvok s daným kľúčom už definovaný, nahraďte jeho hodnotu. Pri vkladaní prvku do zoznamu synonym zvoľte najefektívnejšiu možnosť a vložte prvok na začiatok zoznamu. Využite funkciu ht_search().
* **`float *ht_get(ht_table_t *table, char *key)`** : Získanie hodnoty z tabuľky, vráti ukazovateľ na hodnotu prvku alebo NULL ak nebol prvok nájdený. Využite funkciu ht_search().
* **`void ht_delete(ht_table_t *table, char *key)`** : Zmazanie prvku z tabuľky. Funkcia musí korektne uvoľniť alokované zdroje prvku. Ak prvok neexistuje, nič sa nestane. Nepoužívajte ht_search()!
* **`void ht_delete_all(ht_table_t *table)`** : Zmazanie všetkých prvkov tabuľky. Funkcia korektne uvoľnuje alokované zdroje a uvedie ju do stavu po inicializácií.

## Binárny vyhľadávací strom s rekurzivními operacemi (rbtree)

```c
// Uzol stromu
typedef struct bst_node {
  char key;               // kľúč
  int value;              // hodnota
  struct bst_node *left;  // ľavý potomok
  struct bst_node *right; // pravý potomok
} bst_node_t;
```

Implementujte binárny vyhľadávací strom pomocou rekurzie.

### Funkce rbtree

* **`void bst_init(bst_node_t **tree)`** : Inicializácia stromu. Uživateľ musí zaistiť, že inicializácia sa nebude opakovane volať nad inicializovaným stromom, inak môže dôjsť k *memory leak*. Keďže neinicializovaný ukazovateľ má nedefinovanú hodnotu, nie je možné toto detekovať vo funkcií.
* **`void bst_insert(bst_node_t **tree, char key, int value)`** : Vloženie uzlu do stromu. Pokiaľ uzol už existuje, nahraďte jeho hodnotu. Výsledný strom musí byť validný (teda ľavý podstrom uzlu musí obsahovať iba menšie kľúče, pravý iba väčšie); implementujte rekurzívne bez pomocných funkcií.
* **`bool bst_search(bst_node_t *tree, char key, int *value)`** : Nájdenie uzlu v strome, vráti true a zapíše do ukazateľa `int *value` hodnotu nájdeného ukazateľa, alebo false ak uzol nebol nájdený; implementujte rekurzívne bez pomocných funkcií.
* **`void bst_delete(bst_node_t **tree, char key)`** : Odstránenie uzlu v strome. Pokiaľ uzol so zadaným kľúčom neexistuje, funkcia nič nerobí. Pokiaľ má odstránený uzol jeden podstrom, zdedí ho otec odstráneného uzla. Pokiaľ má odstránený uzol oba podstromy, je nahradený najpravejším uzlom ľavého podstromu. Najpravejší uzol nemusí byť listom! Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu. Funkciu implementujte rekurzívne pomocou bst_replace_by_rightmost a bez použitia vlastných pomocných funkcií.
* **`void bst_dispose(bst_node_t **tree)`** : Zrušenie celého stromu. Po zrušení sa celý strom bude nachádzať v rovnakom stave ako po inicializácii. Funkcia korektne uvoľní všetky alokované zdroje rušených uzlov. Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
* **`void bst_preorder(bst_node_t *tree)`** : Preorder prechod stromom. Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node. Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
* **`void bst_inorder(bst_node_t *tree)`** : Inorder prechod stromom. Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node. Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
* **`void bst_postorder(bst_node_t *tree)`** : Postorder prechod stromom. Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node. Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
* **`void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree)`** : Pomocná funkcia, ktorá nahradí uzol najpravejším potomkom. Kľúč a hodnota uzli *target* budú nahradené kľúčom a hodnotou najpravejšieho uzlu podstromu *tree*. Najpravejší potomok bude odstránený. Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu. Funkcia predpokladá že hodnota tree nie je NULL. Táto pomocná funkcia bude využitá pri implementácii funkcie bst_delete. Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.

## Binárny vyhľadávací strom s iterativními operacemi (ibtree)

```c
// Uzol stromu
typedef struct bst_node {
  char key;               // kľúč
  int value;              // hodnota
  struct bst_node *left;  // ľavý potomok
  struct bst_node *right; // pravý potomok
} bst_node_t;
```

Implementujte binárny vyhľadávací strom BEZ rekurzie.

### Funkce ibtree

* **`void bst_init(bst_node_t **tree)`** : Inicializácia stromu. Uživateľ musí zaistiť, že inicializácia sa nebude opakovane volať nad inicializovaným stromom, inak môže dôjsť k *memory leak*. Keďže neinicializovaný ukazovateľ má nedefinovanú hodnotu, nie je možné toto detekovať vo funkcií.
* **`void bst_insert(bst_node_t **tree, char key, int value)`** : Vloženie uzlu do stromu. Pokiaľ uzol už existuje, nahraďte jeho hodnotu. Výsledný strom musí byť validný (teda ľavý podstrom uzlu musí obsahovať iba menšie kľúče, pravý iba väčšie); implementujte iteratívne bez pomocných funkcií.
* **`bool bst_search(bst_node_t *tree, char key, int *value)`** : Nájdenie uzlu v strome, vráti true a zapíše do ukazateľa `int *value` hodnotu nájdeného ukazateľa, alebo false ak uzol nebol nájdený; implementujte iteratívne bez pomocných funkcií.
* **`void bst_delete(bst_node_t **tree, char key)`** : Odstránenie uzlu v strome. Pokiaľ uzol so zadaným kľúčom neexistuje, funkcia nič nerobí. Pokiaľ má odstránený uzol jeden podstrom, zdedí ho otec odstráneného uzla. Pokiaľ má odstránený uzol oba podstromy, je nahradený najpravejším uzlom ľavého podstromu. Najpravejší uzol nemusí byť listom! Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu. Funkciu implementujte iteratívne pomocou bst_replace_by_rightmost a bez použitia vlastných pomocných funkcií.
* **`void bst_dispose(bst_node_t **tree)`** : Zrušenie celého stromu. Po zrušení sa celý strom bude nachádzať v rovnakom stave ako po inicializácii. Funkcia korektne uvoľní všetky alokované zdroje rušených uzlov. Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
* **`void bst_preorder(bst_node_t *tree)`** : Preorder prechod stromom. Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node. Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
* **`void bst_inorder(bst_node_t *tree)`** : Inorder prechod stromom. Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node. Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
* **`void bst_postorder(bst_node_t *tree)`** : Postorder prechod stromom. Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node. Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
* **`void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree)`** : Pomocná funkcia, ktorá nahradí uzol najpravejším potomkom. Kľúč a hodnota uzli *target* budú nahradené kľúčom a hodnotou najpravejšieho uzlu podstromu *tree*. Najpravejší potomok bude odstránený. Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu. Funkcia predpokladá že hodnota tree nie je NULL. Táto pomocná funkcia bude využitá pri implementácii funkcie bst_delete. Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
