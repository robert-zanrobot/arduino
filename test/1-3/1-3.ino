#include <pt.h>
     
    static int counter1,counter2,state1=0,state2=0;
     
    static int protothread1(struct pt *pt)
    {  
      PT_BEGIN(pt);  
      while(1)
      {  
        PT_WAIT_UNTIL(pt, counter1==1);
        digitalWrite(12,state1);
        state1=!state1;
        counter1=0;   
      }
      PT_END(pt);
    }
     
     
    static int protothread2(struct pt *pt)
    {
      PT_BEGIN(pt);
      while(1) {   
        PT_WAIT_UNTIL(pt, counter2==5);
        counter2=0;
        digitalWrite(13,state2);
        state2=!state2;
      }
      PT_END(pt);
    }
     
     
    static struct pt pt1, pt2;
    void setup()
    {
     
      pinMode(12,OUTPUT);
      pinMode(13,OUTPUT);
      PT_INIT(&pt1);
      PT_INIT(&pt2);
    }
     
    void loop ()
    {
        protothread1(&pt1);
        protothread2(&pt2);
        delay(1000);
        counter1++;
        counter2++;
      }