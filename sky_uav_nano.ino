#include <Servo.h>


Servo r_ail; //Right aileron
Servo l_ail; //Left aileron
Servo Elevator; //elevator servo
Servo Rudder; //rudder servo
Servo thrust; //thrust motor variable


#define thrPin 3  //Throttle esc data pin
#define rAilPin 5     //Right aileron servo pin
#define lAilPin 6     //Left aileron servo pin
#define elePin  9    //Elevator servo pin
#define rudderPin 10  //Rudder servo pin


//We create variables for the time width values of each PWM input signal
unsigned long counter_1, counter_2, counter_3, counter_4, current_count;

//We create 4 variables to stopre the previous value of the input signal (if LOW or HIGH)
byte last_CH1_state, last_CH2_state, last_CH3_state, last_CH4_state;

int yaw, pitch, roll, throttle, filtered_roll=0;

int temp=0;

//To store the 1000us to 2000us value we create variables and store each channel
int input_YAW;      //channel 4 of the receiver and pin D10 of arduino
int input_PITCH;    //channel 2 of the receiver and pin D9 of arduino
int input_ROLL;     //channel 1 of the receiver and pin D5&D6 of arduino
int input_THROTTLE; //channel 3 of the receiver and pin D3 of arduino


void setup() {
  /*
   * Port registers allow for lower-level and faster manipulation of the i/o pins of the microcontroller on an Arduino board. 
   * The chips used on the Arduino board (the ATmega8 and ATmega168) have three ports:
     -B (digital pin 8 to 13)
     -C (analog input pins)
     -D (digital pins 0 to 7)
   
  //All Arduino (Atmega) digital pins are inputs when you begin...
  */  
   
  PCICR |= (1 << PCIE1);    //enable PCMSK1 scan                                                 
  PCMSK1 |= (1 << PCINT8);  //Set pin A0 trigger an interrupt on state change. 
  PCMSK1 |= (1 << PCINT9);  //Set pin A1 trigger an interrupt on state change.                                             
  PCMSK1 |= (1 << PCINT10);  //Set pin A2 trigger an interrupt on state change.                                               
  PCMSK1 |= (1 << PCINT11);  //Set pin A3 trigger an interrupt on state change.  
  
 
  r_ail.attach(rAilPin);
  l_ail.attach(lAilPin);
  Elevator.attach(elePin);
  Rudder.attach(rudderPin);
  thrust.attach(thrPin,1000,2000);

  //Start the serial to be able to compute the values in computer
  //same baud rate should be selected on serial monitor
  Serial.begin(250000);  

}

void loop() //using map function to manipulate the data comes from the receiver
{
 
    roll = map(input_ROLL,1080,1920,40,110); //ailerons
    yaw = map(input_YAW,1080,1930,40,110); //rudder (on surface)
    pitch = map(input_PITCH,1080,1925,55,100); //elevator
    throttle = map(input_THROTTLE,1080,1930,0,180); 
    
    Serial.print("Roll: ");
    Serial.print(roll);
    Serial.print("    ");  
    Serial.print("yaw: ");
    Serial.print(yaw);
    Serial.print("    ");  
    Serial.print("Pitch: ");
    Serial.print(pitch);
    Serial.print("    ");  
    Serial.print("thr: ");
    Serial.print(throttle);
    Serial.println("    ");  

   
    if(abs(input_ROLL-temp)>=5){
       filtered_roll=roll;
    }
      temp=input_ROLL;

  
   elevator(pitch);
   thr(throttle);
   aileron(filtered_roll);
   rudder(yaw);
   delay(50);
   
}



ISR(PCINT1_vect){
//First we take the current count value in micro seconds using the micros() function
  
  current_count = micros();
  //***************************Channel 1
  if(PINC & B00000001)
  {                                                   //verifying whether if the pin A0 is HIGH ==> pin A0 -- B00000001  
    if(last_CH1_state == 0)
    {                                                 //If the last state == 0, there is a state change...
      last_CH1_state = 1;                            //store the current state to use it in next loop
      counter_1 = current_count;                     //set counter_1 to current value
    }
  }
  else if(last_CH1_state == 1)
  {                                                   //If pin 8 == LOW and the last state was HIGH there is a state change      
    last_CH1_state = 0;                              //store the current state to use it in next loop
    input_ROLL = current_count - counter_1;         //creating a time difference ; Channel 1 is current_time - timer_1.
  }



  //*********************************Channel 2
  if(PINC & B00000010 )
  {                                                                           
    if(last_CH2_state == 0)   //pin A1 -- B00000010
    {                                               
      last_CH2_state = 1;                                                   
      counter_2 = current_count;                                             
    }
  }
  else if(last_CH2_state == 1){                                           
    last_CH2_state = 0;                                                     
    input_PITCH = current_count - counter_2;                             
  }


  
  //*********************************Channel 3
  if(PINC & B00000100 )
  {                                                                     
    if(last_CH3_state == 0)       //pin A2 - B00000100 
    {                                             
      last_CH3_state = 1;                                                  
      counter_3 = current_count;                                               
    }
  }
  else if(last_CH3_state == 1){                                             
    last_CH3_state = 0;                                                    
    input_THROTTLE = current_count - counter_3;                            

  }


  
  //*************************************Channel 4
  if(PINC & B00001000 )
  {                                                   
    if(last_CH4_state == 0)           //pin A3  -- B00001000
    {                                               
      last_CH4_state = 1;                                                   
      counter_4 = current_count;                                              
    }
  }
  else if(last_CH4_state == 1)
  {                                             
    last_CH4_state = 0;                                                  
    input_YAW = current_count - counter_4;                            
  }
}

void thr(int a)  //throttle level
{ 
  thrust.write(a);
}

void aileron(int a) //writer function for aileron servos
{ 
  l_ail.write(a);
  r_ail.write(a);
}

void elevator(int a) //writer function for elevator servo
{ 
  Elevator.write(a);
}

void rudder(int a) //writer function for rudder servo
{ 
  Rudder.write(a);
}
