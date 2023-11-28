#include "ReWire_MAX32664.h"

// calib vector sample from https://github.com/Protocentral/protocentral-pulse-express/
uint8_t calibVector[CALIBVECTOR_SIZE] = {0, 0, 175, 63, 3, 33, 75, 0, 0, 0, 0, 15, 198, 2, 100, 3, 32, 0, 0, 3, 207, 0, // calib vector sample
                                         4, 0, 3, 175, 170, 3, 33, 134, 0, 0, 0, 0, 15, 199, 2, 100, 3, 32, 0, 0, 3,
                                         207, 0, 4, 0, 3, 176, 22, 3, 33, 165, 0, 0, 0, 0, 15, 200, 2, 100, 3, 32, 0,
                                         0, 3, 207, 0, 4, 0, 3, 176, 102, 3, 33, 203, 0, 0, 0, 0, 15, 201, 2, 100, 3,
                                         32, 0, 0, 3, 207, 0, 4, 0, 3, 176, 178, 3, 33, 236, 0, 0, 0, 0, 15, 202, 2,
                                         100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 176, 255, 3, 34, 16, 0, 0, 0, 0, 15,
                                         203, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 177, 64, 3, 34, 41, 0, 0, 0, 0,
                                         15, 204, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 177, 130, 3, 34, 76, 0, 0,
                                         0, 0, 15, 205, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 177, 189, 3, 34, 90,
                                         0, 0, 0, 0, 15, 206, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 177, 248, 3, 34,
                                         120, 0, 0, 0, 0, 15, 207, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 178, 69, 3,
                                         34, 137, 0, 0, 0, 0, 15, 208, 2, 100, 3, 32, 0, 0, 3, 0, 0, 175, 63, 3, 33,
                                         75, 0, 0, 0, 0, 15, 198, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 175, 170, 3,
                                         33, 134, 0, 0, 0, 0, 15, 199, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 176,
                                         22, 3, 33, 165, 0, 0, 0, 0, 15, 200, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3,
                                         176, 102, 3, 33, 203, 0, 0, 0, 0, 15, 201, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4,
                                         0, 3, 176, 178, 3, 33, 236, 0, 0, 0, 0, 15, 202, 2, 100, 3, 32, 0, 0, 3, 207,
                                         0, 4, 0, 3, 176, 255, 3, 34, 16, 0, 0, 0, 0, 15, 203, 2, 100, 3, 32, 0, 0, 3,
                                         207, 0, 4, 0, 3, 177, 64, 3, 34, 41, 0, 0, 0, 0, 15, 204, 2, 100, 3, 32, 0, 0,
                                         3, 207, 0, 4, 0, 3, 177, 130, 3, 34, 76, 0, 0, 0, 0, 15, 205, 2, 100, 3, 32,
                                         0, 0, 3, 207, 0, 4, 0, 3, 177, 189, 3, 34, 90, 0, 0, 0, 0, 15, 206, 2, 100, 3,
                                         32, 0, 0, 3, 207, 0, 4, 0, 3, 177, 248, 3, 34, 120, 0, 0, 0, 0, 15, 207, 2,
                                         100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 178, 69, 3, 34, 137, 0, 0, 0, 0, 15,
                                         208, 2, 100, 3, 32, 0, 0, 3, 0, 0, 175, 63, 3, 33, 75, 0, 0, 0, 0, 15, 198, 2,
                                         100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 175, 170, 3, 33, 134, 0, 0, 0, 0, 15,
                                         199, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 176, 22, 3, 33, 165, 0, 0, 0, 0,
                                         15, 200, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 176, 102, 3, 33, 203, 0, 0,
                                         0, 0, 15, 201, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 176, 178, 3, 33, 236,
                                         0, 0, 0, 0, 15, 202, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 176, 255, 3, 34,
                                         16, 0, 0, 0, 0, 15, 203, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 177, 64, 3,
                                         34, 41, 0, 0, 0, 0, 15, 204, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3, 177,
                                         130, 3, 34, 76, 0, 0, 0, 0, 15, 205, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4, 0, 3,
                                         177, 189, 3, 34, 90, 0, 0, 0, 0, 15, 206, 2, 100, 3, 32, 0, 0, 3, 207, 0, 4,
                                         0, 3, 177, 248, 3, 34, 120, 0, 0, 0, 0, 15, 207, 2, 100, 3, 32, 0, 0, 3, 207,
                                         0, 4, 0, 3, 178, 69, 3, 34, 137, 0, 0, 0, 0, 15, 208, 2, 100, 3, 32, 0, 0, 3,
                                         0, 0, 175, 63, 3, 33, 75, 0, 0, 0, 0, 15, 198, 2, 100, 3, 32, 0, 0, 3, 207, 0,
                                         4, 0, 3, 175, 170, 3, 33, 134, 0, 0, 0, 0, 15, 199, 2, 100, 3, 32, 0, 0, 3,
                                         207, 0, 4, 0, 3, 176, 22, 3, 33, 165, 0, 0, 0, 0, 15, 200, 2, 100, 3, 32, 0,
                                         0, 3, 207, 0, 4, 0, 3, 176, 102, 3};

ReWire_MAX32664::ReWire_MAX32664(TwoWire *i2c_instance, int pin_mfio, int pin_reset, int i2c_address)
{
    ConfigurePinsAndI2C(i2c_instance, pin_mfio, pin_reset, i2c_address);
}

void ReWire_MAX32664::ConfigurePinsAndI2C(TwoWire *i2c_instance, int pin_mfio, int pin_reset, int i2c_address)
{
    wire_instance = i2c_instance;
    mfio_pin = pin_mfio;
    reset_pin = pin_reset;
    max32664_i2c_address = i2c_address;
}

uint8_t ReWire_MAX32664::Begin(uint8_t &device_mode, TwoWire *i2c_instance, int pin_mfio, int pin_reset, int i2c_address)
{
    ConfigurePinsAndI2C(i2c_instance, pin_mfio, pin_reset, i2c_address);
    return Begin(device_mode);
}

/// @brief Initializes communication with the MAX32664
/// @param device_mode the resulting operating mode of the MAX32664
/// @return the resulting status byte of the read operation
uint8_t ReWire_MAX32664::Begin(uint8_t &device_mode)
{
    // Set the MFIO and reset pins to be output pins
    pinMode(mfio_pin, OUTPUT);
    pinMode(reset_pin, OUTPUT);

    // As described in the datasheet, to enter "application mode", we must set the reset pin low for 10 ms,
    // and also set the MFIO pin high.
    digitalWrite(mfio_pin, HIGH);
    digitalWrite(reset_pin, LOW);
    delay(10);

    // As described in the datasheet, after 10 ms has elapsed, we must set the reset pin to high.
    digitalWrite(reset_pin, HIGH);

    // After approximately 50 ms, the MAX32664 is now in "application mode".
    // After approximately 1 second from when the reset pin was set to high, the application should have
    // completed initialization and the device is now ready to accept I2C commands.
    delay(1000);

    // Set the mfio pin to INPUT_PULLUP. It can be used to receive interrupts.
    pinMode(mfio_pin, INPUT_PULLUP);

    // Read the device's operating mode and return the result to the caller
    uint8_t status_byte = ReadDeviceMode(device_mode);
    return status_byte;
}

/// @brief Reads a single sample from the output fifo, working under the assumption the sample
///     is a sensor+algorithm sample w/o accelerometer (so 21 bytes in size)
/// @param sample The sample
/// @return The status of the read operation
uint8_t ReWire_MAX32664::ReadSample_SensorAndAlgorithm(MAX32664_Data &sample)
{
    uint8_t read_length = 21;
    uint8_t read_buffer[21] = {0};

    // Read the sample
    uint8_t read_status = ReadOutputFifo(read_buffer, read_length);

    // Parse the sample
    uint32_t ir0 = ((uint32_t)read_buffer[0]) << 16;
    uint32_t ir1 = ((uint32_t)read_buffer[1]) << 8;
    uint32_t ir2 = ((uint32_t)read_buffer[2]);
    uint32_t ir_final = (uint32_t)(ir0 | ir1 | ir2) / 10;

    uint32_t red0 = ((uint32_t)read_buffer[3]) << 16;
    uint32_t red1 = ((uint32_t)read_buffer[4]) << 8;
    uint32_t red2 = ((uint32_t)read_buffer[5]);
    uint32_t red_final = (uint32_t)(red0 | red1 | red2) / 10;

    uint16_t hr = (uint16_t(read_buffer[12]) << 8);
    hr |= (read_buffer[13]);
    hr /= 10;

    uint8_t hr_confidence = read_buffer[14];

    uint16_t spo2 = uint16_t(read_buffer[15]) << 8;
    spo2 |= read_buffer[16];
    spo2 /= 10;

    // Assign these values to the MAX32664_Data object
    sample.ir = ir_final;
    sample.red = red_final;
    sample.hr = hr;
    sample.hr_confidence = hr_confidence;
    sample.spo2 = spo2;
    sample.algorithm_state = read_buffer[17];
    sample.algorithm_status = read_buffer[18];
    sample.interbeat_interval = ((read_buffer[19] << 8) | read_buffer[20]) / 1000;

    // Return the result of the read operation
    return read_status;
}

/// @brief This function executes all the commands necessary to start the HR/SpO2 algorithm and also include PPG data.
/// @return The status result
uint8_t ReWire_MAX32664::ConfigureDevice_SensorAndAlgorithm()
{
    // In this function, we are following the steps outlined in Table 8 (section 3.2) of
    //   the document "measuring-heart-rate-and-spo2-using-the-max32664a.pdf".

    // Step 1.1: Set SpO2 calibration coefficients
    //   We are skipping this step for now.

    // Step 1.2: Set output mode to sensor + algorithm data (0x03, streamed data will include
    //   PPG and algorithm data, but NOT accelerometer data).
    uint8_t status_byte = SetOutputMode_OutputFormat(MAX32664_OutputModeFormat::SensorData_And_AlgorithmData);
    delay(10);

    // Check to make sure the operation was successful
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        return status_byte;
    }

    // Step 1.3: Set sensor hub interrupt threshold to 0x0F (the value used in the datasheet example).
    status_byte = SetOutputMode_FifoInterruptThreshold(0x0F);
    delay(10);

    // Check to make sure the operation was successful
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        return status_byte;
    }

    // Step 1.4: Enable the AGC (automatic gain control)
    status_byte = SetAlgorithmMode_EnableAGC(true);
    delay(200);

    // Check to make sure the operation was successful
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        return status_byte;
    }

    // Step 1.5: Enable the accelerometer with the sensor hub
    //   We are skipping this step because we do not currently have
    //   an accelerometer.

    // Step 1.6: Enable the AFE ("analog front end" - the MAX30101 in this case)
    status_byte = EnableSensor(true);
    delay(40);

    // Check to make sure the operation was successful
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        return status_byte;
    }

    // Step 1.7: Enable the HR/SpO2 algorithm.
    status_byte = EnableAlgorithmMode_MaximFast(0x01);
    delay(10);

    // Return the result of the final operation
    return status_byte;
}

/// @brief Reads the status of the sensor hub
/// @param status the sensor hub status
///     [0] = Err0
///         No error = 0
///         Sensor communication problem = 1
///     [1] = Err1 / Not used
///     [2] = Err2 / Not used
///     [3] = DataRdyInt
///         FIFO below threshold = 0
///         FIFO filled = 1
///     [4] = FifoOutOvrInt
///         No FIFO overflow = 0
///         FIFO overflowed / data lost = 1
///     [5] = FifoInOvrInt
///         No FIFO overflow = 0
///         FIFO overflowed / data lost = 1
///     [6] = HostAccelUfInt
///         No underflow = 0
///         Host data to input FIFO has slowed = 1
/// @return the status byte of the read operation
uint8_t ReWire_MAX32664::ReadSensorHubStatus(uint8_t &status)
{
    uint8_t status_byte = read_byte(MAX32664_CommandFamilyByte::ReadSensorHubStatus, 0x00, status);
    return status_byte;
}

/// @brief Reads the device operating mode
/// @param device_mode will be set to: 0x00 = Application operating mode, 0x02 = Reset, 0x08 = Bootloader operating mode
/// @return the status byte of the read operation
uint8_t ReWire_MAX32664::ReadDeviceMode(uint8_t &device_mode)
{
    uint8_t status_byte = read_byte(MAX32664_CommandFamilyByte::ReadDeviceMode, 0x00, device_mode);
    return status_byte;
}

/// @brief Reads the firmware version of the MAX32664
/// @param major_version MAX32664 major version number
/// @param minor_version MAX32664 minor version number
/// @param revision_number MAX32664 revision number
/// @return the status byte of the read operation
uint8_t ReWire_MAX32664::ReadSensorHubVersion(uint8_t &major_version, uint8_t &minor_version, uint8_t &revision_number)
{
    uint8_t status_byte;

    wire_instance->beginTransmission(max32664_i2c_address);
    wire_instance->write(MAX32664_CommandFamilyByte::ReadIdentity);
    wire_instance->write(0x03);
    wire_instance->endTransmission();

    wire_instance->requestFrom(max32664_i2c_address, 4);
    status_byte = wire_instance->read();
    delayMicroseconds(10);
    major_version = wire_instance->read();
    delayMicroseconds(10);
    minor_version = wire_instance->read();
    delayMicroseconds(10);
    revision_number = wire_instance->read();
    delayMicroseconds(10);

    return status_byte;
}

/// @brief Sets the operating mode of the MAX32664
/// @param operating_mode 0x00 = exit bootloader/enter application, 0x01 = shutdown, 0x02 = reset, 0x08 = enter bootloader
/// @return the status byte of the write operation
uint8_t ReWire_MAX32664::SetDeviceOperatingMode(MAX32664_DeviceOperatingMode operating_mode)
{
    return write_byte(MAX32664_CommandFamilyByte::SetDeviceMode, 0x00, operating_mode);
}

/// @brief Sets the output format of the sensor data
/// @param output_format the output format of the sensor data
/// @return the status byte of the write operation
uint8_t ReWire_MAX32664::SetOutputMode_OutputFormat(MAX32664_OutputModeFormat output_format)
{
    return write_byte(MAX32664_CommandFamilyByte::SetOutputMode, 0x00, output_format);
}

/// @brief Sets the threshold for the FIFO interrupt bit/pin. The MFIO pin is used as the interrupt pin.
/// @param interrupt_threshold 0x01 to 0xFF. Sensor interrupt threshold for FIFO.
/// @return the status byte of the write operation
uint8_t ReWire_MAX32664::SetOutputMode_FifoInterruptThreshold(uint8_t interrupt_threshold)
{
    return write_byte(MAX32664_CommandFamilyByte::SetOutputMode, 0x01, interrupt_threshold);
}

/// @brief Enable the AGC algorithm
/// @param enable 0 = disable, 1 = enable
/// @return the status byte of the write operation
uint8_t ReWire_MAX32664::SetAlgorithmMode_EnableAGC(bool enable)
{
    return write_byte_with_custom_cmd_delay(MAX32664_CommandFamilyByte::EnableAlgorithm, 0x00, enable, 20 + 20);
}

/// @brief Enable the MAX30101 sensor
/// @param enable 0 = disable, 1 = enable
/// @return the status byte of the write operation
uint8_t ReWire_MAX32664::EnableSensor(bool enable)
{
    return write_byte_with_custom_cmd_delay(MAX32664_CommandFamilyByte::EnableSensorMode, 0x03, enable, 40 + 20);
}

/// @brief Enable the WHRM MaximFast algorithm.
/// @param mode 0x00 = disable, 0x01 = mode 1 report, 0x02 = mode 2 extended report
/// @return
uint8_t ReWire_MAX32664::EnableAlgorithmMode_MaximFast(uint8_t mode)
{
    return write_byte_with_custom_cmd_delay(MAX32664_CommandFamilyByte::EnableAlgorithm, 0x02, mode, 40 + 20);
}

/// @brief Reads the number of available samples in the output FIFO on the MAX32664
/// @param num_samples The number of available samples
/// @return the status byte of the read operation
uint8_t ReWire_MAX32664::ReadNumberAvailableSamples(uint8_t &num_samples)
{
    uint8_t status_byte;

    wire_instance->beginTransmission(max32664_i2c_address);
    wire_instance->write(MAX32664_CommandFamilyByte::ReadOutputFIFO);
    wire_instance->write(0x00);
    wire_instance->endTransmission();
    delay(MAX32664_COMMAND_DELAY);

    wire_instance->requestFrom(max32664_i2c_address, 2);
    status_byte = wire_instance->read();
    num_samples = wire_instance->read();

    return status_byte;
}

/// @brief Reads data stored in the output FIFO
/// @param read_buffer the buffer to hold the bytes that are read
/// @param read_length the number of bytes to read
/// @return The status of the read operation
uint8_t ReWire_MAX32664::ReadOutputFifo(uint8_t *read_buffer, uint8_t read_length)
{
    return read_multiple_bytes(MAX32664_CommandFamilyByte::ReadOutputFIFO, 0x01, read_buffer, read_length);
}

uint8_t ReWire_MAX32664::read_byte(uint8_t data1, uint8_t data2, uint8_t &return_byte)
{
    uint8_t status_byte;

    wire_instance->beginTransmission(max32664_i2c_address);
    wire_instance->write(data1);
    wire_instance->write(data2);
    wire_instance->endTransmission();
    delay(MAX32664_COMMAND_DELAY);

    wire_instance->requestFrom(max32664_i2c_address, 2);
    status_byte = wire_instance->read();
    return_byte = wire_instance->read();
    return status_byte;
}

uint8_t ReWire_MAX32664::read_multiple_bytes(uint8_t data1, uint8_t data2, uint8_t *read_buffer, uint8_t read_length)
{
    uint8_t status_byte;

    wire_instance->beginTransmission(max32664_i2c_address);
    wire_instance->write(data1);
    wire_instance->write(data2);
    wire_instance->endTransmission();
    delay(MAX32664_COMMAND_DELAY);

    wire_instance->requestFrom(max32664_i2c_address, read_length + 1);
    status_byte = wire_instance->read();
    for (int i = 0; i < read_length; ++i)
    {
        read_buffer[i] = wire_instance->read();
        delayMicroseconds(10);
    }

    return status_byte;
}

uint8_t ReWire_MAX32664::write_byte(uint8_t data1, uint8_t data2, uint8_t data3)
{
    wire_instance->beginTransmission(max32664_i2c_address);
    wire_instance->write(data1);
    wire_instance->write(data2);
    wire_instance->write(data3);
    wire_instance->endTransmission();
    delay(MAX32664_COMMAND_DELAY);

    wire_instance->requestFrom(max32664_i2c_address, 1);
    uint8_t status_byte = wire_instance->read();
    return status_byte;
}

uint8_t ReWire_MAX32664::write_byte_with_custom_cmd_delay(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t cmd_delay)
{
    wire_instance->beginTransmission(max32664_i2c_address);
    wire_instance->write(data1);
    wire_instance->write(data2);
    wire_instance->write(data3);
    wire_instance->endTransmission();
    delay(cmd_delay);

    wire_instance->requestFrom(max32664_i2c_address, 1);
    uint8_t status_byte = wire_instance->read();
    return status_byte;
}

uint8_t ReWire_MAX32664::write_multiple_bytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t *buffer, uint16_t buffer_size)
{
    wire_instance->beginTransmission(max32664_i2c_address);
    wire_instance->write(data1);
    wire_instance->write(data2);
    wire_instance->write(data3);
    //wire_instance->write((const uint8_t *)buffer,(size_t) buffer_size);
    for (uint16_t i = 0; i < buffer_size; ++i){
        wire_instance->write(buffer[i]);
        delayMicroseconds(1);
    }
        wire_instance->endTransmission();
    delay(MAX32664_COMMAND_DELAY);

    wire_instance->requestFrom(max32664_i2c_address, 1);
    uint8_t status_byte = wire_instance->read();
    return status_byte;
}

uint8_t ReWire_MAX32664::loadBPTCalibVector()
{
    uint8_t status = write_multiple_bytes(MAX32664_CommandFamilyByte::SetAlgorithmConfiguration, 0x04, MAX32664_ConfigrationIndex::BPCalibrationData, calibVector, CALIBVECTOR_SIZE);
    return status;
}

uint8_t ReWire_MAX32664::setDataTime()
{
    uint8_t dateTimeBuffer[8] = {0x5c, 0xc2, 0x02, 0x00, 0xe0, 0x7f, 0x02, 0x00}; // @note Default value from user guide need to change
    uint8_t status = write_multiple_bytes(MAX32664_CommandFamilyByte::SetAlgorithmConfiguration, 0x04, MAX32664_ConfigrationIndex::SetDateAndTime, dateTimeBuffer, 8);

    return status;
}

uint8_t ReWire_MAX32664::loadSpo2Coefficients(float spo2CalibCoefA, float spo2CalibCoefB, float spo2CalibCoefC)
{
    uint32_t A = spo2CalibCoefA * 100000;
    uint32_t B = spo2CalibCoefB * 100000;
    uint32_t C = spo2CalibCoefC * 100000;
    uint8_t spo2CoefBuffer[12] = {0};
    spo2CoefBuffer[0] = (A & 0xff000000) >> 24;
    spo2CoefBuffer[1] = (A & 0x00ff0000) >> 16;
    spo2CoefBuffer[2] = (A & 0x0000ff00) >> 8;
    spo2CoefBuffer[3] = (A & 0x000000ff);

    spo2CoefBuffer[4] = (B & 0xff000000) >> 24;
    spo2CoefBuffer[5] = (B & 0x00ff0000) >> 16;
    spo2CoefBuffer[6] = (B & 0x0000ff00) >> 8;
    spo2CoefBuffer[7] = (B & 0x000000ff);

    spo2CoefBuffer[8] = (C & 0xff000000) >> 24;
    spo2CoefBuffer[9] = (C & 0x00ff0000) >> 16;
    spo2CoefBuffer[10] = (C & 0x0000ff00) >> 8;
    spo2CoefBuffer[11] = (C & 0x000000ff);
    uint8_t status = write_multiple_bytes(MAX32664_CommandFamilyByte::SetAlgorithmConfiguration, 0x04, MAX32664_ConfigrationIndex::SpO2CalibrationCoefficients, spo2CoefBuffer, 12);

    return status;
}

uint8_t ReWire_MAX32664::EnableBPT_Algorithm(uint8_t mode)
{
    return write_byte(MAX32664_CommandFamilyByte::EnableAlgorithm, 0x04, mode);
}

uint8_t ReWire_MAX32664::ReadSample_BPTSensorAndAlgorithm(MAX32664_Data_VerD &sample)
{
    uint8_t read_length = 23;
    uint8_t read_buffer[23] = {0};

    // Read the sample
    uint8_t read_status = ReadOutputFifo(read_buffer, read_length);

    // Parse the sample
    uint32_t ir0 = ((uint32_t)read_buffer[0]) << 16;
    uint32_t ir1 = ((uint32_t)read_buffer[1]) << 8;
    uint32_t ir2 = ((uint32_t)read_buffer[2]);
    uint32_t ir_final = (uint32_t)(ir0 | ir1 | ir2) / 10;

    uint32_t red0 = ((uint32_t)read_buffer[3]) << 16;
    uint32_t red1 = ((uint32_t)read_buffer[4]) << 8;
    uint32_t red2 = ((uint32_t)read_buffer[5]);
    uint32_t red_final = (uint32_t)(red0 | red1 | red2) / 10;

    uint16_t hr = (uint16_t(read_buffer[14]) << 8);
    hr |= (read_buffer[15]);
    hr /= 10;

    uint16_t spo2 = uint16_t(read_buffer[18]) << 8;
    spo2 |= read_buffer[19];
    spo2 /= 10;

    uint16_t r_value = uint16_t(read_buffer[20]) << 8;
    r_value |= read_buffer[21];
    r_value /= 1000;
    // Assign these values to the MAX32664_Data object
    sample.ir = ir_final;
    sample.red = red_final;
    sample.bp_status = read_buffer[12];
    sample.progress = read_buffer[13];
    sample.hr = hr;
    sample.sys_bp = read_buffer[16];
    sample.dia_bp = read_buffer[17];
    sample.spo2 = spo2;
    sample.r_value = r_value;
    sample.hr_resting_flag = read_buffer[22];
    // Return the result of the read operation
    return read_status;
}

uint8_t ReWire_MAX32664::ConfigureBPT_SensorAndAlgorithm()
{
    // In this function, we are following the steps outlined in Table 8 (section 3.2) of
    //   the document "measuring-heart-rate-and-spo2-using-the-max32664a.pdf".

    // Step 1.1: Load 824 bytes of BPT calibration vector data
    uint8_t status_byte = loadBPTCalibVector();
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("CALIB VECTOR\r\n");
        return status_byte;
    }
    delay(10);

    // Step 1.2: THIS STEP IS NOT NEEDED IN FW VER. 40.2.2 AND LATER.
    // Step 1.3: THIS STEP IS NOT NEEDED IN FW VER. 40.2.2 AND LATER.

    // Step 1.4: Set data and time as two 32-bit numbers for
    // YYMMDD and HHMMSS in little-endian format.
    // Provided example is for date:180828, time:163808.
    status_byte = setDataTime();
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("DATA TIME\r\n");
        return status_byte;
    }
    delay(10);
    // Step 1.5: Set SpO_2 calibration coefficients as described in
    // the document. Provided example for:
    // A = 1.5958422, B = -34.659664, C = 112.68987
    status_byte = loadSpo2Coefficients(1.5958422, -34.659664, 112.68987); //@note Default values from documentation (change)
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("SPO2\r\n");
        return status_byte;
    }
    delay(10);

    // Step 1.7: ąSet output mode to sensor + algorithm data
    //(streamed data will include PPG and algorithm data).
    status_byte = SetOutputMode_OutputFormat(MAX32664_OutputModeFormat::SensorData_And_AlgorithmData);
    delay(10);

    // Check to make sure the operation was successful
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("OUTPUT FORMAT\r\n");
        return status_byte;
    }

    // Step 1.8: Set sensor hub interrupt threshold to 0x0F (the value used in the datasheet example).
    status_byte = SetOutputMode_FifoInterruptThreshold(0x0F);
    delay(10);

    // Check to make sure the operation was successful
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("FIFO INTERRUPT\r\n");

        return status_byte;
    }

    

    // Step 1.10: Enable the AFE ("analog front end" - the MAX30101 in this case)
    status_byte = EnableSensor(true);
    delay(40);

    // Check to make sure the operation was successful
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("ENABLE SENSOR\r\n");

        return status_byte;
    }

    // Step 1.11: Enable the BPT Estimation algorithm.
    status_byte = EnableBPT_Algorithm(0x02);
    if (status_byte == MAX32664_ReadStatusByteValue::ERR_TRY_AGAIN)
    {
        do
        {
            delay(10);
            status_byte = EnableBPT_Algorithm(0x02);
        } while (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS);
    }
    else if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("ENABLE BPT\r\n");
    }
    delay(100);
    // Step 1.9: Enable the AGC (automatic gain control)
    status_byte = SetAlgorithmMode_EnableAGC(false);
    delay(200);
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("ENABLE AGC\r\n");

        return status_byte;
    }
    // Return the result of the final operation
    return status_byte;
}

uint8_t ReWire_MAX32664::ConfigureBPT_RawValue()
{
    // In this function, we are following the steps outlined in Table 8 (section 3.2) of
    //   the document "measuring-heart-rate-and-spo2-using-the-max32664a.pdf".

    // Step 1.7: Set output mode to sensor + algorithm data
    //(streamed data will include PPG and algorithm data).
    uint8_t status_byte = SetOutputMode_OutputFormat(MAX32664_OutputModeFormat::SensorData);
    delay(10);

    // Check to make sure the operation was successful
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("OUTPUT FORMAT\r\n");
        return status_byte;
    }

    // Step 1.8: Set sensor hub interrupt threshold to 0x0F (the value used in the datasheet example).
    status_byte = SetOutputMode_FifoInterruptThreshold(0x0F);
    delay(10);

    // Check to make sure the operation was successful
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("FIFO INTERRUPT\r\n");

        return status_byte;
    }

    // Step 1.10: Enable the AFE ("analog front end" - the MAX30101 in this case)
    status_byte = EnableSensor(true);
    delay(1);

    // Check to make sure the operation was successful
    if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("ENABLE SENSOR\r\n");

        return status_byte;
    }

    // Step 1.11: Enable the BPT Estimation algorithm.
    status_byte = EnableBPT_Algorithm(0x02);

    if (status_byte == MAX32664_ReadStatusByteValue::ERR_TRY_AGAIN)
    {
        do
        {
            delay(10);
            status_byte = EnableBPT_Algorithm(0x02);
        } while (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS);
    }
    else if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("ENABLE BPT ALGO\r\n");
    }
    // Step 1.9: Enable the AGC (automatic gain control)
    status_byte = SetAlgorithmMode_EnableAGC(false);

    // Check to make sure the operation was successful
    if (status_byte == MAX32664_ReadStatusByteValue::ERR_TRY_AGAIN)
    {
        do
        {
            delay(10);
            status_byte = SetAlgorithmMode_EnableAGC(false);
        } while (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS);
    }
    else if (status_byte != MAX32664_ReadStatusByteValue::SUCCESS_STATUS)
    {
        printf("ENABLE AGC\r\n");

        return status_byte;
    }

    delay(100);

    // Return the result of the final operation
    return status_byte;
}

uint8_t ReWire_MAX32664::ReadSample_BPTSensor(MAX32664_Data_VerD &sample)
{
    uint8_t read_length = 12;
    uint8_t read_buffer[12] = {0};

    // Read the sample
    uint8_t read_status = ReadOutputFifo(read_buffer, read_length);

    // Parse the sample
    uint32_t ir0 = ((uint32_t)read_buffer[0]) << 16;
    uint32_t ir1 = ((uint32_t)read_buffer[1]) << 8;
    uint32_t ir2 = ((uint32_t)read_buffer[2]);
    uint32_t ir_final = (uint32_t)(ir0 | ir1 | ir2) / 10;

    uint32_t red0 = ((uint32_t)read_buffer[3]) << 16;
    uint32_t red1 = ((uint32_t)read_buffer[4]) << 8;
    uint32_t red2 = ((uint32_t)read_buffer[5]);
    uint32_t red_final = (uint32_t)(red0 | red1 | red2) / 10;

    // Assign these values to the MAX32664_Data object
    sample.ir = ir_final;
    sample.red = red_final;
    sample.bp_status = 0;
    sample.progress = 0;
    sample.hr = 0;
    sample.sys_bp = 0;
    sample.dia_bp = 0;
    sample.spo2 = 0;
    sample.r_value = 0;
    sample.hr_resting_flag = 0;
    // Return the result of the read operation
    return read_status;
}

uint8_t ReWire_MAX32664::getMCUType(uint8_t &return_byte){

    uint8_t status_byte = read_byte(0xFF, 0x00, return_byte);
    return status_byte;
}

uint8_t ReWire_MAX32664::readBPTAlgoCalibData(uint8_t *calibArray)
{

    uint8_t status = read_multiple_bytes(0x51, 0x04, 0x03, calibArray, CALIBVECTOR_SIZE);
    return status;
}

uint8_t ReWire_MAX32664::read_multiple_bytes(uint8_t data1, uint8_t data2,uint8_t data3, uint8_t *read_buffer, uint16_t read_length)
{
    uint8_t status_byte;

    wire_instance->beginTransmission(max32664_i2c_address);
    wire_instance->write(data1);
    wire_instance->write(data2);
    wire_instance->write(data3);
    wire_instance->endTransmission();
    delay(MAX32664_COMMAND_DELAY);

    wire_instance->requestFrom16(max32664_i2c_address, read_length + 1, 0, 0, true);
    status_byte = wire_instance->read();
    for (uint16_t i = 0; i < read_length; ++i)
    {
        read_buffer[i] = wire_instance->read();
    }

    return status_byte;
}
