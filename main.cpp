  const byte Green = 3;
  const byte Red = 4;
  const byte Yellow = 5;
  const byte Blue = 6;
  const byte Button = 2;

  volatile bool changeloop = false;
  volatile int switcher = 1;
  volatile long random_delay = 0;

  static volatile unsigned long last_interrupt_time = 0;

  unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
  unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
  
  


void setup() {
  // put your setup code here, to run once:


  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Blue, OUTPUT);
  pinMode(Button, INPUT);

  randomSeed(analogRead(0));
  attachInterrupt(digitalPinToInterrupt(Button), switch_mode, RISING);
  Serial.begin(9600);
  

}

void myDelay(int x)   {
  for(int i=0; i<=x; i++){
  if (changeloop) break;
    delayMicroseconds(1000);
  }
} 
void all_off(){
  digitalWrite(Green, LOW);
  digitalWrite(Red, LOW);
  digitalWrite(Yellow, LOW);
  digitalWrite(Blue, LOW); 
}
void all_on(){
 
  digitalWrite(Green, HIGH);
  digitalWrite(Red, HIGH);
  digitalWrite(Yellow, HIGH);
  digitalWrite(Blue, HIGH);
  
  
}

void one_steps(){
  all_off();
  
  
  digitalWrite(Red, HIGH);
    myDelay(500);
  digitalWrite(Red, LOW);
  digitalWrite(Blue, HIGH);
    myDelay(500);
  digitalWrite(Blue, LOW);
  digitalWrite(Yellow, HIGH);
    myDelay(500);
  digitalWrite(Yellow, LOW);
  digitalWrite(Green, HIGH);
    myDelay(500);
  digitalWrite(Green, LOW);
  
}

void two_steps(){
    all_off();
  
  
  digitalWrite(Red, HIGH);
  digitalWrite(Blue, HIGH);
    myDelay(500);
  digitalWrite(Red, LOW);
  digitalWrite(Blue, LOW);
    myDelay(500);
  digitalWrite(Green, HIGH);
  digitalWrite(Yellow, HIGH);
    myDelay(500);
  digitalWrite(Yellow, LOW);
  digitalWrite(Green, LOW);

  
}
void waterfall_forward(){
  all_off();

  //Red Blue Yellow Green
 
    random_delay = random(100, 1000);
    
    for(int i = 0; i <= 10; ++i){
      digitalWrite(Red, HIGH);
      digitalWrite(Blue, HIGH);
      digitalWrite(Green, LOW);
        myDelay(random_delay);
      digitalWrite(Red, LOW);
      digitalWrite(Yellow, HIGH);
        myDelay(random_delay);
      digitalWrite(Blue, LOW);
      digitalWrite(Green, HIGH);
        myDelay(random_delay);
      digitalWrite(Yellow, LOW);
      digitalWrite(Red, HIGH);
        myDelay(random_delay);
        if(changeloop) break;
    }
 
 
}

void waterfall_backward(){
   all_off();
   //Green Yellow Blue Red
 
      random_delay = random(100, 1000);
      
      for(int i = 0; i <= 10; ++i){
        digitalWrite(Green, HIGH);
        digitalWrite(Yellow, HIGH);
        digitalWrite(Red, LOW);
          myDelay(random_delay);
        digitalWrite(Green, LOW);
        digitalWrite(Blue, HIGH);
          myDelay(random_delay);
        digitalWrite(Yellow, LOW);
        digitalWrite(Red, HIGH);
          myDelay(random_delay);
        digitalWrite(Blue, LOW);
        digitalWrite(Green, HIGH);
          myDelay(random_delay);
          if(changeloop) break;
      }
  
}

void random_dir(){
  all_off();
  
    if(random(1)){
      waterfall_forward();
    } else {
      waterfall_backward();
    }
    
  
    
}
void switch_mode(){

 unsigned long interrupt_time = millis();
 
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 200) 
 {
    
  interrupts();
  switcher +=1;
  if(switcher > 6) switcher = 1;
  changeloop = true;
  Serial.println(switcher);
 }
  last_interrupt_time = interrupt_time;

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("loop");

  


  changeloop = false;
  
  switch(switcher){
  case 1:
    all_on();
    break;
  case 2:
    one_steps();
    break;
  case 3:
    two_steps();
    break;
  case 4:
    waterfall_forward();
    break;
  case 5:
    waterfall_backward();
    break;
  case 6:
    random_dir();
    break;
  }

}

