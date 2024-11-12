# Contador sin locks

## Compilacion

```
make
```

## Uso

Para usar ejecutelo de la siguiente manera:

```
./counter_wo_locks -t N_THREADS -c COUNTER
```

**Ejemplos**

La siguiente tabla muestra algunos ejemplos donde se ilustra el uso de la aplicación:

|Caso|Numero de hilos|Valor del contador|Comando aplicado|
|---|---|---|---|
|1|1|100000000|```./counter_wo_locks -t 1 -c 100000000```|
|2|2|100000000|```./counter_wo_locks -t 2 -c 100000000```|
|3|4|100000000|```./counter_wo_locks -t 4 -c 100000000```|

