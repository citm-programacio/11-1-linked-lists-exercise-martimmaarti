/*Starting with the class structure given in the previous slides

Implement the push_back function:
    void push_back (const int &value) {...}
Implement the insert function:
    void insert (unsigned int position, const int &value) {...}
Implement the print function. It prints the whole list from beginning to end:
    void print () {...}
From the main function, insert 5 elements in different positions and print the whole list after each insertion*/

#include <iostream>
using namespace std;

class List {
public:
    // Constructor
    List() : first(nullptr), last(nullptr), num_elems(0) {
        first = last = nullptr;
    }
    //destructor
    ~List() {
        clear(); // Libera los recursos asociados a la lista
    }

    // Modifiers
    void push_back(const int &value);
    void insert(unsigned int position, const int &value); //const = su valor no puede ser modificado ni cambiado a través de esa variable. por ejemplo:
                                                          //const int *ptr = &x; // El valor de x no puede ser modificado a través de ptr
                                                          //*ptr = 20; // Error
                                                          //ptr = &y; // OK

    void clear();
    void print();
    bool empty() const; //const: el metodo (la función) no puede modificar el estado del objeto en el que se llama, por ejemplo:
                        //bool empty() const {
                        //return num_elems == 0; //si la lista esta vacia, devolvera TRUE(1), si la lista no esta vacia devolverá FALSE(0)
                        //}

    void addElement() {
        ++num_elems;
    }

private:
    // Internal struct for list nodes
    struct Node {
        int value;
        Node *next;
        Node *prev;
    };

    // List internals
    Node *first = nullptr;
    Node *last = nullptr;
    unsigned int num_elems = 0;
};

void List::push_back(const int &value) {
    Node *node = new Node{value, nullptr, last}; //primero de todo: creamos un nodo con el valor dado
    if (num_elems == 0) { //si el numero de elementos de la lista es = a 0, le estamos diciendo q el primer numero apunte al segundo que es el valor del nodo
        first = last = node;
    }
    else { // si el numero de elementos de la lista NO es = a 0, le estamos diciendo que el siguiente del ultimo numero (que puede ser inexistente o no) apunte al nodo actual
        last->next = node;
        last = node; //y a su vez, como este nodo pasa a ser el ultimo valor de la lista ya que ha sido añadido al final, le tenemos que decir que "last" (el ultimo) apunta también a este nodo
    }
    num_elems++; //le sumamos un elemento a la lista
}

void List::insert(unsigned int position, const int &value) {
    if (position > num_elems) {
        cout << "Position out of bounds." << endl;
        return;
    }

    if (position == num_elems) { // Insert at the end
        push_back(value);
        return;
    }

    Node *new_node = new Node{value, nullptr, nullptr};
    if (position == 0) { // Insert at the beginning
        new_node->next = first; //le dices que el siguiente del nodo nuevo apunte al que actualmente es el primero
        first->prev = new_node; //le dices que el anterior del nodo que actualmente es el primero, apunte al nuevo nodo
        first = new_node; //rediriges el primer nodo al nuevo
    } else {
        Node *current = first; //nos colocamos en el principio
        for (unsigned int i = 0; i < position; ++i) {//tiramos hacia atras hasta llegar a la posicion que queremos, yendo posicion por posicion
            current = current->next;
        }//una vez hemos llegado a la posicion que queríamos
        new_node->prev = current->prev; //el nodo anterior del nuevo nodo es el anterior del nodo que antes se hallaba en esta posicion
        new_node->next = current; //el nodo sigueinte del nuevo nodo es el que antes se hallaba en esa posicion. por ejemplo: 1 2 4 3: new_node=4/new_node.prev=2/new_node.next=3
        if (current->prev) { //si el nodo actual tiene previo (true o false)
            current->prev->next = new_node; //el siguiente del previo del nodo en el que nos encontramos es el actual, por lo tanto, el nuevo
        }
        current->prev = new_node;//el previo del nodo actual es el nuevo nodo
    }
    num_elems++; //se le suma uno a los elementos ya que hemos añadido uno nuevo a la lista
}

void List::print() {
    Node *current = first;
    while (current != nullptr) { // Mientras haya nodos
        cout << current->value << " "; //muestralos por pantalla
        current = current->next; // Avanzar al siguiente nodo
    }
    cout << endl;
}

void List::clear() {
    while (first) { //mientras haya nodos en la lista
        Node *temp = first; //guardamos el nodo actual en el primero como una variable temporal
        first = first->next; //avanzamos señalando que "first" señale a su nodo siguiente
        delete temp; //liberamos la memoria del nodo temporal
    } //así eliminamos toodos los elementos de la lista y de la memoria
    first = last = nullptr; //reseteamos "first" y "last" ya que ahora no apuntan a nada
    num_elems = 0; //la lista vuelve a tener 0 elementos
}

int main() {
    List myList;

    // Insert 5 elements at different positions
    myList.push_back(10); // Add at the end
    myList.print();

    myList.insert(0, 20); // Add at the beginning
    myList.print();

    myList.insert(1, 30); // Add in the middle
    myList.print();

    myList.insert(3, 40); // Add at the end
    myList.print();

    myList.insert(2, 50); // Add in another middle position
    myList.print();

    return 0;
}


//PRINT RECURSIVE
/*
#include <iostream>

class List {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
        Node(int val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node* first = nullptr;
    Node* last = nullptr;
    unsigned int num_elems = 0;

    // Función recursiva auxiliar para imprimir los valores
    void printRecursiveHelper(Node* node) const {
        if (node == nullptr) return; // Caso base: nodo nulo
        std::cout << node->value << " "; // Imprimir el valor actual
        printRecursiveHelper(node->next); // Llamada recursiva al siguiente nodo
    }

public:
    List() : first(nullptr), last(nullptr), num_elems(0) {}

    ~List() {
        while (first != nullptr) {
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }

    void push_back(const int& value) {
        Node* newNode = new Node(value);
        if (last == nullptr) { // Lista vacía
            first = last = newNode;
        }
        else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
        num_elems++;
    }

    void push_front(const int& value) {
        Node* newNode = new Node(value);
        if (first == nullptr) { // Lista vacía
            first = last = newNode;
        }
        else {
            newNode->next = first;
            first->prev = newNode;
            first = newNode;
        }
        num_elems++;
    }

    void insert(unsigned int position, const int& value) {
        if (position == 0) { // Insertar al inicio
            push_front(value);
        }
        else if (position >= num_elems) { // Rellenar con 'N' y luego insertar
            for (unsigned int i = num_elems; i < position; ++i) {
                push_back(0); // Rellenar con 'NULL'
            }
            push_back(value); // Insertar el valor en la última posición
        }
        else { // Insertar en el medio
            Node* current = first;
            for (unsigned int index = 0; index < position; ++index) {
                current = current->next;
            }
            Node* newNode = new Node(value);
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev != nullptr) {
                current->prev->next = newNode;
            }
            current->prev = newNode;
            num_elems++;
        }
    }

    void erase(unsigned int position) {
        if (position >= num_elems) {
            std::cout << "Invalid position to erase.\n";
            return;
        }

        Node* current = first;

        if (position == 0) { // Eliminar el primer elemento
            first = first->next;
            if (first != nullptr) {
                first->prev = nullptr;
            }
            else { // Lista vacía
                last = nullptr;
            }
            delete current;
        }
        else if (position == num_elems - 1) { // Eliminar el último elemento
            current = last;
            last = last->prev;
            if (last != nullptr) {
                last->next = nullptr;
            }
            else { // Lista vacía
                first = nullptr;
            }
            delete current;
        }
        else { // Eliminar un elemento en el medio
            for (unsigned int index = 0; index < position; ++index) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }

        num_elems--;
    }

    // Imprime la lista usando la función recursiva auxiliar
    void print() const {
        printRecursiveHelper(first);
        std::cout << std::endl;
    }
};

int main() {
    List myList;
    myList.push_back(1);
    myList.print();
    myList.insert(3, 7);
    myList.print();
    myList.insert(2, 2);
    myList.print();
    myList.insert(1, 3);
    myList.print();
    myList.insert(0, 4);
    myList.print();
    myList.push_front(100);
    myList.print();
    myList.erase(2); // Eliminar el elemento en la posición 2
    myList.print();

    return 0;
}
*/
