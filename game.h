typedef struct score{
    char nome[100];
    int dias;
}score;

void printStatus();
void loading();
void nextDay();
void action(double hours, double dificulty_modifier);
void rest();
void hunt();
void scavenge();
void openInventory();
void mainHistory();
void registerScore(int days);
void sortScore(score arr[], int n);
void readScore();

