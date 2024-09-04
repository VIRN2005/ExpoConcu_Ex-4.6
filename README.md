# README
================

Este programa es una implementación multihilo de una lista enlazada con un cerrojo de lectura-escritura. El programa permite que varios hilos accedan a la lista enlazada simultáneamente, con lectores que pueden acceder a la lista concurrentemente mientras que los escritores tienen acceso exclusivo a la lista.

## Funcionalidad
----------------

El programa consta de tres componentes principales:

1. **Lista enlazada**: Una implementación de lista enlazada que permite insertar y eliminar nodos.
2. **Cerrojo de lectura-escritura**: Una implementación personalizada de un cerrojo de lectura-escritura que permite que varios lectores accedan a la lista enlazada concurrentemente, mientras que los escritores tienen acceso exclusivo a la lista.
3. **Hilos**: Se crean dos hilos, uno para insertar nodos en la lista enlazada y otro para eliminar nodos de la lista.

## Cómo funciona
----------------

Aquí hay una explicación paso a paso de cómo funciona el programa:

1. El programa inicializa una lista enlazada y un cerrojo de lectura-escritura.
2. Se crean dos hilos, uno para insertar nodos en la lista enlazada y otro para eliminar nodos de la lista.
3. El hilo de inserción inserta nodos en la lista enlazada utilizando la función `list_insert`, que adquiere el cerrojo de escritura antes de insertar un nodo.
4. El hilo de eliminación elimina nodos de la lista enlazada utilizando la función `list_delete`, que también adquiere el cerrojo de escritura antes de eliminar un nodo.
5. La función `list_print` se utiliza para imprimir el contenido de la lista enlazada, que adquiere el cerrojo de lectura antes de imprimir la lista.
6. El cerrojo de lectura-escritura asegura que varios lectores puedan acceder a la lista enlazada concurrentemente, mientras que los escritores tienen acceso exclusivo a la lista.

## Requisitos
-------------

* Un compilador de C (por ejemplo, `gcc`)
* La biblioteca `pthread` para la implementación de hilos

## Compilación y ejecución
---------------------------

Para compilar y ejecutar el programa, sigue estos pasos:

1. Compila el programa utilizando un compilador de C (por ejemplo, `gcc`).
2. Ejecuta el programa utilizando el ejecutable compilado.

## Licencia
---------

Este programa está bajo la licencia MIT. Ver el archivo `LICENSE` para más información.

## Nota
-----

Este programa es una demostración de una implementación de cerrojo de lectura-escritura y no está destinado para uso en producción. El programa asume que la lista enlazada no está vacía al eliminar nodos y no maneja errores o casos límite.
