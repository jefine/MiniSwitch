#include <ESP8266WiFi.h>
#include <Servo.h>
const char *ssid = "balalanengliang";           //AP的WiFi名字
const char *password = "WuhuLahu-DarkDemonTransformation";  //密码
int led=2;                          //设置指示灯io
Servo servo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);             //设置波特率
  Serial.println("");
  pinMode(led,OUTPUT); 
  digitalWrite(led,1);
  servo.attach(14);                 //PWM引脚设置，与GPIO引脚号对应.
  WiFi.mode(WIFI_AP);                  //设置为AP模式
  servo.write(10);
  
  WiFi.softAP(ssid,password,1,true);          //设置AP信息，并开启AP
//自定义AP的ip段
  IPAddress softLocal(192,168,1,1);    //ip地址，可用以设置ip第4字段
  IPAddress softGateway(192,168,1,1);  //ip网关，第3
  IPAddress softSubnet(255,255,255,0);
//配置自定义IP信息
  WiFi.softAPConfig(softLocal,softGateway,softSubnet);
  IPAddress myIP=WiFi.softAPIP();    //用变量myIP接收AP当前IP地址
  Serial.println(myIP);              //打印出myIP的IP地址
}

void loop() {
  // put your main code here, to run repeatedly:
  int gotoAP=WiFi.softAPgetStationNum();   //获取当前连接到AP的设备数量
  if(gotoAP==0){                           //若没有连接到设备，熄灭LED，否则点亮
    digitalWrite(led,1);
  }else{
    digitalWrite(led,0);
    servo.write(100);
    delay(2000);
    digitalWrite(led,1);
    servo.write(10);
  }
}
