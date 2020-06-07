#include <Wire.h> 
#include <FlagTank.h>
#define STOP 0
#define GO   1
#define TURN 2
#define BACK 3
#define RESTOP 4
char help[][15]={"Press",
                 "  K3 to Start",  
                 "  K0-2 to Stop"};
byte state;
char buf[14]={0};
byte key=0;
byte line=0;
void setup() {
  // put your setup code here, to run once:
  iTank.begin();
  iTank.clearLCD();
  iTank.writeLCD(0, help[0]);
  iTank.writeLCD(1, help[1]);
  iTank.writeLCD(2, help[2]);
  pinMode(13, INPUT);
  #ifdef DEBUG
  Serial.begin(19200);
  Serial.print("---100-");
  delay(100);
  #endif
}

void loop() {
  iTank.readDistanceIR();
  line=0;
   if (analogRead(0)<350){line=line+13;}  //從左邊數第一個(D12)看見
   if (analogRead(1)<350){line=line+16;}  //從左邊數第二個(A1)看見
   if (analogRead(2)<350){line=line+8;}  //從左邊數第三個(A2)看見
   if (analogRead(3)<350){line=line+4;}  //從左邊數第四個(A3)看見
   if (analogRead(6)<350){line=line+2;}  //從左邊數第五個(A6)看見
   if (analogRead(7)<350){line=line+1;}  //從左邊數第六個(A7)看見
   key = iTank.readKey();
   if(key==4) {
    iTank.stop();
  }
   switch(state){
    case STOP:
    if(key==8){
    state=GO;
   }
   break;
    case GO:
      if(line >=30) {
        iTank.stop();
        delay(500);
        state=TURN;}
   else {
    tryFollowLine();
      }
   break;
   case TURN:
   while(line<40)    //BACK FROM T 
   {
   if (analogRead(0)<350){line=line+13;}  //從左邊數第一個(D12)看見
   if (analogRead(1)<350){line=line+16;}  //從左邊數第二個(A1)看見
   if (analogRead(2)<350){line=line+8;}  //從左邊數第三個(A2)看見
   if (analogRead(3)<350){line=line+4;}  //從左邊數第四個(A3)看見
   if (analogRead(6)<350){line=line+2;}  //從左邊數第五個(A6)看見
   if (analogRead(7)<350){line=line+1;}  //從左邊數第六個(A7)看見
   iTank.writeMotor(-1,-1);
   }
   iTank.writeMotor(2,2);
   delay(900);
   iTank.stop();
   iTank.writeMotor(2,-2);    //TURN 45
   delay(1050);
   iTank.stop();//停車
   delay(500);
   iTank.writeMotor(-2,-2);       //Back to frame
   delay(950);
   /**
   iTank.writeMotor(1,-7);
   delay(1230);
   **/
   iTank.stop();
   delay(500);
   while(analogRead(7)>350 and analogRead(6)>350){  //直到左邊碰到線ww
   iTank.writeMotor(-1,-1);  //持續倒車
   }
   iTank.writeMotor(-2,-1);
   delay(300);
   while(analogRead(0)>350 and analogRead(1)>350){
   iTank.writeMotor(-2,1);
   }
   iTank.writeMotor(-1,-1);
   delay(200);
   state= BACK;
   break;
   case BACK:
   if(line >=25) 
   {
       iTank.stop();
       if(analogRead(7)<350)
       {
           while (analogRead(0)>350)
           {
               if (analogRead(0)<350){line=line+1;}
               if (analogRead(1)<350){line=line+2;}
               if (analogRead(2)<350){line=line+4;}
               if (analogRead(3)<350){line=line+8;}
               if (analogRead(6)<350){line=line+16;}
               if (analogRead(7)<350){line=line+13;}
               iTank.writeMotor(0,1);
            }
        }
        else
        {
            while (analogRead(7)>350)
            {
                if (analogRead(0)<350){line=line+1;}
                if (analogRead(1)<350){line=line+2;}
                if (analogRead(2)<350){line=line+4;}
                if (analogRead(3)<350){line=line+8;}
                if (analogRead(6)<350){line=line+16;}
                if (analogRead(7)<350){line=line+13;}
                iTank.writeMotor(1,0);
            }
        }
        iTank.stop();
        state=RESTOP;
   }
   else
   {
       iTank.writeMotor(1,1);
   }
   break;
   case RESTOP:
   iTank.writeMotor(-1,-1);
   delay(300);
   iTank.stop();  //停車
   state=STOP;
   break;
    
}
}
void tryFollowLine(void)
{
  switch(line){
    case 1:  //從左邊數來第六個(A7)看見
       iTank.writeMotor(5,-3);
       break;
    case 3:  //從左邊數來第六個和第五個(A7,A6)看見
        iTank.writeMotor(5,-1);
        break;
    case 2:  //從左邊數來第五個(A6)看見
        iTank.writeMotor(5,0);
        break;
    case 6:  //從左邊數來第五個和第四個(A6,A3)看見
        iTank.writeMotor(7,2);
        break;
    case 4:  //從左邊數來第四個(A3)看見
        iTank.writeMotor(6,2);
        break;
    case 12:  //從左邊數來第四個和第三個(A3,A2)看見
        iTank.writeMotor(7,7);
        break;
    case 8:  //從左邊數來第三個(A2)看見
        iTank.writeMotor(2,6);
        break;
    case 24:  //從左邊數來第三個和第二個(A2,A1)看見
        iTank.writeMotor(2,7);
        break;  
    case 16:  //從左邊數來第二個(A1)看見
        iTank.writeMotor(0,5);
        break;
    case 29:  //從左邊數來第二個和第一個(A1,D12)看見
        iTank.writeMotor(-1,5);
        break;
    case 13:  //從左邊數來第一個(D12)看見
        iTank.writeMotor(-3,5);
        break;         
    }
    delay(20);
}


/**
void tryFollowLine(void)
{
  switch(line){
    case 1:  //從左邊數來第六個(A7)看見
       iTank.writeMotor(4,-4);
       break;
    case 3:  //從左邊數來第六個和第五個(A7,A6)看見
        iTank.writeMotor(4,-2);
        break;
    case 2:  //從左邊數來第五個(A6)看見
        iTank.writeMotor(4,-1);
        break;
    case 6:  //從左邊數來第五個和第四個(A6,A3)看見
        iTank.writeMotor(6,1);
        break;
    case 4:  //從左邊數來第四個(A3)看見
        iTank.writeMotor(5,1);
        break;
    case 12:  //從左邊數來第四個和第三個(A3,A2)看見
        iTank.writeMotor(7,7);
        break;
    case 8:  //從左邊數來第三個(A2)看見
        iTank.writeMotor(1,5);
        break;
    case 24:  //從左邊數來第三個和第二個(A2,A1)看見
        iTank.writeMotor(1,6);
        break;  
    case 16:  //從左邊數來第二個(A1)看見
        iTank.writeMotor(-1,4);
        break;
    case 48:  //從左邊數來第二個和第一個(A1,D12)看見
        iTank.writeMotor(-2,4);
        break;
    case 32:  //從左邊數來第一個(D12)看見
        iTank.writeMotor(-4,4);
        break;         
    }
    delay(20);
}
**/
