
#ifndef		__H_FIRMATAC_
#define		__H_FIRMATAC_

#include	"serial.h"

#define MODE_INPUT	0x00
#define MODE_OUTPUT	0x01
#define MODE_ANALOG	0x02
#define MODE_PWM	0x03
#define MODE_SERVO	0x04
#define MODE_SHIFT	0x05
#define MODE_I2C	0x06

#define LOW		0
#define HIGH		1

#define FIRMATA_START_SYSEX		0xF0 // start a MIDI Sysex message
#define FIRMATA_END_SYSEX		0xF7 // end a MIDI Sysex message
#define FIRMATA_PIN_MODE_QUERY		0x72 // ask for current and supported pin modes
#define FIRMATA_PIN_MODE_RESPONSE	0x73 // reply with current and supported pin modes
#define FIRMATA_PIN_STATE_QUERY		0x6D
#define FIRMATA_PIN_STATE_RESPONSE	0x6E
#define FIRMATA_CAPABILITY_QUERY	0x6B
#define FIRMATA_CAPABILITY_RESPONSE	0x6C
#define FIRMATA_ANALOG_MAPPING_QUERY	0x69
#define FIRMATA_ANALOG_MAPPING_RESPONSE	0x6A

#define FIRMATA_DIGITAL_MESSAGE         0x90 // send data for a digital pin
#define FIRMATA_ANALOG_MESSAGE          0xE0 // send data for an analog pin (or PWM)
#define FIRMATA_ANALOG_MESSAGE          0xE0 // send data for an analog pin (or PWM)
#define FIRMATA_REPORT_ANALOG           0xC0 // enable analog input by pin #
#define FIRMATA_REPORT_DIGITAL          0xD0 // enable digital input by port pair

#define FIRMATA_SET_PIN_MODE            0xF4 // set a pin to INPUT/OUTPUT/PWM/etc

#define FIRMATA_REPORT_VERSION          0xF9 // report protocol version
#define FIRMATA_SYSTEM_RESET            0xFF // reset from MIDI

#define FIRMATA_START_SYSEX             0xF0 // start a MIDI Sysex message
#define FIRMATA_END_SYSEX               0xF7 // end a MIDI Sysex message

// extended command set using sysex (0-127/0x00-0x7F)
/* 0x00-0x0F reserved for custom commands */
#define FIRMATA_SERVO_CONFIG            0x70 // set max angle, minPulse, maxPulse, freq
#define FIRMATA_STRING                  0x71 // a string message with 14-bits per char
#define FIRMATA_VL53L0X_GET_DISTANCE	0x72 // get distance from VL53L0X
#define FIRMATA_REPORT_FIRMWARE         0x79 // report name and version of the firmware
#define FIRMATA_SYSEX_NON_REALTIME      0x7E // MIDI Reserved for non-realtime messages
#define FIRMATA_SYSEX_REALTIME          0x7F // MIDI Reserved for realtime messages

#define FIRMATA_MSG_LEN			1024

#define GET_CUSTOM_VALUE(in) in - 0x72

typedef struct		s_pin
{
  uint8_t		mode;
  uint8_t		analog_channel;
  uint64_t		supported_modes;
  uint32_t		value;
}			t_pin;

typedef struct		s_firmata
{
  t_serial		*serial;
  t_pin			pins[128];
  int			parse_command_len;
  int			parse_count;
  uint8_t		parse_buff[FIRMATA_MSG_LEN];
  int			isReady;
  char			firmware[140];

  // custom commands reserved from 0x72 to 0x78 (120-127)
  uint32_t      custom_value[7];
}			t_firmata;

t_firmata		*firmata_new(char *name);
t_firmata		*firmata_new_with_baud(char *name, int baud);
void			firmata_initPins(t_firmata *firmata);
void			firmata_initCustomValues(t_firmata *firmata);
int			firmata_askFirmware(t_firmata *firmata);
int			firmata_pinMode(t_firmata *firmata, int pin, int mode);
int			firmata_digitalWrite(t_firmata *firmata, int pin, int value);
int			firmata_analogWrite(t_firmata *firmata, int pin, int value);
int			firmata_pull(t_firmata *firmata);
void			firmata_parse(t_firmata *firmata, const uint8_t *buf, int len);
void			firmata_endParse(t_firmata *firmata);

#endif
