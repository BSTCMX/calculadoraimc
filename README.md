# Calculadora IMC (C + WebAssembly)

Demo web de calculadora de salud nutricional (IMC) con logica en C compilada a WebAssembly, clasificacion OMS y historial en `localStorage`.

**Autor:** Jorge Leal Cornejo  
**Matricula:** ES251115052  
**Grupo:** DS-DIIS-2601-B2-002

## Demo en linea

https://bstcmx.github.io/calculadoraimc/

## Version de consola (C)

```bash
gcc src/calculadora_imc.c src/imc_core.c -o calculadora_imc -lm
./calculadora_imc
```

## Build WebAssembly (local)

Requiere [Emscripten](https://emscripten.org/):

```bash
bash scripts/build_wasm.sh
```

Abrir `web/index.html` con un servidor local:

```bash
cd web && python3 -m http.server 8080
```

## Deploy

GitHub Actions compila WASM y publica la carpeta `web/` en GitHub Pages al hacer push a `main`.

## Estructura

- `src/imc_core.c` — logica compartida de IMC
- `src/imc_wasm.c` — exports para WebAssembly
- `src/calculadora_imc.c` — programa de consola
- `web/` — interfaz web
- `scripts/build_wasm.sh` — compilacion Emscripten
