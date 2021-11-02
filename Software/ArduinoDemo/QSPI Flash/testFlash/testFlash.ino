#include <S25FL128.h>

#define BUFFER_SIZE         ((uint32_t)0x0100)
#define WRITE_READ_ADDR     ((uint32_t)0x00C0)

uint8_t aTxBuffer[BUFFER_SIZE] = {0xc6 , 0xfe , 0xd7 , 0xba , 0x6e , 0x9f , 0x3e , 0x8e , 0x53 , 0x18 , 0x3e , 0x51 , 0xb0 , 0xe2 , 0x18 , 0x17 , 0x43 , 0xcb , 0x23 , 0x24 , 0x00 , 0x58 , 0x9c , 0x31 , 0x08 , 0x7f , 0x94 , 0xdc , 0xc1 , 0x22 , 0x34 , 0x7a , 0x11 , 0xe3 , 0x2d , 0xf1 , 0xac , 0x63 , 0x7e , 0xbe , 0x0f , 0xa3 , 0x27 , 0x05 , 0x47 , 0x46 , 0x56 , 0xbb , 0x70 , 0xf0 , 0x27 , 0x76 , 0x3a , 0x51 , 0x9e , 0x30 , 0x8a , 0x4a , 0x78 , 0x79 , 0xef , 0x04 , 0x9c , 0x74 , 0x3b , 0x6d , 0xeb , 0xee , 0xbf , 0x10 , 0xcf , 0xd6 , 0xca , 0xfa , 0x3b , 0x60 , 0x17 , 0x86 , 0x3f , 0x95 , 0xdd , 0x97 , 0xff , 0x44 , 0xed , 0x79 , 0x90 , 0xf6 , 0x20 , 0x58 , 0xe2 , 0x6f , 0xc6 , 0xee , 0xed , 0xd2 , 0x46 , 0xe9 , 0x55 , 0x24 , 0x2c , 0x16 , 0x7a , 0x82 , 0x7a , 0x49 , 0xef , 0xd1 , 0x0a , 0x18 , 0x02 , 0xab , 0xc8 , 0xf8 , 0x14 , 0xa2 , 0x59 , 0x56 , 0x33 , 0x0c , 0x92 , 0xbd , 0xea , 0xd1 , 0xe1 , 0x7e , 0x00 , 0x14 , 0xf2 , 0x89 , 0x49 , 0xd5 , 0x9d , 0xdf , 0x5e , 0xaf , 0x98 , 0xab , 0x36 , 0xdc , 0x11 , 0xe6 , 0xa6 , 0xf6 , 0x1d , 0xae , 0x16 , 0xc6 , 0x88 , 0xd9 , 0x51 , 0xaf , 0x76 , 0xe7 , 0x96 , 0x31 , 0x77 , 0x25 , 0x6a , 0xf8 , 0x37 , 0xe9 , 0x1c , 0xca , 0xb3 , 0x6f , 0x99 , 0xb7 , 0xf4 , 0xc0 , 0x39 , 0x20 , 0x8a , 0xa8 , 0xde , 0x87 , 0xdb , 0xb7 , 0x3f , 0x75 , 0x1f , 0x67 , 0x85 , 0x73 , 0xdc , 0xa2 , 0x48 , 0x19 , 0xcf , 0xbf , 0xd3 , 0x5e , 0x48 , 0x8f , 0xa2 , 0xfe , 0xa8 , 0x9d , 0xa5 , 0xba , 0x94 , 0x9d , 0xf7 , 0xff , 0x57 , 0x07 , 0x46 , 0xfd , 0x15 , 0x14 , 0xc5 , 0x89 , 0xec , 0x3b , 0x5d , 0x51 , 0xb0 , 0x92 , 0x31 , 0xeb , 0x49 , 0x30 , 0x63 , 0x11 , 0xe4 , 0x7e , 0x1d , 0xa4 , 0x89 , 0xb1 , 0x28 , 0x90 , 0x9c , 0x02 , 0xbc , 0x50 , 0x70 , 0x9d , 0x4d , 0xdb , 0x5a , 0xf1 , 0x68 , 0xd1 , 0x3d , 0x19};
uint8_t aRxBuffer[BUFFER_SIZE];

static void     Fill_Buffer (uint8_t *pBuffer, uint32_t uwBufferLength, uint32_t uwOffset);
static uint8_t  Buffercmp   (uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);

void setup() {
  Serial.begin(9600);
}

void printHex(uint8_t num) {
  char hexCar[2];

  sprintf(hexCar, "%02X", num);
  Serial.print(hexCar);
}

void loop() {
  uint8_t status;
  int i;
  int incomingByte = 0;
  uint8_t *mem_addr;
  
  Serial.println("*****************************************************************");
  Serial.println("*********************** Memory Test *****************************");
  Serial.println("*****************************************************************");

  S25FL128.end();

  /*##-1- Configure the device ##########################################*/
  /* Device configuration */
  S25FL128.begin();
  
  status = S25FL128.status();

  if ((status == MEMORY_ERROR) || (status == MEMORY_SUSPENDED) || (status == MEMORY_BUSY))
  {
    Serial.println("Init : FAILED, Test Aborted");
  }
  else
  {
    Serial.println("Init : OK");
    
    S25FL128.read(aRxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);
    for(i=0; i<BUFFER_SIZE; i++){
        Serial.print("0x");
        printHex(aRxBuffer[i]);
        Serial.print(" ");
    }
    Serial.println("");
    Serial.println("-----------------------------------------------------------------");
    
    
    
//    mem_addr = S25FL128.mapped();
//    if(mem_addr != NULL) 
//    {
//        mem_addr += WRITE_READ_ADDR;
//        for(i=0; i<BUFFER_SIZE; i++)
//        {
//            Serial.print("0x");
//            printHex(*mem_addr);
//            Serial.print(" ");
//            mem_addr++;
//        }
//        Serial.println("");
//        Serial.println("-----------------------------------------------------------------");
//    }
  }

  // Enables the de ep power mode

  Serial.println("e: erase the chip");
  Serial.println("s: erase first sector only");
  Serial.println("w: write to chip");

  if (Serial.available() > 0) 
  {
      incomingByte = Serial.read();
      if('e' == incomingByte)
      {
          Serial.print("erasing chip...");
          i = S25FL128.eraseChip();  
          if(i == 0){
            Serial.println("DONE");
          }else{
            Serial.println("FAIL");  
          }
      }

      if('s' == incomingByte)
      {
          Serial.print("erasing sector 1");
          S25FL128.eraseSector(1);
      }

      if('w' == incomingByte)
      {
          S25FL128.write(aTxBuffer, 0xC0, BUFFER_SIZE);
          Serial.println("WRITE : done");
      }
  }
  
  delay(5000);
}

static void Fill_Buffer(uint8_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset)
{
  uint32_t tmpIndex = 0;

  /* Put in global buffer different values */
  for (tmpIndex = 0; tmpIndex < uwBufferLenght; tmpIndex++ )
  {
    pBuffer[tmpIndex] = tmpIndex + uwOffset;
  }
}

static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}
