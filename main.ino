/*                   
                                  /   \       
 _                        )      ((   ))     (
(@)                      /|\      ))_((     /|\
|-|                     / | \    (/\|/\)   / | \                      (@)
| | -------------------/--|-voV---\`|'/--Vov-|--\---------------------|-|
|-|                         '^`   (o o)  '^`                          | |
| |                               `\Y/'                               |-|
|-|                              Authors                              | |
| |                   Vujovic Jelena & Mrdalj Denis                   |-|
|-|                                                                   | |
| |                                                                   |-|
|_|___________________________________________________________________| |
(@)              l   /\ /         ( (       \ /\   l                `\|-|
                 l /   V           \ \       V   \ l                  (@)
                 l/                _) )_          \I
                                   `\ /'
                                     '                        
 */


#include <SPI.h>          //Including header for SPI communication
#include <Pixy.h>         //Including header for PIXY camera

/*           Defining pins            */
#define PIND2 2
#define PIND3 3
#define PIND4 4
#define PIND5 5

// This is the main Pixy object 
Pixy pixy;

void setup()
{
  //Defining pins as outputs
  pinMode(PIN2, OUTPUT);  
  pinMode(PIN3, OUTPUT);
  pinMode(PIN4, OUTPUT);
  pinMode(PIN5, OUTPUT);
  Serial.begin(9600);                 //Defining Baud Rate
  Serial.print("Starting...\n");      //Useless garbage

  pixy.init();                        //Pixy define function
}


void loop()
{ 
  uint16_t blocks;                    //
  int niz[3] = {0,0,0};               //Array in which we sort the signatures according to x-axis

   blocks = pixy.getBlocks();         //Getting all the information about the blocks

   if (blocks == 3){                  //Only for three colors without black

   if (pixy.blocks[0].x > pixy.blocks[1].x && pixy.blocks[0].x > pixy.blocks[2].x) {        //Sorting of an array by x-axis (if first block is larger than the rest) 
    niz[0] = pixy.blocks[0].signature;
    if (pixy.blocks[1].x > pixy.blocks[2].x){
      niz[1] = pixy.blocks[1].signature;
      niz[2] = pixy.blocks[2].signature;
    }else{
      niz[2] = pixy.blocks[1].signature;
      niz[1] = pixy.blocks[2].signature;
    }
  }

  if (pixy.blocks[1].x > pixy.blocks[0].x && pixy.blocks[1].x > pixy.blocks[2].x) {         //Sorting of an array by x-axis (if second block is larger than the rest)
    niz[0] = pixy.blocks[1].signature;
    if (pixy.blocks[0].x > pixy.blocks[2].x){
      niz[1] = pixy.blocks[0].signature;
      niz[2] = pixy.blocks[2].signature;
    }else{
      niz[2] = pixy.blocks[0].signature;
      niz[1] = pixy.blocks[2].signature;
    }
  }

  if (pixy.blocks[2].x > pixy.blocks[1].x && pixy.blocks[2].x > pixy.blocks[0].x) {         //Sorting of an array by x-axis (if third block is larger than the rest)
    niz[0] = pixy.blocks[2].signature;
    if (pixy.blocks[1].x > pixy.blocks[0].x){
      niz[1] = pixy.blocks[1].signature;
      niz[2] = pixy.blocks[0].signature;
    }else{
      niz[2] = pixy.blocks[1].signature;
      niz[1] = pixy.blocks[0].signature;
    }
  }
           //Sending a signal according to combinations provided
  if(niz[2]== 1 && niz[1] == 2 && niz[0] == 3)      //Combination num.2        
    digitalWrite(PIND3, HIGH);
  if(niz[2]== 3 && niz[1] == 1 && niz[0] == 5){     //Combination num.5
    digitalWrite(PIND2, HIGH);
    digitalWrite(PIND4, HIGH);
  }
  if(niz[2]== 1 && niz[1] == 5 && niz[0] == 2){     //Combination num.6
    digitalWrite(PIND3, HIGH);
    digitalWrite(PIND4, HIGH);
  }
  if(niz[2]== 5 && niz[1] == 3 && niz[0] == 2){     //Combination num.10
    digitalWrite(PIND5, HIGH);
    digitalWrite(PIND3, HIGH);
  }
 }
}
