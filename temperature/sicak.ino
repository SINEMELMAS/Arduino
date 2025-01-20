int lm35Pin = A0;
int led = 13;
#define buzzer 8
int zaman = 50;
int okunan_deger = 0;
float sicaklik_gerilim = 0;
float sicaklik = 0;
int frekans = 2000;

void setup() 
{
 
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
}
 
void loop()
{
  okunan_deger = analogRead(lm35Pin);
  sicaklik_gerilim = (okunan_deger / 1023.0)*5000;
  sicaklik = sicaklik_gerilim /10.0; 
  Serial.println(sicaklik);
  

  if(sicaklik >= 50){
    digitalWrite(led,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(zaman);
    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    delay(zaman);
  }
  else{

    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    
    
  }
}




















