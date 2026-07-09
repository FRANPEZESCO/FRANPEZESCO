# EXP-01 — Estar en la cárcel
## El libre albedrío suspendido
# EXP-01 — Estar en la cárcel · Being in Prison · Essere in Prigione
## El libre albedrío suspendido · The suspended free will · Il libero arbitrio sospeso

<div align="center">

[🏠 ES: Índice](../README.md) &nbsp;|&nbsp; [🏠 EN: Index](../README_EN.md) &nbsp;|&nbsp; [🏠 IT: Indice](../README_IT.md)

[⬅️ Inicio / Start / Inizio](../README.md) &nbsp;&nbsp;&nbsp; **EXP-01** &nbsp;&nbsp;&nbsp; [EXP-02 ➡️](../EXP-02/EXP-02.md)

</div>

---

<!-- SELECTOR DE IDIOMA / LANGUAGE SELECTOR / SELETTORE LINGUA -->
<div align="center">

🇪🇸 [Español](#-español) &nbsp;|&nbsp; 🇬🇧 [English](#-english) &nbsp;|&nbsp; 🇮🇹 [Italiano](#-italiano)

</div>

---

## 🖼️ Imágenes del experimento · Experiment Images · Immagini dell'esperimento

<div align="center">

<table>
<tr>
<td align="center" width="50%">

<img src="./img/EXP-01_circuito.jpeg" alt="Circuito EXP-01 montado — Servo + Potenciómetro + Arduino Mega" width="100%"/>

**🔌 Circuito montado · Circuit · Circuito**
*Servo SG90 · Potenciómetro 10kΩ · Arduino Mega 2560*

</td>
<td align="center" width="50%">

<img src="./img/EXP-01_monitor.jpg" alt="Monitor serie EXP-01 — salida JSON en tiempo real" width="100%"/>

**📺 Salida en tiempo real · Live output · Output in tempo reale**
*Monitor serie — JSON: estado, voluntad, tiempo*

</td>
</tr>
</table>

> 💡 **ES:** Para actualizar las imágenes, reemplaza los archivos en `./img/`
> 💡 **EN:** To update images, replace files in `./img/`
> 💡 **IT:** Per aggiornare le immagini, sostituisci i file in `./img/`

</div>

---

## 🇪🇸 Español

### El experimento

Un **servo motor** representa la posición del sistema — puede moverse de 0° a 180°.
Un **potenciómetro** representa la voluntad: cada giro calcula un ángulo que se
envía al servo.

En **MODO LIBRE**, el servo sigue la voluntad en tiempo real. El LED verde está encendido.

Cuando el **botón** activa el **MODO CÁRCEL**, el servo se congela exactamente
en la posición en que estaba. La voluntad sigue calculando ángulos — el monitor serie
los muestra — pero el servo no responde. El LED rojo se enciende. El contador
`tiempo_carcel` sube segundo a segundo, documentando cuánto tiempo el sistema
lleva en ese estado.

En esta versión **sin salida**, no hay ningún mecanismo que libere automáticamente
al servo. El botón puede desactivar el bloqueo, pero el experimento lo documenta
como reversión manual, no como resolución.

### Cómo funciona el código — sin tecnicismos

```cpp
// La voluntad existe — pero el sistema la ignora cuando está bloqueado
int voluntad = map(analogRead(PIN_POT), 0, 1023, 0, 180);

if (!bloqueado) {
  servo.write(voluntad);        // LIBRE: el servo obedece
} else {
  servo.write(posicionActual);  // CÁRCEL: el servo ignora la voluntad
  tiempo_carcel++;              // El contador sube sin importar cuánto empuje la voluntad
}
```

**`bloqueado`** — verdadero/falso. Cuando es verdadero, `servo.write(posicionActual)`
escribe siempre el mismo ángulo. La voluntad genera el número correcto,
pero ninguna línea del código lo usa para mover el servo.

**`tiempo_carcel`** — sube en cada ciclo mientras `bloqueado` es verdadero.
No importa si la voluntad está al mínimo o al máximo — el contador sube igual.

### El caso de vida real

Una persona en una situación que no puede cambiar de inmediato — un contrato,
una situación legal, una circunstancia familiar — siente exactamente lo que el servo
en modo cárcel: la voluntad existe y funciona perfectamente, pero el contexto
no la deja actuar.

Lo que el experimento hace visible es que **el bloqueo no destruye la voluntad**.
Lo que el código documenta, con `tiempo_carcel`, es cuántos segundos pasaron
con la voluntad activa pero sin efecto sobre la posición real del sistema.

---

## 🇬🇧 English

### The experiment

A **servo motor** represents the system's position — it can move from 0° to 180°.
A **potentiometer** represents the will: each turn calculates an angle sent to the servo.

In **FREE MODE**, the servo follows the will in real time. The green LED is on.

When the **button** activates **PRISON MODE**, the servo freezes exactly at its
current position. The will keeps calculating angles — the serial monitor shows them —
but the servo doesn't respond. The red LED turns on. The `prison_time` counter
increases every second, documenting how long the system has been in that state.

In this **no-exit version**, there is no mechanism that automatically releases
the servo. The button can deactivate the lock, but the experiment documents it
as a manual reversion, not a resolution.

### How the code works — without technical jargon

```cpp
// The will exists — but the system ignores it when locked
int will = map(analogRead(PIN_POT), 0, 1023, 0, 180);

if (!locked) {
  servo.write(will);           // FREE: servo obeys
} else {
  servo.write(currentPos);     // PRISON: servo ignores the will
  prison_time++;               // Counter rises no matter how hard the will pushes
}
```

**`locked`** — true/false. When true, `servo.write(currentPos)` always writes
the same angle. The will generates the correct number, but no line of code
uses it to move the servo.

**`prison_time`** — increases each cycle while `locked` is true. It doesn't matter
if the will is at minimum or maximum — the counter rises the same.

### The real-life case

A person in a situation they cannot change immediately — a contract, a legal situation,
a family circumstance — feels exactly what the servo in prison mode feels:
the will exists and works perfectly, but the context won't let it act.

What the experiment makes visible is that **the block does not destroy the will**.
What the code documents, with `prison_time`, is how many seconds passed
with the will active but with no effect on the system's actual position.

---

## 🇮🇹 Italiano

### L'esperimento

Un **servo motore** rappresenta la posizione del sistema — può muoversi da 0° a 180°.
Un **potenziometro** rappresenta la volontà: ogni rotazione calcola un angolo
inviato al servo.

In **MODALITÀ LIBERA**, il servo segue la volontà in tempo reale. Il LED verde è acceso.

Quando il **pulsante** attiva la **MODALITÀ PRIGIONE**, il servo si congela esattamente
nella posizione in cui si trovava. La volontà continua a calcolare angoli — il monitor
seriale li mostra — ma il servo non risponde. Il LED rosso si accende. Il contatore
`tempo_prigione` aumenta ogni secondo, documentando quanto tempo il sistema
è rimasto in quello stato.

In questa versione **senza uscita**, non esiste alcun meccanismo che liberi
automaticamente il servo. Il pulsante può disattivare il blocco, ma l'esperimento
lo documenta come reversione manuale, non come risoluzione.

### Come funziona il codice — senza tecnicismi

```cpp
// La volontà esiste — ma il sistema la ignora quando è bloccato
int volonta = map(analogRead(PIN_POT), 0, 1023, 0, 180);

if (!bloccato) {
  servo.write(volonta);        // LIBERO: il servo obbedisce
} else {
  servo.write(posizioneAttu);  // PRIGIONE: il servo ignora la volontà
  tempo_prigione++;            // Il contatore sale indipendentemente dalla volontà
}
```

**`bloccato`** — vero/falso. Quando è vero, `servo.write(posizioneAttuale)` scrive
sempre lo stesso angolo. La volontà genera il numero corretto, ma nessuna riga
di codice lo usa per muovere il servo.

**`tempo_prigione`** — aumenta ogni ciclo mentre `bloccato` è vero.
Non importa se la volontà è al minimo o al massimo — il contatore sale lo stesso.

### Il caso nella vita reale

Una persona in una situazione che non può cambiare immediatamente — un contratto,
una situazione legale, una circostanza familiare — sente esattamente ciò che sente
il servo in modalità prigione: la volontà esiste e funziona perfettamente,
ma il contesto non le permette di agire.

Ciò che l'esperimento rende visibile è che **il blocco non distrugge la volontà**.
Ciò che il codice documenta, con `tempo_prigione`, è quanti secondi sono passati
con la volontà attiva ma senza effetto sulla posizione reale del sistema.

---

## 🔧 Hardware · ES/EN/IT

| Componente | Qty | Función / Function / Funzione |
|------------|-----|-------------------------------|
| Arduino Mega 2560 | 1 | Controlador / Controller / Controllore |
| Servo motor SG90 | 1 | Acción posible / Possible action / Azione possibile |
| Potenciómetro 10kΩ | 1 | La voluntad / The will / La volontà |
| Botón pulsador / Push button / Pulsante | 1 | Activa bloqueo / Activates lock / Attiva blocco |
| LED verde / Green LED / LED verde | 1 | Modo libre / Free mode / Modalità libera |
| LED rojo / Red LED / LED rosso | 1 | Modo cárcel / Prison mode / Modalità prigione |
| Resistencias 220Ω / Resistors / Resistenze | 2 | Una por LED / One per LED / Uno per LED |
| Cables jumper / Jumper wires / Cavi jumper | varios | Conexiones / Connections / Connessioni |
| Protoboard | 1 | Montaje / Assembly / Montaggio |

---

## 📁 Archivos de este experimento · Files · File

| Archivo / File | Descripción / Description / Descrizione | Enlace / Link |
|----------------|----------------------------------------|---------------|
| `EXP-01_Estar_en_la_carcel.ino` | Código Arduino completo / Complete Arduino code / Codice Arduino completo | [📥 Descargar](./EXP-01_Estar_en_la_carcel.ino) |
| `EXP-01_circuito.jpeg` | Foto del circuito montado / Circuit photo / Foto del circuito | [🖼️ Ver](./img/EXP-01_circuito.jpeg) |
| `EXP-01_monitor.jpg` | Captura del monitor serie / Serial monitor capture / Cattura monitor seriale | [🖼️ Ver](./img/EXP-01_monitor.jpg) |
| `EXP-01_esquema.pdf` | Esquema de conexiones / Wiring diagram / Schema connessioni | [📄 Abrir](./EXP-01_esquema.pdf) |

---

## 💬 Comentarios · Comments · Commenti

¿Te identificaste con este experimento? / Did you identify with this experiment? / Ti sei identificato con questo esperimento?

Abre un **[💬 Issue aquí](https://github.com/FRANPEZASCO/FRANPEZESCO/issues/new?title=[EXP-01]+Tu+experiencia&labels=experiencia-personal)**
con el título `[EXP-01] Tu experiencia / Your experience / La tua esperienza`

---

<div align="center">

[⬅️ Inicio / Start / Inizio](../README.md) &nbsp;&nbsp;&nbsp; **EXP-01** &nbsp;&nbsp;&nbsp; [EXP-02 ➡️](../EXP-02/EXP-02.md)

[🏠 ES: Índice](../README.md) &nbsp;|&nbsp; [🏠 EN: Index](../README_EN.md) &nbsp;|&nbsp; [🏠 IT: Indice](../README_IT.md)

---

*🇪🇸 "El libre albedrío no desaparece en la cárcel. Solo no puede actuar."*
*🇬🇧 "Free will does not disappear in prison. It simply cannot act."*
*🇮🇹 "Il libero arbitrio non scompare in prigione. Semplicemente non può agire."*

**— I.F.P.E · Dr. Ittalo Francisco Pezzotti Escobar**

</div>
