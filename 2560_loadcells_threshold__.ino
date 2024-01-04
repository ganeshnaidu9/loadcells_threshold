#include <HX711.h>
const int ld_cell2_dout = 40;
const int ld_cell2_sck = 42;

const int thresholdValue1 = 300;
const int thresholdValue2 = 1500;
const int motorPin = 4;
//HX711 scale1;
HX711 scale2;

int X=0;
//int loadcell2();
int currentWeight = 0; // loadcell2();
void setup()
{
  Serial.begin(115200);
  pinMode(motorPin,OUTPUT);

  //scale1.begin(ld_cell1_dout,ld_cell1_sck);
  //scale1.set_scale();
  //scale1.tare();

  scale2.begin(ld_cell2_dout,ld_cell2_sck);
  scale2.set_scale();
  scale2.tare();
  currentWeight = waterLevel();
}

void loop()
{
  // digitalWrite(motorPin,HIGH);
  // delay(2000);
  // digitalWrite(motorPin,0);
  // delay(1000);
  //loadcell1();
  
  //waterLevel();
  currentWeight = waterLevel();
  delay(100);
  // Serial.print("currentWeight : ");
  // Serial.println(currentWeight);

  while (!Serial.available()) {
  }
  X = Serial.parseInt();
  Serial.println(X);
delay(10);
  currentWeight = waterLevel();
  delay(100);
  Serial.print("currentWeight : ");
  Serial.println(currentWeight);
   //delay(100);
  if(currentWeight > X)
  {
    digitalWrite(motorPin,HIGH);
    Serial.println("pump ON");
    delay(10);
    while(waterLevel() > (currentWeight - X))
    {
       delay(150);
      // Serial.println("filling water");
    }
    digitalWrite(motorPin,LOW);
    Serial.println("pump OFF");
    delay(10);
    
  }
  delay(100);
  currentWeight = waterLevel();
  Serial.print("currentWeight : ");
  Serial.println(currentWeight);
  delay(100);
  X=0;

  
}

//void loadcell1() {
//Serial.println("place weights on loadcell1");
  //delay(1000);

  //if(scale1.is_ready())
  //{
    //long reading1 = scale1.get_units(10);
    //int weight1 = reading1/1800;
    //Serial.print("weight on loadcell1");
    //Serial.println(weight1);

    //if (weight1>thresholdValue1)
    //{
      //Serial.println("weight on loadcell1 is greater than thresholdvalue1");
    //}

  //}
//}

int loadcell2(){
 // Serial.println("place weights on loadcell2");
  //delay(1000);

  if(scale2.is_ready())
  {
    delay(50);
    long reading2 = scale2.get_units(10);
    int weight2 = (reading2/400)-258;
    if(weight2<0){
      weight2 = 0;
    }
   // return weight2;


    Serial.print("weight on loadcell2  ");
    Serial.println(weight2);

   if(weight2<thresholdValue1)
    {
      Serial.println("please fill the container");
    }

    if (weight2>thresholdValue2)
    {
      Serial.println("container is full");
    }

  }
  delay(10);
}

int waterLevel(){
  delay(10);
  int weight2;
  if(scale2.is_ready())
 {
  delay(50);
    long reading2 = scale2.get_units(10);
    int weight2 = (reading2/400)-258;
    if(weight2<0){
      weight2 = 0;
    }
    return weight2;
    // Serial.print("weight on loadcell2  ");
    // Serial.println(weight2);
  }
  // delay(10);
  // return weight2;
}

