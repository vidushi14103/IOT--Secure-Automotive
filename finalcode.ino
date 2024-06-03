#define BLYNK_TEMPLATE_ID "TMPL3eque4NRR"
#define BLYNK_TEMPLATE_NAME "carcrash"
#define BLYNK_AUTH_TOKEN "vSEGZvYMGTZ_pVeuog5P7pzgirN_-Cgi"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const int trigPin = 5;
const int echoPin = 16;
const int flame = 4 ; // A2 is the analog pin 
const int vib_pin=13;
const int led_pin=2;
// defines variables
long duration;
int distance;

char ssid[] = "Galaxy S20 FE 5GC50C";
char pass[] = "ritwik@99";
char auth[] = "vSEGZvYMGTZ_pVeuog5P7pzgirN_-Cgi";

void setup() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  pinMode(12,OUTPUT);//led
  pinMode(4,INPUT);//flame
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(14,OUTPUT);//buzzeer
  
  pinMode(vib_pin,INPUT);
  pinMode(led_pin,OUTPUT);
  Serial.begin(9600); // Starts the serial communication
  

  Blynk.begin(auth, ssid, pass);
}

void loop() {

 int f=digitalRead(4); // FIRE SENSOR
  int val;
  val=digitalRead(vib_pin); 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("flame: ");
  Serial.println(f);
  Serial.print("vibration:");
  Serial.println(val);
  
  if (distance<20)
  {
    digitalWrite(12,HIGH);
    Blynk.virtualWrite(V1, distance);
    if (f==0)
    {
      Serial.println("FIRE");
      digitalWrite(14,HIGH);
      Blynk.virtualWrite(V0, f);
    }
    else
    {
      Serial.println("no fire");
      digitalWrite(14,LOW);
      Blynk.virtualWrite(V0,f );
    }
    
  }
  else
  {
    digitalWrite(12,LOW);
    Blynk.virtualWrite(V1, distance);
  }
  if (f==0)
    {
      Serial.println("FIRE");
      digitalWrite(14,HIGH);
      Blynk.virtualWrite(V0, f);
    }
    else
    {
      Serial.println("no fire");
      digitalWrite(14,LOW);
      Blynk.virtualWrite(V0,f );
    }
  
if(val==1)
  {
    digitalWrite(led_pin,HIGH);
    Blynk.virtualWrite(V2,vib_pin );
   }
else
  {
   digitalWrite(led_pin,LOW);
   Blynk.virtualWrite(V2, vib_pin);
 }
 Blynk.run();
}