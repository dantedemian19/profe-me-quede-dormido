#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>

#define space 32
#define up 72
#define down 80
#define entr 13
#define esc 27
#define back 8
 
// namespaces

using std::ios;
using std::cout;
using std::string;
using std::cin;
using std::fstream;

// fin namespaces
//
// classes
class tree{
    typedef tree* node;// definicion del puntero para obejtos tree
public:
    int num = 0;//valor del nodo
    string cha = "";
    bool isroot = false;
    bool isparent = false;
    bool isleaf = true;
    bool isnode = false;
    tree* upinthetree = nullptr;// valor del nodo de arriba 
    tree* left = nullptr;// apunta al nodo de la izquierda
    tree* right = nullptr;// apunta al nodo de la derecha
    int sright = 0, sleft = 0; // apunta al nodo siguiente, para el ejercicio estatico
    node search(node root, int& dir);
    void add2tree(node& selected);
    void showtreeinorder(int mode);
    void showtreepostorder(int mode);
    void showtreepreorder(int mode);
};
typedef tree* node;// definicion del puntero para obejos tree

class menuVars {
public:
    string name = "";
    int w = 1;
    int exit = 0, program = 0;
    bool enter = false;
    string namef = "";
    void detection();
};
class count {
public:
    int parentnodes = 0, leafnodes = 0;// cantidad de nodoshoja y nodos rama que hay
};
// end classes
//
// funciones globales
void pause() {
    int cha = 0;
    cout << "\t pulse a enter to continue";
    while (cha != entr) {
        cha = _getch();
    }
};
void cls() {
    cout << "\033c";
};
void wait() {// hace esperar al usuario 2 segundos
    cout << "loading \n";
    Sleep(2000);
    cls();
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
// end of class menuVars methods
//
// class tree methods
node tree::search(node cursor, int& dir) { // verifica segun propiedad (num) en que lugar va en el arbol
    node z = cursor;// cursor
    if (z != nullptr) {
        if (z->num != num) {
            if (z->num > num) {//verifica si el valor selected es mayor o menor
                if (z->left != nullptr)
                    z = search(z->left, dir);
                else
                    dir = 1;
                return z;
            }
            if (z->num < num) {
                if (z->right != nullptr)
                    z = search(z->right, dir);
                else
                    dir = 2;
                return z;
            }
        }
    }
    else dir = 0;
    return z;
};
void tree::add2tree(node& selected) { //ingresa un valor nuevo al arbol desde root
    int dir = 0;// si va a la izquierda o derecha
    node z = selected->search(this, dir);
    if (isroot){
        selected->upinthetree = z;
        switch (dir)
        {
        case 2: // si va a la derecha
            z->right = selected;
            z->isparent = true;
            z->isleaf = false;
            break;

        case 1: // si va a la izquierda
            z->left = selected;
            z->isparent = true;
            z->isleaf = false;
            break;

        default:// si hay error
            cout << "\n error dos nodos son iguales \n";
            free(selected);
            break;
        }
    }else  z->isroot = true;
};
void tree::showtreepreorder(int mode) {// devuelve los nodos
    if (this != nullptr) {
        if (mode == 0 || mode == 1)cout << num << " ";// el nodo (this)
        if (mode == 0 || mode == 2)cout << cha << " ";// el nodo (this)
        if (left != nullptr) {
            left->showtreepreorder(mode);// la izquierda del arbol
        }
        if (right != nullptr) {
            right->showtreepreorder(mode);// la derecha del nodo
        }
    }
};
void tree::showtreeinorder(int mode) {// devuelve los nodos de menor a mayor apartir de la raiz
    if (this != nullptr) {
        if (left != nullptr) {
            left->showtreeinorder(mode);// la izquierda del arbol
        }
        if (mode == 0 || mode == 1)cout << num << " ";// el nodo (this)
        if (mode == 0 || mode == 2)cout << cha << " ";// el nodo (this)
        if (right != nullptr) {
            right->showtreeinorder(mode);// la derecha del nodo
        }
    }
};
void tree::showtreepostorder(int mode) {// devuelve los nodos
    if (this != nullptr) {
        if (left != nullptr) {
            left->showtreepostorder(mode);// la izquierda del arbol
        }
        if (right != nullptr) {
            right->showtreepostorder(mode);// la derecha del nodo
        }
        if (mode == 0 || mode == 1)cout << num << " ";// el nodo (this)
        if (mode == 0 || mode == 2)cout << cha << " ";// el nodo (this)
    }
};
// end of class tree methods
//
// funciones globales
void read(menuVars menuv, node& root, int mode) {// lee un archivo .txt y lo ingresa en memoria dinamica
    // mode 0, reads only numbers
    // mode 1, read numbers and a string
    fstream file;// sirve para abrir el archivo
    node z = nullptr;
    file.open(menuv.namef, ios::in);// intenta abrir el archivo .txt
    if (file.fail()) {// si el archivo falla al abrir
        cout << "error abriendo el archivo " << menuv.namef << "\n";
        pause();
    }
    else {

        while (!file.eof()) {// mientras que el archivo no este en el final
            z = new(tree);
            file >> z->num;// lee los datos del archivo
            if (mode == 1) file >> z->cha;
            if (root == nullptr) { // si es la root
                root = z;
                root->isroot = true;
            }
            else root->add2tree(z);// si no es la root
        }
    }
    file.close();// cierra el archivo
};
void contadorpedorro(node root, count& contador) {// devuelve el numero de nodos que hay    
    if (root !=nullptr) {
        if (root->isleaf) { 
            contador.leafnodes += 1; // si hay un nodo leaf
        }
        if (root->isparent) { 
            contador.parentnodes += 1; // si hay un nodo parent
        }
        /*cout << "\t" << root->num << " " << root->isleaf << " " << root->isparent << " "; // debug, muestra los nodos con datos sobre si es leaf, si es parent,
        if (root->isparent) {                                                               // y datos sobre el nodos hijos
            if (root->left != nullptr) {
                cout << "left: " << root->left->num << " ";
            }
            if (root->right != nullptr) {
                cout << "right: " << root->right->num << " ";
            }
        }
        cout << "\n";*/
        if(root->left != nullptr) contadorpedorro(root->left, contador);// si tiene nodos hijos, repite la funcion con el nodo siguiente
        if(root->right != nullptr) contadorpedorro(root->right, contador);// si tiene nodos hijos, repite la funcion con el nodo siguiente
    }
    else {
        // por ahora nada
    }
};
void addvalue(node& root) { // aniade un nodo nuevo
    node z = new(tree);
    cout << "\t ingresar valor del nodo: ";
    cin >> z->num;
    root->add2tree(z);
};
int sadd2tree(tree root[], tree selected, int i, int dad, int& dir) {// busca el lugar del nodo en el arbol static
    if (root[i].num > selected.num) {
        if (root[i].sleft != 0) i = sadd2tree(root, selected, (root[i].sleft), i, dir);// si va para la izquierda
        else dir = 1;
            return i;
        
    }
    if (root[i].num < selected.num) {
        if (root[i].sright != 0) i = sadd2tree(root, selected, (root[i].sright), i, dir); // si va para la derecha
        else dir = 2;
            return i;
    }
    return dad;// si va en este nodo
};
void loopaddvalue(tree root[], tree selected, int i, int j, int& dir) {
    if(root[i].num != selected.num)
    if (root[i + j].isnode == false && dir > 0) {// si el lugar en el vector esta disponible
        root[i + j] = selected;
        root[i + j].isnode = true;// ocupa el nodo
        //cout << root[i+j].num << " " << i << " ";
        root[i].isparent = true;
        root[i].isleaf = false;
        if (dir == 1) { 
            root[i].sleft = i + j; // si va a la izquierda
            //cout << root[i].sleft<<"\n";
        }
        if (dir == 2) { 
            root[i].sright = i + j; // si va a la derecha
            //cout << root[i].sright << "\n";
        }
    }
    else if(dir>0 && j+1 < 9999) loopaddvalue(root, selected, i, j+1, dir);// si el nodo esta ocupado repite la funcion con el siguiente espacio
        else  exit;
};
void addvaluestatic(tree root[], tree selected) {// funcion para agregar un nodo selected, al arbol static
    int i = 0, dir = 0;
        i = sadd2tree(root, selected, 0, 0, dir);
        loopaddvalue(root, selected, i, 1, dir);
};
void staticcontadorpedorro(tree root[], count& contador,int i) {// devuelve el numero de nodos que hay en el arbol static
    if (root[i].isnode != false ) { // si el nodo es parte del arbol
        if (root[i].isleaf) {
            contador.leafnodes += 1;// si el nodo es leaf
        }
        if (root[i].isparent) {
            contador.parentnodes += 1;// si el nodo es parent
        }
        
        if (root[root[i].sleft].isnode != false) staticcontadorpedorro(root, contador, (root[i].sleft));// si el nodo tiene nodos hijos
        if (root[root[i].sright].isnode != false) staticcontadorpedorro(root, contador, (root[i].sright));// repite la funcion
    }
    else {
        // por ahora nada
    }
};
void readstatic(menuVars menuv, tree root[]) {// lee un archivo .txt y lo ingresa en memoria dinamica
    fstream file;// sirve para abrir el archivo
    tree add;
    file.open(menuv.namef, ios::in);// intenta abrir el archivo .txt
    if (file.fail()) {// si el archivo falla al abrir
        cout << "error abriendo el archivo " << menuv.namef << "\n";
        pause();
    }
    else {

        while (!file.eof()) {// mientras que el archivo no este en el final
            file >> add.num;// lee los datos del archivo
            if (root[0].isroot == false) { // si es la root
                root[0] = add;
                root[0].isnode = true;
                root[0].isroot = true;
            }
            else addvaluestatic(root,add);// si es un nodo hoja
        }
        pause();
    }
    file.close();// cierra el archivo
};
void showstatictree(tree root[], int i) {// devuelve los nodos de menor a mayor no funciona
    if (root[i].isnode) {
        if (!root[root[i].sleft].isroot) {
            showstatictree(root, (root[i].sleft));
        }
        cout << " " << root[i].num << " ";
        if (!root[root[i].sright].isroot) {
            showstatictree(root, (root[i].sright));
        }
    }
};
// end funciones globales
//
// menus
void menu1() {
    menuVars menuv;
    menuv.name = "\tejercicio 1 \n";
    cout << menuv.name;
    cout << "\t a) a + b \n";
    cout << "\t b) log x \n";
    cout << "\t c) n ! \n";
    cout << "\t d) a - b * c \n";
    cout << "\t e) a < b o c < d\n";
    pause();
};
void menu2() {
    menuVars menuv;
    node root[4] = { nullptr,nullptr,nullptr,nullptr };
    string names[4] = {"a","b","c","d"};
    menuv.name = "\tejercicio 2 \n"; \
    const int menuexit = 4;
    menuv.exit = menuexit;
    menuv.program = 2;
    for (int i = 0; i < 4; i += 1) {
        menuv.namef = names[i];
        menuv.namef += ".txt";
        read(menuv, root[i],1);
    }
    cls();
    while (menuv.w != menuv.exit) { // its a easy menu
        menuv.enter = false;
        while (!menuv.enter) {
            cls();//cursor appears only in selected option 
            cout << menuv.name << "  ";
            if (menuv.w == 1) { cout << ">>"; } cout << " ver arboles en preorder \n" << "  ";
            if (menuv.w == 2) { cout << ">>"; } cout << " ver arboles en order \n" << "  ";
            if (menuv.w == 3) { cout << ">>"; } cout << " ver arboles en postorder \n" << "  ";
            if (menuv.w == menuv.exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            menuv.detection();
            //detection of the cursor
        }
        cls();
        switch (menuv.w) {
        case 1:
            cout << "\t en preorder: \n";
            for (int i = 0; i < 4; i += 1) {
                cout << "\t"<<names[i]<<")\t";
                root[i]->showtreepreorder(2);
                cout << "\n";
            }
            pause();
            break;
        case 2:
            cout << "\t en inorder: \n";
            for (int i = 0; i < 4; i += 1) {
                cout << "\t" << names[i] << ")\t";
                root[i]->showtreeinorder(2);
                cout << "\n";
            }
            pause();
            break;
        case 3:
            for (int i = 0; i < 4; i += 1) {
                cout << "\t" << names[i] << ")\t";
                root[i]->showtreepostorder(2);
                cout << "\n";
            }
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
void menu3() { // menu para el ejercicio de los empleados
    //advice();
    menuVars menuv;
    menuv.name = " ejercicio 3 \n";
    const int menuexit = 4;
    menuv.exit = menuexit;
    menuv.program = 3;
    node root = nullptr;
    count contador;
    cls();
    cout << "   ingresar el nombre del archivo (sin el .txt): ";
    cin >> menuv.namef;
    menuv.namef += ".txt";
    read(menuv, root,0);
    cls();
    while (menuv.w != menuv.exit) { // its a easy menu
        menuv.enter = false;
        while (!menuv.enter) {
            cls();//cursor appears only in selected option 
            cout << menuv.name << "  ";
            if (menuv.w == 1) { cout << ">>"; } cout << " ingresar nodo \n" << "  ";
            if (menuv.w == 2) { cout << ">>"; } cout << " contar nodos \n" << "  ";
            if (menuv.w == 3) { cout << ">>"; } cout << " ver el arbol (debug, los muestra en lista, de menor a mayor) \n" << "  ";
            if (menuv.w == menuv.exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            menuv.detection();
            //detection of the cursor
        }
        cls();
        switch (menuv.w) {
        case 1:
            addvalue(root);
            break;
        case 2:
            contador.parentnodes = 0;
            contador.leafnodes = contador.parentnodes;
            contadorpedorro(root, contador);
            cout << "\t cantidad de nodos parent: "<<contador.parentnodes<<" \n";
            cout << "\t cantidad de nodos leaf: " << contador.leafnodes << " \n";
            pause();
            break;
        case 3:
            root->showtreeinorder(0);
            pause();
            break;
        case menuexit:
            //exit message
            free (root);
            break;
        default:
            errormens();
            break;
        }
    }
};
void menu4() { // menu para el ejercicio 4
    //advice();
    menuVars menuv;
    menuv.name = " ejercicio 4 \n";
    const int menuexit = 4;
    menuv.exit = menuexit;
    menuv.program = 3;
    tree root[9999];
    tree selected;
    count contador;
    cls();
    cout << "   ingresar el nombre del archivo (sin el .txt): ";
    cin >> menuv.namef;
    menuv.namef += ".txt";
    readstatic(menuv, root);
    cls();
    while (menuv.w != menuv.exit) { // its a easy menu
        menuv.enter = false;
        while (!menuv.enter) {
            cls();//cursor appears only in selected option 
            cout << menuv.name << "  ";
            if (menuv.w == 1) { cout << ">>"; } cout << " ingresar nodo \n" << "  ";
            if (menuv.w == 2) { cout << ">>"; } cout << " contar nodos \n" << "  ";
            if (menuv.w == 3) { cout << ">>"; } cout << " ver el arbol de menor a mayor (debug) \n" << "  ";
            if (menuv.w == menuv.exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            menuv.detection();
            //detection of the cursor
        }
        cls();
        switch (menuv.w) {
        case 1:
            cout << "\t ingresar valor del nodo: ";
            cin >> selected.num;
            if (root[0].isnode != false && root[0].isroot == false) {
                    root[0] = selected;
                    root[0].isnode = true;
                    root[0].isroot = true;
            }else addvaluestatic(root,selected);
            break;
        case 2:
            contador.parentnodes = 0;
            contador.leafnodes = contador.parentnodes;
            staticcontadorpedorro(root, contador,0);
            cout << "\t cantidad de nodos parent: " << contador.parentnodes << " \n";
            cout << "\t cantidad de nodos leaf: " << contador.leafnodes << " \n";
            pause();
            break;
        case 3:
            showstatictree(root,0);
            pause();
            //exit message
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
    menuVars menuv;
    menuv.name = " programa de ejercicios de hashing \n";
    const int menuexit = 5;
    menuv.exit = menuexit;
    menuv.program = 3;
    cls();
    while (menuv.w != menuv.exit) { // its a easy menu
        menuv.enter = false;
        while (!menuv.enter) {
            cls();//cursor appears only in selected option 
            cout << menuv.name << "  ";
            if (menuv.w == 1) { cout << ">>"; } cout << " ejercicio 1 \n" << "  ";
            if (menuv.w == 2) { cout << ">>"; } cout << " ejercicio 2 \n" << "  ";
            if (menuv.w == 3) { cout << ">>"; } cout << " ejercicio 3 \n" << "  ";
            if (menuv.w == 4) { cout << ">>"; } cout << " ejercicio 4 \n" << "  ";
            if (menuv.w == menuv.exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            menuv.detection();
            //detection of the cursor
        }
        cls();
        switch (menuv.w) {
        case 1:
            menu1();
            break;
        case 2:
            menu2();
            break;
        case 3:
            menu3();
            break;
        case 4:
            menu4();
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
// end of menus
int main()
{
    menu();
    return 0;
};