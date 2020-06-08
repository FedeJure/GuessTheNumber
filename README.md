

<center>
<div style="align: right"><img style="position:absolute" src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/0d/FIUBA_gris_transparente.png/275px-FIUBA_gris_transparente.png"></div>

<br></br>
<br></br>


# <center>Trabajo práctico 3 - Adivina el número</center>
### <center>Taller de programación 1 - Veiga - 1er Cuatrimestre 2020

<br></br>

| | |
|---|---|
|  Alumno | Federico Jure  |
| Padrón  |  97598 |
| Email   | fedejure@gmail.com |
## [<center>Repositorio fuente](https://github.com/FedeJure/GuessTheNumber)


<br></br>
</center>
----------------------------------

## Descripción del trabajo realizado

El presente trabajo se realizo en C++11 utilizando unicamente librerias estandar.
El programa representa un juego cliente-servidor el cual el cliente tiene que adivinar 
un numero de 3 cifras sin repetidos, provisto por el servidor. A medida que el cliente 
usa sus 10 chances para adivinarlo, el servidor le envia un resultado parcial de esos intentos 
asi el cliente puede ir ajustando sus proximos numeros.



-----------------------------------

## Modelo de dominio: <br/>
### Cliente:
__client__: Es la clase principal del cliente el cual conoce al socket conectado al servidor y los comandos que puede procesar.<br/>
__clientArgumentHandler__: Tiene la responsabilidad de handlear el input del usuario<br/>
__clientCommandProcessor__: Procesa un comando ingresado por el usuario<br/>  

### Server:
__server__: Es la clase principal del servidor. Tiene la referencia al socket, a las conexiónes de cada cliente conectado, los comandos disponibles para procesar. Se encarga de delegar el funcionamiento del servidor a las distintas clases.<br/>
__serverFileReader__: Tiene la responsabilidad de leer del archivo de numeros provisto al iniciar la ejecucion y devolver un numero diferente cada vez que se lo solicite para cada cliente.<br/>
__serverArgumentHandler__: Handlea el input del usuario al iniciar la ejecucion del programa<br/> 
__serverClientConnection__: Representa una conexión con un cliente especifico el cual tiene la referencia al socket para esa conexion.<br/>
__serverCommandProcessor__: Procesa un comando ingresado por un cliente. <br/>

### Common:
__commonUtils__: Utilidades para conversion entre tipos numericos y buffer para enviar por la conexión<br/>
__commonSocket__: Socket utilizado tanto por cliente y servidor.<br/>

---------------