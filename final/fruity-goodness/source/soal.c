

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<time.h>

struct Fruit
{
	int coolness;
	int tastiness;
	int number;
	char *name;
	struct Fruit *next_fruit;
	int level;
};

int number_of_fruits = 0;
struct Fruit *newest_fruit = NULL;
struct Fruit *first_fruit = NULL;

void timeout()
{
	puts("Sorry thats it for the demo!");
	exit(0);
}

void flusher()
{
	fflush(stdin);
	fflush(stdout);
	fflush(stderr);
}

void setup()
{
	signal(SIGALRM, timeout);
	alarm(150);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	srand(time(NULL));
	puts("==================================================");
	puts("WELCOME TO FRUIT WAR v6.9");
	puts("I'm still a noob C coder :(, please report any bugs you find");
	puts("I'm also poor so i cant pay you :(");
	puts("Hopefully you have fun!");
	puts("==================================================");
}

void menu()
{
	flusher();
	puts("1. I want a new fruit");
	puts("2. I want to train my fruit");
	puts("3. I want to list all my fruits");
	puts("4. I want out :(");
	puts("Your choice:");
	return;
}

void make_fruit()
{	
	if(number_of_fruits > 5)	{
		puts("Sorry... We only have the resources for 5 fruits...");
		exit(-1);
	}
	struct Fruit *new_fruit = malloc(sizeof(struct Fruit));
	new_fruit->coolness = 0;
	new_fruit->tastiness = 0;
	new_fruit->level = 0;
	new_fruit->number = number_of_fruits;
	if(number_of_fruits == 0)	{
		first_fruit = new_fruit;
	}
	else	{
		newest_fruit->next_fruit = new_fruit;
	}
	newest_fruit = new_fruit;
	puts("How long do you want this fruit's name to be? (Max 4096 characters)");
	int length;
	scanf("%d", &length);
	getchar();
	if(length > 4096)	{
		puts("NO! BAD!");
		exit(-1);
	}
	char new_name[length];
	puts("What do you want this fruit's name to be?");
	fgets(new_name, length, stdin);
	new_fruit->name = malloc(length);
	strncpy(new_fruit->name, new_name, length);
	number_of_fruits++;
	puts("Fruit Made!");
	return;
}

struct Fruit *get_fruit(int fruit_number)	{
	struct Fruit *temp = first_fruit;
	for(int i = 0; i < fruit_number; i++)	{
		temp = temp->next_fruit;
		if(temp == NULL)	{
			puts("Something went wrong!");
			exit(-1);
		}
	}
	return temp;
}

void evolve_berry()	{
	usleep(1000000);
	for(int i = 0; i < 10; i++)	{
		puts(".");
		for(int j = 0; j < 20; j++)
			puts("");
		usleep(400000);
		puts("/\\");
		puts("\\/");
		for(int j = 0; j < 20; j++)
			puts("");
		usleep(400000);
	}
	puts("Congratz your fruit evolved into a berry!");
	return;
}

void evolve_apple()	{
	usleep(1000000);
	for(int i = 0; i < 10; i++)	{
		puts("/\\");
		puts("\\/");
		for(int j = 0; j < 20; j++)
			puts("");
		usleep(400000);
		puts(" ,(.");
		puts("(   )");
		puts(" `\"'");
		for(int j = 0; j < 20; j++)
			puts("");
		usleep(400000);
	}
	puts("Congratz your fruit evolved into an apple!");
	return;
}

void evolve_orange()	{
	usleep(1000000);
	for(int i = 0; i < 10; i++)	{
		puts(" ,(.");
		puts("(   )");
		puts(" `\"'");
		for(int j = 0; j < 20; j++)
			puts("");
		usleep(400000);
		puts("  ,--./,-.");
		puts(" / #      \\");
		puts("|          |");
		puts(" \\        /");
		puts("  `.____,'");
		for(int j = 0; j < 20; j++)
			puts("");
		usleep(400000);
	}
	puts("Congratz your fruit evolved into an orange!");
	return;
}

void train_fruit()
{
	int fruit_number;

	printf("You have %d fruits\n", number_of_fruits);
	puts("Which fruit do you want to train?");
	scanf("%d", &fruit_number);
	getchar();
	if(0 > fruit_number || number_of_fruits-1 < fruit_number)	{
		puts("That fruit doesnt exist yet...");
		return;
	}
	struct Fruit *fruit_to_train = get_fruit(fruit_number);
	if(fruit_to_train->level >= 3)	{
		puts("This fruit can no longer train!");
		return;
	}
	fruit_to_train->coolness += rand() % 10 + 1;
	fruit_to_train->tastiness += rand() % 10 + 1;
	if(fruit_to_train->coolness >= 50 && fruit_to_train->tastiness >= 50)	{
		fruit_to_train->coolness = 0;
		fruit_to_train->tastiness = 0;
		puts("Whats this? This fruit is evolving?!");
		if(fruit_to_train->level == 0)	{
			evolve_berry();
		}
		else if(fruit_to_train->level == 1)	{
			evolve_apple();
		}
		else if(fruit_to_train->level == 2)	{
			evolve_orange();
		}
		fruit_to_train->level++;
		puts("Would you like to rename this fruit? (y/n)");
		char choice[5];
		fgets(choice, 5, stdin);
		if(strstr(choice, "y"))	{
			puts("How long do you want this fruit's name to be? (Max 4096 characters)");
			int length;
			scanf("%d", &length);
			getchar();
			if(length > 4096)	{
				puts("NO! BAD!");
				exit(-1);
			}
			char new_name[length];
			puts("What do you want this fruit's name to be?");
			__read_chk(0, new_name, length);
			strncpy(fruit_to_train->name, new_name, length);
			return;
		}
		else if(strstr(choice, "n"))	{
			puts("Okay then");
			return;
		}
		else	{
			puts("Dont play games with me >:(");
			exit(-1);
		}
	}
	puts("Fruit Trained!");
	return;
}

void print_fruit(struct Fruit *fruit_to_print)
{
	puts("==================================================");
	printf("Number: %d\n", fruit_to_print->number);
	printf("Name: %s", fruit_to_print->name);
	printf("Coolness: %d\n", fruit_to_print->coolness);
	printf("Tastiness: %d\n", fruit_to_print->tastiness);
	printf("Level: %d\n", fruit_to_print->level);
	puts("==================================================");
	return;	
}

void list_fruits()
{
	if(number_of_fruits == 0)	{
		puts("You have no fruits yet silly!");
		return;
	}
	struct Fruit *fruit_to_print = first_fruit;
	while(fruit_to_print->next_fruit != NULL)	{
		print_fruit(fruit_to_print);
		fruit_to_print = fruit_to_print->next_fruit;
	}
	print_fruit(fruit_to_print);
	return;
}

int main(int argc, char* argv[], char** env)
{
	setup();
	int choice;
	while(1)	{
		menu();
		scanf("%d", &choice);
		getchar();
		if(choice == 1)	{
			make_fruit();
		}
		else if (choice == 2)	{
			train_fruit();
		}
		else if (choice == 3)	{
			list_fruits();
		}
		else	{
			puts("You gave up on your fruits..."); exit(0);
		}
	}
}