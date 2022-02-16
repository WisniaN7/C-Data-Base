#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//#include <conio.h>

// Czyszczenie terminalu w zależności od systemu
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

// Porównywanie int (potrzebne do qsort)
int copmareInt(const void *a, const void *b) {
  int val1 = *(int*)a;
  int val2 = *(int*)b;

  return (val1 - val2);
}

// Porównywane struct person w kolejności: nazwisko, imię, wiek, zarobki
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

// Porównywane struct person w kolejności: imię, nazwisko, wiek, zarobki
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

// Porównywane struct person w kolejności: wiek, nazwisko, imię, zarobki
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

// Porównywane struct person w kolejności: zarobki, nazwisko, imię, wiek
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

// Pobieranie danych
/*
  fileName - nazwa pliku do wczytania
  data[] - output / tablica do której zostaną wczytane dane
  dataCount - liczba rekordów do wczytania
*/
int getData(char fileName[], struct person data[], unsigned int dataCount) {
  // Otwarcie pliku
  FILE *fin = fopen(fileName, "r");

  // Error handler
  if (!fin) {
    printf("\n\n\t* * * Blad otwarcia pliku * * *\n\n");
    return -1;
  }

  // HACK: zignoruj 1 linię (liczbę wierszy)
  char line[35];
  fgets(line, sizeof(line), fin);

  // Wczytaj 'dataCount' rekordów (linii) z pliku
  unsigned int i = 0;

  for (i = 0; i < dataCount; i++) {
    fscanf(fin, "%s %s %u %lg", data[i].surname, data[i].name, &data[i].age, &data[i].earnigns);
  }

  // Zamknij plik
  fclose(fin);
  return 1;
}

// Wyświetlanie danych
/*
  data[] - dane do wyświetlenia
  dataCount - ilość danych (rekordów) do wyświetlenia
*/
void printData(struct person data[], unsigned int dataCount) {
  unsigned int i;

  // Wyczyść terminal i wydrukuj nagłówek
  system(CLEAR);
  printf("\n");
  printf("\n");
  printf("\t+---------------------------------------------------------------------------------------+\n");
  printf("\t|  LP  |              NAZWISKO              |         IMIE         |  WIEK  |  ZAROBKI  |\n");
  printf("\t+------+------------------------------------+----------------------+--------+-----------+\n");

  // Wydrukuj w tablei dane
  /*
    %*LICZBA**TYP*
    LICZBA - jaką długość ma zajmować wyświetlana dana (dopełnienie spacjami  // słabodziała z polskimi znakami, gdyż są uznawane za znaki 'wieloznakowe')
    TYP - format w jakim ma się wyświetlić dana, musi pasować odpowiedniemu typowi struct'a
  */
  for (i = 0; i < dataCount; i++) {
    printf("\t| %4u | %-34s | %-20s | %6d | %9lg |\n", i + 1, data[i].surname, data[i].name, data[i].age, data[i].earnigns);
    printf("\t+------+------------------------------------+----------------------+--------+-----------+\n");

  }

  return;
}

// Dodawanie danych do data[]
/*
  data[] - zmienna do dodania danych (rekordów)
  n - liczba danych (rekordów) do dodania
  dataCount - obecna ilość danych (rekordów) w data[]
*/
int addData(struct person data[], unsigned int n, unsigned int dataCount) {
  system(CLEAR);
  unsigned int i;

  // Zaczynając od ostatniego indeksu data[] (tj. data[ dataCount ]), dodaj następne rekordy
  for (i = dataCount; i < (dataCount + n); i++) {
    printf("\n\n\tWPROWADZ DANE W FORMACIE: NAZWISKO IMIE WIEK ZAROBKI\n");
    printf("\t%u rekord: ", i - dataCount + 1);
    fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa) // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
    scanf("%s %s %u %lg", data[i].surname, data[i].name, &data[i].age, &data[i].earnigns);
    system(CLEAR);
  }

  return i;
}

// Usuwanie danych z data[]
/*
  data[] - zmienna do usunięcia danych (rekordów)
  n - liczba danych (rekordów) do usunięcia
  dataCount - obecna ilość danych (rekordów) w data[]
*/
int deleteData(struct person data[], unsigned int n, unsigned int dataCount) {
  system(CLEAR);
  unsigned int i, ids[n]; // Deklaracja licznika i tablicy 'n' indeksów do usunięcia

  printData(data, dataCount); // Wyświetlanie danych
  printf("\n\n\tPodaj %d rekordow do usuniecie oddzielajac je spacja: ", n);
  fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)

  // Pobieranie 'n' indeksów rekordów do usunięcia
  for (i = 0; i < n; i++) {
    scanf("%u", &ids[i]);
  }

  // Sortowanie indeksów - w przypadku podania 2 lub więcej takich samych indeksów, powinny być one obok siebie, aby nie usunąc zbyt dużo rekordów
  qsort((void *)ids, n, sizeof(unsigned int), copmareInt);

  // Usuwanie 'n' rekordów po indeksach
  for (i = 0; i < n; i++) {
    // Pomijanie takich samych indeksów
      // Dopóki następny indeks nie jest ostatnim, jeżeli następny indeks jest taki sam jak obecny zmniejsz ilość indeksów do usunięcia
    while (i + 1 != n && ids[i] == ids[i + 1]) n--;

    // data[ indeks ] = data[ ostatni indeks ]
      // indeks = ids[i] - 1, ponieważ przy wyświetlaniu rekordy są numerowane od 1, a nie od 0
    data[ids[i] - 1] = data[dataCount - i - 1];
  }

  // qsort((void *)data, dataCount, sizeof(struct person), copmareSNAE);

  system(CLEAR);
  // Zwróć obecną ilość indeksów
  return dataCount - n;
}

// Zapisywanie danych
/*
  fileName[] - nazwa pliku do zapisu
  data[] - dane (rekordy) do zapisania
  count - ilość rekordów do zapisania
*/
void saveData(char fileName[], struct person data[], unsigned int count) {
  FILE *fout = fopen(fileName, "w");

  if (!fout) {
    printf("\n\n\t* * * Blad otwarcia pliku * * *\n\n");
    return;
  }

  // Umieszczenie w nagłówku ilości rekordów znajdujących się w pliku
  fprintf(fout, "NUMBER_OF_ROWS: %d\n", count);
  unsigned int i;

  // Zapisywanie rekordów linijka po linijce
  for (i = 0; i < count; i++) {
    fprintf(fout, "%s %s %u %g\n", data[i].surname, data[i].name, data[i].age, data[i].earnigns);
  }

  fclose(fout);
  return;
}

// Sortowanie danych / Wybieranie odpowiedniej funkcji porównywującej do qsort
/*
  data[] - dane do posortowania
  dataCount - ilość danych (rekodrów) do posortowania
  mode - tryb sortowania
*/
void sortData(struct person data[], unsigned int dataCount, int mode) {
  switch (mode) {
    case 1:
      // Sortowanie nazwisko, imię, wiek, zarobki
      qsort((void *)data, dataCount, sizeof(struct person), copmareSNAE);
      break;
    case 2:
    // Sortowanie imię, nazwisko, wiek, zarobki
      qsort((void *)data, dataCount, sizeof(struct person), copmareNSAE);
      break;
    case 3:
      // Sortowanie wiek, nazwisko, imię, zarobki
      qsort((void *)data, dataCount, sizeof(struct person), copmareASNE);
      break;
    case 4:
      // Sortowanie zarobki, nazwisko, imię, wiek
      qsort((void *)data, dataCount, sizeof(struct person), copmareESNA);
      break;
  }

  return;
}

// Pobieranie liczby rekodrów znajdujących się w pliku (tylko pierwszej linijki)
/*
  fileName[] - nazwa pliku z którego zostanie pobrana liczba rekordów
*/
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

// Generator liczb losowych z prawdobodobieństwem (polecam wrzucić do Desmos'a)
double getRandomEarinings() {
  double randval = rand() % 1000;

  return 5 * randval + pow(1.5, randval/45) + 2600;
}

// Mieszanie tablicy stringów (nazwisk) w przedziale indeksów od start do start + n (osobno nazwisk męskich i nazwisk żeńskich, które znajdują się w jednej tablicy ( people[] ), jednakże są oddzielone przez pewien indeks)
/*
  people[] - tablica stringów (nazwisk) do wymieszania
  n - liczba indeksów do przemieszania
  start - indeks początkowy, potrzebny do oddzielenia kobiet i mężczyzn
    people = {
      Adamska Marta
      Cendrowska Jolanta
      .
      .
      .
      Żebrzyk Iwona
      Adamczyk Marcin
      .
      .
      .
      Ziobro Mikołaj
    }
*/
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

// Wybieranie losowych imion / nazwisk z plku data/imiona *.dat / data/nazwiska *.dat
/*
  input:
    people[] - zmienna do przechowania wybranych imion
    mode - tryb działania: n - imiona (names), s - nazwiska (surnames)
    n - ilość nazwisk / imion do pobrania
    start - zmienna wskazująca na indeks którym kobiety oddzielone są od mężczyzn
    fileName[] - nazwa pliku z którego zostaną pobranie nazwiska / imiona

  output:
     0 - operacja przebiegła pomyślnie
    -1 - nie zdołano pobrać ilości nazwisk / imion
    -2 - indeks nazwiska / imiona nie istnieje (raczej nie powino wystąpić)
*/
int getNames(struct person people[], char mode, unsigned int n, unsigned int start, char fileName[]) {
  // Pobierz ilość nazwisk / imion z pliku (informacja znajdująca się w nagłówku)
  int lineCount = getDataCount(fileName);
  unsigned int i, index = 0, nameIndex[n];

  // Error handler
  if (lineCount == -1) return -1;

  // Wygeneruj 'n' losowych indeksów imion do pobrania
  for (i = 0; i < n; i++) {
    nameIndex[i] = rand() % lineCount;
  }

  // Sortowanie indeksów w celu liniowego przeszukiwania pliku
  qsort((void *)nameIndex, n, sizeof(int), copmareInt);

  char line[35];
  FILE *fin = fopen(fileName, "r");
  fgets(line, sizeof(line), fin); //  HACK: zignoruj 1 linię (liczbę wierszy)

  // Przeglądanie całego pliku w poszukiwaniu odpowiednich indeksów
  for (i = 0; i < (unsigned)lineCount; i++) {
    fgets(line, sizeof(line), fin); // Pobiranie 1 linijki z pliku
    line[strlen(line) - 1] = '\0'; // Zastąp znak nowej linii znakiem końca linii (NUL)

    // Dopóki szukane nazwisko / imię jest w obecnej linijce, kopiuj je do następnego indeksu tablicy
    while (i == nameIndex[index]) {
      if (mode == 'n') {
        strcpy(people[start + index++].name, line);
      } else if (mode == 's') {
        strcpy(people[start + index++].surname, line);
      } else {
        return -2;
      }

      // Jeżeli wypełniliśmy wszystkie indeksy (n indeksów) zakończ pętlę
      if (index == n) break;
    }
  }

  // Jeżeli jesteśmy w trybie nazwiska, przemieszaj je, aby nie wystąpiła sytuacja:
  //  Adamska Agata
  //  Adamska Amelia
  //  Adamska Anna
  //  Bogacka Alicja
  //  etc
  if (mode == 's') {
    shuffleNames(people, n, start);
  }

  return 0;
}

// Wygeneruj losowe rekordy do pliku
/*
  input:
    fileName[] - nazwa pliku do zapisania danych (rekordów)

  output:
     1 - operacja przebiegła pomyślnie
    -1 - błąd przy wybieraniu imion
*/
int getRandomPeople(char fileName[]) {
  unsigned int n, i;
  printf("\n\n\tPodaj liczbe osob do wygenerowania: ");
  fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
  scanf("%u", &n);
  struct person people[n];
  // Podziel losowo liczbę 'n' osób do wygenerowania na kobiety i mężczyzn
  int femCount = rand() % n, maleCount = n - femCount, temp;
  char file[30]; // Zmienna pomocnicza potrzebna do otwarcia plików

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

  // Wygeneruj losowy wiek i zarobki
  for (i = 0; i < n; i++) {
    people[i].age = rand() % 80 + 20;
    people[i].earnigns = getRandomEarinings();
  }

  // Zapisz dane do pliku
  saveData(fileName, people, n);
  system(CLEAR);
  return 1;
}

/*
  TO DO:
  1. Wczytywanie danych ✓
    a. Dynamiczne alokowanie pamięci w zależności od ilości rekordów ✓ ?
    b. Wczytywanie nazwisk ze spacjami
  2. Dodawanie rekordów ✓
    a. Rozszerzanie zmiennej struct person ✓ ?
  3. Sortowanie danych ✓
  4. Przedstawianie danych ✓
  5. Usuwanie danych
*/


int main() {
  srand(time(NULL));
  short int action, unsaved = 0; // Zmienne wykorzystane do nawigacji po programie i przypomnieniu o niezapisanych zmianach
  char save; // Zmienna do wybrania akcji przy monicie o niezapisanych zmianach

  char fileName[32]; // Nazwa pliku na którym wykonywane będą operacje
  strncpy(fileName, "data/db.dat", 32); // Przypisanie fileName domyślnego pliku
  unsigned int dataCount = getDataCount(fileName); // Pobranie ilość danych (rekordów) z pliku domyślnego
  struct person *data = (struct person *)malloc(dataCount * sizeof(struct person)); // Przypisanie odpowiedniej ilości pamięci zmiennej data[ dataCount ]
  struct person *dataRealloc; // Zmienna wykorzytywana przy rozszerzeniu wielkości zmiennej data[]
  getData(fileName, data, dataCount); // Pobieranie danych z pliku domyślnego
  unsigned int n;

  // Menu
  do {
    printf("\n\n");
    printf("\n\n");
    printf("\t1. Wczytaj dane (z domyslnego pliku)\n");
    printf("\t2. Wczytaj dane z pliku\n");
    printf("\t3. Przedstaw dane w postaci tabelki\n");
    printf("\t4. Sortuj dane\n");
    printf("\t5. Dodaj rekord\n");
    printf("\t6. Usun rekord z danych\n");
    printf("\t7. Zapisz dane (do pliku domyslnego)\n");
    printf("\t8. Wyeksportuj dane do pliku\n");
    printf("\t9. Wygeneruj nowy (losowy) zestaw danych\n");
    printf("\t0. Koniec programu\n\n\t");

    fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
    scanf("%hd", &action); // Wybieranie akcji

    switch (action) {
      // Zamykanie programu
      case 0:
        // Monit o niezapisanych zmienach
        if (unsaved) {
          system(CLEAR);
          printf("\n\n\tCzy chcesz zapisać zmiany w pliku: %s [ T ak / N ie / A nuluj ]?\n\t", fileName);
          fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
          scanf(" %c", &save);

          if (save == 'T' || save == 't' || save == 'Y' || save == 'y') {
            saveData(fileName, data, dataCount);
          } else if (save == 'A' || save == 'a' || save == 'C' || save == 'c') {
            action = -1;
          }
        }

        break;
      // Wczytywanie danych z pliku domyślnego
      case 1:
        strncpy(fileName, "data/db.dat", 32);
        dataCount = getDataCount(fileName);
        getData(fileName, data, dataCount);
        system(CLEAR);
        break;
      // Wczytywanie danych z wybranego pliku
      case 2:
        // Monit o niezapisanych zmienach
        if (unsaved) {
          system(CLEAR);
          printf("\n\n\tCzy chcesz zapisać zmiany w pliku: %s [ T ak / N ie / A nuluj ]?\n\t", fileName);
          fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
          scanf(" %c", &save);

          if (save == 'T' || save == 't' || save == 'Y' || save == 'y') {
            fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
            saveData(fileName, data, dataCount);
            unsaved = 0;
          } else if (save == 'A' || save == 'a' || save == 'C' || save == 'c') {
            fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
            break;
          }
        }

        system(CLEAR);
        printf("\n\n\tWCZYTYWANIE DANYCH\n");
        printf("\tPodaj nazwe pliku: ");
        fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
        scanf("%s", fileName);
        dataCount = getDataCount(fileName); // Pobranie ilości danych z pliku

        // Rozszerzenie zmiennej data[]
        dataRealloc = (struct person *)realloc(data, (dataCount) * sizeof(struct person)); // Przypisanie odpowiedniej wielkości zmiennej dataRealloc[]

        if (dataRealloc) {
          data = dataRealloc; // Przypisanie wielkości dataRealloc[] zmiennej data[]
        } else {
          exit(5); // Error handler: zamknięcie programu
        }

        getData(fileName, data, dataCount); // Pobranie danych
        break;
      // Wyświetlanie danych
      case 3:
        printData(data, dataCount);
        // printf("\n\tNacisnij ENTER, aby powrocic");
        // fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
        // getch();
        break;
      // Sortrowanie danych
      case 4:
        unsaved = 1; // Niezapisane zmiany
        system(CLEAR);
        printf("\n\n\tSORTOWANIE DANYCH\n");
        printf("\tWybierz w jaki sposob chcesz posortowac dane:\n");
        printf("\t\t1) nazwisko, imie, wiek, zarobki\n");
        printf("\t\t2) imie, nazwisko, wiek, zarobki\n");
        printf("\t\t3) wiek, nazwisko, imie, zarobki\n");
        printf("\t\t4) zarobki, nazwisko, imie, wiek\n\n\t");
        fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
        scanf("%hu", &action);
        sortData(data, dataCount, action);
        printData(data, dataCount);
        // printf("\n\tNacisnij ENTER, aby powrocic");
        // fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
        // getch();
        action = -1; // Aby w przypadku wprowadzenia 0 program się nie zakończył
        break;
      // Dodawanie nowych danych (rekordów)
      case 5:
        unsaved = 1; // Niezapisane zmiany
        system(CLEAR);
        printf("\n\n\tDODAWANIE NOWYCH REKORDOW\n");
        printf("\tPodaj liczbe rekordow do dodania: ");
        fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
        scanf("%u", &n);

        dataRealloc = (struct person *)realloc(data, (dataCount + n) * sizeof(struct person)); // Przypisanie odpowiedniej wielkości zmiennej dataRealloc[]

        // Rozszerzenie zmiennej data[]
        if (dataRealloc) {
          data = dataRealloc; // Przypisanie wielkości dataRealloc[] zmiennej data[]
        } else {
          exit(5); // Error handler: zamknięcie programu
        }

        dataCount = addData(data, n, dataCount);
        break;
      // Usuwanie danych
      case 6:
        unsaved = 1; // Niezapisane zmiany
        system(CLEAR);
        printf("\n\n\tUSUWANIE REKORDOW\n");
        printf("\tPodaj liczbe rekordow do usuniecia: ");
        fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
        scanf("%u", &n);
        dataCount = deleteData(data, n, dataCount); // Zmniejszenie liczby ilości danych
        /* Program się krzaczył, więc po prostu ograniczam wyświetlanie, zapisywanie danych zmienną dataCount
        dataRealloc = realloc(data, (dataCount - n) * sizeof(struct person));

        if (dataRealloc) {
          data = dataRealloc;
        } else {
          exit(5);
        }
        */
        break;
      // Zapisywanie do pliku domyślnego
      case 7:
        unsaved = 0;
        system(CLEAR);
        strncpy(fileName, "data/db.dat", 32);
        saveData(fileName, data, dataCount);
        break;
      // Eksportowanie danych (zapisywanie do nowego / własnego pliku)
      case 8:
        unsaved = 0;
        system(CLEAR);
        printf("\n\n\tEKSPORT DANYCH\n");
        printf("\tPodaj nazwe pliku do wyeksportowania (max 31 znakow): ");
        fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
        scanf("%s", fileName);
        saveData(fileName, data, dataCount);
        break;
      // Generowanie losowych danych
      case 9:
        system(CLEAR);
        printf("\n\n\tGENEROWANIE LOSOWYCH DANYCH\n");
        printf("\tPodaj nazwe pliku do wyeksportowania danych (max 31 znakow): ");
        fflush(stdin); // Czyszczenie buffora standardowego wejścia (nie jestem pewien czy działa)
        scanf("%s", fileName);
        getRandomPeople(fileName);
      break;
      // W innym przypadku zignoruj imput
      default:
        action = 0;
        break;
    }
  } while(action);

  return 0;
}
