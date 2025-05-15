// Cotton Panel Code
// Author: Cebrail Dunra
// September 15, 2024

// Coressponding pin for the pushbutton
const int BUTTON = 12;

// Here, LEDs must be mapped to their corresponding pins
const int LED1 = 18;
const int LED2 = 10;
const int LED3 = 11;
const int LED4 = 19;
const int LED5 = 8;
const int LED6 = 9;
const int LED7 = 20;
const int LED8 = 6;
const int LED9 = 7;
const int LED10 = 21;
const int LED11 = 4;
const int LED12 = 5;
const int LED13 = 22;
const int LED14 = 2;
const int LED15 = 3;

const int LED_ARRAY[] = { LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15 };

int buttonState = 0;  // variable for reading the pushbutton status
bool stateLock = false;
int ledMode = 0;

int arrowIndex = 0;
int const ARROW_ENTRIES = 5;
// Array for storing a display option, this one is used to display a sequential arrow
int ARROW_ARRAY [ARROW_ENTRIES][15] = {
   {
    LOW, HIGH, LOW,
    LOW, LOW, LOW,
    LOW, LOW, LOW,
    LOW, LOW, LOW,
    LOW, LOW, LOW
  },
   {
    LOW, HIGH, LOW,
    LOW, HIGH, LOW,
    LOW, LOW, LOW,
    LOW, LOW, LOW,
    LOW, LOW, LOW
  },
  {
    LOW, HIGH, LOW,
    LOW, HIGH, LOW,
    LOW, HIGH, LOW,
    LOW, LOW, LOW,
    LOW, LOW, LOW
  },
  {
    LOW, HIGH, LOW,
    LOW, HIGH, LOW,
    LOW, HIGH, LOW,
    HIGH, LOW, HIGH,
    LOW, HIGH, LOW
  },
  {
    LOW, HIGH, LOW,
    LOW, HIGH, LOW,
    LOW, HIGH, LOW,
    HIGH, LOW, HIGH,
    LOW, HIGH, LOW
  }
};

int panelIndex = 0;
int const PANEL_ENTRIES = 5;
int PANEL_ARRAY [PANEL_ENTRIES][15] = {
  {
    HIGH, LOW, HIGH,
    HIGH, LOW, HIGH,
    HIGH, HIGH, HIGH,
    HIGH, LOW, HIGH,
    HIGH, LOW, HIGH
  },
  {
    HIGH, HIGH, HIGH,
    HIGH, LOW, LOW,
    HIGH, HIGH, HIGH,
    HIGH, LOW, LOW,
    HIGH, HIGH, HIGH
  },
  {
    HIGH, LOW, LOW,
    HIGH, LOW, LOW,
    HIGH, LOW, LOW,
    HIGH, LOW, LOW,
    HIGH, HIGH, HIGH
  },
  {
    HIGH, LOW, LOW,
    HIGH, LOW, LOW,
    HIGH, LOW, LOW,
    HIGH, LOW, LOW,
    HIGH, HIGH, HIGH
  },
  {
    HIGH, HIGH, HIGH,
    HIGH, LOW, HIGH,
    HIGH, LOW, HIGH,
    HIGH, LOW, HIGH,
    HIGH, HIGH, HIGH
  }
};

int elifIndex = 0;
int const ELIF_ENTRIES = 5;
int ELIF_ARRAY [ELIF_ENTRIES][15] = {
  {
    HIGH, HIGH, HIGH,
    HIGH, LOW, LOW,
    HIGH, HIGH, HIGH,
    HIGH, LOW, LOW,
    HIGH, HIGH, HIGH
  },
  {
    HIGH, LOW, LOW,
    HIGH, LOW, LOW,
    HIGH, LOW, LOW,
    HIGH, LOW, LOW,
    HIGH, HIGH, HIGH
  },
  {
    LOW, HIGH, LOW,
    LOW, LOW, LOW,
    LOW, HIGH, LOW,
    LOW, HIGH, LOW,
    LOW, HIGH, LOW
  },
  {
    HIGH, HIGH, HIGH,
    HIGH, LOW, LOW,
    HIGH, HIGH, HIGH,
    HIGH, LOW, LOW,
    HIGH, LOW, LOW
  },
  {
    HIGH, LOW, HIGH,
    HIGH, HIGH, HIGH,
    HIGH, HIGH, HIGH,
    HIGH, LOW, HIGH,
    LOW, HIGH, LOW
  }
};

void setup() {
  // initialize the pushbutton pin as an input
  pinMode(BUTTON, INPUT);

  // initialize the LED pins as output
  for (int led : LED_ARRAY) {
    pinMode(led, OUTPUT);
  }
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH && !stateLock) {
    stateLock = true;
    ledMode = (ledMode + 1) % 5;
  } else if (buttonState == LOW) {
    stateLock = false;
  }
  
  if (ledMode == 0) {
    // turn all LEDs off
    for (int led : LED_ARRAY) {
      digitalWrite(led, LOW);
    }
  } else if (ledMode == 1) {
    // turn all LEDs on
    for (int led : LED_ARRAY) {
      digitalWrite(led, HIGH);
    }
  } else if (ledMode == 2) {
    // Display the next arrow entry
    int ledIndex = 0;
    for (int led : LED_ARRAY) {
      digitalWrite(led, ARROW_ARRAY[arrowIndex][ledIndex]);
      ledIndex++;
    }
    delay(1000);

    // turn all LEDs off
    for (int led : LED_ARRAY) {
      digitalWrite(led, LOW);
    }
    delay(300);

    arrowIndex = (arrowIndex + 1) % ARROW_ENTRIES;
  } else if (ledMode == 3) {
    // Display the next panel entry
    int ledIndex = 0;
    for (int led : LED_ARRAY) {
      digitalWrite(led, PANEL_ARRAY[panelIndex][ledIndex]);
      ledIndex++;
    }
    delay(1000);

    // turn all LEDs off
    for (int led : LED_ARRAY) {
      digitalWrite(led, LOW);
    }
    delay(300);

    panelIndex = (panelIndex + 1) % PANEL_ENTRIES;
  } else if (ledMode == 4) {
    // Display the ELIF entry
    int ledIndex = 0;
    for (int led : LED_ARRAY) {
      digitalWrite(led, ELIF_ARRAY[elifIndex][ledIndex]);
      ledIndex++;
    }
    delay(1000);

    // turn all LEDs off
    for (int led : LED_ARRAY) {
      digitalWrite(led, LOW);
    }
    delay(300);

    elifIndex = (elifIndex + 1) % ELIF_ENTRIES;
  }

}
