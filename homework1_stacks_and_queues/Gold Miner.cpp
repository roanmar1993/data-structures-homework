{\rtf1\ansi\ansicpg1252\cocoartf2822
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <iostream>\
#include <cstdlib>\
using namespace std;\
\
template <class T> class LinkedList;\
template <class T> class Node;\
\
template <class T>\
class Node\
\{\
public:\
    friend class LinkedList<T>;\
\
    // constructor\
    Node(T x,T y,T fence)\{\
        this-> x = x;\
        this-> y = y;\
        this-> fence = fence;\
        next = NULL;\
    \}\
\
    // member function\
    // this is for you to compare the order of nodes\
    T compare(T x,T y)\{\
        if (this->y > y)\{\
            return 1;\
        \}\
        else if (this->y == y)\
        \{\
            if (this->x>x)\
            \{\
                return 2;\
            \}\
        \}\
        return 0;\
    \}\
\
private:\
    T x;\
    T y;\
    T fence;\
    Node<T>* next;\
\
\};\
\
\
template <class T>\
class LinkedList\
    \{\
        public:\
        \
            /// constructor\
        LinkedList()\
        \{\
            first = NULL;\
            length =0;\
        \}\
        \
            /// member function\
        void insert(T x, T y,T fence)\{\
            Node<T>* temp = first;\
            if(temp!=NULL)\{\
                while (temp->next!=NULL) \{\
                    if(temp->x == x && temp->y == y)\{\
                        //it already exists\
                        if(temp->fence==0 && fence ==1)\{\
                            temp->fence =1;\
                        \}\
                        return;\
                    \}\
                    \
                    temp = temp ->next;\
                \}\
                //last element\
                if(temp->x == x && temp->y == y)\{\
                    //it already exists\
                    if(temp->fence==0 && fence ==1)\{\
                        temp->fence =1;\
                    \}\
                    return;\
                \}else\{\
                    temp->next= new Node<T> (x,y,fence);\
                    length +=1;\
                \}\
            \}else\{\
                first = new Node<T> (x,y,fence);\
                length =1;\
            \}\
            \
        \}\
            \
       \
        \
        void deletion(T x, T y)\{\
            Node<T>* temp = first;\
//\
//                if(temp!=NULL)\{\
//                    if((temp->x == x) && (temp->y==y) && (temp->fence==0))\{\
//                        if(temp->next != NULL)\{\
//                            first = temp->next;\
//                            length -=1;\
//\
//                        \}else\{\
//                            first = NULL;\
//                            length =0;\
//                        \}\
//                        return;\
//                    \}\
//                \}\
//                else\{\
//                    return;\
//                    \}\
//\
//                temp = temp->next;\
//\
//                //second case\
//                if(temp!=NULL)\{\
//                    if(temp->x == x && temp->y == y && temp->fence==0)\{\
//                        if(temp->next != NULL)\{ //double check\
//                            first->next = temp->next;\
//                            delete temp;\
//                        \}\
//                        else\{\
//                            first->next = NULL;\
//                            \}\
//                        length-=1;\
//                        return;\
//                    \}\
//\
//                \}\
//                else\{\
//                    return;\
//                \}\
//\
//                //other cases\
//                Node<T>* future = temp->next;\
//                    int n = 0;\
//                    while (n <= length && future!=NULL) \{\
//                    if(future->x==x && future->y==y && future->fence ==0)\{\
//\
//                        if(future->next!=NULL)\{\
//                            future=future->next;\
//                        \}\
//                        else\{\
//                            future= NULL;\
//                            \}\
//\
//                        length-=1;\
//                        return;\
//                    \}\
//                        future = future->next;\
//                        n++;\
//                    \}\
//                if(temp!=NULL)\{\
//                    if(temp->x == x && temp->y == y && temp->fence==0)\{\
//                        if(temp->next != NULL)\{ //double check\
//                            first->next = temp->next;\
//                            delete temp;\
//                    \}\
//                    else\{\
//                        first->next = NULL;\
//                        \}\
//                    length-=1;\
//                    return;\
//                \}\
//\
//            \}\
//            else\{\
//                return;\
//            \}\
//        \}\
            \
            if (first == NULL)\{\
                return;\
            \}\
            \
            else if (temp    !=NULL)\{\
                if (temp->x == x && temp->y==y && temp->fence==0)\{\
                    first= first->next;\
                    return;\
            \}\
            \
            else\{\
                \
            Node<T> *pastNode=first;\
            Node<T> *FutureNode=first->next;\
                \
            if(FutureNode != NULL)\{\
                while(FutureNode-> x != x || FutureNode-> y != y)\
                \{\
                    pastNode = pastNode->next;\
                    FutureNode = FutureNode->next;\
                    if (FutureNode== NULL)\
                    return;\
                \}\
            if (FutureNode-> x == x && FutureNode-> y == y)\
                \{\
                    if (FutureNode->fence == 0)\
                    pastNode->next= FutureNode->next;\
                    else\
                        return;\
                \}\
\
            \}\
            \}\
    \
         \}\
        \}\
                \
        void SortedList() \{\
            // Immediately check if the list is empty\
            if (first == nullptr) \{\
                return; // The list is empty, no action needed\
            \}\
\
            Node<T>* temp = first;\
            Node<T>* lado = temp->next; // Since we've checked first is not nullptr, this is safe\
\
            for (int i = 0; i < length; i++) \{\
                temp = first; // Reset temp for each outer loop iteration\
                lado = temp->next; // Safe to assign since we're within the check for first not being nullptr\
\
                for (int j = 0; j < length - 1; j++) \{ // Assuming j < length - 1 to ensure we don't go out of bounds\
                    // No need to check first == NULL here, it's already done at the function start\
\
                    if (lado != nullptr) \{\
                        if (temp->compare(lado->x, lado->y) == 1 || temp->compare(lado->x, lado->y) == 2) \{\
                            // Swapping logic...\
                            Node<T>* umbrella = new Node<T>(temp->x, temp->y, temp->fence);\
                            temp->x = lado->x;\
                            temp->y = lado->y;\
                            temp->fence = lado->fence;\
\
                            lado->x = umbrella->x;\
                            lado->y = umbrella->y;\
                            lado->fence = umbrella->fence;\
\
                            delete umbrella; // Remember to delete the temporary node to avoid memory leaks\
                        \}\
                        temp = temp->next;\
                        lado = lado->next;\
                    \}\
                    // Moved inside the loop to check at each iteration\
                    if (first == nullptr) \{\
                        return;\
                    \}\
                \}\
            \}\
        \}\
\
        void show()\{\
            Node<T>* tempi = first;\
            //cout<<"lenght "<<length;\
            while (tempi!=NULL)\{\
                cout<<"("<< tempi->x<< ","<<tempi->y<<")"<<endl;\
                tempi = tempi->next;\
            \}\
          \
            \
            \
        \}\
        private:\
            Node<T>* first;\
            int length;\
    \};\
\
LinkedList<long long> Prueba1;\
\
/**  solving function  **/\
void plant(long long x,long long y,int withFence)\{\
    Prueba1.insert(x, y, withFence);\
\}\
//\
void thief(long long x,long long y )\{\
    Prueba1.deletion(x+1, y);\
    Prueba1.deletion(x-1, y);\
    Prueba1.deletion(x, y+1);\
    Prueba1.deletion(x, y-1);\
    Prueba1.deletion(x, y);\
 \
\}\
void superThief(long long x,long long y)\{\
    Prueba1.deletion(x+1, y);\
    Prueba1.deletion(x+1, y+1);\
    Prueba1.deletion(x+1, y-1);\
    Prueba1.deletion(x-1, y);\
    Prueba1.deletion(x-1, y+1);\
    Prueba1.deletion(x-1, y-1);\
    Prueba1.deletion(x, y+1);\
    Prueba1.deletion(x, y-1);\
    Prueba1.deletion(x, y);\
\
\}\
\
void display()\{\
    cout<<"Display\\n";\
    Prueba1.SortedList();\
    Prueba1.show();\
    \
\}\
}