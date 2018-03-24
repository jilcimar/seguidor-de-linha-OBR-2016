#include <Ultrasonic.h>
#include <Servo.h>

int pino_passo_esquerda = 11; // Branco
int pino_direcao_esquerda = 10; // Azul
int pino_passo_direita = 12; // Laranja
int pino_direcao_direita = 13; // Verde

int pino_sensorCor_esquerda = A2; // Cinza
int pino_sensorCor_direita = A0; // Verde
int pino_sensorCor_centro = A1; // Laranja
int pino_sensorCor_frente_direita = A3; // Azul
int pino_sensorCor_frente_esquerda = A4; // Cinza

int servo_subir = 6; // Laranja
int servo_fechar = 5; // Laranja

Servo subir;
Servo fechar;

int direcao_esquerda = 1;
int direcao_direita = 1;
int passos_motor = 11400;

int e;
int c;
int d;
int fe;
int fd;

#define echoPin 3
#define trigPin 4

#define echoPin 3
#define trigPin 4

Ultrasonic ultrasonic(4, 3);

int passo_alinhamento = 1200;

void setup()
{
  Serial.begin(9600);
  subir.attach(servo_subir);
  fechar.attach(servo_fechar);
  subir.write(15);
  fechar.write(60);

  pinMode(pino_sensorCor_direita, INPUT); 
  pinMode(pino_sensorCor_centro, INPUT);
  pinMode(pino_sensorCor_esquerda, INPUT);
  pinMode(pino_sensorCor_frente_esquerda, INPUT);
  pinMode(pino_sensorCor_frente_direita, INPUT);
  
  pinMode(pino_passo_esquerda, OUTPUT);
  pinMode(pino_direcao_esquerda, OUTPUT);

  pinMode(pino_passo_direita, OUTPUT);
  pinMode(pino_direcao_direita, OUTPUT);
}

void loop()
{
  seguirLinha();
}

void garra_subir (int x)
{
  if (x == 1)
  {
    for (int f = 15 ; f < 125 ; f++)
    {
      subir.write(f);
      delay(30);
    }
  }
  else
  {
    for (int f = 125 ; 15 < f; f--)
    {
      subir.write(f);
      delay(30);
    }
  }
}

void garra_fechar (int x)
{
  if (x == 1)
  {
    for (int f = 0 ; f < 60 ; f++)
    {
      fechar.write(f);
      delay(30);
    }
  }
  else
  {
    for (int f = 60 ; 1 < f; f--)
    {
      fechar.write(f);
      delay(30);
    }
  }
}

void frente_tras (int x, int p) //Frente --> x = 1 p = passos | Tras --> x = 0 p = passos
{
  for (int f = 0 ; f < p ; f++)
  {
    direcao_esquerda = x;
    direcao_direita = x;

    digitalWrite(pino_direcao_esquerda, direcao_esquerda);
    digitalWrite(pino_direcao_direita, direcao_direita);

    digitalWrite(pino_passo_esquerda, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_esquerda, 0);
    delayMicroseconds(100);
    digitalWrite(pino_passo_direita, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_direita, 0);
    delayMicroseconds(100);
  }
}

void rotacionar (int x, int y, int p) // Esquerda -- > x = 1 y = 0 p = passos | Direita --> x = 0 y = 1 p = passos
{
  for (int f = 0 ; f < p; f++)
  {
    direcao_direita = x;
    digitalWrite(pino_direcao_direita, direcao_direita);

    digitalWrite(pino_passo_direita, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_direita, 0);
    delayMicroseconds(100);


    direcao_esquerda = y;
    digitalWrite(pino_direcao_esquerda, direcao_esquerda);

    digitalWrite(pino_passo_esquerda, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_esquerda, 0);
    delayMicroseconds(100);
  }
}

void esquerda (int x, int p) //Frente -- > x = 1 p = passos | Tras --> x = 0 p = passos
{
  for (int f = 0 ; f < p; f++)
  {
    direcao_esquerda = x;
    digitalWrite(pino_direcao_esquerda, direcao_esquerda);

    digitalWrite(pino_passo_esquerda, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_esquerda, 0);
    delayMicroseconds(100);
  }
}

void direita (int x, int p) //Frente -- > x = 1 p = passos | Tras --> x = 0 p = passos
{
  for (int f = 0 ; f < p; f++)
  {
    direcao_direita = x;
    digitalWrite(pino_direcao_direita, direcao_direita);

    digitalWrite(pino_passo_direita, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_direita, 0);
    delayMicroseconds(100);
  }
}

void lerLinha()
{
  int xc = 420;
  int xd = 412;
  int xe = 515;
  int xfe = 77;
  int xfd = 652;
  
  int centro = analogRead((pino_sensorCor_centro)); 
  int direita = analogRead((pino_sensorCor_direita)); 
  int esquerda = analogRead((pino_sensorCor_esquerda));
  int frente_esquerda = analogRead((pino_sensorCor_frente_esquerda));
  int frente_direita = analogRead((pino_sensorCor_frente_direita));

  if(centro < xc )
  {
    c = 0;
  }
  else
  {
    c = 1;
  }

  if(direita < xd )
  {
    d = 0;
  }
  else
  {
    d = 1;
  }

  if(esquerda < xe )
  {
    e = 0;
  }
  else
  {
    e = 1;
  }
  
  if(frente_esquerda < xfe)
  {
    fe = 0;
  }
  else
  {
    fe = 1;
  }

  if(frente_direita < xfd)
  {
    fd = 0;
  }
  else
  {
    fd = 1;
  }
}

void seguirLinha()
{
  lerLinha();
  
  while (((!fe) && (fd) && (!c)) || ((!fe) && (fd) && (e) && (!d))) //Alinhamento simples esquerda
  {
    direita (1, 900);
    lerLinha();
  }
  while ((fe) && (fd) && (c) && (!e) && (d)) //Alinhamento 1 sensor esquerda
  {
    direita (1, 2500);
    lerLinha();
  }
  
  
  while (((fe) && (!fd) && (!c)) || ((fe) && (!fd) && (!e) && (d))) //Alinhamento simples direita
  {
    esquerda (1, 900);
    lerLinha();
  }
  while ((fe) && (fd) && (c) && (e) && (!d)) //Alinhamento 1 sensnor direita
  {
    esquerda (1, 2500);
    lerLinha();
  }
  
  if ((fe) && (fd) && (!c) && (!d))
  {
    rotacionar (0, 1, 9000);
  }
  else if ((fe) && (fd) && (!c) && (!e) && (d))
  {
    rotacionar (1, 0, 9000);
  }
  else
  {
    frente_tras (1, 100);
  }
}

void desvia()
{
  long distancia = ultraFrente();
  
  if( distancia < 7)
  {
    delay(2);
    
    rotacionar (0, 1, 9000);
    frente_tras (1, 9000);
    rotacionar (1, 0, 8500);
    frente_tras (1, 23000);
    rotacionar (1, 0, 9000);
    frente_tras (1, 9000);
    rotacionar (0, 1, 9000);
  }
}

float ultraFrente()
{

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  digitalWrite(trigPin, LOW);
  
  float tempo;
  tempo = pulseIn(echoPin,HIGH);
  float distanciaF = tempo / 29.4 / 2;
  
  return distanciaF; 
}
