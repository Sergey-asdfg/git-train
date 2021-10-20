#pragma once

#define MAX 128									//максимальное число символов в строке входного файла

												//наша главная структура из которой будем делать массив структур
struct Record {
    short year;
    short  month;
    short  day;
    short  hour;
    short  minute;
    short  temperature;
};

int razbor(char *str, struct Record &record, int i); //парсинг строк из файла в массив структур

int menu(void); 									//функция меню

void year_statistics(struct Record *list, int n); 	//статистика за год

void month_statistics(struct Record *list, int n);  //статистика за месяц

int choose_month(void);								//выбор месяца для статистики

void help(void);  									//описание программы

void printList(struct Record *list, int n);			//расспечатка массива структур, после обр ошибок

void finish(struct Record *list, int n);			//выход из программы
