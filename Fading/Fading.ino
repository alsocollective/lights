
int pannel = -1;
//setters 
int r1o = -1;
int g1o = -1;
int b1o = -1;
//faders
int r1f = -1;
int g1f = -1;
int b1f = -1;
//setters 
int r2o = -1;
int g2o = -1;
int b2o = -1;
//faders
int r2f = -1;
int g2f = -1;
int b2f = -1;
//variables
int transitionspeed = 50;


void setup()  { 
  Serial.begin(9600);
  while (!Serial) {
  }  
  establishContact();
} 

void loop()  {
  if(pannel == -1){
    Serial.println("READY"); 
    delay(300); 
  }
  if (Serial.available() > 0) {
    //establish what the next bits are going to be... (this would be the first bit)
    /*
      1 == setting pannel 1 values, is expecting 3 more bytes
      2 == setting pannel 2 values, is expecting 3 more bytes
      3 == fade to pannel 1 colours is not expecting any more bytes
      4 == fade to pannel 2 colours is not expecting any more bytes
      5 == fade both pannels, is not expecting any more bytes
      6 == set the speed at which the backgrounds are tansitioned
    */
    if(pannel == -1){
      pannel = Serial.read();
      if(pannel == 1){
        reset1();        
        Serial.println(" set colour for 1 ");  
      } else if(pannel == 2){
        reset2();
        Serial.println(" set colour for 2 ");   
      } else if(pannel == 6){
         transitionspeed = -1;       
      } else if(pannel > 6){
         respond();
      }
    }
    if(pannel == 1){
      if(r1o == -1){
        r1o = Serial.read();
      } else if(g1o == -1) {
        g1o = Serial.read();
      } else {
        b1o = Serial.read();
        Serial.print("set colour 1: ");
        Serial.print(r1o);
        Serial.print(" ");
        Serial.print(g1o);
        Serial.print(" ");
        Serial.println(b1o);        
        respond();
      }
    } else if(pannel == 2){
      if(r2o == -1){
        r2o = Serial.read();
      } else if(g2o == -1) {
        g2o = Serial.read();
      } else {
        b2o = Serial.read();
        Serial.print("set colour 2: ");
        Serial.print(r2o);
        Serial.print(" ");
        Serial.print(g2o);
        Serial.print(" ");
        Serial.println(b2o);         
        respond();
      }
    } else if(pannel == 3){
      fade1();
    } else if(pannel == 4){
      fade2();
    }  else if(pannel == 5){
      fade3();
    } else if(pannel == 6){
      Serial.println("set speed");
      transitionspeed = Serial.read();
      if(transitionspeed != -1){
        Serial.print("changed speed to:");
        Serial.println(transitionspeed);
        respond();
      }
    }

    
//    if(r != -1 && g != -1 && b != -1){
//      setColours();
//      delay(10);
//      respond();
//    }       
  }  
}

void reset1(){
  r1o = -1;
  g1o = -1;
  b1o = -1;  
  Serial.println(" reset 1 ");
}
void reset2(){  
  r2o = -1;
  g2o = -1;
  b2o = -1;  
  Serial.println(" restd 2 ");    
}

void fade1(){
  Serial.print(" fadding 1: "); 
  Serial.print(r1o);
  Serial.print(" ");
  Serial.print(g1o);
  Serial.print(" ");  
  Serial.print(b1o);
  Serial.print(" from:");
  Serial.print(r1f);
  Serial.print(" ");
  Serial.print(g1f);
  Serial.print(" ");  
  Serial.println(b1f); 
  while(true){
    if(r1o > r1f){
      ++r1f;
    } else if(r1o < r1f){
      --r1f;
    }
    if(g1o > g1f){
      ++g1f;
    } else if(g1o < g1f){
      --g1f;
    }
    if(b1o > b1f){
      ++b1f;
    } else if(b1o < b1f){
      --b1f;
    } 
    delay(transitionspeed);
    analogWrite(3, b1f);
    analogWrite(5, r1f);
    analogWrite(6, g1f);
    if(((r1o == r1f) && (g1o == g1f)) && (b1o == b1f)){
      break;
    }  
  }
  Serial.println("finnished fadding");  
  respond();
}

void fade2(){
  Serial.print(" fadding 2: "); 
  Serial.print(r2o);
  Serial.print(" ");
  Serial.print(g2o);
  Serial.print(" ");  
  Serial.print(b2o);
  Serial.print(" from:");
  Serial.print(r2f);
  Serial.print(" ");
  Serial.print(g2f);
  Serial.print(" ");  
  Serial.println(b2f); 
  
  while(true){
    if(r2o > r2f){
      ++r2f;
    } else if(r2o < r2f){
      --r2f;
    }
    if(g2o > g2f){
      ++g2f;
    } else if(g2o < g2f){
      --g2f;
    }
    if(b2o > b2f){
      ++b2f;
    } else if(b2o < b2f){
      --b2f;
    }
    delay(transitionspeed);
    analogWrite(9, b2f);
    analogWrite(10, r2f);
    analogWrite(11, g2f);
    if(r2o==r2f && g2o==g2f && b2o==b2f){
      break;
    }
  }
  Serial.println("finnished fadding");  
  respond();
}

void fade3(){
  Serial.println(" fadding both... ");
  Serial.print(" fadding 1: "); 
  Serial.print(r1o);
  Serial.print(" ");
  Serial.print(g1o);
  Serial.print(" ");  
  Serial.print(b1o);
  Serial.print(" from:");
  Serial.print(r1f);
  Serial.print(" ");
  Serial.print(g1f);
  Serial.print(" ");  
  Serial.println(b1f);   
  Serial.print(" fadding 2: "); 
  Serial.print(r2o);
  Serial.print(" ");
  Serial.print(g2o);
  Serial.print(" ");  
  Serial.print(b2o);
  Serial.print(" from:");
  Serial.print(r2f);
  Serial.print(" ");
  Serial.print(g2f);
  Serial.print(" ");  
  Serial.println(b2f);   
  while(true){
    if(r1o > r1f){
      ++r1f;
    } else if(r1o < r1f){
      --r1f;
    }
    if(g1o > g1f){
      ++g1f;
    } else if(g1o < g1f){
      --g1f;
    }
    if(b1o > b1f){
      ++b1f;
    } else if(b1o < b1f){
      --b1f;
    }    
    if(r2o > r2f){
      ++r2f;
    } else if(r2o < r2f){
      --r2f;
    }
    if(g2o > g2f){
      ++g2f;
    } else if(g2o < g2f){
      --g2f;
    }
    if(b2o > b2f){
      ++b2f;
    } else if(b2o < b2f){
      --b2f;
    }
    delay(transitionspeed);
    analogWrite(3, b1f);
    analogWrite(5, r1f);
    analogWrite(6, g1f);    
    analogWrite(9, b2f);
    analogWrite(10, r2f);
    analogWrite(11, g2f);
    if(r2o==r2f && g2o==g2f && b2o==b2f && r1o==r1f && g1o==g1f && b1o==b1f){
      break;
    }
  }
  Serial.println("finnished fadding");  
  respond();
}


void setColours(){
  if(pannel = 1){
   analogWrite(3, b1f);
   analogWrite(5, r1f);
   analogWrite(6, g1f);
  } if(pannel = 2){
   analogWrite(9, b2f);
   analogWrite(10, r2f);
   analogWrite(11, g2f); 
  }
}

void respond(){
    Serial.print("finshed working on setting: ");
    Serial.println(pannel);    
    pannel = -1;
}

void establishContact() {
    Serial.println('Established Connection');
}
