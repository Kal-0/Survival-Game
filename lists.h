typedef struct event{
    char event[1000];
    int health;
    int hunger;
    int thirst;
} Event;

struct list{
int item;
Event* event;
struct list* next;
struct list* last;

};

int sizeLs(struct list** listH);
int insertLs(struct list** listH, int index, int value, Event* event);
int deleteLs(struct list** listH, int index);
int searchLs(struct list** listH, int value);
int countLs(struct list** listH, int value);