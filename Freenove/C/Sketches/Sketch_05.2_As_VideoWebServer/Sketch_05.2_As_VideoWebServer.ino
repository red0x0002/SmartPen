#include "esp_camera.h"
#include <WiFi.h>
#include "BluetoothSerial.h"
//
// WARNING!!! PSRAM IC required for UXGA resolution and high JPEG quality
//            Ensure ESP32 Wrover Module or other board with PSRAM is selected
//            Partial images will be transmitted if image exceeds buffer size
//

// Select camera model
#define CAMERA_MODEL_WROVER_KIT // Has PSRAM

#include "camera_pins.h"

const char* ssid     = "MyNetworkShare";   //input your wifi name
const char* password = "Wayne911911";   //input your wifi passwords

void startCameraServer();

bool is_initialised = false;

void setup() {
  Serial.begin(921600);
  Serial.setDebugOutput(true);
  Serial.println();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  // drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_VGA);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
  //Serial.println("WiFi connected");

  startCameraServer();

  //camera_fb_t* cam = esp_camera_fb_get();
  
  //Serial.print("Format: ");
  //Serial.print(cam->format);
  //Serial.println();

  //for(int i = 0; i < cam->len; i++)
  //{
  //  Serial.print(cam->buf[i], HEX);
  //  Serial.print(" ");
  //}

  /*Serial.println();
  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");*/

  is_initialised = true;
}

void loop() {
  // put your main code here, to run repeatedly:

  if(!is_initialised)
  {
    if(!is_initialised)
      return;
  }
  delay(15000);

  camera_fb_t* cam = esp_camera_fb_get();
  if(!cam || !cam->buf || !cam->len)
  {
    Serial.print("Invalid Data\n");
    return;
  }

  for(int i = 0; i < cam->len; i++)
  {
    Serial.print("0x");
    Serial.print(cam->buf[i], HEX);
    Serial.print(" ");
  }

  esp_camera_fb_return(cam);
  cam = 0;
  Serial.println();
  //Serial.print("Helo\n");
  return;
}
