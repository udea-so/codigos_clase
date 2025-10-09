# Ejemplos con semaforos
Estos ejemplos fueron tomados y adaptados(algunos de ellos) del libro de Operating Systems: Three Easy Pieces ([link](https://pages.cs.wisc.edu/~remzi/OSTEP/)). Los ejemplo se dividen de la siguiente manera

## Ejemplos - Parte 1

Implementación de locks y variables de condicion usando semaforos.
1. Implementación de locks usando semaforos
2. Implementación de variables de condición por medio de semaforos.

## Ejemplos - Parte 2

En esta parte se implemento **The Producer/Consumer (Bounded Buffer) Problem** todo el recorrido se encuentra en el siguiente link [producer_consumer](producer_consumer/) de la siguiente manera:
1. Caso de un buffer de tamaño 1
2. Ejemplo del buffer limitado (buffer circular) el cual se divide en los siguientes analisis:
   * Sección **First Attempt** (link [pc_attemp1](producer_consumer/circular_buffer/pc_attemp1/))
   * Sección **A Solution: Adding Mutual Exclusion** (link [pc_attemp2](producer_consumer/circular_buffer/pc_attemp2/))
   * Secciones **Avoiding Deadlock** y **At Last, A Working Solution** (link [pc_work](producer_consumer/circular_buffer/pc_work/))
   
   La implementación final del libro esta en el siguiente [link](producer_consumer/work/)

## Ejemplos parte 3

1. Sección **Reader-Writer Locks** (link [reader_writer_locks](reader_writer_locks/))
2. Sección **The Dining Philosophers** (link [dining_philosophers](dining_philosophers/))

## Enlaces de utilidad
1. https://hpc-tutorials.llnl.gov/
2. https://hpc-tutorials.llnl.gov/posix/
3. https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/POSIXThreads.html
4. http://www.cse.cuhk.edu.hk/~ericlo/teaching/os/lab/9-PThread/index.html
5. https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
6. https://www.cl72.org/100winProg/pthread-primer.pdf
7. https://bootlin.com/doc/legacy/posix/posix-api.pdf
8. https://github.com/okeeffed/cheat-sheets/blob/master/COMP3520-OS/Pthread.md
9. https://appsrv.cse.cuhk.edu.hk/~ericlo/?page_id=145
10. https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/index.html
11. https://api.riot-os.org/group__posix__semaphore.html
12. https://www.gnu.org/software/libc/manual/html_node/Semaphores.html
13. http://profesores.elo.utfsm.cl/~agv/elo330/2s19/lectures/
14. http://profesores.elo.utfsm.cl/~agv/elo330/2s19/
15. https://see.stanford.edu/materials/icsppcs107/23-Concurrency-Examples.pdf
16. https://sites.cs.ucsb.edu/~rich/class/cs170/notes/Semaphores/index.html
17. https://www3.physnet.uni-hamburg.de/physnet/Tru64-Unix/HTML/APS33DTE/DOCU_010.HTM
18. https://www.ibm.com/docs/en/i/7.4?topic=programs-example-using-semaphore-set-shared-memory-functions
19. https://www.cs.cornell.edu/courses/cs4410/2018su/lectures/lec07-sema.html
20. https://www.cs.cornell.edu/courses/cs4410/2018su/
21. https://esp32tutorials.com/esp32-esp-idf-freertos-semaphore-tutorial/
22. https://courses.washington.edu/cp105/06_Synchronization/Semaphores.html
23. https://courses.washington.edu/cp105/index.html
