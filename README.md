Sistema de Iluminación Multi-modo

Este es uno de mis primeros proyectos aplicando lo aprendido hasta el momento de filtros RC y debounce por software. La idea inicial fue crearle diferentes modos para poder medir y ver como a traves del filtro se atenúa el ruido

Modos de Operación:
1) **Modo Manual:** Control directo del brillo mediante un potenciómetro. 
2) **Modo Automático:** La intensidad se regula sola según la luz del ambiente (LDR). Tiene una función de calibración en tiempo real para adaptar el sensor a diferentes condiciones de luz.
3) **Modo Progresivo:** Una variación del manual donde el brillo no cambia bruscamente, sino que busca la posición del potenciómetro haciendo una transición suave.

### Cosas que aprendí haciendo este código:
* **Evitar rebotes (Debounce):** Implementación tanto por hardware como por software, analizando el comportamiento de los botones en cada caso.
* **Multitarea básica:** Uso de la función `millis()` para evitar detener el procesador, permitiendo que el sistema lea el potenciómetro mientras realiza transiciones de brillo.
* **Manejo de señales:** Mapeo de valores de sensores analógicos para controlar la potencia de un LED mediante PWM.
* **Calibración:** Uso de `constrain()` para manejar rangos de la fotorresistencia y asegurar un funcionamiento estable ante diferentes condiciones de luz.

### Conexiones (Hardware)
* **Placa:** Arduino Uno.
* **Entradas:** Potenciómetro, Fotorresistencia (LDR) y dos pulsadores.
* **Salida:** Un LED común con su resistencia

### Tecnologías utilizadas:
* Arduino IDE / PlatformIO
* C++ (Sistemas Embebidos)
* Tinkercad (Simulación)

![Esquema del circuito](img/circuito.png)
![Foto del circuito real](img/circuito_fisico.jpg)