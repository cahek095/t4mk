#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

const int max_len = 500; // в зависимости от задачи
int osn = 10;
int len = 1;

struct BigInt
{
    int amount=0;     // количество цифр в числе
    int digits[max_len]; // массив цифр в обратном порядке
    int sign=0;

    BigInt(){
        amount = 1;
        for (int i = 0; i < 500; ++i)
            digits[i] = 0;
        sign=0;
    }

    ~BigInt(){
        amount = 0;
        for (int i = 0; i < 500; ++i)
            digits[i] = 0;
        sign=0;
    }

    void input(char* f1, int &b)
      {
        FILE* f;
        if (b == 1){
            f = fopen(f1, "rb");
            fseek(f, 0, SEEK_END);
            int count = ftell(f);
            fseek(f,0,SEEK_SET);
            char c;
            fread(&c,sizeof(char),1,f);
            if(c=='+'){
                sign = 0;
            }else{
                sign = 1;
            }
            for (int i=0;i<count-1;++i)
                fread(&digits[count-i-2],sizeof(char),1,f);
            amount = count;
            int pos = amount;
            while (pos>=0 && !digits[pos])
                pos--;
            amount = pos+1;
            fclose(f);
        }
        else{
            f = fopen(f1, "r");
            memset(digits,0,sizeof(digits));
            char str[500];
            char c = fgetc(f);
            if(c=='+'){
                sign = 0;
            }else{
                sign = 1;
            }
            fgets(str,500,f);
            int pos = 0;
            for (int i=strlen(str)-2;i>=0;i--)
              digits[pos++] = str[i] - '0';
            amount = strlen(str)-1;
            fclose(f);
        }
      }

    void output(char* f2, int &b)
    {
        FILE* f;
        if (b == 1){
            f = fopen(f2, "ab");
            rewind(f);
            char c;
            if(sign==0){
                c = '+';
            }else{
                c = '-';
            }
            fwrite(&c,sizeof(char),1,f);
            for (int i=amount-1;i>=0;i--)
                fwrite(&digits[i],sizeof(char),1,f);
            fclose(f);
        }
        else{
            f = fopen(f2, "w");
            if (f == NULL) {
                    printf("Error opening file");
                    }
            char c;
            if(sign==0){
                c = '+';
            }else{
                c = '-';
            }
            fputc(c,f);
            for (int i=amount-1;i>=0;i--)
                fputc(digits[i]+'0',f);
            fclose(f);
        }
    }

    void LevelUp()
    {
      for (int i = amount;i>=1;i--)
        digits[i] = digits[i-1];
      if (digits[amount])
        amount++;
    }
};

bool operator == (const BigInt &a, const BigInt &b)
{
  if (a.amount!=b.amount)
    return false;
  for (int i=0;i<a.amount;i++)
  {
    if (a.digits[i]!=b.digits[i])
      return false;
  }
  return true;
}

bool operator != (const BigInt &a, const BigInt &b)
{
  if (a.amount!=b.amount)
    return true;
  for (int i=0;i<a.amount;i++)
  {
    if (a.digits[i]!=b.digits[i])
      return true;
  }
  return false;
}

bool operator > (const BigInt &a, const BigInt &b)
{
  if (a.amount!=b.amount)
    return a.amount>b.amount;
  for (int i=a.amount-1;i>=0;i--)
  {
    if (a.digits[i]!=b.digits[i])
      return a.digits[i]>b.digits[i];
  }
  return false;
}

bool operator < (const BigInt &a, const BigInt &b)
{
  if (a.amount!=b.amount)
    return a.amount<b.amount;
  for (int i=a.amount-1;i>=0;i--)
  {
    if (a.digits[i]!=b.digits[i])
      return a.digits[i]<b.digits[i];
  }
  return false;
}

bool operator <= (const BigInt &a, const BigInt &b)
{
  if (a.amount!=b.amount)
    return a.amount<=b.amount;
  for (int i=a.amount-1;i>=0;i--)
  {
    if (a.digits[i]!=b.digits[i])
      return a.digits[i]<=b.digits[i];
  }
  return true;
}

bool operator >= (const BigInt &a, const BigInt &b)
{
  if (a.amount!=b.amount)
    return a.amount>=b.amount;
  for (int i=a.amount-1;i>=0;i--)
  {
    if (a.digits[i]!=b.digits[i])
      return a.digits[i]>=b.digits[i];
  }
  return true;
}

BigInt operator + (const BigInt &a, const int &b)
{
  BigInt res = a;
  int pos = 0;
  res.digits[0] += b;
  while (res.digits[pos]>=osn)
  {
    res.digits[pos+1]++;
    res.digits[pos++]-=osn;
  }
  if (res.digits[res.amount])
    res.amount++;
  int pos1 = a.amount;
  while (pos1>=0 && !res.digits[pos1])
      pos1--;
  res.amount = pos1+1;
  return res;
}

BigInt operator + (const BigInt &a, const BigInt &b)
{
  BigInt res;
  res.amount = max(a.amount,b.amount);
  int r = 0;
  for (int i=0; i < res.amount || r;i++)
  {
    res.digits[i] = a.digits[i] + b.digits[i] + r;
    if (res.digits[i]>=osn)
    {
      res.digits[i]-=osn;
      r = 1;
    }
    else
      r = 0;
  }
  if (res.digits[res.amount])
    res.amount++;
  int pos = a.amount;
  while (pos>=0 && !res.digits[pos])
      pos--;
  res.amount = pos+1;

  return res;
}



BigInt operator - (const BigInt &a, const int &b)
{
  BigInt res = a;
  int pos = 0;
  res.digits[0] -= b;
  while (res.digits[pos] < 0)
  {
    res.digits[pos+1] --;
    res.digits[pos++] +=osn;
  }
  if (res.amount && !res.digits[res.amount-1])
    res.amount--;
  int pos1 = a.amount;
  while (pos1>=0 && !res.digits[pos1])
      pos1--;
  res.amount = pos1+1;
  return res;
}



BigInt operator - (const BigInt &a, const BigInt &b)
{
    BigInt res = a;
    int r = 0;
    for (int i = 0;i<res.amount;i++)
    {
        res.digits[i] -= b.digits[i] + r;
        if (res.digits[i]<0)
        {
            res.digits[i]+=osn;
            r = 1;
        }
        else
            r = 0;
    }
    if (!res.digits[res.amount-1] && res.amount != 1)
        res.amount--;
    int pos = a.amount;
    while (pos>=0 && !res.digits[pos])
        pos--;
    res.amount = pos+1;
    return res;
}



BigInt operator * (const BigInt &a, const int &n)
{
  BigInt res;
  res.amount = a.amount;

  int r = 0;
  for (int i=0;i<res.amount || r;i++)
  {
    res.digits[i] = a.digits[i] * n + r;
    r = res.digits[i]/osn;
    res.digits[i] -= r*osn;
  }
  if (res.digits[res.amount])
    res.amount++;
  r = 0;
  int pos = a.amount;
  while (pos>=0 && !res.digits[pos])
      pos--;
  res.amount = pos+1;
  return res;
}

BigInt operator * (const BigInt &a, const BigInt &b)
{
  BigInt res;
  for (int i=0;i<a.amount;i++)
  {
    int r = 0;
    for (int j=0;j<b.amount || r;j++)
    {
      res.digits[i+j] += a.digits[i] * b.digits[j] + r;
      r = res.digits[i+j] / osn;
      res.digits[i+j] -= r*osn;
    }
    r = 0;
  }
  int pos = a.amount + b.amount;
  while (pos>0 && !res.digits[pos])
    pos--;
  res.amount = pos + 1;
  return res;
}


BigInt operator / (const BigInt &a, const int &n)
{
  BigInt res;
  res.amount = a.amount;
  int ost = 0;
  for (int i=res.amount-1;i>=0;i--)
  {
    int cur = ost * osn + a.digits[i];
    res.digits[i] = cur / n;
    ost = cur % n;
  }
  if (!res.digits[res.amount-1] && res.amount != 1)
    res.amount--;
  int pos = a.amount;
  while (pos>=0 && !res.digits[pos])
      pos--;
  res.amount = pos+1;
  return res;
}

int operator % (const BigInt &a, const int &n)
{
  BigInt res;
  res.amount = a.amount;
  int ost = 0;
  for (int i=res.amount-1;i>=0;i--)
  {
    int cur = ost * osn + a.digits[i];
    res.digits[i] = cur / n;
    ost = cur % n;
  }
  int pos = a.amount;
  while (pos>=0 && !res.digits[pos])
      pos--;
  res.amount = pos+1;
  return ost;
}

BigInt operator / (const BigInt &a, const BigInt &b)
{
    if (a < b)
    {
        BigInt res;
        res.amount = 1;
        res.digits[0]=0;
        return res;
    }
    BigInt res;
    BigInt curValue;
    curValue.amount=1;
    for (int i = a.amount-1; i>=0; i--)
    {
        curValue.LevelUp(); // * osn
        curValue.digits[0] = a.digits[i];
        // подбираем максимальное число x, такое что b * x <= curValue
        int x = 0;
        int l = 0, r = osn;
        while (l <= r)
        {
            int m = (l + r) / 2;
            BigInt cur = b * m;
            if (cur <= curValue)
            {
                x = m;
                l = m+1;
            }
            else
                r = m-1;
            for (int j = cur.amount-1; j>=0; --j)
                cur.digits[j] = 0;

        }
        res.digits[i] = x;
        curValue = curValue - b * x;
    }
    int pos = a.amount;
    while (pos>=0 && !res.digits[pos])
        pos--;
    res.amount = pos+1;

    return res;
}

BigInt operator % (const BigInt &a, const BigInt &b)
{
    BigInt res;
    BigInt curValue;
    curValue.amount=1;
    for (int i = a.amount-1; i>=0; i--)
    {
        curValue.LevelUp(); // * osn
        curValue.digits[0] = a.digits[i];
        // подбираем максимальное число x, такое что b * x <= curValue
        int x = 0;
        int l = 0, r = osn;
        while (l <= r)
        {
            int m = (l + r) / 2;
            BigInt cur = b * m;
            if (cur <= curValue)
            {
                x = m;
                l = m+1;
            }
            else
                r = m-1;
            for (int j = cur.amount-1; j>=0; --j)
                cur.digits[j] = 0;

        }
        res.digits[i] = x;
        curValue = curValue - b * x;
    }
    int pos = a.amount;
    while (pos>=0 && !res.digits[pos])
        pos--;
    res.amount = pos+1;
  return curValue;
}

BigInt binpow (const BigInt &a, const BigInt &n, const BigInt &m)
{
    BigInt c;
    c.amount = 1;
    c.digits[0] = 0;
    BigInt res;
    res.amount = 1;
    res.digits[0] = 1;
    BigInt cur = a % m;
    BigInt N = n;

    while (N > c)
    {
        if (N % 2 == 1)
        {
            res = res * cur;
            res = res % m;
        }
        cur = cur * cur;
        cur = cur % m;
        N = N / 2;
    }
    /*int pos = a.amount;
    while (pos>=0 && !res.digits[pos])
        pos--;
    res.amount = pos+1;*/
    return res;
}

int main()
{
    int bin = 0;
    BigInt c;
    c.amount = 1;
    c.digits[0] = 0;
    cout << "Введите 1 если хотите работать с бинарными файлами\n";
    scanf("%d",&bin);
    cout << "Введите имя файла с 1 числом\n";
    char f1[20];
    scanf("%s", f1);
    cout << "Введите имя файла с 2 числом\n";
    char f2[20];
    scanf("%s",f2);
    cout << "Введите операцию\n";
    char act;
    scanf(" %c", &act);
    cout << "Введите имя файла с результатом\n";
    char fres[20];
    scanf("%s",fres);
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
            char fm[20];
            cout << "Введите имя файла с модулем\n";
            scanf("%s",fm);
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
