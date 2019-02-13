#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_BUILTIN 7
#define KAIGUAN 6

//读出来的16进制uid
String  g_uid;
String passwd_uid[4] = {"75136140101","24524570119","21815213197","691631126"};
MFRC522 rfid(SS_PIN, RST_PIN); //实例化类
 
// 初始化数组用于存储读取到的NUID 
byte nuidPICC[4];
 
void setup() { 
  pinMode(LED_BUILTIN, OUTPUT);
   pinMode(KAIGUAN, INPUT);
  Serial.begin(9600);
  SPI.begin(); // 初始化SPI总线
  rfid.PCD_Init(); // 初始化 MFRC522 
}
 
void loop() {
  int Pin = 0;
Pin =  digitalRead(KAIGUAN);
if(Pin==HIGH){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }

 
  // 找卡
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
 
  // 验证NUID是否可读
  if ( ! rfid.PICC_ReadCardSerial())
    return;
 
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
 
  // 检查是否MIFARE卡类型
//  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
//    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
//    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
//    Serial.println("不支持读取此卡类型");
//    return;
//  }
  
  // 将NUID保存到nuidPICC数组
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }   
  Serial.print("十六进制UID：");
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  
  Serial.print("十进制UID：");
  printDec(rfid.uid.uidByte, rfid.uid.size);

  


  // 使放置在读卡区的IC卡进入休眠状态，不再重复读卡
  rfid.PICC_HaltA();
 
  // 停止读卡模块编码
  rfid.PCD_StopCrypto1();
}
 
void printHex(byte *buffer, byte bufferSize) {
String  uid;
  for (byte i = 0; i < bufferSize; i++) {
//    Serial.print(buffer[i] < 0x10 ? " 0" : "");
//    Serial.print(buffer[i], HEX);
    uid = uid + buffer[i];
  }
Serial.println(uid);
g_uid = uid;
uid = "";


for(int i =0;i<4; i++){
  if(passwd_uid[i]==g_uid){
    Serial.println("----");
    Serial.println(passwd_uid[i]);
     Serial.println("----");
       Serial.println(g_uid);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
       
    }
  
  }
}
 
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : "");
  Serial.print(buffer[i], DEC);
  }

}

//void openDoor(byte *buffer, byte bufferSize, cardUid){
//  
//  for (byte i = 0; i < bufferSize; i++) {
//
//    Serial.print(buffer[i], HEX);
//  }
//  
//  }
