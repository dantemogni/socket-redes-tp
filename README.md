<p align="center">
  <img src="./.assets/unla25.jpg" alt="UNLa 25" width="15%">
</p>
<h1 align="center" font-size="3em">Redes y Comunicaciones<br>Trabajo Práctico  2022<br>Sockets</h1>
  <h4 align="center">Alumno:</h4>
<p align="center">
   • Dante Joaquin Mogni
</p>
  <h4 align="center">Equipo docente:</h4>
<p align="center">
    • Ing Diego Andrés Azcurra <br>
    • Lic. Gustavo Fernández
</p>
 <h4 align="center">Año 2022</h4>
 <h4 align="center">Universidad Nacional de Lanús</h4>
 
---
   
_Repositorio del proyecto de la cátedra de Redes y Comunicaciones de la Universidad Nacional de Lanús, año 2022._

**Tabla de contenidos:**

- [Inicio fácil](#inicio-fácil)
  - [Comandos](#comandos)
- [Enunciado](#enunciado)
  - [Proyecto](#proyecto)
  - [Req. funcionales](#req-funcionales)
    - [Servidor](#servidor)
    - [Cliente](#cliente)
    - [UI](#ui)
  - [Req. No funcionales](#req-no-funcionales)

## Inicio fácil

Para levantar rápidamente, tanto el cliente como el servidor, existe en el repositorio un archivo Makefile con algunas instrucciones:

### Comandos

|                   | Cliente                    | Servidor                   |
| ----------------- | -------------------------- | -------------------------- |
| Compilar          | `make compile-client`      | `make compile-server`      |
| Correr            | `make run-client PORT=xxx` | `make run-server PORT=xxx` |
| Compilar y correr | `make client PORT=xxx`     | `make server PORT=xxx`     |

_NOTA: El valor del puerto (PORT) es opcional. Por defecto a 8080._

Se recomienda ejecutar aquel comando para **compilar y correr** al mismo tiempo.

## Enunciado

### Proyecto

Desarrollar en lenguaje C o C++ una calculadora de números enteros positivos,
basada en dos aplicaciones que se ejecutarán en modo consola, las cuales
estarán comunicadas por sockets (una con el rol de servidor y otra con el rol de
cliente).

El cliente se conectará al servidor y enviará las operaciones a realizar. El servidor
hará el procesamiento y devolverá el resultado al cliente.

---

### Req. funcionales

#### Servidor

- Inicia y espera la conexión del cliente
- Toda la actividad relacionada con la administración de conexiones realizada por el servidor debe quedar registrada en un archivo de texto llamado server.log
- En caso de haber un cliente conectado, luego de 2 minutos sin actividad la sesión expira. El servidor lo desconecta.
- Cuando un cliente sale o su sesión expira, el servidor se queda esperando a otro.
- **Caracteres aceptados**: los caracteres aceptados dentro de una operación son números enteros positivos y operadores matemáticos:
  - Suma: +
  - Resta: -
  - Multiplicación: \*
  - División: /
  - Potenciación: ^
  - Factorial: !
- **Tipo de operaciones aceptadas:** las operaciones aceptadas por la calculadora pueden ser:
  - [operando][operación][operando]: siendo operación Suma, Resta, Multiplicación, División o Potenciación, y operando es un número entero positivo. Por ejemplo:
    - 15+50
    - 20/10
    - 4^5
  - [operando][factorial]: operando es un número entero positivo y Factorial el símbolo que lo representa !. Por ejemplo: 8!
- **Validaciones para los cálculos:**
  1. **Validación de caracteres de la operación:** el servidor debe validar que la operación recibida sea correcta, verificando que no haya ningún carácter inesperado. En caso de encontrar un carácter no contemplado, deberá informar al cliente: "No se pudo realizar la operación, se encontró un carácter no contemplado: [carácter]", donde [carácter] es el carácter que provocó el error.
  2. **Validación de operación**: en el caso que la operación esté mal formada, el servidor informará "No se pudo realizar la operación, la operación está mal formada: [abc]". Donde b es el carácter donde se detectó el error, a es el carácter anterior (si lo hubiere), y c el carácter siguiente (si lo hubiere). Una operación mal formada se da cuando faltan términos o se mezclan operaciones.
  3. **Longitud de operación:** la longitud máxima de una operación será de 20 caracteres, y la mínima será de 1 caracter. En el caso de recibir una operación fuera del rango mencionado, el servidor responderá "La operación debe tener entre 1 y 20 caracteres".

#### Cliente

- Para conectarse al servidor, primero deberá especificar la dirección IP y el puerto, una vez que el servidor acepte la conexión, el cliente dispone de las siguientes opciones:
  - Realizar cálculo
  - Ver registro de actividades
  - Cerrar sesión
- **Realizar operación**: esta opción solicita al usuario el ingreso de una operación y la envía al servidor, según las especificaciones detalladas en la sección de servidor. En caso de querer volver al menú anterior, al escribir "volver" en la operación, se mostrará el menú principal nuevamente.
- **Ver registro de actividades:** mediante esta función se solicita al servidor que transfiera al cliente el archivo de registro de actividades. Una vez recibido, se muestra por pantalla el contenido del mismo.
- **Cerrar sesión:** se desconecta del servidor.

#### UI

- Utilizar menús para simplificar la selección de las diferentes opciones
- La presentación de los datos debe ser clara (borrando la pantalla cuando
  corresponda, presentando páginas si las opciones son demasiadas, etc.).

---

### Req. No funcionales

- Lenguaje de programación C/C++.
- Entorno de desarrollo a elección.
- Sistema operativo Linux o Windows, a elección.
