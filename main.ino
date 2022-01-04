/***********************************************************
 * Project        :     Better Earth
 * Input          :     Soil Moisture Sensors,PH Sensor
 * Output         :     Relay
 **********************************************************/

int s1=A0;
int s2=A1;
int gMotor=3;
int fMotor=5;
int oMotor=6;
int mSwitch=7;
int phTest=0;

#define BUTTON_PRESSED 0
#define MOTOR_ON 0
#define MOTOR_OFF 1

int gFlag=0;
int fFlag=0;
String ph;
void setup() {
 pinMode(s1,INPUT);
 pinMode(s2,INPUT);
 pinMode(gMotor,OUTPUT);
 pinMode(fMotor,OUTPUT);
 pinMode(oMotor,OUTPUT);
 pinMode(mSwitch,INPUT_PULLUP);
 digitalWrite(gMotor,MOTOR_OFF);
 digitalWrite(fMotor,MOTOR_OFF);
 digitalWrite(oMotor,MOTOR_OFF);
 
 Serial.begin(9600);
}

void loop() {
 int phValue=(digitalRead(0));
 if(phValue==0) {
  Serial.println("oMotor ON");
  digitalWrite(oMotor,MOTOR_ON);
 } else {
  Serial.println("oMotor OFF");
  digitalWrite(oMotor,MOTOR_OFF);
 }
 
 int s1Value=analogRead(s1);
 int s2Value=analogRead(s2);
  
 if(digitalRead(mSwitch)==BUTTON_PRESSED && gFlag==0) {
   Serial.println("Switch On");
   digitalWrite(gMotor,MOTOR_ON);
   gFlag=1;
 }

 if(s1Value<300 && gFlag==1) {
  gFlag=0;
  Serial.println("Motor Off");
  digitalWrite(gMotor,MOTOR_OFF);
 }

 if(s2Value<300 && fFlag==0) {
  phTest=0;
  Serial.println("Flush Motor On");
  digitalWrite(fMotor,MOTOR_ON);
  fFlag=1; 
 }

 if(s2Value>600 && fFlag==1) {
  Serial.println("Flush Motor Off");
  digitalWrite(fMotor,MOTOR_OFF);
  fFlag=0;
  phTest=1;
 }

 
 
 Serial.print("s1Value: ");
 Serial.print(s1Value);
 Serial.print(",s2Value: ");
 Serial.print(s2Value);
 Serial.println();
 delay(1000);
}
