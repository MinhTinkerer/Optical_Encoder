/*
  Quadrature encoder
  See http://en.wikipedia.org/wiki/Rotary_encoder#Incremental_rotary_encoder for more info.
*/

// current encoder state, default it to a 0 state
byte i = B00000000;
// delta since last update
volatile int  d = 0;

void setup(){
  Serial.begin(115200);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(0, read, CHANGE);
  attachInterrupt(1, read, CHANGE);
}

void read(){
  i <<= 2;
  // check the state of the bits
  if(digitalRead(2)){
    i |= B00000010;
  }
  if(digitalRead(3)){
    i |= B00000001;
  }
  // mask off old bits
  i &= B00001111;

  switch(i){
    case B00000000: // no change
      break;
    case B00000001:
      d++;
      break;
    case B00000010:
      d--;
      break;
    case B00000011: // error
      break;
    case B00000100:
      d--;
      break;
    case B00000101: // no change
      break;
    case B00000110: // error
      break;
    case B00000111:
      d++;
      break;
    case B00001000:
      d++;
      break;     
    case B00001001: // error
      break;     
    case B00001010: // no change
      break;     
    case B00001011:
      d--;
      break;
    case B00001100: // error
      break;     
    case B00001101:
      d--;
      break;     
    case B00001110:
      d++;
      break;     
    case B00001111: // no change
      break;
  }

}

void loop(){
  delay(100);
  Serial.println(d, DEC);
}