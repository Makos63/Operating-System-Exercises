# Aufgabe 4: Virtuelle Speicherverwaltung

## Ziel:

Sie sollen eine Umgebung für die Erforschung und das Testen von virtueller-Speicher-Algoritmen, vor allem Seitenersetzungsalgorithmen, bauen.

Danach sollen sie eine Hypothese formulieren und testen unter Verwendung Ihrer Umgebung, um sowohl virtuelle Speicher zu untersuchen als auch zu zeigen, dass Ihre Umgebung funktioniert.

Diese Aufgabenbeschreibung verwendet Begriffe vom Kapitel 4 des Skripts ("Speicherverwaltung", besonders den Absatz über "Virtueller Speicher").

## Anforderungsanalyse

Folgende Anforderungen beschreiben die notwendige Verhalten Ihrer Test-Umgebung; Sie haben komplette Freiheit bzgl. der Implementierung. Daraus folgt, dass alle Design- bzw. Implementierungs-Entscheidungen Ihnen überlassen sind!

Grundsätzlich soll Ihre Umgebung mindestens zwei Prozesse simulieren, die von virtuellen Speicher Daten lesen bzw. zu virtuellen Speicher Daten schreiben.  Die Daten sollten allerdings in einem gemeinsamen "physischen" Speicher tatsächlich gespeichert werden -- solange der ausreicht. Darüber hinaus können Daten auf einem Backup-Speicher, d.h. eine "Festplatte" gespeichert werden.

Alle Daten sollen so gewählt werden, sodass das System sich selbst testet. Das heißt, jedes Prozess darf nur seine eigenen Speicher lesen oder überschreiben. Daraus folgt, dass das System es bemerken sollte, wenn ein Prozess die Daten eines anderen Prozesses ließt, oder die Daten eines anderen Prozesses überschreibt.  Auch Speicherbereiche, die keinem Prozess zugeteilt wurden, dürfen nicht gelesen werden (bzw. es muss bemerkt werden, falls das doch passiert),

Ihre Umgebung sollte folgende Komponente modellieren bzw. simulieren:

* Ein Hauptspeicher (RAM).  Ein Speicher mit der Große von 1 Kilobyte würde anfangs reichen.  Konzeptuell ist der Hauptspeicher nicht viel mehr als eine Array von Bytes.
* Ein Backup-Speicher, d.h. eine Festplatte.  Sie muss mindestens alle Seiten, die nicht eingelagert sind, speichern, und zwar für alle Prozessen. Sie darf mehr speichern. Die "Festplatte" ist auch kaum mehr als eine Array von Bytes.  Allerdings sollten die Seiten jeder Prozesse mit Inhalt initialisiert werden, sodass wir die Seiten der verschiedenen Prozesse auseinander halten können, s.o.
* Eine MMU (Memory Management Unit).  Sie soll virtuelle Adressen in physische Adressen übersetzten. Sie verwendet die aktuelle Seitentabelle. 
  * Falls die Übersetzung nicht möglich ist, soll sie das Betriebssystem auf rufen. S.u. 
  * Sie sollen selbst festlegen, wie groß die virtuelle Speicherräume sind, d.h. wie viele Bits die Adressen haben, und wie groß eine Seite ist; d.h. wie viele Bits für die Offsets notwendig sind -- und wie viele Bits für die Seitenzahlen übrig bleiben. Es soll relativ leicht sein, diese Konstante auszutauschen, falls wir deren Auswirkungen testen wollen.
* Die Seitentabellen. Jedes Prozess hat eine eigene Seitentabelle. Die Seitentabelle des aktuellen Prozesses ist die aktuelle Seitentabelle, und wird von der MMU verwendet.  Das Betriebssystem darf auf alle Seitentabellen zugreifen, falls notwendig.
* Das Betriebssystem. Das Betriebssystem hier ist für Seitenvergabe bzw. --- falls keine Seite frei ist -- Seitenersetzung.  Es läuft nur wenn es von der MMU aufgerufen wird. 
* Die CPU.  Die CPU ist stochastisch, d.h. sie wird von Zufalls-Zahlen gesteuert. Sie führt Schritte aus, einen Schritt nach den anderen, wobei in einem Schritt eines der folgende Ereignisse passieren wird. Jedes Ereignis hat eine fest definierte Wahrscheinlichkeit. Die Liste unten ist in der Reihenfolge von wahrscheinlichsten bis unwahrscheinlichsten sortiert:
  * Lesen
    * wie die Adresse für das LOAD-Operation ausgewählt wird, ist nicht definiert, bzw. soll als Teil des jeweiligen Experiments gesehen werden. Anders gesagt, die LOAD- (und STORE-) Operationen verwenden einen austauschbaren Adressengenerator. Sehe unten (!).
    * Die Daten, die aus dem Speicher gelesen werden, sollen auf Richtigkeit geprüft werden. D.h. es soll getestet werden, ob nur der eigenen Seiten gelesen werden. S.o.
  * Schreiben -- genau wie Lesen, s.o. -- mutatis mutandis.
  * Prozesswechsel -- eigentlich Aufgabe eines Betriebssystems; hier macht die CPU einfach eine willkürliche Prozesswechsel.
* Messungen: Die Umgebung soll Messungen machen und am Ende der Simulation sie im Form eines Reports ausgeben. Mindestens die Anzahl Seitenfehler soll gezählt und berichtet werden. Andere Messungen sollen nach Bedarf gemacht werden, sodass aussagekräftige Vergleiche zwischen verschiedenen virtuellen Speicher Algorithmen bzw. Systemen gemacht werden können.
* Andere Komponenten bzw. Datenstrukturen sind auch erlaubt, sogar wahrscheinlich notwendig.  Die Liste, oben, erhebt also keinen Anspruch auf Vollständigkeit.

## Experimente:

Implementieren und testen Sie:
* mindestens zwei Adressengenerator-Algorithmen -- zum Beispiel:
  * Sie könnten zufällige Adressen verwenden, -- in dem Fall scheitert jeder Seitenersetzungsalgorithmus (von Optimal abgesehen), aber als Vergleich ist dieser Generator nicht ungeeignet;
  * Oder ein "Bubble-Sort" simulieren (d.h. immer wieder vom Anfang bis Ende des Speicher "laufen");
  * Oder die letzte Adresse +/- eine zufällige "delta-Adresse" (das nennt man ein "Random Walk");
  * Oder mit einer gewissen Wahrscheinlichkeit die letzte Adresse wiederverwenden und sonst zu einer neuen, zufälliger Adresse springen ("Dr. Who's Random Walk", vielleicht?);
  * Oder einen Generator, den Sie selber aus denken! 
* mindesten zwei Seitenersetzungsalgorithmen.  Geeignet wären Optimal, NRU, FIFO, Clock, LRU, NFU, LRU oder Aging ... Vgl. Skript (Kapitel IV - Speicherverwaltung).

Formulieren Sie eine Hypothese bzgl. welcher Seitenersetzungsalgorithmus geeignet ist, und zwar unter welche Annahmen bzgl. verwendeten Adressen. Formulieren Sie ein Test für Ihre Hypothese, führen Sie dieses Test durch, und dokumentieren Sie die Ergebnisse an Hand von Messungen, die Sie mit Ihrer Umgebung gemacht haben. Stellen Sie Ihre Ergebnisse -- inkl. Ihre Deutung der Ergebnissen -- im Form eines Laborprotokolls dar.  Hinweis: Die Ergebnisse müssen die Hypothese nicht stützen; es ist OK, wenn die Ergebnisse die Hypothese widerlegen.