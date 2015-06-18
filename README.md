# Projekt k predmetu ICP - Labyrinth

Autori:
	- Peter Gazdík <xgazdi03@stud.fit.vutbr.cz>
	- Klára Mihalíková <xmihal05@stud.fit.vutbr.cz>

## Potrebné knižnice:

QT vo verzii 5.2.1
BOOST vo verzii 1.55.0

## Popis projektu:

Tento projekt implementuje aplikáciu Labyrinth, ktorá vychádza z rovnomennej spoločenskej hry. Aplikácia je navrhnutá
lokálne pre 2 - 4 hráčov, pričom veľkosť hracieho poľa je voliteľná v rozmedzí 5x5 až 11x11. Cieľom hry je zozbierať
určitý počet pokladov, ktorý závisí na vybranom počte hráčov a počte vygenerovaných pokladov pre danú hru.

## Rozloženie hracej plochy:
	
Hracia plocha obsahuje:

  - voľnú kartu: kameň hracieho poľa určený na vloženie do labyrintu
  - tlačidlo Turn Right: slúži na otáčanie voľnej karty
  - kartu s pokladom: karta zobrazujúca hľadaný poklad (každý hráč má vlastnú)
  - tlačidlo OK: potvrdzuje, že hráč končí svoj ťah
  - panel zobrazujúci skóre hráčov
  - hraciu dosku: hracie pole obsahujúce hracie kamene, poklady a hráčov


## Pravidlá hry

Hráč na ťahu najskôr vloží voľnú kartu do hracieho poľa a tak zmení rozloženie bludiska. Následne sa pohybuje, pričom
posunúť sa môže o ľubovolný počet krokov a svoju finálnu pozíciu potvrdzuje tlačidlom OK. Na ťahu je ďalší hráč...
