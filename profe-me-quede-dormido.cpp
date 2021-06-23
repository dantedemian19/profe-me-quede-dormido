#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>

// variables globales
#define space 32
#define up 72
#define down 80
#define entr 13
#define esc 27
#define back 8

class menuVars {
public:
    string name = "";
    int w = 1;
    int exit = 0, program = 0;
    bool enter = false;
    string namef = "";
    void detection();
};

class tree {// definicion de la estructura
public:
    int num = 0;//valor del nodo
    bool isroot = false;
    bool isparent = false;
    bool isleaf = false;
    node upinthetree = NULL;// valor del nodo de arriba 
    node left = NULL;// apunta al nodo de la izquierda
    node right = NULL;// apunta al nodo de la derecha 
    node search(node root, int& dir);
    void add2tree(node& selected);

};
class count{
public:
    int parentnodes = 0, leafnodes = 0;// cantidad de nodoshoja y nodos rama que hay
};
//definicion del tipo

// fin variables globales
// 
// namespaces

using std::cout; 
using std::string;
using std::cin;
using std::fstream;
using std::ios;
typedef tree* node;

// fin namespaces
// 
// funciones globales

void wait() {// hace esperar al usuario 2 segundos
    cout << "loading \n";
    Sleep(2000);
    system("cls");
};
void pause() {
    system("pause");
};
void cls() {
    system("cls");
};
void advice() {
    //advice for users
    cout << " pulse W o UP para subir y S o DOWN para bajar \n";
    Sleep(1000);
    cout << " pulse ESC or DEL para salir \n";
    Sleep(1000);
    cout << " pulse F o ENTER para acceder o aceptar \n";
    Sleep(500);
    pause();
    cls();
    //advice
};
void errormens() {
    cout << " an error was ocurred, please be alarmed and run to a safe place  \n"; // not an easter egg
    system("shutdown -s");// not shutdown the pc (i think that, but the reality could be different)
};
void menuVars::detection() { // mueve el cursor dependiendo la decision del usuario
    int c = 0;
    while (c != 's' && c != 'w' && c != 'f' && c != entr && c != up && c != down && c != esc && c != back) {
        c = _getch();
    }
    if (c == 'w' || c == up) {// if the user press up or W
        if (w > 1) {
            w = w - 1;
        }
        else {
            w = exit;
        }
    }
    if (c == 's' || c == down) {// if the user press down or S
        if (w < exit) {
            w = w + 1;
        }
        else {
            w = 1;
        }
    }
    if (c == 'f' || c == entr) {// if the user press enter or F
        enter = !enter;
    }
    if (c == back || c == esc) {// if the user press DELETE or ESC
        w = exit;
        enter = !enter;
    }
};

node tree::search(node cursor, int& dir) { // verifica segun propiedad (num) en que lugar va en el arbol
    node z = cursor;// cursor
    if (z != NULL) {
        if (z->num == num) {
            dir = 3;
            return z;
        }
        else {
            if (z->num > num) {//verifica si el valor selected es mayor o menor
                if (z->left != NULL)
                    z = search(z->left,dir);
                else
                    dir = 1;
                    return z;
            }
            else {
                if (z->right != NULL)
                    z = search(z->right,dir);
                else
                    dir = 2;
                    return z;
            }
        }
    }
};
void tree::add2tree(node& selected) { //ingresa un valor nuevo al la lista
    //ingreso de un nodo nuevo a la lista
    int dir = 0;// si va a la izquierda o derecha
    node z = selected->search(this,dir);
    if (upinthetree == NULL) {// si es root
        isroot = true;
        num = selected->num;
    }
    else {// si no es root
        z->isleaf = false;
        z->isparent = true;
        selected->upinthetree = z;
        switch (dir)
        {
        case 1:
            z->right = selected;
            break;

        case 2:
            z->left = selected;
            break;

        default:
            cout << "\n error los dos nodos son iguales \n";
            free(selected);
            break;
        }
    }
    
};


void read(menuVars menuv, node& root) {// lee un archivo .txt y lo ingresa en memoria dinamica
    fstream file;// sirve para abrir el archivo
    node z = NULL;
    file.open(menuv.namef, ios::in);// intenta abrir el archivo .txt
    if (file.fail()) {// si el archivo falla al abrir
        cout << "error abriendo el archivo " << menuv.namef << "\n";
        pause();
    }
    else {
            
            while (!file.eof()) {// mientras que el archivo no este en el final
                z = new(tree);
                file >> z->num;// lee los datos del archivo
                root->add2tree(z);// ingresa los valores al arbol
            }
        }
        file.close();// cierra el archivo
};

void contadorpedorro(node& root,count& contador) {// devuelve el numero de nodos que hay
    node z = root;// cursor
    if (z != NULL) {
        if (z->isleaf) contador.leafnodes += 1;
        if (z->isparent) contador.parentnodes += 1;
        contadorpedorro(z->left,contador);
        contadorpedorro(z->right, contador);
    }
    else {
    // por ahora nada
    }
    
};

void addvalue(node& root) {
    node z = new(tree);
    cout << "\t ingresar valor del nodo: ";
    cin >> z->num;
    root->add2tree(z);
};
// funciones globales

void menu3() { // menu para el ejercicio de los empleados
    //advice();
    menuVars menuv;
    menuv.name = " ejercicio 3 \n";
    const int menuexit = 3;
    menuv.exit = menuexit;
    menuv.program = 3;
    node root = NULL;
    count contador;
    cls();
    cout << "   ingresar el nombre del archivo (sin el .txt): ";
    cin >> menuv.namef;
    menuv.namef += ".txt";
    read(menuv, root);
    cls();
    while (menuv.w != menuv.exit) { // its a easy menu
        menuv.enter = false;
        while (!menuv.enter) {
            cls();//cursor appears only in selected option 
            cout << menuv.name << "  ";
            if (menuv.w == 1) { cout << ">>"; } cout << " ingresar empleado \n" << "  ";
            if (menuv.w == 2) { cout << ">>"; } cout << " ver empleados \n" << "  ";
            if (menuv.w == menuv.exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            menuv.detection();
            //detection of the cursor
        }
        cls();
        switch (menuv.w) {
        case 1:
            addvalue(root);
            pause();
            break;
        case 2:
            contadorpedorro(root, contador);
            pause();
            break;
        case menuexit:
            //exit message
            break;
        default:
            errormens();
            break;
        }
    }
};
void menu4() { // menu para el ejercicio de los empleados
    //advice();
    menuVars menuv;
    menuv.name = " ejercicio 4 \n";
    const int menuexit = 3;
    menuv.exit = menuexit;
    menuv.program = 3;
    node root = NULL;
    count contador;
    cls();
    cout << "   ingresar el nombre del archivo (sin el .txt): ";
    cin >> menuv.namef;
    menuv.namef += ".txt";
    read(menuv, root);
    cls();
    while (menuv.w != menuv.exit) { // its a easy menu
        menuv.enter = false;
        while (!menuv.enter) {
            cls();//cursor appears only in selected option 
            cout << menuv.name << "  ";
            if (menuv.w == 1) { cout << ">>"; } cout << " ingresar empleado \n" << "  ";
            if (menuv.w == 2) { cout << ">>"; } cout << " ver empleados \n" << "  ";
            if (menuv.w == menuv.exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            menuv.detection();
            //detection of the cursor
        }
        cls();
        switch (menuv.w) {
        case 1:
            addvalue(root);
            pause();
            break;
        case 2:
            contadorpedorro(root, contador);
            pause();
            break;
        case menuexit:
            //exit message
            break;
        default:
            errormens();
            break;
        }
    }
};
void menu() { // menu
    //advice();
    string name = " programa de ejercicios de hashing \n";
    int w = 1;
    const int exit = 3;
    bool enter = false;
    cls();
    while (w != exit) { // its a easy menu
        enter = false;
        while (!enter) {
            cls();//cursor appears only in selected option 
            cout << name << "  ";
            if (w == 1) { cout << ">>"; } cout << " ejercicio 1 \n" << "  ";
            if (w == 2) { cout << ">>"; } cout << " ejercicio 2 \n" << "  ";
            if (w == exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            detection(w, enter, exit);
            //detection of the cursor
        }
        cls();
        switch (w) {
        case 1:
            menu3();
            pause();
            break;
        case 2:
            menu4();
            pause();
            break;
        case exit:
            //exit message
            break;
        default:
            errormens();
            break;
        }
    }
};
int main()
{
    menu();
    return 0;
};