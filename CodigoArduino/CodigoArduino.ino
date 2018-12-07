/*
 * Name: Cubo LED RGB
 * Description: Cubo LED RGB para Diseño Digital - Universidad Francisco de Paula Santander | Diciembre 2018 (2018-2)
 * Author: José Daniel Durán
 * Author URI: https://superjd10.com
 * GitHub Repo: https://github.com/Superjd10/CuboLEDRGB
 * Presentado por:
 * - 1161268 - Dallan Caceres
 * - 1161269 - Felipe Rivera
 * - 1161381 - Jose Daniel Duran
 */

/*
 * Comenzamos incluyendo las librerías e inicializando el serial
 */
#include <SoftwareSerial.h>
SoftwareSerial BTserial(11, 10); // RX | TX

/*
 * Declaracion de variables globales
 */

const byte maximoCaracteres = 20; // No recibir más de 20 caracteres del módulo Bluetooth
char caracteresRecibidos[maximoCaracteres]; // Lector de caracteres
boolean nuevosDatos = false; // Sólo ejecutaremos la lectura de nuevos datos si es 'true'

// Declaracion de pines

/*
 * Pines en orden:
 *     COLORES   {1B, 4B, 1R, 1G, 4R, 2B, 2G, 5B, 3B, 2R, 3R, 3G, 6R, 5R, 6G, 6B, 5G, 4G, 9R, 9G, 8R, 9B, 8B, 8G, 7G, 7R, 7B}
 * int Pines[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48};

*/
// Colores =  {1R, 1G, 1B, 2R, 2G, 2B, 3R, 3G, 3B, 4R, 4G, 4B, 5R, 5G, 5B, 6R, 6G, 6B, 7R, 7G, 7B, 8R, 8G, 8B, 9R, 9G, 9B}
int Pines[] = {24, 25, 22, 31, 28, 27, 32, 33, 30, 26, 39, 23, 35, 38, 29, 34, 36, 37, 47, 46, 48, 42, 45, 44, 40, 41, 43};

int Pines_total = 27;

int Row_C[] = {4, 3, 2};
int Row_C_l = 3;

int duracionTotalSecuencia_1 = 0;

int Personalizada_R = 0;
int Personalizada_G = 0;
int Personalizada_B = 0;
int Personalizada_Comun_Pin = 0;
int Personalizada_Comun_Estado = 1;


/*
 * Dejamos hechas las secuencias de los LEDs
 */

void forFading_ON( float tiempoDelay ){
  for(int duracionEncendido = 255; duracionEncendido >  0; duracionEncendido--) {
    analogWrite(Row_C[0], duracionEncendido);
    analogWrite(Row_C[1], duracionEncendido);
    analogWrite(Row_C[2], duracionEncendido);
    delay( tiempoDelay );
  }
}
void forFading_OFF( float tiempoDelay ){
  for(int duracionApagado = 0; duracionApagado < 255; duracionApagado++) {
    analogWrite(Row_C[0], duracionApagado);
    analogWrite(Row_C[1], duracionApagado);
    analogWrite(Row_C[2], duracionApagado);
    delay( tiempoDelay );
  }
}

void EjecutarSecuencias_S1() {
  int Secuencia1_Velocidades[] = {300, 250, 200, 150, 100, 100, 100, 100, 50, 50, 50, 50, 100, 100, 100, 100, 150, 200, 250, 300};
  /*
   * int Secuencia1_Conteo_1 = 0;
   * int Secuencia1_Conteo_2 = 1;
   * int Secuencia1_Conteo_3 = 2;
   */
  int Secuencia1_Conteo[] = {0, 1, 2};
  
  if(duracionTotalSecuencia_1 < 1) {

    for(int Secuencia1_AumentarVelocidades = 0; Secuencia1_AumentarVelocidades < 20; Secuencia1_AumentarVelocidades++) {
        for(int Secuencia1_Conteo_LED = 0; Secuencia1_Conteo_LED < 3; Secuencia1_Conteo_LED++){
            while(Secuencia1_Conteo[Secuencia1_Conteo_LED] < 27) {
                digitalWrite(Pines[Secuencia1_Conteo[Secuencia1_Conteo_LED]], HIGH);
                Secuencia1_Conteo[Secuencia1_Conteo_LED] = Secuencia1_Conteo[Secuencia1_Conteo_LED] + 3;
            }
            forFading_ON(0.5);
            delay(Secuencia1_Velocidades[Secuencia1_AumentarVelocidades]);
            forFading_OFF(0.5);
            while(Secuencia1_Conteo[Secuencia1_Conteo_LED] > 0) {
                Secuencia1_Conteo[Secuencia1_Conteo_LED] = Secuencia1_Conteo[Secuencia1_Conteo_LED] - 3;
                digitalWrite(Pines[Secuencia1_Conteo[Secuencia1_Conteo_LED]], LOW);
            }
        }
    }  

    duracionTotalSecuencia_1++;
}
  
}

void EjecutarSecuencias_S2() {
    int Secuencia2_Conteo[] = {0, 1, 2};
    for(int Secuencia2_Conteo_LED_Bajada = 0; Secuencia2_Conteo_LED_Bajada < 3; Secuencia2_Conteo_LED_Bajada++){
        while(Secuencia2_Conteo[Secuencia2_Conteo_LED_Bajada] < 27) {
            digitalWrite(Pines[Secuencia2_Conteo[Secuencia2_Conteo_LED_Bajada]], HIGH);
            Secuencia2_Conteo[Secuencia2_Conteo_LED_Bajada] = Secuencia2_Conteo[Secuencia2_Conteo_LED_Bajada] + 3;
        }
        digitalWrite(Row_C[0], LOW);
        delay(500);
        digitalWrite(Row_C[0], HIGH);
        digitalWrite(Row_C[1], LOW);
        delay(500);
        digitalWrite(Row_C[1], HIGH);
        digitalWrite(Row_C[2], LOW);
        delay(500);
        digitalWrite(Row_C[2], HIGH);
        while(Secuencia2_Conteo[Secuencia2_Conteo_LED_Bajada] > 0) {
            Secuencia2_Conteo[Secuencia2_Conteo_LED_Bajada] = Secuencia2_Conteo[Secuencia2_Conteo_LED_Bajada] - 3;
            digitalWrite(Pines[Secuencia2_Conteo[Secuencia2_Conteo_LED_Bajada]], LOW);
        }
    }
    for(int Secuencia2_Conteo_LED_Subida = 2; Secuencia2_Conteo_LED_Subida >= 0; Secuencia2_Conteo_LED_Subida--){
        while(Secuencia2_Conteo[Secuencia2_Conteo_LED_Subida] < 27) {
            digitalWrite(Pines[Secuencia2_Conteo[Secuencia2_Conteo_LED_Subida]], HIGH);
            Secuencia2_Conteo[Secuencia2_Conteo_LED_Subida] = Secuencia2_Conteo[Secuencia2_Conteo_LED_Subida] + 3;
        }
        digitalWrite(Row_C[2], LOW);
        delay(500);
        digitalWrite(Row_C[2], HIGH);
        digitalWrite(Row_C[1], LOW);
        delay(500);
        digitalWrite(Row_C[1], HIGH);
        digitalWrite(Row_C[0], LOW);
        delay(500);
        digitalWrite(Row_C[0], HIGH);
        while(Secuencia2_Conteo[Secuencia2_Conteo_LED_Subida] > 0) {
            Secuencia2_Conteo[Secuencia2_Conteo_LED_Subida] = Secuencia2_Conteo[Secuencia2_Conteo_LED_Subida] - 3;
            digitalWrite(Pines[Secuencia2_Conteo[Secuencia2_Conteo_LED_Subida]], LOW);
        }
    }
}

void EjecutarSecuencias_S3() {
  
  int Secuencia3_Conteo_1[] = {0, 3, 6};
  int Secuencia3_Conteo_2[] = {1, 4, 7};
  int Secuencia3_Conteo_3[] = {2, 5, 8};

  for(int Secuencia3_Conteo_LED = 0; Secuencia3_Conteo_LED < 3; Secuencia3_Conteo_LED++){
    while(Secuencia3_Conteo_1[Secuencia3_Conteo_LED] < 27) {
      digitalWrite(Pines[Secuencia3_Conteo_1[Secuencia3_Conteo_LED]], HIGH);
      Secuencia3_Conteo_1[Secuencia3_Conteo_LED] = Secuencia3_Conteo_1[Secuencia3_Conteo_LED] + 9;
    }
    forFading_ON(0.5);
    delay(300);
    forFading_OFF(0.5);
    while(Secuencia3_Conteo_1[Secuencia3_Conteo_LED] > 0) {
      Secuencia3_Conteo_1[Secuencia3_Conteo_LED] = Secuencia3_Conteo_1[Secuencia3_Conteo_LED] - 9;
      digitalWrite(Pines[Secuencia3_Conteo_1[Secuencia3_Conteo_LED]], LOW);
    }
  }
  for(int Secuencia3_Conteo_LED = 0; Secuencia3_Conteo_LED < 3; Secuencia3_Conteo_LED++){
    while(Secuencia3_Conteo_2[Secuencia3_Conteo_LED] < 27) {
      digitalWrite(Pines[Secuencia3_Conteo_2[Secuencia3_Conteo_LED]], HIGH);
      Secuencia3_Conteo_2[Secuencia3_Conteo_LED] = Secuencia3_Conteo_2[Secuencia3_Conteo_LED] + 9;
    }
    forFading_ON(0.5);
    delay(300);
    forFading_OFF(0.5);
    while(Secuencia3_Conteo_2[Secuencia3_Conteo_LED] > 0) {
      Secuencia3_Conteo_2[Secuencia3_Conteo_LED] = Secuencia3_Conteo_2[Secuencia3_Conteo_LED] - 9;
      digitalWrite(Pines[Secuencia3_Conteo_2[Secuencia3_Conteo_LED]], LOW);
    }
  }
  for(int Secuencia3_Conteo_LED = 0; Secuencia3_Conteo_LED < 3; Secuencia3_Conteo_LED++){
    while(Secuencia3_Conteo_3[Secuencia3_Conteo_LED] < 27) {
      digitalWrite(Pines[Secuencia3_Conteo_3[Secuencia3_Conteo_LED]], HIGH);
      Secuencia3_Conteo_3[Secuencia3_Conteo_LED] = Secuencia3_Conteo_3[Secuencia3_Conteo_LED] + 9;
    }
    forFading_ON(0.5);
    delay(300);
    forFading_OFF(0.5);
    while(Secuencia3_Conteo_3[Secuencia3_Conteo_LED] > 0) {
      Secuencia3_Conteo_3[Secuencia3_Conteo_LED] = Secuencia3_Conteo_3[Secuencia3_Conteo_LED] - 9;
      digitalWrite(Pines[Secuencia3_Conteo_3[Secuencia3_Conteo_LED]], LOW);
    }
  }


  for(int Secuencia3_Conteo_LED = 2; Secuencia3_Conteo_LED >= 0; Secuencia3_Conteo_LED--){
    while(Secuencia3_Conteo_1[Secuencia3_Conteo_LED] < 27) {
      digitalWrite(Pines[Secuencia3_Conteo_1[Secuencia3_Conteo_LED]], HIGH);
      Secuencia3_Conteo_1[Secuencia3_Conteo_LED] = Secuencia3_Conteo_1[Secuencia3_Conteo_LED] + 9;
    }
    forFading_ON(0.5);
    delay(300);
    forFading_OFF(0.5);
    while(Secuencia3_Conteo_1[Secuencia3_Conteo_LED] > 0) {
      Secuencia3_Conteo_1[Secuencia3_Conteo_LED] = Secuencia3_Conteo_1[Secuencia3_Conteo_LED] - 9;
      digitalWrite(Pines[Secuencia3_Conteo_1[Secuencia3_Conteo_LED]], LOW);
    }
  }
  for(int Secuencia3_Conteo_LED = 2; Secuencia3_Conteo_LED >= 0; Secuencia3_Conteo_LED--){
    while(Secuencia3_Conteo_2[Secuencia3_Conteo_LED] < 27) {
      digitalWrite(Pines[Secuencia3_Conteo_2[Secuencia3_Conteo_LED]], HIGH);
      Secuencia3_Conteo_2[Secuencia3_Conteo_LED] = Secuencia3_Conteo_2[Secuencia3_Conteo_LED] + 9;
    }
    forFading_ON(0.5);
    delay(300);
    forFading_OFF(0.5);
    while(Secuencia3_Conteo_2[Secuencia3_Conteo_LED] > 0) {
      Secuencia3_Conteo_2[Secuencia3_Conteo_LED] = Secuencia3_Conteo_2[Secuencia3_Conteo_LED] - 9;
      digitalWrite(Pines[Secuencia3_Conteo_2[Secuencia3_Conteo_LED]], LOW);
    }
  }
  for(int Secuencia3_Conteo_LED = 2; Secuencia3_Conteo_LED >= 0; Secuencia3_Conteo_LED--){
    while(Secuencia3_Conteo_3[Secuencia3_Conteo_LED] < 27) {
      digitalWrite(Pines[Secuencia3_Conteo_3[Secuencia3_Conteo_LED]], HIGH);
      Secuencia3_Conteo_3[Secuencia3_Conteo_LED] = Secuencia3_Conteo_3[Secuencia3_Conteo_LED] + 9;
    }
    forFading_ON(0.5);
    delay(300);
    forFading_OFF(0.5);
    while(Secuencia3_Conteo_3[Secuencia3_Conteo_LED] > 0) {
      Secuencia3_Conteo_3[Secuencia3_Conteo_LED] = Secuencia3_Conteo_3[Secuencia3_Conteo_LED] - 9;
      digitalWrite(Pines[Secuencia3_Conteo_3[Secuencia3_Conteo_LED]], LOW);
    }
  }
  
}

void EjecutarSecuencias_S4() {
  int Secuencia4_tiempoDelay = 350;
  int Secuencia4_For_1, Secuencia4_For_2, Secuencia4_For_3;
  for( int Row_Activo = 0; Row_Activo < 3; Row_Activo++) {
    digitalWrite(Row_C[Row_Activo], LOW);
  }
  // Prendemos el centro de rojo
  
  digitalWrite(Pines[12], HIGH);

  // Mantenemos los extremos apagados

  digitalWrite(Pines[0], LOW);
  digitalWrite(Pines[6], LOW);
  digitalWrite(Pines[18], LOW);
  digitalWrite(Pines[24], LOW);
  digitalWrite(Pines[1], LOW);
  digitalWrite(Pines[7], LOW);
  digitalWrite(Pines[19], LOW);
  digitalWrite(Pines[25], LOW);
  digitalWrite(Pines[2], LOW);
  digitalWrite(Pines[8], LOW);
  digitalWrite(Pines[20], LOW);
  digitalWrite(Pines[26], LOW);
  
  delay(Secuencia4_tiempoDelay);

  // Apagamos del centro el rojo y prendemos el verde
  
  digitalWrite(Pines[12], LOW);
  
  digitalWrite(Pines[13], HIGH);

  // Prendemos los adyacentes al centro de rojo
  
  digitalWrite(Pines[3], HIGH); 
  digitalWrite(Pines[9], HIGH);
  digitalWrite(Pines[15], HIGH);
  digitalWrite(Pines[21], HIGH);
  
  delay(Secuencia4_tiempoDelay);

  // Apagamos del centro el verde y prendemos el azul

  digitalWrite(Pines[13], LOW);

  digitalWrite(Pines[14], HIGH);

  // Apagamos de los adyacentes al centro el rojo

  digitalWrite(Pines[3], LOW);
  digitalWrite(Pines[9], LOW);
  digitalWrite(Pines[15], LOW);
  digitalWrite(Pines[21], LOW);

  // Prendemos los adyacentes al centro de verde

  digitalWrite(Pines[4], HIGH);
  digitalWrite(Pines[10], HIGH);
  digitalWrite(Pines[16], HIGH);
  digitalWrite(Pines[22], HIGH);

  // Prendemos los extremos de rojo
  
  digitalWrite(Pines[0], HIGH);
  digitalWrite(Pines[6], HIGH);
  digitalWrite(Pines[18], HIGH);
  digitalWrite(Pines[24], HIGH);

  delay(Secuencia4_tiempoDelay);

  // Apagamos en el centro el azul y prendemos en el centro el Amarillo (rojo + verde)

  digitalWrite(Pines[14], LOW);
  
  digitalWrite(Pines[12], HIGH);
  digitalWrite(Pines[13], HIGH);

  // Apagamos los adyacentes al centro de verde

  digitalWrite(Pines[4], LOW);
  digitalWrite(Pines[10], LOW);
  digitalWrite(Pines[16], LOW);
  digitalWrite(Pines[22], LOW);

  // Prendemos los adyacentes al centro el azul

  digitalWrite(Pines[5], HIGH);
  digitalWrite(Pines[11], HIGH);
  digitalWrite(Pines[17], HIGH);
  digitalWrite(Pines[23], HIGH);

  // Apagamos en los extremos el rojo

  digitalWrite(Pines[0], LOW);
  digitalWrite(Pines[6], LOW);
  digitalWrite(Pines[18], LOW);
  digitalWrite(Pines[24], LOW);

  // Prendemos en los extremos el verde

  digitalWrite(Pines[1], HIGH);
  digitalWrite(Pines[7], HIGH);
  digitalWrite(Pines[19], HIGH);
  digitalWrite(Pines[25], HIGH);

  delay(Secuencia4_tiempoDelay);

  // Prendemos en el centro el blanco

  digitalWrite(Pines[12], HIGH);
  digitalWrite(Pines[13], HIGH);  
  digitalWrite(Pines[14], HIGH);

  // Apagamos en los adycantes el azul

  digitalWrite(Pines[5], LOW);
  digitalWrite(Pines[11], LOW);
  digitalWrite(Pines[17], LOW);
  digitalWrite(Pines[23], LOW);

  // Prendemos en los adyacentes el amarillo

  digitalWrite(Pines[3], HIGH);
  digitalWrite(Pines[9], HIGH);
  digitalWrite(Pines[15], HIGH);
  digitalWrite(Pines[21], HIGH);
  digitalWrite(Pines[4], HIGH);
  digitalWrite(Pines[10], HIGH);
  digitalWrite(Pines[16], HIGH);
  digitalWrite(Pines[22], HIGH);

  // Apagamos en los extremos el verde

  digitalWrite(Pines[1], LOW);
  digitalWrite(Pines[7], LOW);
  digitalWrite(Pines[19], LOW);
  digitalWrite(Pines[25], LOW);

  // Prendemos en los extremos el azul

  digitalWrite(Pines[2], HIGH);
  digitalWrite(Pines[8], HIGH);
  digitalWrite(Pines[20], HIGH);
  digitalWrite(Pines[26], HIGH);

  delay(Secuencia4_tiempoDelay);

  // Apagamos el centro
  
  digitalWrite(Pines[12], LOW);
  digitalWrite(Pines[13], LOW);
  digitalWrite(Pines[14], LOW);

  // Apagamos en los adyacentes el amarillo y prendemos en los adyacentes el blanco (activando el azul)

  digitalWrite(Pines[5], HIGH);
  digitalWrite(Pines[11], HIGH);
  digitalWrite(Pines[17], HIGH);
  digitalWrite(Pines[23], HIGH);

  // Apagamos en los extremos el azul

  digitalWrite(Pines[2], LOW);
  digitalWrite(Pines[8], LOW);
  digitalWrite(Pines[20], LOW);
  digitalWrite(Pines[26], LOW);

  // Prendemos en los extremos el amarillo

  digitalWrite(Pines[0], HIGH);
  digitalWrite(Pines[6], HIGH);
  digitalWrite(Pines[18], HIGH);
  digitalWrite(Pines[24], HIGH);
  digitalWrite(Pines[1], HIGH);
  digitalWrite(Pines[7], HIGH);
  digitalWrite(Pines[19], HIGH);
  digitalWrite(Pines[25], HIGH);

  delay(Secuencia4_tiempoDelay);

  // Apagamos los adyacentes al centro

  digitalWrite(Pines[3], LOW);
  digitalWrite(Pines[9], LOW);
  digitalWrite(Pines[15], LOW);
  digitalWrite(Pines[21], LOW);
  digitalWrite(Pines[4], LOW);
  digitalWrite(Pines[10], LOW);
  digitalWrite(Pines[16], LOW);
  digitalWrite(Pines[22], LOW);
  digitalWrite(Pines[5], LOW);
  digitalWrite(Pines[11], LOW);
  digitalWrite(Pines[17], LOW);
  digitalWrite(Pines[23], LOW);

  // Apagamos en los extremos el amarillo y prendemos el blanco (activando el azul)
  digitalWrite(Pines[2], HIGH);
  digitalWrite(Pines[8], HIGH);
  digitalWrite(Pines[20], HIGH);
  digitalWrite(Pines[26], HIGH);

  delay(Secuencia4_tiempoDelay);

  // Apagamos en los extremos el blanco
  digitalWrite(Pines[0], LOW);
  digitalWrite(Pines[6], LOW);
  digitalWrite(Pines[18], LOW);
  digitalWrite(Pines[24], LOW);
  digitalWrite(Pines[1], LOW);
  digitalWrite(Pines[7], LOW);
  digitalWrite(Pines[19], LOW);
  digitalWrite(Pines[25], LOW);
  digitalWrite(Pines[2], LOW);
  digitalWrite(Pines[8], LOW);
  digitalWrite(Pines[20], LOW);
  digitalWrite(Pines[26], LOW);

  delay(Secuencia4_tiempoDelay);

}

void EjecutarSecuencias_S5() {
  digitalWrite(Row_C[0], HIGH);
  digitalWrite(Row_C[1], HIGH);
  digitalWrite(Row_C[2], HIGH);
  
  int Secuencia5_Delay[] = {100, 200, 300};

    for (int Secuencia5_Velocidad = 2; Secuencia5_Velocidad >= 0; Secuencia5_Velocidad--) {
      
        for( int Secuencia5_Row_Filas = 2; Secuencia5_Row_Filas >= 0; Secuencia5_Row_Filas--) {
          
            digitalWrite(Row_C[Secuencia5_Row_Filas], LOW);
            
            digitalWrite(Pines[0], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[0], LOW);
            digitalWrite(Pines[3], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[3], LOW);
            digitalWrite(Pines[6], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[6], LOW);
            digitalWrite(Pines[15], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[15], LOW);
            digitalWrite(Pines[24], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[24], LOW);
            digitalWrite(Pines[21], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[21], LOW);
            digitalWrite(Pines[18], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[18], LOW);
            digitalWrite(Pines[9], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[9], LOW);
            digitalWrite(Pines[12], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[12], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[12], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[12], LOW);
            digitalWrite(Pines[9], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[9], LOW);
            digitalWrite(Pines[18], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[18], LOW);
            digitalWrite(Pines[21], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[21], LOW);
            digitalWrite(Pines[24], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[24], LOW);
            digitalWrite(Pines[15], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[15], LOW);
            digitalWrite(Pines[6], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[6], LOW);
            digitalWrite(Pines[3], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[3], LOW);
            digitalWrite(Pines[0], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[0], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);


            digitalWrite(Pines[0], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[3], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[6], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[15], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[24], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[21], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[18], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[9], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[12], HIGH);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[12], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[9], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[18], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[21], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[24], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[15], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[6], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[3], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);
            digitalWrite(Pines[0], LOW);
            delay(Secuencia5_Delay[Secuencia5_Velocidad]);

            digitalWrite(Pines[0], LOW);
            digitalWrite(Pines[3], LOW);
            digitalWrite(Pines[6], LOW);
            digitalWrite(Pines[15], LOW);
            digitalWrite(Pines[24], LOW);
            digitalWrite(Pines[21], LOW);
            digitalWrite(Pines[18], LOW);
            digitalWrite(Pines[9], LOW);
            digitalWrite(Pines[12], LOW);

            digitalWrite(Row_C[Secuencia5_Row_Filas], HIGH);
          }
        
    }

}


/*
 * Leer los datos nuevos y ejecutar las secuencias correspondientes.
 */

void leerDatos() {
  nuevosDatos = false;

  Serial.println( caracteresRecibidos );

  /* 
   *  Mis secuencias se llaman: 
   *  <S1>, <S2>, <S3>, <S4>, <S5> (Secuencias requeridas)
   *  <P1>, <P2>, <P3>, <P4>, <P5> (Secuencias personalizadas)
   */
  if ( caracteresRecibidos[0] == 'S') {
    switch(caracteresRecibidos[1]) {
      case '1':
        duracionTotalSecuencia_1 = 0;
        EjecutarSecuencias_S1();
        break;

      case '2':
        EjecutarSecuencias_S2();
        break;
        
      case '3':
        EjecutarSecuencias_S3();
        break;
        
      case '4':
        EjecutarSecuencias_S4();
        break;
        
      case '5':
        EjecutarSecuencias_S5();
        break;
    }
  }

  /*
   * Prender cada LED (y cada común) independientemente.
   * Comandos empleados:
   * *  <LN_RX_GY_BZ>
   *    Con:
   *         N = Número del LED
   *         X = Estado LED Rojo
   *         Y = Estado LED Verde
   *         Z = Estado LED Azul
   * *  <CN_X>
   *    Con: 
   *         N = Número del común (1) Superior - (2) Central - (3) INferior)
   *         X = Estado común (1) Apagado - (0) Encendido
   */

  if ( caracteresRecibidos[0] == 'L') {
    switch(caracteresRecibidos[4]) { case '1': Personalizada_R = HIGH; break; case '0': Personalizada_R = LOW; break; }
    switch(caracteresRecibidos[7]) { case '1': Personalizada_G = HIGH; break; case '0': Personalizada_G = LOW; break; }
    switch(caracteresRecibidos[10]) { case '1': Personalizada_B = HIGH; break; case '0': Personalizada_B = LOW; break; }
    
    switch(caracteresRecibidos[1]) {     
      case '1':
        Serial.println(Personalizada_R);
        Serial.println(Personalizada_G);
        Serial.println(Personalizada_B);
        digitalWrite(Pines[0], Personalizada_R);
        digitalWrite(Pines[1], Personalizada_G);
        digitalWrite(Pines[2], Personalizada_B);
        delay(500);
        break;
      case '2':
        digitalWrite(Pines[3], Personalizada_R);
        digitalWrite(Pines[4], Personalizada_G);
        digitalWrite(Pines[5], Personalizada_B);
        delay(500);
        break;
      case '3':
        digitalWrite(Pines[6], Personalizada_R);
        digitalWrite(Pines[7], Personalizada_G);
        digitalWrite(Pines[8], Personalizada_B);
        delay(500);
        break;
      case '4':
        digitalWrite(Pines[9], Personalizada_R);
        digitalWrite(Pines[10], Personalizada_G);
        digitalWrite(Pines[11], Personalizada_B);
        delay(500);
        break;
      case '5':
        digitalWrite(Pines[12], Personalizada_R);
        digitalWrite(Pines[13], Personalizada_G);
        digitalWrite(Pines[14], Personalizada_B);
        delay(500);
        break;
      case '6':
        digitalWrite(Pines[15], Personalizada_R);
        digitalWrite(Pines[16], Personalizada_G);
        digitalWrite(Pines[17], Personalizada_B);
        delay(500);
        break;
      case '7':
        digitalWrite(Pines[18], Personalizada_R);
        digitalWrite(Pines[19], Personalizada_G);
        digitalWrite(Pines[20], Personalizada_B);
        delay(500);
        break;
      case '8':
        digitalWrite(Pines[21], Personalizada_R);
        digitalWrite(Pines[22], Personalizada_G);
        digitalWrite(Pines[23], Personalizada_B);
        delay(500);
        break;
      case '9':
        digitalWrite(Pines[24], Personalizada_R);
        digitalWrite(Pines[25], Personalizada_G);
        digitalWrite(Pines[26], Personalizada_B);
        delay(500);
        break;
    }
  }

  if ( caracteresRecibidos[0] == 'C') {

    switch(caracteresRecibidos[1]) {
      case '1':
        Personalizada_Comun_Pin = 0;
        break;
      case '2':
        Personalizada_Comun_Pin = 1;
        break;
      case '3':
        Personalizada_Comun_Pin = 2;
        break;
      
    }
    
    switch(caracteresRecibidos[3]) {
     case '0':
      digitalWrite(Row_C[Personalizada_Comun_Pin], LOW); 
      break;
     case '1':
      digitalWrite(Row_C[Personalizada_Comun_Pin], HIGH);
      break;
    }
  }

  if ( caracteresRecibidos[0] == 'F') {
    switch(caracteresRecibidos[1]) {
      case '1':
        for(int conteoPines = 0; conteoPines < Row_C_l; conteoPines++) {
          digitalWrite(Row_C[conteoPines], LOW);
        }
        for(int conteoPines = 0; conteoPines < Pines_total; conteoPines++) {
          digitalWrite(Pines[conteoPines], HIGH);
        }
        break;
      case '2':
        for(int conteoPines = 0; conteoPines < Row_C_l; conteoPines++) {
          digitalWrite(Row_C[conteoPines], HIGH);
        }
        for(int conteoPines = 0; conteoPines < Pines_total; conteoPines++) {
          digitalWrite(Pines[conteoPines], LOW);
        }
        break;
    }
  }
  

}


/*
 * Revisamos si vienen datos del módulo Bluetooth.
 */
 
void comenzarRecibirBluetooth() {
  /*
   * Para asegurarse que los comandos vengan correctamente
   * deben enviarse desde la aplicación con las etiquetas de abertura y cierre
   * en este caso son los signos mayor que (>) y menor que (<)
   */
  static boolean recibiendoDatos = false;
  static byte nuevoscaracteres = 0;
  char marcaInicial = '<';
  char marcaFinal = '>';
  char lecturaserial;

  if (BTserial.available()) {
    lecturaserial = BTserial.read();
    if (recibiendoDatos == true) {
      if (lecturaserial != marcaFinal) {
        caracteresRecibidos[nuevoscaracteres] = lecturaserial;
        nuevoscaracteres++;
        if (nuevoscaracteres >= maximoCaracteres) {
          nuevoscaracteres = maximoCaracteres - 1;
        }
      } else {
        caracteresRecibidos[nuevoscaracteres] = '\0';
        recibiendoDatos = false;
        nuevoscaracteres = 0;
        nuevosDatos = true;
      }
    }

    else if (lecturaserial == marcaInicial) {
      recibiendoDatos = true;
    }
  }
}

void setup() {
  for(int conteoPines = 0; conteoPines < Pines_total; conteoPines++) {
    pinMode(Pines[conteoPines], OUTPUT);
  }
  for(int conteoPines = 0; conteoPines < Row_C_l; conteoPines++) {
    pinMode(Row_C[conteoPines], OUTPUT);
  }
  
  Serial.begin(9600);
  Serial.println("La Arduino esta lista para funcionar");
  BTserial.begin(9600);

  for(int conteoPines = 0; conteoPines < Row_C_l; conteoPines++) {
    analogWrite(Row_C[conteoPines], 255);
  }
  for(int conteoPines = 0; conteoPines < Pines_total; conteoPines++) {
    digitalWrite(Pines[conteoPines], LOW);
  }
}

void loop() {
  if ( BTserial.available() ) {
    comenzarRecibirBluetooth();
  }
  if ( nuevosDatos ) {
    leerDatos();
  }
}