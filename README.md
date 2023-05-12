# TrivialLike
###### Laboratórios de Informática II

### Features

* Movimento do jogador
* Outros ainda em desenvolvimento :)

### Controlos ⌨️ (Apenas Teclado)

* **Setas** - Mover o jogador
* **q** - Para sair / voltar

## Código

O código está organizado em módulos.

O programa começa em `src/main.c` que cria a janela do ncurses e o estado do jogo (disponível em `src/state.c`). Depois dentro do loop da função main a cada iteração é verificado qual é a scene atual e chamadas as respetivas funções de renderização (desenha*.c) e de controlo de eventos (eventos*.c).

Cada scene tem a sua pasta dentro de `src/Scenes/` com 2 ficheiros (mais os respetivos headers), responsáveis pelas respetivas funções de renderização e controlo de eventos, com nome igual ao ficheiro.

## Contribuir

### Repositório

Para clonar o repositório usa um dos seguintes comandos

```bash
# Por HTTPS
$ git clone https://github.com/Darguima/triviallike.git
$ cd triviallike

# Por SSH
$ git clone git@github.com:Darguima/triviallike.git
$ cd triviallike
```

### Dependências

#### Debian / Ubuntu / Mint

Para instalar o `ncurses` (libncurses-dev) ,o `gcc` (build-essential) em derivados Debian.

```bash
$ sudo apt-get install libncurses-dev build-essential
```
Para instalar o `json-c` (libjson-c-dev)

```bash
$ sudo apt install libjson-c-dev
```

---

### Compilar

Para compilar, limpar os objetos e executar.

```bash
$ make dev
```

Para apenas compilar o código:

```bash
$ make
```

Para apenas remover todos os ficheiros de código objeto:

```bash
$ make clean
```

Será gerado um executável `triviallike` que pode ser executado isoladamente.

```bash
# No Linux
$ ./triviallike
```

Agora podes enviar para qualquer lado o executável, sem necessidade de teres o `gcc` e o código em outros computadores.

## Realizado por

- **a104537** Afonso Pedreira ;
- **A104344** Dário Guimarães ;
- **a104534** Hugo Rauber ;
- **a104523** Rodrigo Macedo ;
