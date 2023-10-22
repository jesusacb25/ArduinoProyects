#ifndef DATA_H
#define DATA_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <title>Lampara</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <!-- <link rel="stylesheet" type="text/css" media="screen" href="main.css" /> -->
    <style>
      * {
        padding: 0;
        margin: 0;
      }

      .main {
        height: 100vh;
        background-color: #000;
        overflow: hidden;
        display: flex;
      }

      .container {
        position: relative;
        width: 80%;
      }

      .image1 {
        margin: auto;
        position: absolute;
        top: 50%; /* Centra verticalmente */
        left: 50%; /* Centra horizontalmente */
        transform: translate(-50%, -50%);
        z-index: 1;
        height: 100%;
        width: 100%;
      }

      .image2 {
        margin: auto;
        position: absolute;
        top: 60%; /* Centra verticalmente */
        left: 45%; /* Centra horizontalmente */
        transform: translate(-50%, -50%);
        z-index: 2;
        height: 674px;
        width: 502px;
        opacity: 0;
      }

      .dial {
        position: absolute;
        bottom: 20px; /* Ajusta la distancia desde abajo según tus preferencias */
        right: 20px; /* Ajusta la distancia desde la derecha según tus preferencias */
        width: 200px;
        height: 200px;
        background-color: lightgray;
        border-radius: 50%;
        transform: rotate(270deg); /* Inicia la flecha apuntando a las nueve */
        z-index: 3;
        margin-right: 30px;
        margin-bottom: 30px;
      }

      .arrow {
        width: 20px;
        height: 100px;
        background-color: red;
        position: absolute;
        bottom: 100px;
        left: 90px;
        transform-origin: 50% 100%;
        transform: rotate(0deg);
        transition: transform 0.1s;
        cursor: pointer;
      }
    </style>
  </head>
  <body>
    <div class="main">
      <div class="container">
        <img
          src="https://github.com/jesusacb25/PAGINA_WEB/blob/main/img/screen.png"
          alt="Rading Book"
          class="image1"
        />
        <img
          src="https://github.com/jesusacb25/PAGINA_WEB/blob/main/img/screen.png"
          alt="luz de lampara"
          class="image2"
        />
      </div>
      <div class="dial" id="dial">
        <div class="arrow" id="arrow"></div>
      </div>
      <script>
  const dial = document.getElementById("dial");
  const arrow = document.getElementById("arrow");
  const image2 = document.querySelector(".image2");

  function updateDialRotation(potenciometroValue) {
    const minPotenciometro = 0;
    const maxPotenciometro = 4095;
    const minAngle = -135; // Ángulo mínimo para el dial
    const maxAngle = 135; // Ángulo máximo para el dial
    const angleRange = maxAngle - minAngle;

    // Calcula el ángulo basado en el valor de potenciometro
    const angle = ((potenciometroValue - minPotenciometro) / (maxPotenciometro - minPotenciometro)) * angleRange + minAngle;

    arrow.style.transform = `rotate(${angle}deg)`;
  }

  function updateImageOpacity(fotoceldaValue, potenciometroValue) {
    const maxOpacity = 1;
    const fotoceldaOpacity = fotoceldaValue / 4095;
    const potenciometroOpacity = potenciometroValue / 4095;
    
    // Combina la opacidad de fotocelda y potenciometro
    const totalOpacity = (fotoceldaOpacity + potenciometroOpacity) / 2;
    
    image2.style.opacity = totalOpacity;
  }

  function updateValues() {
    fetch("/values")
      .then(response => response.json())
      .then(data => {
        console.log("Fotocelda: " + data.fotocelda);
        console.log("Potenciometro: " + data.potenciometro);
        updateDialRotation(data.potenciometro);
        updateImageOpacity(data.fotocelda, data.potenciometro);
      });
  }

  setInterval(updateValues, 500);
</script>


    </div>
  </body>
</html>


)rawliteral";

#endif
