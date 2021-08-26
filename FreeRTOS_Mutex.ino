
#include <Arduino_FreeRTOS.h> 
#include <semphr.h> 

volatile bool LED = false;
int count = 0;

SemaphoreHandle_t mutex; 
void setup() { 

    pinMode(13, OUTPUT);
    
    Serial.begin(9600); 
    //Create Mutex Here
    mutex = xSemaphoreCreateMutex(); 
    
    if (mutex == NULL) { 
        Serial.println("Mutex Error"); 
    } 
    xTaskCreate(Task1, "Task1", 128, NULL, 1, NULL); 
    xTaskCreate(Task2, "Task2", 128, NULL, 1, NULL); 
} 
 
void Task1(void *pvParameters) { 
    while(1) { 
        xSemaphoreTake(mutex, portMAX_DELAY); 
        count++;
        Serial.println("Task1"); 
        Serial.println(count); 
        LED = !LED;
        digitalWrite(13,LED);
        
        xSemaphoreGive(mutex); 
        vTaskDelay(pdMS_TO_TICKS(10000)); 
    } 
} 
 
void Task2(void *pvParameters) { 
    while(1) { 
        xSemaphoreTake(mutex, portMAX_DELAY);
        count++; 
        Serial.println("Task2"); 
        Serial.println(count); 
        LED = !LED;
        digitalWrite(13,LED);
        
        xSemaphoreGive(mutex); 
        vTaskDelay(pdMS_TO_TICKS(5000)); 
    } 
} 
 
void loop() { 
}
