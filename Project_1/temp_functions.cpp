#include <iostream>
#include <stdio.h>
#include <string.h>
#include "temp_functions.h"

using namespace std;

int razbor(char *str, struct Record &record, int i) {
	char* part;
	int error_in_row = 0;
	part=strtok(str, ";");
	record.year = (short)atoi(part);
	if (record.year < 1970 || record.year > 2021) {
		printf("Ошибка года в строке: %d\n", i); 
		error_in_row = i;
	}
	part = strtok(NULL, ";");
	record.month = (short)atoi(part);
	if (record.month < 1 || record.month > 12) {
		printf("Ошибка месяца в строке: %d\n", i);
		error_in_row = i;
	}
	part = strtok(NULL, ";");
	record.day = (short)atoi(part);
	if (record.day < 1 || record.day > 31) {
		printf("Ошибка дня в строке: %d\n", i);
		error_in_row = i;
	}
	part = strtok(NULL, ";");
	record.hour = (short)atoi(part);
	if (record.hour < 1 || record.hour > 24) {
		printf("Ошибка в часе в строке: %d\n", i);
		error_in_row = i;
	}
	part = strtok(NULL, ";");
	record.minute = (short)atoi(part);
	if (record.minute < 1 || record.minute > 60) {
		printf("Ошибка в минутах в строке: %d\n", i);
		error_in_row = i;
	}
	part = strtok(NULL, "\n");
	record.temperature = (short)atoi(part);
	if (record.temperature < -99 || record.temperature > 99) {
		printf("Ошибка значения температуры в строке: %d\n", i);
		error_in_row = i;
	}
	if (error_in_row != 0) {
		printf("Удаляем строку: %d\n", error_in_row);
		return error_in_row;
	}
	return 0;
}

int menu() { //вывод на консоль текста меню и ввод корректного выбора
	cout << "\n1 - Статистика за год\n";
	cout << "2 - Статистика за месяц\n";
	cout << "3 - Печать всех очищенных данных\n";
	cout << "4 - Помощь\n";
	cout << "5 - Выход из программы\n";
	int k;
	cout << "Ваш выбор: ";
	cin >> k;
	while (k < 1 || k>5) {
		cout << "Неверный выбор! Повторите ввод: ";
		cin >> k;
	}
	cout << endl;
	return k;
}

void year_statistics(struct Record *list, int n) {
	cout << "Статистика за год\n";
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum = sum + (list + i)->temperature;
	}
	printf("\nСреднегодовая температура = %.3f\n", (float)sum/n);
	int max = list->temperature;
	for (int i = 0; i < n; i++) {
		if ((list + i)->temperature > max) max = (list + i)->temperature;
	}
	printf("\nМаксимальная годовая температура = %d\n", max);
	int min = list->temperature;
	for (int i = 0; i < n; i++) {
		if ((list + i)->temperature < min) min = (list + i)->temperature;
	}
	printf("\nМинимальная годовая температура = %d\n", min);
}

int choose_month(void) { //вывод на консоль текста выбора месяца и ввод корректного выбора
	cout << "\n1 - Статистика за январь\n";
	cout << "2 - Статистика за февраль\n";
	cout << "3 - Статистика за март\n";
	cout << "4 - Статистика за апрель\n";
	cout << "5 - Статистика за май\n";
	cout << "6 - Статистика за июнь\n";
	cout << "7 - Статистика за июль\n";
	cout << "8 - Статистика за август\n";
	cout << "9 - Статистика за сентябрь\n";
	cout << "10 - Статистика за октябрь\n";
	cout << "11 - Статистика за ноябрь\n";
	cout << "12 - Статистика за декабрь\n";
	int k;
	cout << "Ваш выбор: ";
	cin >> k;
	while (k < 1 || k>12) {
		cout << "Неверный выбор! Повторите ввод: ";
		cin >> k;
	}
	cout << endl;
	return k;
}

void month_statistics(struct Record *list, int n) {
	cout << "Статистика за месяц\n";
	int month = choose_month();
	int sum = 0; int days = 0;
	for (int i = 0; i < n; i++) {
		if ((list + i)->month == month) {
			sum = sum + (list + i)->temperature; 
			days++;
		}
	}
	printf("\nСреднемесячная температура = %.3f\n", (float)sum/days);
	int max = -99;
	for (int i = 0; i < n; i++) {
		if ((list + i)->month == month) 
			if ((list + i)->temperature > max) max = (list + i)->temperature;
	}
	printf("\nМаксимальная месячная температура = %d\n", max);
	int min = 99;
	for (int i = 0; i < n; i++) {
		if ((list + i)->month == month) 
			if ((list + i)->temperature < min) min = (list + i)->temperature;
	}
	printf("\nМинимальная месячная температура = %d\n", min);
}

void printList(struct Record *list, int n) {
	cout << "Очищенные данные с датчика температуры:\n";
	for (int i = 0; i < n; i++) {
		cout << " Год: " << list[i].year << " Месяц: " << list[i].month << " День: " << list[i].day;
		cout << " Час: " << list[i].hour << " Минута: " << list[i].minute << " Температура: " << list[i].temperature;
		cout << endl;
	}
	cout << endl;
}

void help(void) {
	cout << "Файл помощи\n";
}

void finish(struct Record *list, int n) {
	cout << "Выход из программы\n";
}

int main(int argc, char *argv[]) {
    FILE *input_ = fopen(argv[1],"r");
    if (input_ == 0) {
        printf("Ошибка открытия файла для чтения\n");
        return 1;
    }
    char str[MAX];
    fscanf(input_,"%s", str); //пропускаем заголовок
    int n = 0;
    while (fscanf(input_,"%s", str)==1) {
        //printf("%s\n", str);
        n++;
    }
    if (fclose(input_) != 0) {
        printf("Ошибка закрытия файла для чтения\n");
    }
    printf("Количество строк в файле = %d\n", n);
    
    FILE *input = fopen(argv[1],"r");
    if (input == 0) {
        printf("Ошибка открытия файла для чтения\n");
        return 1;
    }
    struct Record *list = new struct Record[n];
    fgets(str, MAX, input);        //для игнорирования заголовка таблицы
    int i = 0;
    while (i < n ) {
		for (i; i < n; i++) {
			fgets(str, MAX, input);
			//cout << str;
			int result_razbor = razbor(str, list[i], i);//разбор строки и заполнение i-го элемента массива
			if (result_razbor != 0) {	
				n--;
				break;
			}
		}
	}
	//printList(list, n);//вывод массива на консоль
	//cout << endl;
    if (fclose(input_) != 0) {
        printf("Ошибка закрытия файла для чтения\n");
    }
    
	int menu_item;
	while (true) {//бесконечный цикл вывода меню и выполнения одного пункта 
		menu_item = menu();
		switch (menu_item) {
		case 1: year_statistics(list, n); break;
		case 2: month_statistics(list, n); break;
		case 3: printList(list, n); break;
		case 4: help(); break;
		case 5: finish(list, n); delete[] list; return 0;
		}
	}
	delete[] list;
	return 0;
}

/*
Создание консольного приложения - Статистика температуры.
Необходимо реализовать консольное приложение, которое
осуществляет считывание текстового файла csv, состоящего из
строк следующего формата:
YEAR;MONTH;DAY;HOUR;MINUTE;TEMPERATURE
dddd;mm;dd;hh;mm;temperature
dddd - год 4 цифры
mm - месяц 2 цифры
dd - день 2 цифры
hh - часы 2 цифры
mm - минуты 2 цифры
temperature - целое число от -99 до 99
В файле хранится статистика собранная датчиком температуры за
1 календарный год. Предполагается, что датчик собирал
информацию не чаще чем 1 раз в минуту и сохранял в заданном
формате каждое значение в текстовый файл с новой строки. В
какой-то момент времени датчик мог не работать, тогда данные по
этому периоду могут отсутствовать.

Необходимо вывести статистику по каждому месяцу:
• среднемесячная температура
• минимальная температура
• максимальная температура
Также необходимо вывести статистику за год:
• среднегодовая температура
• минимальная температура
• максимальная температура
Приложение должно обрабатывать аргументы командной строки:
минимальный набор поддерживаемых ключей:
• -h Описание функционала приложения. Список ключей, которые
обрабатывает данное приложение и их назначение.
• -f <filename.csv> входной файл csv для обработки.
• -m <номер месяца> если задан данный ключ, то выводится
только статистика за указанный месяц.
Приложение должно корректно работать на любых входных
данных, если формат csv файла не соответствует заданному, то
необходимо указать номер строки файла csv, в которой
обнаружена ошибка и не учитывать данную строку.
Приложение должно собираться при помощи утилиты make.
Все прототипы функций используемые в приложении должны быть
вынесены в отдельный файл temp_functions.h
Тексты функций - в файл temp_functions.c.
Для реализации приложения рекомендуется использовать массив
из структурного типа данных для хранения показаний датчика.
*/
