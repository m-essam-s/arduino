const int led[3] = {5, 6, 7}

void setup () {
  for (int i=0 ; i<3 ; i++){
    pinMode(led[i], OUTPUT);
  }
}

void loop () {
  for (int j = 0; j< 3; j++){ 
    for (int k=0; k<3; k++ ){
      digitalWrite(led[k], LOW); // turn off all LEDs
    }
    digitalWrite(led[j], HIGH); // turn on the current LED
    delay(1000);
  }
}