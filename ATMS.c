#include <LPC21xx.H>

#define GREEN_PIN   (1 << 10)
#define YELLOW_PIN  (1 << 11)
#define RED_PIN     (1 << 12)

#define SENSOR_PIN1 (1 << 0)
#define SENSOR_PIN2 (1 << 1)

void GPIO_init(void) {
    IODIR0 |= GREEN_PIN | YELLOW_PIN | RED_PIN;
    IODIR0 &= ~(SENSOR_PIN1 | SENSOR_PIN2);
}

void setTrafficLights(int green, int yellow, int red) {
    if (green)   IOSET0 = GREEN_PIN;
    else         IOCLR0 = GREEN_PIN;

    if (yellow)  IOSET0 = YELLOW_PIN;
    else         IOCLR0 = YELLOW_PIN;

    if (red)     IOSET0 = RED_PIN;
    else         IOCLR0 = RED_PIN;
}

int vehicleDetected(int sensorPin) {
    return (IOPIN0 & sensorPin) == 0;
}

int main(void) {
    GPIO_init();

    while (1) {
        if (vehicleDetected(SENSOR_PIN1)) {
            setTrafficLights(1, 0, 0);
            for (int i = 0; i < 1000000; i++);
            setTrafficLights(0, 1, 0);
            for (int i = 0; i < 500000; i++);
            setTrafficLights(0, 0, 1);
            for (int i = 0; i < 1000000; i++);
        }

        if (vehicleDetected(SENSOR_PIN2)) {
            setTrafficLights(0, 0, 1);
            setTrafficLights(1, 0, 0);
            for (int i = 0; i < 1000000; i++);
            setTrafficLights(0, 1, 0);
            for (int i = 0; i < 500000; i++);
            setTrafficLights(0, 0, 1);
            for (int i = 0; i < 1000000; i++);
        }
    }
}
