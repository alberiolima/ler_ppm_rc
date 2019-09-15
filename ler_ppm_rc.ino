//#define plotter true
#define maxChNumber 20 //O limite do PPM são 8 canais, então 20 é bem mais que o necessário
#define PPMin       2  //Pino do Arduino que recebe o sinal PPM

unsigned int channel[maxChNumber]; 
byte channelCount = 0;

void setup() {  
  Serial.begin(115200); //Iniciamos com serial
  pinMode(PPMin, INPUT_PULLUP); 
}  
  
void loop() {  
  unsigned long tempoFrame = micros();
  if ( pulseIn(PPMin , HIGH) > 3500){
    unsigned int valorLido = 0;
    channelCount = 0;
    while ((valorLido < 3500)&&(channelCount < maxChNumber)) {
      valorLido = pulseIn(PPMin , HIGH);
      channel[channelCount++] = valorLido;
    }
    #ifndef plotter
      tempoFrame = micros() - tempoFrame - channel[channelCount-1];
      Serial.print( "Frame: " );
      Serial.print( tempoFrame );
      Serial.print( '\t' );
    #endif  
    for(byte i = 0; i < channelCount-1; i++) {
      #ifndef plotter
        Serial.print( i + 1 );
        Serial.print( ")");
      #else  
        channel[i] += ((i+1)*1000);
      #endif
      Serial.print(channel[i]);
      #ifndef plotter
        Serial.print("\t"); 
      #else
        Serial.print(" "); 
      #endif
    }
    Serial.println(); 
  } 
}
