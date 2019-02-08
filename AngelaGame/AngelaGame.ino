
int scelta = -1;
int meta = 0;
bool turno = true; //TRUE : P1, FALSE : P2
int punteggio = 0;
bool zero = true;

void setup() 
{
  Serial.begin(9600);
}

void loop() {
  
inserisciMeta();

while(punteggio<meta){
  giocata();
}

vittoria();

}

void inserisciMeta()
{
  bool metaGiusta= false;
  Serial.println("Scegliere una meta da un minimo di 30 ad un massimo di 90");

  while(!metaGiusta)
  {
    while(Serial.available() == 0){}
    meta=Serial.parseInt();
    Serial.println(meta);
    if(meta<30 || meta>99){
      Serial.println("Meta fuori dai limiti indicati, immettere una meta adeguata");
    }
    else{
      metaGiusta = true;
    }
  }
}

void giocata()
{
  int i;  bool done = false;
  if(turno){
    Serial.println("Turno del giocatore 1");
  }
  else {
    Serial.println("Turno del giocatore 2");
  } 
  while(!done)
  {
    if(scelta == -1)
    {
      Serial.println("Scegliere tra i numeri: 0, 1, 2, 3, 4, 5, 6"); 
    }
    if(scelta == 0)
    {  
      Serial.println("Scegliere tra i numeri: 1, 2, 3, 4, 5, 6");
      zero = false;
    }
    else if(scelta == 1 || scelta == 6)
    {
      Serial.println("Scegliere un numero tra 2, 3, 4, 5");
    }
    else if(scelta == 2 || scelta == 5)
    {
      Serial.println("Scegliere un numero tra 1, 3, 4, 6");
    }
    else if(scelta == 3 || scelta == 4)
    { 
      Serial.println("Scegliere un numero tra 1, 2, 5, 6");
    } 
    while(Serial.available()==0){}
    i = Serial.parseInt();
    done = valuta(i);
  }
  scelta = i;
  Serial.println("Punteggio:" + String(punteggio += scelta)); 
  turno = !turno;
}

void vittoria()
{
  if(punteggio>meta)
  {
    if(turno)
    {Serial.println("Vince il giocatore 1!");}
    else
    {Serial.println("Vince il giocatore 2!");}
  }
  else
  {
    if(turno)
    {Serial.println("Vince il giocatore 2!");}
    else
    {Serial.println("Vince il giocatore 1!");}
  }
  reset();
}

bool valuta(int i)
{
  if(i == scelta || i == 7-scelta || (i==0 && !zero)){
    Serial.println("Non barare!");
    return false;
  }
  else if (i<0 || i>6) {
    Serial.println("Scrivi un numero adeguato!");
  }
  else
  {return true;}
}

void reset()
{
  scelta = -1;
  meta = 0;
  turno = true; 
  punteggio = 0;
  zero = true; 
}



