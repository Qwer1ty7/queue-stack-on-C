#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

struct in_queue{         //��������� ��� �������
	int data;               //���� ��� ��������
	struct in_queue *next;  // ��������� �� ��������� �������
	int size;             //������ �������
	int el_count;         //���������� ���������
};
struct out_stack{        //��������� ��� �����
	struct in_queue *start;  //�������� �� ������ �����
	struct in_queue *end;    //��������� �� ����� �����
	struct out_stack *next;   //��������� �� ��������� �������
};
///////////////////////////
//������� ������
int start_work_with_interior();  //�������� ������� ������ ������ � ��������
void make_in_empty(struct in_queue **,struct in_queue **);  //������� �������� ������
void is_in_empty(struct in_queue *);      //�������� - ������ �� �������
void show_in_queue(struct in_queue *);   //������� ������ �������
void delete_in_start(struct in_queue **,struct in_queue **); //������� ������ �������
int take_in_start(struct in_queue **,struct in_queue **, int **); //����� ������ �������
void change_in_start(struct in_queue *); //�������� ������ �������
int add_to_end_in(struct in_queue **,struct in_queue **); //�������� � ������ �������
void print_in(struct in_queue *,struct in_queue *); //���������� �������

struct in_queue *menu_in_queue(struct in_queue *start,int input_flag)    //������� ���� �������
{
	struct in_queue *end = start;     // ������ ��������� �� ����� ������ ��������� �� ������
	int *taken_element = NULL, choice = 0,access = 0,i,size,el_count;   //��������� ����������
	char choice_str[30]; //������ ��� ���������� ����� ������������
	if(!input_flag)   //���� � ���� ������� ������� ����������
	{
		system("cls");  //��������� ������
		system("color B");
		printf("Vvedite razmer ocheredi -  ");
		scanf("%d", &size);//��������� ������ �������
		el_count = 0;  //���������� ��������� = 0
	}
	else  //�����
	{
		for(;end->next != NULL; end = end->next);   //������������ ������ � ���������� ���������
		size = start->size;
		el_count = start->el_count;
	}

	while(choice != 10)    //���� �� ��� ������ �����
	{
		choice = -1;  //���������� ����� - -1
		system("cls");  //��������� ������
		system("color B");
		printf("Vnytrennaia cochered\n");
		if(access)     //���� ��� ������� ������
			if(!input_flag)   //���� ������� ���������� � �������
			printf("Ochered inicializirovana\n");
			else
			printf("Dostyp polychen\n");
		else    //���� ������ �� ��� �������
			if(!input_flag) //���� ������� ���������� � �������
			printf("Ochered ne bila inicializirovana\n");
			else
			printf("Dostyp ne polychen\n");
		if(access)//���� ������ ��� �������
		{
			printf("Razmer ocheredi - %d\n",size);  //����� �������
			printf("Kolichestvo elemetov d ocheredi - %d\n",el_count);  //����� ���������� ���������
			print_in(start,end);//����������� �������
		}
		if(taken_element != NULL)    //���� ������ ������� �� ����
		printf("\nVzatiy element - %d\n\n",*taken_element); //����� ������� ��������
		printf("Menu:\n");  //���������� ����
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
		gets(choice_str); //����������� ������ 
		i = 0;
		while(choice_str[i] != '\0')  //���� ������ � �����������
		{
			if(!(choice_str[i] >= '0' && choice_str[i] <= '9'))  //��������, ����� ���� ������� ���� �����
			choice = 0;  //���� ���� �� �����, �� ����� = 0
			i++;
		}
		if(choice)//���� ����� �� ����
		choice = atoi(choice_str);  //������� ������ � �����
		if(access || choice == 1 || choice == 10) //���� ����� � ���������� �� 1 �� 10
		{
			switch(choice)  //�������� �� ������������ ������� ���� �����
			{
				case 1:{ //���� �������
					if(!access)   //� ������ �� �������
					 access = start_work_with_interior();//����� ������� ��� ��������� �������
					 else
						if(!input_flag) //���� �� ������ ����
						printf("Ochered yge inicializirovana\n");
						else
						printf("Dostyp yge polychen\n");
				break;}
				case 2:{
				 	 el_count = 0;
					 make_in_empty(&start , &end);//�������� �������
					 printf("Ochered pystaia seichas\n");
				break;}
				case 3:{    //�������� �� ������� �������
					 is_in_empty(start);
				break;}
				case 4:{  //�������� ������ �������
					 show_in_queue(start);
				break;}
				case 5:{
					 if(el_count > 0)
					 el_count--;
					 delete_in_start(&start , &end);  //������� ������
				break;}
				case 6:{
					 if(el_count > 0)
					 el_count--;
					 take_in_start(&start , &end, &taken_element);//����� ������
				break;}
				case 7:{
					 change_in_start(start);//�������� ������
				break;}
				case 8:{
					 if(el_count < size) //���� ���������� ��������� ������ �������
					 {
						el_count++; //���������� ����� ���������
						add_to_end_in(&start , &end);  //���������� ���������
					 }
					 else
					 printf("Ochered perepolnena\n");
				break;}
				case 9:{
					 print_in(start , end); //����������� �������
				break;}
				case 10:{                     //������ ���������
					printf("Rabota s ocherediu zavershena\n");
				break;}
				default:{                    //�������� ����
					printf("Neverniy vvod\n");
				break;}
			}
		}
		else    //���� ����� ����
		{
			if(!input_flag)//����� ������
			printf("Ochered ne bila inicializirovana\n");
			else
			printf("Dostyp ne bil polychen\n");
		}
		if(choice != 10) //���� ����� �� ������ - ������ �� ������� � ����������
		printf("Najmite lubyiu knopky...\n");
		getch();
	}
	if(start != NULL)//���� ����� �� ����, ��
	{
		start->size = size;  //�������� ������� � �����
		start->el_count = el_count;
	}
	return start;//������� ������� ��������
}

int start_work_with_interior()  //������ ������ � ��������
{
	char c[10] = "1234",c1[10] = {0};//������������� ������
	printf("Vvedite parol :  ");
	scanf("%s", c1);  //���������� ������
	if(!strcmp(c,c1)) //���� ������ ������
	{
		printf("Parol podtverjden\n");
		return 1;     //������� ������� � ���������� access � ����
	}
	printf("Neverniy parol\n");
	return 0;  //���� �� ������, �� ����
}
void make_in_empty(struct in_queue **start,struct in_queue **end)//������� �������
{
	struct in_queue *del;
	while(*start != NULL) //���� ������ ������� �� ����
	{
		del = *start; //�������� ������� �� �����
		(*start) = (*start)->next;//������ ������� ������������� �� ���������
		free(del); //�������� ������� ��������
	}
	*end = NULL;//����� ��������������� �� ����
}
void is_in_empty(struct in_queue *start)//�������� �� �������
{
	if(start == NULL)   //���� ������ ������� ����
	{
		printf("Da, ochered pysta\n"); //������
		return 1;
	}
	else  //�����
	printf("Net, ochered ne pysta\n"); //�� ������
	return 0;
}
void show_in_queue(struct in_queue *start)       //�������� ������ �������
{
	if(start != NULL)
	{
		printf("Number in start = %d\n",start->data);  //����� ������� ��������, ���� ������� �� ������
	}
	else
	printf("Ochered pysta\n");
}
void delete_in_start(struct in_queue **start,struct in_queue **end)// ������� �� ������
{
	struct in_queue *del;
	if(*start != NULL)//���� ������� �� �����
	{
		del = *start;//������ ��������� �������� �� �����
		if(*start == *end)//���� ����� ������� ��������� � �������
		{
			free(del);  //������� �������
			*end = NULL;
			*start = NULL;
			printf("Ochered pysta\n");
		}
		else
		{
			*start = (*start)->next;//������ ������� ������������� �� ���������
			free(del);//�������� ��������
		}
	}
	else
	printf("Ochered pysta\n");
}
int take_in_start(struct in_queue **start,struct in_queue **end, int **taken_element)  //����� �� ������
{
	struct in_queue *del;
	if(*start != NULL)  //���� ������� �� �����
	{
        *taken_element = (int *)malloc(sizeof(int)); //��������� ������ ��� ������� ��� ������
		if(*taken_element == NULL)  //���� ������ �� ����������
		{
			printf("Pamat ne bila videlena\n");  //��������� �� ������
			getch();
			return 0;
		}
		**taken_element = (*start)->data;//������ ������� ��������� �������� ������� ��������
		del = *start;    //����� ������ ��������  ��������
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
void change_in_start(struct in_queue *start) //��������� ������
{
	if(start != NULL)            //���� ������� �� �����
	{
		printf("Vvedite novoe znachenie dla \"%d\" -  ", start->data);//���� ������ ��������
		scanf("%d",&(start->data));
	}
	else
	printf("Ochered pysta\n");
}
int add_to_end_in(struct in_queue **start,struct in_queue **end)  //�������� ������� � �����
{
	struct in_queue *add; 
	add = (struct in_queue *)malloc(sizeof(struct in_queue));//��������� ������ ��� ����������� �������
	if(add == NULL)    //�������� - ���������� �� ������
	{
		printf("Pamyat ne videlilas\n");
		getch();
		return 0;
	}
	printf("Vvedite noviy element -  ");
	scanf("%d",&(add->data));    //���� ������ �������
	if(*start == NULL) //���� ������� ������
	{
		*start = add;  //����������� ���������� ������
		*end = add;  //����� �����
		(*start)->next = NULL;  //��������� �� ���� �������� = ����
		(*end)->next = NULL;
	}
	else
	{
		add->next = NULL;  //��������� �� ����������� = ����
		(*end)->next = add;//��������� �� ��������� - �����������
		*end = add; //����������� ���������� ���������
	}
}
void print_in(struct in_queue *start,struct in_queue *end) //���������� �������
{
	struct in_queue *output = start; //��������� ������ �� �����
	int i = 1;
	if(start != NULL)
	{
		printf("Element 1: %d  - nachalo ocheredi\n",output->data);//����� ������� ��������
		output = output->next;// ������������ �� ���������
		if(output != NULL)// ���� �� ����������
		for(i = 2;output != end;i++,output = output->next)printf("Element %d: %d\n",i,output->data);//����� �������������
		printf("Element %d: %d  - konec ocheredi\n",i,end->data);//����� ����������
	}
	else
	printf("Ochered pysta\n");
}
//������� �����
//////////////////////////


//////////////////////////
//���� ������
int start_work_with_outer();
void make_out_empty(struct out_stack **,struct out_stack **);
void is_out_empty(struct out_stack *);
void show_out_stack(struct out_stack *);
void delete_out_start(struct out_stack **,struct out_stack **);
struct in_queue *take_out_start(struct out_stack **,struct out_stack **);
void change_out_start(struct out_stack **,struct out_stack **,int *);
void add_to_start_out(struct out_stack **,struct out_stack **,int *);
void print_out(struct out_stack *,struct out_stack *);

void LSD_in_stack(struct in_queue *start)//������� ��� ������ ���������� ��������� - �������
{
	struct in_queue *output;
    for(output = start; output != NULL; output = output->next) printf("%d ", output->data); //����� ����� ������ ���� ������ � �������
}

void menu_out_stack(struct out_stack *start)  //���� �����
{
	struct out_stack *end = start;
	struct in_queue *taken_element = NULL;   //��������� �� ������ ������� ���������� ����
	int choice = 0,access = 0,i,size,el_count; //���� ����������
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
			LSD_in_stack(taken_element);//���� ������ ������� �� ����, �� ����� ��� �����������
			printf("\n");
		}
		printf("Menu:\n");   //���������� ����
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
		while(choice_str[i] != '\0')//������ �� ������������� ����� ��� � �������
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
					if(!access)    //���� ������, ���� �� �� ��� ��� �����
					 access = start_work_with_outer();
					 else
						printf("Stek yge inicializirovan\n");
				break;
				}
				case 2:
				{    //�������
				 	 el_count = 0;
					 make_out_empty(&start , &end);
					 printf("Stek pyst seichas\n");
				break;
				}
				case 3:
				{    //�������� �� �������
					 is_out_empty(start);
				break;
				}
				case 4:
				{ //�������� ������ �������
					 show_out_stack(start);
				break;
				}
				case 5:
				{       //������� ����� �������
					 if(el_count > 0)
					 el_count--;
					 delete_out_start(&start , &end);
				break;
				}
				case 6:
				{ //����� ������ �������
                     if(el_count > 0)
					 el_count--;
					 taken_element = take_out_start(&start , &end);
				break;
				}
				case 7:
				{         //������� ������ �������
					 change_out_start(&start,&end,&el_count);
				break;
				}
				case 8:
				{
					 if(el_count < size)  //���� ������ ��������, ���� ���� �� ����������
						add_to_start_out(&start , &end, &el_count);
					 else
					 printf("Stek perepolnen\n");
				break;
				}
				case 9:
				{     //���������� �����
					 print_out(start , end);
				break;}
				case 10:
				{     //���������� ������
					make_out_empty(&start , &end);   //�������� ����� ����� �������
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


int start_work_with_outer() //���� ������
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
void make_out_empty(struct out_stack **start,struct out_stack **end)      //��������
{
	struct out_stack *del;
	while(*start != NULL) //������ �� ���� ��������� ��� � � �������
	{
		del = *start;
		(*start) = (*start)->next;
		make_in_empty(&(del->start) , &(del->end));//�� ��� � �������� ���� �������� � �����
		free(del);
	}
	*end = NULL;
}
void is_out_empty(struct out_stack *start)  //�������� �� �������
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
void show_out_stack(struct out_stack *start)   //����� ������� ��������
{
	if(start != NULL)
	{
		printf("Ochered v nachale = ");
		LSD_in_stack(start->start);    //����� �������
		printf("\n");
	}
	else
	printf("Stek pyst\n");
}
void delete_out_start(struct out_stack **start,struct out_stack **end)  //�������� ������
{
	struct out_stack *del;
	if(*start != NULL)
	{
		del = *start;
		if(*start == *end)
		{
			make_in_empty(&(del->start) , &(del->end));//��������� ������� ������� �������� (��������� ��� � �������)
			free(del);
			*end = NULL;
			*start = NULL;
			printf("Stek pyst\n");
		}
		else
		{
			*start = (*start)->next;
			make_in_empty(&(del->start) , &(del->end));//��������� ������� ������� ��������
			free(del);
		}
	}
	else
	printf("Stek pyst\n");
}
struct in_queue *take_out_start(struct out_stack **start,struct out_stack **end) //������ ��������
{
	struct out_queue *del;
	struct in_queue *taken_element;
	if(*start != NULL)
	{
		taken_element = (*start)->start; //������ ��� � � �������, ������ ����� ��������� ������� - ��������� �������
		del = *start;
		if(*start == *end) //�������� �������� ������������ ��� �������� ��������� �������
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
	return taken_element; //������� ������ �������
}
void change_out_start(struct out_stack **start,struct out_stack **end, int *el_count) //��������� �������
{
	struct out_stack *del;
  	if(*start != NULL)
	{
		printf("Vvedite novoe znachenie dla ocheredi - ");
		LSD_in_stack((*start)->start);  //����� �������
		printf("\n");
		(*start)->start = menu_in_queue((*start)->start,1); //����� ������� ���� ��� �������
		if((*start)->start == NULL)   // ���� ������� ���� �������
		{
			(*el_count)--; //�������� �������� �� �����
			printf("Ochered bila ydalena\n");
            del = *start;
			if(*start == *end) //���� ��� ��� ������������� �������
			{
				make_in_empty(&(del->start) , &(del->end)); //�������� �����
				free(del);
				*end = NULL;
				*start = NULL;
				printf("Stek pyst\n");
			}
			else     //�����
			{
				*start = (*start)->next;//������ ��������
				make_in_empty(&(del->start) , &(del->end));
				free(del);
			}
		}
	}
	else
	printf("Stek pyst\n");
}
void add_to_start_out(struct out_stack **start,struct out_stack **end,int *el_count) //���������� � ������
{
	struct out_stack *add;
	add = (struct in_queue *)malloc(sizeof(struct in_queue)); //��������� ������ ��� ����� �������
	if(add == NULL)     //��������- ���� �� �������� ������
	{
		printf("Pamyat ne videlilas\n");
		getch();
		return 0;
	}
	printf("Dalee vi bydete rabotat s vnytrenney ocherediu\n");
	add->start = NULL;
	add->start = menu_in_queue(add->start,0);//����� ���� ��� ����� �������
	if(add->start != NULL)  //���� ��������� �� ������ �������
	{
		(*el_count)++; //���������� ��������, ��� � � ������
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
	else   //�����
	{
		free(add); //������������ ������
		printf("Stek ne bil inicializirovan\n"); //��������� � ��� ,��� ������� �� ���� ����������������
	}
}
void print_out(struct out_stack *start,struct out_stack *end) //����� �����
{
	struct out_stack *output = start;//��������� ������ �� ������
	int i = 1;
	if(start != NULL)
	{                //����� ��������� ���� ���������
		printf("Element %d:",i);
		LSD_in_stack(start->start);//���������� �������
		printf("  - nachalo steka\n");
		output = output->next;
		if(output != NULL)
		for(i = 2;output != end;i++,output = output->next){printf("Element %d:",i);LSD_in_stack(output->start);printf("\n");}
		printf("Element %d:",i);
		LSD_in_stack(end->start);//���������� �������
		printf("  - konec steka\n");
	}
	else
	printf("Stek pyst\n");
}
//���� �����
/////////////////////////

int main()
{
	char choice[10] = {0};
	struct out_stack *stack = NULL;//�������� ������ �����
	while(strcmp(choice,"2")) //��� ��� ������ �����
	{
		system("cls");
		system("color A"); //������� ����
		printf("1)Nachat raboty so stekom\n");
		printf("2)Zavershit raboty s programmoi\n");
		gets(choice);
		while(strcmp(choice,"2") && strcmp(choice,"1"))   //���� ���� �� ���������
		{
			system("cls");
			printf("Neverniy vvod\n");
			printf("1)Nachat raboty so stekom\n");
			printf("2)Zavershit raboty s programmoi\n");
			gets(choice);
		}
		if(!strcmp(choice,"1"))
		menu_out_stack(stack);  //����� ������� ���� ��� �����
	}
	clrscr();
	return 0;
}
