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

/*           Defining colors          */
#define GREEN 1
#define YELLOW 2
#define BLUE 3
#define ORANGE 5

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
  uint16_t blocks;                    
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
           //Sending a signal according to combinations provided (3 blocks)
  if(niz[2]== GREEN && niz[1] == YELLOW && niz[0] == BLUE)      //Combination num.2        
    digitalWrite(PIND3, HIGH);
  if(niz[2]== BLUE && niz[1] == GREEN && niz[0] == ORANGE){     //Combination num.5
    digitalWrite(PIND2, HIGH);
    digitalWrite(PIND4, HIGH);
  }
  if(niz[2]== GREEN && niz[1] == ORANGE && niz[0] == YELLOW){   //Combination num.6
    digitalWrite(PIND3, HIGH);
    digitalWrite(PIND4, HIGH);
  }
  if(niz[2]== ORANGE && niz[1] == BLUE && niz[0] == YELLOW){    //Combination num.10
    digitalWrite(PIND5, HIGH);
    digitalWrite(PIND3, HIGH);
  }
 }
 
 if (blocks==2){                        //For two colors, ignoring black, doesn't matter if it's there or nah
   if (pixy.blocks[0].x > pixy.blocks[1].x){                   //Sorting of an array by x-axis (if first block is larger)
     niz[0] = pixy.blocks[0].signature;
     niz[1] = pixy.blocks[1].signature;
   }
   if (pixy.blocks[1].x > pixy.blocks[0].x){                  //Sorting of an array by x-axis (if second block is larger)
     niz[1] = pixy.blocks[0].signature;
     niz[0] = pixy.blocks[1].signature;
   }
   
   
          //Sending a signal according to combinations provided (2 blocks)
  if(niz[1] == ORANGE && niz[0] == GREEN){                          //Combination num.1
    digitalWrite(PIND2, HIGH);
  }
  if(niz[1] == YELLOW && niz[0] == BLUE){                        //Combination num.3
    digitalWrite(PIND2, HIGH);
    digitalWrite(PIND3, HIGH);
  }
  if(niz[1] == BLUE && niz[0] == ORANGE){                           //Combination num.4  
    digitalWrite(PIND4, HIGH);
  }
  if(niz[1] == YELLOW && niz[0] == GREEN){                       //Combination num.7  
    digitalWrite(PIND2, HIGH);
    digitalWrite(PIND3, HIGH);
    digitalWrite(PIND4, HIGH);
  }
  if(niz[1] == BLUE && niz[0] == GREEN){                         //Combination num.8
    digitalWrite(PIND5, HIGH);
  }
  if(niz[1] == YELLOW && niz[0] == ORANGE){                      //Combination num.9
    digitalWrite(PIND2, HIGH);
    digitalWrite(PIND5, HIGH);
  }
 }
}
