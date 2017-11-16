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
  pinMode(PIND2, OUTPUT);  
  pinMode(PIND3, OUTPUT);
  pinMode(PIND4, OUTPUT);
  pinMode(PIND5, OUTPUT);
  Serial.begin(9600);                 //Defining Baud Rate
  Serial.print("Starting...\n");      //Useless garbage
  
  int first_block_x;
  int second_block_x;
  int third_block_x;
    
  int first_block_signature;
  int second_block_signature;
  int third_block_signature;
  
  int signature_array[3] = {0,0,0};               //Array in which we sort the signatures according to x-axis

  pixy.init();                        //Pixy define function
}


void loop()
{ 
  uint16_t blocks;   
  
   signature_array[3] = {0,0,0}; 

   blocks = pixy.getBlocks();         //Getting all the information about the blocks
   first_block_x = pixy.blocks[0].x;              //Variables for easier code understanding
   second_block_x = pixy.blocks[1].x;
   third_block_x = pixy.blocks[2].x;
  
   first_block_signature = pixy.blocks[0].signature;
   second_block_signature = pixy.blocks[1].signature;
   third_block_signature = pixy.blocks[2].signature;

   if (blocks == 3){                  //Only for three colors without black

   if (first_block_x > second_block_x && first_block_x > third_block_x) {        //Sorting of an array by x-axis (if first block is larger than the rest) 
    signature_array[0] = first_block_signature;
    if (second_block_x > third_block_x){
      signature_array[1] = second_block_signature;
      signature_array[2] = third_block_signature;
    }else{
      signature_array[2] = second_block_signature;
      signature_array[1] = third_block_signature;
    }
  }

  if (second_block_x > first_block_x && second_block_x > third_block_x) {         //Sorting of an array by x-axis (if second block is larger than the rest)
    signature_array[0] = second_block_signature;
    if (first_block_x > third_block_x){
      signature_array[1] = first_block_signature;
      signature_array[2] = third_block_signature;
    }else{
      signature_array[2] = first_block_signature;
      signature_array[1] = third_block_signature;
    }
  }

  if (third_block_x > second_block_x && third_block_x > first_block_x) {         //Sorting of an array by x-axis (if third block is larger than the rest)
    signature_array[0] = third_block_signature;
    if (second_block_x > first_block_x){
      signature_array[1] = second_block_signature;
      signature_array[2] = first_block_signature;
    }else{
      signature_array[2] = second_block_signature;
      signature_array[1] = first_block_signature;
    }
  }
           //Sending a signal according to combinations provided (3 blocks)
  if(signature_array[2]== GREEN && signature_array[1] == YELLOW && signature_array[0] == BLUE)      //Combination num.2        
    digitalWrite(PIND3, HIGH);
  if(signature_array[2]== BLUE && signature_array[1] == GREEN && signature_array[0] == ORANGE){     //Combination num.5
    digitalWrite(PIND2, HIGH);
    digitalWrite(PIND4, HIGH);
  }
  if(signature_array[2]== GREEN && signature_array[1] == ORANGE && signature_array[0] == YELLOW){   //Combination num.6
    digitalWrite(PIND3, HIGH);
    digitalWrite(PIND4, HIGH);
  }
  if(signature_array[2]== ORANGE && signature_array[1] == BLUE && signature_array[0] == YELLOW){    //Combination num.10
    digitalWrite(PIND5, HIGH);
    digitalWrite(PIND3, HIGH);
  }
 }
 
 if (blocks==2){                        //For two colors, ignoring black, doesn't matter if it's there or nah
   if (first_block_x > second_block_x){                   //Sorting of an array by x-axis (if first block is larger)
     signature_array[0] = first_block_signature;
     signature_array[1] = second_block_signature;
   }
   if (second_block_x > first_block_x){                  //Sorting of an array by x-axis (if second block is larger)
     signature_array[1] = first_block_signature;
     signature_array[0] = second_block_signature;
   }
   
   
          //Sending a signal according to combinations provided (2 blocks)
  if(signature_array[1] == ORANGE && signature_array[0] == GREEN){                         //Combination num.1
    digitalWrite(PIND2, HIGH); 
  }
  if(signature_array[1] == YELLOW && signature_array[0] == BLUE){                         //Combination num.3
    digitalWrite(PIND2, HIGH); 
    digitalWrite(PIND3, HIGH);
  }
  if(signature_array[1] == BLUE && signature_array[0] == ORANGE){                         //Combination num.4  
    digitalWrite(PIND4, HIGH);
  }
  if(signature_array[1] == YELLOW && signature_array[0] == GREEN){                        //Combination num.7  
    digitalWrite(PIND2, HIGH);
    digitalWrite(PIND3, HIGH);
    digitalWrite(PIND4, HIGH);
  }
  if(signature_array[1] == BLUE && signature_array[0] == GREEN){                          //Combination num.8
    digitalWrite(PIND5, HIGH);
  }  
  if(signature_array[1] == YELLOW && signature_array[0] == ORANGE){                       //Combination num.9
    digitalWrite(PIND2, HIGH);
    digitalWrite(PIND5, HIGH);
  }
 }
}
