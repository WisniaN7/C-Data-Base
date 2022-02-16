#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/ioctl.h>
//#include <conio.h>

#ifdef _WIN32
    #define CLEAR "cls"
#endif

#ifdef _WIN64
    #define CLEAR "cls"
#endif

#ifdef __linux__
    #define CLEAR "clear"
#endif

struct person {
  char name[20];
  char surname[35];
  unsigned int age;
  double earnigns;
};

struct winsize windowSize() {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  // printf ("lines %d\n", w.ws_row);
  // printf ("columns %d\n", w.ws_col);

  return w;
}

int copmareInt(const void *a, const void *b) {
  int val1 = *(int*)a;
  int val2 = *(int*)b;

  return (val1 - val2);
}

int copmareSNAE(const void *p1, const void *p2) {
  struct person n1 = *(struct person *)p1;
  struct person n2  = *(struct person *)p2;

  int n = strcmp(n1.surname, n2.surname);

  if (n) {
    return n;
  } else {
    n = strcmp(n1.name, n2.name);

    if (n) {
      return n;
    } else {
      n = n1.age - n2.age;

      if (n) {
        return n;
      } else {
        return (n1.earnigns - n2.earnigns);
      }
    }
  }
}

int copmareNSAE(const void *p1, const void *p2) {
  struct person n1 = *(struct person *)p1;
  struct person n2  = *(struct person *)p2;

  int n = strcmp(n1.name, n2.name);

  if (n) {
    return n;
  } else {
    n = strcmp(n1.surname, n2.surname);

    if (n) {
      return n;
    } else {
      n = n1.age - n2.age;

      if (n) {
        return n;
      } else {
        return (n1.earnigns - n2.earnigns);
      }
    }
  }
}

int copmareASNE(const void *p1, const void *p2) {
  struct person n1 = *(struct person *)p1;
  struct person n2  = *(struct person *)p2;

  int n = n1.age - n2.age;

  if (n) {
    return n;
  } else {
    n = strcmp(n1.surname, n2.surname);

    if (n) {
      return n;
    } else {
      n = strcmp(n1.name, n2.name);

      if (n) {
        return n;
      } else {
        return (n1.earnigns - n2.earnigns);
      }
    }
  }
}

int copmareESNA(const void *p1, const void *p2) {
  struct person n1 = *(struct person *)p1;
  struct person n2  = *(struct person *)p2;

  int n = n1.earnigns - n2.earnigns;

  if (n) {
    return n;
  } else {
    n = strcmp(n1.surname, n2.surname);

    if (n) {
      return n;
    } else {
      n = strcmp(n1.name, n2.name);

      if (n) {
        return n;
      } else {
        return n1.age - n2.age;
      }
    }
  }
}

int getData(char fileName[], struct person data[], unsigned int dataCount) {
  FILE *fin = fopen(fileName, "r");

  if (!fin) {
    printf("\n\n\t* * * Blad otwarcia pliku * * *\n\n");
    return -1;
  }

  char line[35];
  fgets(line, sizeof(line), fin); // zignoruj 1 linię (liczbę wierszy) HACK

  unsigned int i = 0;

  for (i = 0; i < dataCount; i++) {
    fscanf(fin, "%s %s %u %lg", data[i].surname, data[i].name, &data[i].age, &data[i].earnigns);
  }

  fclose(fin);
  system(CLEAR);
  return 1;
}

void printData(struct person data[], unsigned int dataCount) {
  unsigned int i;

  system(CLEAR);
  printf("\n");
  printf("\n");
  printf("\t┌───────────────────────────────────────────────────────────────────────────────────────────┐\n");
  printf("\t│  CherryDB.exe                                                                             │\n");
  printf("\t├────────┬────────────────────────────────────┬──────────────────────┬────────┬─────────────┤\n");
  printf("\t│   LP   │              NAZWISKO              │         IMIE         │  WIEK  │   ZAROBKI   │\n");
  printf("\t├────────┼────────────────────────────────────┼──────────────────────┼────────┼─────────────┤\n");

  for (i = 0; i < dataCount; i++) {
    printf("\t│ %6u │ %-34s │ %-20s │ %6d │ %11lg │\n", i + 1, data[i].surname, data[i].name, data[i].age, data[i].earnigns);

    if (i == dataCount - 1) {
      printf("\t└────────┴────────────────────────────────────┴──────────────────────┴────────┴─────────────┘\n");
    } else {
      printf("\t├────────┼────────────────────────────────────┼──────────────────────┼────────┼─────────────┤\n");
    }
  }

  return;
}

int addData(struct person data[], unsigned int n, unsigned int dataCount) {
  system(CLEAR);
  unsigned int i, j, m, digitCount = 0;

  for (i = dataCount; i < (dataCount + n); i++) {
    m = i;
    digitCount = 0;

    while (m != 0) {
      m /= 10;
      digitCount++;
    }

    printf("\n\n");
    printf("\t┌────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("\t│  CherryDB.exe                                                                          │\n");
    printf("\t├────────────────────────────────────────────────────────────────────────────────────────┤\n");
    printf("\t│  WPROWADZ DANE W FORMACIE: NAZWISKO IMIE WIEK ZAROBKI                                  │\n");
    printf("\t│  %u rekord: ", i - dataCount + 1);
    for (j = 0; j < 78 - digitCount; j++) printf(" ");
    printf("│\n");
    printf("\t└────────────────────────────────────────────────────────────────────────────────────────┘\033[A\r\t│  %u rekord: ", i - dataCount + 1);
    fflush(stdin);
    scanf("%s %s %u %lg", data[i].surname, data[i].name, &data[i].age, &data[i].earnigns);
    system(CLEAR);
  }

  return i;
}

int deleteData(struct person data[], unsigned int n, unsigned int dataCount) {
  system(CLEAR);
  unsigned int i, ids[n], m = n, digitCount;

  while (m != 0) {
    m /= 10;
    ++digitCount;
  }

  printData(data, dataCount);
  printf("\t│  Podaj %d rekordow do usuniecie oddzielajac je spacja: ", n);
  for (i = 0; i < 33 - digitCount; i++) printf(" ");
  printf("│\n");
  printf("\t└───────────────────────────────────────────────────────────────────────────────────────┘\033[A\r\t│  Podaj %d rekordow do usuniecie oddzielajac je spacja: ", n);
  fflush(stdin);

  for (i = 0; i < n; i++) {
    scanf("%u", &ids[i]);
  }

  qsort((void *)ids, n, sizeof(unsigned int), copmareInt);

  for (i = 0; i < n; i++) {
    while (i + 1 != n && ids[i] == ids[i + 1]) n--;

    data[ids[i] - 1] = data[dataCount - i - 1];
  }

  // qsort((void *)data, dataCount, sizeof(struct person), copmareSNAE);

  system(CLEAR);
  return dataCount - n;
}

void saveData(char fileName[], struct person data[], unsigned int count) {
  FILE *fout = fopen(fileName, "w");

  if (!fout) {
    printf("\n\n\t* * * Blad otwarcia pliku * * *\n\n");
    return;
  }

  fprintf(fout, "NUMBER_OF_ROWS: %d\n", count);
  unsigned int i;

  for (i = 0; i < count; i++) {
    fprintf(fout, "%s %s %u %g\n", data[i].surname, data[i].name, data[i].age, data[i].earnigns);
  }

  fclose(fout);
  system(CLEAR);
  return;
}

void sortData(struct person data[], unsigned int dataCount, int mode) {
  switch (mode) {
    case 1:
      qsort((void *)data, dataCount, sizeof(struct person), copmareSNAE);
      break;
    case 2:
      qsort((void *)data, dataCount, sizeof(struct person), copmareNSAE);
      break;
    case 3:
      qsort((void *)data, dataCount, sizeof(struct person), copmareASNE);
      break;
    case 4:
      qsort((void *)data, dataCount, sizeof(struct person), copmareESNA);
      break;
  }
  system(CLEAR);
  return;
}

int getDataCount(char fileName[]) {
  int count;

  FILE *fin = fopen(fileName, "r");

  if (!fin) {
    printf("\n\n\t* * * Blad otwarcia pliku * * *\n\n");
    return -1;
  }

  fscanf(fin, "NUMBER_OF_ROWS: %d", &count);
  fclose(fin);

  return count;
}

double getRandomEarinings() {
  double randval = rand() % 1000;

  return 5 * randval + pow(1.5, randval/45) + 2600;
}

void shuffleNames(struct person people[], unsigned int n, unsigned int start) {
    if (n > 1) {
        unsigned int i;

        for (i = 0; i < n - 1; i++) {
          unsigned int j = i + rand() / (RAND_MAX / (n - i) + 1);
          struct person temp;
          strcpy(temp.name, people[start + j].name);
          strcpy(people[start + j].name, people[start + i].name);
          strcpy(people[start + i].name, temp.name);
        }
    }

    return;
}

int getNames(struct person people[], char mode, unsigned int n, unsigned int start, char fileName[]) {
  int lineCount = getDataCount(fileName);;
  unsigned int i, index = 0, nameIndex[n];

  if (lineCount == -1) return -1;

  for (i = 0; i < n; i++) {
    nameIndex[i] = rand() % lineCount;
  }

  qsort((void *)nameIndex, n, sizeof(int), copmareInt);

  char line[35];
  FILE *fin = fopen(fileName, "r");
  fgets(line, sizeof(line), fin); // zignoruj 1 linię (liczbę wierszy) HACK

  for (i = 0; i < (unsigned)lineCount; i++) {
    fgets(line, sizeof(line), fin);
    line[strlen(line) - 1] = '\0'; // usuń '\n'

    while (i == nameIndex[index]) {
      if (mode == 'n') {
        strcpy(people[start + index++].name, line);
      } else if (mode == 's') {
        strcpy(people[start + index++].surname, line);
      } else {
        return -2;
      }

      if (index == n) break;
    }
  }

  if (mode == 's') {
    shuffleNames(people, n, start);
  }

  return 0;
}

int getRandomPeople(char fileName[]) {
  unsigned int n, i;
  system(CLEAR);
  printf("\n\n");
  printf("\t┌────────────────────────────────────────────────────────────┐\n");
  printf("\t│  CherryDB.exe                                              │\n");
  printf("\t├────────────────────────────────────────────────────────────┤\n");
  printf("\t│  Podaj liczbe osob do wygenerowania:                       │\n");
  printf("\t└────────────────────────────────────────────────────────────┘\033[A\r\t│  Podaj liczbe osob do wygenerowania: ");
  fflush(stdin);
  scanf("%u", &n);
  struct person people[n];
  int femCount = rand() % n, maleCount = n - femCount, temp;
  char file[30];

  strncpy(file, "data/imiona zenskie.dat", 30);
  temp = getNames(people, 'n', femCount, 0, file);
  if (temp == -1) return -1;
  strncpy(file, "data/imiona meskie.dat", 30);
  temp = getNames(people, 'n', maleCount, femCount, file);
  if (temp == -1) return -1;
  strncpy(file, "data/nazwiska zenskie.dat", 30);
  temp = getNames(people, 's', femCount, 0, file);
  if (temp == -1) return -1;
  strncpy(file, "data/nazwiska meskie.dat", 30);
  temp = getNames(people, 's', maleCount, femCount, file);
  if (temp == -1) return -1;

  for (i = 0; i < n; i++) {
    people[i].age = rand() % 80 + 20;
    people[i].earnigns = getRandomEarinings();
  }

  saveData(fileName, people, n);
  system(CLEAR);
  return 1;
}

char unsavedDataPrompt(char fileName[]) {
  unsigned int i;
  char save;

  system(CLEAR);
  printf("\n\n");
  printf("\t┌──────────────────────────────────────────────────────────────────────");
  for (i = 0; i < strlen(fileName); i++) printf("─");
  printf("┐\n");
  printf("\t│  CherryDB.exe                                                        ");
  for (i = 0; i < strlen(fileName); i++) printf(" ");
  printf("│\n");
  printf("\t├──────────────────────────────────────────────────────────────────────");
  for (i = 0; i < strlen(fileName); i++) printf("─");
  printf("┤\n");
  printf("\t│  Czy chcesz zapisać zmiany w pliku: %s [ T ak / N ie / A nuluj ]?      │\n", fileName);
  printf("\t│                                                                      ");
  for (i = 0; i < strlen(fileName); i++) printf(" ");
  printf("│\n");
  printf("\t│                                                                      ");
  for (i = 0; i < strlen(fileName); i++) printf(" ");
  printf("│\n");
  printf("\t└──────────────────────────────────────────────────────────────────────");
  for (i = 0; i < strlen(fileName); i++) printf("─");
  printf("┘\033[A\r\t│  ");
  fflush(stdin);
  scanf(" %c", &save);

  return save;
}

/* TO DO:
  1. Wczytywanie danych ✓
    a. Dynamiczne alokowanie pamięci w zależności od ilości rekordów ✓ ?
    b. Wczytywanie nazwisk ze spacjami
  2. Dodawanie rekordów ✓
    a. Rozszerzanie zmiennej struct person ✓ ?
  3. Sortowanie danych ✓
  4. Przedstawianie danych ✓
  5. Usuwanie danych ✓
*/

int main() {
  srand(time(NULL));
  short int action, unsaved = 0;
  char save;

  char fileName[32];
  strncpy(fileName, "data/db.dat", 32);
  unsigned int dataCount = getDataCount(fileName);
  struct person *data = (struct person *)malloc(dataCount * sizeof(struct person));
  struct person *dataRealloc;
  getData(fileName, data, dataCount);
  unsigned int n;

  do {
    printf("\n\n");
    printf("\t┌────────────────────────────────────────────────────────────┐\n");
    printf("\t│  CherryDB.exe                                              │\n");
    printf("\t├────────────────────────────────────────────────────────────┤\n");
    struct winsize width = windowSize();
    if (width.ws_col < 114) printf("\t│  ! Zalecana szerokosc terminalu to 114 kolumn !            │\n\t│                                                            │\n");
    printf("\t│  1. Wczytaj dane (z domyslnego pliku)                      │\n");
    printf("\t│  2. Wczytaj dane z pliku                                   │\n");
    printf("\t│  3. Przedstaw dane w postaci tabelki                       │\n");
    printf("\t│  4. Sortuj dane                                            │\n");
    printf("\t│  5. Dodaj rekord                                           │\n");
    printf("\t│  6. Usun rekord z danych                                   │\n");
    printf("\t│  7. Zapisz dane (do pliku domyslnego)                      │\n");
    printf("\t│  8. Wyeksportuj dane do pliku                              │\n");
    printf("\t│  9. Wygeneruj nowy (losowy) zestaw danych                  │\n");
    printf("\t│  0. Koniec programu                                        │\n");
    printf("\t│                                                            │\n");
    printf("\t│                                                            │\n");
    printf("\t└────────────────────────────────────────────────────────────┘\033[A\r\t│  ");

    fflush(stdin);
    scanf("%hd", &action);

    switch (action) {
      case 0:
        if (unsaved) {
          save = unsavedDataPrompt(fileName);

          if (save == 'T' || save == 't' || save == 'Y' || save == 'y') {
            saveData(fileName, data, dataCount);
          } else if (save == 'A' || save == 'a' || save == 'C' || save == 'c') {
            action = -1;
          }
        }

        break;
      case 1:
        strncpy(fileName, "data/db.dat", 32);
        dataCount = getDataCount(fileName);
        getData(fileName, data, dataCount);
        system(CLEAR);
        break;
      case 2:
        if (unsaved) {
          save = unsavedDataPrompt(fileName);

          if (save == 'T' || save == 't' || save == 'Y' || save == 'y') {
            fflush(stdin);
            saveData(fileName, data, dataCount);
            unsaved = 0;
          } else if (save == 'A' || save == 'a' || save == 'C' || save == 'c') {
            fflush(stdin);
            break;
          }
        }

        system(CLEAR);
        printf("\n\n");
        printf("\t┌────────────────────────────────────────────────────────────┐\n");
        printf("\t│  CherryDB.exe                                              │\n");
        printf("\t├────────────────────────────────────────────────────────────┤\n");
        printf("\t│  WCZYTYWANIE DANYCH                                        │\n");
        printf("\t│  Podaj nazwe pliku:                                        │\n");
        printf("\t└────────────────────────────────────────────────────────────┘\033[A\r\t│  Podaj nazwe pliku: ");
        fflush(stdin);
        scanf("%s", fileName);
        dataCount = getDataCount(fileName);

        dataRealloc = (struct person *)realloc(data, (dataCount) * sizeof(struct person));

        if (dataRealloc) {
          data = dataRealloc;
        } else {
          exit(5);
        }

        getData(fileName, data, dataCount);
        break;
      case 3:
        printData(data, dataCount);
        // fflush(stdin);
        // getch();
        break;
      case 4:
        unsaved = 1;
        system(CLEAR);
        printf("\n\n");
        printf("\t┌────────────────────────────────────────────────────────────┐\n");
        printf("\t│  CherryDB.exe                                              │\n");
        printf("\t├────────────────────────────────────────────────────────────┤\n");
        printf("\t│  SORTOWANIE DANYCH                                         │\n");
        printf("\t│  Wybierz w jaki sposob chcesz posortowac dane:             │\n");
        printf("\t│  \t1) nazwisko, imie, wiek, zarobki                     │\n");
        printf("\t│  \t2) imie, nazwisko, wiek, zarobki                     │\n");
        printf("\t│  \t3) wiek, nazwisko, imie, zarobki                     │\n");
        printf("\t│  \t4) zarobki, nazwisko, imie, wiek                     │\n");
        printf("\t└────────────────────────────────────────────────────────────┘\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r\t|  Wybierz w jaki sposob chcesz posortowac dane: ");
        fflush(stdin);
        scanf("%hu", &action);
        sortData(data, dataCount, action);
        printData(data, dataCount);
        // fflush(stdin);
        // getch();
        action = -1; // Aby w przypadku wprowadzenia 0 program się nie zakończył
        break;
      case 5:
        unsaved = 1;
        system(CLEAR);
        printf("\n\n");
        printf("\t┌────────────────────────────────────────────────────────────┐\n");
        printf("\t│  CherryDB.exe                                              │\n");
        printf("\t├────────────────────────────────────────────────────────────┤\n");
        printf("\t│  DODAWANIE NOWYCH REKORDOW                                 │\n");
        printf("\t│  Podaj liczbe rekordow do dodania:                         │\n");
        printf("\t└────────────────────────────────────────────────────────────┘\033[A\r\t│  Podaj liczbe rekordow do dodania: ");
        fflush(stdin);
        scanf("%u", &n);

        dataRealloc = (struct person *)realloc(data, (dataCount + n) * sizeof(struct person));

        if (dataRealloc) {
          data = dataRealloc;
        } else {
          exit(5);
        }

        dataCount = addData(data, n, dataCount);
        break;
      case 6:
        unsaved = 1;
        system(CLEAR);
        printf("\n\n");
        printf("\t┌────────────────────────────────────────────────────────────┐\n");
        printf("\t│  CherryDB.exe                                              │\n");
        printf("\t├────────────────────────────────────────────────────────────┤\n");
        printf("\t│  USUWANIE REKORDOW                                         │\n");
        printf("\t│  Podaj liczbe rekordow do usuniecia:                       │\n");
        printf("\t└────────────────────────────────────────────────────────────┘\033[A\r\t│  Podaj liczbe rekordow do usuniecia: ");
        scanf("%u", &n);
        dataCount = deleteData(data, n, dataCount);
        /*
        dataRealloc = realloc(data, (dataCount - n) * sizeof(struct person));

        if (dataRealloc) {
          data = dataRealloc;
        } else {
          exit(5);
        }
        */
        break;
      case 7:
        unsaved = 0;
        system(CLEAR);
        strncpy(fileName, "data/db.dat", 32);
        saveData(fileName, data, dataCount);
        break;
      case 8:
        unsaved = 0;
        system(CLEAR);
        printf("\t┌────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
        printf("\t│  CherryDB.exe                                                                                  │\n");
        printf("\t├────────────────────────────────────────────────────────────────────────────────────────────────┤\n");
        printf("\t│  EKSPORT DANYCH                                                                                │\n");
        printf("\t│  Podaj nazwe pliku do wyeksportowania (max 31 znakow):                                         │\n");
        printf("\t└────────────────────────────────────────────────────────────────────────────────────────────────┘\033[A\r\t│  Podaj nazwe pliku do wyeksportowania (max 31 znakow): ");
        fflush(stdin);
        scanf("%s", fileName);
        saveData(fileName, data, dataCount);
        break;
      case 9:
        system(CLEAR);
        printf("\t┌────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
        printf("\t│  CherryDB.exe                                                                                  │\n");
        printf("\t├────────────────────────────────────────────────────────────────────────────────────────────────┤\n");
        printf("\t│  GENEROWANIE LOSOWYCH DANYCH                                                                   │\n");
        printf("\t│  Podaj nazwe pliku do wyeksportowania (max 31 znakow):                                         │\n");
        printf("\t└────────────────────────────────────────────────────────────────────────────────────────────────┘\033[A\r\t│  Podaj nazwe pliku do wyeksportowania (max 31 znakow): ");
        fflush(stdin);
        scanf("%s", fileName);
        getRandomPeople(fileName);
      break;
      default:
        action = 0;
        break;
    }
  } while(action);

  return 0;
}
