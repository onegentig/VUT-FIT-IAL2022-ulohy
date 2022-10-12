/**
 * @file c203.c
 * @author GitHub User (xplagi00@stud.fit.vutbr.cz)
 * @brief Implementace fronty znaků v poli (Character Queue Array ADT)
 * @date 2022-10-12
 *
 */

#include "c203.h"

int QUEUE_SIZE = MAX_QUEUE;
int error_flag;
int solved;

/**
 * @brief Vytiskne upozornění na to, že došlo k chybě a nastaví error_flag na 1
 * @param error_code Interní identifikátor chyby
 *
 */
void Queue_Error(int error_code) {
	static const char *QERR_STRINGS[MAX_QERR + 1] = {"Unknown error",		 "Queue error: ENQUEUE",
													 "Queue error: FRONT",	 "Queue error: REMOVE",
													 "Queue error: DEQUEUE", "Queue error: INIT"};

	if (error_code <= 0 || error_code > MAX_QERR) {
		error_code = 0;
	}
	printf("%s\n", QERR_STRINGS[error_code]);
	error_flag = 1;
}

/**
 * @brief Inicializuje frontu
 * @param queue Ukazatel na strukturu fronty
 *
 */
void Queue_Init(Queue *queue) {
	// Kontrola, zda je ukazatelem platný
	if (queue == NULL) {
		Queue_Error(QERR_INIT);
		return;
	}

	// Nastavení indexů na 0
	queue->firstIndex = 0;
	queue->freeIndex = 0;

	// Nastavení všech hodnot v poli na '*'
	for (int i = 0; i < QUEUE_SIZE; i++) {
		queue->array[i] = '*';
	}
}

/**
 * @brief Vrací index následujícího prvku v poli
 * @param index Aktuální index
 * @return Index následujícího prvku
 *
 */
int nextIndex(int index) {
	// Výpočet indexu následujícího prvku se zajištěním kruhovitosti pole
	return (index + 1) % QUEUE_SIZE;
}

/**
 * @brief Zjistí, zda je fronta prázdná
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @return Nenulová hodnota, pokud je fronta prázdná, jinak 0
 *
 */
int Queue_IsEmpty(const Queue *queue) {
	return queue->firstIndex == queue->freeIndex;
}

/**
 * @brief Zjistí, zda je fronta plná
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @return Nenulová hodnota, pokud je fronta plná, jinak 0
 *
 */
int Queue_IsFull(const Queue *queue) {
	return (nextIndex(queue->freeIndex) == queue->firstIndex ||
			(queue->freeIndex == 0 && queue->firstIndex == MAX_QUEUE - 1));
}

/**
 * @brief Vloží znak ze začátku fronty do ukazatele
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @param dataPtr Ukazatel na cílovou proměnnou
 *
 */
void Queue_Front(const Queue *queue, char *dataPtr) {
	// Kontrola, zda je fronta neprázdná
	if (Queue_IsEmpty(queue)) {
		Queue_Error(QERR_FRONT);
		return;
	}

	// Vložení hodnoty ze začátku fronty do cílové proměnné
	*dataPtr = queue->array[queue->firstIndex];
}

/**
 * @brief Odstraní znak ze začátku fronty
 * @param queue Ukazatel na inicializovanou strukturu fronty
 *
 */
void Queue_Remove(Queue *queue) {
	// Kontrola, zda je fronta neprázdná (underflow)
	if (Queue_IsEmpty(queue)) {
		Queue_Error(QERR_REMOVE);
		return;
	}

	// Přesunutí indexu pro "odstranění" prvku
	queue->firstIndex = nextIndex(queue->firstIndex);
}

/**
 * @brief Odstraní znak ze začátku fronty a vloží jej do ukazatele
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @param dataPtr Ukazatel na cílovou proměnnou
 *
 */
void Queue_Dequeue(Queue *queue, char *dataPtr) {
	// Kontrola, zda je fronta neprázdná (underflow)
	if (Queue_IsEmpty(queue)) {
		Queue_Error(QERR_DEQUEUE);
		return;
	}

	// Vložení hodnoty ze začátku fronty do cílové proměnné
	Queue_Front(queue, dataPtr);

	// Odstranění prvku ze začátku fronty
	Queue_Remove(queue);
}

/**
 * @brief Vloží znak data do fronty
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @param data Znak k vložení
 *
 */
void Queue_Enqueue(Queue *queue, char data) {
	// Kontrola, zda fronta není plná (overflow)
	if (Queue_IsFull(queue)) {
		Queue_Error(QERR_ENQUEUE);
		return;
	}

	// Vložení znaku do fronty na volnou pozici
	queue->array[queue->freeIndex] = data;

	// Nastavení indexu na další volnou pozici
	queue->freeIndex = nextIndex(queue->freeIndex);
}