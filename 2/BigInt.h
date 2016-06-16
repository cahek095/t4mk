#pragma once
#define max_len 500
#define osn 10
#define len 1
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class BigInt
{

public:

    int amount;     // количество цифр в числе
    int digits[max_len]; // массив цифр в обратном порядке
    int sign;

    BigInt();//Конструктор

    ~BigInt();// деструктор

	// Операции с файлами
    void input(char* f1, int &b);
    void output(char* f2, int &b);

    void LevelUp();
    //Операторы сравнения
    bool operator == (const BigInt &b);
    bool operator != (const BigInt &b);
    bool operator > (const BigInt &b);
    bool operator < (const BigInt &b);
    bool operator <= (const BigInt &b);
    bool operator >= (const BigInt &b);


    //Арифметические операторы
    BigInt operator + (const int &b);
    BigInt operator + (const BigInt &b);
    BigInt operator - (const int &b);
    BigInt operator - (const BigInt &b);
    BigInt operator * (const int &n);
    BigInt operator * (const BigInt &b);
    BigInt operator / (const int &n);
    int operator % (const int &n);
    BigInt operator / (BigInt &b);
    BigInt operator % (BigInt &b);
    
};
BigInt binpow(BigInt &a, BigInt &n,BigInt &m);

