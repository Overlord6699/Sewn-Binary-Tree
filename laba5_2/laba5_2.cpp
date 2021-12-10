#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "BinaryTree.h"
#include "SewnBinaryTree.h"

//сим сим
//удаление работает только с сим

void printInfo1() 
{
    cout << "1 Выйти из программы" << endl;
    cout << "2 Добавить новый узел" << endl;
    cout << "3 Сменить дерево" << endl;
    cout << "4 Удаление элемента" << endl;
    cout << "5 Поиск по значению" << endl;
    cout << "6 Симметричный обход" << endl;
    cout << "7 Обратный обход" << endl;
    cout << "8 Прямой обход" << endl;
    cout << "9 Визуализировать дерево" << endl;
    cout << "\nВыберите нужное действие и нажмите Enter: ";
}

void printInfo2()
{
    cout << "1 Выйти из программы" << endl;
    cout << "2 Добавить новый узел" << endl;
    cout << "3 Сменить дерево" << endl;
    cout << "4 Удаление элемента" << endl;
    cout << "5 Поиск по значению" << endl;
    cout << "6 Cимметричный обход" << endl;
    cout << "7 Обратный обход" << endl;
    cout << "8 Прямой обход" << endl;
    cout << "9 Визуализировать дерево" << endl;
    cout << "10 Прошить дерево" << endl;
    cout << "\nВыберите нужное действие и нажмите Enter: ";
}

void printSewKindsInfo()
{
    cout << "\nВведите нужный вид прошивки:";
    cout << "\n1 - правая";
    cout << "\n2 - левая";
    cout << "\n3 - симметричная";
}

int retrieveElem()
{
    int tmpElem;
    bool isIncorrect;
    cout << "Введите элемент:" << endl;
    do {
        isIncorrect = false;
        try {
            cin >> tmpElem;
        }
        catch (...) {
            cout << "Введено некорректное значение. Введите число: " << endl;
            isIncorrect = true;
        }
    } while (isIncorrect);

    return tmpElem;
}

/*

//для поиска длины поддерева
void findSmallTreeLength(BinaryTree& myBinaryTree) 
{
    nodeptr node = NULL;
    int tmpElem, length = 0;
    tmpElem = retrieveElem();
    node = myBinaryTree.find(tmpElem, myBinaryTree.root);

    if (node != NULL)
        length = myBinaryTree.get_tree_height(node);

    cout << "Длина поддерева = " << length;
    cout << endl;
}

*/

int retrieveChoice(const int minValue, const int maxValue) 
{
    int choice = 0;
    bool isIncorrect;

    do {
        isIncorrect = false;
        try {
            cin >> choice;
        }
        catch (...) {
            cout << "Введено некорректное значение. Введите число: " << endl;
            isIncorrect = true;
        }
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите число от " << minValue << " до " << maxValue << ": " << endl;
            isIncorrect = true;
        }
        if (choice < minValue || choice > maxValue && !isIncorrect) {
            isIncorrect = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите число от " << minValue << " до " << maxValue << ": " << endl;
        }
    } while (isIncorrect);
    return choice;
}

void processChoice(BinaryTree& myBinaryTree, SewnBinaryTree& mySewnTree, int& choice, bool isSewnTree = false)
{
    int tmpElem, findElem, delElem;
    nodeptr minElem = NULL, maxElem = NULL, prevPtr = NULL;
    int length;

    isSewnTree? printInfo2(): printInfo1();
    
   
    choice = (!isSewnTree)? retrieveChoice(1, 9): retrieveChoice(1, 10);
    do
    {
        switch (choice)
        {
        case 1:
            break;
        case 2:
            cout << "\n\t\tДобавление нового узла." << endl;
            tmpElem = retrieveElem();

            if (!isSewnTree)
                myBinaryTree.insert(tmpElem, myBinaryTree.root);
            else
                if (mySewnTree.isSewn)
                    mySewnTree.insertInSewnTree(tmpElem);
                else
                    mySewnTree.insert(tmpElem, mySewnTree.root);
            
            cout << "\nНовый элемент добавлен успешно\n" << endl;
            break;
        case 3:
            isSewnTree = !isSewnTree;
            break;
        case 4:
            cout << "\nКакой узел удалять? ";
            delElem = retrieveElem();

            if (!isSewnTree) {
                myBinaryTree.del(delElem, myBinaryTree.root);
            }
            else {
                if(mySewnTree.isSewn)
                    if (mySewnTree.find(delElem, mySewnTree.root))
                    {
                        mySewnTree.remove(mySewnTree.root, delElem);
                        cout << "\nЭлемент был успешно удалён";
                    }
                else
                    mySewnTree.del(delElem, mySewnTree.root);
            }
            
            break;
        case 5:
            findElem = retrieveElem();

            if (!isSewnTree) {             
                if (myBinaryTree.root != NULL)
                {
                    myBinaryTree.find(findElem, myBinaryTree.root);
                }
            }
            else {
                if (mySewnTree.root != NULL)
                {
                    if(!mySewnTree.find(findElem, mySewnTree.root))
                        cout << "\nЭлемент не был найден!";
                }
            }
            break;
        case 6:
            if (!isSewnTree)
            {
                cout << "\nСимметричный обход:\n";
                myBinaryTree.inorder(myBinaryTree.root);
            }
            else {
                if (mySewnTree.isSewn) {
                    cout << "\nСимметричный обход с прошивкой:\n";
                    mySewnTree.inorder(mySewnTree.root);
                }
                else {
                    cout << "\nСимметричный обход:\n";
                    mySewnTree.inorder(mySewnTree.root);
                }
            }
            break;
        case 7:
            if (!isSewnTree)
            {
                cout << "\nОбратный обход:\n";
                myBinaryTree.postorder(myBinaryTree.root);
            }
            else {
                if (mySewnTree.isSewn) {
                    cout << "\nОбратный обход c прошивкой:\n";
                    mySewnTree.postorder(mySewnTree.root);
                }
                else {
                    cout << "\nОбратный обход:\n";
                    mySewnTree.postorder(mySewnTree.root);
                }
            }

            break;
        case 8:
            if (!isSewnTree)
            {
                cout << "\nПрямой обход:\n";
                myBinaryTree.preorder(myBinaryTree.root);
            }
            else {
                if (mySewnTree.isSewn) {
                    cout << "\nПрямой обход c прошивкой:\n";
                    mySewnTree.preorder(mySewnTree.root);
                }
                else {
                    cout << "\nПрямой обход:\n";
                    mySewnTree.preorder(mySewnTree.root);
                }
            }

            break;
        case 9:    
            if (!isSewnTree) {
                BinaryTree visualizer(myBinaryTree);
                visualizer.visualize();
                visualizer.~BinaryTree();
            }
            else {
                SewnBinaryTree visualizer(mySewnTree);
                visualizer.visualize();
                visualizer.~SewnBinaryTree();
            }
            break;
        case 10:
            printSewKindsInfo();
            cout << "\nВведите Ваш выбор:";

            tmpElem = retrieveChoice(1, 3);
            mySewnTree.sew(tmpElem);
            break;
        }

        cout << endl;
        if (choice != 1) {
            system("pause");
            system("cls");
            processChoice(myBinaryTree, mySewnTree, choice, isSewnTree);
        }
    } while (choice != 1);
} 

int main()
{
    BinaryTree myBinaryTree, myBinaryTree2;

    setlocale(LC_ALL, "Russian");

    for (int i = 0; i < 15; i++)
    {
        int ran = rand() % 100;
        myBinaryTree.insert(ran, myBinaryTree.root);
    } 

    for (int i = 0; i < 15; i++)
    {
        int ran = rand() % 100;
        myBinaryTree2.insert(ran, myBinaryTree2.root);
    }

    SewnBinaryTree mySewnTree = SewnBinaryTree(myBinaryTree2);
    myBinaryTree2.~BinaryTree();

    int choice = 0;
    processChoice(myBinaryTree, mySewnTree, choice);
    system("cls");

    myBinaryTree.~BinaryTree();
    mySewnTree.~SewnBinaryTree();

    return 0;
}
