/**
 * @file rec/btree.c
 * @author Onegenimasu <https://github.com/Onegenimasu>
 * @brief Binárny vyhľadávací strom — rekurzívna varianta
 * @date 2022-xx-xx
 *
 */

#include "../btree.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializácia stromu.
 *
 * Užívateľ musí zaistiť, že incializácia sa nebude opakovane volať nad
 * inicializovaným stromom. V opačnom prípade môže dôjsť k úniku pamäte (memory
 * leak). Keďže neinicializovaný ukazovateľ má nedefinovanú hodnotu, nie je
 * možné toto detegovať vo funkcii.
 */
void bst_init(bst_node_t **tree) {
	*tree = NULL;
}

/*
 * Nájdenie uzlu v strome.
 *
 * V prípade úspechu vráti funkcia hodnotu true a do premennej value zapíše
 * hodnotu daného uzlu. V opačnom prípade funckia vráti hodnotu false a premenná
 * value ostáva nezmenená.
 *
 * Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
 */
bool bst_search(bst_node_t *tree, char key, int *value) {
	// Strom je prázdny
	if (tree == NULL) {
		return false;
	}

	char currentKey = tree->key;

	// Uzol nájdený
	if (currentKey == key) {
		*value = tree->value;
		return true;
	}

	// Rekurzívne vyhľadávanie v ľavom podstrome
	if (currentKey > key) {
		return bst_search(tree->left, key, value);
	}

	// Rekurzívne vyhľadávanie v pravom podstrome
	if (currentKey < key) {
		return bst_search(tree->right, key, value);
	}

	return false;
}

/*
 * Vloženie uzlu do stromu.
 *
 * Pokiaľ uzol so zadaným kľúčom v strome už existuje, nahraďte jeho hodnotu.
 * Inak vložte nový listový uzol.
 *
 * Výsledný strom musí spĺňať podmienku vyhľadávacieho stromu — ľavý podstrom
 * uzlu obsahuje iba menšie kľúče, pravý väčšie.
 *
 * Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
 */
void bst_insert(bst_node_t **tree, char key, int value) {
	// Vložiť uzol ako koreň stromu
	if (*tree == NULL) {
		bst_node_t *newNode = (bst_node_t *)malloc(sizeof(bst_node_t));
		if (newNode == NULL) {
			return; // Chyba alokácie pamäte
		}

		// Vloženie nového uzla
		newNode->key = key;
		newNode->value = value;
		newNode->left = NULL;
		newNode->right = NULL;
		*tree = newNode;
		return;
	}

	// Aktuálny kľúč
	char currentKey = (*tree)->key;

	// Zhodný kľúč - nahradenie hodnoty
	if (currentKey == key) {
		(*tree)->value = value;
		return;
	}

	// Rekurzívne vloženie do ľavého podstromu
	if (key < currentKey) {
		bst_insert(&(*tree)->left, key, value);
		return;
	}

	// Rekurzívne vloženie do pravého podstromu
	if (key > currentKey) {
		bst_insert(&(*tree)->right, key, value);
		return;
	}
}

/*
 * Pomocná funkcia ktorá nahradí uzol najpravejším potomkom.
 *
 * Kľúč a hodnota uzlu target budú nahradené kľúčom a hodnotou najpravejšieho
 * uzlu podstromu tree. Najpravejší potomok bude odstránený. Funkcia korektne
 * uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkcia predpokladá že hodnota tree nie je NULL.
 *
 * Táto pomocná funkcia bude využitá pri implementácii funkcie bst_delete.
 *
 * Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
	// Kontrola, či je strom neprázdny (pre istotu)
	if (*tree == NULL) {
		return;
	}

	// Nájdený najpravejší potomok
	if ((*tree)->right == NULL) {
		// Nahradenie kľúča a hodnoty `target` podľa nájdeného uzla
		target->key = (*tree)->key;
		target->value = (*tree)->value;

		// Nastavenie ukazovateľa na podstrom na ľavo od nájdeného uzla
		bst_node_t *temp = *tree;
		*tree = (*tree)->left;

		// Uvoľnenie pamäte najpravejšieho potomka
		free(temp);
		return;
	}

	// Rekurzívne hľadanie najpravejšieho potomka
	bst_replace_by_rightmost(target, &(*tree)->right);
}

/*
 * Odstránenie uzlu v strome.
 *
 * Pokiaľ uzol so zadaným kľúčom neexistuje, funkcia nič nerobí.
 * Pokiaľ má odstránený uzol jeden podstrom, zdedí ho otec odstráneného uzla.
 * Pokiaľ má odstránený uzol oba podstromy, je nahradený najpravejším uzlom
 * ľavého podstromu. Najpravejší uzol nemusí byť listom!
 * Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkciu implementujte rekurzívne pomocou bst_replace_by_rightmost a bez
 * použitia vlastných pomocných funkcií.
 */
void bst_delete(bst_node_t **tree, char key) {
	// Koreň stromu je prázdny
	if (*tree == NULL) {
		return;
	}

	char currentKey = (*tree)->key;
	bool hasLeftSubtree = (*tree)->left != NULL;
	bool hasRightSubtree = (*tree)->right != NULL;

	// Zhodný kľúč - odstránenie uzla
	if (currentKey == key) {

		// Uzol nemá potomkov - list
		if (!hasLeftSubtree && !hasRightSubtree) {
			free(*tree);
			*tree = NULL;
			return;
		}

		// Uzol má jeden podstrom
		if (hasLeftSubtree ^ hasRightSubtree) {
			bst_node_t *temp = *tree;
			*tree = hasLeftSubtree ? (*tree)->left : (*tree)->right;
			free(temp);
			return;
		}

		// Uzol má podstromy na oboch stranách
		if (hasLeftSubtree && hasRightSubtree) {
			bst_replace_by_rightmost(*tree, &(*tree)->left);
			return;
		}
	}

	// Rekurzívne odstránenie z ľavého podstromu
	if (key < currentKey && hasLeftSubtree) {
		bst_delete(&(*tree)->left, key);
		return;
	}

	// Rekurzívne odstránenie z pravého podstromu
	if (key > currentKey && hasRightSubtree) {
		bst_delete(&(*tree)->right, key);
		return;
	}
}

/*
 * Zrušenie celého stromu.
 *
 * Po zrušení sa celý strom bude nachádzať v rovnakom stave ako po
 * inicializácii. Funkcia korektne uvoľní všetky alokované zdroje rušených
 * uzlov.
 *
 * Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
 */
void bst_dispose(bst_node_t **tree) {
	if (*tree == NULL) {
		return;
	}
}

/*
 * Preorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
 */
void bst_preorder(bst_node_t *tree) {
}

/*
 * Inorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
 */
void bst_inorder(bst_node_t *tree) {
}
/*
 * Postorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte rekurzívne bez použitia vlastných pomocných funkcií.
 */
void bst_postorder(bst_node_t *tree) {
}
