#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

struct in_queue{         //структура для очереди
	int data;               //поле для значений
	struct in_queue *next;  // указатель на следующий элемент
	int size;             //размер очереди
	int el_count;         //количество элементов
};
struct out_stack{        //структура для стека
	struct in_queue *start;  //указатль на начало стека
	struct in_queue *end;    //указатель на конец стека
	struct out_stack *next;   //указатель на следующий элемент
};
///////////////////////////
//Очередь начало
int start_work_with_interior();  //прототип функции начала работы с очередью
void make_in_empty(struct in_queue **,struct in_queue **);  //сделать очереедь пустой
void is_in_empty(struct in_queue *);      //проверка - пустая ли очередь
void show_in_queue(struct in_queue *);   //вывести начало очереди
void delete_in_start(struct in_queue **,struct in_queue **); //удалить начало очереди
int take_in_start(struct in_queue **,struct in_queue **, int **); //взять начало очереди
void change_in_start(struct in_queue *); //изменить начало очереди
int add_to_end_in(struct in_queue **,struct in_queue **); //добавить в начало очереди
void print_in(struct in_queue *,struct in_queue *); //напечатать очередь

struct in_queue *menu_in_queue(struct in_queue *start,int input_flag)    //функция меню очереди
{
	struct in_queue *end = start;     // создаём указатель на конец равным указателю на начало
	int *taken_element = NULL, choice = 0,access = 0,i,size,el_count;   //объявляем переменные
	char choice_str[30]; //строка для считывания ввода пользователя
	if(!input_flag)   //если к этой очереди впервые обращаемся
	{
		system("cls");  //настройки текста
		system("color B");
		printf("Vvedite razmer ocheredi -  ");
		scanf("%d", &size);//считываем размер очереди
		el_count = 0;  //количество элементов = 0
	}
	else  //иначе
	{
		for(;end->next != NULL; end = end->next);   //подсчитываем размер и количество элементов
		size = start->size;
		el_count = start->el_count;
	}

	while(choice != 10)    //пока не был выбран выход
	{
		choice = -1;  //изначально выбор - -1
		system("cls");  //настройки текста
		system("color B");
		printf("Vnytrennaia cochered\n");
		if(access)     //если был получен доступ
			if(!input_flag)   //если впервые обращаемся к очереди
			printf("Ochered inicializirovana\n");
			else
			printf("Dostyp polychen\n");
		else    //если доступ не был получен
			if(!input_flag) //если впервые обращаемся к очереди
			printf("Ochered ne bila inicializirovana\n");
			else
			printf("Dostyp ne polychen\n");
		if(access)//если доступ был получен
		{
			printf("Razmer ocheredi - %d\n",size);  //вывод размера
			printf("Kolichestvo elemetov d ocheredi - %d\n",el_count);  //вывод количества элементов
			print_in(start,end);//распечатать очередь
		}
		if(taken_element != NULL)    //если взятый элемент не НУЛЛ
		printf("\nVzatiy element - %d\n\n",*taken_element); //вывод взятого элемента
		printf("Menu:\n");  //построение меню
		printf("1)Nachat raboty s ocherediu\n");
		printf("2)Sdelat ochered pystoi\n");
		printf("3)Proverit - pysta li ochered?\n");
		printf("4)Pokazat nachalo ocheredi\n");
		printf("5)Ydalit nachalo ocheredi\n");
		printf("6)Vzat iz nachala ocheredi\n");
		printf("7)Izmenit nachalo ocheredi\n");
		printf("8)Dobavit v konec ocheredi\n");
		printf("9)Napechatat ochered\n");
		printf("10)Zakonchit raboty s ochrediu\n");
		printf("Input:   ");
		gets(choice_str); //считываение строки 
		i = 0;
		while(choice_str[i] != '\0')  //пока строка е завершилась
		{
			if(!(choice_str[i] >= '0' && choice_str[i] <= '9'))  //проверка, чтобы были введены лишь цифры
			choice = 0;  //если есть не цифры, то выбор = 0
			i++;
		}
		if(choice)//если выбор не ноль
		choice = atoi(choice_str);  //перевод выбора в число
		if(access || choice == 1 || choice == 10) //если выбор в промежутке от 1 до 10
		{
			switch(choice)  //проверка на соответствие пунктов меню вводу
			{
				case 1:{ //если единицы
					if(!access)   //и доступ не получен
					 access = start_work_with_interior();//вызов функции для получения доступа
					 else
						if(!input_flag) //если не первый ввод
						printf("Ochered yge inicializirovana\n");
						else
						printf("Dostyp yge polychen\n");
				break;}
				case 2:{
				 	 el_count = 0;
					 make_in_empty(&start , &end);//очищение очереди
					 printf("Ochered pystaia seichas\n");
				break;}
				case 3:{    //проверка на пустоту очереди
					 is_in_empty(start);
				break;}
				case 4:{  //показать начало очереди
					 show_in_queue(start);
				break;}
				case 5:{
					 if(el_count > 0)
					 el_count--;
					 delete_in_start(&start , &end);  //удалить начало
				break;}
				case 6:{
					 if(el_count > 0)
					 el_count--;
					 take_in_start(&start , &end, &taken_element);//взять начало
				break;}
				case 7:{
					 change_in_start(start);//изменить начало
				break;}
				case 8:{
					 if(el_count < size) //если количество элементов меньше размера
					 {
						el_count++; //увеличение числа элементов
						add_to_end_in(&start , &end);  //добавление элементов
					 }
					 else
					 printf("Ochered perepolnena\n");
				break;}
				case 9:{
					 print_in(start , end); //распечатать очередь
				break;}
				case 10:{                     //работа завершена
					printf("Rabota s ocherediu zavershena\n");
				break;}
				default:{                    //неверный ввод
					printf("Neverniy vvod\n");
				break;}
			}
		}
		else    //если выбор ноль
		{
			if(!input_flag)//вывод ошибки
			printf("Ochered ne bila inicializirovana\n");
			else
			printf("Dostyp ne bil polychen\n");
		}
		if(choice != 10) //если выбор не десять - нажать на клавишу и продолжить
		printf("Najmite lubyiu knopky...\n");
		getch();
	}
	if(start != NULL)//если старт не НУЛЛ, то
	{
		start->size = size;  //пересчёт размера и длины
		start->el_count = el_count;
	}
	return start;//возврат первого элемента
}

int start_work_with_interior()  //начать работу с очередью
{
	char c[10] = "1234",c1[10] = {0};//инициализация пароля
	printf("Vvedite parol :  ");
	scanf("%s", c1);  //считывание пароля
	if(!strcmp(c,c1)) //если пароль совпал
	{
		printf("Parol podtverjden\n");
		return 1;     //возврат единицы в переменную access в меню
	}
	printf("Neverniy parol\n");
	return 0;  //если не совпал, то ноль
}
void make_in_empty(struct in_queue **start,struct in_queue **end)//очистка очереди
{
	struct in_queue *del;
	while(*start != NULL) //пока первый элемент не НУЛЛ
	{
		del = *start; //удаляемы элемент на старт
		(*start) = (*start)->next;//первый элемент переключается на следующий
		free(del); //удаление первого элемента
	}
	*end = NULL;//конец устанавливается на НУЛЛ
}
void is_in_empty(struct in_queue *start)//проверка на пустоту
{
	if(start == NULL)   //если первый элемент НУЛЛ
	{
		printf("Da, ochered pysta\n"); //пустая
		return 1;
	}
	else  //иначе
	printf("Net, ochered ne pysta\n"); //не пустая
	return 0;
}
void show_in_queue(struct in_queue *start)       //показать первый элемент
{
	if(start != NULL)
	{
		printf("Number in start = %d\n",start->data);  //выовд первого элемента, если очередь не пустая
	}
	else
	printf("Ochered pysta\n");
}
void delete_in_start(struct in_queue **start,struct in_queue **end)// удалить из начала
{
	struct in_queue *del;
	if(*start != NULL)//если очередь не пуста
	{
		del = *start;//ставим указатель удаления на старт
		if(*start == *end)//если конец очереди совпадает с началом
		{
			free(del);  //очищаем очередь
			*end = NULL;
			*start = NULL;
			printf("Ochered pysta\n");
		}
		else
		{
			*start = (*start)->next;//первый элемент переключается на следующий
			free(del);//удаление элемента
		}
	}
	else
	printf("Ochered pysta\n");
}
int take_in_start(struct in_queue **start,struct in_queue **end, int **taken_element)  //взять из начала
{
	struct in_queue *del;
	if(*start != NULL)  //если очередь не пуста
	{
        *taken_element = (int *)malloc(sizeof(int)); //выделение памяти под элемент для взятия
		if(*taken_element == NULL)  //если память не выделилась
		{
			printf("Pamat ne bila videlena\n");  //сообщение об ощибке
			getch();
			return 0;
		}
		**taken_element = (*start)->data;//взятый элемент принимает значение первого элемента
		del = *start;    //далее просто удаление  элемента
		if(*start == *end)
		{
			free(del);
			*end = NULL;
			*start = NULL;
			printf("Ochered pysta\n");
		}
		else
		{
			*start = (*start)->next;
			free(del);
		}
	}
	else
	printf("Ochered pysta\n");
}
void change_in_start(struct in_queue *start) //изменение начала
{
	if(start != NULL)            //если очередь не пуста
	{
		printf("Vvedite novoe znachenie dla \"%d\" -  ", start->data);//ввод нового значения
		scanf("%d",&(start->data));
	}
	else
	printf("Ochered pysta\n");
}
int add_to_end_in(struct in_queue **start,struct in_queue **end)  //добавить элемент в конец
{
	struct in_queue *add; 
	add = (struct in_queue *)malloc(sizeof(struct in_queue));//выделение памяти под добавляемый элемент
	if(add == NULL)    //проверка - выделилась ли память
	{
		printf("Pamyat ne videlilas\n");
		getch();
		return 0;
	}
	printf("Vvedite noviy element -  ");
	scanf("%d",&(add->data));    //ввод нового данного
	if(*start == NULL) //если очередь пустая
	{
		*start = add;  //добавляемый становится первым
		*end = add;  //конец также
		(*start)->next = NULL;  //следующие за ними элементы = НУЛЛ
		(*end)->next = NULL;
	}
	else
	{
		add->next = NULL;  //следующий за добавляемым = НУЛЛ
		(*end)->next = add;//следующий за последним - добавляемый
		*end = add; //добавляемый становится последним
	}
}
void print_in(struct in_queue *start,struct in_queue *end) //распечатка очереди
{
	struct in_queue *output = start; //указатель вывода на старь
	int i = 1;
	if(start != NULL)
	{
		printf("Element 1: %d  - nachalo ocheredi\n",output->data);//вывод первого элемента
		output = output->next;// переключение на следующий
		if(output != NULL)// если не закончился
		for(i = 2;output != end;i++,output = output->next)printf("Element %d: %d\n",i,output->data);//вывод промежуточных
		printf("Element %d: %d  - konec ocheredi\n",i,end->data);//вывод последнего
	}
	else
	printf("Ochered pysta\n");
}
//Очередь конец
//////////////////////////


//////////////////////////
//Стек начало
int start_work_with_outer();
void make_out_empty(struct out_stack **,struct out_stack **);
void is_out_empty(struct out_stack *);
void show_out_stack(struct out_stack *);
void delete_out_start(struct out_stack **,struct out_stack **);
struct in_queue *take_out_start(struct out_stack **,struct out_stack **);
void change_out_start(struct out_stack **,struct out_stack **,int *);
void add_to_start_out(struct out_stack **,struct out_stack **,int *);
void print_out(struct out_stack *,struct out_stack *);

void LSD_in_stack(struct in_queue *start)//функция для вывода внутренней структуры - очереди
{
	struct in_queue *output;
    for(output = start; output != NULL; output = output->next) printf("%d ", output->data); //вывод через пробел всех данныъ в очереди
}

void menu_out_stack(struct out_stack *start)  //меню стека
{
	struct out_stack *end = start;
	struct in_queue *taken_element = NULL;   //указатель на взятый эелмент изначально НУЛЛ
	int choice = 0,access = 0,i,size,el_count; //ввод параметров
	char choice_str[30];
	system("cls");
	system("color D");
	printf("Vvedite razmer steka-  ");
	scanf("%d", &size);
	el_count = 0;
	while(choice != 10)
	{
		choice = -1;
		system("cls");
		system("color D");
		printf("Vneshniy stek\n");
		if(access)
			printf("Stek inicializirovan\n");
		else
			printf("Stek ne bil initializirovan\n");
		if(access)
		{
			printf("Razmer steka - %d\n",size);
			printf("Kolichestvo elementov v steke - %d\n",el_count);
			print_out(start,end);
		}
		if(taken_element != NULL)
		{
			printf("\nVzatiy element - ");
			LSD_in_stack(taken_element);//если взятый элемент не НУЛЛ, то вывод его содержимого
			printf("\n");
		}
		printf("Menu:\n");   //построение меню
		printf("1)Nachat raboty so stekom\n");
		printf("2)Sdelat stek pystim\n");
		printf("3)Proverit - pyst li stek?\n");
		printf("4)Pokazat nachalo steka\n");
		printf("5)Ydalit nachalo steka\n");
		printf("6)Vzat nachali steka\n");
		printf("7)Izmenit nachalo steka\n");
		printf("8)Dobavit v nachalo steka\n");
		printf("9)Napechatat stek\n");
		printf("10)Prekratit raboty so stekom\n");
		printf("Vvod:   ");
		gets(choice_str);
		i = 0;
		while(choice_str[i] != '\0')//защита от некорректного ввода как в очереди
		{
			if(!(choice_str[i] >= '0' && choice_str[i] <= '9'))
			choice = 0;
			i++;
		}
		if(choice)
		choice = atoi(choice_str);
		if(access || choice == 1 || choice == 10)
		{
			switch(choice)
			{
				case 1:
				{
					if(!access)    //ввод пароля, если он не был ещё введён
					 access = start_work_with_outer();
					 else
						printf("Stek yge inicializirovan\n");
				break;
				}
				case 2:
				{    //очщение
				 	 el_count = 0;
					 make_out_empty(&start , &end);
					 printf("Stek pyst seichas\n");
				break;
				}
				case 3:
				{    //проверка на пустоту
					 is_out_empty(start);
				break;
				}
				case 4:
				{ //показать первый элемент
					 show_out_stack(start);
				break;
				}
				case 5:
				{       //удалить первй элемент
					 if(el_count > 0)
					 el_count--;
					 delete_out_start(&start , &end);
				break;
				}
				case 6:
				{ //взять первый элемент
                     if(el_count > 0)
					 el_count--;
					 taken_element = take_out_start(&start , &end);
				break;
				}
				case 7:
				{         //именить первый элемент
					 change_out_start(&start,&end,&el_count);
				break;
				}
				case 8:
				{
					 if(el_count < size)  //ввод нового элемнета, если стек не переполнен
						add_to_start_out(&start , &end, &el_count);
					 else
					 printf("Stek perepolnen\n");
				break;
				}
				case 9:
				{     //распечатка стека
					 print_out(start , end);
				break;}
				case 10:
				{     //завершение работы
					make_out_empty(&start , &end);   //очищение стека перед выходом
					printf("Rabota so stekom zavershena\n");
				break;
				}
				default:
				{
                	printf("Neverniy vvod\n");
				break;
				}
			}
		}
		else
			printf("Stek ne bil inicializirovan\n");
		printf("Najmite lubuiu knopky...\n");
		getch();
	}
}


int start_work_with_outer() //ввод пароля
{
	char c[10] = "1234",c1[10] = {0};
	printf("Vvedite parol :  ");
	scanf("%s", c1);
	if(!strcmp(c,c1))
	{
		printf("Parol podtverjden\n");
		return 1;
	}
	printf("Neverniy parol\n");
	return 0;
}
void make_out_empty(struct out_stack **start,struct out_stack **end)      //очищение
{
	struct out_stack *del;
	while(*start != NULL) //проход по всем элементам как и у очереди
	{
		del = *start;
		(*start) = (*start)->next;
		make_in_empty(&(del->start) , &(del->end));//но ещё и очищение всех очередей в стеке
		free(del);
	}
	*end = NULL;
}
void is_out_empty(struct out_stack *start)  //проверка на пустоту
{
	if(start == NULL)
	{
		printf("Da, stek pystoi\n");
		return 1;
	}
	else
	printf("Net, stek ne pystoi\n");
	return 0;
}
void show_out_stack(struct out_stack *start)   //вывод первого элемента
{
	if(start != NULL)
	{
		printf("Ochered v nachale = ");
		LSD_in_stack(start->start);    //вывод очереди
		printf("\n");
	}
	else
	printf("Stek pyst\n");
}
void delete_out_start(struct out_stack **start,struct out_stack **end)  //удаление начала
{
	struct out_stack *del;
	if(*start != NULL)
	{
		del = *start;
		if(*start == *end)
		{
			make_in_empty(&(del->start) , &(del->end));//очищениие очереди первого элемента (остальное как в очереди)
			free(del);
			*end = NULL;
			*start = NULL;
			printf("Stek pyst\n");
		}
		else
		{
			*start = (*start)->next;
			make_in_empty(&(del->start) , &(del->end));//очищениие очереди первого элемента
			free(del);
		}
	}
	else
	printf("Stek pyst\n");
}
struct in_queue *take_out_start(struct out_stack **start,struct out_stack **end) //взятие элемента
{
	struct out_queue *del;
	struct in_queue *taken_element;
	if(*start != NULL)
	{
		taken_element = (*start)->start; //взятие как и в очереди, только здесь изымаемый элемент - структура очереди
		del = *start;
		if(*start == *end) //удаление элемента производится без очищения изымаемой очереди
		{
			free(del);
			*end = NULL;
			*start = NULL;
			printf("Stek pyst\n");
		}
		else
		{
			*start = (*start)->next;
			free(del);
		}
	}
	else
	printf("Stek pyst\n");
	return taken_element; //возврат взятой очереди
}
void change_out_start(struct out_stack **start,struct out_stack **end, int *el_count) //изменение очереди
{
	struct out_stack *del;
  	if(*start != NULL)
	{
		printf("Vvedite novoe znachenie dla ocheredi - ");
		LSD_in_stack((*start)->start);  //вывод очереди
		printf("\n");
		(*start)->start = menu_in_queue((*start)->start,1); //вызов функции меню для очереди
		if((*start)->start == NULL)   // если очередь была очищена
		{
			(*el_count)--; //удаление элемента из стека
			printf("Ochered bila ydalena\n");
            del = *start;
			if(*start == *end) //если это был единцственный элемнет
			{
				make_in_empty(&(del->start) , &(del->end)); //очищение стека
				free(del);
				*end = NULL;
				*start = NULL;
				printf("Stek pyst\n");
			}
			else     //инача
			{
				*start = (*start)->next;//просто удаление
				make_in_empty(&(del->start) , &(del->end));
				free(del);
			}
		}
	}
	else
	printf("Stek pyst\n");
}
void add_to_start_out(struct out_stack **start,struct out_stack **end,int *el_count) //добавление в начаор
{
	struct out_stack *add;
	add = (struct in_queue *)malloc(sizeof(struct in_queue)); //выделение памяти под новую очередь
	if(add == NULL)     //проверка- была ли выделена память
	{
		printf("Pamyat ne videlilas\n");
		getch();
		return 0;
	}
	printf("Dalee vi bydete rabotat s vnytrenney ocherediu\n");
	add->start = NULL;
	add->start = menu_in_queue(add->start,0);//вызов меню для новой очереди
	if(add->start != NULL)  //если вернулась не пустая очередь
	{
		(*el_count)++; //добавление элемента, как и в очеред
		if(*start == NULL)
		{
			*start = add;
			*end = add;
			(*start)->next = NULL;
			(*end)->next = NULL;
		}
		else
		{
			add->next = *start;
			*start = add;
		}
	}
	else   //иначе
	{
		free(add); //освобождение памяти
		printf("Stek ne bil inicializirovan\n"); //сообщение о том ,что очередь не была инициализирована
	}
}
void print_out(struct out_stack *start,struct out_stack *end) //вывод стека
{
	struct out_stack *output = start;//указатель вывода на начало
	int i = 1;
	if(start != NULL)
	{                //вывод поочердёно всез элементов
		printf("Element %d:",i);
		LSD_in_stack(start->start);//распечатка очереди
		printf("  - nachalo steka\n");
		output = output->next;
		if(output != NULL)
		for(i = 2;output != end;i++,output = output->next){printf("Element %d:",i);LSD_in_stack(output->start);printf("\n");}
		printf("Element %d:",i);
		LSD_in_stack(end->start);//распечатка очереди
		printf("  - konec steka\n");
	}
	else
	printf("Stek pyst\n");
}
//Стек конец
/////////////////////////

int main()
{
	char choice[10] = {0};
	struct out_stack *stack = NULL;//создание нового стека
	while(strcmp(choice,"2")) //пок ане выбран выход
	{
		system("cls");
		system("color A"); //главное меню
		printf("1)Nachat raboty so stekom\n");
		printf("2)Zavershit raboty s programmoi\n");
		gets(choice);
		while(strcmp(choice,"2") && strcmp(choice,"1"))   //пока ввод не корректен
		{
			system("cls");
			printf("Neverniy vvod\n");
			printf("1)Nachat raboty so stekom\n");
			printf("2)Zavershit raboty s programmoi\n");
			gets(choice);
		}
		if(!strcmp(choice,"1"))
		menu_out_stack(stack);  //вызов функции меню для стека
	}
	clrscr();
	return 0;
}
