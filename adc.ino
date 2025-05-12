float r = 1943.5; 	//Resistor value
float c = .000470;  	//Capacitance value
float v = 15; 		//Voltage supply value
float e = 2.71828;  	//Euler's number

void setup() {
  pinMode(2, OUTPUT);
  pinMode(7, INPUT);
  pinMode(A5, INPUT);
  Serial.begin(9600);
}

void loop() {
  float start = micros(); 		//Start the timer in microseconds
  digitalWrite(2, LOW); 		//Turn off the NPN and start the capacitor charging
  while (digitalRead(7) == 0){  	//While the comparator isn't flipped, wait
  }
  float end = micros(); 		//End the timer in microseconds
  digitalWrite(2, HIGH); 	 	//Turn on the NPN and start the capacitor discharge
  float adc = (analogRead(A5) - 9.38483) / 102.67;  	//Calculate ADC from Arduino with error correction
  float time = ((end - start)/1000000);   	//Calculate time between start and end in seconds
  float exp = -time / (r * c);  		//Calculate the exponent of e in the formula
  float power = pow(e, exp);  		//Calculate e to the power of the exponent value
  float voltage = ((v - v * power) / 1.08709 + 0.068094); //Put in the rest of the equation, with correction
  Serial.println(voltage, 5); 		//Print our adc voltage
  Serial.println(adc, 5); 		//Print the Arduino ADC
  float perc_dif = ( abs(adc - voltage) / ((adc + voltage) / 2) ) * 100;  //Calculate the percent difference
  Serial.print(perc_dif); 		//Print the percent difference
  Serial.println("%");  			//Print a percentage symbol
  Serial.println("~~~~~~~~~~~~"); 	//Print a spacer
  delay(100); 				//Delay for 0.1 seconds to discharge the capacitor properly
}
