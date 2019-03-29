#include <LiquidCrystal.h>
int scelta = -1;
int meta = 60;
bool turno = true; //TRUE : P1, FALSE : P2
int punteggio = 0;
bool zero = true;
#define UP 10
#define OK 9
#define DOWN 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(UP, INPUT_PULLUP);
  pinMode(OK, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
}

void loop() {

introduction();

inserisciMeta();

while(punteggio<meta){
  imposta_giocata();
  esegui_giocata();
  dai_punti();
}

vittoria();

}

void introduction()
{
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Angela");
  lcd.setCursor(2,1);
  lcd.print("game by G.D.");
  delay(2000);
}
void inserisciMeta()
{
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Scegli una meta");
  lcd.setCursor(1,1); lcd.print("30<-  " + String(meta) + "  ->99");
  while(digitalRead(OK)== HIGH)
  {
    if (digitalRead(DOWN) == LOW && meta > 30)
    {
      while (digitalRead(DOWN) == LOW){}
      meta--;
      lcd.setCursor(7,1); lcd.print(String(meta));
    }
    if (digitalRead(UP) == LOW && meta < 99)
    {
      while (digitalRead(UP) == LOW){}
      meta++;
      lcd.setCursor(7,1); lcd.print(String(meta));
    }
  }
}

void imposta_giocata()
{
  
  lcd.clear(); lcd.setCursor(3,0); lcd.print("Turno del");
  lcd.setCursor(2,1);
  
  if(turno)
  {
    lcd.print("giocatore 1");
  }
  else 
  {
    lcd.print("giocatore 2");
  } 
  delay(2000);
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Scegli num. tra");
    lcd.setCursor(0,1);
    
    if(scelta == -1)
    {
      lcd.print("0,1,2,3,4,5,6"); 
    }
    if(scelta == 0)
    {  
      lcd.print("1,2,3,4,5,6");
      zero = false;
    }
    else if(scelta == 1 || scelta == 6)
    {
      lcd.print("2,3,4,5");
    }
    else if(scelta == 2 || scelta == 5)
    {
      lcd.print("1,3,4,6");
    }
    else if(scelta == 3 || scelta == 4)
    { 
      lcd.print("1,2,5,6");
    } 
    delay(2000);
}

void esegui_giocata()
{
  lcd.clear(); 
  bool finito = false; int mossa = 0;
  lcd.setCursor(7,1); lcd.print(String(mossa));
  while(!finito)
  {
    while(digitalRead(OK)== HIGH)
    {
        if (digitalRead(DOWN) == LOW && mossa > 0)
        {
          while (digitalRead(DOWN) == LOW){}
          mossa--;
          lcd.setCursor(7,1); lcd.print(String(mossa));
        }
        if (digitalRead(UP) == LOW && mossa < 6)
        {
          while (digitalRead(UP) == LOW){}
          mossa++;
          lcd.setCursor(7,1); lcd.print(String(mossa));
        }     
   }
    finito = valuta(mossa);
  }
  punteggio += mossa;
  scelta = mossa;
  turno = !turno;
  zero=false;
}

void dai_punti()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Punteggio:");
  lcd.setCursor(11,0);
  lcd.print(String(punteggio));
  lcd.setCursor(11,1); lcd.print(String(scelta));
  delay(1000);
}

void vittoria()
{
  lcd.clear();
  lcd.setCursor(4,0);lcd.print("Vince il");
  lcd.setCursor(2,1);
  if(punteggio>meta)
  {
    if(turno)
    {lcd.print("giocatore 1!");delay(2000);}
    else
    {lcd.print("giocatore 2!");delay(2000);}
  }
  else
  {
    if(turno)
    {lcd.print("giocatore 2!");delay(2000);}
    else
    {lcd.print("giocatore 1!");delay(2000);}
  }
  reset();
}

bool valuta(int i)
{
  if(i == scelta || i == 7-scelta || (i==0 && !zero))
  {
    return false;
  }
  else
  {
    return true;
  }
}

void reset()
{
  lcd.clear();
  scelta = -1;
  meta = 60;
  turno = true; 
  punteggio = 0;
  zero = true; 
}
