#include <Arduino.h>
#include <Wire.h>
#include <ReWire_MAX32664.h>

// An instance of the MAX32664. We are using the default I2C instance.
// Change this to match the values for your board.
ReWire_MAX32664 max32664 = ReWire_MAX32664(&Wire, D7, D6);

void setup()
{
    // Initialize serial communication
    Serial.begin(250000);

    // Initiate a 10-second countdown
    for (int i = 10; i > 0; i--)
    {
        Serial.print("[DEBUG] ");
        Serial.println(i);
        delay(1000);
    }
    Serial.println("[DEBUG] Countdown completed...");

    // Initialize I2C
    Serial.println("[DEBUG] Initializing I2C");
    Wire.begin();

    // Initialize the MAX32664 biohub
    Serial.println("[DEBUG] Initializing MAX32664");
    uint8_t device_mode;
    uint8_t result = max32664.Begin(device_mode);
    if (result == MAX32664_ReadStatusByteValue::SUCCESS_STATUS && device_mode == MAX32664_DeviceOperatingMode::ApplicationMode)
    {
        // We successfully initialized communication with the sensor
        Serial.println("[DEBUG] Sensor started!");
    }
    else
    {
        // We were not able to communicate with the sensor
        Serial.println("[DEBUG] Could not communicate with the sensor!");
        while (1)
        {
            // empty
        }
    }

    // Configure the sensor to output both raw data as well as calculated data
    Serial.println("[DEBUG] Configuring Sensor Calibration....");

    result = max32664.Configure_BPTCalibrationMode();
    if (result == MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        Serial.println("[DEBUG] Sensor Calibration MODe Configured.");
    }
    else
    {
        Serial.println("[DEBUG] Error configuring sensor.");
        Serial.print("[DEBUG] Error: ");
        Serial.println(result);
        while (1)
        {
            // empty
        }
    }
   result = max32664.Start_BPTCalibrationMode(0,117,75); // calindex systoli & diatolic value from medical equipment
   if (result == MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        Serial.println("[DEBUG] Start Calibration.");
    }
    else
    {
        Serial.println("[DEBUG] Error configuring sensor.");
        Serial.print("[DEBUG] Error: ");
        Serial.println(result);
        while (1)
        {
            // empty
        }
    }
}

void loop()
{
    // In this function, we are following the steps outlined in Table 8 (section 3.2) of
    //   the document "measuring-heart-rate-and-spo2-using-the-max32664a.pdf".
    //   Specifically, we are following the steps 2.1, 2.2, and 2.3 in the "READING SAMPLES"
    //   portion of Table 8.

    // Step 2.1: Read the sensor hub status byte

    uint8_t sensor_hub_status;
    uint8_t read_status = max32664.ReadSensorHubStatus(sensor_hub_status);
    // If the read was successful...
    if (read_status == MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        // Note: I am purposefully not checking "sensor_hub_status"
        //   to see if the DataRdyBit is set, because I've found that
        //   it doesn't really matter and just slows things down.
        //   Proceed.

        // Step 2.2: Get the number of samples in the FIFO
        uint8_t num_available_samples;
        read_status = max32664.ReadNumberAvailableSamples(num_available_samples);
        // If the read was successful and if there are samples available to read...
        if (read_status == MAX32664_ReadStatusByteValue::SUCCESS_STATUS || num_available_samples > 0)
        {
            // Step 2.3: Read the data stored in the FIFO
            for (int i = 0; i < num_available_samples; i++)
            {
                MAX32664_Data_VerD current_sample;
                read_status = max32664.ReadSample_BPTSensorAndAlgorithm(current_sample);

                // If the sample was successfully read...
                if (read_status == MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
                {
                    // Output the sample data to over serial communication
                    Serial.print(current_sample.ir);
                    Serial.print("\t");
                    Serial.print(current_sample.red);
                    Serial.print("\t");
                    Serial.print(current_sample.bp_status);
                    Serial.print("\t");
                    Serial.print(current_sample.progress);
                    Serial.print("\t");
                    Serial.print(current_sample.hr);
                    Serial.print("\t");
                    Serial.print(current_sample.sys_bp);
                    Serial.print("\t");
                    Serial.print(current_sample.dia_bp);
                    Serial.print("\t");
                    Serial.print(current_sample.spo2);
                    Serial.print("\t");
                    Serial.print(current_sample.r_value);
                    Serial.print("\t");
                    Serial.print(current_sample.pulse_flag);
                    Serial.print("\t");
                    Serial.print(current_sample.ibi);
                    Serial.print("\t");
                    Serial.print(current_sample.spo2_conf);
                    Serial.print("\t");
                    Serial.print(current_sample.bpt_report);
                    Serial.print("\t");
                    Serial.print(current_sample.spo2_report);
                    Serial.println("");
                }
            }
        }
    }
}
