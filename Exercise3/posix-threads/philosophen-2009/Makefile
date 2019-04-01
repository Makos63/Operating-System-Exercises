#Wichtig - Diese Datei soll "Makefile" gennant werden!

# HINWEIS: Wenn Sie nicht sicher sind, ob diese Datei noch richtig ist,
# rufen sie "make -n" auf - das zeit, was passieren würde, wenn Sie 
# "make" aufrufen würden - ohne aber irgendetwas sonst zu tun!
# D.h. "make -n" so harmloss sein - aber informativ.

# ==== Macros ====
# Hier sind die Bibliotheke, f
# die ganz am Ende mit gelinkt werden mussen
LIBS = -lpthread

# Hier sind die "Objekt-Datein", die erzeugt werden müssen.
# D.h. - jede Datei *.c bzw *.cpp wird zuerst zu eine Datei *.o
# compiliert - und hier ist die Liste der Dateien.
OBJ = randomness.o time-killer.o philosophers-dijkstra-utils.o philosophers-dijkstra.o  

# Hier ist die Name des Programms, die wir bauen wollen
TARGET = philosophers-dijkstra

#  Compilerflags
# Hier sind die Argumente, die wir verwenden, wenn wir den Compiler
# aufrufen:
# -g  		- erzeuge Debugging info für den debugger
# -Wall 	- alle Warnungen, bitte
# -fmessage-length=0 - Warnungen bzw Fehlermeldungen nicht über mehrere Zeile teilen
#                      - für Eclipse
FLAGS = -g -Wall -fmessage-length=0 $(INCDIRS)

# ==== TARGETS und REGELN ====
# Es ist ganz WICHTIG, 
# dass die Zeile unten, die Befehle beinhalten 
# (z. B. gcc... oder g++... oder rm ... ) 
# mit TABULATOR anfangen!

# Regel: all hängt von TARGET ab.  
#        D.h. "make all" == "make <was auch immer TARGET ist>
# Das ist der erste Regel, also ist "make" == "make 
all: $(TARGET)

#special - "make clean" deletes all *.o Dateien, und den Target, usw 
clean:
	rm -fv $(OBJ) $(TARGET) *~

####################  Abhängigkeiten

# Wenn time-killer.h ODER random.h geändert wurden, 
# muss time-killer.o neu erzeut werden.
#   Hinweis: Der Regel WIE time-killer.o erzeugt wird, 
#   folgt weiter unter (bei Muster "%0: %c").
#   Deswegen wird die Abhängigkeit zwischen time-killer.o und
#   time-killer.c hier NICHT angegeben!
time-killer.o: time-killer.h randomness.h

# Wenn randomness.h geändert wurde, 
# muss randomness.o neu erzeut werden
randomness.o: randomness.h

# Wenn time-killer.h ODER philosophers-dijkstra-utils.h geändert  
# wurden, muss philosophers-dijkstra-utils.o neu erzeut werden
philosophers-dijkstra-utils.o: philosophers-dijkstra-utils.h time-killer.h

# Wenn random.h ODER philosophers-dijkstra-utils.h geändert  
# wurden, muss philosophers-dijkstra.o neu erzeut werden
philosophers-dijkstra.o: philosophers-dijkstra-utils.h randomness.h

# Algemeiner Regel - wie eine .o Datei von einer .c Datei 
# erzeugt wird bzw. abhängt.
%o: %c
	gcc -c $(FLAGS) -o $@ $<

# Nun haben wir alle die *.o Dateien erzeugt.
# Nun müssen wir den Target linken.
$(TARGET): $(OBJ)
	gcc -o $(TARGET) $(OBJ) $(LIBS)

# Fertig!
