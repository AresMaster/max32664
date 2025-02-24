#ifndef __REWIRE_MAX32664_H
#define __REWIRE_MAX32664_H

#include <Arduino.h>
#include <Wire.h>
#include <algorithm>

#define MAX32664_I2C_ADDRESS_DEFAULT 0x55
#define MAX32664_COMMAND_DELAY 5
#define CALIBVECTOR_SIZE 512
struct MAX32664_Data
{
    uint32_t ir;
    uint32_t red;
    uint16_t accelX;
    uint16_t accelY;
    uint16_t accelZ;
    uint16_t hr;
    uint8_t hr_confidence;
    uint16_t spo2;
    uint8_t algorithm_state;
    uint8_t algorithm_status;
    uint16_t interbeat_interval;
};
struct MAX32664_Data_VerD
{
    uint32_t ir;
    uint32_t red;
    uint8_t bp_status;
    uint8_t progress;
    float hr;
    uint8_t sys_bp;
    uint8_t dia_bp;
    float spo2;
    float r_value;
    uint8_t pulse_flag;
    float ibi;
    uint8_t spo2_conf;
    uint8_t bpt_report;
    uint8_t spo2_report;
    uint8_t end_bpt; // reserved not used
};
enum MAX32664_ReadStatusByteValue
{
    SUCCESS_STATUS = 0x00,
    ERR_UNAVAIL_CMD = 0x01,
    ERR_UNAVAIL_FUNC = 0x02,
    ERR_DATA_FORMAT = 0x03,
    ERR_INPUT_VALUE = 0x04,
    ERR_INVALID_MODE = 0x05,

    ERR_BTLDR_TRY_AGAIN = 0x05,
    ERR_BTLDR_GENERAL = 0x80,
    ERR_BTLDR_CHECKSUM = 0x81,
    ERR_BTLDR_AUTH = 0x82,
    ERR_BTLDR_INVALID_APP = 0x83,

    ERR_TRY_AGAIN = 0xFE,
    ERR_UNKNOWN = 0xFF
};

enum MAX32664_CommandFamilyByte
{
    ReadSensorHubStatus = 0x00,
    SetDeviceMode = 0x01,
    ReadDeviceMode = 0x02,
    SetOutputMode = 0x10,
    ReadOutputMode = 0x11,
    ReadOutputFIFO = 0x12,
    ReadInputFIFO = 0x13,
    WriteInputFIFO = 0x14,
    WriteRegister = 0x40,
    ReadRegister = 0x41,
    GetAttributesOfAFE = 0x42,
    DumpRegisters = 0x43,
    EnableSensorMode = 0x44,
    ReadSensorMode = 0x45,
    WriteSensorConfiguration = 0x46,
    ReadSensorConfiguration = 0x47,
    SetAlgorithmConfiguration = 0x50,
    GetAlgorithmConfiguration = 0x51,
    EnableAlgorithm = 0x52,
    BootloaderFlash = 0x80,
    GetBootloaderInformation = 0x81,
    GetSensorHubAFEAuthentication = 0xB2,
    GetSensorHubAFEInitializationVector = 0xB3,
    WriteSensorHubAFEPublicKey = 0xB4,
    GetSensorHubAFEPublicKey = 0xB5,
    ReadIdentity = 0xFF
};

enum MAX32664_DeviceOperatingMode
{
    ApplicationMode = 0x00,
    Shutdown = 0x01,
    Reset = 0x02,
    BootloaderMode = 0x08
};

enum MAX32664_OutputModeFormat
{
    Pause_NoData = 0x00,
    SensorData = 0x01,
    AlgorithmData = 0x02,
    SensorData_And_AlgorithmData = 0x03,

    SampleCounterByte_Pause_NoData = 0x04,
    SampleCounterByte_SensorData = 0x05,
    SampleCounterByte_AlgorithmData = 0x06,
    SampleCounterByte_SensorData_And_AlgorithmData = 0x07
};

enum MAX32664_ConfigrationIndex
{
    SystolicBPCalibrationValues = 0x01,
    DiastolicBPCalibrationValues = 0x02,
    BPCalibrationData = 0x03,
    SetDateAndTime = 0x04,
    SpO2CalibrationCoefficients = 0x06
};

class ReWire_MAX32664
{
private:
    TwoWire *wire_instance;
    int mfio_pin;
    int reset_pin;
    int max32664_i2c_address;

public:
    // Constructor
    ReWire_MAX32664(TwoWire *i2c_instance = &Wire, int pin_mfio = -1, int pin_reset = -1, int i2c_address = MAX32664_I2C_ADDRESS_DEFAULT);

    // Methods
    void ConfigurePinsAndI2C(TwoWire *i2c_instance = &Wire, int pin_mfio = -1, int pin_reset = -1, int i2c_address = MAX32664_I2C_ADDRESS_DEFAULT);
    uint8_t Begin(uint8_t &device_mode, TwoWire *i2c_instance, int pin_mfio, int pin_reset, int i2c_address = MAX32664_I2C_ADDRESS_DEFAULT);
    uint8_t Begin(uint8_t &device_mode);
    uint8_t ReadSample_SensorAndAlgorithm(MAX32664_Data &sample);
    uint8_t ConfigureDevice_SensorAndAlgorithm();
    uint8_t ReadSensorHubStatus(uint8_t &status);
    uint8_t ReadDeviceMode(uint8_t &device_mode);
    uint8_t ReadSensorHubVersion(uint8_t &major_version, uint8_t &minor_version, uint8_t &revision_number);
    uint8_t SetDeviceOperatingMode(MAX32664_DeviceOperatingMode operating_mode);
    uint8_t SetOutputMode_OutputFormat(MAX32664_OutputModeFormat output_format);
    uint8_t SetOutputMode_FifoInterruptThreshold(uint8_t interrupt_threshold);
    uint8_t SetAlgorithmMode_EnableAGC(bool enable);
    uint8_t EnableSensor(bool enable);
    uint8_t EnableAlgorithmMode_MaximFast(uint8_t mode);
    uint8_t ReadNumberAvailableSamples(uint8_t &num_samples);
    uint8_t ReadOutputFifo(uint8_t *read_buffer, uint8_t read_length);

    uint8_t loadSpo2Coefficients(float spo2CalibCoefA, float spo2CalibCoefB, float spo2CalibCoefC);
    uint8_t setDataTime();
    uint8_t ReadSample_BPTSensorAndAlgorithm(MAX32664_Data_VerD &sample);
    uint8_t ConfigureBPT_SensorAndAlgorithm();
    uint8_t ConfigureBPT_RawValue();
    uint8_t ReadSample_BPTSensor(MAX32664_Data_VerD &sample);
    uint8_t getMCUType(uint8_t &return_byte);
    uint8_t read_multiple_bytes(uint8_t data1, uint8_t data2, uint8_t data_3, uint8_t *read_buffer, uint16_t read_length);
    uint8_t readBPTAlgoCalibData(uint8_t *calibArray);
    uint8_t Configure_BPTCalibrationMode();
    uint8_t Start_BPTCalibrationMode(uint8_t calIndex, uint8_t systolicValue, uint8_t dystolicValue);

    //@note maybe as private functions
    uint8_t loadBPTCalibVector(uint8_t *buffer, uint16_t buffer_size);
    uint8_t EnableBPT_Algorithm(uint8_t mode);

private:
    uint8_t read_byte(uint8_t data1, uint8_t data2, uint8_t &return_byte);
    uint8_t read_multiple_bytes(uint8_t data1, uint8_t data2, uint8_t *read_buffer, uint8_t read_length);

    uint8_t write_byte(uint8_t data1, uint8_t data2, uint8_t data3);
    uint8_t write_byte_with_custom_cmd_delay(uint8_t data1, uint8_t data2, uint8_t data3, uint16_t cmd_delay);
    uint8_t write_multiple_bytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t *buffer, uint16_t buffer_size);
    uint8_t write_multiple_bytes(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t *buffer, uint16_t buffer_size, uint16_t cmd_delay);
    uint8_t setCalibrationIndex(uint8_t calIndex, uint8_t systolicValue, uint8_t dystolicValue);
    uint8_t setCalibrationIndex(uint8_t calIndex);
};

#endif /* __REWIRE_MAX32664_H */
