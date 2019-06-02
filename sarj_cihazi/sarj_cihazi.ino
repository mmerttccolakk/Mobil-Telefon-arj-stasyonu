//kutuphane tanimlamalari
#include <LiquidCrystal_I2C.h>

//jeton durumu
bool jeton=0;

//calisma suresi
unsigned long sure = 10;

//zaman ayarlari
unsigned long gecmis_zaman;

//pin tanimlamalari
#define role 2
#define para 3

//ekran_guncelle
byte ekran_gun = 4534;

//ekran tanimlaniyor
LiquidCrystal_I2C lcd(0x27, 16, 2);

//kurulum
void setup() {
  
  //pin giris ve cikislari tanimlandi
  pinMode(role, OUTPUT);
  pinMode(para, INPUT);

  //lcd ayari
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print(" **HOSGELDINIZ***");
  lcd.setCursor(0,1); //Second line
  lcd.print("SISTEM KURULUYOR");
  delay(1000);
  lcd.clear();
  lcd.print("1 TL ILE CALISIR");
  lcd.setCursor(0,1); //Second line
  lcd.print("15 DK SARJ EDER");
  }

void loop() {
 //simdiki zaman
  unsigned long zaman = millis();
  jeton = digitalRead(para); 
  
  if(jeton==1){
    gecmis_zaman=zaman; 
    sure = 900000;//milisaniye
    ekran_gun=1;
    }
  
    if((gecmis_zaman+sure)<=zaman){
      digitalWrite(role, HIGH);//calisiyor 
          if(ekran_gun==0){
            //birsey yapma
          }else{
            lcd.clear();
            lcd.print("1 TL ILE CALISIR");
            lcd.setCursor(0,1); //Second line
            lcd.print("15 DK SARJ EDER");
            ekran_gun=0;
            }
    }else{
        if(ekran_gun==2){
            lcd.setCursor(0,1);
            unsigned long kalan_sn = (gecmis_zaman+sure)-zaman;
            kalan_sn=(kalan_sn/1000);

            if(kalan_sn>60){
                  kalan_sn=(kalan_sn/60);
                  kalan_sn=kalan_sn+1;
                  String kalan_saniye = String(kalan_sn);
                  kalan_saniye = "KALAN SURE:"+ kalan_saniye + " dk       ";
                  lcd.print(kalan_saniye); 
              }else{
                  kalan_sn=(kalan_sn);
                  String kalan_saniye = String(kalan_sn);
                  kalan_saniye = "KALAN SURE:"+ kalan_saniye + " sn       ";
                  lcd.print(kalan_saniye); 
                }
            
            
          }else{
            digitalWrite(role, LOW);//calisiyor
            lcd.clear();
            lcd.print("SARJ EDILIYOR...");
            ekran_gun=2;
            }
    }
    
    
}
