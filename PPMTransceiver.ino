#include <mk_CPPM.h>


uint16_t p, t, r;

uint16_t adjust_signal(uint16_t signal, uint16_t center, float multiplier, uint16_t min, uint16_t max, uint16_t offset=0){
  uint16_t sig = signal - offset;
  // if ((signal-offset - center) > 10){
  //   sig = (signal - offset) * multiplier;
  // }
  // else if ((signal-offset - center) < -10){
  //   sig = (signal - offset) * 1/multiplier;
  // }
  // else sig = center-offset;
  return (uint16_t)constrain(sig, min, max);
}

void cppm_cycle(void)
{
	if (CPPM.synchronized() && CPPM.received())
	{
	  p = adjust_signal(CPPM.read_us(4), 1675, 1, 1000, 2000, 25);
		t = adjust_signal(CPPM.read_us(5), 1525, 1, 1000, 2000, 25);
    r = adjust_signal(CPPM.read_us(6), 1525, 1, 1000, 2000, 25);

#if 1
		Serial.print("pan="); Serial.print(p); Serial.print(", ");
		Serial.print("tilt="); Serial.print(t); Serial.print(", ");
		Serial.print("roll="); Serial.print(r); Serial.print("\n");

#else
		for (uint16_t i=0; i<(CPPM_MSERVO + 2); i++) {
			Serial.print('\t');
			Serial.print(CPPM._sync2s[i]/2); // width of synch pulses
		}
		Serial.println();
		for (int i=0; i<(CPPM_MSERVO + 2); i++) {
			Serial.print('\t');
			Serial.print(CPPM._puls3s[i]/2); // width of servo pulses
		}
		Serial.println();
#endif

		Serial.flush();

		delay(100);

		CPPM.received();
	}
	else
	{
		// if not synchronized, do something...
	}
}

void setup()
{
	Serial.begin(115200);
  Serial.print("PPM Transceiver started\n");
	CPPM.begin();
}

void loop()
{
	cppm_cycle();

  CPPM.write1_us(0, p);
  CPPM.write1_us(1, t);
  CPPM.write1_us(2, r);

}
