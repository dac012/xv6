# xv6

Este repositorio contiene una versión trabajada y adaptada del sistema operativo educativo xv6. xv6 es una reimplementación moderna y sencilla de Unix Version 6 (v6), diseñada para propósitos académicos, prácticas de laboratorio y experimentación con sistemas operativos.

## Descripción

xv6 está escrito en C y Assembly, y proporciona una base clara para aprender conceptos de sistemas operativos como:

- Gestión de procesos y memoria
- Planificación de CPU
- Llamadas al sistema y manejo de excepciones
- Sistemas de archivos básicos
- Sincronización y concurrencia

Este proyecto es ideal para estudiantes, docentes y entusiastas que deseen profundizar en el funcionamiento interno de un sistema operativo real y minimalista.

## Estructura del repositorio

- `.vscode/`: Configuración para el entorno de desarrollo Visual Studio Code.
- `xv6/`: Carpeta principal con el código fuente y recursos del sistema operativo xv6.
- `scheduler`, `scheduler.c`: Archivos relacionados con el planificador de procesos.
- `README.md`: Este archivo.

## Requisitos

- QEMU (máquina virtual recomendada para pruebas)
- Herramientas de compilación para C y Assembly (gcc, as, ld, etc.)
- GNU Make

## Compilación y ejecución

Clona el repositorio y ejecuta:

```sh
make
make qemu
```

Esto compilará xv6 y lo lanzará en QEMU.

## Créditos y licencia

xv6 es originalmente desarrollado por el MIT para su curso de sistemas operativos. Esta versión contiene adaptaciones, prácticas o extensiones propias para el estudio y la experimentación.

Consulta el archivo LICENSE para detalles sobre su uso y distribución.
