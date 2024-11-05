# Definición de variables
CC = gcc                     # Compilador
CFLAGS = -Wall -pthread      # Opciones de compilación (avisos, hilos)
SOURCES = $(wildcard *.c)    # Todos los archivos .c en el directorio actual
OBJECTS = $(SOURCES:.c=.o)   # Los archivos objeto generados a partir de .c
EXECUTABLES = $(SOURCES:.c=) # Ejecutables generados, uno por cada archivo fuente
INCLUDES = .

# Regla para compilar todo
all: $(EXECUTABLES)

# Regla genérica para compilar cada archivo .c en un ejecutable
$(EXECUTABLES): % : %.o
	$(CC) $(CFLAGS) -o $@ $<

# Regla genérica para compilar cada archivo .c en un archivo .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos objeto y ejecutables generados
clean:
	rm -f $(OBJECTS) $(EXECUTABLES)