# Laboratorio per il corso di Algoritmi e Strutture Dati

## Esercizio 1 - Merge-BinaryInsertion Sort

### Linguaggio richiesto: C

### Testo

Implementare una libreria che offre un algoritmo di ordinamento  *Merge-BinaryInsertion Sort* su dati generici, implementando il seguente prototipo di funzione:

```c
void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void*, const void*));
```

- `base` è un puntatore al primo elemento dell'array da ordinare;
- `nitems` è il numero di elementi nell'array da ordinare;
- `size` è la dimensione in bytes di ogni elemento dell'array;
- `k` è un parametro dell'algoritmo;
- `compar` è il criterio secondo cui ordinare i dati (dati due **puntatori a elementi** dell'array, restituisce un numero maggiore, uguale o minore di zero se il primo argomento è rispettivamente maggiore, uguale o minore del secondo). 

Con *BinaryInsertion Sort* ci riferiamo a una versione dell'algoritmo *Insertion Sort* in cui la posizione, all'interno della sezione ordinata del vettore, in cui inserire l'elemento corrente è determinata tramite ricerca binaria. Il *Merge-BinaryInsertion Sort* è un algoritmo ibrido che combina *Merge Sort* e *BinaryInsertion Sort*.  L'idea è di approfittare del fatto che il *BinaryInsertion Sort* può essere più veloce del *Merge Sort* quando la sottolista da ordinare è piccola. Ciò suggerisce di considerare una modifica del *Merge Sort* in cui le sottoliste di lunghezza `k` o inferiore sono ordinate usando il  *BinaryInsertion Sort* e sono poi combinate usando il meccanismo tradizionale di fusione del *Merge Sort*. Il valore del parametro `k` dovrà essere studiato e discusso nella relazione. Ad esempio, `k=0` implica che *Merge-BinaryInsertion Sort* si comporta esattamente come il *Merge Sort* classico, mentre `k>>0` aumenta l'utilizzo del *BinaryInsertion Sort*.

In alternativa, è anche ammissibile implementare il seguente prototipo meno generico, che ordina dati a patto che siano organizzati in un array di puntatori:

```
void merge_binary_insertion_sort(void **base, size_t nitems, size_t k, int (*compar)(const void*, const void*));
```

- `base` è un puntatore al primo elemento dell'array di puntatori da ordinare sulla base dei valori riferiti;
- `nitems` è il numero di elementi nell'array di puntatori da ordinare;
- `k` è un parametro dell'algoritmo;
- `compar` è il criterio secondo cui ordinare i dati (dati due **elementi** dell'array di puntatori).

Dato che la prima versione è anche in grado di ordinare array di puntatori (passando un comparatore opportuno, i cui argomenti saranno puntatori a puntatori ai dati), non serve implementare questa seconda versione se avete già implementato la prima.

### Unit Testing

Implementare gli unit-test per la libreria secondo le indicazioni suggerite nel documento Unit Testing.

### Uso della libreria di ordinamento implementata

Il file `records.csv` che potete trovare (compresso) all'indirizzo:

> [https://datacloud.di.unito.it/index.php/s/X7qC8JSLNRtLxPC](https://datacloud.di.unito.it/index.php/s/X7qC8JSLNRtLxPC)

contiene 20 milioni di record da ordinare.
Ogni record è descritto su una riga e contiene i seguenti campi:

- `id`: (tipo intero) identificatore univoco del record;
- `field1`: (tipo stringa) contiene parole estratte dalla divina commedia,
  potete assumere che i valori non contengano spazi o virgole;
- `field2`: (tipo intero);
- `field3`: (tipo floating point).

Il formato è un CSV standard: i campi sono separati da virgole; i record sono
separati da `\n`.

Usando l'algoritmo implementato precedentemente, si realizzi la seguente funzione per ordinare *record* contenuti nel file `records.csv` in ordine non decrescente secondo i valori contenuti nei tre campi "field".

```
void sort_records(FILE *infile, FILE *outfile, size_t k, size_t field);
```

- `infile` è il file contenente i record da ordinare;
- `outfile` è il file nel quale salvare i record ordinati (che deve essere diverso da `infile`);
- `k` è un parametro dell'algoritmo;
- `field` può valere 1, 2 o 3 e indica quale dei tre campi deve essere usato per ordinare i record.

Si misurino i tempi di risposta variando il valore di `k`, per ciascuno dei tre field che si possono usare come chiave di ordinamento, e si produca una breve relazione in cui si riportano i risultati ottenuti insieme a un loro commento. Dimostrare nella relazione come il valore di `k` dovrebbe essere scelto nella pratica. Nel caso l'ordinamento si protragga per più di 10 minuti potete interrompere l'esecuzione e riportare un fallimento dell'operazione. I risultati sono quelli che vi sareste aspettati? Se sì, perché? Se no, fate delle ipotesi circa il motivo per cui l'algoritmo non funziona come vi aspettate, verificatele e riportate quanto scoperto nella relazione. I risultati dipendono dal campo usato come chiave di ordinamento?

**Si ricorda che il file `records.csv` NON DEVE ESSERE OGGETTO DI COMMIT SU GIT!**

### Condizioni per la consegna:

- Creare una sottocartella chiamata `ex1` all'interno del repository.
- La consegna deve obbligatoriamente contenere un `Makefile`. Il `Makefile` deve produrre all'interno di `ex1/bin` un file eseguibile chiamato `main_ex1`.
- L'eseguibile `main_ex1` deve ricevere come parametri il percorso del file CSV contenente i record da ordinare, il percorso del file in cui salvare i record ordinati, il valore di `k` e il valore del campo `field` da utilizzare per l'ordinamento. Per esempio:

```bash
$ ./main_ex1 /tmp/data/records.csv /tmp/data/sorted.csv 27 1
```

## Esercizio 2 - SkipList

### Linguaggio richiesto: C

### Testo

Realizzare una struttura dati chiamata *SkipList*. La *SkipList* è un tipo di lista concatenata che memorizza una *lista ordinata* di elementi.

Al contrario delle liste concatenate classiche, la *SkipList* è una struttura dati probabilistica che permette di realizzare l'operazione di ricerca con complessità `O(log n)` in termini di tempo. Anche le operazioni di inserimento e cancellazione di elementi possono essere realizzate in tempo `O(log n)`. Per questa ragione, la *SkipList* è una delle strutture dati che vengono spesso utilizzate per indicizzare dati.

Ogni nodo di una lista concatenata contiene un puntatore all'elemento successivo nella lista. Dobbiamo quindi scorrere la lista sequenzialmente per trovare un elemento nella lista. La *SkipList* velocizza l'operazione di ricerca creando delle "vie espresse" che permettono di saltare parte della lista durante l'operazione di ricerca. Questo è possibile perché ogni nodo della *SkipList* contiene non solo un singolo puntatore al prossimo elemento della lista, ma un array di puntatori che ci permettono di saltare a diversi punti seguenti nella lista. Un esempio di questo schema è rappresentato nella seguente figura:

![Esempio di una *SkipList*. Dal nodo che contiene il numero 6 si può saltare direttamente ai nodi 9 e 25, senza visitare gli altri nodi.](skiplist.png)

Si implementi quindi una libreria che realizza la struttura dati *SkipList* implementando la seguente dichiarazione:

```c
struct SkipList;
```

L'implementazione deve essere generica per quanto riguarda il tipo dei dati memorizzati nella struttura. Come suggerimento, una possibile definizione del tipo di dati *SkipList* è il seguente:

```c
struct SkipList {
  struct Node **heads;
  size_t max_level;
  size_t max_height;
  int (*compare)(const void*, const void*);
};

struct Node {
  struct Node **next;
  size_t size;
  void *item;
};
```

Dove:

- `heads` sono i puntatori di inizio della *SkipList* per ogni livello fino a `max_height`;
- `max_level` è il massimo numero di puntatori che **al momento ci sono** in un singolo nodo della *SkipList* (come si vede nella figura, ogni nodo può avere un numero distinto di puntatori);
- `max_height` è una costante che definisce il massimo numero di puntatori che **possono esserci** in un singolo nodo della *SkipList*;
- `compar` è il criterio secondo cui ordinare i dati (dati due puntatori a elementi);
- `next` è l'array di puntatori in un dato nodo della *SkipList*;
- `size` è il numero di puntatori in un dato nodo della *SkipList*;
- `item` è il dato memorizzato in un dato nodo della *SkipList*.

La libreria deve implementare tutte le seguenti dichiarazioni.

```c
void new_skiplist(struct SkipList **list, size_t max_height, int (*compar)(const void*, const void*));

void clear_skiplist(struct SkipList **list);

void insert_skiplist(struct SkipList *list, void *item);

const void* search_skiplist(struct SkipList *list, void *item);
```

##### newSkipList: alloca una skiplist vuota

La funzione deve allocare una nuova skiplist, data l'altezza massima e la funzione di confronto, salvando la locazione di memoria allocata in `*list`.

##### clearSkipList: dealloca una skiplist

La funzione deve liberare correttamente tutta la memoria allocata per la *SkipList*, inclusi tutti i nodi interni e i dati in essi contenuti. L'utilizzo inteso di queste prime due funzioni è ad esempio:

```c
struct Skiplist *list = NULL;
new_skiplist(&list, 10, compare);
// ora list != NULL, posso usarla
// per inserire elementi: insert_skiplist(list, ptr); 
// per cercare elementi: search_skiplist(list, ptr) != NULL; 
clear_skiplist(&list);
// ora list == NULL e tutta la memoria è libera
```

##### insertSkipList: inserisce un elemento nella skiplist

La funzione deve inserire un certo elemento `item` nella skiplist `list`. L'elemento da inserire viene fornito come puntatore ad un dato generico, la cui "responsabilità" viene passata alla skiplist (che quindi dovrà deallocarlo quando verrà deallocata la skiplist). Una possibile implementazione di questa funzione in pseudo-codice (da tradurre quindi in C) è la seguente:

```c
insertSkipList(list, item):
    new = createNode(item, randomLevel(list->max_height))
    if new->size > list->max_level:
        list->max_level = new->size

    x = list->heads
    for k = list->max_level downto 1:
        if x[k] == NULL or item < x[k]->item:
            if k < new->size:
              new->next[k] = x[k]
              x[k] = new
        else:
            x = x[k]->next
            k++
```

La funzione `randomLevel()` nel codice precedente determina il numero di puntatori da includere nel nuovo nodo e deve essere realizzata conformemente al seguente algoritmo. Spiegare il vantaggio di questo algoritmo nella relazione da consegnare con l'esercizio:

```c
randomLevel(max_height):
    lvl = 1

    // random() returns a random value in [0...1)
    while random() < 0.5 and lvl < max_height:
        lvl = lvl + 1
    return lvl
```

#####  searchSkipList: verifica se un elemento è presente nella skiplist

La funzione deve verificare se un elemento con valore uguale ad  `item` è presente nella skiplist `list`; restituendo `NULL` se nessuna corrispondenza viene trovata, e restituendo il puntatore all'elemento `item` memorizzato nella skiplist altrimenti. Una possibile implementazione di questa funzione in pseudo-codice (da tradurre quindi in C) è la seguente:

```c
searchSkipList(list, item):
    x = list->heads

    // loop invariant: x[i]->item <= item or item < first element of level i in list
    for i = list->max_level downto 1:
        while x[i]->next[i] != NULL and x[i]->next[i]->item <= item:
            x = x[i]->next

    // loop end: x[1]->item <= item or item < first element in list
    if x[1]->item == item then
        return x[1]->item
    else
        return failure
```

### Unit Testing

Implementare gli unit-test per tutte le operazioni della *SkipList* secondo le indicazioni suggerite nel documento Unit Testing.

### Uso delle funzioni implementate

All'indirizzo:

> [https://datacloud.di.unito.it/index.php/s/gfoEndRSfwQKiHS](https://datacloud.di.unito.it/index.php/s/gfoEndRSfwQKiHS)

potete trovare un dizionario (`dictionary.txt`) e un file da correggere (`correctme.txt`).

Il dizionario contiene un elenco di parole. Le parole sono scritte di seguito, ciascuna su una riga.

Il file `correctme.txt` contiene un testo da correggere. Alcune parole in questo testo non ci sono nel dizionario.

Si implementi una applicazione che usa la struttura dati *SkipList* per determinare in maniera efficiente la lista di parole nel testo da correggere non presenti nel dizionario dato come input al programma. L'applicazione deve implementare la seguente dichiarazione:

```c
void find_errors(FILE *dictfile, FILE *textfile, size_t max_height);
```

- `dictfile` è il percorso del file contenente le parole del dizionario;
- `textfile` è il percorso del file contenente il testo da correggere;
- `max_height` è il parametro della *SkipList*;
- la funzione deve stampare a schermo le parole del testo non presenti nel dizionario, nell'ordine con cui appaiono nel testo da correggere.

Si sperimenti il funzionamento dell'applicazione considerando diversi valori per il parametro `max_height`, riportando in una breve relazione (circa una pagina) i risultati degli esperimenti.

**Si ricorda che i file `dictionary.txt` e `correctme.txt` NON DEVONO ESSERE OGGETTO DI COMMIT SU GIT!**

### Condizioni per la consegna:

- Creare una sottocartella chiamata `ex2` all'interno del repository.
- La consegna deve obbligatoriamente contenere un `Makefile`. Il `Makefile` deve produrre all'interno di `ex2/bin` un file eseguibile chiamato `main_ex2`.
- `main_ex2` deve ricevere come parametri il percorso del dizionario da usare come riferimento, il file da correggere, e la massima altezza `max_height`, in quest'ordine. Il risultato va stampato a schermo, con le parole ordinate come nel file da correggere. Per esempio:

```bash
$ ./main_ex2 /tmp/data/dictionary.txt /tmp/data/correctme.txt 2
cinqve
perpeteva
squola
domandrono
vuolessi
corpito
wita
```

## Esercizio 3 - PriorityQueue

### Linguaggio richiesto: Java

### Testo

Si implementi la struttura dati *coda con priorità (PriorityQueue)*.

La struttura dati deve gestire tipi generici e consentire un numero qualunque e non noto a priori di elementi, implementando la seguente interfaccia (con requisiti minimi di complessità):

```java
public interface AbstractQueue<E> {
  public boolean empty(); // controlla se la coda è vuota -- O(1)
  public boolean push(E e); // aggiunge un elemento alla coda -- O(logN)
  public boolean contains(E e); // controlla se un elemento è in coda -- O(1)
  public E top(); // accede all'elemento in cima alla coda -- O(1)
  public void pop(); // rimuove l'elemento in cima alla coda -- O(logN)
  public boolean remove(E e); // rimuove un elemento se presente in coda -- O(logN)
};
```

*Suggerimento*: per implementare i metodi `contains` e `remove` potrebbe essere necessario usare una struttura dati di appoggio oltre allo heap (è ammesso usare strutture dati dalla libreria standard di Java se necessario).

La classe concreta `PriorityQueue<E>` che implementa l'interfaccia dovrebbe avere almeno un costruttore che crea una coda vuota e prende come argomento un `Comparator<E>` da usare per confrontare gli elementi:

```java
PriorityQueue(Comparator<E> comparator)
```

_Nota_: `Comparator` è un'[interfaccia base](https://docs.oracle.com/en/java/javase/20/docs/api/java.base/java/util/Comparator.html) di Java.

### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni suggerite nel documento [Unit Testing](UnitTesting.md).

### Condizioni per la consegna:

- Creare una sottocartella chiamata `ex3-4` all'interno del repository, che conterrà tutte le classi relative a questo esercizio e al seguente, compresi i file di progetto relativi all'IDE Java che avete utilizzato.

## Esercizio 4 - Grafi sparsi e foreste ricoprenti minime

### Linguaggio richiesto: Java

### Testo

Si implementi una libreria che realizza la struttura dati *Grafo* in modo che sia ottimale per dati sparsi
(**attenzione**: le scelte implementative che farete dovranno essere giustificate in relazione alle nozioni presentate
durante le lezioni in aula).

L'implementazione deve essere generica sia per quanto riguarda il tipo dei nodi, sia per quanto riguarda le etichette
degli archi, implementando la seguente interfaccia (con requisiti minimi di complessità; dove _N_ può indicare il numero di nodi o il numero di archi, a seconda del contesto):

```java
public interface AbstractGraph<V,L> {
  public boolean isDirected(); // dice se il grafo è diretto o meno -- O(1)
  public boolean isLabelled(); // dice se il grafo è etichettato o meno -- O(1)
  public boolean addNode(V a); // aggiunge un nodo -- O(1)
  public boolean addEdge(V a, V b, L l); // aggiunge un arco dati estremi ed etichetta -- O(1)
  public boolean containsNode(V a); // controlla se un nodo è nel grafo -- O(1)
  public boolean containsEdge(V a, V b); // controlla se un arco è nel grafo -- O(1) (*)
  public boolean removeNode(V a); // rimuove un nodo dal grafo -- O(N)
  public boolean removeEdge(V a, V b); // rimuove un arco dal grafo -- O(1) (*)
  public int numNodes(); // numero di nodi -- O(1)
  public int numEdges(); // numero di archi -- O(N)
  public Collection<V> getNodes(); // recupero dei nodi del grafo -- O(N)
  public Collection<? extends AbstractEdge<V,L>> getEdges(); // recupero degli archi del grafo -- O(N)
  public Collection<V> getNeighbours(V a); // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)
  public L getLabel(V a, V b); // recupero dell'etichetta di un arco -- O(1) (*)
};
```

_(*)_ quando il grafo è veramente sparso, assumendo che l'operazione venga effettuata su un nodo la cui lista di adiacenza ha una lunghezza in O(1).

_Nota_: `AbstractCollection` è un'[interfaccia base](https://docs.oracle.com/en/java/javase/20/docs/api/java.base/java/util/AbstractCollection.html) di Java.

L'interfaccia `AbstractGraph` si basa sulla seguente interfaccia per la rappresentazione di un arco:

```java
public interface AbstractEdge<V,L> {
  public V getStart(); // il nodo di partenza dell'arco
  public V getEnd(); // il nodo di arrivo dell'arco
  public L getLabel(); // l'etichetta dell'arco
};
```

La classe concreta `Graph<V,L>` che implementa l'interfaccia `AbstractGraph` dovrebbe avere almeno un costruttore che crea un grafo vuoto in complessità O(1) e prende come argomenti due valori booleani per impostare se il grafo è da considerarsi diretto o meno, e se è da considerarsi etichettato o meno:

```java
Graph(boolean directed, boolean labelled)
```

A seconda del valore di questi due parametri, cambierà il comportamento dei metodi per gestire gli archi per tutte le operazioni successive.

*Suggerimento*:  un grafo non diretto può essere rappresentato usando un'implementazione per grafi diretti modificata
per garantire che, per ogni arco *(a,b)* etichettato *w*, presente nel grafo, sia presente nel grafo anche l'arco *(b,a)*
etichettato *w*. Ovviamente, il grafo dovrà mantenere l'informazione che specifica se esso è un grafo diretto o non diretto.
Similmente, un grafo non etichettato può essere rappresentato usando l'implementazione per grafi etichettati modificata per garantire
che le etichette siano sempre `null` (che invece non devono mai essere `null` per i grafi etichettati).

### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni suggerite nel documento [Unit Testing](UnitTesting.md).

### Uso della libreria che implementa la struttura dati Grafo

Si implementi l'algoritmo di Prim per la determinazione della minima foresta ricoprente di un grafo, secondo il seguente template:

```java
public class Prim {
  public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
    // calcola la minima foresta ricoprente con l'algoritmo di Prim
    // restituisce la collezione degli archi che formano la foresta
  }
  public static void main(String[] args) {
    // leggi i dati CSV del grafo dal percorso in args[1] 
    // calcola la minima foresta ricoprente con minimumSpanningForest
    // scrivi su standard output solo la descrizione della foresta calcolata come CSV con formato analogo a quello in input
    // su standard error si possono scrivere ulteriori informazioni, come il numero di nodi e archi nella foresta calcolata,
    // o il peso totale della foresta
  }
}
```

L'implementazione dell'algoritmo di Prim dovrà utilizzare la struttura dati *PriorityQueue* implementata nell'esercizio precedente e la struttura dati grafo appena implementata.
La struttura dati e l'algoritmo di Prim dovranno poi essere utilizzati con i dati contenuti nel file `italian_dist_graph.csv`, che potete recuperare all'indirizzo:

> [https://datacloud.di.unito.it/index.php/s/PirTJpq4JMnpH3G](https://datacloud.di.unito.it/index.php/s/PirTJpq4JMnpH3G)

Tale file contiene le distanze in metri tra varie località italiane e una frazione delle località a loro più vicine. Il formato è un CSV standard: i campi sono separati da virgole; i record sono separati dal carattere di fine riga (`\n`).

Ogni record contiene i seguenti dati:

- `place1`: (tipo stringa) nome della località "sorgente" (la stringa può contenere spazi ma non può contenere virgole);
- `place2`: (tipo stringa) nome della località "destinazione" (la stringa può contenere spazi ma non può contenere virgole);
- `distance`: (tipo float) distanza in metri tra le due località.

**Note:**

- Nel caso in cui il grafo sia costituito da una sola componente connessa, l'algoritmo restituirà un albero. Nel caso in cui, invece, vi siano più componenti connesse, l'algoritmo restituirà una foresta costituita dai minimi alberi ricoprenti di ciascuna componente connessa.
- Potete intrepretare le informazioni presenti nelle righe del file come archi **non diretti** (per cui probabilmente vorrete inserire nel vostro grafo sia l'arco di andata che quello di ritorno a fronte di ogni riga letta).
- Il file è stato creato a partire da un dataset poco accurato. I dati riportati contengono inesattezze e imprecisioni.
- Un'implementazione corretta dell'algoritmo di Prim, eseguita sui dati contenuti nel file `italian_dist_graph.csv`, dovrebbe determinare una minima foresta ricoprente con 18.640 nodi, 18.637 archi (non orientati) e di peso complessivo di circa 89.939,913 Km.

**Si ricorda che il file `italian_dist_graph.csv` NON DEVE ESSERE OGGETTO DI COMMIT SU GIT!**

### Condizioni per la consegna:

- Creare una sottocartella chiamata `ex3-4` all'interno del repository, che conterrà tutte le classi relative a questo esercizio e al precedente, compresi i file di progetto relativi all'IDE Java che avete utilizzato.
