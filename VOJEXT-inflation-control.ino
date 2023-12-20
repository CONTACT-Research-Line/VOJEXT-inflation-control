#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

#define VALVE1 2
#define VALVE2 3

#define NONE 0
#define RIGHT 1
#define LEFT 2
#define BOTH 3

ros::NodeHandle node_handle;

std_msgs::String button_msg;
std_msgs::UInt16 led_msg;

void subscriberCallback(const std_msgs::UInt8& msg) {
  if (msg.data  == NONE) {
    digitalWrite(VALVE1, LOW);
    digitalWrite(VALVE2, LOW);  
  } 
  else if (msg.data == RIGHT) {
    digitalWrite(VALVE1, HIGH);
    digitalWrite(VALVE2, LOW); 
  } 
  else if (msg.data == LEFT) {
    digitalWrite(VALVE1, LOW);
    digitalWrite(VALVE2, HIGH); 
  }
  else {
    digitalWrite(VALVE1, HIGH);
    digitalWrite(VALVE2, HIGH); 
  }
}

ros::Subscriber<std_msgs::UInt8> inflatable_subscriber("arm/inflate", &subscriberCallback);

void setup()
{
  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE2, OUTPUT);
  
  node_handle.initNode();
  node_handle.subscribe(inflatable_subscriber);
}

void loop()
{ 
  node_handle.spinOnce();  
  delay(100);
}
