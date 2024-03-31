// Definição dos pinos para LEDs e botões
#define ledP A3
#define led0 A2
#define led1 A4
#define led2 A0
#define led3 A1
#define led4 9
#define led5 8
#define led6 7

#define BTN_0 0
#define BTN_1 1
#define BTN_2 2
#define BTN_3 3 // Pinos dos botões

#define LED_0 10
#define LED_1 11
#define LED_2 12
#define LED_3 13 // Pinos dos LEDs

// Pinos analógicos
int potPin = A5; // Pino analógico conectado ao potenciômetro
int buzzerPin = 6; // Pino do buzzer

#define BUZZ 6 // Pino do falante

byte mem[40], botao = 4, sort = 4, aux = 0;
int stagio = 0;

// Função para apagar todos os LEDs
void limpadisplay()
{
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(ledP, LOW);
}

// Função para realizar um autoteste no display
void AutoTeste(int TempoTeste)
{
  limpadisplay();

  digitalWrite(led0, HIGH);
  delay(TempoTeste);
  digitalWrite(led0, LOW);

  digitalWrite(led1, HIGH);
  delay(TempoTeste);
  digitalWrite(led1, LOW);

  digitalWrite(led5, HIGH);
  delay(TempoTeste);
  digitalWrite(led5, LOW);

  digitalWrite(led6, HIGH);
  delay(TempoTeste);
  digitalWrite(led6, LOW);

  digitalWrite(led4, HIGH);
  delay(TempoTeste);
  digitalWrite(led4, LOW);

  digitalWrite(led3, HIGH);
  delay(TempoTeste);
  digitalWrite(led3, LOW);

  digitalWrite(led2, HIGH);
  delay(TempoTeste);
  digitalWrite(led2, LOW);

  digitalWrite(ledP, HIGH);
  delay(TempoTeste);
  digitalWrite(ledP, LOW);

  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(ledP, HIGH);
  delay(TempoTeste + 200);

  limpadisplay();
}

void setup()
{
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(ledP, OUTPUT);

  pinMode(BUZZ, OUTPUT);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  pinMode(BTN_0, INPUT_PULLUP);
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);

  limpadisplay();
  AutoTeste(200);

  tone(BUZZ, 200);
  digitalWrite(LED_0, HIGH);
  delay(600);
  noTone(BUZZ);
  tone(BUZZ, 300);
  digitalWrite(LED_1, HIGH);
  delay(600);
  noTone(BUZZ);
  tone(BUZZ, 400);
  digitalWrite(LED_2, HIGH);
  delay(600);
  noTone(BUZZ);
  tone(BUZZ, 500);
  digitalWrite(LED_3, HIGH);
  delay(600);
  noTone(BUZZ);

  limpadisplay();
}

// Função para reiniciar o jogo
void Reset()
{
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(ledP, LOW);
  noTone(BUZZ);

  stagio = 0;
  aux = 0;
  sort = 4;

  for (int i = 0; i < 40; i++)
  {
    mem[i] = 0;
  }
}

void loop()
{
  if (sort == 4)
  {
    while (digitalRead(BTN_0) && digitalRead(BTN_1) && digitalRead(BTN_2) && digitalRead(BTN_3))
      Sort();
    while (!digitalRead(BTN_0) || !digitalRead(BTN_1) || !digitalRead(BTN_2) || !digitalRead(BTN_3))
      leds(4);
  }
  mem[stagio] = sort;

  int potValue = analogRead(potPin);

  int volume = map(potValue, 0, 1023, 0, 255);

  analogWrite(buzzerPin, volume);

  for (int i = 0; i < stagio + 1; i++)
    leds(mem[i]);

  while (aux <= stagio)
  {
  while (!(digitalRead(BTN_0) && digitalRead(BTN_1) && digitalRead(BTN_2) && digitalRead(BTN_3))){

      if (!digitalRead(BTN_0))
        botao = 0;
      if (!digitalRead(BTN_1))
        botao = 1;
      if (!digitalRead(BTN_2))
        botao = 2;
      if (!digitalRead(BTN_3))
        botao = 3;
      Sort();
    }
    if (botao < 4)
    {
      leds(botao);
      if (botao != mem[aux])
      {
        digitalWrite(LED_0, HIGH);
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_3, HIGH);
        tone(BUZZ, 80);
        delay(1000);
        noTone(BUZZ);
        delay(500);
        leds(4);
        stagio = -1;
      }
      aux++;
    }
    botao = 4;
  }
  delay(200);
  stagio++;
  NumeroNoDisplay(stagio);
  aux = 0;

  if (!digitalRead(BTN_3))
  {
    Reset();
  }
}

// Função para controlar os LEDs
void leds(int led)
{
  if (led < 4)
  {
    tone(BUZZ, (led + 2) * 100);
    digitalWrite(led + 10, HIGH);
    delay(500);
    noTone(BUZZ);
  }
  digitalWrite(LED_0, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  delay(200);
}

// Função para sortear números
void Sort()
{
  if (sort)
    sort--;
  else
    sort = 3;
  delayMicroseconds(500);
}

// Função para exibir números no display
void NumeroNoDisplay(int valor)
{
  switch (valor)
  {
    case 0:
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(ledP, LOW);
      break;

    case 1:
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(ledP, LOW);
      break;

    case 2:
      digitalWrite(led0, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(ledP, LOW);
      break;

    case 3:
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, LOW);
      digitalWrite(ledP, LOW);
      break;

    case 4:
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(ledP, LOW);
      break;

    case 5:
      digitalWrite(led0, LOW);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, LOW);
      digitalWrite(ledP, LOW);
      break;

    case 6:
      digitalWrite(led0, LOW);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(ledP, LOW);
      break;

    case 7:
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(ledP, LOW);
      break;

    case 8:
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(ledP, LOW);
      break;

    case 9:
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, LOW);
      digitalWrite(ledP, LOW);
      break;

    default:
      digitalWrite(led0, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(ledP, HIGH);
      break;
  }
}
