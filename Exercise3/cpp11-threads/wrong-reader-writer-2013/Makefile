#Wichtig - Diese Datei soll "Makefile" gennant werden!

# HINWEIS: Wenn Sie nicht sicher sind, ob diese Datei noch richtig ist,
# rufen sie "make -n" auf - das zeigt, was passieren würde, wenn Sie
# "make" aufrufen würden - ohne aber irgendetwas sonst zu tun!
# D.h. "make -n" ist harmlos - aber informativ.

# ==== Macros ====
# Welcher Compiler?
# CC = clang++
CC = g++

# Hier sind die Bibliotheke,
# die ganz am Ende mit gelinkt werden mussen
LIBS = -lpthread

# Hier sind die "Objekt-Datein", die erzeugt werden müssen.
# D.h. - jede Datei *.c bzw *.cpp wird zuerst zu eine Datei *.o
# compiliert - und hier ist die Liste der Dateien.
OBJ = database.o reader-writer-threads.o  reader-writer.o

# Hier ist die Name des Programms, die wir bauen wollen
TARGET = reader-writer

#  Compilerflags
# Hier sind die Argumente, die wir verwenden, wenn wir den Compiler
# aufrufen:
# -g  		- erzeuge Debugging info für den debugger
# -Wall 	- alle Warnungen, bitte
# -fmessage-length=0 - Warnungen bzw Fehlermeldungen nicht über mehrere Zeile teilen
#                      - für Eclipse
# -MMD          - erzeuge *.d Dateien, die später von Make importiert werden.
#                             vgl. http://mad-scientist.net/make/autodep.html
#             (die Version hier ist viel einfacher, und daher u.U. nur mit
#              gnu make und { g++ oder clag++ } kompatibel).
FLAGS = -g -std=c++11 -Wall -MMD -fmessage-length=0

# ==== TARGETS und REGELN ====
# Es ist ganz WICHTIG,
# dass die Zeile unten, die Befehle beinhalten
# (z. B. gcc... oder g++... oder rm ... )
# mit TABULATOR anfangen!

# Regel: all hängt von TARGET ab.
#        D.h. "make all" == "make <was auch immer TARGET ist>
# Das ist der erste Regel, also ist "make" == "make
all: $(TARGET)

#special - "make clean" löscht alle *.o Dateien, und den Target, usw usf
clean:
	rm -fv $(OBJ) $(TARGET) outputFile.txt *~ *.d

####################  Abhängigkeiten

# Algemeiner Regel - wie eine .o Datei von einer .cpp Datei
# erzeugt wird - auch, dass es eine Abhängigkeit gibt (!)
# Hinweis: Der "Recipe" ($(CC) -c $(FLAGS) ...), aber nicht die Abhänigkeit,
# wird verwendet wenn es keine *.d Dateien gibt.  Falls es sie gibt, werden
# die Regelen dort kombiniert mit dem Rezept hier.
%.o : %.cpp
	$(CC) -c $(FLAGS) -o $@ $<

# Nun haben wir alle die *.o Dateien erzeugt.
# Nun müssen wir den Target linken.
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS)
	touch outputFile.txt

# Fertig!
