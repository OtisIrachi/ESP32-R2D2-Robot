//********************************************************************************
// R2D2IR.ino
// For ESP32 D1 Mini
// Works well as a WiFi DC Motor Drive System. 
// Uses 4 "arrow" buttons for steering.
// Direction controls also for head movement.
// Set TMC2209 stepper driver MS1 and MS2 to GND for 1/8 steps.
// 28BYJ-48 = 64:1 gear ratio,  With 1/16 stepping = 32768 pulses per Rev.
// With 1/8 stepping = 16384 pulses per Rev.  
// 
// by RCI
//
// 7-14-2025  
//********************************************************************************

//********************************************************************************
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <sstream>
#include <Tone32.h>
#include <AccelStepper.h>
#include "ircodes.h"
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
//***************************************************************
// RCI MotherBoard Pinouts
//***************************************************************
//
// *** ESP32 D1 Mini Board Pinouts ***
// Only working I/O Pins are listed here.
//
//                        IO#      Board Label
#define ledPin            2     // IN/OUT  (IO2)    
#define speakerPin        4     // IN/OUT  (IO4)    
#define X_ENABLE_PIN      5     // IN/OUT  (D8-CS) 
#define X_STEP_PIN        18    // IN/OUT  (D5-SCK)    
#define X_DIR_PIN         19    // IN/OUT  (D6-MISO)  
#define SDA               21    // D21     (D2-SDA)    
#define SCL               22    // D22     (D1-SCL)    
   
#define IN1               16
#define IN2               17
#define IN3               27
#define IN4               32
#define MOTOR_ENA         25
#define MOTOR_ENB         33  

#define BUZZER_CHANNEL    0

#define ZERO   0
#define FOR    1
#define REV    2
#define LEFT   3
#define RIGHT  4
#define CENTER 5
#define STOP   88
#define motorInterfaceType 1    // Used for AccelStepper 

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int PWMSpeedChannel = 2;
const int PWMLightChannel = 3;

// IR Stuff
const uint16_t kRecvPin = 23;   // D7-MOSI ESP32
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t  kTimeout = 50;
unsigned long irButton;
int lastCase;
unsigned char prognum = 0;

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;

float tempspeed;
float motorspeed;
int headPosition;
int headDistance = 0;
bool headLatchL = 0;
bool headLatchR = 0;
int timeCount = 0;

const char *ssid = "R2D2WiFi";
IPAddress    apIP(192,168,4,1);

AsyncWebServer server(80);
AsyncWebSocket wsCarInput("/CarInput");

// Create a new instance of the AccelStepper class:
AccelStepper stepperX = AccelStepper(motorInterfaceType, X_STEP_PIN, X_DIR_PIN);
//************************************************************************************************
// delayms (loops) Milliseconds if using ESPAlexa
void delayms(int loops) 
{
unsigned long time_now = 0;
    time_now = millis();
    
    while(millis() < time_now + loops)
      {       
      if (irrecv.decode(&results)) 
        {
        serialPrintUint64(results.value, HEX);
        Serial.println(" delayms");
        irButton = results.value;
        Process_IR(); 
        irrecv.resume();  // Receive the next value              
        }
      delay(1);   
      }  
}
//****************************************************************************
void Process_IR()
{
  //**************************************** 
  switch(irButton)
  {
    //*****************************
    case IRButton0: // 
      //prognum = 0;    
    break;    
    //*****************************
    case IRButton1: // 
      prognum = 1;    
    break;
    //*****************************
    case IRButton2: // 
      prognum = 2;    
    break;
    //*****************************
    case IRButton3: // 
      prognum = 3;    
    break;
    //*****************************
    case IRButton4: // 
      prognum = 4;    
    break;
    //*****************************
    case IRButton5: // 
      prognum = 5;    
    break; 
    //*****************************
    case IRButton6: // 
      prognum = 6;    
    break;       
    //*****************************
    case IRButton7: // 
      prognum = 7;    
    break;
    //*****************************
    case IRButton8: // 
      prognum = 8;    
    break;    
    //*****************************
    case IRButton9: // 
      prognum = 9;    
    break;
    //*****************************
    case IRButton10: // 
      prognum = 10;    
    break;
    //*****************************
    case IRButton11: // 
      prognum = 11;    
    break; 
    //*****************************
    case IRButton12: // 
      prognum = 12;    
    break; 
    //*****************************
    case IRButton13: // 
      prognum = 13;    
    break;               
    //*****************************
    case IRButton14: // 
      prognum = 14;    
    break;
    //*****************************
    case IRButton15: // 
      prognum = 15;    
    break;
    //*****************************
    case IRButton16: // 
      prognum = 16;    
    break;
    //*****************************
    case IRButton17: // 
      prognum = 17;    
    break;    
    //*****************************
    case IRButton18: // 
      prognum = 18;    
    break;
    //*****************************
    case IRButton19: // 
      prognum = 19;    
    break; 
    //*****************************
    case IRButton20: // 
      prognum = 20;    
    break;        
    //*****************************
    default:   
    
    break;    
    //*****************************
    
    }// End Switch  
    //**************************************** 
    
    irButton = 0;
}
//****************************************************************************
void Read_IR()
{
  if (irrecv.decode(&results)) 
    {
    serialPrintUint64(results.value, HEX);
    //Serial.println(results.value);
    Serial.println("");
    irButton = results.value;
    irrecv.resume();  // Receive the next value
    }// End if (irrecv)  
   
}// End Read_IR
//********************************************************************************
const char* htmlHomePage PROGMEM = R"HTMLHOMEPAGE(
<!DOCTYPE html>
<html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <style>
    .arrows {
      font-size:30px;
      color:red;
    }
    td.button {
      background-color:black;
      border-radius:25%;
      box-shadow: 5px 5px #888888;
    }
    td.button:active {
      transform: translate(5px,5px);
      box-shadow: none; 
    }

    .noselect {
      -webkit-touch-callout: none; /* iOS Safari */
        -webkit-user-select: none; /* Safari */
         -khtml-user-select: none; /* Konqueror HTML */
           -moz-user-select: none; /* Firefox */
            -ms-user-select: none; /* Internet Explorer/Edge */
                user-select: none; /* Non-prefixed version, currently
                                      supported by Chrome and Opera */
    }

    .slidecontainer {
      width: 100%;
    }

    .slider {
      -webkit-appearance: none;
      width: 100%;
      height: 15px;
      border-radius: 5px;
      background: #d3d3d3;
      outline: none;
      opacity: 0.7;
      -webkit-transition: .2s;
      transition: opacity .2s;
    }

    .slider:hover {
      opacity: 1;
    }
  
    .slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 25px;
      height: 25px;
      border-radius: 50%;
      background: red;
      cursor: pointer;
    }

    .slider::-moz-range-thumb {
      width: 25px;
      height: 25px;
      border-radius: 50%;
      background: red;
      cursor: pointer;
    }

    </style>
  
  </head>
  <body class="noselect" align="center" style="background-color:white">
    <table id="mainTable" style="width:300px;margin:auto;table-layout:fixed" CELLSPACING=10>     
      <tr>
        <td></td>
        <td style="text-align:left"><b>R2D2 Direction:</b></td>
      </tr>
      <tr>  
        <td></td>
        <td class="button" ontouchstart='sendButtonInput("MoveCar","1")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows" >&#8679;</span></td>
        <td></td>
      </tr>
      <tr>
        <td class="button" ontouchstart='sendButtonInput("MoveCar","3")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows" >&#8678;</span></td>
        <td class="button"></td>    
        <td class="button" ontouchstart='sendButtonInput("MoveCar","4")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows" >&#8680;</span></td>
      </tr>
      <tr>
        <td></td>
        <td class="button" ontouchstart='sendButtonInput("MoveCar","2")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows" >&#8681;</span></td>
        <td></td>
      </tr>
      <tr>
        <td></td>
        <td style="text-align:left"><b>Head:</b></td>
      </tr>
      <tr>  
        <td class="button" ontouchstart='sendButtonInput("butHead","3")' ontouchend='sendButtonInput("butHead","0")'><span class="arrows" >&#8678;</span></td>
        <td class="button" ontouchstart='sendButtonInput("butHead","5")' ontouchend='sendButtonInput("butHead","0")'></td>  
        <td class="button" ontouchstart='sendButtonInput("butHead","4")' ontouchend='sendButtonInput("butHead","0")'><span class="arrows" >&#8680;</span></td>
      </tr>    
      <tr/><tr/>
      <tr>
        <td style="text-align:left"><b>Speed:</b></td>
        <td colspan=2>
         <div class="slidecontainer">
            <input type="range" min="100" max="2500" value="1200" class="slider" id="Speed" oninput='sendButtonInput("Speed",value)'>
          </div>
        </td>
      </tr>        
      <tr>
        <td style="text-align:left"><b>Light:</b></td>
        <td colspan=2>
          <div class="slidecontainer">
            <input type="range" min="0" max="255" value="0" class="slider" id="Light" oninput='sendButtonInput("Light",value)'>
          </div>
        </td>   
      </tr>
      <tr>
        <td style="text-align:left"><b>Head:</b></td>
        <td colspan=2>
          <div class="slidecontainer">
            <input type="range" min="-8000" max="8000" value="0" class="slider" id="Head" oninput='sendButtonInput("Head",value)'>
          </div>
        </td>   
      </tr>             
    </table>
  
    <script>
      var webSocketCameraUrl = "ws:\/\/" + window.location.hostname + "/Camera";
      var webSocketCarInputUrl = "ws:\/\/" + window.location.hostname + "/CarInput";      
      var websocketCamera;
      var websocketCarInput;
      
      function initCameraWebSocket() 
        {
        websocketCamera = new WebSocket(webSocketCameraUrl);
        websocketCamera.binaryType = 'blob';
        websocketCamera.onopen    = function(event){};
        websocketCamera.onclose   = function(event){setTimeout(initCameraWebSocket, 2000);};
        websocketCamera.onmessage = function(event)
          {
          var imageId = document.getElementById("cameraImage");
          imageId.src = URL.createObjectURL(event.data);
          };
        }
      
      function initCarInputWebSocket() 
        {
        websocketCarInput = new WebSocket(webSocketCarInputUrl);
        websocketCarInput.onopen    = function(event)
          {
          sendButtonInput("Speed", document.getElementById("Speed").value);
          sendButtonInput("Light", document.getElementById("Light").value);
          sendButtonInput("Pan", document.getElementById("Pan").value);
          sendButtonInput("Tilt", document.getElementById("Tilt").value);                    
          };
        websocketCarInput.onclose   = function(event){setTimeout(initCarInputWebSocket, 2000);};
        websocketCarInput.onmessage = function(event){};        
        }
      
      function initWebSocket() 
        {
        initCameraWebSocket ();
        initCarInputWebSocket();
        }

      function sendButtonInput(key, value) 
        {
        var data = key + "," + value;
        websocketCarInput.send(data);
        }
    
      window.onload = initWebSocket;
      document.getElementById("mainTable").addEventListener("touchend", function(event){
        event.preventDefault()
      });      
    </script>
  </body>    
</html>
)HTMLHOMEPAGE";
//*********************************************************************
// Left Forward
void r2Voice(int pgm)
{

    int K = 1000;  // lowest frequency
    switch (pgm) 
        {       
        case 1:phrase1(); break;
        case 2:phrase2(); break;
        case 3:phrase1(); phrase2(); break;
        case 4:phrase1(); phrase2(); phrase1();break;
        case 5:phrase1(); phrase2(); phrase1(); phrase2(); phrase1();break;
        case 6:phrase2(); phrase1(); phrase2(); break;
        }
        
    for (int i = 0; i <= random(3, 20); i++)
        {        
        digitalWrite(ledPin, HIGH);  
        tone(speakerPin, K + random(-1700, 2000), 0, BUZZER_CHANNEL);           
        delay(random(70, 170));  
        digitalWrite(ledPin, LOW);           
        noTone(speakerPin, BUZZER_CHANNEL);         
        delay(random(0, 30));             
        } 
        
    noTone(speakerPin, BUZZER_CHANNEL); 
    Serial.println("Sound Completed!");       
 
}
//*********************************************************************
void phrase1() 
{
    
    int k = random(1000,2000);
    digitalWrite(ledPin, HIGH);
    
    for (int i = 0; i <=  random(100,2000); i++)
        {
        tone(speakerPin, k + (-i * 2), 0, BUZZER_CHANNEL);         
        delay(random(.9, 2));             
        } 
    digitalWrite(ledPin, LOW);   
    
    for (int i = 0; i <= random(100,1000); i++)
        {        
        tone(speakerPin, k + (i * 10), 0, BUZZER_CHANNEL);          
        delay(random(.9, 2));             
        } 
}
//*********************************************************************
void phrase2() 
{
    
    int k = random(1000,2000);
    digitalWrite(ledPin, HIGH);  
    
    for (int i = 0; i <= random(100,2000); i++)
        {       
        tone(speakerPin, k + (i * 2), 0, BUZZER_CHANNEL);          
        delay(random(.9, 2));             
        } 
    digitalWrite(ledPin, LOW); 
      
    for (int i = 0; i <= random(100,1000); i++)
        {        
        tone(speakerPin, k + (-i * 10), 0, BUZZER_CHANNEL);        
        delay(random(.9, 2));             
        } 
}
//*********************************************************************
void butHead(int inputValue)
{
   
  switch(inputValue)
    {
    case ZERO:
      return;
    break;    
    
    case LEFT:
      headLatchL = 1;
      headLatchR = 0;
    break;
  
    case RIGHT:
      headLatchL = 0;
      headLatchR = 1;    
    break;
 
    case CENTER: 
    headDistance = 0; 
    headLatchL = 0;
    headLatchR = 0;
    return;        
    break;
    }

   if(headLatchR == 1) 
      {
      headDistance = headDistance + 1000;
      if(headDistance >= 6000) headDistance = 6000;     
      }
      
   if(headLatchL == 1) 
      {
      headDistance = headDistance - 1000;
      if(headDistance <= -6000) headDistance = -6000;     
      } 
   Serial.print("butHead: "); Serial.print(headDistance);      
   stepperX.moveTo(headDistance);
 
}
//*********************************************************************
void moveHead(int distance, int inputValue)
{
    
  switch(inputValue)
    {
    case LEFT:
      stepperX.moveTo(distance); 
    break;
  
    case RIGHT:
      stepperX.moveTo(distance);      
    break;
 
    case STOP: 
         
    break;
    }
    
  Serial.print("moveHead: "); Serial.println(distance); 
}
//********************************************************************************
void moveBOT(int inputValue)
{

  switch(inputValue)
    {
    case FOR:
    //Serial.println("FOR: ");
    digitalWrite(IN1, 1);   // motor 1 forward
    digitalWrite(IN2, 0);   // motor 1 forward
    digitalWrite(IN3, 0);   // motor 2 backward
    digitalWrite(IN4, 1);   // motor 2 backward                   
    break;
  
    case REV:
    //Serial.println("DN: ");
    digitalWrite(IN1, 0);   // motor 1 backward
    digitalWrite(IN2, 1);   // motor 1 backward
    digitalWrite(IN3, 1);   // motor 2 forward
    digitalWrite(IN4, 0);   // motor 2 forward  
    break;
  
    case LEFT:
    digitalWrite(IN1, 1);   // motor 1 forward
    digitalWrite(IN2, 0);   // motor 1 forward
    digitalWrite(IN3, 1);   // motor 2 forward
    digitalWrite(IN4, 0);   // motor 2 forward       
    break;
  
    case RIGHT:
    digitalWrite(IN1, 0);   // motor 1 backward
    digitalWrite(IN2, 1);   // motor 1 backward
    digitalWrite(IN3, 0);   // motor 2 backward
    digitalWrite(IN4, 1);   // motor 2 backward     
    break;
 
    case STOP: 
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);            
    break;
  
    default:   
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);         
    break;
    }
}
//********************************************************************************
void handleRoot(AsyncWebServerRequest *request) 
{
  request->send_P(200, "text/html", htmlHomePage);
}
//********************************************************************************
void handleNotFound(AsyncWebServerRequest *request) 
{
    request->send(404, "text/plain", "File Not Found");
}
//********************************************************************************
void onCarInputWebSocketEvent(AsyncWebSocket *server, 
                      AsyncWebSocketClient *client, 
                      AwsEventType type,
                      void *arg, 
                      uint8_t *data, 
                      size_t len) 
{                      
  switch (type) 
    {
    case WS_EVT_CONNECT:
      //Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      //Serial.printf("WebSocket client #%u disconnected\n", client->id());
      moveBOT(0);
      ledcWrite(PWMLightChannel, 0); 
      //headServo.write(90);
      //tiltServo.write(90);       
      break;
    case WS_EVT_DATA:
      AwsFrameInfo *info;
      info = (AwsFrameInfo*)arg;
      if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) 
        {
        std::string myData = "";
        myData.assign((char *)data, len);
        std::istringstream ss(myData);
        std::string key, value;
        std::getline(ss, key, ',');       // GET NAME FROM SLIDER
        std::getline(ss, value, ',');     // GET VALUE FROM SLIDER
        //Serial.printf("Key [%s] Value[%s]\n", key.c_str(), value.c_str()); 
        int valueInt = atoi(value.c_str());  

        
        if (key == "MoveCar")
          {
          moveBOT(valueInt);        
          }
        if (key == "butHead")
          {        
          butHead(valueInt); 
          r2Voice(random(1,7));        
          }          
        else if (key == "Speed")
          {
          ledcWrite(PWMSpeedChannel, valueInt);
          //Serial.print("Speed: "); Serial.println(valueInt);
          }
        else if (key == "Light")
          {
          ledcWrite(PWMLightChannel, valueInt);  
          r2Voice(random(1,7));          
          //Serial.print("Light: "); Serial.println(valueInt);       
          }
        else if (key == "Head")
          {        
          headPosition = valueInt;
          moveHead(headPosition, 3);        
          }         
        else
          {
          
          }           
        }
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
    default:
      break;  
    }
}
//********************************************************************************
void setUpPinModes()
{
  //Set up PWM
  ledcSetup(PWMSpeedChannel, PWMFreq, PWMResolution);
  ledcSetup(PWMLightChannel, PWMFreq, PWMResolution);  

  ledcAttachPin(ledPin, PWMLightChannel);
  ledcAttachPin(MOTOR_ENA, PWMSpeedChannel);
  ledcAttachPin(MOTOR_ENB, PWMSpeedChannel);   
  
  //moveBOT(STOP);
  pinMode(IN1, OUTPUT);     
  pinMode(IN2, OUTPUT);     
  pinMode(IN3, OUTPUT);     
  pinMode(IN4, OUTPUT);    
  pinMode(MOTOR_ENA, OUTPUT);     
  pinMode(MOTOR_ENB, OUTPUT);       
  digitalWrite(MOTOR_ENA, 0);     
  digitalWrite(MOTOR_ENB, 0); 
  
  pinMode(ledPin, OUTPUT);   
   
}
//********************************************************************************
void setup(void) 
{
  setUpPinModes();
  Serial.begin(115200);
  // Wifi to access point mode.
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); 
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();

  irrecv.enableIRIn();  // Start the receiver

  stepperX.setCurrentPosition(0);
  // Change these to suit your stepper if you want
  stepperX.setMaxSpeed(20000);
  stepperX.setAcceleration(8000);
  pinMode(X_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN, LOW); // enable all steppers     
  tempspeed = 0;

  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);
      
  wsCarInput.onEvent(onCarInputWebSocketEvent);
  server.addHandler(&wsCarInput);

  server.begin();
  headDistance = 0;

}
//********************************************************************************
void loop() 
{

  Read_IR();
  Process_IR();


  //************************************************
  switch(prognum)
  {
    
    //*****************************
    case 0:

    ledcWrite(PWMSpeedChannel, 0);
    
    break;
    //*****************************
    case 1:

    Serial.println(String(remoteButtonName[prognum]));  
    
   
    break;    
    //*****************************
    case 2:

    Serial.println(String(remoteButtonName[prognum])); 
    
   
    break;
    //*****************************
    case 3:
        
    Serial.println(String(remoteButtonName[prognum])); 
    

    break;
    //*****************************
    case 4:

    Serial.println(String(remoteButtonName[prognum]));  
     

    break;
    //*****************************
    case 5:
      
    Serial.println(String(remoteButtonName[prognum])); 
    

    break;
    //*****************************
    case 6:
      
    Serial.println(String(remoteButtonName[prognum])); 
      

    break;    
    //*****************************
    case 7: // FOR

    Serial.println(String(remoteButtonName[prognum])); 
    ledcWrite(PWMSpeedChannel, 2500);
    moveBOT(FOR);

    break;
    //*****************************
    case 8:
 
    Serial.println(String(remoteButtonName[prognum])); 
    

    break; 
    //*****************************
    case 9: // LEFT

    Serial.println(String(remoteButtonName[prognum])); 
    ledcWrite(PWMSpeedChannel, 2500);
    moveBOT(LEFT); 
     

    break; 
    //*****************************
    case 10: // STOP

    Serial.println(String(remoteButtonName[prognum])); 
    ledcWrite(PWMSpeedChannel, 0);
    prognum = 0;
    moveBOT(STOP);

    break;    
    //*****************************
    case 11: // RIGHT

    Serial.println(String(remoteButtonName[prognum])); 
    ledcWrite(PWMSpeedChannel, 2500);
    moveBOT(RIGHT);

    break;
    //*****************************
    case 12: // DomeLEFT
 
    Serial.println(String(remoteButtonName[prognum])); 
    headDistance = headDistance - 2000;
    if(headDistance <= -6000) headDistance = -6000;         
    stepperX.moveTo(headDistance);
    prognum = 99;
        
    break;
    //*****************************
    case 13: // REV

    Serial.println(String(remoteButtonName[prognum])); 
    ledcWrite(PWMSpeedChannel, 2500);
    moveBOT(REV);
    
    break;
    //*****************************
    case 14: // DomeRIGHT

    Serial.println(String(remoteButtonName[prognum]));   
    headDistance = headDistance + 2000;
    if(headDistance >= 6000) headDistance = 6000;         
    stepperX.moveTo(headDistance);
    prognum = 99;

    break; 
    //*****************************
    case 15: //Projector Light ON

    Serial.println(String(remoteButtonName[prognum])); 
    ledcWrite(PWMLightChannel, 255);   

    break; 
    //*****************************
    case 16: //Projector Light OFF
 
    Serial.println(String(remoteButtonName[prognum])); 
    ledcWrite(PWMLightChannel, 0);  

    break; 
    //*****************************
    case 17:

    Serial.println(String(remoteButtonName[prognum])); 
     

    break; 
    //*****************************
    case 18:
 
    Serial.println(String(remoteButtonName[prognum])); 
    

    break; 
    //*****************************
    case 19:
 
    Serial.println(String(remoteButtonName[prognum])); 
    

    break; 
    //*****************************
    case 20:

    Serial.println(String(remoteButtonName[prognum])); 
    

    break; 
    //*****************************
    case 99:

    r2Voice(random(1,7));    
    prognum = 0; 

    break;                                                        
    //*****************************
    default:  
 

    
    break;
    //***************************** 

  }// End Switch
  //**************************************** 

  timeCount++;
  if(timeCount >= 600000000)
     {
     timeCount = 0;
     r2Voice(random(1,7));
     }

  wsCarInput.cleanupClients(); 
  stepperX.run(); // non-blocking execution
 
}// End Loop
//********************************************************************************
