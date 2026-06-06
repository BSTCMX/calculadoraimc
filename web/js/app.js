const STORAGE_KEY = 'calculadoraimc_historial_v1';
const CATEGORIAS = ['Bajo peso', 'Peso normal', 'Sobrepeso', 'Obesidad'];

const pesoInput = document.getElementById('peso');
const estaturaInput = document.getElementById('estatura');
const form = document.getElementById('form-imc');
const estadoModulo = document.getElementById('estado-modulo');
const resultado = document.getElementById('resultado');
const historialLista = document.getElementById('historial');
const btnLimpiar = document.getElementById('btn-limpiar');

let wasmValidar;
let wasmCalcular;
let wasmCategoria;
let wasmRequiereAlerta;

function cargarHistorial() {
  try {
    const raw = localStorage.getItem(STORAGE_KEY);
    return raw ? JSON.parse(raw) : [];
  } catch {
    return [];
  }
}

function guardarHistorial(items) {
  localStorage.setItem(STORAGE_KEY, JSON.stringify(items));
}

function renderHistorial() {
  const items = cargarHistorial();
  historialLista.innerHTML = '';

  if (items.length === 0) {
    historialLista.innerHTML = '<li>Sin registros todavia.</li>';
    return;
  }

  for (const item of items) {
    const li = document.createElement('li');
    li.innerHTML = `
      <span class="fecha">${item.fecha}</span>
      Peso: ${item.peso} kg | Estatura: ${item.estatura} m |
      IMC: ${item.imc.toFixed(2)} | ${item.categoria}
      ${item.alerta ? ' | Alerta de riesgo' : ''}
    `;
    historialLista.appendChild(li);
  }
}

function mostrarResultado({ imc, categoria, alerta }) {
  resultado.classList.remove('hidden', 'alerta');
  if (!alerta) {
    resultado.classList.remove('alerta');
  }

  resultado.innerHTML = `
    <strong>IMC: ${imc.toFixed(2)}</strong>
    <div>Categoria: ${categoria}</div>
    ${
      alerta
        ? '<div class="alerta-texto">ALERTA: posible riesgo para la salud. Consulte a un profesional.</div>'
        : '<div>Resultado dentro de la categoria esperada.</div>'
    }
  `;

  if (alerta) {
    resultado.classList.add('alerta');
  }
}

async function initWasm() {
  const moduleUrl = new URL('../wasm/imc.js', import.meta.url);
  const { default: createImcModule } = await import(moduleUrl.href);
  const module = await createImcModule({
    locateFile: (path) => new URL(`../wasm/${path}`, import.meta.url).href,
  });

  wasmValidar = module.cwrap('wasm_validar', 'number', ['number', 'number']);
  wasmCalcular = module.cwrap('wasm_calcular', 'number', ['number', 'number']);
  wasmCategoria = module.cwrap('wasm_categoria', 'number', ['number']);
  wasmRequiereAlerta = module.cwrap('wasm_requiere_alerta', 'number', ['number']);

  estadoModulo.textContent = 'Modulo WebAssembly listo.';
}

form.addEventListener('submit', (event) => {
  event.preventDefault();

  const peso = Number(pesoInput.value);
  const estatura = Number(estaturaInput.value);

  if (!wasmValidar(peso, estatura)) {
    estadoModulo.textContent = 'Error: ingrese valores numericos mayores que cero.';
    return;
  }

  const imc = wasmCalcular(peso, estatura);
  const categoria = CATEGORIAS[wasmCategoria(imc)] ?? 'Desconocido';
  const alerta = wasmRequiereAlerta(imc) === 1;

  mostrarResultado({ imc, categoria, alerta });
  estadoModulo.textContent = 'Calculo realizado con logica C/WebAssembly.';

  const registro = {
    fecha: new Date().toLocaleString('es-MX'),
    peso,
    estatura,
    imc,
    categoria,
    alerta,
  };

  const historial = [registro, ...cargarHistorial()].slice(0, 20);
  guardarHistorial(historial);
  renderHistorial();
});

btnLimpiar.addEventListener('click', () => {
  localStorage.removeItem(STORAGE_KEY);
  renderHistorial();
});

renderHistorial();
initWasm().catch((error) => {
  console.error(error);
  estadoModulo.textContent = 'No se pudo cargar WebAssembly.';
});
