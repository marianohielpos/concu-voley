
## Concu-voley

*Trabajo práctico de Técnicas de Programación Concurrente I (75.59)*


Este trabajo consiste en una simulación de un torneo de voley concurrente.
Está programado en C++11 y probado en Linux (Ubuntu 16.04) y Mac OSX.

### Compilar y correr

Se compila vía:

```bash
cmake .
make
```

Y se corre:

```bash
./bin/Concu_voley
```


### Opciones de linea de comando

```
Uso:

  Concu_voley [Opciones]

Opciones:
  -j      Cantidad de jugadores máxima para jugar en el torneo (default: 15)
  -p      Cantidad de partidos que puede jugar un jugador como máximo (default: 3)
  -f      Cantidad de filas de canchas (default: 5)
  -c      Cantidad de columnas de canchas (default: 5)

  -l      Archivo de log (default: ninguno, se escribe a stdout)
  -k      Nivel de log (default: info)

  -a      Cantidad de milisegundos que duerme la marea entre los checkeos si
          subir o no (default: 200)
  -b      Cantidad de milisegundos que duerme un partido entre los sets (default: 200)
  -e      Cantidad de milisegundos que duerme el publicador entre cada escritura
          de resultados (default: 200)
  -g      Cantidad de milisegundos que pasa entre la entrada de los jugadores
          nuevos (default: 200)

  -s      Archivo a escribir los resultados (default: /tmp/webvoley.html)
```
