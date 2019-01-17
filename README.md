# Gra w życie

Symulacja życia komórek na dwuwymiarowej planszy. Odbywa sie na bardzo prostych zasadach, określających jedynie kiedy żywa komórka przeżywa daną jednostę czasu, a kiedy nie oraz kiedy na pustym miejscu powstaje nowa komórka. Jest to najprostszy przykład automatu komórkowego.
Szerszy opis zagadnienia dostępny [tutaj](https://pl.wikipedia.org/wiki/Gra_w_%C5%BCycie).

Program przyjmuje różne parametry, określające początkowy stan planszy, sąsiedztwo i reguły gry.
W tej wersji komórki na skraju planszy traktowane są tak, jakby zamiast krawędzi był tam kolejny rząd martwych komórek.

# Kompilacja

Kompilacja odbywa się za pomocą uruchomienia komendy

```bash
make lifegame
```

Skompilowany program znjdzie się w folderze bazowym projektu

# Parametry

Program przyjmuje 5 różnych parametrów:

-   **-d, --delay**
    Liczba milisekund dzielących kolejne iteracje. Domyślna wartość to 1000 (1s). Gdy wynosi 0 to program oczekuje na naciśnięcie klawisza ENTER po każdej iteracji.

-   **-n, --neighbourhood**
    Nazwa pliku tekstowego zawierającego maskę sąsiedztwa. Więcej formacie i działaniu tego pliku [tutaj](#plik-sąsiedztwa)
-   **-c, --createnum**
    Ciąg cyfr, oznaczający liczby (0-8) żywych sąsiadów, dla których na pustym polu powstaje nowa komórka.
-   **-s, --surviveum**
    Ciąg cyfr określający, dla jakich liczb (0-8) żwych sąsiadów komórka przeżywa do następnej iteracji.
-   **-h, --help**
    Wypisuje instrukcje używania

Wszystkie one są opcjonalne.

Domyślnymi regułami gry są reguły Conwaya 23/3. Domyśnie używane jest sąsiedztwo Moore'a.

Oprócz parametrów, należy podać także nazwę pliku, z którego program ma wczytać początkowy stan planszy. Argument ten jest wymagany. O formatowaniu danych w tym pliku przeczytasz [tutaj](#plik-planszy)

## Przykłady

Zaczyna symulację z sybkością 300ms ze stanem zapisanym w pliku board.txt

```bash
./gameOfLife.out -d 300 board.txt
```

Zaczyna symulację na zasadach 012345678/3 z szybkością 4fps

```bash
./gameOfLife.out -s 012345678 -c 3 -d 250 boards/plansza.txt
```

# Formaty plików wejściowych

W pliku wejściowym znak `1` oznacza żywą komórkę, każdy inny martwą.

Dla upodobnienia planszy wymiarami do tej wyświetlanej w konsoli, oraz żeby wymiary były bardziej zbilżone wizualnie do siebie, **rzędy są dwa razy dłuższe niż kolumny.**

Z założenia jedno pole planszy tworzy znak + spacja, np `1 0` , lecz dowolny inny znak może pełnić rolę "dopełniacza" w polu. Kolejność w obrębie pola nie jest istotna.

## Plik planszy

Długość pierwszej liniki tego pliku określa rozmiar planszy (ilość pól, nie znaków!).
Plansza zawsze jest traktowana jako kwadrat.
W każdej następnej linii, która jest dłuższa niż pierwsza, nadmiar zostanie zignorowany.
Ponadto, w zbyt krótkiej linii puste miejsce jest uzupełniane zerami.

To samo dodtyczy nadmiarowych lub brakujących rzędów.
Pozwala to dość swobodnie bawić się w pliku, nie martwiąc sie o spowodowanie błędu w działaniu programu.

### Przykłady

Plik definiujący pustą planszę 10x10

```
0 0 0 0 0 0 0 0 0 0
```

Plik definiujący planszę 15x15 z dwoma bloczkami i blinkerem

```
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0



    1 1         1 1
    1 1         1 1


        1
        1
        1


```

Zera w pierwszej linice są również opcjonalne (wystarczyłyby same spacje), lecz dzięki nim lepiej widać rozmiar planszy.

## Plik sąsiedztwa

Zawiera on maskę bitową w postaci macierzy 3x3 określającą, które z komórek sąsiadujących z danym polem mają być brane pod uwagę podczas liczenia żwywych sąsiadów.
Środkowe pole jest ignorowane niezależnie od wartości (komórka nie może sąsiadować sama z sobą).

Tak samo jak w przypadku pliku planszy wszystkie nadmiarowe znaki i linie są ignorowane, a brakujące uzupełniane zerami.
Tutaj jednak pierwsza linia nie jest istotna, ponieważ rozmiar maski jest stały.

### Przykłady

Maska obrazujaca sąsiedzwtwo Moore'a (domyślna)

```
1 1 1
1 0 1
1 1 1
```

Sąsiedztwo von Neumanna

```
0 1 0
1 0 1
0 1 0
```

## Licencja

Ten program jest udostępniany na bazie licencji [MIT](./LICENSE)
