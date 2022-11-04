/**
 * @file iter/btree.c
 * @author Onegenimasu <https://github.com/Onegenimasu>
 * @brief Binárny vyhľadávací strom — iteratívna varianta
 * @date 2022-11-04
 *
 */

#include "../btree.h"
#include "stack.h"
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
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
bool bst_search(bst_node_t *tree, char key, int *value) {
	// Strom je prázdny - nie je kde hľadať
	if (tree == NULL) {
		return false;
	}

	bst_node_t *currentNode = tree;
	bool found = false;

	// Iteratívne hľadanie uzla
	while (!found) {
		char currentKey = tree->key;
		bool hasLeftSubtree = currentNode->left != NULL;
		bool hasRightSubtree = currentNode->right != NULL;

		if (key == currentKey) {
			// Zhodný kľúč - uzol nájdený
			*value = currentNode->value;
			found = true;
		} else if (key < currentKey && hasLeftSubtree) {
			// Prechod do ľavého podstromu
			currentNode = currentNode->left;
		} else if (key > currentKey && hasRightSubtree) {
			// Prechod do pravého podstromu
			currentNode = currentNode->right;
		} else {
			// Uzol nebol nájdený
			break;
		}
	}

	return found;
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
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_insert(bst_node_t **tree, char key, int value) {
	// Alokovanie nového uzla
	bst_node_t *newNode = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (newNode == NULL) {
		return; // Chyba alokácie pamäte
	}

	// Nastavenie hodnôt uzla
	newNode->key = key;
	newNode->value = value;
	newNode->left = newNode->right = NULL;

	// Strom je prázdny - vloženie uzla ako koreň
	if (*tree == NULL) {
		*tree = newNode;
		return;
	}

	bst_node_t *currentNode = *tree;
	bool done = false;

	// Iteratívne vloženie do podstromu
	while (!done) {
		char currentKey = currentNode->key;
		bool hasLeftSubtree = currentNode->left != NULL;
		bool hasRightSubtree = currentNode->right != NULL;

		// Zhodný kľúč - uzol nájdený
		if (key == currentKey) {
			// Nahradenie hodnoty
			currentNode->value = value;
			free(newNode); // Nie je potrebný nový uzol
			done = true;
		}

		// Ľavý podstrom
		if (key < currentKey) {
			if (hasLeftSubtree) {
				// Prechod do ľavého podstromu
				currentNode = currentNode->left;
			} else {
				// Nájdený najľavejší uzol - vloženie
				currentNode->left = newNode;
				done = true;
			}
		}

		// Pravý podstrom
		if (key > currentKey) {
			if (hasRightSubtree) {
				// Prechod do pravého podstromu
				currentNode = currentNode->right;
			} else {
				// Nájdený najpravejší uzol - vloženie
				currentNode->right = newNode;
				done = true;
			}
		}
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
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
	// Kontrola, či je strom neprázdny (pre istotu)
	if (*tree == NULL) {
		return;
	}

	bst_node_t *currentNode = *tree;
	bst_node_t *parentNode = NULL;
	bool done = false;

	// Iteratívne hľadanie najpravejšieho uzla
	while (!done) {
		// Nájdený najpravejší potomok
		if (currentNode->right == NULL) {
			// Nahradenie kľúča a hodnoty `target` podľa nájdeného uzla
			target->key = currentNode->key;
			target->value = currentNode->value;

			// Odstránenie uzla
			if (parentNode == NULL) {
				// Odstránenie koreňa stromu
				*tree = currentNode->left;
			} else {
				// Odstránenie uzla z ľavého podstromu
				parentNode->right = currentNode->left;
			}

			// Uvoľnenie pamäte najpravejšieho potomka
			free(currentNode);
			done = true;
		} else {
			// Prechod do pravého podstromu
			parentNode = currentNode;
			currentNode = currentNode->right;
		}
	}
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
 * Funkciu implementujte iteratívne pomocou bst_replace_by_rightmost a bez
 * použitia vlastných pomocných funkcií.
 */
void bst_delete(bst_node_t **tree, char key) {
	// Koreň stromu je prázdny
	if (*tree == NULL) {
		return;
	}

	bst_node_t *currentNode = *tree;
	bst_node_t *parentNode = NULL;
	bool done = false;

	// Iteratívne nájdenie a odstránenie uzla
	while (!done) {
		// Bol prevedený prechod na neexistujúci uzol
		if (currentNode == NULL) {
			return;
		}

		char currentKey = currentNode->key;
		bool hasLeftSubtree = currentNode->left != NULL;
		bool hasRightSubtree = currentNode->right != NULL;

		// Zhodný kľúč - odstránenie uzla
		if (key == currentKey) {
			bool isLeftChild = parentNode != NULL && parentNode->left->key == currentNode->key;
			bool isRightChild = parentNode != NULL && parentNode->right->key == currentNode->key;

			// Uzol nemá potomkov
			if (!hasLeftSubtree && !hasRightSubtree) {
				free(currentNode);

				// Odstránenie ukazateľa z rodičovského uzla
				if (isLeftChild) {
					parentNode->left = NULL;
				} else if (isRightChild) {
					parentNode->right = NULL;
				} else {
					*tree = NULL; // Žiadny rodič - odstránenie koreňa
				}
			}

			// Uzol má jeden podstrom
			if (hasLeftSubtree ^ hasRightSubtree) {
				bst_node_t *replacementNode = hasLeftSubtree ? currentNode->left : currentNode->right;
				free(currentNode);

				// Odstránenie ukazateľa z rodičovského uzla
				if (isLeftChild) {
					parentNode->left = replacementNode;
				} else if (isRightChild) {
					parentNode->right = replacementNode;
				} else {
					*tree = replacementNode; // Žiadny rodič - koreň
				}
			}

			// Uzol má podstromy na oboch stranách
			if (hasLeftSubtree && hasRightSubtree) {
				bst_replace_by_rightmost(currentNode, &(currentNode->left));
			}
			done = true;
		}

		// Prechod do pravého podstromu
		if (key > currentKey) {
			parentNode = currentNode;
			currentNode = currentNode->right;
		}

		// Prechod do ľavého podstromu
		if (key < currentKey) {
			parentNode = currentNode;
			currentNode = currentNode->left;
		}
	}
}

/*
 * Zrušenie celého stromu.
 *
 * Po zrušení sa celý strom bude nachádzať v rovnakom stave ako po
 * inicializácii. Funkcia korektne uvoľní všetky alokované zdroje rušených
 * uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_dispose(bst_node_t **tree) {
	// Prázdny strom - nie je čo rušiť
	if (*tree == NULL) {
		return;
	}

	// Inicializácia zásobníku
	stack_bst_t *stack = (stack_bst_t *)malloc(sizeof(stack_bst_t));
	if (stack == NULL) {
		return; // Chyba alokácie pamäte
	}
	stack_bst_init(stack);

	// Pridanie koreňa stromu do zásobníka
	stack_bst_push(stack, *tree);

	// Iteratívne pridávanie uzlov do zásobníka a uvoľňovanie ich pamäte
	while (!stack_bst_empty(stack)) {
		bst_node_t *currentNode = stack_bst_pop(stack);
		if (currentNode == NULL) {
			continue;
		}

		// Pridanie ľavého potomka do zásobníka
		if (currentNode->left != NULL) {
			stack_bst_push(stack, currentNode->left);
		}

		// Pridanie pravého potomka do zásobníka
		if (currentNode->right != NULL) {
			stack_bst_push(stack, currentNode->right);
		}

		// Uvoľnenie pamäte
		free(currentNode);
	}

	*tree = NULL;
	free(stack);
}

/*
 * Pomocná funkcia pre iteratívny preorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu.
 * Nad spracovanými uzlami zavola bst_print_node a uloží ich do zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit) {
	bst_node_t *currentNode = tree;

	while (currentNode != NULL) {
		bst_print_node(currentNode);

		// Pridanie uzla do zásobníka
		stack_bst_push(to_visit, currentNode);

		// Prechod do ľavého podstromu
		currentNode = currentNode->left;
	}
}

/*
 * Preorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_preorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_preorder(bst_node_t *tree) {
	// Prázdny strom - nie je čo prechádzať
	if (tree == NULL) {
		return;
	}

	// Preorder tree walk: koreň -> ľavý podstrom -> pravý podstrom
	// Inicializácia zásobníku
	stack_bst_t *stack = (stack_bst_t *)malloc(sizeof(stack_bst_t));
	if (stack == NULL) {
		return; // Chyba alokácie pamäte
	}
	stack_bst_init(stack);

	// Prechod k najľavejšiemu uzlu
	bst_node_t *currentNode = tree;
	bst_leftmost_preorder(currentNode, stack);

	while (!stack_bst_empty(stack)) {
		currentNode = stack_bst_pop(stack);

		// Prechod do pravého podstromu
		if (currentNode->right != NULL) {
			bst_leftmost_preorder(currentNode->right, stack);
		}
	}

	free(stack);
}

/*
 * Pomocná funkcia pre iteratívny inorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit) {
	bst_node_t *currentNode = tree;

	while (currentNode != NULL) {
		// Pridanie uzla do zásobníka
		stack_bst_push(to_visit, currentNode);

		// Prechod do ľavého podstromu
		currentNode = currentNode->left;
	}
}

/*
 * Inorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_inorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_inorder(bst_node_t *tree) {
	// Prázdny strom - nie je čo prechádzať
	if (tree == NULL) {
		return;
	}

	// Inorder tree walk: ľavý podstrom -> koreň -> pravý podstrom
	// Inicializácia zásobníku
	stack_bst_t *stack = (stack_bst_t *)malloc(sizeof(stack_bst_t));
	if (stack == NULL) {
		return; // Chyba alokácie pamäte
	}
	stack_bst_init(stack);

	// Prechod k najľavejšiemu uzlu
	bst_node_t *currentNode = tree;
	bst_leftmost_inorder(currentNode, stack);

	while (!stack_bst_empty(stack)) {
		currentNode = stack_bst_pop(stack);
		bst_print_node(currentNode);

		// Prechod do pravého podstromu
		if (currentNode->right != NULL) {
			bst_leftmost_inorder(currentNode->right, stack);
		}
	}

	free(stack);
}

/*
 * Pomocná funkcia pre iteratívny postorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov. Do zásobníku bool hodnôt ukladá informáciu že uzol
 * bol navštívený prvý krát.
 *
 * Funkciu implementujte iteratívne pomocou zásobníkov uzlov a bool hodnôt a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit, stack_bool_t *first_visit) {
	bst_node_t *currentNode = tree;

	while (currentNode != NULL) {
		// Pridanie uzla do zásobníka
		stack_bst_push(to_visit, currentNode);
		stack_bool_push(first_visit, true);

		// Prechod do ľavého podstromu
		currentNode = currentNode->left;
	}
}

/*
 * Postorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_postorder a
 * zásobníkov uzlov a bool hodnôt bez použitia vlastných pomocných funkcií.
 */
void bst_postorder(bst_node_t *tree) {
	// Prázdny strom - nie je čo prechádzať
	if (tree == NULL) {
		return;
	}

	// Postorder tree walk: ľavý podstrom -> pravý podstrom -> koreň
	// Inicializácia zásobníkov
	stack_bst_t *stack = (stack_bst_t *)malloc(sizeof(stack_bst_t));
	if (stack == NULL) {
		return; // Chyba alokácie pamäte
	}
	stack_bst_init(stack);

	stack_bool_t *bStack = (stack_bool_t *)malloc(sizeof(stack_bool_t));
	if (bStack == NULL) {
		return; // Chyba alokácie pamäte
	}
	stack_bool_init(bStack);

	// Prechod k najľavejšiemu uzlu
	bst_node_t *currentNode = tree;
	bst_leftmost_postorder(currentNode, stack, bStack);

	while (!stack_bst_empty(stack)) {
		currentNode = stack_bst_pop(stack);
		bool firstVisit = stack_bool_pop(bStack);

		if (firstVisit) {
			// Uzol bol navštívený prvý krát - uloženie do zásobníka
			stack_bst_push(stack, currentNode);
			stack_bool_push(bStack, false);

			// Prechod do pravého podstromu
			if (currentNode->right != NULL) {
				bst_leftmost_postorder(currentNode->right, stack, bStack);
			}
		} else {
			// Uzol už bol navštívený - výpis
			bst_print_node(currentNode);
		}
	}

	// Uvoľnenie pamäte zásobníkov
	free(stack);
	free(bStack);
}
