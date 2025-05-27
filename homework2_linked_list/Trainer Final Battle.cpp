{\rtf1\ansi\ansicpg1252\cocoartf2822
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <iostream>\
#include <string>\
using namespace std;\
\
class CircularDoublyLinkedList \{\
private:\
    struct Node \{ // usamos struc para crear nuestro objecto pokemon\
        int pokedex;\
        int damage;\
        int health;\
        int level;\
        string stance;\
        Node* next;\
        Node* prev;\
\
        //constructor\
        Node(int pokedex, int damage, int health, string stance, int level = 1)\
            : pokedex(pokedex), damage(damage), health(health), level(level), stance(stance), next(this), prev(this) \{\}\
    \};\
    Node* first;\
    int lenght;\
    \
public:\
  \
    //first es null al principio y lenght trackea la cantidad de pokemons en la arena\
    CircularDoublyLinkedList() : first(nullptr),lenght(0)\{\}; \
\
    // Destructor para limpiar la lista\
    ~CircularDoublyLinkedList() \{\
        while (first != nullptr) \{ \
            removeHead(); //llama remove head and deletes one by one para desalocar la memoria\
        \}\
    \}\
    // pasa los elementos de un nodo. Con esto manejo ataque cuando se elimina el current target y cuando se evoluciona\
    void replace_to_delete(Node* old_attributes, Node* new_attributes) \{\
        old_attributes->pokedex = new_attributes->pokedex;\
        old_attributes->damage = new_attributes->damage;\
        old_attributes->health = new_attributes->health;\
        old_attributes->level = new_attributes->level;\
        old_attributes->stance = new_attributes->stance;\
    \}\
\
    // remueve el ultimo elemento de la lista, se usa cuando ataque elimina el pokemon a la izquierda\
    void removeLast() \{\
        if (first == nullptr) return; // Empty list, nothing to do\
\
        Node* temp = first->prev; // This is the current first->prev node\
\
        if (temp == first) \{\
            // This means there's only one node in the list\
            first = nullptr;\
        \} else \{\
            // More than one node in the list\
            temp->prev->next = first;\
            first->prev = temp->prev;\
        \}\
        delete temp;\
        lenght--;\
    \}\
    //agrega un pokemon a la lista\
    void insertNormal(int pokedex, int damage, int health, string = "Neutral", int level=1) \{\
        Node* newNode = new Node(pokedex, damage, health, "Neutral", 1); \
        if (first == nullptr) \{ \
            first = newNode;\
        \} else \{\
            newNode->prev = first->prev;\
            newNode->next = first;\
            first->prev->next = newNode;\
            first->prev = newNode;\
        \}\
        lenght++;\
    \}\
    //cuando el stance is attack se usa esta funcion\
    void insertAttack(int pokedex, int damage, int health, string = "Neutral")\{\
        Node* newNode = new Node(pokedex, damage, health, "Neutral",1);\
        if (!first) \{\
            insertNormal(pokedex,  damage,  health,"Neutral", 1);\
            delete newNode; // como no se inserto el nuevo nodo pero se creo lo borramos igual;\
            return; // Finaliza la funci\'f3n aqu\'ed ya que el nodo ya est\'e1 insertado.\
        \}\
\
        // Aplica da\'f1o a first y first->prev si la lista tiene m\'e1s de un nodo.\
        if (first != first->prev) \{ //  verifica si hay al menos dos elementos\
            first->health -= damage;\
            first->prev->health -= damage;\
        \} else \{\
            first->health -= damage; // Solo hay un nodo.\
        \}\
        //si ningun pokemon es put to sleep solo insertamos normalmente\
        if (first->health > 0 && first->prev->health > 0) \{\
            // cout << "executing scenario 1" << endl; // for debugging\
            insertNormal(pokedex, damage, health, "Neutral", 1);\
\
        //si el pokemon en la ultima posicion y el ultimo tambien es puesto a dormir\
        \} else if (first != first->prev && first->health <= 0 && first->prev->health <= 0) \{\
            // cout << "executing scenario 2" << endl; // for debugging\
            replace_to_delete(first, newNode);\
            removeLast();\
\
        //si se elimna el current node, solo reemplazamos los valores con los del nuevo pokemon y borramos en nuevo nodo\
        \} else if (first->health <= 0) \{\
        //    cout << "executing scenario 3" << endl; // for debugging\
            replace_to_delete(first, newNode);\
            delete newNode;\
\
        //si el pokemon en la ultima posicion es puesto a dormir\
        \} else if (first->prev->health <= 0) \{\
            // cout << "executing scenario 4" << endl; // for debugging\
            replace_to_delete(first->prev, newNode);\
            delete newNode;\
        \}\
    \}\
    //checka las condiciones si la evolucion es possible or not\
    bool canEvolve(int pokedex)\{\
        if (!first || first==first->prev) return false;\
        if(first->pokedex == pokedex && first->prev->pokedex == pokedex && first->level < 3 && first->prev->level < 3) return true;\
        else return false;\
    \}\
    //evolucionamos\
\
    int maxiMax(int one, int two)\{ //selecciona los atributos mas altos para hacer la digievolucion\
        if (one > two)\{\
            return one;\
        \}\
        else return two;\
    \}\
\
    void insertEvolve(int pokedex, int damage, int health, string = "Neutral")\{\
        \
        if (!canEvolve(pokedex))\{\
            insertNormal( pokedex,  damage,  health, "Neutral", 1);\
            // cout<<"cannot evolve mi perro"<<endl;\
        \}\
        else\{\
            //calcular los vales para el pokemon evolucionado\
            // cout<<"digievolucion perrrriiiii"<<endl;\
            int evolved_damage = maxiMax(maxiMax(first->damage, first->prev->damage), damage);\
            int evolved_health = maxiMax(maxiMax(first->health, first->prev->health), health);\
            int evolved_level = maxiMax(first->level, first->prev->level) + 1;\
            // cout<<"new health is "<<evolved_health<<endl;\
\
            // agregar los valores al nuevo \
            first->damage = evolved_damage;\
            first->health = evolved_health;\
            first->level = evolved_level;\
            removeLast();\
        \
        \}\
    \}\
\
    //elimina el current target\
    void removeHead() \{\
        if (first == nullptr) return; \
\
        Node* temp = first; \
        \
        if (first->next == first) \{ \
            first = nullptr; \
        \} else \{\
            first->next->prev = first->prev;\
            first->prev->next = first->next;\
            first = first->next; \
        \}\
        delete temp;\
        lenght--;\
    \}\
\
    // cuando hacemos hacemos shuffle primero rotamos las cabeza y luego hacemos shuffle a los valores\
    void swap_value(Node* old_attributes, Node* new_attributes) \{\
        int tempPokedex = old_attributes->pokedex;\
        int tempDamage = old_attributes->damage;\
        int tempHealth = old_attributes->health;\
        int tempLevel = old_attributes->level;\
\
        old_attributes->pokedex = new_attributes->pokedex;\
        old_attributes->damage = new_attributes->damage;\
        old_attributes->health = new_attributes->health;\
        old_attributes->level = new_attributes->level;\
\
        new_attributes->pokedex = tempPokedex;\
        new_attributes->damage = tempDamage;\
        new_attributes->health = tempHealth;\
        new_attributes->level = tempLevel;\
\
    \}\
   \
    void switchHead(char direction,int n) \{\
        if (first == nullptr || n == 0 || n==lenght) return; \
        \
        if(n>lenght) n = n%lenght;\
        // cout<<n<<" is this value now"<<endl;\
        Node *original_head = first;\
        if (direction == 'c')\{\
            for (int i = 0; i < n; i++) \{\
                first = first->next; \
                if (i==n-1) swap_value(original_head, first);\
            \}\
        \}\
\
        if (direction == 'a')\{\
            for (int i = 0; i < n; i++) \{\
                first = first->prev; \
                if (i==n-1) swap_value(original_head, first);\
            \}\
        \}\
    \}\
    //check :(\
    void check(int n) \{\
        if (first == nullptr || n <= 0) return; // Si la lista est\'e1 vac\'eda o n es inv\'e1lido, no hacer nada.\
\
        Node* current_headnode = first; \
        bool anyDeletionOccurs = false;\
\
        while (n > 0 && current_headnode != nullptr && first != nullptr) \{ // condiciones para seguir en el loop\
            Node* dummy = current_headnode->next;\
            bool foundDuplicateForHeadnode = false;\
            int deletedNodes = 0;\
            int positionsToCheck = n-1; // Excluye el current_headnode al contar las posiciones.\
\
            while (positionsToCheck > 0 && dummy != current_headnode) \{\
\
                if (dummy->pokedex == current_headnode->pokedex) \{\
                    Node* nodeToDelete = dummy;\
                    dummy->prev->next = dummy->next;\
                    dummy->next->prev = dummy->prev;\
                    dummy = dummy->next; // Avanza antes de eliminar para no perder la referencia.\
                    delete nodeToDelete; // Elimina el nodo duplicado.\
                    foundDuplicateForHeadnode = true;\
                    anyDeletionOccurs = true;\
                    deletedNodes++;\
                    lenght--;\
\
                \} else \{\
\
                    dummy = dummy->next; // Solo avanza si no hay duplicado.\
                \}\
                positionsToCheck = positionsToCheck -1;\
\
            \}\
\
            if (foundDuplicateForHeadnode && current_headnode != first && positionsToCheck == 0) \{ // Protecci\'f3n adicional para no eliminar el nuevo first.\
                if (current_headnode->next == current_headnode) \{ // Si solo queda current_headnode en la lista.\
                    delete current_headnode;\
                    lenght--;\
                    first = nullptr;\
                \} else \{\
                    // cout<<"si hay duplicado 2"<<endl;\
                    Node* nextNode = current_headnode->next;\
                    current_headnode->prev->next = current_headnode->next;\
                    current_headnode->next->prev = current_headnode->prev;\
                    delete current_headnode;\
                    current_headnode = nextNode; // Establece el siguiente nodo v\'e1lido como current_headnode.\
                    lenght--;\
                \}\
            \
            \} else if (foundDuplicateForHeadnode && current_headnode == first && positionsToCheck == 0) \{\
                // cout<<"si hay duplicado 3"<<endl;\
                removeHead();\
                // cout<<"head now is"<<first->pokedex<<endl;\
                current_headnode = first; // Avanza al siguiente nodo si no se elimin\'f3 el headnode.\
                // cout<<"head now is"<<first->pokedex<<endl;\
                foundDuplicateForHeadnode = false;\
            \}\
            else if (positionsToCheck == 0)\{\
                // cout<<"suup boiii"<<endl;\
                current_headnode = current_headnode->next; // Avanza al siguiente nodo si no se elimin\'f3 el headnode.           \
            \}\
\
            if (anyDeletionOccurs && positionsToCheck == 0 ) \{\
                // cout<<deletedNodes<<" nodes got deleted "<<endl;\
                n = n - deletedNodes- 1 ; // Ajusta n si se realizaron eliminaciones \
                // anyDeletionOccurs = false; // Restablece el indicador para la pr\'f3xima iteraci\'f3n.\
            \} else if (positionsToCheck == 0 )\{\
                n--; // Decrementa n si no hubo eliminaciones, para avanzar en la comparaci\'f3n.\
            \}\
        \}\
    \}\
\
\
    void reverse(int n)\{\
\
        if (first ==nullptr || n<2 || first == first->next) return; //la lista esta vacia, n no es valido o solo hay un elemento\
\
        Node* startingPoint = first;\
        Node* primero = first;\
        Node* ultimo;\
        ultimo = primero;\
        Node* primeroNext;\
        Node* ultimoPrev;\
        Node* ultimoBU;\
\
\
        int numberOfRounds = 0;\
        if (lenght%n!=0) numberOfRounds = lenght/n+1;\
        else numberOfRounds = lenght/n;\
        int checkedPositions = 1;\
        int finishedRounds = 0;\
\
        if (lenght == 2)\{\
            swap_value(first, first->next);\
        \}\
\
        while(finishedRounds<numberOfRounds && checkedPositions<lenght-1)\{\
            int checkedPositionsSubGroup = 1;\
            primero = startingPoint;\
            ultimo = startingPoint;\
\
        while(checkedPositionsSubGroup < n && checkedPositions <lenght)\{\
            ultimo = ultimo->next;\
            ultimoBU= ultimo;\
            // cout<<"checked positions"<<checkedPositionsSubGroup<<endl;\
            // cout<<"ultimo is "<<ultimo->pokedex<<endl;\
            if (checkedPositionsSubGroup == n-1 || ultimo->next == first)\{\
                // cout<<"hello"<<endl;\
                if (n>=lenght)\{\
\
                    for (int j=0 ;j<lenght/2;j++)\{\
                        \
                        primeroNext = primero;\
                        ultimoPrev = ultimoBU;\
                        swap_value(primeroNext, ultimoPrev);\
                        primero = primero->next;\
                        ultimoBU = ultimoBU->prev;\
                        startingPoint = ultimo->next;\
                    \}\
                \}\
                else if (n< lenght && finishedRounds<numberOfRounds-1) \{\
                    for (int j=0 ;j<n/2;j++)\{\
                    \
                        primeroNext = primero;\
                        ultimoPrev = ultimoBU;\
                        swap_value(primeroNext, ultimoPrev);\
                        primero = primero->next;\
                        ultimoBU = ultimoBU->prev;\
                        startingPoint = ultimo->next;\
                        \}\
                    \}\
                else if (n< lenght && finishedRounds == numberOfRounds - 1) \{\
\
                    for (int j=0 ;j<(lenght-finishedRounds*n)/2;j++)\{\
                        primeroNext = primero;\
                        ultimoPrev = ultimoBU;\
                        swap_value(primeroNext, ultimoPrev);\
                        primero = primero->next;\
                        ultimoBU = ultimoBU->prev;\
                        startingPoint = ultimo->next;\
                    \}\
                \
                \}\
\
            \}\
            checkedPositions++;\
            checkedPositionsSubGroup++;\
            if (ultimo->next==first)\{\
                break;\
            \}\
\
        \}\
        finishedRounds++;\
        \
    \}\
    \}\
\
\
    void print() \{\
    if (first == nullptr) \{\
        cout << "no Poke Poke ;-;" << endl;\
        return;\
    \}\
    Node* temp = first;\
    do \{\
        cout << "ID: " << temp->pokedex;\
        cout << " HP: " << temp->health;\
        cout << " LVL: " << temp->level;        \
        cout << endl;\
\
        temp = temp->next;\
    \} while (temp != first);\
\}\
\
\};\
\
bool debug=false;\
\
int main() \{\
    CircularDoublyLinkedList arena_de_combate;\
    if (debug)\{\
    for (int i =1; i<16; i++)\{\
        arena_de_combate.insertNormal(i, 1, i+1);\
    \}\
\
    arena_de_combate.reverse(5);\
    arena_de_combate.print();\
    \}\
    else \{\
    int numberOfCommands;\
    cin>>numberOfCommands;\
    string command;\
    for (int i=0;i<numberOfCommands;i++)\{\
        int pokedex,damage,health;\
        string stance;\
\
        cin>>command;\
        if (command == "Insert")\{\
            cin>>pokedex>>damage>>health>>stance;\
            if (stance == "Neutral")\{\
                arena_de_combate.insertNormal(pokedex,  damage, health);\
            \}\
            else if (stance == "Attack")\{\
                arena_de_combate.insertAttack( pokedex,  damage,  health);\
            \}\
            else if (stance == "Evolve")\{\
                arena_de_combate.insertEvolve(pokedex,  damage,  health);           \
            \}\
        \}\
\
        else if (command == "Delete")\{\
            arena_de_combate.removeHead();\
        \}\
        else if (command == "Shuffle")\{\
            char direction;\
            int n;\
            cin>>direction>>n;\
            arena_de_combate.switchHead(direction, n);\
        \}\
\
        else if (command=="Reverse")\{\
            int numberOfNodes;\
            cin>> numberOfNodes;\
            arena_de_combate.reverse(numberOfNodes);\
        \}\
        else if (command == "Check") \{\
            int positions;\
            cin>>positions;\
            arena_de_combate.check(positions);\
        \}\
        else \{\
            arena_de_combate.print();\
        \}\
        \
\
    \}\
\
    arena_de_combate.print();\
\
\
 \}\
\
\
\}\
\
}