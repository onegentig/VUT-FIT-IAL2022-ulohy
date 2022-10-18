/**
 * @file c203.c
 * @author Onegenimasu <https://github.com/Onegenimasu>
 * @brief Implementácia fronty znakov v poli (Character Queue Array ADT)
 * @date 2022-10-12
 *
 */

#include "c203.h"

int QUEUE_SIZE = MAX_QUEUE;
int error_flag;
int solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě.
 * Tato funkce bude volána z některých dále implementovaných operací.
 *
 * TUTO FUNKCI, PROSÍME, NEUPRAVUJTE!
 *
 * @param error_code Interní identifikátor chyby
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
 * Inicializujte frontu následujícím způsobem:
 * - všechny hodnoty v poli queue->array nastavte na '*',
 * - index na začátek fronty nastavte na 0,
 * - index prvního volného místa nastavte také na 0.
 *
 * V případě, že funkce dostane jako parametr queue == NULL, volejte funkci
 * Queue_Error(QERR_INIT).
 *
 * @param queue Ukazatel na strukturu fronty
 */
void Queue_Init(Queue *queue) {
	// Kontrola, či je queue platný ukazateľ
	if (queue == NULL) {
		Queue_Error(QERR_INIT);
		return;
	}

	// Nastavenie indexov na 0
	queue->firstIndex = 0;
	queue->freeIndex = 0;

	// Nastavenie všetkých hodnôt v poli na '*'
	for (int i = 0; i < QUEUE_SIZE; i++) {
		queue->array[i] = '*';
	}
}

/**
 * Pomocná funkce, která vrací index následujícího prvku v poli.
 * Funkci implementujte jako jediný prikaz využívající operace '%'.
 * Funkci nextIndex budete využívat v dalších implementovaných funkcích.
 *
 * @param index Aktuální index
 */
int nextIndex(int index) {
	// Výpočet indexu nasledujúceho prvku so zaistením kruhovosti pola
	return (index + 1) % QUEUE_SIZE;
}

/**
 * Vrací nenulovou hodnotu, pokud je frona prázdná, jinak vrací hodnotu 0.
 * Funkci je vhodné implementovat jedním příkazem return.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 */
int Queue_IsEmpty(const Queue *queue) {
	return queue->firstIndex == queue->freeIndex;
}

/**
 * Vrací nenulovou hodnotu, je-li fronta plná, jinak vrací hodnotu 0.
 * Funkci je vhodné implementovat jedním příkazem return
 * s využitím pomocné funkce nextIndex.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 */
int Queue_IsFull(const Queue *queue) {
	return (nextIndex(queue->freeIndex) == queue->firstIndex ||
			(queue->freeIndex == 0 && queue->firstIndex == MAX_QUEUE - 1));
}

/**
 * Prostřednictvím parametru dataPtr vrátí znak ze začátku fronty queue.
 * Pokud je fronta prázdná, ošetřete to voláním funkce Queue_Error(QERR_FRONT).
 * Volání této funkce při prázdné frontě je vždy nutné považovat za nekorektní.
 * Bývá to totiž důsledek špatného návrhu algoritmu, ve kterém je fronta
 * použita. O takové situaci se proto musí programátor-vývojář dozvědět.
 * V opačném případě je ladění programů obtížnější!
 *
 * Při implementaci využijte dříve definované funkce Queue_IsEmpty.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void Queue_Front(const Queue *queue, char *dataPtr) {
	// Kontrola, či je fronta neprázdna (underflow)
	if (Queue_IsEmpty(queue)) {
		Queue_Error(QERR_FRONT);
		return;
	}

	// Vloženie hodnoty zo začiatku fronty do cielovej premennej
	*dataPtr = queue->array[queue->firstIndex];
}

/**
 * Odstraní znak ze začátku fronty queue. Pokud je fronta prázdná, ošetřete
 * vzniklou chybu voláním funkce Queue_Error(QERR_REMOVE).
 * Hodnotu na uvolněné pozici ve frontě nijak neošetřujte (nepřepisujte).
 * Při implementaci využijte dříve definované funkce Queue_IsEmpty a nextIndex.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 */
void Queue_Remove(Queue *queue) {
	// Kontrola, či je fronta neprázdna (underflow)
	if (Queue_IsEmpty(queue)) {
		Queue_Error(QERR_REMOVE);
		return;
	}

	// Posunutie indexu na "vymazanie" prvku
	queue->firstIndex = nextIndex(queue->firstIndex);
}

/**
 * Odstraní znak ze začátku fronty a vrátí ho prostřednictvím parametru dataPtr.
 * Pokud je fronta prázdná, ošetřete to voláním funkce Queue_Error(QERR_DEQUEUE).
 *
 * Při implementaci využijte dříve definovaných funkcí Queue_IsEmpty,
 * Queue_Front a Queue_Remove.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void Queue_Dequeue(Queue *queue, char *dataPtr) {
	// Kontrola, či je fronta neprázdna (underflow)
	if (Queue_IsEmpty(queue)) {
		Queue_Error(QERR_DEQUEUE);
		return;
	}

	// Vloženie hodnoty zo začiatku fronty do cielovej premennej
	Queue_Front(queue, dataPtr);

	// Odstránenie prvku zo začiatku fronty
	Queue_Remove(queue);
}

/**
 * Vloží znak data do fronty. Pokud je fronta plná, ošetřete chybu voláním
 * funkce Queue_Error(QERR_ENQUEUE). Vkládání do plné fronty se považuje za
 * nekorektní operaci. Situace by mohla být řešena i tak, že by operace
 * neprováděla nic, ale v případě použití takto definované abstrakce by se
 * obtížně odhalovaly chyby v algoritmech, které by abstrakci využívaly.
 *
 * Při implementaci využijte dříve definovaných funkcí Queue_IsFull a nextIndex.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @param data Znak k vložení
 */
void Queue_Enqueue(Queue *queue, char data) {
	// Kontrola, či fronta nie je plná (overflow)
	if (Queue_IsFull(queue)) {
		Queue_Error(QERR_ENQUEUE);
		return;
	}

	// Vloženie znaku do fronty na volnú pozíciu
	queue->array[queue->freeIndex] = data;

	// Nastavenie indexu na ďalšiu volnú pozíciu
	queue->freeIndex = nextIndex(queue->freeIndex);
}

/* Konec c203.c */
