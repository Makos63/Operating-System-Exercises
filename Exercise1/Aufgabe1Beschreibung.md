# Aufgabe 1: Programmierung mit Systemaufrufen
## Vorlesung Betriebssysteme
### Wintersemester 2018/2019

#### Diese Version: Prof. Dr. Ronald Moore
#### Originale Version: Prof. Dr. Alois Schütte
#### Fachbereich Informatik, Hochschule Darmstadt

## 1. Praktikumsaufgabe: Eine Mini Shell realisieren
**Ziel: **Systemaufrufe zur Prozesserzeugung anwenden

### Schritt 1: Shell entwickeln

Realisieren Sie einen Kommando-Interpreter (in C oder C++). Orientieren Sie sich dabei an der Unix-Shell. Die Shell liest die Benutzereingabe, extrahiert daraus Kommandonamen und optional anzugebende Argumente. Dann wird ein neuer Prozess erzeugt, der das Kommando ausführt. Der Vater-Prozess wartet auf die Beendigung des Kindprozesses.

Verwenden Sie als C-Programmgerüßt die Vorlage aus dem Skript.

Alle Benutzereingaben sollen in einer Log-Datei protokolliert werden und zwar in der Form:

    [Datum und Uhrzeit] eingegebenes Kommando

Die Shell soll durch Eingabe von ’CTR_C’ beendet werden. Dabei soll nachgefragt werden, ob man die Shell wirklich verlassen will, etwa durch (’Do you want to quit (y/n) ?’).

Als Benutzer-Prompt soll ’aktuelles Verzeichnis >’ verwendet werden, also sieht ein Dialog etwa wie folgt aus (nur ein Beispiel!):

    $ pwd                  # wir sind noch in der Unix-Shell
    /tmp
    $ ~/bs/Aufg1/miniShell # Aufruf Ihrer Minishell
    exit with CTR-C
    /tmp > date
    Mi 22 Jan 2014 11:08:29 CET
    /tmp > cd /usr/local
    /usr/local > pwd
    /usr/local
    ...
    /usr/local > ^C
    Do you really want to quit (y/n) ? y
    $ echo $SHELL          # wieder in normaler Shell

### Schritt 2 Shell um Hintergrundverarbeitung erweitern

Erweitern sie die Shell aus Aufgabe 1 so, dass der Benutzer bei der Kommandoeingabe (letztes Zeichen ist ein ’&’) bestimmen kann, dass das eingegebene Kommando im Hintergrund ausgeführt wird, also direkt ein weiteres Kommando eingebbar ist. Die Prozess-Id des Kindprozesses soll dabei ausgegeben werden.

  **Achtung: Nach Beendigung eines im Hintergrund ablaufenden Kommandos darf kein   Zombi-Prozess enstehen.
**

Beispiel (wird so oder leicht abgewandelt auch für die Abnahme im Praktikum verwendet):

        $ pwd                  # wir sind noch in der Unix-Shell
        /tmp
        $ ~/bs/Aufg1/miniShell # Aufruf Ihrer Minishell
        exit with CTR -C
        /tmp > echo 1 2 drei
        1 2 drei
        /tmp > date
        Wed Oct 10 16:58:01 CEST 2018
        /tmp > sleep 10
        /tmp > date
        Wed Oct 10 16:58:07 CEST 2018
        /tmp > sleep 20 &
        [97160]
        /tmp > date
        Wed Oct 10 16:58:09 CEST 2018
        /tmp > ps
        PID TT STAT TIME COMMAND
        96440 s000 S 0:00.04 -bash
        97144 s000 S+ 0:00.00 msh
        97160 s000 S+ 0:00.00 sleep 20
        /tmp > ps
        PID TT STAT TIME COMMAND
        96440 s000 S 0:00.04 -bash
        97144 s000 S+ 0:00.00 msh
        /tmp > date
        Wed Oct 10 16:58:42 CEST 2018
        /tmp > ^C
        Do you want to quit (y/n) ? y
        $ echo $SHELL          # wieder in normaler Shell