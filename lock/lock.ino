//Tranca Eletronica
//Autor: manogray

//#include <Keypad.h>
#include <LiquidCrystal.h>

//const byte Coluna = 3;
//const byte Linha = 3;

//int i = 3;

//char Teclas[Linha][Coluna] = {
//    {'1','2','3'},
//    {'4','5','6'},
//    {'7','8','9'}
//};

//byte Pino_linha[Linha] = {13,10,9};

//byte Pino_coluna[Coluna] = {8,7,6};

LiquidCrystal lcd(12,11,5,4,3,2);
//Keypad keypad = Keypad(makeKeymap(Teclas),Pino_linha,Pino_coluna,Linha,Coluna);

int ledVerm = 6;
int ledVerde = 7;
String senhaAtual = "281295";
String senha = "";
int contador = 3;

String modo = "lock";

void setup(){
    Serial.begin(9600);
    pinMode(ledVerm,OUTPUT);
    pinMode(ledVerde,OUTPUT);
    digitalWrite(ledVerm,HIGH);
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Trava Eletronica");
    lcd.setCursor(2,1);
    lcd.print("by: manogray");
    delay(3500);
    lcd.clear();
}

void exibeMensagem(int coluna, int linha, String mensagem){
  lcd.setCursor(coluna,linha);
  lcd.print(mensagem);
}

void ascendeApaga(int ascende,int apaga){
  digitalWrite(ascende,HIGH);
  digitalWrite(apaga,LOW);
}

void destravar(){
  exibeMensagem(0,0,"ACESSO PERMITIDO");
  ascendeApaga(ledVerde,ledVerm);
}

void travar(){

}

void limpaBuffer(){
  senha = "";
  contador = 3;
  lcd.clear();
}

void loop(){
    
    if(modo == "lock"){
      exibeMensagem(5,0,"SENHA");
    }else if(modo == "definir"){
      exibeMensagem(0,0,"DIGITE UMA SENHA");
    }
    
    ascendeApaga(ledVerm,ledVerde);
    
    lcd.setCursor(contador,1);
    
    while(Serial.available() > 0){
      char caractere;
      caractere = Serial.read();
      if(caractere != 'd'){
        senha.concat(caractere);
        lcd.print('*');
        contador++;
        delay(10);
      }else {
        lcd.clear();
        if(senha == senhaAtual && modo == "lock"){
          destravar();
          delay(8000);
          travar();
          limpaBuffer();
        }else if(senha == "066695"){
          modo = "definir";
          limpaBuffer();
        }else if(modo == "definir"){
          senhaAtual = senha;
          ascendeApaga(ledVerde,ledVerm);
          exibeMensagem(1,0,"SENHA ALTERADA");
          modo = "lock";
          delay(3000);
          limpaBuffer();
        }else{
          exibeMensagem(1,0,"ACESSO NEGADO");
          ascendeApaga(ledVerm,ledVerde);
          delay(5000);
          limpaBuffer();
        }
      }
    }
    
    
    /*
    char teclaPressionada = keypad.getKey();
    if(teclaPressionada != NO_KEY){
        lcd.setCursor(i,1);
        lcd.print(teclaPressionada);
        i++;
    }*/
}
