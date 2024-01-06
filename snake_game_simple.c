#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
//gcc snake_game_simple.c -lncurses
//./a.out
struct snakepos
{
	int posX;
	int posY;
	struct snakepos* next;
};

void main() 
{
	WINDOW* win = initscr();
	keypad(win, true);
	nodelay(win, true);
	
	struct snakepos* head = (struct snakepos*)malloc(sizeof(struct snakepos));
	head->posX = 0;
	head->posY = 0;
	struct snakepos* tail = head;
	int foodX = rand() % 20;
	int foodY = rand() % 20;
	int dirX = 1;
	int dirY = 0;
	
	mvaddstr(head->posY, head->posX, "*");
	mvaddstr(foodY, foodX, "&");
		
	while(true) 
	{
		int pressed = wgetch(win);
		if (pressed == KEY_LEFT) 
		{
			dirX = -1;
			dirY = 0;
		}
		if (pressed == KEY_RIGHT) 
		{
			dirX = 1;
			dirY = 0;
		}
		if (pressed == KEY_UP) 
		{
			dirX = 0;
			dirY = -1;
		}
		if (pressed == KEY_DOWN) 
		{
			dirX = 0;
			dirY = 1;
		}
		
		head->next = (struct snakepos*)malloc(sizeof(struct snakepos));
		head->next->posX = head->posX + dirX;
		head->next->posY = head->posY + dirY;
		head = head->next;
		
		mvaddstr(head->posY, head->posX, "*");
		
		if(foodX == head->posX && foodY == head->posY) 				//if snake eats the food create new food and don't move tail forward
		{
			//mvaddstr(foodY, foodX, " ");
			foodX = rand() % 20;
			foodY = rand() % 20;
			mvaddstr(foodY, foodX, "&");
		}
		else								 //move tail forward
		{
			struct snakepos* tmp = tail;
			tail = tail->next;
			mvaddstr(tmp->posY, tmp->posX, " ");
			free(tmp);
		}
		usleep(100000);
	}
	endwin();
}
