#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <ctime>

using namespace std;

#define N_COLUMNS 130
#define N_ROWS_TRANSITIONS 10
// Adjust this with your serial port
#define SERIAL_PORT "/dev/ttyACM0"

int plot[N_COLUMNS];
int current_state = 0; // Variable to store the current state of the button
int press_count = 0; // Variable to count button presses
int previous_state = 0; // Variable to store the previous state of the button

// Function to process the character read from the serial port
void process_serial_char(char value) {
  switch (value) {
  case '0':
    current_state = 0;
    break;
  case '1':
    current_state = 1;
    break;
  default:
    break;
  }

  if (current_state == 1 && previous_state == 0) {
    press_count++; // Increment the press count on a rising edge
  }
  previous_state = current_state; // Update the previous state

  plot[N_COLUMNS - 1] = current_state;
}

void initialize_plot() {
  for (int i = 0; i < N_COLUMNS; i++)
    plot[i] = 0;
}

void update_plot() {
  for (int i = 0; i < N_COLUMNS - 1; i++)
    plot[i] = plot[i + 1];
  plot[N_COLUMNS - 1] = current_state; // Update the last column with the current state
}

int main() {
  const char *device = SERIAL_PORT;

  struct termios tio;
  memset(&tio, 0, sizeof(tio)); // Initialize the `tio` structure to zero

  // Open the serial port in non-blocking mode
  int fd = open(device, O_RDONLY | O_NOCTTY | O_NONBLOCK); // `device` is the name of the serial port
  if (fd == -1) {
    perror("Unable to open device");
    return 1;
  }

  // Configure the serial port
  tio.c_cflag = CS8 | CREAD | CLOCAL; // 8 data bits, enable receiver, ignore modem control lines
  tio.c_cc[VMIN] = 1;  // Read non-blocking
  tio.c_cc[VTIME] = 0; // No inter-character timer

  // Set the baud rate for the serial port
  cfsetospeed(&tio, B9600); // Set output baud rate to 9600
  cfsetispeed(&tio, B9600); // Set input baud rate to 9600
  tcsetattr(fd, TCSANOW, &tio); // Apply the settings to the serial port immediately

  initialize_plot();

  // Get the start time
  time_t start_time = time(nullptr);

  // Read data from the serial port
  while (1) {
    char value;

    // read must be non-blocking, otherwise the loop will freeze
    int n = read(fd, &value, sizeof(char)); // Read a character from the serial port

    if (n > 0) {
      process_serial_char(value); // Process the received character
    }

    update_plot();

    // Use ANSI escape codes to clear the screen and move the cursor to the top-left
    cout << "\033[2J\033[H";
    cout << "\n";

    // Print states '1' - upper line
    for (int i = 0; i < N_COLUMNS; i++) {
      if (plot[i] == 1)
        cout << '_';
      else
        cout << ' ';
    }
    cout << endl;

    // Print transitions
    for (int j = 0; j < N_ROWS_TRANSITIONS; j++) {
      for (int i = 0; i < N_COLUMNS - 1; i++) {
        if (plot[i] != plot[i + 1])
          cout << '|';
        else
          cout << ' ';
      }
      cout << endl;
    }

    // Print states '0' - lower line
    for (int i = 0; i < N_COLUMNS; i++) {
      if (plot[i] == 0)
        cout << '_';
      else
        cout << ' ';
    }
    cout << endl;

    // Calculate and print the elapsed time in seconds
    time_t current_time = time(nullptr);
    int elapsed_time = static_cast<int>(difftime(current_time, start_time));
    cout << "Time elapsed: " << elapsed_time << " seconds" << endl;

    // Print the button press count
    cout << "Button pressed: " << press_count << " times" << endl;

    // Add a small delay to avoid overwhelming the CPU
    usleep(100000); // 100 ms delay
  }

  close(fd); // Close the serial port
  return 0;
}

