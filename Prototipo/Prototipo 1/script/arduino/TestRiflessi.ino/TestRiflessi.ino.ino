#define r1 11 //rosso rgb1
#define g1 10 //verde rgb1
#define b1 9 //blu rgb1
#define r2 8 //rosso rgb2
#define g2 7 //verde rgb2
#define b2 6 //blu rgb2
#define  l1 13 //led1
#define l2 12 //led2
#define btn1 5 //bottone led1
#define btn2 4 //bottone led2
#define btn3 3 //bottone rgb1
#define btn4 2 //bottone rgb2



void setup()
{
  pinMode(r1, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int scelta = Serial.available();
  int test;
  if (scelta == 1)
  {
    test = Test1();
  }
  else if (scelta == 2)
  {
    test = Test2();
  }
}

//test led singoli
int Test1()
{
  int punteggio = 0;
  int tempo = 0;
  int ledOn;
  bool change = true;
  int tempoIniziale, tempoFinale, tempoMax = 1500;
  bool continua = true; //fin quando sei in gioco
  while (continua == true)
  {
    tempoIniziale = millis(); //vedo quando entro
    if (change) {
      ledOn = random(1, 2);
      change = false;
    }
    if (ledOn == 1)
    {
      digitalWrite(l1, HIGH);
      digitalWrite(l2, LOW);
    }
    else
    {
      digitalWrite(l2, HIGH);
      digitalWrite(l1, LOW);
    }

    if (digitalRead(btn1) ==HIGH)
    {
      tempoFinale = millis();
      tempo = tempoFinale - tempoIniziale;
      if (tempo <= tempoMax && ledOn == 1)
      {
        change = true;
        punteggio++;
        continua = true;
        if (tempoMax > 500)
        {
          tempoMax = tempoMax - 500;
        }
      }
      else
      {
        continua = false;
        digitalWrite(l2, LOW);
        digitalWrite(l1, LOW);
        return punteggio;
      }
    }
      else if (digitalRead(btn2)== HIGH)
      {
        tempoFinale = millis();
        tempo = tempoFinale - tempoIniziale;
        if (tempo <= tempoMax && ledOn == 2)
        {
          change = true;
          punteggio++;
          continua = true;
          if (tempoMax > 500)
          {
            tempoMax = tempoMax - 500;
          }
        }
        else
        {
          continua = false;
          digitalWrite(l2, LOW);
          digitalWrite(l1, LOW);
          return punteggio;

        }
      }

    }

  }





//test led rgb
int Test2()
{
  int punteggio = 0;
  int tempo = 0;
  int ledOn;
  bool change = true;
  int tempoIniziale, tempoFinale, tempoMax = 1500;
  bool continua = true;

  while (continua == true)
  {
    tempoIniziale = millis(); //vedo quando entro
    if (change) {
      ledOn = random(1, 4); //1 rgb1 blu,2 rgb1 rosso, 3 rgb2 blu, 4 rgb2 rosso
      change = false;
      //quando uno mette il rosso, devi schiaccere il led spento
    }
    if (ledOn == 1)
    {
      digitalWrite(b1, HIGH);
      digitalWrite(b2, LOW);
      digitalWrite(r1, LOW);
      digitalWrite(r2, LOW);
    }
    else if (ledOn == 2)
    {
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
      digitalWrite(r1, HIGH);
      digitalWrite(r2, LOW);
    }
    else if (ledOn == 3)
    {
      digitalWrite(b1, LOW);
      digitalWrite(b2, HIGH);
      digitalWrite(r1, LOW);
      digitalWrite(r2, LOW);
    }
    else
    {
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
      digitalWrite(r1, LOW);
      digitalWrite(r2, HIGH);
    }


    if (digitalRead(btn3)== HIGH)
    {
      tempoFinale = millis();
      tempo = tempoFinale - tempoIniziale;
      if ((tempo <= tempoMax && ledOn == 1) || (tempo <= tempoMax && ledOn == 4))
      {
        change = true;
        punteggio++;
        continua = true;
        if (tempoMax > 500)
        {
          tempoMax = tempoMax - 500;
        }
      }
      else
      {
        continua = false;
        digitalWrite(b1, LOW);
        digitalWrite(b2, LOW);
        digitalWrite(r1, LOW);
        digitalWrite(r2, HIGH);
        return punteggio;
      }

    }
    else if (digitalRead(btn4) ==HIGH)
    {
      tempoFinale = millis();
      tempo = tempoFinale - tempoIniziale;
      if (tempo <= tempoMax && (ledOn == 2 || ledOn == 3))
      {
        change = true;
        punteggio++;
        continua = true;
        if (tempoMax > 500)
        {
          tempoMax = tempoMax - 500;
        }
      }
      else
      {
        continua = false;
        digitalWrite(l2, LOW);
        digitalWrite(l1, LOW);
        return punteggio;

      }
    }

  }


}
