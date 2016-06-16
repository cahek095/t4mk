#include "BigInt.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
void printmenu()
{
    cout << "Long_ariph <A filelame> <operation> <B filelame> <result filename> [-b] [<mod filename>]" << endl << endl;
    cout << "Ariph operations: + , -, * , / ,^, %"<<endl;
    cout << "mod and binary key isn't required "<<endl;
}

int main(int argc, char* argv[])
{
        if (argc < 5)
        {
            cout << "Don't enough arguments" << endl;
            printmenu();
            return -1;
        }

        if (argc > 7)
        {
            cout << "So many arguments" << endl;
            printmenu();
            return -2;
        }

        if (strlen(argv[2]) > 1)
        {
            cout << "unknown operation" << endl;
            printmenu();
            return -3;
        }

        char* f1 = argv[1];
        char act = argv[2][0];
        char* f2 = argv[3];
        char* fres = argv[4];
        int bin = 0;
        char* fm = NULL;

        if (argc == 6)
        {
            if (!strcmp(argv[5], "-b"))
                bin = 1;
            else
                fm = argv[5];
        }

        if (argc == 7)
        {
            bin = 1;
            fm = argv[6];
        }

    BigInt c;
    c.amount = 1;
    c.digits[0] = 0;

    BigInt chislo1,chislo2,result,modul;
    chislo1.input(f1,bin);
    chislo2.input(f2,bin);
    switch(act)
    {
        case '+':
            if ((chislo1.sign == 1) && (chislo2.sign == 0)){
                if (chislo1 > chislo2){
                    result = chislo1 - chislo2;
                    result.sign = 1;
                }
                if (chislo1 <= chislo2){
                    result = chislo2 - chislo1;
                }
            }
            if ((chislo1.sign == 0) && (chislo2.sign == 0)){
                result = chislo1 + chislo2;
            }
            if ((chislo1.sign == 0) && (chislo2.sign == 1)){
                if (chislo1 >= chislo2){
                    result = chislo1 - chislo2;
                }
                if (chislo1 < chislo2){
                    result = chislo2 - chislo1;
                    result.sign = 1;
                }
            }
            if ((chislo1.sign == 1) && (chislo2.sign == 1)){
                result = chislo2 + chislo1;
                result.sign = 1;
            }
            break;
        case '-':
            if ((chislo1.sign == 1) && (chislo2.sign == 0)){
                result = chislo1 + chislo2;
                result.sign = 1;
            }
            if ((chislo1.sign == 0) && (chislo2.sign == 0)){
                if (chislo1 < chislo2){
                    result = chislo2 - chislo1;
                    result.sign = 1;
                }else
                    result = chislo1 - chislo2;
            }
            if ((chislo1.sign == 0) && (chislo2.sign == 1)){
                result = chislo1 + chislo2;
                result.sign = 0;
            }
            if ((chislo1.sign == 1) && (chislo2.sign == 1)){
                result = chislo2 - chislo1;
                if (chislo1 > chislo2)
                    result.sign = 1;
            }
            break;
        case '*':
            result = chislo1 * chislo2;
            if (chislo1.sign!=chislo2.sign)
                 result.sign = 1;
            break;
        case '/':
            if (chislo2 == c){
                cout << endl << "На ноль делить нельзя\n";
                return 0;
            }
            result = chislo1 / chislo2;
            if (chislo1.sign!=chislo2.sign)
                 result.sign = 1;
            break;
        case '%':
            if (chislo2 == c){
                cout << endl << "На ноль делить нельзя\n";
                return 0;
            }
            result = chislo1 % chislo2;
            break;
        case '^':
            //char fm[20];
            //cout << "Введите имя файла с модулем\n";
            //scanf("%s",fm);
            modul.input(fm,bin);
            if (chislo2.sign == 1){
                cout << endl << "Степень должна быть больше нуля!" << endl;
                return 0;
            }
            if (modul.sign == 1){
                cout << endl << "Модуль должен быть больше нуля!" << endl;
                return 0;
            }
            if (chislo1.sign == 1)
                if (chislo2 % 2 != 0)
                    result.sign = 1;
            result = binpow(chislo1,chislo2,modul);
            if (chislo1.sign == 1)
                if (chislo2 % 2 != 0)
                    result.sign = 1;
            break;
    }
    result.output(fres,bin);
    return 0;
}
