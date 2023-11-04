struct list{
int item;
struct list* next;
struct list* last;

};

int sizeLs(struct list** listH);
int insertLs(struct list** listH, int index, int value);
int deleteLs(struct list** listH, int index);
int searchLs(struct list** listH, int value);
int countLs(struct list** listH, int value);