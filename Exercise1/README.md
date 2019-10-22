# Aufgabe 1: Programmierung mit Systemaufrufen
## Vorlesung Betriebssysteme
### Wintersemester 2019/2020

#### Diese Version: Prof. Dr. Ronald Moore
#### Originale Version: Prof. Dr. Alois Schütte
#### Schritt 3 geliehen von: Prof. Dr. Michael von Rüden
#### Fachbereich Informatik, Hochschule Darmstadt

## 1. Praktikumsaufgabe: Eine Mini Shell realisieren
**Ziel: **Systemaufrufe zur Prozesserzeugung anwenden

### Schritt 1: Shell entwickeln

Realisieren Sie einen Kommando-Interpreter (in C oder C++). Orientieren Sie sich dabei an der Unix-Shell. Die Shell liest die Benutzereingabe, extrahiert daraus Kommandonamen und optional anzugebende Argumente. Dann wird ein neuer Prozess erzeugt, der das Kommando ausführt. Der Vater-Prozess wartet auf die Beendigung des Kindprozesses.

Verwenden Sie als C-Programmgerüßt die Vorlage aus dem Skript.

Der Befehl **exit** soll Ihre Shell beenden. Dabei soll zuerst abgefragt werden, ob wirklich die Shell verlassen werden soll und erst dann die Shell beendet werden.

Als Benutzer-Prompt soll **'aktuelles Verzeichnis >’** verwendet werden, also sieht ein Dialog etwa wie folgt aus (nur ein Beispiel!):

    $ pwd                  # wir sind noch in der Unix-Shell
    /tmp
    $ ~/bs/Aufg1/miniShell # Aufruf Ihrer Minishell
    exit with "exit"
    /tmp > date
    Tue 22 Oct 20:28:20 CEST 2019
    /tmp > cd /usr/local
    /usr/local > pwd
    /usr/local
    ...
    /usr/local > exit
    Do you really want to quit (y/n) ? y
    $ echo $SHELL          # wieder in normaler Shell
      ...

### Schritt 2: Shell um Hintergrundverarbeitung erweitern

Erweitern Sie die Shell aus Aufgabe 1 so, dass der Benutzer bei der Kommandoeingabe (letztes Zeichen ist ein ’&’) bestimmen kann, dass das eingegebene Kommando im Hintergrund ausgeführt wird, also direkt ein weiteres Kommando eingebbar ist. Die Prozess-Id des Kindprozesses soll dabei ausgegeben werden.

*Stellen Sie sicher, dass die Shell keine Zombie-Prozesse hinterlässt, indem Sie in der Shell geeignet auf das Beenden eines Prozesses reagieren.*

Beispiel (wird so oder leicht abgewandelt auch für die Abnahme im Praktikum verwendet):

        $ pwd                  # wir sind noch in der Unix-Shell
        /tmp
        $ ~/bs/Aufg1/miniShell # Aufruf Ihrer Minishell
        exit with CTR -C
        /tmp > echo 1 2 drei
        1 2 drei
        /tmp > date
        Wed Oct 10 16:58:01 CEST 2019
        /tmp > sleep 10
        /tmp > date
        Wed Oct 10 16:58:07 CEST 2019
        /tmp > blahblahwoofwoof
        minishell: command not found: blahblahwoofwoof
        /tmp > sleep 20 &
        [97160]
        /tmp > date
        Wed Oct 10 16:58:09 CEST 2019
        /tmp > ps
        PID TT STAT TIME COMMAND
        96440 s000 S 0:00.04 -bash
        97144 s000 S+ 0:00.00 msh
        97160 s000 S+ 0:00.00 sleep 20
        Process 97160 done (sleep 20)
        /tmp > ps
        PID TT STAT TIME COMMAND
        96440 s000 S 0:00.04 -bash
        97144 s000 S+ 0:00.00 miniShell
        /tmp > date
        Wed Oct 10 16:58:42 CEST 2019
        /tmp > exit
        Do you want to quit (y/n) ? n
        /tmp > cd
        /home/studentX/ > exit
        Do you want to quit (y/n) ? y
        $ echo $SHELL          # wieder in normaler Shell
        

### Schritt 3: EXTRA-CREDIT: Shell um Signale erweitern

*Dieser Schritt ist für Ehrgeizigen reserviert.  Er ist also nicht Pflicht.*

Erweitern Sie die Shell so, dass bei Eingabe von CTRL-C der aktuell laufende
Vordergrundprozess (kein Hintergrundprozess!) das Signal SIGINT zugestellt bekommt, nicht Ihre Shell.

*  Erweitern Sie die Shell so, dass bei Eingabe von CTRL-Z der aktuell laufende
   Vordergrundprozess (kein Hintergrundprozess!) das Signal SIGTSTP zugestellt bekommt und damit angehalten wird.

*  Implementieren Sie einen Shell Befehl fg, der einen (1 ist hier ausreichend!) mittels CTRL-Z (SIGTSTP) angehaltenen Prozess wieder in den Vordergrund bringt.

* Implementieren Sie einen Shell Befehl bg, der einen (1 ist hier ausreichend!) mittels CTRL-Z (SIGTSTP) angehaltenen Prozess im Hintergrund weiterlaufen lässt.

*  Stellen Sie sicher, dass die Shell nur dann beendet werden kann, wenn sämtliche im Hintergrund laufenden Prozesse ebenfalls beendet sind. Andernfalls soll eine Fehlermeldung ausgegeben werden.

* Wenn Sie das Signal SIGINT oder SIGTSTP an Ihre Shell senden, soll nur ein evtl. laufender Vordergrundprozess dieses Signal erhalten. Um zu verhindern, dass Signale, die an Elternprozesse (d.h. die Shell) geschickt werden, auch an Hintergrundprozesse gesendet werden, ändern Sie die Prozessgruppe des Kindprozesses auf die PID des Kindprozesses. Sie können dafür den Systemaufruf setpgid nutzen.

* Wenn kein Vordergrundprozess läuft, soll mittels CTRL-C die Shell beendet werden können. Dazu soll allerdings vorher eine Abfrage („Wollen Sie die Shell wirklich beenden? (J/N)“ angezeigt und die Antwort entsprechend ausgewertet werden.

* Testen Sie Ihre Shell mit u.a. folgenden Befehlen/Eingaben in dieser Reihenfolge (Achtung:am Schluss sollte es notwendig sein, 2x exit einzugeben):


		$ ./miniShell
		Welcome to myshell!
		 firefox
		^Z [caught SIGTSTP]
		/tmp > ps ax
		/tmp > fg
		/tmp > ^C [caught SIGINT]
		/tmp > firefox
		/tmp > ^Z [caught SIGTSTP]
		/tmp > bg
		/tmp > ^C [caught SIGINT, no fg process]
		/tmp > exit
		Background processes running!
		... hier den Hintergrundprozess manuell beenden ...
		/tmp > exit
		/tmp > Do you really want to exit(Y/N)? Y
	

### Schritt *n* In code.fbi.h-da.de pushen

Stellen Sie sicher, dass Ihr gesamter Code in GitLab eingecheckt ist. 

Das soll immer wieder gemacht werden, um Verlust zu vermeiden und um die Zusammenarbeit in der Gruppe zu erleichtern.

Nach Abgabe der Aufgabe *muss* es (jindestens noch) ein letzes mal geschehen.
