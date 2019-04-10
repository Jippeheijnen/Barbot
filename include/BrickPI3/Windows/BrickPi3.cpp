//
// Created by niels on 3/4/2019.
//

#include <iostream>
#include "../BrickPi3.h"


/**
 * Holds data for a Lego Motor
 */
struct Motor {
    char id = 't';
    std::string power = "0";
    std::string dps = "0";
    std::string limit_power = "0";
    std::string limit_dps = "0";
    std::string encoder = "0";

};

/**
 * Struct for holding all BrickPi motors.
 * Why this couldn't just be an array, only god knows
 */
struct MotorData {
    Motor A, B, C, D;
};

Motor &getPort(int8_t port);

void printStates();

MotorData data = {};


BrickPi3::BrickPi3(uint8_t addr) {

}

int BrickPi3::detect(bool critical) {
    return 0;
}

int BrickPi3::get_manufacturer(char *str) {
    return 0;
}

int BrickPi3::get_board(char *str) {
    return 0;
}

int BrickPi3::get_version_hardware(char *str) {
    return 0;
}

int BrickPi3::get_version_firmware(char *str) {
    return 0;
}

int BrickPi3::get_id(char *str) {
    return 0;
}

int BrickPi3::set_led(uint8_t value) {
    return 0;
}

float BrickPi3::get_voltage_3v3() {
    return 0;
}

float BrickPi3::get_voltage_5v() {
    return 0;
}

float BrickPi3::get_voltage_9v() {
    return 0;
}

float BrickPi3::get_voltage_battery() {
    return 0;
}

int BrickPi3::get_voltage_3v3(float &voltage) {
    return 0;
}

int BrickPi3::get_voltage_5v(float &voltage) {
    return 0;
}

int BrickPi3::get_voltage_9v(float &voltage) {
    return 0;
}

int BrickPi3::get_voltage_battery(float &voltage) {
    return 0;
}

int BrickPi3::set_sensor_type(uint8_t port, uint8_t type, uint16_t flags, i2c_struct_t *i2c_struct) {
    return 0;
}

int BrickPi3::transact_i2c(uint8_t port, i2c_struct_t *i2c_struct) {
    return 0;
}

int BrickPi3::get_sensor(uint8_t port, sensor_val_struct_t &sensor_val_struct) {
    return 0;
}

int BrickPi3::set_motor_power(uint8_t port, uint8_t power) {

    getPort(port).power = std::to_string((int) power);
    printStates();
    return 0;
}

int BrickPi3::set_motor_position(uint8_t port, int32_t position) {
    std::cout << "(" << getPort(port).id << ") " << "Setting Position: " << (int) position << std::endl;
    printStates();
    return 0;
}

int BrickPi3::set_motor_position_relative(uint8_t port, int32_t position) {
    std::cout << "(" << getPort(port).id << ") " << "Adding Position: " << (int) position << std::endl;
    return 0;
}

int BrickPi3::set_motor_dps(uint8_t port, int16_t dps) {
    getPort(port).dps = std::to_string((int) dps);
    printStates();
    return 0;
}

int BrickPi3::set_motor_limits(uint8_t port, uint8_t power, uint16_t dps) {
    getPort(port).limit_power = std::to_string((int) power);
    getPort(port).limit_dps = std::to_string((int) power);
    printStates();
    return 0;
}

int BrickPi3::get_motor_status(uint8_t port, uint8_t &state, int8_t &power, int32_t &position, int16_t &dps) {
    return 0;
}

int BrickPi3::offset_motor_encoder(uint8_t port, int32_t position) {
    std::cout << "(" << getPort(port).id << ") " << "Offsetting Encoder: " << (int) position << std::endl;
    return 0;
}

int BrickPi3::reset_motor_encoder(uint8_t port, int32_t &value) {
    return 0;
}

int BrickPi3::reset_motor_encoder(uint8_t port) {
    return 0;
}

int BrickPi3::set_motor_encoder(uint8_t port, int32_t value) {
    getPort(port).encoder = std::to_string((int) value);
    printStates();
    return 0;
}

int BrickPi3::get_motor_encoder(uint8_t port, int32_t &value) {
    return 0;
}

int32_t BrickPi3::get_motor_encoder(uint8_t port) {
    return 0;
}

int BrickPi3::reset_all() {
    return 0;
}

int BrickPi3::spi_write_8(uint8_t msg_type, uint8_t value) {
    return 0;
}

int BrickPi3::spi_read_16(uint8_t msg_type, uint16_t &value) {
    return 0;
}

int BrickPi3::spi_read_32(uint8_t msg_type, uint32_t &value) {
    return 0;
}

int BrickPi3::spi_read_string(uint8_t msg_type, char *str, uint8_t chars) {
    return 0;
}

std::string fill(std::string &value, const size_t &size) {
    bool side = true;
    for (size_t i = value.size(); i < size; i++) {
        if (side)
            value += " ";
        else
            value = " " + value;
        side = !side;
    }
    return value;
}

void printStates() {
    std::cout
//            << fill(data.A.power, 8) << " " << fill(data.A.dps, 8) << " " << fill(data.A.encoder, 8) << " " << fill(data.A.limit_dps, 8) << " " << fill(data.A.limit_power, 8) << " | "
            << fill(data.B.power, 8) << " " << fill(data.B.dps, 8) << " " << fill(data.B.encoder, 8) << " "
            << fill(data.B.limit_dps, 8) << " " << fill(data.B.limit_power, 8) << " | "
            << fill(data.C.power, 8) << " " << fill(data.C.dps, 8) << " " << fill(data.C.encoder, 8) << " "
            << fill(data.C.limit_dps, 8) << " " << fill(data.C.limit_power, 8) << " | "
            //            << fill(data.D.power, 8) << " " << fill(data.D.dps, 8) << " " << fill(data.D.encoder, 8) << " " << fill(data.D.limit_dps, 8) << " " << fill(data.D.limit_power, 8) << " | " << std::endl
            << std::endl;
}

Motor &getPort(int8_t port) {
    switch (port) {
        case PORT_A:
            return data.A;
        case PORT_B:
            return data.B;
        case PORT_C:
            return data.C;
        case PORT_D:
            return data.D;
        default:
            return data.A;
    }
}
